#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>

int main()
{
    int n;
    std::cout<<"Unesite broj elemenata: ";
    std::cin>>n;
    std::cout<<"Unesite elemente: ";
    std::vector<double> v(n);
    for(double& x: v) std::cin>>x;
    std::transform(v.begin(), v.end(), v.begin(),
        std::bind(std::divides<double>(), 1, std::placeholders::_1));
    for(const double& x: v) std::cout<<x<<" ";
    endl(std::cout);
    return 0;
}
