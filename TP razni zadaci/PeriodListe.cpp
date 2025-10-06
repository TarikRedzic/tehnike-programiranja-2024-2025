#include <iostream>
#include <list>

int PeriodListe(std::list<double> lista)
{
    int T{};
    for(auto p = lista.begin(); p != lista.end(); p++)
    {
        auto q = p;
        for(q++; q != lista.end(); q++)
        {
            if(*p == *q)
            {
                auto r = p;
                
            }
        }
    }
}

int main()
{

}

