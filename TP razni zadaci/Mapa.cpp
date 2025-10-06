#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <map>
#include <vector>

template <typename T> class Mapa
{
    std::vector<std::pair<std::string, T>> mapa;
public:
    Mapa() = default;
    Mapa(std::initializer_list<std::pair<std::string, T>> lista);
    int DajVelicinu() const {return mapa.size();};
    Mapa& DodajPar(std::pair<std::string, T>);
    void IzbrisiElement(const std::string&);
    const T& NadjiElement(const std::string&) const;
    void IspisiMapu() const;
}; 

int main() {
    Mapa<int> m {
        {"jabuka", 5},
        {"banana", 3},
        {"narandza", 7}
    };

    m.IspisiMapu();
    m.DodajPar({"banana", 10});
    m.DodajPar({"kruska", 4});
    std::cout << "\nNakon izmjena:\n";
    m.IspisiMapu();
    m.DodajPar({"banana", 11});
    
    try {
        std::cout << "\nVrijednost za 'banana': " << m.NadjiElement("banana") << std::endl;
        std::cout << "Vrijednost za 'sljiva': " << m.NadjiElement("sljiva") << std::endl; // should throw
    } catch (const std::domain_error& e) {
        std::cout << "Greska: " << e.what() << std::endl;
    }

    m.IzbrisiElement("kruska");
    std::cout << "\nNakon brisanja 'kruska':\n";
    m.IspisiMapu();

    return 0;
}


template <typename T> Mapa<T>::Mapa(std::initializer_list<std::pair<std::string, T>> lista)
{
    for(auto p = lista.begin(); p != lista.end(); p++)
    {
        DodajPar(*p);
    }
}

template <typename T>  Mapa<T>& Mapa<T>::DodajPar(std::pair<std::string, T> par)
{
    bool bio = false;
    for(int i{}; i < DajVelicinu(); i++)
    {
        if(par.first == mapa[i].first) 
        {
            mapa[i].second = par.second;
            bio = true;
        }
    }
    if(!bio) mapa.push_back(par);
    std::sort(mapa.begin(), mapa.end());
}

template <typename T> const T& Mapa<T>::NadjiElement(const std::string& s) const
{
    for(auto &par: mapa) if(par.first == s) return par.second;
    throw std::domain_error("Nije pronadjen element");
}

template <typename T> void Mapa<T>::IzbrisiElement(const std::string& s)
{
    for(auto par = mapa.begin(); par != mapa.end(); par++) 
        if(par->first == s) mapa.erase(par);
}

template <typename T> void Mapa<T>::IspisiMapu() const
{
    for(auto& p: mapa) std::cout<<p.first<<"/"<<p.second<<std::endl;
}