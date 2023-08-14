package co.il.ILRD.Quizzes_and_Exams.DS2Exam;

public class TreeNode {
    private TreeNode parent = null;
    private TreeNode left = null;
    private TreeNode right = null;
    private Integer data = null;

    TreeNode(Integer data) {
        setData(data);
    }

    public TreeNode getParent() {
        return parent;
    }

    public TreeNode getChild(Q5_BSTInsert.Children child) {
        return (child == Q5_BSTInsert.Children.LEFT) ? this.left : this.right;
    }

    public Integer getData() {
        return data;
    }

    public void setParent(TreeNode parent) {
        this.parent = parent;
    }

    public void setChild(TreeNode childNode, Q5_BSTInsert.Children childPos) {
        if (Q5_BSTInsert.Children.LEFT == childPos) {
            this.left = childNode;
        } else {
            this.right = childNode;
        }
    }

    public void setData(Integer data) {
        this.data = data;
    }
}
