#include <iostream>
#include <vector>

class DnevnaEvidencija
{
    std::vector<double> lista;
    bool prestupna;
    int br_pod;
    int godina[12]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
public:
    DnevnaEvidencija(bool pr = false): prestupna(pr),br_pod(0){
        if(pr) godina[1]++;
    }
    void RegistrirajPodatak(double podatak);
    int DajBrojRegistriranih() const{return br_pod;}
    double DajPodatakNaDan(double dan, double mjesec) const;
    void AzurirajDan(double dan, double mjesec);
protected:
    bool DaLiJePrestupna() const;
    int RedniBrojDana(double dan, double mjesec) const;
    double DajPodatakSRednimBrojem() const;
};

double ZbirniPodaci(DnevnaEvidencija ev);

class DnevnaEvidencijaFleksibilna: public DnevnaEvidencija
{
    int poc_dan, poc_mjesec;
};

int main()
{

    return 0;
}
