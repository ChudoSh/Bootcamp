/*
Dev: BarSh
Rev: Daniel
Status: Approved
Date: 5.9.23
*/

package il.co.ILRD.thread_pool;

import il.co.ILRD.waitable_queue.SemWaitableQueue;

import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;

public class ThreadPool implements Executor {
    private AtomicInteger numOfThreads;
    private final SemWaitableQueue<Task<?>> tasks;
    private Semaphore semPause;
    private int pausedThreads = 0;
    private volatile boolean isShutdown = false;
    private volatile boolean isPaused = false;
    private final int MIN_PRIORITY = Priority.LOW.value - 1;
    private final int MAX_PRIORITY = Priority.HIGH.value + 1;

    /*==============================Main functions============================*/
    public ThreadPool(int numOfThreads) {
        this.numOfThreads = new AtomicInteger(
0);
        this.tasks = new SemWaitableQueue<>(numOfThreads);
        this.semPause = new Semaphore(0);
        this.createWorkingThreads(numOfThreads);
    }

    public ThreadPool() {
        this(Runtime.getRuntime().availableProcessors());
    }

    public <V> Future<V> submit(Callable<V> command, Priority priority) {
        return this.submit(command, priority.getValue());
    }

    public <V> Future<V> submit(Callable<V> command) {
        return this.submit(command, Priority.DEFAULT);
    }

    public Future<Void> submit(Runnable command, Priority priority) {
        return this.submit(command, priority, null);
    }

    public <V> Future<V> submit(Runnable command, Priority priority, V returnValue) {
        return this.submit(toCallable(command, returnValue), priority);
    }

    private <V> Future<V> submit(Callable<V> command, int priority) {
        if (this.isShutdown) {
            return null;
        }

        Task<V> newTask = new Task<>(command, priority);
        this.tasks.enqueue(newTask);

        return newTask.getFuture();
    }

    @Override
    public void execute(Runnable command) {
        this.submit(command, Priority.DEFAULT);
    }

    public void setNumOfThreads(int numOfThreads) { //add pausing factor
        int newNumOfThreads;
        int oldNumOfThreads = this.numOfThreads.get();

        newNumOfThreads = oldNumOfThreads - numOfThreads;

        if (0 > newNumOfThreads) {
            this.createWorkingThreads(-newNumOfThreads);
        } else if (0 < newNumOfThreads) {
            this.destroyWorkingThreads(newNumOfThreads, this.MAX_PRIORITY);
        }

    }

    public void pause() {
        Callable<?> pause = () -> { //poison pill
            this.semPause.acquire();
            return null;
        };

        int oldNumPausedThreads = this.pausedThreads;
        this.pausedThreads = this.numOfThreads.get();
        for (int i = oldNumPausedThreads; i < this.pausedThreads; ++i) {
            this.submit(pause, this.MAX_PRIORITY);
        }
        this.isPaused = true;
    }

    public void resume() {
        if (this.isPaused) {
            this.semPause.release(this.pausedThreads);
            this.pausedThreads = 0;
        }
    }

    public void shutDown() {
        this.resume();
        this.destroyWorkingThreads(this.numOfThreads.get(), this.MIN_PRIORITY);
        this.isShutdown = true;
    }

