package responses;

public class PrijavaResponse {
    private String imePrezimeStudenta;
    private String brojIndeksaStudenta;
    private String sifraPredmeta;
    private String nazivPredmeta;
    private String nazivRoka;
    public String getImePrezimeStudenta() {
        return imePrezimeStudenta;
    }
    public PrijavaResponse setImePrezimeStudenta(String imePrezimeStudenta) {
        this.imePrezimeStudenta = imePrezimeStudenta;
        return this;
    }
    public String getBrojIndeksaStudenta() {
        return brojIndeksaStudenta;
    }
    public PrijavaResponse setBrojIndeksaStudenta(String brojIndeksaStudenta) {
        this.brojIndeksaStudenta = brojIndeksaStudenta;
        return this;
    }
    public String getSifraPredmeta() {
        return sifraPredmeta;
    }
    public PrijavaResponse setSifraPredmeta(String sifraPredmeta) {
        this.sifraPredmeta = sifraPredmeta;
        return this;
    }
    public String getNazivPredmeta() {
        return nazivPredmeta;
    }
    public PrijavaResponse setNazivPredmeta(String nazivPredmeta) {
        this.nazivPredmeta = nazivPredmeta;
        return this;
    }
    public String getNazivRoka() {
        return nazivRoka;
    }
    public PrijavaResponse setNazivRoka(String nazivRoka) {
        this.nazivRoka = nazivRoka;
        return this;
    }
}
