package co.il.ILRD.Quizzes.DS2Exam;

import java.io.*;
import java.util.*;

public class Q4 {

    public static void sortCharsInFiles(File toSort) {
        List<String> lines = new ArrayList<String>();
        String line = null;


        try {
            FileReader fileReader = new FileReader(toSort);
            BufferedReader bufferReader = new BufferedReader(fileReader);

            while ((line = bufferReader.readLine()) != null){
                lines.add(line);
            }
            bufferReader.close();

            for (String str : lines){
                Arrays.sort(str.toCharArray());

            }

            FileWriter writer = new FileWriter(toSort);
            for (String str : lines){
                writer.write(str + "\r\n");
            }

            writer.close();

        } catch (IOException e) {
            throw new RuntimeException(e);
        }


    }
}
