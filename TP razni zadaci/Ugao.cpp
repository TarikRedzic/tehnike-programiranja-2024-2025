#include <cmath>
#include <iostream>

class Ugao
{
    double radijani;
    static int CijeliDio(double x) { return int(x + 1e-10); }
    static const double PI;
public:
    Ugao(double radijani = 0);
    Ugao(int stepeni, int minute, int sekunde);
    Ugao & Postavi(double radijani);
    Ugao & Postavi(int stepeni, int minute, int sekunde);
    double DajRadijane() const{return radijani;};
    void OcitajKlasicneJedinice(int & stepeni, int & minute, int & sekunde);
    int DajStepene() const;
    int DajMinute() const;
    int DajSekunde() const;
    void Ispisi() const{std::cout<<DajRadijane();};
    void IspisiKlasicno() const{std::cout<<DajStepene()<<"^ "
        <<DajMinute()<<"' "<<DajSekunde()<<"\"\n";};
    Ugao & SaberiSa(const Ugao & u);
    Ugao & PomnoziSa(double x);
    friend Ugao ZbirUglova(const Ugao & u1, const Ugao & u2);
    friend Ugao ProduktUglaSaBrojem(const Ugao & u, double x);
};
const double Ugao::PI = 4 * std::atan(1);

int main() {
    auto NR = []() {
        std::cout << std::endl;
    };
    Ugao u1, u2(1), u3(100), u4(-1), u5 = 1;
    u1.Ispisi();
    NR(); // 0
    u2.Ispisi();
    NR(); // 1
    u3.Ispisi();
    NR(); // 5.75222
    u4.Ispisi();
    NR(); // 5.28319
    u5.Ispisi();
    NR(); // 1
    u2.IspisiKlasicno();
    NR(); // 57^ 17' 45"
    std::cout << u2.DajRadijane() << std::endl; // 1
    std::cout << u2.DajStepene() << " " << u2.DajMinute() <<
        " " << u2.DajSekunde() << std::endl; // 57 17 45
    u1.Postavi(2).Ispisi();
    NR(); // 2
    u1.IspisiKlasicno();
    NR(); // 114^ 35' 30"
    u1.Postavi(50, 25, 12).Ispisi();
    NR(); // 0.879995
    u1.IspisiKlasicno();
    NR(); // 50^ 25' 12"
    u1.Postavi(500, 300, 200).IspisiKlasicno();
    NR(); // 145^ 3' 20"
    u1.Postavi(-10, -20, -30).IspisiKlasicno();
    NR(); // 349^ 39' 30"
    Ugao u6(50, 25, 12), u7(500, 300, 200), u8(-10, -20, -30);
    u6.IspisiKlasicno();
    NR(); // 50^ 25' 12"
    u7.IspisiKlasicno();
    NR(); // 145^ 3' 20"
    u8.IspisiKlasicno();
    NR(); // 349^ 39' 30"
    u2.SaberiSa(u5).IspisiKlasicno();
    NR(); // 114^ 35' 30"
    u2.SaberiSa(u3).IspisiKlasicno();
    NR(); // 84^ 10' 10"
    u2.SaberiSa(u3).SaberiSa(u4).IspisiKlasicno();
    NR(); // 356^ 27' 6"
    u1.SaberiSa(u2).SaberiSa(u3).Ispisi();
    NR(); // 5.50979
    u1.SaberiSa(1).IspisiKlasicno();
    NR(); // 12^ 59' 1"
    u2.PomnoziSa(5).IspisiKlasicno();
    NR(); // 342^ 15' 30"
    u3.PomnoziSa(5).SaberiSa(u1).Ispisi();
    NR(); // 3.85497
    u3.IspisiKlasicno();
    NR(); // 220^ 52' 25"
    u1 = ZbirUglova(u2, u3);
    u1.IspisiKlasicno();
    NR(); // 203^ 7' 55"
    ZbirUglova(u2, u3).IspisiKlasicno();
    NR(); // 203^ 7' 55"
    u1 = ZbirUglova(u1, 5);
    u1.IspisiKlasicno();
    NR(); // 129^ 36' 39"
    ZbirUglova(1, 2).Ispisi();
    NR(); // 3
    u4 = ProduktUglaSaBrojem(u1, 5);
    u4.IspisiKlasicno();
    NR(); // 288^ 3’ 15"
    ProduktUglaSaBrojem(u1, 5).IspisiKlasicno();
    NR(); // 288^ 3’ 15"
    ProduktUglaSaBrojem(1.5, 2.5).Ispisi();
    NR(); // 3.75
    const Ugao u9 = u1;
    std::cout << u9.DajRadijane() << " " << std::endl // 2.26214
        <<
        u9.DajStepene() << " " << u9.DajMinute() << " " <<
        u9.DajSekunde() << std::endl; // 129 36 39
    u9.Ispisi();
    NR(); // 2.26214
    u9.IspisiKlasicno();
    NR(); // 129^ 36' 39"
    return 0;
}

Ugao::Ugao(double radijani)
{
    Postavi(radijani);
}

Ugao::Ugao(int stepeni, int minute, int sekunde)
{
   Postavi(stepeni, minute, sekunde);
}

Ugao& Ugao::Postavi(double radijani)
{
    if(radijani >= 0 || radijani < 2*PI) radijani -= CijeliDio(radijani / (2 * PI)) * (2*PI);
    else radijani += 2 * PI;
    Ugao::radijani = radijani;
    return *this;
}

Ugao& Ugao::Postavi(int stepeni, int minute, int sekunde)
{
    return Postavi((stepeni + minute / 60. + sekunde / 3600.) * (2 * PI/ 180));
}

void Ugao::OcitajKlasicneJedinice(int& stepeni, int& minute, int& sekunde)
{
    stepeni = DajStepene(); minute = DajMinute(); sekunde = DajSekunde();
}

int Ugao::DajStepene() const
{
    return CijeliDio((DajRadijane() * 180) / PI);
}

int Ugao::DajMinute() const
{
    (((DajRadijane() * 180) / PI) - DajStepene());
}

int Ugao::DajSekunde() const
{
    
}

Ugao& Ugao::SaberiSa(const Ugao& u)
{
    return Postavi(DajRadijane() + u.DajRadijane());
}

Ugao& Ugao::PomnoziSa(double x)
{
    return Postavi(DajRadijane() * x);
}

Ugao ZbirUglova(const Ugao & u1, const Ugao & u2)
{
    return Ugao(u1.DajRadijane() + u2.DajRadijane());
}

Ugao ProduktUglaSaBrojem(const Ugao & u, double x)
{
    return {u.DajRadijane() * x};
}