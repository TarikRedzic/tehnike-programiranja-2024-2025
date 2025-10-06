#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <vector>

template <typename Tip> class Skup
{
    std::vector<Tip> skup;
public:
    Skup() = default;
    Skup(std::initializer_list<Tip> lista);
    int Velicina() const{return skup.size();};
    Skup& Dodaj(Tip element);
    Skup& Izbrisi(Tip element);
    bool ImaLiGa(Tip element);
    void Ispisi();
};
int main()
{
    Skup<int> s{2, 2, 5, 8, 8, 3};
    s.Ispisi();
    s.Dodaj(1).Dodaj(9).Izbrisi(3).Dodaj(11);
    s.Ispisi();
    s.Dodaj(3).Ispisi();
    return 0;
}

template <typename Tip> Skup<Tip>::Skup(std::initializer_list<Tip> lista)
    : skup()
{
    for(auto p = lista.begin(); p != lista.end(); p++)
    {
        if(!ImaLiGa(*p)) skup.push_back(*p);
    }
    std::sort(skup.begin(), skup.end());
}

template <typename Tip> Skup<Tip>& Skup<Tip>::Dodaj(Tip element)
{
    if(!ImaLiGa(element))
    {
        skup.push_back(element);
        std::sort(skup.begin(), skup.end());
    }
    return *this;
}

template <typename Tip> bool Skup<Tip>::ImaLiGa(Tip element)
{
    for(int j = 0; j < skup.size(); j++)
        if(skup.at(j) == element) return true;
    return false;
}

template <typename Tip> Skup<Tip>& Skup<Tip>::Izbrisi(Tip element)
{
    auto it = std::remove(skup.begin(), skup.end(), element);
    skup.erase(it, skup.end());
    return *this;
}

template <typename Tip> void Skup<Tip>::Ispisi()
{
    std::cout<<"{";
    for(int i = 0; i < skup.size(); i++)
    {
        std::cout<<skup.at(i)<<(i == skup.size() - 1 ? "}\n" : ", ");
    }
}