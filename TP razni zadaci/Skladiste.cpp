#include <fstream>
#include <iostream>
#include <algorithm>

class Spremnik
{
public:
    virtual ~Spremnik() = default;
    virtual double DajTezinu() const = 0;
    virtual double DajUkupnuTezinu() const = 0;
    virtual void Ispisi(std::ostream& tok = std::cout) const = 0;
    virtual Spremnik *DajKopiju() const = 0;
};

class Sanduk: public Spremnik
{
    double sv_tezina;
    std::string naziv;
    int broj_predmeta;
    double tezina_predmeta;
public:
    Sanduk(double tezina, const char* naziv, int br_predmeta, double t_predmeta):
        sv_tezina(tezina), naziv(naziv), broj_predmeta(br_predmeta), 
            tezina_predmeta(t_predmeta){}
    double DajTezinu() const override{return sv_tezina;}
    double DajUkupnuTezinu() const override{
        return DajTezinu() + broj_predmeta * tezina_predmeta;
    }
    void Ispisi(std::ostream& tok = std::cout) const override;
    Sanduk* DajKopiju() const override{
        return new Sanduk(*this);
    }
};

class Bure: public Spremnik
{
    double sv_tezina;
    std::string naziv;
    double tezina_predmeta;
public:
    Bure(double tezina, const char* naziv, double t_predmeta):
        sv_tezina(tezina), naziv(naziv), tezina_predmeta(t_predmeta){}
    double DajTezinu() const override{return sv_tezina;}
    double DajUkupnuTezinu() const override{
        return DajTezinu() + tezina_predmeta;
    }
    void Ispisi(std::ostream& tok = std::cout) const override;
    Bure* DajKopiju() const override{
        return new Bure(*this);
    }
};

class Skladiste
{
    Spremnik** inventar;
    int kapacitet, stanje;
    void Dealociraj();
public:
    explicit Skladiste(int kapacitet): kapacitet(kapacitet){}
    ~Skladiste(){Dealociraj();}
    Skladiste(const Skladiste& s);
    Skladiste(Skladiste&& s);
    Skladiste operator=(Skladiste&& s);
    Skladiste& operator=(const Skladiste& s);
    void DodajSanduk(double tezina, const char* naziv, int br_predmeta,
        double t_predmeta);
    void DodajBure(double tezina, const char* naziv, double t_predmeta);
    const Spremnik& DajNajlaksi() const;
    Spremnik& DajNajlaksi();
    const Spremnik& DajNajtezi() const;
    Spremnik& DajNajtezi();
    int BrojPreteskih(double max) const;
    void IzlistajSkladiste() const;
    void UcitajIzDatoteke(std::string ime);
};

int main()
{

    return 0;
}

void Bure::Ispisi(std::ostream& tok) const
{
    tok<<"Vrsta spremnika: Bure\n"<<"Sadrzaj: "<<naziv<<
        "\nVlastita tezina: "<<DajTezinu()<<" kg\n"<<
        "Ukupna tezina: "<<DajUkupnuTezinu()<<" kg\n";
}

void Sanduk::Ispisi(std::ostream& tok) const
{
    tok<<"Vrsta spremnika: Sanduk\n"<<"Sadrzaj: "<<naziv<<
        "\nVlastita tezina: "<<DajTezinu()<<" kg\n"<<
        "Ukupna tezina: "<<DajUkupnuTezinu()<<" kg\n";
}

void Skladiste::Dealociraj()
{
    for(int i = 0; i < stanje; i++) delete inventar[i];
    delete[] inventar;
}

Skladiste::Skladiste(const Skladiste& s): 
    inventar(nullptr), kapacitet(s.kapacitet), stanje(s.stanje)
{
    inventar = new Spremnik*[s.kapacitet]();
    try
    {
        for(int i{}; i < s.stanje; i++)
            inventar[i] = s.inventar[i]->DajKopiju();
    }
    catch(const std::exception& e)
    {
        Dealociraj();
    }
    
}

