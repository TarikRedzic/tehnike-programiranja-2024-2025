#include <iostream>
#include <functional>

std::function<int(int)> IteriranaFunkcija(std::function<int(int)>, int);

int main()
{
    auto f = [](int x){return x + 1;};
    //auto g = IteriranaFunkcija(f, 5);
    std::cout<<IteriranaFunkcija(f, 5)(6);
    return 0;
}

std::function<int(int)> IteriranaFunkcija(std::function<int(int)> f, int n)
{
    return [f, n](int x){
        int rez = x;
        for(int i = 0; i < n; i++) rez = f(rez);
        return rez;
    };
}