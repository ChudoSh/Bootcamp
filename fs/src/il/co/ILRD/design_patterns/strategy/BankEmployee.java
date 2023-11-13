package il.co.ILRD.design_patterns.strategy;

import java.time.LocalDate;

public class BankEmployee {
    private final int id;
    private final String name;
    private final LocalDate birthday;
    private final LocalDate startDate;
    private double salary;
    private EmployeeStrategy salaryLevel;

    public BankEmployee(int id, String name, LocalDate birthday, LocalDate startDate, double salary) {
        this.id = id;
        this.name = name;
        this.birthday = birthday;
        this.startDate = startDate;
        this.salary = salary;
    }

    public void setSalary(double salary) {
        this.salary = salary;
    }

    public int getId() {
        return id;
    }

    public void setRole(BankEmployee employee) {
        if(this.salaryLevel instanceof ManagerSalary && employee.getSalaryLevel() instanceof JuniorSalary){
            employee.salaryLevel = new SeniorSalary();
        } else {
            System.out.println("Access denied");
        }
    }

    public EmployeeStrategy getSalaryLevel() {
        return salaryLevel;
    }

    public void setSalaryLevel(EmployeeStrategy salaryLevel) {
        this.salaryLevel = salaryLevel;
    }

    public String getName() {
        return name;
    }

    public LocalDate getBirthday() {
        return birthday;
    }

    public LocalDate getStartDate() {
        return startDate;
    }

    public double getSalary() {
        return salary;
    }

    public double calculateAnnualSalary(){
        return salaryLevel.calculateAnnualSalary(this.startDate, this.salary);
    }
}
