package pao.sample.model;

/** Entities should be simple POJO (Plain Old Java Objects), written with encapsulation in mind. */
public class Entity1 {

    /** private fields */
    private String sampleName;

    private int age;

    /** public constructor */
    public Entity1(String sampleName, int age) {
        this.sampleName = sampleName;
        this.age = age;
    }

    /** public getters and setters */
    public String getSampleName() {
        return sampleName;
    }

    public void setSampleName(String sampleName) {
        this.sampleName = sampleName;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }
}
