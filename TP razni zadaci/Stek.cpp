#include <iostream>

template <typename Tip> class Stek
{
    int kapacitet, velicina;
    Tip* stek;
public:
    Stek(): kapacitet(10), velicina(0), stek(new Tip[10]()){};
    ~Stek(){delete[] stek;};
    Stek(const Stek &s);
    Stek(Stek &&s);
    Stek& operator=(const Stek &s);
    Stek& operator=(Stek &&s);
    int DajVelicinu()const{return velicina;};
    bool DaLiJePrazan()const{return DajVelicinu() == 0;};
    void DodajNaVrh(Tip novi);
    const Tip& DajVrh() const{
        if(DaLiJePrazan()) throw std::logic_error("Prazan stek");
        return stek[DajVelicinu() - 1];
    };
    Tip& DajVrh(){
        if(DaLiJePrazan()) throw std::logic_error("Prazan stek");
        return stek[DajVelicinu() - 1];
    };
    void SkiniSVrha();
};
int main() {
    Stek<int> s;

    std::cout << "Test: DaLiJePrazan na pocetku: ";
    std::cout << (s.DaLiJePrazan() ? "OK\n" : "Greska\n");

    std::cout << "Test: DodajNaVrh i DajVrh: ";
    s.DodajNaVrh(10);
    s.DodajNaVrh(20);
    s.DodajNaVrh(30);
    if (s.DajVrh() == 30) std::cout << "OK\n";
    else std::cout << "Greska\n";

    std::cout << "Test: DajVelicinu: ";
    if (s.DajVelicinu() == 3) std::cout << "OK\n";
    else std::cout << "Greska\n";

    std::cout << "Test: SkiniSVrha i novi vrh: ";
    s.SkiniSVrha();
    if (s.DajVrh() == 20 && s.DajVelicinu() == 2) std::cout << "OK\n";
    else std::cout << "Greska\n";

    std::cout << "Test: Puno dodavanja (test realokacije na +50%): ";
    for (int i = 0; i < 100; i++)
        s.DodajNaVrh(i);
    if (s.DajVelicinu() == 102 && s.DajVrh() == 99) std::cout << "OK\n";
    else std::cout << "Greska\n";

    std::cout << "Test: Puno uklanjanja (test realokacije na -50%): ";
    for (int i = 0; i < 95; i++)
        s.SkiniSVrha();
    if (s.DajVelicinu() == 7 && s.DajVrh() == 4) std::cout << "OK\n";
    else std::cout << "Greska\n";

    std::cout << "Test: Praznjenje steka: ";
    while (!s.DaLiJePrazan()) s.SkiniSVrha();
    std::cout << (s.DaLiJePrazan() ? "OK\n" : "Greska\n");

    std::cout << "Test: Bacanje izuzetka pri DajVrh na praznom steku: ";
    try {
        s.DajVrh();
        std::cout << "Greska (nije bacen izuzetak)\n";
    } catch (...) {
        std::cout << "OK\n";
    }

    std::cout << "Test: Bacanje izuzetka pri SkiniSVrha na praznom steku: ";
    try {
        s.SkiniSVrha();
        std::cout << "Greska (nije bacen izuzetak)\n";
    } catch (...) {
        std::cout << "OK\n";
    }

    std::cout << "Test: Const pristup DajVrh: ";
    s.DodajNaVrh(42);
    const Stek<int> cs = s;
    if (cs.DajVrh() == 42) std::cout << "OK\n";
    else std::cout << "Greska\n";

    return 0;
}


template <typename Tip> Stek<Tip>::Stek(const Stek &s):
    kapacitet(s.kapacitet), velicina(s.velicina)
{
    stek = new Tip[kapacitet]();
    for(int i{}; i < velicina; i++) stek[i] = s.stek[i];
}

template <typename Tip> Stek<Tip>::Stek(Stek &&s):
    kapacitet(s.kapacitet), velicina(s.velicina)
{
    stek = s.stek; s.stek = nullptr;
}

template <typename Tip> Stek<Tip>& Stek<Tip>:: operator=(const Stek &s)
{
    auto temp = new Tip[s.kapacitet]();
    for(int i{}; i < velicina; i++) temp[i] = s.stek[i];
    kapacitet = s.kapacitet;  velicina = s.velicina;
    delete[] stek; stek = temp;
    return *this;
}

template <typename Tip> Stek<Tip>& Stek<Tip>:: operator=(Stek &&s)
{
    stek = s.stek; s.stek = nullptr;
    kapacitet = s.kapacitet; velicina = s.velicina;
    return *this;
}

template <typename Tip>void Stek<Tip>::DodajNaVrh(Tip novi)
{
    if(velicina == kapacitet)
    {
        auto temp = new Tip[kapacitet + kapacitet/2]();
        for(int i{}; i < velicina; i++) temp[i] = stek[i];
        temp[velicina++] = novi; kapacitet += kapacitet / 2;
        delete[] stek; stek = temp;
    } 
    else stek[velicina++] = novi;
}

template <typename Tip>void Stek<Tip>::SkiniSVrha()
{
    if(DaLiJePrazan()) throw std::logic_error("Prazan stek");
    if(velicina < (kapacitet * 3)/10 && kapacitet >= 10)
    {
        auto temp = new Tip[kapacitet / 2];
        for(int i = 0; i < velicina - 1; i++) temp[i] = stek[i];
        velicina--; kapacitet /= 2;
        delete[] stek; stek = temp;
    }
    else velicina--;
}