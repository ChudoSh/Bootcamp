package co.il.ILRD.Quizzes.BankBranch;

import java.time.LocalDate;
import java.time.Period;


public class Senior extends BankEmployee {
    EmployeeStrategy salaryLevel = new SeniorSalary();

    public Senior(int id, String name, LocalDate birthDay, LocalDate startDate, double salary) {
        super(id, name, birthDay, startDate, salary);
    }
}

