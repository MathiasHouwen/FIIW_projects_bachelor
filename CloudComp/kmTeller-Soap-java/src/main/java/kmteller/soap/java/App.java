package kmteller.soap.java;

import jakarta.xml.ws.Endpoint;
import io.github.cdimascio.dotenv.Dotenv;
import jakarta.jws.WebMethod;
import jakarta.jws.WebService;

public class App {
    public String getGreeting() {
        return "Hello World!";
    }

    public static void main(String[] args) {
        Dotenv dotenv = Dotenv.configure().load();
        String port = dotenv.get("LISTEN_PORT", "8080");
        String url = "http://0.0.0.0:" + port + "/kmTellerService";
        KmTellerServiceImpl service = new KmTellerServiceImpl();
        Endpoint.publish(url, service);
        System.out.println("Service is running at " + url);

        System.out.println(new App().getGreeting());
    }
}


