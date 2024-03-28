package interfaces.custom;

public class Application implements TcpStackProtocol {
    private String macAddress;

    public Application(String macAddress) {
        this.macAddress = macAddress;
    }

    public String getMacAddress() {
        return macAddress;
    }

    public void setMacAddress(String macAddress) {
        this.macAddress = macAddress;
    }

    @Override
    public String calculateIPv4() {
        StringBuilder asciiString = new StringBuilder();

        for (char c : macAddress.toCharArray()) {
            asciiString.append((int) c).append(".");
        }

        if (!asciiString.isEmpty()) {
            asciiString.deleteCharAt(asciiString.length() - 1);
        }

        return asciiString.toString();
    }
}
