#include <iostream>
#include <vector>

enum class VrstaNiza{Aritmeticki, Geometrijski, Nespecificni};
const double E = 0.00001;
VrstaNiza OdrediVrstuNiza(std::vector<int> v);

int main()
{
    std::vector<int> v{32,56,98,168};
    try
    {
        VrstaNiza tip = OdrediVrstuNiza(v);
        switch(tip)
        {
            case VrstaNiza::Aritmeticki:
                std::cout<<"Niz je artimeticki!";
                break;
            case VrstaNiza::Geometrijski:
                std::cout<<"Niz je geometrijski!";
                break;
            default:
                std::cout<<"Niz je nespecifican!";
        }
    }
    catch(std::exception& e)
    {   
        std::cout<<e.what()<<std::endl;
    }
    return 0;
}

VrstaNiza OdrediVrstuNiza(std::vector<int> v)
{
    if(v.size() < 3) throw std::logic_error("Prekratak niz");
    bool da = true;
    for(int i{2}; i < v.size(); i++)
        if(v.at(1) - v.at(0) != v.at(i) - v.at(i - 1)){
            da = false; break;
        }
    if(da) return VrstaNiza::Aritmeticki;
    for(int i{2}; i < v.size(); i++)
        if(v.at(1) / v.at(0) < (v.at(i) / v.at(i - 1) - E) ||
            v.at(1) / v.at(0) > (v.at(i) / v.at(i - 1) + E)){
            return VrstaNiza::Nespecificni;
        }
    return VrstaNiza::Geometrijski;
} 