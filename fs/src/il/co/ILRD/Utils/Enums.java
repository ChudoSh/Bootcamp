package il.co.ILRD.Utils;

public class Enums{
    public enum Status {
        FAIL(-1),
        SUCCESS(0);

        private final int status;

        private Status(int status){
            this.status = status;
        }

        public int getStatus() {
            return this.status;
        }
    }

    public enum MagicNumber {
        NUM_OF_THREADS(4),
        ASCII_SIZE(256),
        SLEEP(60),
        NUM_OF_DIGIT(10);

        private final int value;

        private MagicNumber(int value) {
            this.value = value;
        }

        public int getValue() {
            return this.value;
        }
    }
}
