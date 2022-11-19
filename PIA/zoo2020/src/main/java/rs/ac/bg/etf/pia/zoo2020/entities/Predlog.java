package rs.ac.bg.etf.pia.zoo2020.entities;

public class Predlog {
    private String posetilac;
    private String zivotinja;
    private String komentar;
    private int glasovi;
    private boolean glasao;
    private boolean odobren;
    private int idP;

    public int getIdP() {
        return idP;
    }

    public void setIdP(int idP) {
        this.idP = idP;
    }

    public boolean isOdobren() {
        return odobren;
    }

    public void setOdobren(boolean odobren) {
        this.odobren = odobren;
    }

    public String getPosetilac() {
        return posetilac;
    }

    public void setPosetilac(String posetilac) {
        this.posetilac = posetilac;
    }

    public String getZivotinja() {
        return zivotinja;
    }

    public void setZivotinja(String zivotinja) {
        this.zivotinja = zivotinja;
    }

    public String getKomentar() {
        return komentar;
    }

    public void setKomentar(String komentar) {
        this.komentar = komentar;
    }

    public int getGlasovi() {
        return glasovi;
    }

    public void setGlasovi(int glasovi) {
        this.glasovi = glasovi;
    }

    public boolean isGlasao() {
        return glasao;
    }

    public void setGlasao(boolean glasao) {
        this.glasao = glasao;
    }
}
