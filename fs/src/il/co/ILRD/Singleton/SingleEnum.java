package il.co.ILRD.Singleton;

public enum SingleEnum {
    SINGLETON();

    SingleEnum() {
        Object singleton = new Object();
    }
}



