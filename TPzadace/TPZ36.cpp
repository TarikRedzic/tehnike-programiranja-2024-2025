#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <string>
#include <vector>

struct Dijete
{
    std::string ime;
    std::shared_ptr<Dijete> sljedeci;
}; 

std::vector<std::set<std::string>> Razvrstavanje(const std::vector<std::string>, int);
int duzina(const std::string);

int main()
{ 
    try
    {
        int n, k;
        std::cout<<"Unesite broj djece: ";
        std::cin>>n;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout<<"Unesite imena djece: \n";
        std::vector<std::string> v(n);
        for(auto &s: v) std::getline(std::cin, s);
        std::cout<<"Unesite broj timova: ";
        std::cin>>k;
        auto timovi = Razvrstavanje(v, k);
        for(int i{}; i < timovi.size(); i++)
        {
            std::cout<<"Tim "<<i + 1<<": ";
            int vel = timovi.at(i).size();
            for(auto str: timovi.at(i)) std::cout<<str<<(--vel > 0 ? ", ": "\n");
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "Izuzetak: "<< e.what() << '\n';
    }
    return 0;
}

std::vector<std::set<std::string>> Razvrstavanje(const std::vector<std::string> v, int k)
{
    int n = v.size();
    if(k < 1 || k > n) throw std::logic_error("Razvrstavanje nemoguce");

    std::vector<std::set<std::string>> timovi(k);
    std::shared_ptr<Dijete> imena{}, tren{};
    for(std::string s: v)
    {
        if (!imena) imena = (tren = std::make_shared<Dijete>());
        else tren = tren->sljedeci = std::make_shared<Dijete>();
        tren->ime = s;
    }
    tren->sljedeci = imena;
    std::shared_ptr<Dijete> prethodni{tren};
    tren = imena;
    imena = nullptr;
    for(int i{}, br_tim = 0; i < n - 1; i++)
    {
        int vel = duzina(tren->ime);
        if(br_tim < (n % k) ? timovi.at(br_tim).size() == (n / k) + 1
            : timovi.at(br_tim).size() == n / k) br_tim++;
        timovi.at(br_tim).insert(tren->ime);
        prethodni->sljedeci = tren->sljedeci;
        tren->sljedeci = nullptr;
        tren = prethodni->sljedeci;
        for(int j{1}; j < vel; j++) tren = (prethodni = tren)->sljedeci;
    }
    std::string finalni = tren->ime;
    tren->sljedeci = nullptr;
    timovi.at(k - 1).insert(finalni);
    return timovi;
}

int duzina(const std::string s)
{
    int l{};
    for(const char& c: s)
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
            l++;
    return l;
}