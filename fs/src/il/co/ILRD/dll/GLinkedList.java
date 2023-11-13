package il.co.ILRD.dll;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class GLinkedList<T> implements Iterable<T> {
    private Node<T> head;
    private int expectedModCounter = 0;

    public GLinkedList() {
        this.head = new Node<>(null, null, null);
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
        private final S data;

        private Node(S data, Node<S> next, Node<S> prev) {
            this.data = data;
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
        if (this.head == null) {
            throw new NoSuchElementException();
        }
        T toReturn = this.head.getData();

        Node<T> toRemove = this.head;
        this.head = this.head.getNext();
        this.head.setPrev(null);

        toRemove.setNext(null);
        toRemove.setPrev(null);

        --expectedModCounter;

        return (toReturn);
    }

    public int count() {
        int count = 0;

        for (T ignore : this) {
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

    public static <U> void merge(GLinkedList<U> dest,
                                 GLinkedList<U> src) {
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
        src.head = new Node<>(null, null, null);

        toFree.setPrev(null);
    }
}
