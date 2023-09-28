package il.co.ILRD.design_patterns.singleton;

public enum SingleEnum {
    SINGLETON();

    SingleEnum() {
        Object singleton = new Object();
    }
}



