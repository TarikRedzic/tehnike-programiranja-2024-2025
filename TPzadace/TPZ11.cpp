//TP 2024/2025: Zadaća 1, Zadatak 1
#include <cmath>
#include <iostream>
#include <vector>

int CiklickaPermutacija(std::vector<int>, std::vector<int>);

int main ()
{
    int n;
    std::vector<int> v1;
    std::cout<<"Prva sekvenca: ";
    while(std::cin>>n)
        v1.push_back(n);
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::vector<int> v2;
    std::cout<<"Druga sekvenca: ";
    while(std::cin>>n)
        v2.push_back(n);
    n = CiklickaPermutacija(v1, v2);
    if (n == -1)
        std::cout<<"\nDruga sekvenca nije ciklicka permutacija prve.";
    else
        std::cout<<"\nDruga sekvenca je ciklicka permutacija prve s pomakom "<<n<<".";
	
    return 0;
}

int CiklickaPermutacija(std::vector<int> v1, std::vector<int> v2)
{
    if(v1.size() != v2.size())
        return -1;
    int a = v2.size(), najm = -1;
    for(int i{}, brojac{}; i < a; i++, brojac = 0)
        if(v1.at(0) == v2.at(i))
        {
            for(int j{1}; j < a; j++)
                if(v1.at(j) != v2.at((i + j) % a))
                    break;
                else
                    brojac++;
            if(brojac == a - 1 && (najm == -1 || najm > i))
                najm = i;
        }
    for(int i{a - 1}, brojac{}; i >= 0; i--, brojac = 0)
        if(v1.at(0) == v2.at(i))
        {
            for(int j{1}; j < a; j++)
                if(v1.at(j) != v2.at((i + j) % a))
                    break;
                else
                    brojac++;
            if(brojac == a - 1 && (najm == -1 || najm > a - i))
                najm = a - i;
        }
    return najm;
}