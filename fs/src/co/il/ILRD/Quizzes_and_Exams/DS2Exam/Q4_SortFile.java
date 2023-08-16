package co.il.ILRD.Quizzes_and_Exams.DS2Exam;

import java.io.*;
import java.util.*;

public class Q4_SortFile {
    public static void sortCharsInFiles(File toSort) {
        StringBuilder stringBuilder = new StringBuilder();
        String line = null;
        String ls = System.getProperty("line.separator");

        try {
            BufferedReader reader = new BufferedReader(
                    new FileReader(toSort));
            while ((line = reader.readLine()) != null) {
                stringBuilder.append(line);
                stringBuilder.append(ls);
            }
            // delete the last new line separator
            stringBuilder.deleteCharAt(stringBuilder.length() - 1);
            reader.close();

            char[] content = stringBuilder.toString().toCharArray();

            Arrays.sort(content);

            FileWriter writer = new FileWriter(toSort);
            writer.write(content);
            writer.close();

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
