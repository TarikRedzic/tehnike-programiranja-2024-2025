#include <iostream>
#include <memory>

int SigurnaPozicija(int, int);

struct Osoba
    {
        int redni_broj;
        std::shared_ptr<Osoba> sljedeci;
    };

int main()
{
    std::cout<<"Pogubljenje ce izbjeci osoba broj "<<SigurnaPozicija(49, 9)<<std::endl;
    return 0;
}

int SigurnaPozicija(int n, int m)
{
    std::shared_ptr<Osoba> pocetak{}, tren{};
    for(int i{1}; i <= n; i++)
    {
        if(!pocetak) pocetak = tren = std::make_shared<Osoba>();
        else tren = tren->sljedeci = std::make_shared<Osoba>();
        tren->redni_broj = i;
    }
    tren->sljedeci = pocetak;
    std::shared_ptr<Osoba> prethodni = tren;
    tren = pocetak;
    pocetak = nullptr;
    while(n != 1)
    {
        for(int i = 1; i < m; i++)
        {
            prethodni = tren;
            tren = tren->sljedeci;
        }
        prethodni->sljedeci = tren->sljedeci;
        tren = tren->sljedeci;
        n--;
    }
    int finalni = tren->redni_broj;
    tren->sljedeci = nullptr;
    return finalni;
}