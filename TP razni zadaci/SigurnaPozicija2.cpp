#include <iostream>

int SigurnaPozicija(int, int);

struct Osoba
{
    int redni_broj;
    Osoba* sljedeci;
};

int main()
{
    try
    {
        std::cout<<"Pogubljenje ce izbjeci osoba broj "<<SigurnaPozicija(41, 3)<<std::endl;
    }
    catch(...)
    {
        std::cout<<"Ovo nema smisla!";
    }
    return 0;
}

int SigurnaPozicija(int n, int m)
{
    Osoba* lista{}, *tren{};
    for(int i{1}; i <= n; i++)
    {
        if(!lista) lista = (tren = new Osoba{i, nullptr});
        else tren = tren->sljedeci = new Osoba{i, nullptr};
    }
    tren->sljedeci = lista;
    Osoba* prethodni{tren};
    tren = lista;
    lista = nullptr;
    while(n != 1)
    {
        for(int i = 1; i < m; i++)
        {
            prethodni = tren;
            tren = tren->sljedeci;
        }
        prethodni->sljedeci = tren->sljedeci;
        delete tren;
        tren = prethodni->sljedeci;
        n--;
    }
    int finalni = tren->redni_broj;
    delete tren;
    return finalni;
}