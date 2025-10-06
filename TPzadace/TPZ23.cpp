#include <iomanip>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

template <typename IterTip1, typename IterTip2>
    auto KroneckerovaSuma(const IterTip1 &v1, const IterTip2 &v2)
{
    using DodTip = std::remove_reference_t<decltype(*std::begin(v1) + *std::begin(v2))>;
    std::vector<std::vector<DodTip>> matrica;
    if((std::begin(v1) == std::end(v1)) || (std::begin(v2) == std::end(v2)))
        return matrica;
    int vel1 = std::distance(std::begin(v1), std::end(v1));
    int vel2 = std::distance(std::begin(v2), std::end(v2));
    try
    {
        matrica.resize(vel1);
    }
    catch(...)
    {
        throw "Greska pri prvoj alokaciji matrice";
    }
    try
    {
        for(std::vector<DodTip> &v: matrica) v.resize(vel2);
    }
    catch(...)
    {
        throw "Greska pri drugoj alokaciji matrice";
    }
    int i{}, j{};
    for(auto p = std::begin(v1); i < vel1; i++, p++, j = 0)
    {
        for(auto q = std::begin(v2); j < vel2; j++, q++)
        {
            matrica.at(i).at(j) = *p + *q;
        }
    }
    return matrica;
}

template <typename ElTip>int NajduziElement(const std::vector<std::vector<ElTip>> &v)
{
    int maxel{};
    for(int i{}; i < v.size(); i++)
        for(int j{}; j < v.at(i).size(); j++)
            if (std::to_string(v.at(i).at(j)).size() > maxel)
                maxel = std::to_string(v.at(i).at(j)).size();
    return maxel;
}

int NajduziElement(const std::vector<std::vector<std::string>> &v);

int main()
{
    int vel1, vel2;
    std::cout<<"Unesite broj elemenata prve sekvence: ";
    std::cin>>vel1;
    std::vector<std::string>v1;
    try
    {
        v1.resize(vel1);
    }
    catch(...)
    {
        std::cout<<"Greska pri alokaciji prvog vektora!";
        return 1;
    }
    std::cout<<"Unesite elemente prve sekvence: ";
    for(int i{}; i < vel1; i++)
    {
        std::cin>>v1.at(i);
        std::cin.clear();
    }

    std::cout<<"Unesite broj elemenata drugog vektora: ";
    std::cin>>vel2;
    std::vector<std::string>v2;
    try
    {
        v2.resize(vel2);
    }
    catch(...)
    {
        std::cout<<"Greska pri alokaciji drugog vektora!";
        return 1;
    }
    std::cout<<"Unesite elemente druge sekvence: ";
    for(int i{}; i < vel2; i++)
    {
        std::cin>>v2.at(i);
        std::cin.clear();
    }
    try
    {
        auto matrica = KroneckerovaSuma(v1, v2);
        if(!matrica.size())
        {
            std::cout<<std::endl;
            return 2;
        }
        int najduzi = NajduziElement(matrica);
        endl(std::cout);
        for(int i{}; i < vel1; i++)
        {
            for(int j{}; j < vel2; j++)
            {
                std::cout<<std::left<<std::setw(najduzi + 1)<<matrica.at(i).at(j);
            }
            std::cout<<std::endl;
        }
    }
    catch(const char* c)
    {
        std::cout<<*c;
    }
    catch(...)
    {
        std::cout<<"Neuspjela alokacija matrice sa sumom";
        return 3;
    }
    return 0;
}


int NajduziElement(const std::vector<std::vector<std::string>> &v)
{
    int maxel{};
    for(int i{}; i < v.size(); i++)
        for(int j{}; j < v.at(i).size(); j++)
            if (v.at(i).at(j).size() > maxel)
                maxel = v.at(i).at(j).size();
    return maxel;
}