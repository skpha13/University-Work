package exceptii.checked;

public class ThermostatService {
    public void setTemperature(int temperature) throws TooColdException {
        if (temperature < 10) {
            throw new TooColdException("It's to cold!");
        } else {
            System.out.println("Setting temperature to " + temperature);
        }
    }

    public static void main(String[] args) {
        ThermostatService service = new ThermostatService();
        try {
            service.setTemperature(9);
        } catch (TooColdException e) {
            // 3 modalitati de a printa exceptia
            System.out.println(e + "\n");
            System.out.println(e.getMessage() + "\n");
            e.printStackTrace();
        }
    }
}
