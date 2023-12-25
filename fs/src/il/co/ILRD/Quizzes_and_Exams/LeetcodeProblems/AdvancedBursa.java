package il.co.ILRD.Quizzes_and_Exams.LeetcodeProblems;

public class AdvancedBursa {
    public static void main(String[] args) {
        int[] prices1 = {8, 2, 6, 2, 6, 3, 7};
        int[] prices2 = {1, 4, 6, 8, 11};
        int[] prices3 = {3, 9, 5, 16, 2, 5, 10, 14};

        int result = maxProfit(prices3);

        System.out.println("Result: " + result);
    }

    public static int maxProfit(int[] prices) {
        int n = prices.length;
        int profit = 0;
        int buyDay = 0;
        int sellDay = 0;
        int lastSold = 0;
        int lastBought = 0;

        for (int i = 1; i < n; ++i) {
            if (prices[i] > prices[i - 1]) {
                sellDay = i;
                if ((prices[lastSold] - prices[lastBought] < prices[sellDay] - prices[lastBought])
                        && lastSold + 1 == sellDay){
                    profit = prices[sellDay] - prices[lastBought];
                    lastSold = sellDay;
                }
            } else {
                if (sellDay > buyDay) {
                    profit += prices[sellDay] - prices[buyDay];
                    lastSold = sellDay;
                    lastBought = buyDay;
                    buyDay = i + 1;

                } else {
                    buyDay = i;
                }
            }
        }

        if (sellDay > buyDay) {
            profit += prices[sellDay] - prices[buyDay];
        }

        return profit;
    }
}
