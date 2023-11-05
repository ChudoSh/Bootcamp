package il.co.ILRD.Quizzes_and_Exams.LeetcodeProblems;

import java.util.ArrayList;
import java.util.List;

public class Twitter {
    private List<User> allUsers;

    public Twitter() {
        this.allUsers = new ArrayList<>();
    }

    interface Update{
        void updateTweet(int tweetId);
    }

    public void postTweet(int userId, int tweetId){

    }

    private class User implements Update{
        private int userId;
        private List<User> followers;
        private List<Integer> newsFeed;

        public User(int userId) {
            this.userId = userId;
            this.newsFeed = new ArrayList<>();
            this.followers = new ArrayList<>();
        }

        @Override
        public void updateTweet(int tweetId) {
            this.addToNewsFeed(tweetId);
            for(User follower : followers){
                follower.addToNewsFeed(tweetId);
            }
        }

        public int getUserId(){
            return this.userId;
        }

        private void addToNewsFeed(int tweetId){
            if (this.newsFeed.size() == 10){
                this.newsFeed.remove(10);
            }

            this.newsFeed.add(tweetId);
        }
    }
}
