package il.co.ILRD.SLL;

public class LinkList {
    private Node head;
    private class Node {
        private Object data;
        private Node next;

        private Node(Object data, Node next) {
            this.data = data;
            this.next = next;
        }
    }
    private class ListIteratorIMP implements ListIterator {
        private Node current;

        private ListIteratorIMP(Node node) {
            this.current = node;
        }

        @Override
        public Object Next() {
            Object toReturn = this.current.data;
            this.current = current.next;

            return (toReturn);
        }

        @Override
        public boolean hasNext() {
            return (null != this.current);
        }// if is it legal to move next
    }

    public int Size() {
        ListIteratorIMP iter = (ListIteratorIMP) this.Begin();
        int count = 0;

        while (iter.hasNext()) {
            iter.Next();
            ++(count);
        }

        return (count);
    }

    public boolean isEmpty() {
        return (null == this.head);
    }

    public void pushFront(Object data) {
        Node newNode = new Node(data, this.head);
        this.head = newNode;
    }

    public Object popFront() {
        assert !this.isEmpty();

        Object toReturn = this.head.data;
        this.head = this.head.next;

        return (toReturn);
    }

    public ListIterator Find(Object data) {
        ListIteratorIMP iter = (ListIteratorIMP) this.Begin();

        while (iter.hasNext() && !data.equals(iter.current.data)) {
            iter.Next();
        }

        return (iter);
    }

    public ListIterator Begin() {
        return (new ListIteratorIMP(this.head));
    }
}