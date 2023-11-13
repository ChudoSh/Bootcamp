package il.co.ILRD.design_patterns.strategy;

import java.time.LocalDate;
import java.time.Period;

public interface EmployeeStrategy {
    double calculateAnnualSalary(LocalDate startDate, double salary);
}

class JuniorSalary implements EmployeeStrategy {
    @Override
    public double calculateAnnualSalary(LocalDate startDate, double salary) {
        double newSalary = 12 * salary;
        Period period = Period.between(LocalDate.now(), startDate);
        return (period.getDays() >= 365) ? newSalary + salary : newSalary;
    }
}

class SeniorSalary implements EmployeeStrategy {
    @Override
    public double calculateAnnualSalary(LocalDate startDate, double salary) {
        double newSalary = new JuniorSalary().calculateAnnualSalary(startDate, salary);
        Period period = Period.between(LocalDate.now(), startDate);
        return (period.getDays() >= 365) ? newSalary * 1.1 : newSalary;
    }
}

class ManagerSalary implements EmployeeStrategy {
    @Override
    public double calculateAnnualSalary(LocalDate startDate, double salary) {
        return (new JuniorSalary().calculateAnnualSalary(startDate, salary));
    }
}