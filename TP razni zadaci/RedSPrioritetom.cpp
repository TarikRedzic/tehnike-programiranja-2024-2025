#include <algorithm>
#include <iostream>
#include <vector>


template <typename Tip> class RedSPrioritetom
{
    std::vector<Tip> red;
public:
    void Dodaj(Tip);
    bool DaLiJePrazan(){return !DajVelicinu();};
    const Tip& DajNajveci(){
        if(DaLiJePrazan()) throw std::logic_error("Red je prazan");
        return red.front();
    };
    int DajVelicinu(){return red.size();};
    void UkloniNajveci();
};

int main() {
    RedSPrioritetom<int> red;

    red.Dodaj(5);
    red.Dodaj(1);
    red.Dodaj(10);
    red.Dodaj(3);
    red.Dodaj(10);

    std::cout << "Velicina reda: " << red.DajVelicinu() << std::endl;
    std::cout << "Najveci element: " << red.DajNajveci() << std::endl;

    red.UkloniNajveci();
    std::cout << "Nakon uklanjanja najveceg, novi najveci: " << red.DajNajveci() << std::endl;

    while (!red.DaLiJePrazan()) {
        std::cout << "Uklanja se: " << red.DajNajveci() << std::endl;
        red.UkloniNajveci();
    }

    std::cout << "Red je sada prazan: " << (red.DaLiJePrazan() ? "DA" : "NE") << std::endl;

    return 0;
}



template <typename Tip>void RedSPrioritetom<Tip>::Dodaj(Tip novi)
{
    red.push_back(novi);
    std::sort(red.begin(), red.end(), [](auto x, auto y){return x > y;});
}

template <typename Tip> void RedSPrioritetom<Tip>::UkloniNajveci()
{
    std::copy(red.begin() + 1, red.end(), red.begin());
    if(DajVelicinu()) red.resize(DajVelicinu() - 1);
}