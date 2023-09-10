package il.co.ILRD.DesignPatterns.Observer;

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
        Consumer<U> consumer;
        Runnable cancel;
        Dispatcher<U> dispatcher;

        public abstract void stop();

        protected void setDispatcher(Dispatcher<U> dispatcher) {
            this.dispatcher = dispatcher;
        }

    }

    public static class CallbackIMP<V> extends Callback<V> {

        public CallbackIMP(Consumer<V> consumer, Runnable cancel) {
            this.consumer = consumer;
            this.cancel = cancel;
        }

        @Override
        public void stop() {
            this.dispatcher.unsubscribe(this);

        }
    }


}
