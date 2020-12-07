#include <iostream>
#include "datum.hpp"
#include "kvar.hpp"
#include "garancija.hpp"
#include "uredjaj.hpp"
#include "klima.hpp"

int main(void) {
    // Datum
    Datum da, db(1, 12), dc(1, 12, 2020);
    std::cout << da["dan"] << " " << da["mesec"] << " " << da["godina"] << " "
              << da["ne"] << " " << (da < db) << " " << (dc < da) << " " << db
              << std::endl;
    // Kvar
    std::string kvar = "Druga greška";
    Kvar ka("Greška", Datum(1, 1, 2020)), kb(kvar, da);
    std::cout << ka.dohvatiOpis() << " " << ka.dohvatiDatum() << " "
              << ka.otklonjenJe() << " " << ka << " ";
    ka.postaviOtklonjen(true);
    std::cout << ka.otklonjenJe() << std::endl;
    // Garancija
    Garancija ga(da, db);
    try {
        ga.poslednjiKvar();
    } catch (const char *error) {
        std::cout << error << std::endl;
    }
    ga.dodajKvar(kb);
    try {
        ga.dodajKvar(ka);
    } catch (const char *error) {
        std::cout << error << std::endl;
    }
    std::cout << ga.poslednjiKvar() << " " << ga.brojKvarova() << " " << ga
              << std::endl;
    // Klima (Uređaj)
    Klima klima("Bosch", 3), klimb("Bosch", 4), klimc("Bosch", 3);
    klima.postaviGaranciju(da);
    std::cout << (*klima.dohvatiGaranciju()) << " "
              << klimb.dohvatiGaranciju() << std::endl
              << (klima == klimb) << " " << (klima == klimc) << " "
              << klima.brojKvarovaZaIzdavanjeNovog() << std::endl
              << klima << std::endl;

    return 0;
}
