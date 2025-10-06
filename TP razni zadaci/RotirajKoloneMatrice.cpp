#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <queue>

std::queue<bool> RotirajKoloneMatrice(std::list<std::list<double>>&);

int main()
{
    int redova, kolona;
    std::cout<<"Unesite broj redova: ";
    std::cin>>redova;
    std::cout<<"Unesite broj kolona: ";
    std::cin>>kolona;
    std::list<std::list<double>> lista(redova, std::list<double>(kolona));
    std::cout<<"Unesite elemente matrice: ";
    for(auto p = lista.begin(); p != lista.end(); p++)
    {
        for(auto q = p->begin(); q != p->end(); q++)
        {
            double d;
            std::cin>>d;
            *q = d;
        } 
    }
    try
    {
        auto rez = RotirajKoloneMatrice(lista);
        std::cout<<"Transformirana matrica: \n";
        for(auto p = lista.begin(); p != lista.end(); p++)
        {
            for(auto q = p->begin(); q != p->end(); q++)
                std::cout<<std::setw(8)<<*q;
            endl(std::cout);
        }
        std::cout<<"Rezultirajuci red: ";
        for(; !rez.empty();)
        {
            std::cout<<std::boolalpha<<rez.front()<<" ";
            rez.pop();
        }
    }
    catch(std::domain_error e)
    {
        std::cout<<e.what()<<std::endl;
    }
    return 0;
}

std::queue<bool> RotirajKoloneMatrice(std::list<std::list<double>> &matrica)
{
    std::queue<bool> red;
    if(!std::distance(matrica.begin(), matrica.end())) throw std::domain_error("Parametar nema formu matrice");
    int vel = std::distance(matrica.begin()->begin(), matrica.begin()->end());
    for(auto p = matrica.begin(); p != matrica.end(); p++)
    {
        if(std::distance(p->begin(), p->end()) != vel) throw std::domain_error("Parametar nema formu matrice");
        int pro = 1;
        for(auto q = p->begin(); q != p->end(); q++)
        {
            if (*q < 0) pro *= -1;
        }
        if(pro < 0) red.push(false);
        else red.push(true);
        auto q = p->end();
        q--;
        std::rotate(p->begin(), q, p->end());
    }
    return red;
}