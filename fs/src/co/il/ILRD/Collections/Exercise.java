package co.il.ILRD.Collections;

import java.util.*;

public class Exercise {
    public static void main(String[] args) {
        Integer[] arr = {1, 2,4,5,6,7,9,7};
        System.out.println(Arrays.toString(arr));
        List<Integer> list = Arrays.asList(arr);
        list.sort(Integer::compare);
        System.out.println(list);


        Map<String, Integer> map = new HashMap<>();

        map.put("Sunday", 1);
        map.put("Monday", 2);
        map.put("Tuesday", 3);
        map.put("Wednesday", 4);
        map.put("Thursday", 5);
        map.put("Friday", 6);
        map.put("Saturday", 7);

        for(String key : map.keySet()){
            System.out.println(key);
        }
        for(Integer value : map.values()){
            System.out.println(value.toString());
        }

        DataObject[] dataObjectArr = {new DataObject("potato", 5, 10),
                new DataObject("banana", 10, 15),
                new DataObject("avocado", 15, 20)};

        Arrays.stream(dataObjectArr).map(obj -> "Code: " + obj.getCode() + "," +
                        " sum of values: " + (obj.getValue1() + obj.getValue2()))
                .forEach(System.out::println);


    }

    public static class DataObject {

            private String code;
            private int value1;
            private int value2;

            public DataObject(String code, int value1, int value2) {
                this.code = code;
                this.value1 = value1;
                this.value2 = value2;
            }

            public int getValue1() {
                return value1;
            }

            public int getValue2() {
                return value2;
            }

            public String getCode() {
                return code;
            }
        }
    }
