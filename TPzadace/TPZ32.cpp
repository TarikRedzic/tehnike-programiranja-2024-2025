#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

typedef std::map<std::string, std::vector<std::string>> Knjiga;

bool SlovoBroj(char);
std::map<std::string, std::set<std::tuple<std::string, int, int>>>
    KreirajIndeksPojmova(const Knjiga&);
std::string Uvecaj(std::string&);
std::set<std::tuple<std::string, int, int>> PretraziIndeksPojmova(std::string, const std::map<std::string, std::set<std::tuple<std::string, int, int>>>&);
void IspisiIndeksPojmova(std::map<std::string, std::set<std::tuple<std::string, int, int>>>&);

int main()
{
    Knjiga k;
    do
    {
        std::pair<std::string, std::vector<std::string>> par{};
        std::string poglavlje{};
        std::cout<<"Unesite naziv poglavlja: ";
        std::getline(std::cin, poglavlje);
        if(poglavlje.size() == 0) break;
        par.first = poglavlje;
        for(int i{1}; true; i++)
        {
            std::string stranica{};
            std::cout<<"Unesite sadrzaj stranice "<<i<<": ";
            std::getline(std::cin, stranica);
            if(stranica.size() == 0) break;
            par.second.push_back(stranica);
        }
        k.insert(par);
    } 
    while (true);
    endl(std::cout);
    auto indeks = KreirajIndeksPojmova(k);
    std::cout<<"Kreirani indeks pojmova:\n";
    IspisiIndeksPojmova(indeks);
    endl(std::cout);
    do
    {
        std::string rijec{};
        std::cout<<"Unesite rijec: ";
        std::getline(std::cin, rijec);
        if(rijec.size() == 0) break;
        try
        {
            auto s = PretraziIndeksPojmova(rijec, indeks);
            if(s.size() != 0)
            {
                std::cout<<"Rijec nadjena na pozicijama: ";
                for(auto t: s)
                    std::cout<<std::get<0>(t)<<"/"<<std::get<1>(t)<<"/"<<std::get<2>(t)<<" ";
                endl(std::cout);
            }  
            else
                std::cout<<"Rijec nije nadjena!\n";
        }
        catch(std::domain_error e)
        {
            std::cout<<"Neispravna rijec!"<<std::endl;
        } 
    }
    while(true);
    std::cout<<"Dovidjenja!";
    return 0;
}

std::map<std::string, std::set<std::tuple<std::string, int, int>>>
    KreirajIndeksPojmova(const Knjiga &k)
{
    std::map<std::string, std::set<std::tuple<std::string, int, int>>> indeks;
    for(auto poglavlje: k)
    {
        int str = 1;
        for(auto stranica: poglavlje.second)
        {
            char pret{' '};
            std::string temp{};
            int ind = 1;
            for(int i{}; i < stranica.size(); i++)
            {
                char c = stranica.at(i);
                if(!SlovoBroj(c))
                {
                    if(SlovoBroj(pret))
                    {
                        auto p = indeks.find(Uvecaj(temp));
                        if(p == indeks.end()) indeks[Uvecaj(temp)].insert({poglavlje.first, str, ind});
                        else p->second.insert({poglavlje.first, str, ind});
                        temp.resize(0);
                    }
                    pret = c;
                }
                else
                {
                    if(!SlovoBroj(pret)) ind = i + 1;
                    temp.push_back(c);
                    pret = c;
                }
                if(i == stranica.size() - 1)
                {
                    auto p = indeks.find(Uvecaj(temp));
                    if(p == indeks.end()) indeks[Uvecaj(temp)].insert({poglavlje.first, str, ind});
                    else p->second.insert({poglavlje.first, str, ind});
                }
            }
            str++;
        }
    }
    return indeks;
}

bool SlovoBroj(char c)
{
    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
        return true;
    return false;
}

std::string Uvecaj(std::string& s)
{
    std::string novi;
    for(char c: s){novi.push_back(toupper(c));};
    return novi;
}

void IspisiIndeksPojmova(std::map<std::string, std::set<std::tuple<std::string, int, int>>>& indeks)
{
    for(auto p: indeks)
    {
        std::cout<<p.first<<": ";
        int vel = p.second.size();
        for(auto skup: p.second)
        {
            std::cout<<std::get<0>(skup)<<"/"<<std::get<1>(skup)<<"/"<<std::get<2>(skup);
            std::cout<<(vel == 1 ? "\n" : ", ");
            vel--;
        }
    }
}

std::set<std::tuple<std::string, int, int>>
    PretraziIndeksPojmova(std::string s, const std::map<std::string, std::set<std::tuple<std::string, int, int>>> &indeks)
{
    //ovakva implementacija je odradjena jer imam problem sa stimanjem verzije c++ na VSC
    //pa sam morao i komentarisat ali hocu da se vidi kako bih uradio
    s = Uvecaj(s);
        for(const char &c: s){if(!SlovoBroj(c)) throw std::domain_error("Neispravna rijec");};
    /*if (__cplusplus == 201703L)
        for(auto par: indeks) if(auto p = indeks.find(s); p != indeks.end()) return p->second;
    else*/
    for(auto par: indeks) 
    {
        auto p = indeks.find(s);
        if(p != indeks.end()) return p->second;
    }
    return {};
}