package records;

public final record PersonRecord(String name, int age) {}

    // from *.class files folder, run javap PersonRecord.class to see the generated code for PersonRecord:

    /*PS C:\WORK\PAO\out\production\PAO\records> javap PersonRecord.class
    Compiled from "PersonRecord.java"

    public final class records.PersonRecord extends java.lang.Record {

        public records.PersonRecord(java.lang.String, int);

        public final java.lang.String toString();
        public final int hashCode();
        public final boolean equals(java.lang.Object);

        public java.lang.String name();
        public int age();
    }*/