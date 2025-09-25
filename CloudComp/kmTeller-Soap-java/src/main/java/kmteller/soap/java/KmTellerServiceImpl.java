package kmteller.soap.java;

import jakarta.xml.ws.Endpoint;
import jakarta.jws.WebMethod;
import jakarta.jws.WebService;


@WebService(endpointInterface = "kmteller.soap.java.KmTellerService")
public class KmTellerServiceImpl implements KmTellerService {

    private double totalKilometers = 5;

    @Override
    public double getTotalKilometers() {
        return totalKilometers;
    }

    @Override
    public synchronized void addKilometers(double km) {
        if (km > 0) {
            totalKilometers += km;
        } else {
            throw new IllegalArgumentException("Kilometers must be positive.");
        }
    }
}