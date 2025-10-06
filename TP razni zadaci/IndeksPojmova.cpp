#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <set>
#include <vector>

std::map<std::string, std::set<std::pair<int, int>>> KreirajIndeksPojmova(const std::vector<std::string>&);
bool Numal(char c);
std::string Smanji(std::string&);
void IspisiIndeksPojmova(std::map<std::string, std::set<std::pair<int, int>>> mapa);
std::set<std::pair<int, int>> PretraziIndeksPojmova(std::string, std::map<std::string, std::set<std::pair<int, int>>>);

int main()
{
    int vel;
    std::cout<<"Unesite broj stranica: ";
    std::cin>>vel;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::vector<std::string> v(vel);
    for(int i = 0; i < vel; i++)
    {
        std::cout<<"Unesite sadrzaj stranice "<<i+1<<": ";
        std::getline(std::cin, v.at(i));
    }
    endl(std::cout);
    auto mapa = KreirajIndeksPojmova(v);
    IspisiIndeksPojmova(mapa);
    endl(std::cout);
    while(true)
    {
        std::string unos;
        std::cout<<"Unesite rijec: ";
        std::getline(std::cin, unos);
        if(unos == ".") break;
        try
        {
            std::set<std::pair<int, int>> pret = PretraziIndeksPojmova(unos, mapa);
            for(auto p: pret)
            {
                std::cout<<p.first<<"/"<<p.second<<" ";
            }
            endl(std::cout);
        }
        catch(const std::logic_error)
        {
            std::cerr << "Unesena rijec nije nadjena!" << '\n';
        }
    }
    return 0;
}

std::map<std::string, std::set<std::pair<int, int>>> KreirajIndeksPojmova(const std::vector<std::string> &v)
{
    std::map<std::string, std::set<std::pair<int, int>>> mapa;
    for(int i{}; i <v.size(); i++)
    {
        std::string s = v.at(i), temp;
        char pret{' '};
        int ind = 0;
        for(int j{}; j < s.size(); j++)
        {
            char c = s.at(j);
            if(!Numal(c))
            {
                if(Numal(pret))
                {
                    auto p = mapa.find(Smanji(temp));
                    if(p == mapa.end()) mapa[Smanji(temp)].insert({i + 1, ind});
                    else p->second.insert({i + 1, ind});
                    temp.resize(0);
                }
                pret = c;
            }
            else
            {
                if(!Numal(pret)) ind = j;
                temp.push_back(c);
                pret = c;
            }
            if(j == s.size() - 1)
            {
                auto p = mapa.find(Smanji(temp));
                if(p == mapa.end()) mapa[Smanji(temp)].insert({i + 1, ind});
                else p->second.insert({i + 1, ind});
            }
        }
    }
    return mapa;
}

bool Numal(char c)
{
    if((c >= 'A' && c <= 'Z') ||
     (c >= 'a' && c <= 'z') ||
     (c >= '0' && c <= '9')) return true;
    return false;
}

std::string Smanji(std::string &s)
{
    std::string novi;
    for(char c: s){novi.push_back(tolower(c));};
    return novi;
}

void IspisiIndeksPojmova(std::map<std::string, std::set<std::pair<int, int>>> mapa)
{
    std::cout<<"Kreirani indeks pojmova: \n";
    for(std::pair<std::string, std::set<std::pair<int, int>>> p: mapa)
    {
        std::cout<<p.first<<": ";
        int i = p.second.size();
        for(const std::pair<int, int> m: p.second)
        {
            std::cout<<m.first<<"/"<<m.second;
            if(i-- > 1) std::cout<<", ";
            else std::cout<<"\n";
        }
    }
}

std::set<std::pair<int, int>> PretraziIndeksPojmova(std::string s, std::map<std::string, std::set<std::pair<int, int>>> mapa)
{
    auto p = mapa.find(s);
    if(p == mapa.end()) throw std::logic_error("Pojam nije nadjen");
    else return p->second;
}