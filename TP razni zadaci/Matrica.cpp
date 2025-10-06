#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <new>

template <typename TipEl>
    class Matrica 
{
    char ime_matrice;
    int br_redova, br_kolona;
    TipEl **elementi;
    static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
    static void DealocirajMemoriju(TipEl **elementi, int br_redova);
    void KopirajElemente(TipEl **elementi);
    public:
    Matrica(int br_redova, int br_kolona, char ime = 0);
    Matrica(const Matrica &m);
    Matrica(Matrica &&m);
    ~Matrica() { DealocirajMemoriju(elementi, br_redova); }
    Matrica &operator =(const Matrica &m);
    Matrica &operator =(Matrica &&m);
    Matrica& operator *=(const Matrica& m);
    Matrica& operator +=(const Matrica& m);
    Matrica& operator -=(const Matrica& m);
    
    template <typename Tip>
    friend Matrica operator*(const Matrica<Tip>& m1, const Matrica<Tip>& m2);
    template <typename Tip>
    friend Matrica operator*(const Matrica<Tip>& m1, Tip broj);
    template <typename Tip>
    friend Matrica operator*(Tip broj, const Matrica<Tip>& m1);
    template <typename Tip>
    friend Matrica operator-(const Matrica<Tip>& m1, const Matrica<Tip>& m2);
    template <typename Tip>
    friend Matrica operator+(const Matrica<Tip>& m1, const Matrica<Tip>& m2);
    template <typename Tip2>
    friend std::ostream& operator<<(std::ostream& tok, const Matrica<Tip2>& a);
    template <typename Tip2>
    friend std::istream& operator>>(std::istream& tok, Matrica<Tip2>& a);
    TipEl *operator [](int i) { return elementi[i]; }
    const TipEl *operator [](int i) const { return elementi[i]; }
    TipEl &operator ()(int i, int j);
    const TipEl operator ()(int i, int j) const;
    operator std::string() const;

};
template <typename TipEl>
TipEl **Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona) 
{
    TipEl **elementi = new TipEl*[br_redova]{};
    try {
    for(int i = 0; i < br_redova; i++) elementi[i] = new TipEl[br_kolona];
    }
    catch(...) {
    DealocirajMemoriju(elementi, br_redova); throw;
    }
    return elementi;
}
template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova) 
{
    for(int i = 0; i < br_redova; i++) delete[] elementi[i];
    delete[] elementi;
}
template <typename TipEl>
    Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime) :
    br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime),
    elementi(AlocirajMemoriju(br_redova, br_kolona)) {}
