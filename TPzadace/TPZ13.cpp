//TP 2024/2025: Zadaća 1, Zadatak 3
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

enum class Smjer {LijevaSpiralna, DesnaSpiralna, NijeSpiralna};

std::vector <std::vector<int>>KreirajSpiralnuMatricu(int, int, int, Smjer);
int Najsiriclan(std::vector<std::vector<int>>);
enum Smjer DaLiJeSpiralnaMatrica(std::vector<std::vector<int>>);
int ZakovanoOduzimanje(int, int);

int main ()
{
    int redova, kolona;
    std::cout<<"Unesite broj redova i kolona matrice: ";
    std::cin>>redova>>kolona;
    std::cout<<"Unesite pocetnu vrijednost: ";
    int k;
    std::cin>>k;
    char c;
    std::cout<<"Unesite L za lijevu, a D za desnu spiralnu matricu: ";
    std::cin>>c;
    std::vector<std::vector<int>> v;
    switch (std::toupper(c)) 
    {
        case 'D':
            v = KreirajSpiralnuMatricu(redova, kolona, k, Smjer::DesnaSpiralna);
            break;
        case 'L':
            v = KreirajSpiralnuMatricu(redova, kolona, k, Smjer::LijevaSpiralna);
            break;
        default:
            v = KreirajSpiralnuMatricu(redova, kolona, k, Smjer::NijeSpiralna);
            return 1;
    }
    if(toupper(c) == 'D')
        std::cout<<"Kreirana desna spiralna matrica:\n";
    else if(toupper(c) == 'L')
        std::cout<<"Kreirana lijeva spiralna matrica:\n";
    if(v.size())
    {
        int najs = Najsiriclan(v);
        for(std::vector<int> niz: v)
        {
            std::cout<<" ";
            for(int x: niz)
                std::cout<<std::setw(najs)<<x<<" ";
            std::cout<<"\n";
        }
        /*if(DaLiJeSpiralnaMatrica(v) == Smjer::DesnaSpiralna)
            std::cout<<"Desna Spiralna!";
        else if(DaLiJeSpiralnaMatrica(v) == Smjer::LijevaSpiralna)
            std::cout<<"Lijeva Spiralna!";
        else
            std::cout<<"Nije Spiralna!";*/
    }  
	return 0;
}

std::vector<std::vector<int>>KreirajSpiralnuMatricu(int redova, int kolona, int k, Smjer dir)
{
    std::vector<std::vector<int>> v(redova, std::vector<int>(kolona));
    int M = redova, N = kolona, kraj = k + redova * kolona - 1;
    int sr = 0, sk = 0, tr = 0, tk = 0;
    if((redova <= 0) || (kolona <= 0) || (dir == Smjer::NijeSpiralna))
        return std::vector<std::vector<int>>{};
    switch (dir) 
    {
        case Smjer::DesnaSpiralna:
            while((sr < M) && (sk < N))
            {
                for(tr = sr, tk = sk; tk < N; tk++)
                    v.at(tr).at(tk) = k++;
                for(tk = N - 1, tr = sr + 1; tr < M; tr++)
                    v.at(tr).at(tk) = k++;
                if((sk == N - 1) || (sr == M - 1) || (k > kraj))
                    break;
                for(tr = M - 1, tk = N - 2; tk >= sr; tk--)
                    v.at(tr).at(tk) = k++;
                for(tk = sk, tr = M - 2; tr > sr; tr--)
                    v.at(tr).at(tk) = k++;
                sr++, sk++, M--, N--;
            }
            break;
        case Smjer::LijevaSpiralna:
            while((sr < M) && (sk < N))
            {
                for(tr = sr, tk = sk; tr < M; tr++)
                    v.at(tr).at(tk) = k++;
                for(tk = sk + 1, tr = M - 1; tk < N; tk++)
                    v.at(tr).at(tk) = k++;
                if((sk == N - 1) || (sr == M - 1) || (k > kraj))
                    break;
                for(tk = N - 1, tr = M - 2; tr >= sr; tr--)
                    v.at(tr).at(tk) = k++;
                for(tk = N - 2, tr = sr; tk > sk; tk--)
                    v.at(tr).at(tk) = k++;
                sr++, sk++, M--, N--;  
            }
            break;
        default:
            return std::vector<std::vector<int>>{};
    }
    return v;
}

