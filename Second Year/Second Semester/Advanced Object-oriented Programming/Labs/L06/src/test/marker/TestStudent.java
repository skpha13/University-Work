package test.marker;

import marker.Student;

public class TestStudent {

    public static void main(String[] args) throws CloneNotSupportedException {
        Student student = new Student("Matei", 23);
        Student clona = (Student) student.clone();
    }
}