template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi) 
{
    for(int i = 0; i < br_redova; i++)
    for(int j = 0; j < br_kolona; j++) Matrica::elementi[i][j] = elementi[i][j];
}
template <typename TipEl>
    Matrica<TipEl>::Matrica(const Matrica<TipEl> &m) : br_redova(m.br_redova),
    br_kolona(m.br_kolona), ime_matrice(m.ime_matrice),
    elementi(AlocirajMemoriju(m.br_redova, m.br_kolona)) 
{
    KopirajElemente(m.elementi);
}
template <typename TipEl>
    Matrica<TipEl>::Matrica(Matrica<TipEl> &&m) : br_redova(m.br_redova),
    br_kolona(m.br_kolona), elementi(m.elementi), ime_matrice(m.ime_matrice) 
{
    m.br_redova = 0; m.elementi = nullptr;
}
template <typename TipEl>
    Matrica<TipEl> &Matrica<TipEl>::operator =(const Matrica<TipEl> &m) 
{
    if(br_redova < m.br_redova || br_kolona < m.br_kolona) {
    TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
    DealocirajMemoriju(elementi, br_redova);
    elementi = novi_prostor;
    }
    else if(br_redova > m.br_redova)
    for(int i = m.br_redova; i < br_redova; i++) delete elementi[i];
    br_redova = m.br_redova; br_kolona = m.br_kolona;
    ime_matrice = m.ime_matrice; KopirajElemente(m.elementi);
    return *this;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(Matrica<TipEl> &&m) 
{
    std::swap(br_redova, m.br_redova); std::swap(br_kolona, m.br_kolona);
    std::swap(ime_matrice, m.ime_matrice); std::swap(elementi, m.elementi);
    return *this;
}


template <typename TipEl>
 Matrica<TipEl> ZbirMatrica(const Matrica<TipEl> &m1,
 const Matrica<TipEl> &m2) {
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
    Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
    for(int i = 0; i < m1.br_redova; i++)
    for(int j = 0; j < m1.br_kolona; j++)
    m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
    return m3;
}
/*
template <typename Tip2>
    std::ostream& operator<<(std::ostream tok, const Matrica<Tip2>& a)
{
    for(int i = 0; i < a.br_redova; i++) 
    {
        for(int j = 0; j < a.br_kolona; j++)
            tok << a.elementi[i][j];
        tok << std::endl;
    }
    return tok;
}*/
template <typename TipEl>
    std::ostream &operator <<(std::ostream &tok, const Matrica<TipEl> &m) 
{
    int sirina_ispisa = tok.width();
    for(int i = 0; i < m.br_redova; i++) {
    for(int j = 0; j < m.br_kolona; j++)
    std::cout << std::setw(sirina_ispisa) << m.elementi[i][j];
    std::cout << std::endl;
    }
    return tok;
}


template <typename TipEl>
std::istream &operator >>(std::istream &tok, Matrica<TipEl> &m) 
{
    for(int i = 0; i < m.br_redova; i++)
    for(int j = 0; j < m.br_kolona; j++) {
        if(&tok == &std::cin)
        std::cout << m.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
        tok >> m.elementi[i][j];
    }
    return tok;
}

/*
template <typename Tip2>
    std::istream& operator>>(std::istream tok, Matrica<Tip2>& a)
{
    for(int i = 0; i < a.br_redova; i++)
        for(int j = 0; j < a.br_kolona; j++) 
        {
            std::cout << a.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
            tok >> a.elementi[i][j];
        }
    return tok;
} */  

template <typename TipEl>
    Matrica<TipEl>& Matrica<TipEl>::operator *=(const Matrica<TipEl>& m)
{
    if(m.br_kolona () != m.br_redova())
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    Matrica<TipEl> nova = *this * m;
    for(int i{}; i < br_redova; i++)
        for(int j{}; j < br_kolona; j++) elementi[i][j] = nova[i][j];
    return *this;
}

template <typename TipEl>
    Matrica<TipEl>& Matrica<TipEl>::operator +=(const Matrica& m)
{
    Matrica<TipEl> nova = *this + m;
    for(int i{}; i < br_redova; i++)
        for(int j{}; j < br_kolona; j++) elementi[i][j] = nova[i][j];
    return *this;
}

template <typename TipEl>
    Matrica<TipEl>& Matrica<TipEl>::operator -=(const Matrica& m)
{
    Matrica<TipEl> nova = *this - m;
    for(int i{}; i < br_redova; i++)
        for(int j{}; j < br_kolona; j++) elementi[i][j] = nova[i][j];
    return *this;
}

template <typename Tip>
    Matrica<Tip> operator*(const Matrica<Tip>& m1, const Matrica<Tip>& m2)
{
    if(m2.br_redova() != m1.br_kolona())
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    Tip nova[m1.br_redova][m2.br_kolona];
    for(int i = 0; i < m1.br_redova; i++)
    {
        for(int j = 0; j < m2.br_kolona; j++)
        {
            Tip sakup{};
            for(int k = 0; k < m1.br_kolona; k++)
            {
                sakup += m1.elementi[i][k] * m2.elementi[j][k];
            }
            nova[i][j] = sakup;
        }
    }
    return nova;
}

template <typename Tip>
    Matrica<Tip> operator*(const Matrica<Tip>& m1, Tip broj)
{
    Tip nova[m1.br_redova][m1.br_kolona];
    for(int i = 0; i < m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            nova[i][j] = m1.elementi[i][j] * broj;
    return nova;
}

template <typename Tip>
    Matrica<Tip> operator*(Tip broj, const Matrica<Tip>& m1)
{
    return m1 * broj;
}

template <typename Tip>
    Matrica<Tip> operator-(const Matrica<Tip>& m1, const Matrica<Tip>& m2)
{
    if(m2.br_redova() != m1.br_redova || m2.br_kolona != m1.br_kolona())
        throw std::domain_error("Matrice nisu saglasne za oduzimanje");
    Tip nova[m1.br_redova][m1.br_kolona];
    for(int i = 0; i < m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            nova[i][j] = m1.elementi[i][j] - m2.elementi[i][j];
    return nova;
}

template <typename Tip>
    Matrica<Tip> operator+(const Matrica<Tip>& m1, const Matrica<Tip>& m2)
{
    if(m2.br_redova() != m1.br_redova || m2.br_kolona != m1.br_kolona())
        throw std::domain_error("Matrice nisu saglasne za sabiranje");
    Tip nova[m1.br_redova][m1.br_kolona];
    for(int i = 0; i < m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            nova[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
    return nova;
}

template < typename TipEl >
    Matrica < TipEl > ::operator std::string() const {
        using std::to_string;
        std::string s = "{";
        for (int i = 0; i < br_redova; i++) {
            s += "{";
            for (int j = 0; j < br_kolona; j++) {
                s += to_string(elementi[i][j]);
                if (j != br_kolona - 1) s += ",";
            }
            s += "}";
            if (i != br_redova - 1) s += ",";
        }
        return s += "}";
    }

template <typename TipEl>
    TipEl& Matrica <TipEl>::operator()(int i, int j) {
        if (i < 1 || i > br_redova || j < 1 || j > br_kolona)
            throw std::range_error("Neispravan indeks");
        return elementi[i - 1][j - 1];
    }
template <typename TipEl>
    const TipEl Matrica <TipEl>::operator()(int i, int j) const 
    {
        if (i < 1 || i > br_redova || j < 1 || j > br_kolona)
            throw std::range_error("Neispravan indeks");
        return elementi[i - 1][j - 1];
    }

int main() 
{
    
    return 0;
}
