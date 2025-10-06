#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

class ApstraktnoVozilo
{
    int vlastita_tezina;
public:
    virtual ~ApstraktnoVozilo() = default;
    ApstraktnoVozilo(int tezina): vlastita_tezina(tezina){};
    int DajTezinu() const{return vlastita_tezina;};
    virtual int DajUkupnuTezinu() const = 0;
    virtual ApstraktnoVozilo* DajKopiju() const = 0;
    virtual void IspisiPodatke() const = 0;
};

class Automobil : public ApstraktnoVozilo
{
    std::vector<int> tezine;
public:
    Automobil(int tezina, std::vector<int> tezine):
        ApstraktnoVozilo(tezina), tezine(tezine){}
    int DajUkupnuTezinu() const override;
    Automobil* DajKopiju() const override{
        return new Automobil(*this);
    }
    void IspisiPodatke() const override;
};

class Kamion: public ApstraktnoVozilo
{
    int tezina_tereta;
public:
    Kamion(int tezina, int tezina_tereta):
        ApstraktnoVozilo(tezina), tezina_tereta(tezina_tereta){}
    int DajUkupnuTezinu() const override{
        return DajTezinu() + tezina_tereta;
    }
    Kamion* DajKopiju() const override{
        return new Kamion(*this);
    }
    void IspisiPodatke() const override;
};

class Autobus: public ApstraktnoVozilo
{
    int broj_putnika, prosjecna_tezina;
public:
    Autobus(int tezina, int br_putnika, int prosjek):
        ApstraktnoVozilo(tezina), broj_putnika(br_putnika), 
        prosjecna_tezina(prosjek){}
    int DajUkupnuTezinu() const override{
        return DajTezinu() + broj_putnika * prosjecna_tezina;
    }
    Autobus* DajKopiju() const override{
        return new Autobus(*this);
    }
    void IspisiPodatke() const override;
};

class Vozilo
{
    ApstraktnoVozilo* v;
    void Proba() const {if(!v) throw std::logic_error("Nespecificirano vozilo!");}
public:
    Vozilo() : v(nullptr){}
    Vozilo(const ApstraktnoVozilo& vozilo): v(vozilo.DajKopiju()){}
    Vozilo(Vozilo&& vozilo): v(vozilo.v){vozilo.v = nullptr;}
    Vozilo(const Vozilo& vozilo):
        v(!vozilo.v ? nullptr: vozilo.v->DajKopiju()){}
    ~Vozilo(){delete v;}
    Vozilo operator=(Vozilo&& vozilo){
        std::swap(v, vozilo.v); return *this;
    }
    Vozilo& operator=(const Vozilo& vozilo){
        ApstraktnoVozilo* temp = (!vozilo.v ? nullptr :vozilo.v->DajKopiju());
        delete v; v = temp; return *this;
    }
    int DajTezinu() const{Proba(); return v->DajTezinu();}
    int DajUkupnuTezinu() const{Proba(); return v->DajUkupnuTezinu();}
    ApstraktnoVozilo* DajKopiju() const{Proba(); return v->DajKopiju();}
    void IspisiPodatke() const{Proba(); v->IspisiPodatke();}
};

int main()
{
    std::ifstream fajl("VOZILA.TXT");
    if(!fajl) throw std::logic_error("Nepostojeca datoteka");
    std::vector<Vozilo> v;
    char c; int i{};
    while((c = fajl.get()) != EOF)
    {
        if(c == 'A')
        {
            int vl_tezina, n,i;
            std::vector<int> putnici;
            fajl>>vl_tezina>>i;
            while(true)
            {
                if(fajl.peek() == '\n') {fajl.get();break; }
                fajl>>n;
                putnici.push_back(n);
            }
            v.push_back(Automobil(vl_tezina, putnici));
            if(fajl.eof()) break;
            if(!fajl) throw std::range_error("Neispravni parametri");
        }
        else if(c == 'K')
        {
            int vl_tezina, teret;
            fajl>>vl_tezina>>teret;
            fajl.get();
            v.push_back(Kamion(vl_tezina, teret));
            if(fajl.eof()) break;
            if(!fajl) throw std::range_error("Neispravni parametri");
        }
        else if(c == 'B')
        {
            int vl_tezina, putnika, prosjek;
            fajl>>vl_tezina>>putnika>>prosjek;
            fajl.get();
            v.push_back(Autobus(vl_tezina, putnika, prosjek));
            if(fajl.eof()) break;
            if(!fajl) throw std::range_error("Neispravni parametri");
        }
        else
        {
            fajl.close(); throw std::logic_error("Nekorektni podaci");
        }
    }
    std::sort(v.begin(), v.end(), [](const Vozilo& v1, const Vozilo& v2){
        return v1.DajUkupnuTezinu() < v2.DajUkupnuTezinu();
    });
    for(int i = 0; i < v.size(); i++)
    {
        std::cout<<v.at(i).DajUkupnuTezinu()<<std::endl;
    }
    return 0;
}

int Automobil::DajUkupnuTezinu() const
{   
    int suma{};
    for(const int& n: tezine) suma += n;
    return DajTezinu() + suma;
}

void Automobil::IspisiPodatke() const
{
    std::cout<<"Vrsta vozila: Automobil\n"<<
    "Vlastita tezina: "<<DajTezinu()<<" kg\n"<<
    "Tezine putnika: ";
    for(int i = 0; i < tezine.size(); i++){
         std::cout<<tezine.at(i)<<" kg";
         std::cout<<(i == tezine.size() - 1? "\n" : ", ");
    }
    std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg\n"; 
}

void Kamion::IspisiPodatke() const
{
    std::cout<<"Vrsta vozila: Kamion\n"<<
    "Vlastita tezina: "<<DajTezinu()<<" kg\n"<<
    "Tezina tereta: "<<tezina_tereta<<" kg\n"<<
    "Ukupna tezina: "<<DajUkupnuTezinu()<<" kg\n";
}

void Autobus::IspisiPodatke() const
{
    std::cout<<"Vrsta vozila: Autobus\n"<<
    "Vlastita tezina: "<<DajTezinu()<<" kg\n"<<
    "Broj putnika: "<<broj_putnika<<
    "\nProsjecna tezina putnika: "<<prosjecna_tezina<<" kg\n"<<
    "Ukupna tezina: "<<DajUkupnuTezinu()<<" kg\n";
}