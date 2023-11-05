package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.Stack;

public class ExpressionTree {
    private NodeComposite root;

    public ExpressionTree(String expression){
        //do something to parse the tree correctly, if it is valid
    }

    private enum OperatorEnum {
        PLUS('+') {
            @Override
            public double calc(NodeComposite Left, NodeComposite Right) {
                return Left.calculate() + Right.calculate();
            }
        },
        MINUS('-') {
            @Override
            public double calc(NodeComposite Left, NodeComposite Right) {
                return Left.calculate() - Right.calculate();
            }
        },
        DIV('/') {
            @Override
            public double calc(NodeComposite Left, NodeComposite Right) {
                return Left.calculate() / Right.calculate();
            }
        },
        MULTI('*') {
            @Override
            public double calc(NodeComposite Left, NodeComposite Right) {
                return Left.calculate() * Right.calculate();
            }
        };
        private char value;

        OperatorEnum(char character) {
            this.value = character;
        }

        public abstract double calc(NodeComposite Left, NodeComposite Right);
    }

    private interface NodeComposite {
        double calculate();
    }

    private class Operand implements NodeComposite {
        private final double val;

        public Operand(double value){
            this.val = value;
        }

        @Override
        public double calculate() {
            return this.val;
        }
    }

    private class Operator implements NodeComposite {
        private NodeComposite Lchild;
        private NodeComposite Rchild;
        private OperatorEnum op;

        public Operator(NodeComposite Lchild, NodeComposite Rchild, OperatorEnum operator){
            this.Lchild = Lchild;
            this.Rchild = Rchild;
            this.op = operator;
        }

        @Override
        public double calculate() {
            return op.calc(Lchild, Rchild);
        }
    }

    public double calculate() {
        return this.root.calculate();
    }
}

// +,3,*,+,2,5,9