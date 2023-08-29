package co.il.ILRD.FactoryDesignPattern;

import com.sun.org.apache.xml.internal.security.Init;

import java.util.function.Function;

public class InfinityStudent implements Function<InfinityStudent,InfinityStudent> {
    private Integer id;
    private String name;
    private int age;
    private String course;

    public InfinityStudent(){
    }

    public InfinityStudent(Integer id, String name, Integer age, String course) {
        this.id = id;
        this.name = name;
        this.age = age;
        this.course = course;
    }

    public InfinityStudent(InfinityStudent infinityStudent) {
        this(infinityStudent.id,infinityStudent.name,infinityStudent.age,infinityStudent.course);
    }

    public int getAge() {
        return age;
    }

    public Integer getId() {
        return id;
    }

    public boolean isIdPrime(Integer id) {
        return (0 == id % 2);
    }

    public String getName() {
        return name;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getCourse() {
        return course;
    }

    public void setCourse(String course) {
        this.course = course;
    }

    @Override
    public InfinityStudent apply(InfinityStudent infinityStudent) {
        if (null == infinityStudent){
            return new InfinityStudent();
        }

        return new InfinityStudent(infinityStudent);
    }
}
