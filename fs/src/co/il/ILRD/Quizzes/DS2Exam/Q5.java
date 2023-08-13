package co.il.ILRD.DS2Exam;

public class Q5 {
    private TreeNode root = null;

    private enum Children {
        FAIL(-1),
        LEFT(0),
        RIGHT(1);

        private int child;

        Children(int child) {
            this.child = child;
        }
    }

    private class TreeNode {
        private TreeNode parent = null;
        private TreeNode left = null;
        private TreeNode right = null;
        private Integer data = null;

        private TreeNode(Integer data) {
            setData(data);
        }

        public TreeNode getParent() {
            return parent;
        }

        public TreeNode getChild(Children child) {
            return (child == Children.LEFT) ? this.left : this.right;
        }

        public Integer getData() {
            return data;
        }

        public void setParent(TreeNode parent) {
            this.parent = parent;
        }

        public void setChild(TreeNode childNode, Children childPos) {
            if (Children.LEFT == childPos) {
                this.left = childNode;
            } else {
                this.right = childNode;
            }
        }

        public void setData(Integer data) {
            this.data = data;
        }

    }

    public Q5(Integer data) {
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
        Children dir = this.getDirection(iterator, new_data);

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

        if (Integer.compare(iterator.getData(), data) > 0) {
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
