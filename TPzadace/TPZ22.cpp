//TP 2024/2025: Zadaća 2, Zadatak 2
#include <iostream>
#include <cmath>
#include <limits>
#include <climits>

void RastavaSlobodnaOdKvadrata(int, int&, int&);
int main()
{
    int n, p = 0, q = 1;
    std::cout<<"Unesi broj: "; //napomena da je u postavci "Unesite broj: "
    std::cin>>n;
    try
    {
        RastavaSlobodnaOdKvadrata(n, p, q);
        std::cout<<n<<" = "<<p<<"*"<<q<<"^2";
    }
    catch(int a)
    {
        std::cout<<"Broj "<<n<<" je slobodan od kvadrata.\n";
    }

	return 0;
}

void RastavaSlobodnaOdKvadrata(int n, int &p, int &q)
{
    p = 0, q = 1;
    if(!n) return;
    bool neg = false;
    if(n < 0)
    {
        n = -n;
        neg = true;
    }
    if(int(std::sqrt(n)) == std::sqrt(n))
    {
        neg ? p = -1 : p = 1;
        q = std::sqrt(n);
        return;
    }
    for(int i = 4; i <= std::abs(n / 2); i += (2 * std::sqrt(i)) + 1)
    {
        if(n % i == 0)
        {
            p = n / i;
            q = std::sqrt(i);
        }
    }
    if (q == 1) p = n;
    if(neg) p = -p;
}