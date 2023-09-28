package il.co.ILRD.sll;

public class LinkList {
    private Node head;

    public LinkList(){
        this.head = null;
    }

    public static class Node {
        private final Object data;
        private Node next;

        private Node(Object data, Node next) {
            this.data = data;
            this.next = next;
        }

        public void setNext(Node node){
            this.next = node;
        }

        public Node getNext(){
            return this.next;
        }

        public boolean hasNext() {
            return (null != this.next);
        }
    }

    private static class ListIteratorIMP implements ListIterator {
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
        ListIterator iter = this.Begin();
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
        this.head = new Node(data, this.head);
    }

    public Object popFront() {
        Object toReturn = this.head.data;
        this.head = this.head.next;

        return (toReturn);
    }

    public ListIterator Find(Object data) {
        ListIterator iter = this.Begin();

        while (iter.hasNext() &&
                !data.equals(((ListIteratorIMP) iter).current.data)) {
            iter.Next();
        }//Breaks encapsulation :(

        return (iter);
    }

    public ListIterator Begin() {
        return (new ListIteratorIMP(this.head));
    }
}