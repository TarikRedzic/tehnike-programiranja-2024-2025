#include <iostream>

class StedniRacun
{
    double stanje;
    static int broj_kreiranih, broj_aktivnih;
public:
    StedniRacun(double poc = 0): stanje(poc){
        if(poc < 0) throw std::logic_error("Nedozvoljeno pocetno stanje");
        broj_aktivnih++;
        broj_kreiranih++;
    };
    StedniRacun(const StedniRacun &s){
        stanje = s.stanje;
        broj_aktivnih++;
        broj_kreiranih++;
    };
    ~StedniRacun(){broj_aktivnih--;};
    StedniRacun operator=(StedniRacun &&s) = delete;
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
    static int DajBrojKreiranih(){return broj_kreiranih;};
    static int DajBrojAktivnih(){return broj_aktivnih;};
};

int StedniRacun::broj_aktivnih = 0;
int StedniRacun::broj_kreiranih = 0;

int main()
{
    StedniRacun r1, r2(50);
    StedniRacun r3 = 50;
    r2.Ulozi(100);
    std::cout<<r1.Ulozi(30).DajStanje()<<std::endl;
    std::cout<<r2.DajStanje()<<std::endl;
    std::cout<<r2.ObracunajKamatu(25).DajStanje()<<std::endl;
    std::cout << StedniRacun::DajBrojKreiranih()
    << " " << StedniRacun::DajBrojAktivnih()<<std::endl;
    StedniRacun s1, s2(100);
    { StedniRacun s3(50); } // Nakon "}", "s3" više ne postoji...
    std::cout << StedniRacun::DajBrojKreiranih()
    << " " << StedniRacun::DajBrojAktivnih()<<std::endl;
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

