package co.il.ILRD.Quizzes_and_Exams.BankBranch;

import java.time.LocalDate;

public class Manager extends BankEmployee {
    EmployeeStrategy salaryLevel = new ManagerSalary();
    private double bonus;

    public Manager(int id, String name, LocalDate birthday, LocalDate startDate, double salary, double bonus) {
        super(id, name, birthday, startDate, salary);
        this.bonus = bonus;
    }

    public double getBonus() {
        return bonus;
    }

    public void setBonus(double bonus) {
        this.bonus = bonus;
    }
}