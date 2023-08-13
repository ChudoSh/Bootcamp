package co.il.ILRD.DS2Exam;

import com.sun.xml.internal.fastinfoset.util.CharArray;

public class Q7 {

    public static String reverseString(String str) {
        StringBuilder reversed = new StringBuilder();

        for(int i = str.length() - 1; i >= 0; --i){
            reversed.append(str.charAt(i));
        }

        return reversed.toString();
    }
}
