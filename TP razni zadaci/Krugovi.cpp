#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>

#define PI (4 * atan(1))
struct Krug{double x, y, r;};
class Krugovi
{
    int kapacitet, broj_krugova;
    Krug* krugovi;
public:
    explicit Krugovi(int broj): krugovi(nullptr), kapacitet(broj), broj_krugova(0) {
        krugovi = new Krug[broj]();
    };
    ~Krugovi(){
        broj_krugova = 0; kapacitet = 0; delete[] krugovi;
    }
    Krugovi(const Krugovi& k): broj_krugova(k.broj_krugova), kapacitet(k.kapacitet), krugovi(nullptr)
    {
        krugovi = new Krug[kapacitet]();
        for(int i = 0; i < kapacitet; i++){krugovi[i] = k.krugovi[i];};
    }
    Krugovi operator=(const Krugovi& k);
    Krugovi(Krugovi &&k);
    Krugovi operator=(Krugovi &&k);
    void DodajKrug(double, double, double);
    Krug& DajKrug(int i);
    const Krug& DajKrug(int i) const;
    void IspisiKrugove() const;
};

template <typename TipIzuzetka>
 void TestirajIzuzetak(std::function<void()> akcija) {
 try { akcija(); }
 catch(TipIzuzetka &e) { std::cout << e.what() << std::endl; }
}


int main()
{
    Krugovi k(4);
    k.DodajKrug(10, 10, 3); k.DodajKrug(20, 5, 3); k.DodajKrug(0, 0, 4);
    TestirajIzuzetak<std::logic_error>([&]() { k.DodajKrug(15, 10, 10); });
    TestirajIzuzetak<std::domain_error>([&]() { k.DodajKrug(15, 10, -5); });
    k.DodajKrug(-5, 0, 1);
    TestirajIzuzetak<std::range_error>([&]() { k.DodajKrug(100, 100, 1); });
    std::cout << k.DajKrug(1).r << std::endl;
    k.IspisiKrugove();
    std::cout << k.DajKrug(1).r << std::endl;
    k.DajKrug(1).r = 2;
    k.IspisiKrugove();
    TestirajIzuzetak<std::range_error>([&]() { k.DajKrug(5); });
    Krugovi k2 = k, k3 = std::move(k);
    k2.IspisiKrugove(); k3.IspisiKrugove();
    Krugovi k4(2);
    k4 = k2; k3 = std::move(k2);
    k3.IspisiKrugove(); k4.IspisiKrugove();
    return 0;
}

Krugovi Krugovi::operator=(const Krugovi& k)
{
    auto temp = krugovi;
    krugovi = new Krug[k.kapacitet]();
    delete[] temp;
    for(int i = 0; i < k.broj_krugova; i++){krugovi[i] = k.krugovi[i];};
    kapacitet = k.kapacitet; broj_krugova = k.broj_krugova;
    return *this;
}

Krugovi::Krugovi(Krugovi &&k)
{
    krugovi = k.krugovi;
    kapacitet = k.kapacitet;
    broj_krugova = k.broj_krugova;
    k.krugovi = nullptr;
}

Krugovi Krugovi::operator=(Krugovi &&k)
{
    if(&k != this)
    {
        delete[] krugovi;
        kapacitet = k.kapacitet; broj_krugova = k.broj_krugova;
        krugovi = k.krugovi; k.krugovi = nullptr;
    }
    return *this;
}

void Krugovi::DodajKrug(double x, double y, double r)
{
    if(broj_krugova == kapacitet) throw std::range_error("Popunjen kapacitet");
    if(r < 0) throw std::domain_error("Negativan poluprecnik");
    for(int i = 0; i < broj_krugova; i++)
    {
        double dx(krugovi[i].x - x), dy(krugovi[i].y - y);
        double d = sqrt(dx * dx + dy * dy);
        if(d < krugovi[i].r + r) throw std::logic_error("Krugovi se preklapaju");
    }
    krugovi[broj_krugova++] = Krug{x,y,r};
}

Krug& Krugovi::DajKrug(int i)
{
    if(i < 1 || i > broj_krugova) throw std::range_error("Neispravan indeks");
    return krugovi[i - 1];
}

const Krug& Krugovi::DajKrug(int i) const
{
    if(i < 1 || i > broj_krugova) throw std::range_error("Neispravan indeks");
    return krugovi[i - 1];
}

void Krugovi::IspisiKrugove() const
{
    Krug* zasort = new Krug[broj_krugova]();
    for(int i{}; i < broj_krugova; i++)
    {
        zasort[i] = krugovi[i];
    }
    std::sort(zasort, zasort + broj_krugova, [](const Krug& k1, const Krug& k2){
        return k1.r > k2.r;
    });
    for(int i{}; i < broj_krugova; i++)
        std::cout<<i + 1<<". [("<<zasort[i].x<<","<<
            zasort[i].y<<")"<<","<<zasort[i].r<<"]\n";
}