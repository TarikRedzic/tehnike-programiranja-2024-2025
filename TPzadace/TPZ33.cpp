#include <iostream>
#include <iomanip>
#include <new>
#include <stdexcept>
#include <vector>

template <typename TipElemenata> struct Matrica
{
    char ime_matrice; // Koristi se samo u funkciji "UnesiMatricu"
    int br_redova, br_kolona;
    TipElemenata ** elementi = nullptr; // VEOMA BITNA INICIJALIZACIJA!!!
};
template <typename TipElemenata> void UnistiMatricu(Matrica <TipElemenata> & mat)
{
    if(!mat.elementi) return;
    for(int i = 0; i < mat.br_redova; i++) delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi = nullptr;
}
template <typename TipElemenata> Matrica <TipElemenata> StvoriMatricu(int br_redova, int br_kolona, char ime = 0)
{
    Matrica <TipElemenata> mat;
    mat.br_redova = br_redova;
    mat.br_kolona = br_kolona;
    mat.ime_matrice = ime;
    mat.elementi = new TipElemenata * [br_redova]{};
    try
    {
        for(int i = 0; i <br_redova; i++) mat.elementi[i] = new TipElemenata[br_kolona];
    }
    catch (...)
    {
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}
template <typename TipElemenata> void UnesiMatricu(Matrica <TipElemenata> & mat)
{
    for(int i = 0; i < mat.br_redova; i++)
        for(int j = 0; j < mat.br_kolona; j++)
        {
            std::cout << mat.ime_matrice <<"(" <<i + 1 <<"," <<j + 1 <<") = ";
            std::cin>> mat.elementi[i][j];
        }
}
template <typename TipElemenata> void IspisiMatricu(const Matrica <TipElemenata> & mat, int sirina_ispisa,
     int preciznost = 6, bool treba_brisati = false)
{
    for(int i = 0; i < mat.br_redova; i++)
    {
        for(int j = 0; j < mat.br_kolona; j++) std::cout <<std::setw(sirina_ispisa)
            <<std::setprecision(preciznost) <<mat.elementi[i][j];
        std::cout <<std::endl;
    }
    if(treba_brisati)
    {
        auto del = mat;
        UnistiMatricu(del);
    }
}
template <typename TipElemenata> Matrica <TipElemenata> Jedinicna(const int br_redova, const int br_kolona, char ime = 'I')
{
    try
    {
        auto I = StvoriMatricu<TipElemenata>(br_redova, br_kolona, ime);
        Nuliraj(I);
        for(int j = 0; j < br_kolona; j++) I.elementi[j][j] = 1;
        return I;
    }
    catch(...)
    {
        throw;
    }
}
template <typename TipElemenata> Matrica <TipElemenata> ZbirMatrica(const Matrica <TipElemenata> & m1,
    const Matrica <TipElemenata> & m2)
{
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
    try
    {
        auto m3 = StvoriMatricu <TipElemenata> (m1.br_redova, m1.br_kolona);
        for(int i = 0; i < m1.br_redova; i++)
            for(int j = 0; j < m1.br_kolona; j++) m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
        return m3;
    }
    catch(...)
    {
       throw;
    }
    
}

template <typename TipElemenata> Matrica <TipElemenata> ProduktMatrica(const Matrica <TipElemenata> & m1,
    const Matrica <TipElemenata> & m2)
{
    if(m1.br_kolona != m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    Matrica <TipElemenata> m3{};
    try
    {
        m3 = StvoriMatricu <TipElemenata> (m1.br_redova, m2.br_kolona);
        Nuliraj(m3);
        for(int i{}; i < m1.br_redova; i++)
        {
            TipElemenata element_nove{};
            for(int k{}; k < m2.br_kolona; k++)
            {
                element_nove = 0;
                for(int j{}; j < m1.br_kolona; j++)
                {
                    element_nove += m1.elementi[i][j] * m2.elementi[j][k];
                }
                m3.elementi[i][k] = element_nove;
            }
        }
    }
    catch(...)
    {
        UnistiMatricu(m3);
        throw;
    }
    return m3;
}

template <typename TipElemenata> void PomnoziSkalarom(Matrica <TipElemenata> & A, double skalar)
{
    for(int i{}; i < A.br_redova; i++)
        for(int j{}; j < A.br_kolona; j++) A.elementi[i][j] *= skalar;
}

template <typename TipElemenata> void Nuliraj(Matrica <TipElemenata> &A)
{
    for(int i = 0; i < A.br_redova; i++)
            for(int j = 0; j < A.br_kolona; j++)
                A.elementi[i][j] = 0;
}
template <typename TipElemenata> Matrica <TipElemenata> MatricniPolinom(const Matrica <TipElemenata> & A,
    std::vector<double> p)
{
    if(A.br_kolona != A.br_redova) throw std::domain_error("Matrica mora biti kvadratna");
    Matrica <TipElemenata> rez{}, N{};
    try
    {   
        if(p.size() == 0)
        {
            auto nova = StvoriMatricu<TipElemenata>(A.br_redova, A.br_kolona, 'O');
            return nova;
        }
        N = StvoriMatricu<TipElemenata>(A.br_redova, A.br_kolona);
        Nuliraj(N);
        for(int i = 0; i < p.size(); i++)
        {
            rez = Jedinicna<TipElemenata>(A.br_redova, A.br_kolona);
            for(int j = 0; j < i; j++)
            {
                auto temp = ProduktMatrica(A, rez);
                UnistiMatricu(rez);
                rez = temp;
            }
            PomnoziSkalarom(rez, p.at(i));
            auto temp = ZbirMatrica(N, rez);
            UnistiMatricu(N);
            UnistiMatricu(rez);
            N = temp; 
        }
        return N;
    }
    catch(...)
    {
        UnistiMatricu(N);
        UnistiMatricu(rez);
        throw;
    }
}
int main()
{
    int vel{};
    Matrica <double> A{};
    std::cout<<"Unesite dimenziju kvadratne matrice: ";
    std::cin>>vel;
    try
    {
        A = StvoriMatricu <double> (vel, vel, 'A');
        std::cout<<"Unesite elemente matrice "<<A.ime_matrice<<":\n";
        UnesiMatricu(A);
    }
    catch (std::bad_alloc)
    {
        std::cout <<"Nema dovoljno memorije!\n";
    }
    int red{};
    std::cout<<"Unesite red polinoma: ";
    std::cin>>red;
    std::cout<<"Unesite koeficijente polinoma: ";
    std::vector<double> koef(red + 1);
    for(int i{}; i <= red; i++) std::cin>> koef.at(i);
    auto P = MatricniPolinom(A, koef);
    UnistiMatricu(A);
    IspisiMatricu(P, 10, 6, true);
    return 0;
}