package co.il.ILRD.DS2Exam;

public class Node {
        private final Object data;
        private Node next;

        public Node(Object data, Node next) {
            this.data = data;
            this.next = next;
        }

        public void setNext(Node node){
            this.next = node;
        }

        public Node getNext(){
            return this.next;
        }
        public Object getData(){
            return this.data;
        }

        public boolean hasNext() {
            return (null != this.next);
        }

}
