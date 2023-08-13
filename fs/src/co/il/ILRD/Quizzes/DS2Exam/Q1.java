package co.il.ILRD.Quizzes.DS2Exam;

public class Q1 {
    public static void FlipListIteratively(Node head) {
        Node prev = null;
        Node current = head;
        Node follow;

        while (current.hasNext()) {
            follow = current.getNext();
            current.setNext(prev);
            prev = current;
            current = follow;
        }

        current.setNext(prev);
    }

    static void FlipListRecursion(Node head) {
        RecursionFlip(head, null);
    }

    private static void RecursionFlip(Node current, Node prev) {
        Node follow;

        if (!current.hasNext()) {
            current.setNext(prev);
            return;
        }

        follow = current.getNext();
        current.setNext(prev);
        prev = current;
        current = follow;

        RecursionFlip(current, prev);
    }

    public static void printList(Node head) {
        if (head == null) {
            System.out.println();
            return;
        }
        System.out.print(head.getData() + " -> ");

        printList(head.getNext());
    }
}
