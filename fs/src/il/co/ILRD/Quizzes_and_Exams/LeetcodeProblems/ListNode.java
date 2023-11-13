package il.co.ILRD.Quizzes_and_Exams.LeetcodeProblems;

public class ListNode {
    public int value;
    public ListNode next;

    public ListNode() {
    }

    public ListNode(int val) {
        this.value = val;
    }

    public ListNode(int val, ListNode next) {
        this.value = val;
        this.next = next;
    }

    @Override
    public String toString() {
        ListNode iter = this;
        StringBuilder builder = new StringBuilder();

        while (null != iter.next) {
            builder.append(iter.value);
            iter = iter.next;
        }

        return builder.reverse().toString();
    }
}

class Solution {
    public static ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        return toList(toNumber(l1) + toNumber(l2));
    }

    private static int toNumber(ListNode list) {
        int toReturn = 0;
        int multiplier = 1;
        ListNode iter = null;

        if (null == list) {
            return 0;
        }

        iter = list;

        while (null != iter) {
            toReturn += multiplier * list.value;
            multiplier *= 10;
            iter = iter.next;
        }

        return toReturn;
    }

    private static ListNode toList(int number) {
        ListNode toReturn = null;
        ListNode iter = null;

        if (0 == number) {
            return new ListNode(0, null);
        }

        toReturn = new ListNode();
        iter = toReturn;

        while (0 != number) {
            iter.value = number % 10;

            iter.next = new ListNode();
            iter = iter.next;

            number /= 10;
        }

        iter.next = null;

        return toReturn;
    }

    public static void main(String[] args) {
        ListNode list2 = new ListNode(1, null);
        ListNode node3 = new ListNode(9, null);
        ListNode node2 = new ListNode(9, node3);
        ListNode list1 = new ListNode(9, node2);

        ListNode result = Solution.addTwoNumbers(list1, list2);

        System.out.println(result);

    }
}
