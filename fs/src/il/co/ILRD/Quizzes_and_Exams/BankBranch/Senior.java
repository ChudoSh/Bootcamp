package il.co.ILRD.Quizzes_and_Exams.BankBranch;

import java.time.LocalDate;


public class Senior extends BankEmployee {
    EmployeeStrategy salaryLevel = new SeniorSalary();

    public Senior(int id, String name, LocalDate birthDay, LocalDate startDate, double salary) {
        super(id, name, birthDay, startDate, salary);
    }
}

