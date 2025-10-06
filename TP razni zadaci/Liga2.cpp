#include <algorithm>
#include <cstring>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

class Tim
{
    char ime_tima[20]{};
    int broj_odigranih;
    int broj_pobjeda, broj_nerijesenih, broj_poraza;
    int broj_datih, broj_primljenih;
    int broj_poena;
public:
    Tim(const char ime[]);
    void ObradiUtakmicu(int broj_datih, int broj_primljenih); 
    const char *DajImeTima() const{return ime_tima;}; 
    int DajBrojPoena() const {return broj_poena;}; 
    int DajGolRazliku() const {return broj_datih - broj_primljenih;}; 
    void IspisiPodatke() const;
};

class Liga
{
    std::vector<std::shared_ptr<Tim>> timovi;
public:
    Liga() = default;
    explicit Liga(std::initializer_list<Tim> lista_timova);
    Liga(const Liga &l);
    Liga(Liga &&l) = default;
    Liga &operator =(const Liga &l);
    Liga &operator =(Liga &&l);
    void DodajNoviTim(const char ime_tima[]);
    void RegistrirajUtakmicu(const char tim1[], const char tim2[],
    int rezultat_1, int rezultat_2);
    void IspisiTimove() const;
    void IspisiTabelu() const;
};



int main() {
    Liga l{"Celik", "Borac", "Jedinstvo", "Zeljeznicar", "Zrinjski", "Sarajevo"};
    for(;;) {
    l.IspisiTabelu();
    char ime1[21], ime2[21];
    std::cout << std::endl << "Unesite ime prvog tima (ENTER za kraj): ";
    std::cin.getline(ime1, 21);
    if(std::strlen(ime1) == 0) break;
    std::cout << "Unesite ime drugog tima: ";
    std::cin.getline(ime2, 21);
    int bg1, bg2;
    std::cout << "Unesite broj postigutih golova za oba tima: ";
    std::cin >> bg1 >> bg2;
    std::cin.ignore(10000, '\n');
    try {
    l.RegistrirajUtakmicu(ime1, ime2, bg1, bg2);
    }
    catch(std::exception &e) {
    std::cout << e.what() << std::endl;
    }
    std::cout << std::endl;
    }
    return 0;
}

Tim::Tim(const char ime[]): broj_datih(), broj_nerijesenih(), broj_odigranih(),
        broj_pobjeda(), broj_poraza(), broj_poena(), broj_primljenih() 
{        
    if(strlen(ime) > 20) throw std::range_error("Predugacko ime tima");
    for(int i = 0; i < strlen(ime); i++) ime_tima[i] = ime[i];
}

void Tim::ObradiUtakmicu(int broj_datih, int broj_primljenih)
{
    if(broj_datih < 0 || broj_primljenih < 0) throw std::range_error("Neispravan broj golova");
    Tim::broj_datih += broj_datih;
    Tim::broj_primljenih += broj_primljenih;
    broj_odigranih++;
    if(broj_datih > broj_primljenih) broj_poena += 3, broj_pobjeda++;
    else if(broj_datih == broj_primljenih) broj_poena++, broj_nerijesenih++;
    else broj_poraza++;
}

void Tim::IspisiPodatke() const
{
    std::cout << std::left << std::setw(20) << ime_tima << std::right
    << std::setw(4) << broj_odigranih << std::setw(4) << broj_pobjeda
    << std::setw(4) << broj_nerijesenih << std::setw(4) << broj_poraza
    << std::setw(4) << broj_datih << std::setw(4) << broj_primljenih
    << std::setw(4) << broj_poena << std::endl;
}

Liga::Liga(std::initializer_list<Tim> lista_timova)
{
    for(auto p = lista_timova.begin(); p != lista_timova.end(); p++)
    {   
        timovi.push_back(std::make_shared<Tim>(*p));
    }
}

Liga::Liga(const Liga &l)
{
    timovi.resize(l.timovi.size());
    for(int i = 0; i < timovi.size(); i++)
    {
        timovi[i] = std::make_shared<Tim>(*l.timovi[i]);
    }
}

Liga& Liga::operator =(const Liga &l)
{
    if(timovi.size() != l.timovi.size()) throw std::logic_error("Nesaglasni kapaciteti liga");
    if(this != &l)
    {
        timovi.resize(0);
        for(int i = 0; i < l.timovi.size(); i++) 
            timovi.push_back(std::make_shared<Tim>(*l.timovi[i]));
    }
    return *this;
}

Liga& Liga::operator =(Liga &&l)
{
    if(timovi.size() != l.timovi.size()) throw std::logic_error("Nesaglasni kapaciteti liga");
    timovi = l.timovi;
    return *this;
}

void Liga::DodajNoviTim(const char ime_tima[])
{
    timovi.push_back(std::make_shared<Tim>(ime_tima));
}

void Liga::RegistrirajUtakmicu(const char tim1[], const char tim2[],
    int rezultat_1, int rezultat_2)
{
    int prvi{-1}, drugi{-1};
    for(int i = 0; i < timovi.size(); i++)
        if(!strcmp(timovi[i]->DajImeTima(), tim1))
            prvi = i;
        else if(!strcmp(timovi[i]->DajImeTima(), tim2))
            drugi = i;
    if(prvi == -1 || drugi == -1) throw std::logic_error("Tim nije nadjen");
    try
    {
       timovi[prvi]->ObradiUtakmicu(rezultat_1, rezultat_2);
       timovi[drugi]->ObradiUtakmicu(rezultat_2, rezultat_1); 
    }
    catch(const std::exception& e)
    {
        throw;
    }  
}

void Liga::IspisiTimove() const
{
    for(int i{}; i < timovi.size(); i++)
        std::cout<<timovi[i]->DajImeTima()<<std::endl;
}

void Liga::IspisiTabelu() const
{
    std::vector<std::shared_ptr<Tim>> zasort = timovi;
    std::sort(zasort.begin(), zasort.end(), [](std::shared_ptr<Tim> prvi, std::shared_ptr<Tim> drugi)
    {
        if(prvi->DajBrojPoena() == drugi->DajBrojPoena())
            if(prvi->DajGolRazliku() == drugi->DajGolRazliku())
                return toupper(prvi->DajImeTima()[0]) < toupper(drugi->DajImeTima()[0]);
            else return prvi->DajGolRazliku() > drugi->DajGolRazliku();
        return prvi->DajBrojPoena() > drugi->DajBrojPoena();
    });
    for(int i = 0; i < zasort.size(); i++)
    {
        zasort.at(i)->IspisiPodatke();
    }
} 