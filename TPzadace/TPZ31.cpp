#include <iostream>
#include <functional>
#include <map>
#include <cmath>
#include <vector>

std::function<double(double)> LagrangeovaInterpolacija(std::vector<std::pair<double, double>>);
std::function<double(double)> 
    LagrangeovaInterpolacija(std::function<double(double)>, double, double, double);
void ProvjeraCvorova(std::vector<std::pair<double, double>>&);
void ProvjeraParametara(const double xmin, const double xmax, const double dx){if(xmin > xmax || dx <= 0) throw std::domain_error("Nekorektni parametri");};

int main()
{
    int opcija;
    std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
    std::cin>>opcija;
    std::vector<std::pair<double, double>> cvorovi;
    if(opcija == 1)
    {
        int br_cvor;
        std::cout<<"Unesite broj cvorova: ";
        std::cin>>br_cvor;
        double a, b, xmin{}, xmax{};
        std::cout<<"Unesite cvorove kao parove x y: ";
        for(int i{}; i < br_cvor; i++) 
        {
            std::cin>>a>>b;
            if(i == 0) xmin = xmax = a;
            else if(a > xmax) xmax = a;
            else if(a < xmin) xmin = a;
            cvorovi.push_back(std::make_pair(a, b));
        }
        try
        {
            ProvjeraCvorova(cvorovi);
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << '\n';
            return 1;
        }
        do
        {
            double x;
            std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
            std::cin>>x;
            if(!std::cin) continue;
            auto f = LagrangeovaInterpolacija(cvorovi);
            std::cout<<"f("<<x<<") = "<<f(x);
            std::cout<<(x < xmin || x > xmax ? " [ekstrapolacija]\n" : "\n");
            
        }
        while(std::cin);    
    }
    else if(opcija == 2)
    {
        double xmin, xmax, dx;
        std::cout<<"Unesite krajeve intervala i korak: ";
        std::cin>>xmin>>xmax>>dx;
        try
        {
            ProvjeraParametara(xmin, xmax, dx);
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << '\n';
            return 1;
        }
        auto f = [](double x){return x*x + sin(x) + log(x + 1);};
        do
        {
            double x;
            std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
            std::cin>>x;
            if(!std::cin) continue;
            auto P = LagrangeovaInterpolacija(f, xmin, xmax, dx);
            std::cout<<"f("<<x<<") = "<<f(x)<<" P("<<x<<") = "<<P(x);
            std::cout<<(x < xmin || x > xmax ? " [ekstrapolacija]\n" : "\n");
        }
        while(std::cin);  
    }  
       
    return 0;
}

std::function<double(double)> LagrangeovaInterpolacija(std::vector<std::pair<double, double>> v)
{
    try
    {
        ProvjeraCvorova(v);
    }
    catch(...)
    {
        throw;
    }
    auto f = [v](double a){
        double l{};
        for(int i{}; i < v.size(); i++)
        {
            double p{1};
            for(int j{}; j < v.size(); j++)
            {
                if(i == j) continue;
                p *= ((a - v.at(j).first) / (v.at(i).first - v.at(j).first));
            }
            l += v.at(i).second * p;
        }
        return l;
    };
    return f;
}

std::function<double(double)> 
    LagrangeovaInterpolacija(std::function<double(double)> f, double xmin, double xmax, double dx)
{
    ProvjeraParametara(xmin, xmax, dx);
    std::vector<std::pair<double, double>> cvorovi;
    for(int i = 0; xmin + i*dx < xmax + 0.0001; i++)
    {
        double in = xmin + i*dx > xmax &&
            xmin + i*dx < xmax + 0.0001 ? xmax: xmin + i*dx;
        cvorovi.push_back(std::make_pair(in, f(in)));
    }
    auto P = LagrangeovaInterpolacija(cvorovi);
    return P;
}

void ProvjeraCvorova(std::vector<std::pair<double, double>>& v)
{
    for(int i = 0; i < v.size(); i++)
        for(int j = i + 1; j < v.size(); j++)
            if(v.at(i).first == v.at(j).first) throw std::domain_error("Neispravni cvorovi");
}