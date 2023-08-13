package co.il.ILRD.Quizzes.BankBranch;

import java.time.LocalDate;
import java.time.Period;

public class Junior extends BankEmployee {
    EmployeeStrategy salaryLevel = new JuniorSalary();

    public Junior(int id, String name, LocalDate birthday, LocalDate startDate, double salary) {
        super(id, name, birthday, startDate, salary);
    }
}