int Najsiriclan(std::vector<std::vector<int>> v)
{
    int najmanji = v.at(0).at(0);
    int najveci = najmanji;
    for(std::vector<int> niz: v)
        for(int x: niz)
        {
            if (x > najveci)
                najveci = x;
        }
    int brmanji = 0, brveci = 0;
    for(; najveci != 0; brveci++)
        najveci /= 10;
    for(; najmanji != 0; brmanji++)
        najmanji /= 10;
    return brveci > brmanji ? brveci : (brmanji < 0 ? brmanji + 1: brmanji);
}


enum Smjer DaLiJeSpiralnaMatrica(std::vector<std::vector<int>> v)
{
    for(int i{1}; i < v.size(); i++)
        if (v.at(0).size() != v.at(i).size())
            return Smjer::NijeSpiralna;
    if(v.size() == 1 || v.at(0).size() == 1)
        return Smjer::DesnaSpiralna;
    if(v.at(0).at(0) == v.at(0).at(1) - 1) //provjera desne spiralne
    {
        int M = v.size(), N = v.at(0).size();
        //int kraj = v.at(0).at(0) + M * N - 1;
        int sr = 0, sk = 0, tr = 0, tk = 0;
        while((sr < M) && (sk + 1 < N))
            {
                for(tr = sr, tk = sk; tk < N; tk++)
                    if(ZakovanoOduzimanje(v.at(tr).at(tk), v.at(tr).at(sk)) != tk - sk)
                        return Smjer::NijeSpiralna;
                for(tk = N - 1, tr = sr + 1; tr < M; tr++)
                    if(ZakovanoOduzimanje(v.at(tr).at(tk), v.at(sr).at(tk)) != tr - sr)
                        return Smjer::NijeSpiralna;
                if((sk == N - 1) || (sr == M - 1))
                    break;
                for(tr = M - 1, tk = N - 2; tk >= sr; tk--)
                    if(ZakovanoOduzimanje(v.at(tr).at(tk), v.at(tr).at(N - 1)) != (N - 1) - tk)
                        return Smjer::NijeSpiralna;
                for(tk = sk, tr = M - 2; tr > sr; tr--)
                    if(ZakovanoOduzimanje(v.at(tr).at(tk), v.at(M - 1).at(tk)) != (M - 1) - tr)
                        return Smjer::NijeSpiralna;
                sr++, sk += 0, M--, N--;
            }
            return Smjer::DesnaSpiralna;
    } 
    else if(v.at(0).at(0) == v.at(1).at(0) - 1) //provjera lijeve spiralne
    {
        int M = v.size(), N = v.at(0).size();
        //int kraj = v.at(0).at(0) + M * N - 1;
        int sr = 0, sk = 0, tr = 0, tk = 0;
        while((sr < M) && (sk < N))
        {
            for(tr = sr, tk = sk; tr < M; tr++)
                if(ZakovanoOduzimanje(v.at(tr).at(tk), v.at(sr).at(tk)) != tr - sr)
                    return Smjer::NijeSpiralna;
            for(tk = sk + 1, tr = M - 1; tk < N; tk++)
                if(ZakovanoOduzimanje(v.at(tr).at(tk), v.at(tr).at(sk)) != tk - sk)
                    return Smjer::NijeSpiralna;
            if((sk == N - 1) || (sr == M - 1))
                break;
            for(tk = N - 1, tr = M - 2; tr >= sr; tr--)
                if(ZakovanoOduzimanje(v.at(tr).at(tk), v.at(M - 1).at(tk)) != (M - 1) - tr)
                    return Smjer::NijeSpiralna;
            for(tk = N - 2, tr = sr; tk > sk; tk--)
                if(ZakovanoOduzimanje(v.at(tr).at(tk), v.at(tr).at(N - 1)) != (N - 1) - tk)
                    return Smjer::NijeSpiralna;
            sr++, sk++, M--, N--;  
        }
        return Smjer::LijevaSpiralna;
    }
    else return Smjer::NijeSpiralna;
}

int ZakovanoOduzimanje(int x, int y)
{
    if(y < 0 && x < std::numeric_limits<int>::min() + (-y)) return std::numeric_limits<int>::min();
    if(y > 0 && x > std::numeric_limits<int>::max() + y) return std::numeric_limits<int>::max();
    return x - y;
}