#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>
#include <list>

template <typename Kontejner, typename FunTip> Kontejner Mapiraj
    (Kontejner c, FunTip f)
{
    Kontejner novi;
    for(auto p = c.begin(); p != c.end(); p++)
    {
        int n = *p;
        int rez = f(*p);
        novi.insert(novi.end(), rez);
    } 
    return novi;
}

int main()
{
    std::vector<int> skup;
    int n;
    std::cout<<"Unesite broj elemenata skupa: ";
    std::cin>>n;
    std::cout<<"Unesite elemente: ";
    for(int i{}; i < n; i++) 
    {
        int m;
        std::cin>>m;
        skup.insert(skup.end(), m);
    }
    auto novi = Mapiraj(skup, [](int x){
        int suma{};
        while(x != 0)
        {
            suma += x % 10;
            x /= 10;
        }
        return suma;
    });
    std::cout<<"Novi skup: ";
    for(auto p = novi.begin(); p != novi.end(); p++) std::cout<<*p<<" ";
}