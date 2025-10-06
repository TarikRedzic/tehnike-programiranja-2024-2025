#include <algorithm>
#include <iostream>
#include <vector>

int** SortirajPoStepenuSumeCifara(std::vector<int>, int);

int main()
{
    try
    {
        std::vector<int> v(5);
        std::cout<<"Unesite 5 elemenata vektora: ";
        for(int i = 0; i < 5; i++) std::cin>>v.at(i);
        auto A = SortirajPoStepenuSumeCifara(v, 3);
        std::cout<<"Sortirana matrica: \n";
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 5; j++)
                std::cout<<A[i][j]<<" ";
            endl(std::cout);
        }
        delete[] A[0];
        delete[] A;
    }
    catch(...)
    {
        std::cout<<"Neuspjesna alokacija uvodnog vektora\n";
    }

    return 0;
}

int** SortirajPoStepenuSumeCifara(std::vector<int> v, int n)
{
    if(n <= 0) throw std::range_error("Pogresan broj redova matrice");
    int m = v.size();
    int** matrica = nullptr;
    try
    {
        matrica = new int*[n]();
    }
    catch(...)
    {
        throw std::range_error("Problemi s alokacijom");
    }
    try
    {
        matrica[0] = new int[m*n]();
        for(int i = 1; i < n; i++) matrica[i] = matrica[i - 1] + m;
        std::cout<<"Pocetak sortiranja:\n";
        
        for(int i{}; i < n; i++)
        {
            std::vector<int> back = v;
            std::sort(back.begin(), back.end(), [i](int x, int y){
                bool istina = x < y;
                int sumx{}, sumy{};
                while(x != 0)
                {
                    int zc{1};
                    for(int j = 0; j < i; j++) zc *= x % 10;
                    sumx += zc;
                    x /= 10;
                }
                while(y != 0)
                {
                    int zc{1};
                    for(int j = 0; j < i; j++) zc *= y % 10;
                    sumy += zc;
                    y /= 10;
                }
                if(sumx == sumy) return istina;
                return sumx > sumy;
            });
            //std::copy(back.begin(), back.end(), matrica[i]);
            for(int j = 0; j < back.size(); j++) *(matrica[i]+j) = back[j];
        }
    }
    catch(...)
    {
        delete[] matrica[0];
        delete[] matrica;
        throw std::range_error("Problemi s alokacijom");
    }
    
    return matrica;
}