Skladiste::Skladiste(Skladiste&& s): 
    inventar(nullptr), kapacitet(0), stanje(0)
{
    std::swap(inventar, s.inventar); std::swap(kapacitet, s.kapacitet);
    std::swap(stanje, s.stanje);
}

Skladiste& Skladiste::operator=(const Skladiste& s)
{
    Spremnik** novi = new Spremnik*[s.kapacitet]();
    try
    {
        for(int i{}; i < s.stanje; i++)
            novi[i] = s.inventar[i]->DajKopiju();
        kapacitet = s.kapacitet;
        Dealociraj();
        inventar = novi; stanje = s.stanje;
    }
    catch(const std::exception& e)
    {
        for(int i = 0; i < s.stanje; i++) 
            delete novi[i];
        delete[] novi;
    }
    return *this;
}

Skladiste Skladiste::operator=(Skladiste&& s)
{
    std::swap(inventar, s.inventar); std::swap(kapacitet, s.kapacitet);
    std::swap(stanje, s.stanje); return *this;
}

void Skladiste::DodajSanduk(double tezina, const char* naziv, int br_predmeta,
        double t_predmeta)
{
    if(stanje == kapacitet) throw std::domain_error("Popunjeno skladiste");
    inventar[stanje++] = new Sanduk(tezina, naziv, br_predmeta, t_predmeta);
}        

void Skladiste::DodajBure(double tezina, const char* naziv, double t_predmeta)
{
    if(stanje == kapacitet) throw std::domain_error("Popunjeno skladiste");
    inventar[stanje++] = new Bure(tezina, naziv, t_predmeta);
}

Spremnik &Skladiste::DajNajlaksi() 
{
    if(stanje == 0) throw std::range_error("Skladiste je prazno");
    return **std::min_element(inventar, inventar + stanje,
    [](Spremnik *s1, Spremnik *s2) {
    return s1->DajTezinu() < s2->DajTezinu();
    });
}
const Spremnik &Skladiste::DajNajlaksi() const 
{
    if(stanje == 0) throw std::range_error("Skladiste je prazno");
    return **std::min_element(inventar, inventar + stanje,
    [](Spremnik *s1, Spremnik *s2) {
    return s1->DajTezinu() < s2->DajTezinu();
    });
}

Spremnik &Skladiste::DajNajtezi() {
    if(stanje == 0) throw std::range_error("Skladiste je prazno");
    return **std::max_element(inventar, inventar + stanje,
    [](Spremnik *s1, Spremnik *s2) {
    return s1->DajTezinu() < s2->DajTezinu();
    });
}
const Spremnik &Skladiste::DajNajtezi() const {
    if(stanje == 0) throw std::range_error("Skladiste je prazno");
    return **std::max_element(inventar, inventar + stanje,
    [](Spremnik *s1, Spremnik *s2) {
    return s1->DajTezinu() < s2->DajTezinu();
    });
}

int Skladiste::BrojPreteskih(double max) const
{
    int br{};
    for(int i = 0; i < stanje; i++)
        if(inventar[i]->DajUkupnuTezinu() > max) br++;
    return br;
}

void Skladiste::IzlistajSkladiste() const
{
    Spremnik** temp = new Spremnik*[stanje]();
    for(int i = 0; i < stanje; i++)
        temp[i] = inventar[i]->DajKopiju();
    std::sort(temp, temp + stanje, [](Spremnik* s1, Spremnik* s2){
        return s1->DajUkupnuTezinu() > s2->DajUkupnuTezinu();
    });
    for(int i{}; i < stanje; i++) temp[i]->Ispisi(), endl(std::cout);
    for(int i{}; i < stanje; i++) delete temp[i];
    delete[] temp;
}

void Skladiste::UcitajIzDatoteke(std::string ime)
{
    std::ifstream fajl(ime);
    
}