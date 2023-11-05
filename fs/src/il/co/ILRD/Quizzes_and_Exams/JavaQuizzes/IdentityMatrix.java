package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

public class IdentityMatrix {
    public static int findMaxIdentityMatrix(int[][] matrix) {
        int j = 0;
        int counter = 0;

        if (matrix[0].length != matrix.length) {
            return 0;
        }

        while (j < matrix.length && 1 != matrix[j][j]) {
            ++j;
        }

        if (j == matrix.length) {
            return 0;
        }

        for (int i = j; i < matrix.length; ++i) {
            int[] row = matrix[i];
            int[] col = getColumn(matrix, i);

            if (checkDimension(row, i) && checkDimension(col, i)) {
                ++counter;
            }
        }

        return counter;
    }

    private static boolean checkDimension(int[] dimension, int index) {
        ++index;

        while (index < dimension.length && 0 == dimension[index]) {
            ++index;
        }

        return index == dimension.length;
    }

    private static int[] getColumn(int[][] array, int index) {
        int[] column = new int[array[0].length]; // Here I assume a rectangular 2D array!

        for (int i = 0; i < column.length; ++i) {
            column[i] = array[i][index];
        }

        return column;
    }

    public static void main(String[] args) {
        int[][] matrix = {{4, 3, 9, 0, 2,},
                {1, 2, 3, 4, 5},
                {6, 3, 1, 2, 0},
                {7, 6, 0, 1, 0},
                {3, 2, 0, 0, 1}};

        System.out.println(IdentityMatrix.findMaxIdentityMatrix(matrix));
    }
}
