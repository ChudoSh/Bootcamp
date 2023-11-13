package il.co.ILRD.design_patterns.singleton;

public enum SingleEnum {
    SINGLETON();

    private Object singleton;

    SingleEnum() {
        this.singleton = new Object();
    }

    public Object getInstance(){
        return this.singleton;
    }
}



