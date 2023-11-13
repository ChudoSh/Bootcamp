package il.co.ILRD.Quizzes_and_Exams.Simulations;


public class AddOneToList {
    private static final int ONE = 1;
    private static final int ZERO = 0;

    public static void main(String[] args) {
        Node head = new Node(9, null);
        head = addOne(head);

        Node iter = head;

        while (null != iter) {
            System.out.println(iter.getDigit());
            iter = iter.getNext();
        }
    }

    public static Node addOne(Node head) {
        return (recAddOne(head) && updateNode(head, ZERO))
                ? new Node(ONE, head) : head;
    }

    private static boolean recAddOne(Node head) {
        if (null == head.getNext() || recAddOne(head.getNext())) {
            int NINE = 9;
            return updateNode(head, NINE);
        }

        return false;
    }

    private static boolean updateNode(Node node, int toCheck) {
        if (toCheck == node.getDigit()) {
            node.setDigit(ZERO);
            return true;
        }

        node.setDigit(node.getDigit() + ONE);
        return false;
    }

    public static class Node {

        private int digit;
        private Node next;

        public Node() {
        }

        public Node(int value) {
            this(value, null);
        }

        public Node(int value, Node next) {
            this.digit = value;
            this.next = next;
        }

        public Node getNext() {
            return next;
        }

        public void setNext(Node next) {
            this.next = next;
        }

        public int getDigit() {
            return digit;
        }

        public void setDigit(int digit) {
            this.digit = digit;
        }

    }

}
