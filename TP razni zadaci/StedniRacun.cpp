#include <iostream>

class StedniRacun
{
    double stanje;
public:
    StedniRacun(double poc = 0): stanje(poc){
        if(poc < 0) throw std::logic_error("Nedozvoljeno pocetno stanje");
    };
    StedniRacun& Ulozi(double ulog){return Podigni(-ulog);};
    StedniRacun& Podigni(double iznos){
        if(iznos > stanje) throw std::logic_error("Transakcija odbijena");
        stanje -= iznos; return *this;
    }
    double DajStanje() const {return stanje;};
    StedniRacun& ObracunajKamatu(double kamata){
        if(kamata <= 0) throw std::logic_error("Nedozvoljena kamatna stopa");
        return Ulozi(stanje * (kamata / 100));
    }
};

int main()
{
    StedniRacun r1, r2(50);
    r1 = 30;
    r2.Ulozi(100);
    std::cout<<r1.Ulozi(30).DajStanje()<<std::endl;
    std::cout<<r2.DajStanje()<<std::endl;
    std::cout<<r2.ObracunajKamatu(25).DajStanje()<<std::endl;
    try
    {
        StedniRacun r3(-20);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        r1.Podigni(5000);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        r1.ObracunajKamatu(0);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    
    return 0;
}

