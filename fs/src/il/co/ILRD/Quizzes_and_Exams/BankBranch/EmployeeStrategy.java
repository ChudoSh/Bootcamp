package il.co.ILRD.Quizzes_and_Exams.BankBranch;

import java.time.LocalDate;
import java.time.Period;

abstract public interface EmployeeStrategy {

    abstract public double calculateAnnualSalary(LocalDate startDate, double salary);
}

class JuniorSalary implements EmployeeStrategy{
    @Override
    public double calculateAnnualSalary(LocalDate startDate, double salary) {
        double newSalary = 12 * salary;
        Period period = Period.between(LocalDate.now(), startDate);
        return (period.getDays() >= 365) ? newSalary + salary : newSalary;
    }
}
class SeniorSalary implements EmployeeStrategy{
    @Override
    public double calculateAnnualSalary(LocalDate startDate, double salary) {
        return (new JuniorSalary().calculateAnnualSalary(startDate, salary)) * 1.1;
    }
}
class ManagerSalary implements EmployeeStrategy{
    @Override
    public double calculateAnnualSalary(LocalDate startDate, double salary) {
        return (new JuniorSalary().calculateAnnualSalary(startDate, salary)) ;
    }
}