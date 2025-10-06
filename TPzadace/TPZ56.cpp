#include <iostream>
#include <functional>
#include <fstream>

template <typename TipElemenata>
void SortirajBinarnuDatoteku(const char ime_datoteke[],
    std::function<bool(TipElemenata, TipElemenata)> kriterij
        = std::less<TipElemenata>())
{
    const int vel = sizeof(TipElemenata);
    std::fstream fajl(ime_datoteke, 
        std::ios::out | std::ios::in | std::ios::binary);
    if(!fajl) throw std::logic_error("Datoteka ne postoji");
    fajl.seekg(0, std::ios::end);
    int br_elemenata = fajl.tellg() / vel;
    fajl.seekg(0, std::ios::beg);
    for(int i{}; i < br_elemenata; i++)
    {
        for(int j{i + 1}; j < br_elemenata; j++)
        {
            TipElemenata x, y;
            fajl.seekg(i * vel).read(reinterpret_cast<char*>(&x), vel);
            fajl.seekg(j * vel).read(reinterpret_cast<char*>(&y), vel);
            if(!kriterij(x, y))
            {
                fajl.seekp(i * vel).write(reinterpret_cast<char*>(&y), vel);
                fajl.seekp(j * vel).write(reinterpret_cast<char*>(&x), vel);
            }
        }
        if(!fajl) std::logic_error("Problemi u pristupu datoteci");
    }
}


int main()
{
    std::ofstream izlazni_tok("BROJEVI.DAT", std::ios::binary);
    for(int i = 0; i < 10; i++) {
        int broj;
        std::cin>>broj;
        izlazni_tok.write(reinterpret_cast<char*>(&broj), sizeof broj);
    }
    izlazni_tok.close();
    SortirajBinarnuDatoteku<int>("BROJEVI.DAT");
    std::cout<<"CITANJE!!\n";
    std::ifstream ulazni_tok("BROJEVI.DAT", std::ios::binary);
    int broj;
    while(ulazni_tok.read(reinterpret_cast<char*>(&broj), sizeof broj))
        std::cout << broj << std::endl;
    return 0;
}
