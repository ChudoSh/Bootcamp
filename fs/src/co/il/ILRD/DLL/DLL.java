package co.il.ILRD.DLL;

import javax.naming.OperationNotSupportedException;
import java.util.ConcurrentModificationException;
import java.util.Iterator;

public class DLL<T> implements Iterable<T> {
    private Node<T> head;
    private static int expectedModCounter = 0;

    public DLL() {
        this.head = new Node<>();
    }

    @Override
    public Iterator<T> iterator() {
        return new IteratorIMP<>(this.head);
    }

    private class IteratorIMP<T> implements Iterator<T> {
        private Node<T> current;
        private final int currentModCounter;

        private IteratorIMP(Node<T> head) {
            this.current = head;
            currentModCounter = expectedModCounter;
        }

        @Override
        public boolean hasNext() {
            return (null != this.current.getNext());
        }

        @Override
        public T next() {
            if (expectedModCounter != currentModCounter) {
                throw new RuntimeException();
            }
            T toReturn = this.current.getData();
            this.current = this.current.getNext();

            return toReturn;
        }
    }

    private static class Node<S> {
        private Node<S> next;
        private Node<S> prev;
        private S data;

        private Node() {
        }

        private Node(S data, Node<S> next, Node<S> prev) {
            this.data = (S) data;
            this.next = next;
            this.prev = prev;
            next.setPrev(this);
        }

        private Node<S> getNext() {
            return (next);
        }

        private void setNext(Node<S> next) {
            this.next = next;
        }

        private void setPrev(Node<S> prev) {
            this.prev = prev;
        }

        private S getData() {
            return this.data;
        }

    }

    public void pushFront(T data) {
        this.head = new Node<>(data, this.head, null);
        ++expectedModCounter;
    }

    public T popFront() {
        T toReturn = this.head.getData();
        this.head = this.head.getNext();
        --expectedModCounter;

        return (toReturn);
    }

    public int count() {
        int count = 0;

        for (T t : this) {
            ++count;
        }

        return count;
    }

    public Iterator<T> find(T data) {
        T toCompare = this.iterator().next();
        while (this.iterator().hasNext() &&
                !data.equals(toCompare)) {
            toCompare = this.iterator().next();
        }//Breaks encapsulation :(

        return (this.iterator());
    }

    public void printDList() {
        for (T toPrint : this) {
            System.out.println(toPrint.toString());
        }
    }

    public boolean isEmpty() {
        return (null == this.head.getNext());
    }

    public static <U> DLL<U> merge(DLL<U> dest,
                                   DLL<U> src) {

        ++dest.expectedModCounter;
        ++src.expectedModCounter;

        Node<U> runner = dest.head;
        Node<U> toFree;

        while (null != runner.getNext().getNext()) {
            runner = runner.getNext();
        }

        toFree = runner.getNext();

        runner.setNext(src.head);
        src.head.setPrev(runner);
        src.head = new Node<>();

        toFree.setPrev(null);

        return dest;
    }
}
