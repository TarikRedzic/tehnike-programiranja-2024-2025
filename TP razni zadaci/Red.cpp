#include <algorithm>
#include <iostream>
#include <vector>

template <typename Tip> class Red
{
    std::vector<Tip> red;
public:
    bool DaLiJePrazan()const {return !DajVelicinu();};
    int DajVelicinu()const{return red.size();};
    void UkloniSaCela(){
        if(DajVelicinu() == 0) throw std::domain_error("Prazan red");
        red.resize(DajVelicinu() - 1);
    }
    const Tip& DajCelo() const{return red.at(DajVelicinu() - 1);};
    Tip& DajCelo(){return red.at(DajVelicinu() - 1);};
    const Tip& DajZacelje() const{return red.at(0);};
    Tip& DajZacelje(){return red.at(0);};
    void DodajNaZacelje(Tip element);
};

int main() 
{
    Red<int> r;

    std::cout << "Test: DaLiJePrazan na pocetku: ";
    std::cout << (r.DaLiJePrazan() ? "OK\n" : "Greska\n");

    std::cout << "Test: DodajNaZacelje i DajCelo: ";
    r.DodajNaZacelje(10);
    r.DodajNaZacelje(20);
    r.DodajNaZacelje(30);
    if (r.DajCelo() == 10) std::cout << "OK\n";
    else std::cout << "Greska\n";

    std::cout << "Test: DajZacelje: ";
    if (r.DajZacelje() == 30) std::cout << "OK\n";
    else std::cout << "Greska\n";

    std::cout << "Test: DajVelicinu: ";
    if (r.DajVelicinu() == 3) std::cout << "OK\n";
    else std::cout << "Greska\n";

    std::cout << "Test: UkloniSaCela i provjera novog cela: ";
    r.UkloniSaCela();
    if (r.DajCelo() == 20 && r.DajVelicinu() == 2) std::cout << "OK\n";
    else std::cout << "Greska\n";

    std::cout << "Test: DodajNaZacelje nakon uklanjanja: ";
    r.DodajNaZacelje(40);
    if (r.DajZacelje() == 40 && r.DajVelicinu() == 3) std::cout << "OK\n";
    else std::cout << "Greska\n";

    std::cout << "Test: Praznjenje reda: ";
    while (!r.DaLiJePrazan()) r.UkloniSaCela();
    std::cout << (r.DaLiJePrazan() ? "OK\n" : "Greska\n");

    std::cout << "Test: Bacanje izuzetka pri DajCelo na praznom redu: ";
    try {
        r.DajCelo();
        std::cout << "Greska (nije bacen izuzetak)\n";
    } catch (...) {
        std::cout << "OK\n";
    }

    std::cout << "Test: Bacanje izuzetka pri DajZacelje na praznom redu: ";
    try {
        r.DajZacelje();
        std::cout << "Greska (nije bacen izuzetak)\n";
    } catch (...) {
        std::cout << "OK\n";
    }

    std::cout << "Test: Bacanje izuzetka pri UkloniSaCela na praznom redu: ";
    try {
        r.UkloniSaCela();
        std::cout << "Greska (nije bacen izuzetak)\n";
    } catch (...) {
        std::cout << "OK\n";
    }

    std::cout << "Test: Const pristup DajCelo i DajZacelje: ";
    r.DodajNaZacelje(55);
    r.DodajNaZacelje(66);
    const Red<int> cr = r;
    if (cr.DajCelo() == 55 && cr.DajZacelje() == 66) std::cout << "OK\n";
    else std::cout << "Greska\n";

    return 0;
}


template <typename Tip> void Red<Tip>::DodajNaZacelje(Tip element)
{
    red.resize(DajVelicinu() + 1);
    std::copy(red.begin(), red.end(), red.begin() + 1);
    red.at(0) = element;
}
