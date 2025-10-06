#include <iomanip>
#include <iostream>

struct Vrijeme
{
    int sati, minute, sekunde;
};

bool ProvjeraVremena(struct Vrijeme t)
{
    if(t.sati < 0 || t.sati > 23 || t.minute < 0 ||
        t.minute > 59 || t.sekunde < 0 || t.sekunde > 59)
        return false;
    return true;
}
void IspisiVrijeme(struct Vrijeme t)
{
    if(!ProvjeraVremena(t)) throw std::domain_error("Neispravno vrijeme"); 
    std::cout<<std::setw(2)<<std::setfill('0')<<t.sati<<":"<<t.minute<<":"<<t.sekunde<<std::endl;  
}

struct Vrijeme ZbirVremena(struct Vrijeme prvo, struct Vrijeme drugo)
{
    if(!(ProvjeraVremena(prvo) && ProvjeraVremena(drugo))) throw std::domain_error("Neispravno vrijeme");
    int ukupno = prvo.sekunde + prvo.minute * 60 + prvo.sati*3600
        + drugo.sekunde + drugo.minute * 60 + drugo.sati * 3600;
    Vrijeme Zbir{};
    Zbir.sati = ukupno / 3600;
    ukupno %= 3600;
    Zbir.minute = ukupno / 60;
    ukupno %= 60;
    Zbir.sekunde = ukupno;
    Zbir.sati %= 24;
    return Zbir;
}

int main()
{
    Vrijeme prvo, drugo;
    std::cout<<"Unesite prvo vrijeme (h m s): ";
    std::cin>>prvo.sati>>prvo.minute>>prvo.sekunde;
    if(!ProvjeraVremena(prvo))
    {
        std::cout<<"Neispravno vrijeme";
        return 1;
    }
    std::cout<<"Unesite drugo vrijeme (h m s): ";
    std::cin>>drugo.sati>>drugo.minute>>drugo.sekunde;
    if(!ProvjeraVremena(drugo))
    {
        std::cout<<"Neispravno vrijeme";
        return 1;
    }
    std::cout<<"Prvo vrijeme: ";IspisiVrijeme(prvo);
    std::cout<<"Drugo vrijeme: ";IspisiVrijeme(drugo);
    try
    {
        std::cout<<"Zbir vremena: ";IspisiVrijeme(ZbirVremena(prvo, drugo));
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    
    return 0;
}