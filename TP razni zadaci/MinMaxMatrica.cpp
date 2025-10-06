#include <complex>
#include <iostream>
#include <vector>

template <typename Tip>
    void MinMaxMatrica(std::vector<std::vector<Tip>> v,
        std::complex<Tip>& min, std::complex<Tip>& max);

int main()
{
    std::vector<std::vector<int>> v{{2,2,5},{8,8,3}};
    std::complex<int> min, max;
    MinMaxMatrica(v, min, max);
    std::cout<<"Najveci element je na poziciji "<<max.real()<<" "<<max.imag()<<std::endl;
    std::cout<<"Najmanji element je na poziciji "<<min.real()<<" "<<min.imag()<<std::endl;
    return 0;
}

template <typename Tip>
    void MinMaxMatrica(std::vector<std::vector<Tip>> v,
        std::complex<Tip>& min, std::complex<Tip>& max)
{
    int mini{}, maxi{}, minj{}, maxj{};
    Tip najmanji = v.at(0).at(0), najveci = v.at(0).at(0);
    for(int i = 0; i < v.size(); i++)
    {
        for(int j = 0; j < v.size(); j++)
        {
            if(v.at(i).at(j) < najmanji){
                mini = i; minj = j;
            }
            if(v.at(i).at(j) > najveci){
                maxi = i; maxj = j;
            }
        }
    }
    min = {mini, minj}; max = {maxi, maxj};
}
//obrisi ; naknadno, postavljeno da se usuti kompajler