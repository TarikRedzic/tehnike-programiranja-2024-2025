#include <iostream>
#include <new>

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
    delete[] trougao[0];
    delete[] trougao;
    return 0;
}

int** KreirajTrougao(int n)
{
    if(n <= 0) throw std::domain_error("Broj redova mora biti pozitivan");
    int** trougao = new int*[n]();
    try
    {
        trougao[0] = new int[n * n]();
        trougao[0][0] = 1;
        for(int i = 1; i < n; i++) {
            trougao[i] = trougao[0] + (i * i);
            for(int j = 0; j <= i; j++){
                trougao[i][j] = i - j + 1;
                trougao[i][(2 * (i + 1) - 2) - j] = i - j + 1;
            }  
        }
    }
    catch(std::exception& e)
    {
        delete[] trougao[0];
        delete[] trougao;
        throw;
    }
    return trougao;
}