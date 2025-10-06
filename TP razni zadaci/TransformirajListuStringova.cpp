#include <algorithm>
#include <iostream>
#include <list>

bool AlNum(const char& c);

int main()
{
    std::string s;
    std::list<std::string> lista;
    std::cout<<"Unesite:\n";
    for(int i = 0; i < 10; i++){
        std::getline(std::cin, s); lista.push_back(s);
    }
    std::transform(lista.begin(), lista.end(), lista.begin(), [](const std::string& s){
        int br{};
        for(int i = 0; i < s.size(); i++){
            if(!AlNum(s.at(i))) br++;
        }
        if(br > 7) return std::string();
        return s;
    });
    std::cout<<"Ispis:\n";
    std::for_each(lista.begin(), lista.end(), [](const std::string& s){
        if(s.size()) std::cout<<s<<std::endl;
    });
    return 0;
}

bool AlNum(const char& c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9')); 
}

