#include <functional>
#include <iostream>
#include <vector>

std::function<double(double)> RacionalnaFunkcija(std::vector<double>, std::vector<double>);
template <typename Kontejner> double Polinom(Kontejner &v, double &x)
{
    double rezultat{};
    for(int i = 0; i < v.size(); i++)
    {
        if(i == 0) 
        {
            rezultat += v[i];
            continue;
        }
        int temp{1};
        for(int j = 0; j < i; j++) temp *= x;
        rezultat += temp * v[i];
    }
    return rezultat;
}

int main()
{
    std::vector<double> p{1, 3, 0, 2}, q{0, 2, 0, -4, 1};
    std::cout<<RacionalnaFunkcija(p, q)(10);
    return 0;
}

std::function<double(double)> RacionalnaFunkcija(std::vector<double> p, std::vector<double> q)
{
    return [p, q](double x){
        return Polinom(p, x)/Polinom(q, x);
    };
}