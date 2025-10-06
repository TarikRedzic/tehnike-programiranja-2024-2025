#include <algorithm>
#include <cstring>
#include <initializer_list>
#include <iomanip>
#include <iostream>

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
    int broj_timova;
    const int max_br_timova;
    Tim** timovi;
    Tim** Alociraj(int);
    void Dealociraj();
public:
    explicit Liga(int velicina_lige);
    explicit Liga(std::initializer_list<Tim> lista_timova);
    ~Liga(){Dealociraj();};
    Liga(const Liga &l);
    Liga(Liga &&l);
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

Tim** Liga::Alociraj(int n)
{
    Tim** pok{};
    try
    {
        pok = new Tim*[n]{};
    }
    catch(const std::exception& e)
    {
        throw;
    }
    return pok;
}
void Liga::Dealociraj()
{
    for(int i = 0; i < broj_timova; i++) delete timovi[i];
    delete[] timovi;    
}

Liga::Liga(int velicina_lige): timovi{nullptr}, max_br_timova(velicina_lige)
{
    broj_timova = 0;
    try {
        timovi = Alociraj(velicina_lige);
    } catch(const std::exception& e){
        throw;
    }
    
}

Liga::Liga(std::initializer_list<Tim> lista_timova): max_br_timova(lista_timova.size()), 
    broj_timova(lista_timova.size())
{
    try {
        timovi = Alociraj(max_br_timova);
        int i{};
        for(auto p = lista_timova.begin(); p != lista_timova.end(); p++, i++)
        {   
            timovi[i] = new Tim(*p);
        }
    } 
    catch(const std::exception& e) 
    {
        Dealociraj();
        throw;
    }
    
}

Liga::Liga(const Liga &l): max_br_timova(l.max_br_timova)
{
    try
    {
        timovi = Alociraj(l.max_br_timova);
        for(int i = 0; i < max_br_timova; i++)
        {
            timovi[i] = new Tim(*l.timovi[i]);
        }
    }
    catch(const std::exception& e)
    {
        Dealociraj();
        throw;
    }
}

Liga::Liga(Liga &&l): max_br_timova(l.max_br_timova), broj_timova(l.broj_timova),
    timovi(l.timovi)
{
    l.broj_timova = 0;
    l.timovi = nullptr;
}

Liga& Liga::operator =(const Liga &l)
{
    if(max_br_timova != l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
    if(this != &l)
    {
        try
        {
            for(int i = 0; i < broj_timova; i++) delete timovi[i];
            for(int i = 0; i < l.broj_timova; i++) 
            timovi[i] = new Tim(*l.timovi[i]);
            broj_timova = l.broj_timova;
        }
        catch(const std::exception& e)
        {
            Dealociraj();
            throw;
        } 
    }
    return *this;
}

Liga& Liga::operator =(Liga &&l)
{
    if(max_br_timova != l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
    Dealociraj();
    timovi = l.timovi;
    l.timovi = nullptr;
    return *this;
}

void Liga::DodajNoviTim(const char ime_tima[])
{
    if(broj_timova = max_br_timova) throw std::range_error("Liga popunjena");
    try
    {
        for(int i = 0; i < broj_timova; i++)
            if(!strcmp(timovi[i]->DajImeTima(), ime_tima)) 
                throw std::logic_error("Tim vec postoji");
        timovi[broj_timova++] = new Tim(ime_tima);
    }
    catch(const std::exception& e)
    {
        throw;
    }
}

void Liga::RegistrirajUtakmicu(const char tim1[], const char tim2[],
    int rezultat_1, int rezultat_2)
{
    int prvi{-1}, drugi{-1};
    for(int i = 0; i < broj_timova; i++)
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
    for(int i{}; i < broj_timova; i++)
        std::cout<<timovi[i]->DajImeTima()<<std::endl;
}

void Liga::IspisiTabelu() const
{
    auto zasort = timovi;
    std::sort(zasort, zasort + broj_timova, [](const Tim *prvi, const Tim *drugi)
    {
        if(prvi->DajBrojPoena() == drugi->DajBrojPoena())
            if(prvi->DajGolRazliku() == drugi->DajGolRazliku())
                return toupper(prvi->DajImeTima()[0]) < toupper(drugi->DajImeTima()[0]);
            else return prvi->DajGolRazliku() > drugi->DajGolRazliku();
        return prvi->DajBrojPoena() > drugi->DajBrojPoena();
    });
    for(int i = 0; i < broj_timova; i++)
    {
        zasort[i]->IspisiPodatke();
    }
} 