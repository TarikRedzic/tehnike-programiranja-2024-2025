#include <iomanip>
#include <iostream>

class Sat
{
    int sati{}, minute{}, sekunde{};
public:
    static bool DaLiJeIspravno(const int, const int, const int);
    Sat& Postavi(int, int, int);
    Sat& PostaviNormalizirano(int, int, int);
    Sat& Sljedeci();
    Sat& Prethodni();
    Sat& PomjeriZa(int);
    void Ispisi() const;
    int DajSate() const{return sati;};
    int DajMinute() const {return minute;};
    int DajSekunde() const {return sekunde;};
    static int Razmak(const Sat &s1, const Sat &s2);
    friend int BrojSekundiIzmedju(const Sat &s1, const Sat &s2);
};



int main() {
    auto NR = []() {
        std::cout << std::endl;
    };
    Sat s1, s2;
    s1.Ispisi();
    NR(); // 00:00:00
    std::cout << std::boolalpha <<
        Sat::DaLiJeIspravno(10, 10, 10) << " " <<
        Sat::DaLiJeIspravno(10, 70, 30) << " " <<
        Sat::DaLiJeIspravno(-1, 0, 0) << std::endl; // true false false
    s1.Postavi(20, 4, 39).Ispisi();
    NR(); // 20:04:39
    std::cout << s1.DajSate() << " " << s1.DajMinute() << " " <<
        s1.DajSekunde() << std::endl; // 20 4 39
    try 
    {
        s2.Postavi(30, 10, -1);
    } 
    catch (std::domain_error e) 
    {
        std::cout << e.what() << std::endl; // Neispravno vrijeme
    }
    s2.PostaviNormalizirano(25, 150, 290).Ispisi();
    NR(); // 03:34:50
    s2.PostaviNormalizirano(0, 0, -1).Ispisi();
    NR(); // 23:59:59
    s1.Sljedeci().Ispisi();
    NR(); // 20:04:40
    s1.Prethodni().Ispisi();
    NR(); // 20:04:39
    s2.Sljedeci().Sljedeci().Sljedeci().Ispisi();
    NR(); // 00:00:02
    s2.Prethodni().Prethodni().Prethodni().Ispisi();
    NR(); // 23:59:59
    s1.PomjeriZa(25000).Ispisi();
    NR(); // 03:01:19
    s1.PomjeriZa(-25000).Ispisi();
    NR(); // 20:04:39
    s1.PomjeriZa(100).Sljedeci().Ispisi();
    NR(); // 20:06:20
    std::cout << BrojSekundiIzmedju(s1, s2) << " " <<
        BrojSekundiIzmedju(s2, s1) << std::endl; // -14019 14019
    std::cout << Sat::Razmak(s1, s2) << " " <<
        Sat::Razmak(s2, s1) << std::endl; // -14019 14019
    const Sat s3 = s1;
    s3.Ispisi();
    NR(); // 20:06:20
    std::cout << s3.DajSate() << " " << s3.DajMinute() << " " <<
        s3.DajSekunde() << std::endl; // 20 6 20
    return 0;
}

bool Sat::DaLiJeIspravno(int sat, int minut, int sekund)
{
    if(sat > 23 || sat < 0) return false;
    if(minut > 59 || minut < 0) return false;
    if(sekund > 59 || sekund < 0) return false;
    return true;
}

Sat& Sat::Postavi(int sat, int min, int sek)
{
    if(!DaLiJeIspravno(sat, min, sek)) throw std::domain_error("Neispravno vrijeme");
    sati = sat; minute = min; sekunde = sek;
    return *this;
}

Sat& Sat::PostaviNormalizirano(int sat, int min, int sek)
{
    int ukupno = (3600 * sat + 60 * min + sek) % 86400;   
    if(ukupno < 0) ukupno += 86400;   
    Sat::sati = ukupno / 3600;   
    Sat::minute = (ukupno % 3600) / 60;   
    Sat::sekunde = ukupno % 60;   
    return *this;
}

Sat& Sat::Sljedeci()
{
    return PostaviNormalizirano(sati, minute, sekunde + 1);
}

Sat& Sat::Prethodni()
{
    return PostaviNormalizirano(sati, minute, sekunde - 1);
}

Sat& Sat::PomjeriZa(int t)
{
    return PostaviNormalizirano(sati, minute, sekunde + t);
}

void Sat::Ispisi() const
{
    std::cout<<std::setw(2)<<std::setfill('0')<<sati<<
        ":"<<std::setw(2)<<std::setfill('0')<<minute<<
        ":"<<std::setw(2)<<std::setfill('0')<<sekunde<<std::endl;
}

int BrojSekundiIzmedju(const Sat &s1, const Sat &s2)
{
    int sek1{s1.DajSate() * 3600 + s1.DajMinute() * 60 + s1.DajSekunde()},
        sek2{s2.DajSate() * 3600 + s2.DajMinute() * 60 + s2.DajSekunde()};
    return sek1 - sek2;
}   

int Sat::Razmak(const Sat &s1, const Sat &s2)
{
    BrojSekundiIzmedju(s1, s2);
}