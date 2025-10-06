#include <algorithm>
#include <iostream>
#include <vector>

template <typename IT1, typename IT2>
    void KumulativnaSuma(IT1 p1, IT1 k1, IT2 p2);

int main()
{
    std::cout<<"Koliko ima brojeva: ";
    int n;
    std::cin>>n;
    std::vector<int> v(n), rez(n);
    std::cout<<"Unesite brojeve: ";
    for(int i = 0; i < n; i++) std::cin>>v.at(i);
    KumulativnaSuma(v.begin(), v.end(), rez.begin());
    std::cout<<"Kumulativna suma: ";
    for(const int& i: rez){std::cout<<i<<" ";};
    return 0;
}

template <typename IT1, typename IT2>
    void KumulativnaSuma(IT1 p1, IT1 k1, IT2 p2)
{
    int vel = std::distance(p1, k1);
    for(int i = 0, suma = 0; i < vel; i++, suma = 0)
    {
        auto t = p1;
        for(int j = 0; j <= i; j++, t++) suma += *t;
        *p2++ = suma;
    }
}