#include <algorithm>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <string>

class Polazak
{
    std::string odrediste;
    int broj_voza, broj_perona, trajanje_voznje;
    int sat_polaska, minute_polaska, kasnjenje;
    bool brzi_voz;
public:
    Polazak(std::string odrediste, int broj_voza, int broj_perona, bool brzi_voz,
    int sat_polaska, int minute_polaska, int trajanje_voznje);
    void PostaviKasnjenje(int kasnjenje){Polazak::kasnjenje = kasnjenje;};
    bool DaLiKasni() const{return kasnjenje;};
    int DajTrajanjeVoznje() const{return trajanje_voznje;};
    std::pair<int, int> DajOcekivanoVrijemePolaska() const;
    std::pair<int, int> DajOcekivanoVrijemeDolaska() const;
    void Ispisi() const;
};
class RedVoznje
{
    int max_broj_polazaka, br_polazaka;
    void Dealociraj(int a);
    Polazak** podaci;
public:
    explicit RedVoznje(int max_broj_polazaka);
    RedVoznje(std::initializer_list<Polazak> lista_polazaka);
    ~RedVoznje();
    RedVoznje(const RedVoznje &red_voznje);
    RedVoznje(RedVoznje &&red_voznje);
    RedVoznje &operator =(const RedVoznje &red_voznje);
    RedVoznje &operator =(RedVoznje &&red_voznje);
    void RegistrirajPolazak(std::string odrediste, int broj_voza, bool brzi_voz,
    int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje);
    void RegistrirajPolazak(Polazak *polazak);
    int DajBrojPolazaka() const{return br_polazaka;};
    int DajBrojPolazakaKojiKasne() const;
    int DajProsjecnoTrajanjeVoznji() const;
    Polazak &DajPrviPolazak() const;
    Polazak &DajPosljednjiPolazak() const;
    void IsprazniRedVoznje();
    void Ispisi(int sati, int minute) const;
};

