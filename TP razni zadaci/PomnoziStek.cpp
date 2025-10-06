#include <iostream>
#include <stack>

template <typename Tip> void PomnoziStek(std::stack<Tip> &hrpa, Tip n)
{
    std::stack<Tip> pomocni;
    while(!hrpa.empty())
    {
        pomocni.push(hrpa.top());
        hrpa.pop();
    }
    while(!pomocni.empty())
    {
        hrpa.push(pomocni.top() * n);
        pomocni.pop();
    }
}

int main()
{
    int vel;
    std::cout<<"Unesite velicinu stacka: ";
    std::cin>>vel;
    std::stack<double> stek;
    std::cout<<"Unesite elemente: ";
    for(int i = 0; i < vel; i++)
    {
        double n;
        std::cin>>n;
        stek.push(n);
    }
    double d;
    std::cout<<"Unesite mnozilac: ";
    std::cin>>d;
    PomnoziStek(stek, d);
    std::cout<<"Stek nakon mnozenja (od vrha ka dnu): ";
    while(!stek.empty())
    {
        std::cout<<stek.top()<<" ";
        stek.pop();
    }
    return 0;
}