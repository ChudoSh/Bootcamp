import java.util.Arrays;
import static org.junit.jupiter.api.Assertions.*;

enum EWeekDay {
    SUNDAY(1),
    MONDAY(2),
    TUESDAY(3),
    WEDNESDAY(4),
    THURSDAY(5),
    FRIDAY(6),
    SATURDAY(7);

    private final int day;
    private EWeekDay(int day) {
        this.day = day;
    }
    public int getValue(){
        return (this.day);
    }
    public EWeekDay fromValue(int day) {
        return (EWeekDay.values()[day -1]);
    }

    public void printAll(){
        System.out.println(Arrays.toString(EWeekDay.values()));
    }
}

public class Main {
    public static void main(String[] args) {
        EWeekDay friday = EWeekDay.FRIDAY;
        assertEquals(6, friday.getValue(), "getValue fail");
    }

}
