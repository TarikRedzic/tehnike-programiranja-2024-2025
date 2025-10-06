#include <iostream>

enum Dani {Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja};
std::ostream& operator<<(std::ostream& tok, const Dani& d)
{
    const char* lista[7] = {"Ponedjeljak", "Utorak", 
        "Srijeda", "Cetvrtak", "Petak", "Subota", "Nedjelja"};
    tok << lista[d];
    return tok;
}

Dani& operator++(Dani &d)
{
    d = Dani((int(d) + 1) % 7);
    return d;
}

Dani operator++(Dani &d, int)
{
    Dani n = d; ++d;
    return n;
}

int main()
{
    for(Dani d = Ponedjeljak; d <= Petak; d++) std::cout << d << std::endl;
    std::cout << "-----------------\n";
    for(Dani d = Ponedjeljak;; d++) {
    std::cout << d << std::endl;
    if(d == Nedjelja) break;
    }
    return 0;
}


