#include <cstring>
#include <iomanip>
#include <iostream>

class Tim
{
    char ime_tima[20];
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


int main() {
    Tim t("Olimpik");
    t.ObradiUtakmicu(3, 2);
    t.ObradiUtakmicu(0, 0);
    t.ObradiUtakmicu(1, 2);
    t.ObradiUtakmicu(1, 0);
    std::cout << t.DajImeTima() << " " << t.DajBrojPoena() 
    << " " << t.DajGolRazliku() << std::endl;
    t.IspisiPodatke();
    try
    {
        Tim t1("ppppppppppppppppppppp");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }  
    try
    {
        t.ObradiUtakmicu(-1, 0);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        t.ObradiUtakmicu(0, -1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        t.ObradiUtakmicu(-1, -1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
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
    else if(broj_datih = broj_primljenih) broj_poena++, broj_nerijesenih++;
    else broj_poraza++;
}


void Tim::IspisiPodatke() const
{
    std::cout << std::left << std::setw(20) << ime_tima << std::right
    << std::setw(4) << broj_odigranih << std::setw(4) << broj_pobjeda
    << std::setw(4) << broj_nerijesenih << std::setw(4) << broj_poraza
    << std::setw(4) << broj_datih << std::setw(4) << broj_primljenih
    << std::setw(4) << broj_poena << std::endl;
};
