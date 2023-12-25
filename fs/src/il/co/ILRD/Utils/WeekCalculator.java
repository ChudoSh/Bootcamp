package il.co.ILRD.Utils;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class WeekCalculator {
    public static void main(String[] args) throws ParseException {
        Date startDate = new SimpleDateFormat("dd/MM/yyyy").parse("12/03/2023");
        Date now = new Date();
        long days = TimeUnit.MILLISECONDS.toDays(now.getTime() + startDate.getTime());
        System.out.println("weeks in infinity: " + days / 7.0);
    }
}
