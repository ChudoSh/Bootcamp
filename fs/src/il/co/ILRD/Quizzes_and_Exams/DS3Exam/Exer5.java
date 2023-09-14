package il.co.ILRD.Quizzes_and_Exams.DS3Exam;

import java.util.List;

public class Exer5 {
    public int countIslandsInBitMap(List<List<Boolean>> bitMap) {
        int ROW = bitMap.size();
        int COL = bitMap.get(0).size();
        int count = 0;
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                if (bitMap.get(i).get(j)) {
                    ++count;
                    recursiveIslandCoutning(bitMap,ROW, COL, i, j); // traversal starts from
                    // current cell
                }
            }
        }

        return count;
    }

    public void recursiveIslandCoutning(List<List<Boolean>> bitMap, int currentRow, int currentCol, int nextRow, int nextCol) {
        if ((nextRow < 0) || (nextCol < 0) || (nextRow > (currentRow - 1)) || (nextCol > (currentCol - 1))
                || !bitMap.get(nextRow).get(nextCol)) {
            return;
        }

        if (bitMap.get(nextRow).get(nextCol)){
            bitMap.get(nextRow).set(nextCol, false);
            recursiveIslandCoutning(bitMap, currentRow, currentCol, nextRow + 1, nextCol);
            recursiveIslandCoutning(bitMap, currentRow, currentCol, nextRow, nextCol);
            recursiveIslandCoutning(bitMap, currentRow, currentCol, nextRow - 1, nextCol);
            recursiveIslandCoutning(bitMap, currentRow, currentCol, nextRow, nextCol + 1);
            recursiveIslandCoutning(bitMap, currentRow, currentCol, nextRow, nextCol - 1);
            recursiveIslandCoutning(bitMap, currentRow, currentCol, nextRow + 1, nextCol + 1);
            recursiveIslandCoutning(bitMap, currentRow, currentCol, nextRow - 1, nextCol - 1);
            recursiveIslandCoutning(bitMap, currentRow, currentCol, nextRow + 1, nextCol - 1);
            recursiveIslandCoutning(bitMap, currentRow, currentCol, nextRow - 1, nextCol + 1);
        }
    }
}