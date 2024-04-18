package csv;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class CsvPrintWriter {

    private static final String SEPARATOR = ",";

    public static void main(String[] args) {
        List<String[]> dataLines = buildSampleData();
        writeUsingPrintWriter(dataLines);
    }

    private static List<String[]> buildSampleData() {
        List<String[]> sampleDataLines = new ArrayList<>();
        sampleDataLines.add(new String[]
                { "Marcel", "Ionescu", "38", "email_marcel@abc.com" });
        sampleDataLines.add(new String[]
                { "Sorin", "Popescu", "19", "email_sorin@def.com" });
        return sampleDataLines;
    }

    private static void writeUsingPrintWriter(List<String[]> dataLines) {
        try (PrintWriter pw = new PrintWriter(new File("./lab8/csv_PrintWriter_output.csv"))) {
            for (String[] line : dataLines) {
                String csvLine = transformToCSV(line);
                pw.println(csvLine);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    private static String transformToCSV(String[] data) {
        StringBuilder csvRow = new StringBuilder();
        for (String element : data) {
            csvRow.append(element).append(SEPARATOR);
        }
        csvRow.deleteCharAt(csvRow.length() -1);
        return csvRow.toString();
    }
}
