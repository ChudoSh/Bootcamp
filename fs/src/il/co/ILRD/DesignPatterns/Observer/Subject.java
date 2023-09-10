package il.co.ILRD.DesignPatterns.Observer;

public class Subject<V> {
    private Dispatcher<V> dispatcher;

    void notify(V data) {
        this.dispatcher.notify(data);
    }

    void subscribe(Dispatcher.Callback<V> callBack) {
        this.dispatcher.subscribe(callBack);
    }

    void notifyLast(V data) {
        this.dispatcher.notifyLast(data);
    }
}
