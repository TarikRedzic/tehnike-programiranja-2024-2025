#include <iostream>
#include <string>

template <typename Tip> struct Cvor
{
    Tip element;
    Cvor* veza = nullptr;
};

template <typename TipElemenata>
Cvor<TipElemenata> *KreirajPovezanuListu(const TipElemenata &zavrsni);
template <typename TipElemenata>
int BrojElemenata(Cvor<TipElemenata> *pocetak);
template <typename TipElemenata>
TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak);
template <typename TipElemenata>
int BrojVecihOd(Cvor<TipElemenata> *pocetak, const TipElemenata &prag);
template <typename TipElemenata>
void UnistiListu(Cvor<TipElemenata> *pocetak);

int main()
{
    auto lista = KreirajPovezanuListu(double(0));
    int vel = BrojElemenata(lista);
    int suma = SumaElemenata(lista);
    int veci_od_ar = BrojVecihOd(lista, double(suma)/vel);
    std::cout<<"U slijedu ima "<<vel<<" elemenata sa sumom "<<suma<<std::endl;
    std::cout<<"U slijedu ima "<<veci_od_ar<<" brojeva vecih od njihove aritmeticke sredine";
    UnistiListu(lista);

    return 0;
}

template <typename TipElemenata> Cvor<TipElemenata> *KreirajPovezanuListu(const TipElemenata &zavrsni)
{
    std::cout<<"Unesite povezanu listu, "<<zavrsni<<" za kraj: \n";
    TipElemenata unos;
    Cvor<TipElemenata> *pocetak{}, *temp, *tren;
    do
    { 
        std::cin>>unos;
        temp = new Cvor<TipElemenata>;
        temp->element = unos;
        temp->veza = nullptr;
        if(pocetak == nullptr) pocetak = tren = temp;
        else tren = tren->veza = temp;
    } 
    while (unos != zavrsni);
    return pocetak;
}

template <typename TipElemenata>
int BrojElemenata(Cvor<TipElemenata> *pocetak)
{
    int vel = 0;
    while(pocetak->veza != nullptr)
    {
        pocetak = pocetak->veza;
        vel++;
    }
    return vel;
}

template <typename TipElemenata>
TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak)
{
    TipElemenata suma{};
    while(pocetak->veza != nullptr)
    {
        suma += pocetak->element;
        pocetak = pocetak->veza;
    }
    return suma;
}

template <typename TipElemenata>
int BrojVecihOd(Cvor<TipElemenata> *pocetak, const TipElemenata &prag)
{
    int brv{};
    while(pocetak->veza != nullptr)
    {
        if(pocetak->element > prag) brv++;
        pocetak = pocetak->veza;
    }
    return brv;
}

template <typename TipElemenata>
void UnistiListu(Cvor<TipElemenata> *pocetak)
{
    
    while(pocetak->veza != nullptr)
    {
        auto zaunistenje = pocetak;
        pocetak = pocetak->veza;
        delete zaunistenje;
    }
}