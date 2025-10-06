//TP 2024/2025: Zadaća 1, Zadatak 2
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

std::vector<std::vector<double>> UsrednjavajuciFilter(std::vector<std::vector<double>>, int);

int main ()
{
    int r, k;
    std::cout<<"Unesite broj redova i kolona matrice: ";
    std::cin>>r>>k;
    std::cout<<"Unesite elemente matrice:\n";
    std::vector<std::vector<double>> v(r, std::vector<double>(k));
    for(int i{}; i < r; i++)
        for(int j{}; j < k; j++)
            std::cin>>v.at(i).at(j);
    int n;
    std::cout<<"Unesite red filtriranja: ";
    std::cin>>n;
    std::vector<std::vector<double>> novi(r, std::vector<double>(k));
    try
    {
        novi = UsrednjavajuciFilter(v, n);
    }
    catch(std::domain_error)
    {
        std::cout<<"GRESKA: Neispravan red filtriranja!";
        return 1;
    }

    std::cout<<"Matrica nakon filtriranja:\n";
    for(int i{}; i < r; i++)
    {
        for(int j{}; j < novi.at(i).size(); j++)
            std::cout<<std::fixed<<std::setprecision(2)<<std::setw(7)<<novi.at(i).at(j);
        std::cout<<std::endl;
    }
	return 0;
}

std::vector<std::vector<double>> UsrednjavajuciFilter(std::vector<std::vector<double>> v, int n)
{
    if (n < 0) throw std::domain_error("Neispravan red filtriranja");
    std::vector<std::vector<double>> novi = v;
    for(int i{}; i < v.size(); i++)
        for(int j{}; j < v.at(i).size(); j++)
        {
            double suma {}; 
            int clanova{};
            for(int k{i - n}; k <= i + n; k++)
                for(int l{j - n}; l <= j + n; l++)
                    if((k >= 0) && (l >= 0) && (k < v.size()) && (l < v.at(k).size()))
                    {
                        suma += v.at(k).at(l);
                        clanova++;
                    }
            novi.at(i).at(j) = suma / clanova;
        }
    return novi;
}