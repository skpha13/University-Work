package csv;

import com.opencsv.CSVWriter;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class ThirdPartyOpenCsv {
    private static final String SEPARATOR = ",";

    public static void main(String[] args) {
        List<String[]> dataLines = buildSampleData();
        writeUsingOpenCsv(dataLines);
    }

    private static List<String[]> buildSampleData() {
        List<String[]> sampleDataLines = new ArrayList<>();
        sampleDataLines.add(new String[]
                { "Marcel", "Ionescu", "38", "email_marcel@abc.com" });
        sampleDataLines.add(new String[]
                { "Sorin", "Popescu", "19", "email_sorin@def.com" });
        return sampleDataLines;
    }

    private static void writeUsingOpenCsv(List<String[]> dataLines) {
        try (CSVWriter writer = new CSVWriter(new FileWriter("./lab8/csv_OpenCsv_output.csv"))) {
            for (String[] line : dataLines) {
                writer.writeNext(line, false);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
