//TP 2024/2025: Zadaća 2, Zadatak 5
#include <array>
#include <cmath>
#include <deque>
#include <forward_list>
#include <iomanip>
#include <iostream>
#include <list>
#include <stdexcept>
#include <type_traits>
#include <vector>

template <typename IterTip1, typename IterTip2, typename FunTip>
    auto KreirajFunkcijskuTablicu(IterTip1 p1, IterTip1 p2, IterTip2 q1, FunTip f)
{
    int vel = std::distance(p1, p2);
    int dimenzija = (vel * (vel + 1)) / 2;
    using DecTip = std::remove_reference_t<decltype(f(*p1, *q1))>;
    DecTip** matrica{};
    try
    {
        matrica = new DecTip*[vel]();
    }
    catch(std::bad_alloc)
    {
        throw std::range_error("Nema dovoljno memorije");
    }
    try
    {
        *matrica = new DecTip[dimenzija];
    }
    catch(std::bad_alloc)
    {
        delete[] matrica;
        throw std::range_error("Nema dovoljno memorije");
    }
    {
        auto temp = matrica;
        int i = 1;
        for(auto p = *matrica; i < vel; i++)
        {
            for(int j{}; j < i; j++, p++);
            *++matrica = p;
        }
        matrica = temp;
    }

    DecTip* P = *matrica;
    IterTip1 M = p1;
    for(int i = 0; i < vel; i++, M++)
    {
        IterTip2 N = q1;
        for(int j = 0; j <= i; j++, N++)
        {
            try
            {
                *P++ = f(*M, *N);
            }
            catch(...)
            {
                delete[] *matrica;
                delete[] matrica;
                throw std::runtime_error("Neocekivani problemi pri racunanju");
            }
        }
    }
    return matrica;
}

int main()
{
    int n;
    std::cout<<"Duzina sekvenci: ";
    std::cin>>n;
    std::vector<double> v(n);
    std::cout<<"Elementi prve sekvence: ";
    for(int i = 0; i < n; i++)
    {
        std::cin>>v.at(i);
    }
    std::cout<<"Elementi druge sekvence: ";
    std::deque<double> d(n);
    //for(int &a: d){std::cin>>a;}
    for(int i = 0; i < n; i++)
    {
        std::cin>>d.at(i);
    }

    try
    {
       auto matrica = KreirajFunkcijskuTablicu(v.begin(), v.end(), d.begin(), [](auto x, auto y)
        {
            return x * y;
        });
        std::cout<<"Tablica mnozenja: \n";

        auto q = *matrica;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j <= i; j++)
                std::cout<<*q++<<" ";
            endl(std::cout);
        }
        delete[] *matrica;
        delete[] matrica;
    }
    catch(std::range_error e)
    {
        std::cout<<e.what()<<std::endl;
        return 1;
    }
    catch(std::runtime_error e)
    {
        std::cout<<e.what()<<std::endl;
        return 1;
    }
    return 0;
}