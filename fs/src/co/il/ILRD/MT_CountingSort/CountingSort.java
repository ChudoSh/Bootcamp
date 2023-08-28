package co.il.ILRD.MT_CountingSort;


import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class CountingSort {
    private static int[] totalCountingArray;
    private static final Object lock = new Object();
    private static final int asciiSize = 256;

    public static char[] mtCountingSort(char[] arr, int numOfThreads) throws InterruptedException {
        assert (0 < numOfThreads);

        List<Thread> threadArray = new ArrayList<>(numOfThreads);
        int threadSegment = arr.length / numOfThreads;
        totalCountingArray = new int[asciiSize];
        int i = 0;

        for (i = 0; i <= arr.length && threadArray.size() < numOfThreads - 1; i += threadSegment) {
            threadArray.add(new myCountingThread(i, i + threadSegment, arr, asciiSize));
        }
        threadArray.add(new myCountingThread(i, arr.length, arr, asciiSize));

        threadArray.forEach(Thread::start);

        for (i = 0; i < numOfThreads; ++i) {
            threadArray.get(i).join();
        }

        int index = 0;
        for (i = 0; i < asciiSize; ++i) {
            for (int j = totalCountingArray[i]; j > 0; --j) {
                arr[index] = (char) i;
                ++index;
            }
        }

        return arr;
    }

    private static class myCountingThread extends Thread {
        private int[] countingArray;
        private final int startIndex;
        private final int endIndex;
        private final char[] arr;
        private final int range;

        public myCountingThread(int startIndex, int endIndex, char[] arr, int range) {
            this.startIndex = startIndex;
            this.endIndex = endIndex;
            this.arr = arr;
            this.range = range;
            this.countingArray = new int[range];
        }

        @Override
        public void run() {
            for (int i = this.startIndex; i < this.endIndex; ++i) {
                ++this.countingArray[this.arr[i]];
            }

            synchronized (lock) {
                for (int i = 0; i < range; ++i) {
                    totalCountingArray[i] += this.countingArray[i];
                }
            }
        }
    }

    public static char[] sortCharsInLinuxDic(File toSort, int numOfThreads) {
        StringBuilder stringBuilder = new StringBuilder();
        String line = null;
        String ls = System.getProperty("line.separator");
        int numOfCopies = 10;

        try {
            BufferedReader reader = new BufferedReader(
                    new FileReader(toSort));
            while ((line = reader.readLine()) != null) {
                stringBuilder.append(line);
                stringBuilder.append(ls);
            }
            // delete the last new line separator
            stringBuilder.deleteCharAt(stringBuilder.length() - 1);
            StringBuilder bulkFile = new StringBuilder();
            for (int i = 0; i < numOfThreads; i++) {
                bulkFile.append(stringBuilder);
            }
            reader.close();

            char[] sortArray = bulkFile.toString().toCharArray();

            return mtCountingSort(sortArray, numOfThreads);

        } catch (IOException | InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) throws InterruptedException {
        int[] threads = {1, 2, 4, 8};
        long[] performanceTime = new long[4];

        File linuxDictionary = new File("/usr/share/dict/words");
        for (int i = 0; i < threads.length; i++) {
            performanceTime[i] = System.currentTimeMillis();
            char[] result = sortCharsInLinuxDic(linuxDictionary, threads[i]);
            performanceTime[i] = System.currentTimeMillis() -  performanceTime[i];
        }

        for (int i = 0; i < performanceTime.length; i++) {
            System.out.println("For " + threads[i] + " threads " + ":" + " " + performanceTime[i]);
        }

    }

    public static boolean isSorted(char[] arr) {
        int i = 0;
        while (i < arr.length - 1 && arr[i] <= arr[i + 1]) {
            ++i;
        }

        return (arr[i] <= arr[i + 1]);
    }
}