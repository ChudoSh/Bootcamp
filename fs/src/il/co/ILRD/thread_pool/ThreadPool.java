/*
Dev: BarSh
Rev:
Status:
Date:
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
    private final int MIN_PRIORITY = Priority.LOW.value - 1;
    private final int MAX_PRIORITY = Priority.HIGH.value + 1;

    /*----------------------------------------------------------------*/
    public ThreadPool(int numOfThreads) {
        this.numOfThreads = new AtomicInteger(0);
        this.tasks = new SemWaitableQueue<>(numOfThreads);
        this.semPause = new Semaphore(0);
        createWorkingThreads(numOfThreads);
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
        if (isShutdown) {
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

    public void setNumOfThreads(int numOfThreads) {
        int newNumOfThreads = 0;
        int oldNumOfThreads = this.numOfThreads.get();

        newNumOfThreads = oldNumOfThreads - numOfThreads;

        if (0 > newNumOfThreads) {
            createWorkingThreads(-newNumOfThreads);
        } else if (0 < newNumOfThreads) {
            destroyWorkingThreads(newNumOfThreads, MAX_PRIORITY);
        }

    }

    public void pause() {
        Callable<?> pause = () -> { //posion pill
            semPause.acquire();
            return null;
        };

        int oldNumPausedThreads = this.pausedThreads;
        this.pausedThreads = this.numOfThreads.get();
        for (int i = oldNumPausedThreads; i < this.pausedThreads; ++i) {
            this.submit(pause, MAX_PRIORITY);
        }
    }

    public void resume() {
        this.semPause.release(this.pausedThreads);
        this.pausedThreads = 0;
    }

    public void shutDown() {
        this.resume();
        destroyWorkingThreads(this.numOfThreads.get(), MIN_PRIORITY);
        this.isShutdown = true;
    }

    public void awaitTermination(long timeout, TimeUnit unit) throws TimeoutException {
        long end = System.currentTimeMillis() + unit.toMillis(timeout);

        while (0 != numOfThreads.get() && end >= System.currentTimeMillis()) {
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

    /*----------------------------------------------------------------*/
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

    /*--------------------------------------
--------------------------*/
    private class WorkingThread extends Thread {
        private boolean toStop = false;

        {
            numOfThreads.incrementAndGet();
        }

        @Override
        public void run() {
            while (!toStop) {
                try {
                    tasks.dequeue().execute();
                } catch (InterruptedException e) {
                    boolean ignored = Thread.interrupted();
                } catch (Exception e) {
                    throw new RuntimeException(e);
                }

            }
            numOfThreads.decrementAndGet();
        }
    }

    /*---------------------------Task-------------------------------------*/
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

    /*------------------------------TaskFuture--------------------------------*/
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
                this.value = callable.call();
            } catch (ExecutionException e) {
                thrownException = e;
            } finally {
                isDoneFlag = true;
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
                isCancelFlag = true;
            } else if (mayInterruptIfRunning) { // what does it mean?
                this.parentTask.workingThread.interrupt();
            }

            this.isCancelFlag = true;
            return this.isCancelFlag;
        }

        @Override
        public boolean isCancelled() {
            return isCancelFlag;
        }

        @Override
        public boolean isDone() {
            return isDoneFlag;
        }

        @Override
        public V get() throws InterruptedException, ExecutionException {
            if (isCancelled()) {
                throw new CancellationException();
            }

            while (!isDone()) {
                TimeUnit.SECONDS.sleep(1); //again, why?
            }

            return getValue();
        }

        @Override
        public V get(long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
            if (isCancelled()) {
                throw new CancellationException();
            }

            long end = System.currentTimeMillis() + unit.toMillis(timeout);

            while (!isDone() && end >= System.currentTimeMillis()) {
                TimeUnit.SECONDS.sleep(1); //again, why?
            }
            if (!isDone()) {
                throw new TimeoutException();
            }

            return getValue();
        }
    }

    /***********************************************************/
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
        Callable<?> destroyThread = () -> {
            ((WorkingThread) (Thread.currentThread())).toStop = true;
            return null;
        };

        for (int i = 0; i < toDestroy; ++i) {
            submit(destroyThread, priority);
        }
    }
}
