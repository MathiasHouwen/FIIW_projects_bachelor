package kmteller.soap.java;


import jakarta.xml.ws.Endpoint;
import jakarta.jws.WebMethod;
import jakarta.jws.WebService;


@WebService
public interface KmTellerService {
    @WebMethod
    double getTotalKilometers();

    @WebMethod
    void addKilometers(double km);
}