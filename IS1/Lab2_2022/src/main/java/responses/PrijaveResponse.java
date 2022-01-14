package responses;

import java.util.List;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name = "prijave")
public class PrijaveResponse {
    private List<PrijavaResponse> prijave;
    @XmlElement(name = "prijava")
    public List<PrijavaResponse> getPrijave() {
        return prijave;
    }
    public void setPrijave(List<PrijavaResponse> prijave) {
        this.prijave = prijave;
    }
}
