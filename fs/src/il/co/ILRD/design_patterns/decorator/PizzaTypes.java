package il.co.ILRD.design_patterns.decorator;

public class PizzaTypes {
}

/*------------------------------------*/
class PeppyPaneer implements Pizza{

    @Override
    public String getDecoration() {
        return "Peppy Paneer Pizza";
    }

    @Override
    public int getPrice() {
        return 10;
    }
}
/*------------------------------------*/
class Farmhouse implements Pizza{

    @Override
    public String getDecoration() {
        return "Farmhouse Pizza";
    }

    @Override
    public int getPrice() {
        return 11;
    }
}
/*------------------------------------*/
class Margarita implements Pizza{

    @Override
    public String getDecoration() {
        return "Margarita Pizza";
    }

    @Override
    public int getPrice() {
        return 12;
    }
}
/*------------------------------------*/
class ChickenFiesta implements Pizza{

    @Override
    public String getDecoration() {
        return "Chicken Fiesta Pizza";
    }

    @Override
    public int getPrice() {
        return 13;
    }
}