    public void awaitTermination(long timeout, TimeUnit unit) throws TimeoutException {
        long end = System.currentTimeMillis() + unit.toMillis(timeout);

        while (0 != this.numOfThreads.get() && end >= System.currentTimeMillis()) {
            try {
                TimeUnit.SECONDS.sleep(1);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }

        if (0 != numOfThreads.get()) {
            throw new TimeoutException();
        }
    }

    public void awaitTermination() {
        while (0 != numOfThreads.get()) {
            try {
                TimeUnit.SECONDS.sleep(1);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }

    /*============================Priority====================================*/
    public enum Priority {
        LOW(1),
        DEFAULT(5),
        HIGH(10);

        private final int value;

        Priority(int value) {
            this.value = value;
        }

        public int getValue() {
            return this.value;
        }
    }

    /*==============================Thread====================================*/
    private class WorkingThread extends Thread {
        private boolean toStop = false;

        {
            ThreadPool.this.numOfThreads.incrementAndGet();
        }

        @Override
        public void run() {
            while (!toStop) {
                try {
                    ThreadPool.this.tasks.dequeue().execute();
                } catch (InterruptedException e) {
                    boolean ignored = Thread.interrupted();
                } catch (Exception e) {
                    throw new RuntimeException(e);
                }
            }
            ThreadPool.this.numOfThreads.decrementAndGet();
        }
    }

    /*===============================Task=====================================*/
    private class Task<V> implements Comparable<Task<V>> {
        private final int priority;
        private final TaskFuture<V> future;
        private Thread workingThread;

        public Task(Callable<V> callable, int priority) {
            this.future = new TaskFuture<>(callable, this);
            this.priority = priority;
        }

        public int getPriority() {
            return this.priority;
        }

        public void execute() throws Exception {
            this.workingThread = Thread.currentThread();
            this.future.run();
        }

        public TaskFuture<V> getFuture() {
            return this.future;
        }

        @Override
        public int compareTo(Task<V> task) {
            return task.getPriority() - this.priority;
        }
    }

    /*==============================TaskFuture================================*/
    private class TaskFuture<V> implements Future<V> {
        private volatile boolean isCancelFlag = false;
        private volatile boolean isDoneFlag = false;
        private V value;
        private Callable<V> callable;
        private Task<V> parentTask;
        private ExecutionException thrownException;

        public TaskFuture(Callable<V> callable, Task<V> task) {
            this.callable = callable;
            this.parentTask = task;
        }

        public void run() throws Exception {
            try {
                this.value = this.callable.call();
            } catch (ExecutionException e) {
                this.thrownException = e;
            } finally {
                this.isDoneFlag = true;
            }
        }

        public V getValue() throws ExecutionException {
            if (null != this.thrownException) {
                throw this.thrownException;
            }
            return value;
        }

        @Override
        public boolean cancel(boolean mayInterruptIfRunning) {
            if (this.isCancelled() || this.isDone()) {
                return false;
            }

            if (tasks.remove(this.parentTask)) {
                this.isCancelFlag = true;
            } else if (mayInterruptIfRunning) {
                this.parentTask.workingThread.interrupt();
            }

            this.isCancelFlag = true;
            return true;
        }

        @Override
        public boolean isCancelled() {
            return this.isCancelFlag;
        }

        @Override
        public boolean isDone() {
            return this.isDoneFlag;
        }

        @Override
        public V get() throws InterruptedException, ExecutionException {
            if (this.isCancelled()) {
                throw new CancellationException();
            }

            while (!this.isDone()) {
                TimeUnit.SECONDS.sleep(1);
            }

            return this.getValue();
        }

        @Override
        public V get(long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
            if (this.isCancelled()) {
                throw new CancellationException();
            }

            long end = System.currentTimeMillis() + unit.toMillis(timeout);

            while (!this.isDone() && end >= System.currentTimeMillis()) {
                TimeUnit.SECONDS.sleep(1);
            }
            if (!this.isDone()) {
                throw new TimeoutException();
            }

            return this.getValue();
        }
    }

    /*===============================Private methods==========================*/
    private <V> Callable<V> toCallable(Runnable runnable, V returnValue) {
        return () -> {
            runnable.run();
            return returnValue;
        };
    }

    private void createWorkingThreads(int toCreate) {
        for (int i = 0; i < toCreate; ++i) {
            new WorkingThread().start();
        }
    }

    private void destroyWorkingThreads(int toDestroy, int priority) {
        Callable<?> destroyThread = () -> { //poison pill
            ((WorkingThread) (Thread.currentThread())).toStop = true;
            return null;
        };

        for (int i = 0; i < toDestroy; ++i) {
            this.submit(destroyThread, priority);
        }
    }
}
