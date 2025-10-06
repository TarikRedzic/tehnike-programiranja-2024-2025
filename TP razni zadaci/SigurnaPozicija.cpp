#include <iostream>
#include <list>

int SigurnaPozicija(int, int);

int main()
{
    try
    {
        std::cout<<"Pogubljenje ce izbjeci osoba broj "<<SigurnaPozicija(14, 3)<<std::endl;
    }
    catch(...)
    {
        std::cout<<"Ovo nema smisla!";
    }
    return 0;
}

int SigurnaPozicija(int n, int m)
{
    if(m <= 0 || n <= 0) throw "Besmisleno";
    std::list<int> lista;
    for(int i = 1; i <= n; i++) lista.push_back(i);
    auto pok = lista.begin();
    for(int br = 1; lista.size() != 1; br++)
    {
        if(pok == lista.end()) pok = lista.begin();
        if(br % m == 0)
        {
            auto temp = pok;
            pok++;
            lista.erase(temp);
        }
        else pok++;
    }
    return *lista.begin();
}