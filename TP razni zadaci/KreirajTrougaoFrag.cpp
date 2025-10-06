#include <iostream>

int** KreirajTrougao(int n);

int main()
{
    std::cout<<"Koliko zelite redova: ";
    int n; 
    std::cin>>n;
    int** trougao = KreirajTrougao(n);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 0; j < 2 * i - 1; j++) 
            std::cout<<trougao[i - 1][j]<<" ";
        endl(std::cout);        
    }
    return 0;
}

int** KreirajTrougao(int n)
{
    int** trougao = new int*[n]();
    try
    {
        for(int i = 1; i <= n; i++) 
        {
            trougao[i - 1] = new int[(2 * i)- 1]{};
            for(int j = 0; j < i; j++)
            {
                trougao[i - 1][j] = i - j;
                trougao[i - 1][((2 * i)- 2) - j] = i - j;
            }
        }
    }
    catch(...)
    {
        for(int i = 0; i < n; i++)delete[] trougao[i];
        delete[] trougao;
    }
    return trougao;
}