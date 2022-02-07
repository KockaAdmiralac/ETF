package requests;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name = "korisnik")
public class CreateAdminRequest {
    public String imeKor;
    public String sifra;
}
