package co.il.ILRD.Quizzes_and_Exams.DS2Exam;

public class Q5_BSTInsert {
    private TreeNode root = null;

    enum Children {
        FAIL(-1),
        LEFT(0),
        RIGHT(1);

        Children(int child) {
        }
    }

    public Q5_BSTInsert(Integer data) {
        this.root = new TreeNode(data);

    }

    public TreeNode insertIteratively(Integer new_data) {
        TreeNode toInsert = new TreeNode(new_data);
        TreeNode iterator = this.root;
        Children dir = this.getDirection(iterator, new_data);

        if (isLeaf(this.root)) {
            this.root.setChild(toInsert, Children.LEFT);
            toInsert.setParent(this.root);
            return toInsert;
        }

        while (dir != Children.FAIL && null != iterator.getChild(dir)) {
            iterator = iterator.getChild(dir);
            dir = this.getDirection(iterator, new_data);
        }

        if (Children.FAIL == dir) {
            return null;
        }

        iterator.setChild(toInsert, dir);
        toInsert.setParent(iterator);

        return toInsert;
    }

    public TreeNode insertRecursively(Integer new_data) {
        TreeNode toInsert = new TreeNode(new_data);
        TreeNode iterator = this.root;

        if (isLeaf(this.root)) {
            this.root.setChild(toInsert, Children.LEFT);
            toInsert.setParent(this.root);
            return toInsert;
        }

        return Recursion(iterator, toInsert);
    }

    private TreeNode Recursion(TreeNode iterator, TreeNode toInsert) {

        Children dir = this.getDirection(iterator, toInsert.getData());

        if (dir == Children.FAIL) {
            return null;
        }

        if (null == iterator.getChild(dir)) {
            iterator.setChild(toInsert, dir);
            toInsert.setParent(iterator);
            return toInsert;
        }

        iterator = iterator.getChild(dir);
        return Recursion(iterator, toInsert);
    }

////    static void Inorder(Node root) {
////        if (root == null) {
////            return;
////        } else {
////            Inorder(root.left);
////            System.out.print(root.val + " ");
////            Inorder(root.right);
////        }
//    }

    public static int insertToTreeArray(int[] arr, int new_data) {
        int i = 0;

        while (0 != arr[i]) {
            if (new_data > arr[i]) {
                i = i * 2 + 2;
            } else if (new_data < arr[i]) {
                i = i * 2 + 1;
            } else {
                return -1;
            }
        }

        arr[i] = new_data;

        return i;
    }

    private Children getDirection(TreeNode iterator, Integer data) {

        if (iterator.getData() > data) {
            return Children.LEFT;
        } else if (Integer.compare(iterator.getData(), data) > 0) {
            return Children.RIGHT;
        } else {
            return Children.FAIL;
        }
    }

    private boolean isLeaf(TreeNode current) {
        return (current.getChild(Children.LEFT) == null &&
                current.getChild(Children.RIGHT) == null);
    }

}
