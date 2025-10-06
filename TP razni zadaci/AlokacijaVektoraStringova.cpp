#include <algorithm>
#include <iostream>
#include <vector>

char** KreirajBlok(std::vector<std::string> v);

int main()
{
    int n;
    std::string s;
    std::cout<<"Unesite broj stringova: ";
    std::cin>>n;
    std::vector<std::string> v(n);
    std::cin.ignore(10000, '\n');
    std::cout<<"Unesite "<<n<<" stringa:\n";
    for(int i = 0; i < n; i++) {
        std::getline(std::cin, s); v.at(i) = s;
    }
    auto blok = KreirajBlok(v);
    std::cout<<"Ispis:\n";
    for(int i = 0; i < n; i++) std::cout<<blok[i]<<std::endl;
    delete[] blok[0];
    delete[] blok;
    return 0;
}

char** KreirajBlok(std::vector<std::string> v)
{
    char** blok = new char*[v.size()]();
    try
    {
        int vel{};
        for(int i = 0; i < v.size(); i++) vel += v.at(i).size() + 1;
        auto temp = new char[vel]();
        for(int i = 0, j = 0; j < vel; i++){
            std::copy(v.at(i).begin(), v.at(i).end(), temp + j);
            blok[i] = temp + j;
            j += v.at(i).size() + 1;
        }
        temp = nullptr;
    }
    catch(...)
    {
        delete[] blok[0];
        delete[] blok;
        throw;
    }
    return blok;
}