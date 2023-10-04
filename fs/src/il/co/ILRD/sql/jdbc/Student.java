package il.co.ILRD.sql.jdbc;

public class Student {
    private String name;
    private short age;
    private String clazz;
    private short year;

    public Student(String name, short age, String clazz, short year){
        this.name = name;
        this.age = age;
        this.clazz = clazz;
        this.year = year;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAge(short age) {
        this.age = age;
    }

    public void setClazz(String clazz) {
        this.clazz = clazz;
    }

    public void setYear(short year) {
        this.year = year;
    }

    public String getName() {
        return name;
    }

    public short getAge() {
        return age;
    }

    public short getYear() {
        return year;
    }

    public String getClazz() {
        return clazz;
    }

    @Override
    public String toString() {
        return "Student{" +
                "name='" + this.name + '\'' +
                ", age=" + this.age +
                ", clazz='" + this.clazz + '\'' +
                ", year=" + this.year +
                '}';
    }

    public String sqlBracketedString() {
        return  " (" +
                this.name +
                ", " + this.age +
                ", " +  this.clazz +
                ", " + this.year  +
                ")";
    }

    public String sqlString() {
        String tmp = this.sqlBracketedString().replace("(", "");
        return tmp.replace(")", "");
    }
}
