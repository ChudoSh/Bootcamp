package il.co.ILRD.networking.HttpServer;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class Factory<K, D> {
    private Map<K, Function<D, Command>> commands;

    public Factory() {
        this.commands = new HashMap<>();
    }

    public void add(K key, Function<D, Command> command) {
        this.commands.put(key, command);
        System.out.println("command " + key + " added to factory");
    }

    public Command create(K key, D data) {
        Function<D, Command> recipe = this.commands.get(key);

        return (null == recipe) ? null : recipe.apply(data);
    }
}

