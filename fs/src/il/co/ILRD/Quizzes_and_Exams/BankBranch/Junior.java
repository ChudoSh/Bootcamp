package il.co.ILRD.Quizzes_and_Exams.BankBranch;

import java.time.LocalDate;

public class Junior extends BankEmployee {
    EmployeeStrategy salaryLevel = new JuniorSalary();

    public Junior(int id, String name, LocalDate birthday, LocalDate startDate, double salary) {
        super(id, name, birthday, startDate, salary);
    }
}
