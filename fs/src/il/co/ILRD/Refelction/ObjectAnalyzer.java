package il.co.ILRD.Refelction;

import java.lang.reflect.*;
import java.util.Arrays;

public class ObjectAnalyzer {
    ObjectAnalyzer() {

    }

    //  Q1
    public static void printSuperClass(Object Data) {
        System.out.println(Data.getClass().getSuperclass());
    }

    //  Q2
    public static void printListedModifierAndInterfaces(Object Data) {
        try {

            Class<?> c = Data.getClass();
            System.out.println("Modifiers in: " + c.getName());
            System.out.println("  " + Modifier.toString(c.getModifiers()));
            System.out.println("Interfaces in: " + c.getName());
            System.out.println("  " + Arrays.toString(c.getInterfaces()));

        } catch (Exception e) {
            System.out.println("Exception: " + e.toString());
        }
    }

    //  Q3
    public static void printAllMembersInObject(Object Data) {
        try {

            Class<?> c = Data.getClass();
            Method[] methods = c.getMethods();
            for (Method m : methods) {
                System.out.println("  " + m);
            }
            Field[] fields = c.getFields();
            for (Field f : fields) {
                System.out.println("  " + f);
            }

        } catch (Exception e) {
            System.out.println("Exception: " + e.toString());
        }
    }

    // Q4
    public static Object getNewInstance(Class<?> Data) throws InstantiationException, IllegalAccessException {
        return Data.newInstance();
    }

    public static Object invokeObjectMethods(Method m, Object obj,
                                             Object... args) throws InstantiationException, IllegalAccessException, NoSuchMethodException, InvocationTargetException {
        return m.invoke(obj, args);
    }
}

