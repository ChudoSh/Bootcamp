package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.*;

public class BlackJack {
    Stack<Card> deck;

    public BlackJack() {
        this.deck = this.combine();
    }

    private Stack<Card> combine() {
        Stack<Card> newDeck = new Stack<>();


        return newDeck;
    }

    public boolean isSet(Set<Card> cards) {
        Iterator<Card> iter = cards.iterator();
        Card prev = iter.next();
        Card curr = iter.next();

        while (iter.hasNext() && !prev.isCardPreviousInTheSeries(curr)) {
            prev = iter.next();
            curr = iter.next();
        }

        if (iter.hasNext()) {
            return false;
        }

        return true;
    }

    public Card getCard() {
        return this.deck.pop();
    }
}

class Hand {
    ArrayList<Card> hand;

    public Hand(){
       this(new ArrayList<>());
    }

    public Hand(ArrayList<Card> hand){
        this.hand = hand;
    }
}

class Deck {
    ArrayList<Card> deck;

    public Deck() {
        for (int i = 1; i <= 13; ++i) {
            this.deck.add(new Card("Diamond", "Red", i));
            this.deck.add(new Card("Heart", "Red", i));
            this.deck.add(new Card("Clover", "Black", i));
            this.deck.add(new Card("Leaf", "Black", i));
        }
    }

    public int size() {
        return this.deck.size();
    }

    public Card get() {
        return this.deck.remove(0);
    }

    public void shuffle() {
        shuffle(this);
    }

    public static void shuffle(Deck shuffleDeck) {
        Random rand = new Random();
        int size = shuffleDeck.size();
        int randIndex = 0;
        Card card;

        for (int i = 0; i < size; ++i) {
            randIndex = rand.nextInt(size - 1);
            card = shuffleDeck.deck.remove(randIndex);
            shuffleDeck.deck.add(size, card);
        }
    }
}

class Card {
    private String shape;
    private String color;
    private int number;
    private boolean isFill;

    public Card(String shape, String color, int number) {
        this.shape = shape;
        this.color = color;
        this.number = number;
    }

    public boolean isCardPreviousInTheSeries(Object object) {
        if (this == object) return true;
        if (object == null || getClass() != object.getClass()) return false;
        Card card = (Card) object;
        return ((number == card.number - 1) &&
                (Objects.equals(shape, card.shape)) &&
                (Objects.equals(shape, card.shape)) &&
                (Objects.equals(color, card.color)));
    }
}

