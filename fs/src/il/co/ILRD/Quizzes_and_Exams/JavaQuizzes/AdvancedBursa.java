package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.ArrayList;
import java.util.List;

public class AdvancedBursa {
    public static void main(String[] args) {
        System.out.println(AdvancedBursa.getMaxProfit(new int[]{
                8, 2, 6, 2, 6, 3, 7
        }));
    }

    public static int getMaxProfit(int[] arr) {
        int sell = 1;
        int buy = 0;
        int maxProfit = 0;
        int currentProfit = 0;
        List<ProfitNode> list = new ArrayList<>();

        while (sell < arr.length - 1) {
            if ((arr[sell] - arr[buy]) > currentProfit) {
                currentProfit += arr[sell] - arr[buy];
                sell = buy;
            } else if ((arr[sell] - arr[buy]) < 0) {
                sell = buy;
            }
            ++sell;
        }

        for (int i = 0; i < list.size() - 1; ++i) {
            if (list.get(i).getProfit() > list.get(i + 1).getProfit() &&
                    list.get(i).getIndexSell() != (list.get(i + 1).getIndexBuy() + 1)) {
                maxProfit += list.get(i).getProfit();

            }
            ++buy;
        }

//        8,2,6,2,6,3,7 = 8

        return maxProfit;
    }

    private static class ProfitNode implements Comparable<ProfitNode> {
        private int indexBuy;
        private int indexSell;
        private int profit;

        public ProfitNode(int buy, int sell, int profit) {
            this.profit = profit;
            this.indexBuy = buy;
            this.indexSell = sell;
        }

        public int getIndexBuy() {
            return indexBuy;
        }

        public void setIndexBuy(int indexBuy) {
            this.indexBuy = indexBuy;
        }

        public int getIndexSell() {
            return indexSell;
        }

        public void setIndexSell(int indexSell) {
            this.indexSell = indexSell;
        }

        public int getProfit() {
            return profit;
        }

        public void setProfit(int profit) {
            this.profit = profit;
        }

        @Override
        public int compareTo(ProfitNode profitNode) {
            return 0;
        }
    }
}