int main()
{
    RedVoznje v(6);
    v.RegistrirajPolazak("A", 123, true, 5, 12, 30, 120);
    v.RegistrirajPolazak("B", 124, false, 4, 10, 20,  180);
    v.RegistrirajPolazak("C", 125, false, 1, 6, 30, 120);
    v.RegistrirajPolazak("D", 127, false, 2, 20, 30, 120);
    Polazak* p = new Polazak("Bugojno", 3, 3, true, 12, 34, 30);
    v.RegistrirajPolazak(p);
    v.Ispisi(10, 30);
    RedVoznje v1 = std::move(v);
    try
    {
        v1.DajPosljednjiPolazak().PostaviKasnjenje(40);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout<<v1.DajBrojPolazakaKojiKasne()<<v1.DajBrojPolazaka()<<std::endl;
    RedVoznje v2(v1);
    RedVoznje v3(2);
    v3 = v2;
    std::cout<<v2.DajProsjecnoTrajanjeVoznji()<<std::endl
    <<v3.DajProsjecnoTrajanjeVoznji()<<std::endl;
}

Polazak::Polazak(std::string odrediste, int broj_voza, int broj_perona, bool brzi_voz,
    int sat_polaska, int minute_polaska, int trajanje_voznje)
{
    if(sat_polaska > 23 || sat_polaska < 0 || minute_polaska < 0 || minute_polaska > 59)
        throw std::domain_error("Neispravno vrijeme polaska");
    if(broj_voza < 0 || broj_voza > 99999) throw std::domain_error("Neispravan broj voza");
    if(broj_perona < 1 || broj_perona > 6) throw std::domain_error("Neispravan broj perona");
    if(trajanje_voznje < 0) throw std::domain_error("Neispravno trajanje voznje");
    PostaviKasnjenje(0); Polazak::broj_voza = broj_voza; Polazak::broj_perona = broj_perona;
    Polazak::brzi_voz = brzi_voz; Polazak::trajanje_voznje = trajanje_voznje;
    Polazak::sat_polaska = sat_polaska; Polazak::minute_polaska = minute_polaska;
    Polazak::odrediste = odrediste;
}

std::pair<int, int> Polazak::DajOcekivanoVrijemeDolaska() const
{
    int min = DajOcekivanoVrijemePolaska().second + trajanje_voznje;
    int sat = (DajOcekivanoVrijemePolaska().first + min / 60) % 24;
    min = min % 60;
    return {sat, min};
}

std::pair<int, int> Polazak::DajOcekivanoVrijemePolaska() const
{
    int min = minute_polaska + kasnjenje;
    int sat = (sat_polaska + min / 60) % 24;
    min %= 60;
    return {sat, min};
}

void Polazak::Ispisi() const
{
    if(!DaLiKasni()) std::cout<<(brzi_voz ?"Brzi voz broj " :"Lokalni voz broj ")<<broj_voza<<", odrediste "
    <<odrediste<<", polazi s perona "<<broj_perona<<" u "<<std::setfill('0')<<std::setw(2)
    <<DajOcekivanoVrijemePolaska().first<<":"<<std::setfill('0')<<std::setw(2)<<
    DajOcekivanoVrijemePolaska().second<<", a na odrediste stize u "<<std::setfill('0')<<std::setw(2)
    <<DajOcekivanoVrijemeDolaska().first<<":"<<std::setfill('0')<<std::setw(2)<<
    DajOcekivanoVrijemeDolaska().second<<". Putnicima i voznom osoblju zelimo ugodno putovanje."<<std::endl;
    else std::cout<<(brzi_voz ?"Brzi voz broj " :"Lokalni voz broj ")<<broj_voza<<", odrediste "
    <<odrediste<<", sa predvidjenim vremenom polaska u "<<std::setfill('0')<<std::setw(2)
    <<sat_polaska<<":"<<std::setfill('0')<<std::setw(2)<<minute_polaska<<", kasni oko "<<kasnjenje
    <<" minuta, te ce poci oko "<<std::setfill('0')<<std::setw(2)<<DajOcekivanoVrijemePolaska().first<<
    ":"<<std::setfill('0')<<std::setw(2)<<DajOcekivanoVrijemePolaska().second<<
    ". Ocekuje se da voz stigne na odrediste oko "<<std::setfill('0')<<std::setw(2)
    <<DajOcekivanoVrijemeDolaska().first<<":"<<std::setfill('0')<<std::setw(2)<<
    DajOcekivanoVrijemeDolaska().second<<". Izvinjavamo se putnicima zbog eventualnih neugodnosti."<<std::endl;
}

RedVoznje::RedVoznje(int max_broj_polazaka)
{
    podaci = new Polazak*[max_broj_polazaka]();
    RedVoznje::max_broj_polazaka = max_broj_polazaka;
    br_polazaka = 0;
}

RedVoznje::RedVoznje(const RedVoznje &red_voznje)
{
    int br_pol = red_voznje.DajBrojPolazaka();
    auto temp = new Polazak*[red_voznje.max_broj_polazaka]();
    try
    {
        for(int i{}; i < br_pol; i++)
        {
            temp[i] = new Polazak(*red_voznje.podaci[i]);
        }
    }
    catch(const std::exception& e)
    {
        for(int i{}; i < br_pol; i++)
        {
            delete temp[i];
        }
        delete[] temp;
        throw;
    }
    br_polazaka = br_pol;
    max_broj_polazaka = red_voznje.max_broj_polazaka;
    podaci = temp;
}

RedVoznje::RedVoznje(std::initializer_list<Polazak> lista_polazaka)
{
    auto temp = new Polazak*[lista_polazaka.size()]();
    try
    {
        int i{};
        for(auto p = lista_polazaka.begin(); p != lista_polazaka.end(); p++, i++)
        {
            temp[i] = new Polazak(*p);
        }
    }
    catch(const std::exception& e)
    {
        for(int i{}; i < lista_polazaka.size(); i++)
        {
            delete temp[i];
        }
        delete[] temp;
        throw;
    }
    max_broj_polazaka = br_polazaka = lista_polazaka.size();
    podaci = temp;
}

void RedVoznje::Dealociraj(int a)
{
    for(int i{}; i < a; i++)
        delete podaci[i];
    delete[] podaci;
}

RedVoznje::~RedVoznje()
{
    RedVoznje::Dealociraj(br_polazaka);
}

RedVoznje::RedVoznje(RedVoznje &&red_voznje)
{
    if(this != &red_voznje)
    {
        podaci = red_voznje.podaci;
        red_voznje.podaci = nullptr;
        br_polazaka = red_voznje.DajBrojPolazaka();
        max_broj_polazaka = red_voznje.max_broj_polazaka;
        red_voznje.br_polazaka = red_voznje.max_broj_polazaka = 0;
    }
}

RedVoznje& RedVoznje::operator =(const RedVoznje &red_voznje)
{
    int br_pol = red_voznje.DajBrojPolazaka();
    auto temp = new Polazak*[red_voznje.max_broj_polazaka]();
    try
    {
        for(int i{}; i < br_pol; i++)
        {
            temp[i] = new Polazak(*red_voznje.podaci[i]);
        }
    }
    catch(const std::exception& e)
    {
        for(int i{}; i < br_pol; i++)
        {
            delete temp[i];
        }
        delete[] temp;
        throw;
    }
    Dealociraj(br_polazaka);
    br_polazaka = red_voznje.DajBrojPolazaka();
    max_broj_polazaka = red_voznje.max_broj_polazaka;
    podaci = temp;
    return *this;
}

RedVoznje &RedVoznje::operator =(RedVoznje &&red_voznje)
{
    if(this != &red_voznje)
    {
        Dealociraj(max_broj_polazaka);
        podaci = red_voznje.podaci;
        red_voznje.podaci = nullptr;
        br_polazaka = red_voznje.br_polazaka;
        max_broj_polazaka = red_voznje.max_broj_polazaka;
        red_voznje.br_polazaka = red_voznje.max_broj_polazaka = 0;
    }
    return *this;
}

void RedVoznje::RegistrirajPolazak(std::string odrediste, int broj_voza, bool brzi_voz,
    int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje)
{
    if(br_polazaka == max_broj_polazaka) throw std::range_error("Dostignut maksimalni broj polazaka");
    podaci[RedVoznje::br_polazaka++] = new Polazak(odrediste, broj_voza, broj_perona, brzi_voz, sat_polaska,
        minute_polaska, trajanje_voznje);
}

void RedVoznje::RegistrirajPolazak(Polazak *polazak)
{
    if(br_polazaka == max_broj_polazaka) throw std::range_error("Dostignut maksimalni broj polazaka");
    podaci[RedVoznje::br_polazaka++] = polazak;
}

int RedVoznje::DajBrojPolazakaKojiKasne() const
{
    return std::count_if(podaci, podaci + DajBrojPolazaka(), [](auto* p){
        return p->DaLiKasni();
    });
}

int RedVoznje::DajProsjecnoTrajanjeVoznji() const
{
    int uk{};
    for(int i{}; i < DajBrojPolazaka(); i++) uk += podaci[i]->DajTrajanjeVoznje();
    return uk / DajBrojPolazaka();
}   

Polazak& RedVoznje::DajPrviPolazak() const
{
    if(!DajBrojPolazaka()) throw std::domain_error("Nema registriranih podataka");
    auto it = std::min_element(podaci, podaci + DajBrojPolazaka(), [](Polazak* p1, Polazak* p2){
        auto kp1 = p1->DajOcekivanoVrijemePolaska(), kp2 = p2->DajOcekivanoVrijemePolaska();
        int pp1 = kp1.first * 60 + kp1.second, pp2 = kp2.first * 60 + kp2.second;
        return pp1 < pp2;
    });
    return **it;
}

Polazak& RedVoznje::DajPosljednjiPolazak() const
{
    if(!DajBrojPolazaka()) throw std::domain_error("Nema registriranih podataka");
    auto it = std::max_element(podaci, podaci + DajBrojPolazaka(), [](Polazak* p1, Polazak* p2){
        auto kp1 = p1->DajOcekivanoVrijemePolaska(), kp2 = p2->DajOcekivanoVrijemePolaska();
        int pp1 = kp1.first * 60 + kp1.second, pp2 = kp2.first * 60 + kp2.second;
        return pp1 < pp2;
    });
    return **it;
}

void RedVoznje::IsprazniRedVoznje()
{
    for(int i{}; i < DajBrojPolazaka(); i++)
    {
        delete podaci[i];
        podaci[i] = nullptr;
    }
    br_polazaka = 0;
}

void RedVoznje::Ispisi(int sati, int minute) const
{
    std::sort(podaci, podaci + DajBrojPolazaka(), [](Polazak* p1, Polazak* p2){
        if(p1->DajOcekivanoVrijemePolaska().first == p2->DajOcekivanoVrijemePolaska().first)
            return p1->DajOcekivanoVrijemePolaska().second < p2->DajOcekivanoVrijemePolaska().second;
        else return  p1->DajOcekivanoVrijemePolaska().first < p2->DajOcekivanoVrijemePolaska().first;
    });
    for(int i{}; i < DajBrojPolazaka(); i++)
    {
        if(podaci[i]->DajOcekivanoVrijemePolaska().first > sati || (podaci[i]->DajOcekivanoVrijemePolaska().first == sati &&
            podaci[i]->DajOcekivanoVrijemePolaska().second >= minute)) podaci[i]->Ispisi();
    }
}