//TP 2024/2025: Zadaća 2, Zadatak 4
#include <algorithm>
#include <iostream>
#include <vector>

template <typename Tip> bool Kriterij(const std::vector<Tip> &x, const std::vector<Tip> &y)
{
    if(x.size() == 0) return true;
    else if(y.size() == 0) return false;
    else return x.size() == y.size() ?
      (x.at(0) < y.at(0) ? true : false) :
      (x.size() < y.size() ? true : false);
}
template <typename Tip> void SortirajPoDuziniRedova(std::vector<std::vector<Tip>> &v)
{
    //int redova = v.size();
    std::sort(v.begin(), v.end(), Kriterij<Tip>);
}

int main()
{
    int n;
    std::vector<int> temp;
    std::vector<std::vector<int>> v;
    std::cout<<"Unesite elemente (* za kraj reda, * na pocetku reda za kraj unosa):\n";
    while(true)
    {
        int br{};
        while(std::cin>>n)
        {
            try
            {
                temp.push_back(n);
                br++;
            }
            catch(...)
            {
                std::cout<<"Greska pri alokaciji!";
                return 1;
            }
        }
        std::cin.clear();
        std::cin.ignore(10000, '*');
        if(!br) break;
        try
        {
            v.push_back(temp);
            temp.resize(0);
        }
        catch(...)
        {
            std::cout<<"Greska pri alokaciji!";
            return 1;
        }
    }
    SortirajPoDuziniRedova(v);
    std::cout<<"Matrica nakon sortiranja:\n";
    for(int i{}; i < v.size(); i++)
    {
        for(int j{}; j < v.at(i).size(); j++)
        {
            std::cout<<v.at(i).at(j)<<" ";
        }
        std::cout<<std::endl;
    }
    return 0;
}

