#include <iostream>
#include <stack>

template <typename Tip, typename FunTip> auto TransformiraniStek
    (std::stack<Tip> stek, FunTip f) -> std::stack<decltype(f(stek.top()))>
{
    
    std::stack<decltype(f(stek.top()))> pomocni;
    if(stek.size() == 1)
    {
        pomocni.push(f(stek.top()));
        return pomocni;
    }  
    auto proba = f(stek.top());
    stek.pop();
    pomocni = TransformiraniStek(stek, f);
    pomocni.push(proba);
    return pomocni;
}

int main()
{
    int vel;
    std::cout<<"Unesite velicinu steka: ";
    std::cin>>vel;
    std::cout<<"Unesite elemente: ";
    std::stack<int> stek;
    for(int i = 0; i < vel; i++)
    {
        int n;
        std::cin>>n;
        stek.push(n);
    }
    auto novi = TransformiraniStek(stek, [](int x){
        return 1/double(x);
    });
    std::cout<<"Stek reciprocnih vrijednosti: ";
    while(!novi.empty())
    {
        std::cout<<novi.top()<<" ";
        novi.pop();
    }
    return 0;
}