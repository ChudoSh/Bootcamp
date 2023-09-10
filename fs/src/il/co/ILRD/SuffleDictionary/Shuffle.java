package il.co.ILRD.SuffleDictionary;

import java.io.*;
import java.util.*;

public class Shuffle {
    public static void main(String[] args) {
        int numOfCols = 20;
        int[] threads = {1, 2, 4, 8};
        long[] performanceTime = new long[4];
        File linuxDictionary = new File("/usr/share/dict/words");
        Shuffle dictShuffle = new Shuffle(linuxDictionary, numOfCols);

        for (int i = 0; i < threads.length; i++) {
            performanceTime[i] = System.currentTimeMillis();
            dictShuffle.threadedSort(threads[i]);
            performanceTime[i] = System.currentTimeMillis() -  performanceTime[i];
        }

        for (int i = 0; i < performanceTime.length; i++) {
            System.out.println("For " + threads[i] + " threads " + ":" + " " + performanceTime[i] + "ms");
        }
    }
/*==============================Public Methods================================*/
    public Shuffle(File file, int numOfCols) {
        this.file = file;
        this.numOfCols = numOfCols;
    }

    public String[][] threadedSort(int numOfThreads) {
        List<Thread> threadList;

        assert (0 < numOfThreads);

        threadList = new ArrayList<>(numOfThreads);

        try {
            generateShuffledWordMatrix();

            for (int i = 0; i < numOfThreads; ++i) {
                threadList.add(new sortingThread(wordMatrix, i));
            }

            threadList.forEach(Thread::start);

            for (Thread thread : threadList) {
                thread.join();
            }

            return wordMatrix;
        } catch (InterruptedException e) {
            System.out.println("Thread interrupted");
            throw new RuntimeException();
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }


    public void setFile(File file) {
        this.file = file;
    }

    public void setNumOfCols(int numOfCols) {
        this.numOfCols = numOfCols;
    }

    private static final Object lock = new Object();
    private static String[][] wordMatrix;
    private File file;
    private int numOfCols;
/*==========================Private Methods===================================*/
    private void generateShuffledWordMatrix() throws FileNotFoundException {
        String[] fileString = toStringFromFile();
        multipleArrays(fileString);
        shuffleWordMatrix();
    }

    private String[] toStringFromFile() throws FileNotFoundException {
        List<String> listOfWords = new ArrayList<>();
        Scanner scanner = new Scanner(this.file);
        String word;

        while (scanner.hasNext()) {
            word = scanner.next();
            listOfWords.add(word);
        }

        return listOfWords.toArray(new String[0]);
    }

    private void multipleArrays(String[] wordArray) {
        String[][] wordMatrix = new String[wordArray.length][this.numOfCols];

        for (int i = 0; i < wordArray.length; i++) {
            for (int j = 0; j < numOfCols; j++) {
                wordMatrix[i][j] = wordArray[j];
            }
        }

        Shuffle.wordMatrix = wordMatrix;
    }

    private void shuffleWordMatrix() {
        List<String> shuffleList;

        for (int i = 0; i < wordMatrix.length; i++) {
            shuffleList = Arrays.asList(Shuffle.wordMatrix[i]);
            Collections.shuffle(shuffleList);
            shuffleList.toArray(Shuffle.wordMatrix[i]);
        }
    }
   /*============================Private Class================================*/
    private static class sortingThread extends Thread {
        private String[] wordArray;
        private final int rowIndex;

        public sortingThread(String[][] wordMatrix, int rowIndex) {
            this.wordArray = wordMatrix[rowIndex];
            this.rowIndex = rowIndex;
        }

        @Override
        public void run() {
            Arrays.sort(wordArray);

            synchronized (lock) {
                wordMatrix[rowIndex] = wordArray;
            }
        }
    }


}
