package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.Stack;

public class ExpressionTree {
    private NodeComposite root;

    enum OperatorEnum {
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
        private char val;

        OperatorEnum(char character) {
            this.val = character;
        }

        public abstract double calc(NodeComposite Left, NodeComposite Right);
    }

    public ExpressionTree(String expressio) {
        //DO some stuff
    }

    interface NodeComposite {
        double calculate();
    }

    private class Operand implements NodeComposite {
        double val;

        //Constuctor

        @Override
        public double calculate() {
            return this.val;
        }
    }

    private class Operator implements NodeComposite {
        NodeComposite Lchild;
        NodeComposite Rchild;
        OperatorEnum op;

        //Constuctor

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