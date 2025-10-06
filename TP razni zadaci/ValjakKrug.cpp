#include <cmath>
#include <iostream>

class Krug
{
    double poluprecnik;
    static const double PI;
public:
    explicit Krug(double r){
        Postavi(r);
    };
    Krug& Postavi(double r){
        if(r <= 0) throw std::domain_error("Neispravan poluprecnik");
        poluprecnik = r;
        return *this;
    };
    double DajPoluprecnik() const {return poluprecnik;};
    double DajObim() const {return 2 * DajPoluprecnik() * PI;};
    double DajPovrsinu() const {return DajPoluprecnik() * DajPoluprecnik() * PI;};
    Krug& Skaliraj(double skala){
        if(skala <= 0) throw std::domain_error("Neispravan faktor skaliranja");
        Postavi(DajPoluprecnik() * skala);
        return *this;
    }
    void Ispisi()const{std::cout<<"R = "<<DajPoluprecnik()<<" O = "
        <<DajObim()<<"P = "<<DajPovrsinu()<<std::endl;
    }
};

const double Krug::PI = 4 * std::atan(1);
class Valjak
{
    Krug baza;
    double visina;
    void PostaviVisinu(double visina){
        if(visina <= 0) throw std::domain_error("Neispravna visina");
        Valjak::visina = visina;
    };
public:
    Valjak(const Krug& k, double visina): baza(k){PostaviVisinu(visina);};
    Valjak(double r, double h): baza(r){PostaviVisinu(h);};
    Valjak& Postavi(const Krug& k, double visina){
        if(k.DajPoluprecnik() <= 0) throw std::domain_error("Neispravan poluprecnik");
        baza = k; PostaviVisinu(visina);
        return *this;
    }
    Valjak& Postavi(double r, double h){
        baza.Postavi(r); PostaviVisinu(h);
        return *this;
    }
    Krug& DajBazu(){return baza;};
    const Krug DajBazu() const{return baza;};
    double DajPoluprecnikBaze() const{return baza.DajPoluprecnik();};
    double DajPovrsinu() const{return 2 * baza.DajPovrsinu() + baza.DajObim() * DajVisinu();};
    double DajVisinu() const{return visina;};
    double DajZapreminu() const{return baza.DajPovrsinu() * DajVisinu();};
    Valjak& Skaliraj(double skala){
        baza.Skaliraj(skala); PostaviVisinu(DajVisinu() * skala);
        return *this;
    }
    void Ispisi() const{
        std::cout<<"R = "<<baza.DajPoluprecnik()<<" H = "<<DajVisinu()
        <<" P = "<<DajPovrsinu()<<" V = "<<DajZapreminu()<<std::endl;
    }
};

template < typename TipIzuzetka, typename FunkcijskiTip >
    void TestirajIzuzetak(FunkcijskiTip akcija) {
        try {
            akcija();
        } catch (TipIzuzetka & e) {
            std::cout << e.what() << std::endl;
        }
    }
    
int main() {
    auto NR = []() {
        std::cout << std::endl;
    };
    Krug k1(5);
    k1.Ispisi();
    NR(); // R=5 O=31.4159 P=78.5398
    k1.Postavi(10).Ispisi();
    NR(); // R=10 O=62.8319 P=314.159
    k1.Skaliraj(2).Ispisi();
    NR(); // R=20 O=125.664 P=1256.64
    std::cout << k1.DajPoluprecnik() << " " <<
        k1.DajObim() << " " << k1.DajPovrsinu() << std::endl; // 20 125.664 1256.64
    Valjak v1(5, 10);
    v1.Ispisi();
    NR(); // R=5 H=10 P=471.239 V=785.398
    v1.DajBazu().Ispisi();
    NR(); // R=5 O=31.4159 P=78.5398
    v1.Skaliraj(10).Ispisi();
    NR(); // R=50 H=100 P=47123.9 V=785398
    v1.DajBazu().Postavi(7).Ispisi();
    NR(); // R=7 O=43.9823 P=153.938
    v1.Ispisi();
    NR(); // R=7 H=100 P=4706.11 V=15393.8
    std::cout << v1.DajPoluprecnikBaze() << " " <<
        v1.DajVisinu() << " " << v1.DajPovrsinu() << " " <<
        v1.DajZapreminu() << std::endl // 7 100 4706.11 15393.8
        <<
        v1.DajBazu().DajPoluprecnik() << std::endl; // 7
    const Krug k2 = k1;
    k2.Ispisi();
    NR(); // R=20 O=125.664 P=1256.64
    std::cout << k2.DajPoluprecnik() << " " <<
        k2.DajObim() << " " << k2.DajPovrsinu() << std::endl; // 20 125.665 1256.64
    const Valjak v2 = v1;
    v2.Ispisi();
    NR(); // R=7 H=100 P=4706.11 V=15393.8
    std::cout << v2.DajPoluprecnikBaze() << " " <<
        v2.DajVisinu() << " " << v2.DajPovrsinu() << " " <<
        v2.DajZapreminu() << std::endl // 7 100 4706.11 15393.8
        <<
        v2.DajBazu().DajPoluprecnik() << std::endl; // 7
    TestirajIzuzetak < std::domain_error > ([]() {
        Krug k3(-10);
    });
    TestirajIzuzetak < std::domain_error > ([ & ]() {
        k1.Postavi(0);
    });
    TestirajIzuzetak < std::domain_error > ([ & ]() {
        k1.Skaliraj(-1);
    });
    TestirajIzuzetak < std::domain_error > ([]() {
        Valjak v3(-1, 5);
    });
    TestirajIzuzetak < std::domain_error > ([]() {
        Valjak v3(1, -5);
    });
    TestirajIzuzetak < std::domain_error > ([]() {
        Valjak v3(-1, -5);
    });
    TestirajIzuzetak < std::domain_error > ([ & ]() {
        v1.Postavi(-1, 5);
    });
    TestirajIzuzetak < std::domain_error > ([ & ]() {
        v1.Postavi(1, -5);
    });
    TestirajIzuzetak < std::domain_error > ([ & ]() {
        v1.Postavi(-1, -5);
    });
    TestirajIzuzetak < std::domain_error > ([ & ]() {
        v1.Skaliraj(-1);
    });
    return 0;
}
