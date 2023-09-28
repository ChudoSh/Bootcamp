package il.co.ILRD.design_patterns.observer;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public class Dispatcher<V> {
    private List<Callback<V>> callBacks;

    public Dispatcher() {
        this.callBacks = new ArrayList<>();
    }

    public void subscribe(Callback<V> callBack) {
        callBack.setDispatcher(this);
        this.callBacks.add(callBack);
    }

    public void unsubscribe(Callback<V> callBack) {
        this.callBacks.remove(callBack);
    }

    public void notify(V data) {
        for (Callback<V> caller : callBacks) {
            caller.consumer.accept(data);
        }
    }

    public void notifyLast(V data) {
        for (Callback<V> caller : callBacks) {
            caller.consumer.accept(data);
            caller.cancel.run();
        }

        this.callBacks.clear();
    }

    public static abstract class Callback<U> {
        private Consumer<U> consumer;
        private Runnable cancel;
        private Dispatcher<U> dispatcher;

        public abstract void stop();

        protected void setDispatcher(Dispatcher<U> dispatcher) {
            this.dispatcher = dispatcher;
        }

        protected void setConsumer(Consumer<U> consumer) {
            this.consumer = consumer;
        }

        protected void setCancel(Runnable cancel) {
            this.cancel = cancel;
        }

        protected void stopDispatcher(){
            this.dispatcher.unsubscribe(this);
        }

    }

    public static class CallbackIMP<V> extends Callback<V> {
        public CallbackIMP(Consumer<V> consumer, Runnable cancel) {
            this.setCancel(cancel);
            this.setConsumer(consumer);
        }

        @Override
        public void stop() {
            this.stopDispatcher();
        }
    }


}
