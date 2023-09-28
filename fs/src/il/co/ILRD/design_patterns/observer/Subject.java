package il.co.ILRD.design_patterns.observer;

public class Subject<V> {
    private Dispatcher<V> dispatcher;

    public void notify(V data) {
        this.dispatcher.notify(data);
    }

    public void subscribe(Dispatcher.Callback<V> callBack) {
        this.dispatcher.subscribe(callBack);
    }

    public void notifyLast(V data) {
        this.dispatcher.notifyLast(data);
    }
}
