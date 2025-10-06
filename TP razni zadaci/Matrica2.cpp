#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <new>
#include <vector>

template <typename TipEl>
    class Matrica 
{
    char ime_matrice;
    std::vector<std::vector<TipEl>> elementi;
    void KopirajElemente(std::vector<std::vector<TipEl>> elementi);
    public:
    Matrica(int br_redova, int br_kolona, char ime = 0);
    Matrica(const Matrica &m);
    Matrica(Matrica &&m);
    ~Matrica() = default;
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
    Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime) :
    ime_matrice(ime) {
        elementi = std::vector<std::vector<TipEl>>(br_redova, std::vector<TipEl>(br_kolona));
    }
template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(std::vector<std::vector<TipEl>> elementi) 
{
    for(int i = 0; i < elementi.size(); i++)
    for(int j = 0; j < elementi.at(0).size(); j++) Matrica::elementi.at(i).at(j) = elementi[i][j];
}
template <typename TipEl>
    Matrica<TipEl>::Matrica(const Matrica<TipEl> &m) {
    KopirajElemente(m.elementi);
}
template <typename TipEl>
    Matrica<TipEl>::Matrica(Matrica<TipEl> &&m) :elementi(m.elementi), ime_matrice(m.ime_matrice) {}

template <typename TipEl>
    Matrica<TipEl> &Matrica<TipEl>::operator =(const Matrica<TipEl> &m) 
{
    ime_matrice = m.ime_matrice; KopirajElemente(m.elementi);
    return *this;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(Matrica<TipEl> &&m) 
{
    std::swap(ime_matrice, m.ime_matrice); std::swap(elementi, m.elementi);
    return *this;
}


template <typename TipEl>
 Matrica<TipEl> ZbirMatrica(const Matrica<TipEl> &m1,
 const Matrica<TipEl> &m2) {
    if(m1.size() != m2.size() || m1.at(0).size() != m2.at(0).size())
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
    Matrica<TipEl> m3(m1.size(), m1.at(0).size());
    for(int i = 0; i < m1.size(); i++)
    for(int j = 0; j < m1.at(0).size(); j++)
    m3.elementi.at(i).at(j) = m1.elementi.at(i).at(j) + m2.elementi.at(i).at(j);
    return m3;
}
/*
template <typename Tip2>
    std::ostream& operator<<(std::ostream tok, const Matrica<Tip2>& a)
{
    for(int i = 0; i < a.size(); i++) 
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
    for(int i = 0; i < m.size(); i++) {
    for(int j = 0; j < m.at(0).size(); j++)
    std::cout << std::setw(sirina_ispisa) << m.elementi.at(i).at(j);
    std::cout << std::endl;
    }
    return tok;
}


template <typename TipEl>
std::istream &operator >>(std::istream &tok, Matrica<TipEl> &m) 
{
    for(int i = 0; i < m.size(); i++)
    for(int j = 0; j < m.at(0).size(); j++) {
        if(&tok == &std::cin)
        std::cout << m.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
        tok >> m.elementi.at(i).at(j);
    }
    return tok;
}

/*
template <typename Tip2>
    std::istream& operator>>(std::istream tok, Matrica<Tip2>& a)
{
    for(int i = 0; i < a.size(); i++)
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
    if(m.at(0).size() != m.size())
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    Matrica<TipEl> nova = *this * m;
    for(int i{}; i < elementi.size(); i++)
        for(int j{}; j < elementi.at(0).size(); j++) elementi.at(i).at(j) = nova.at(i).at(j);
    return *this;
}

template <typename TipEl>
    Matrica<TipEl>& Matrica<TipEl>::operator +=(const Matrica& m)
{
    Matrica<TipEl> nova = *this + m;
    for(int i{}; i < m.size(); i++)
        for(int j{}; j < elementi.at(0).size(); j++) elementi.at(i).at(j) = nova.at(i).at(j);
    return *this;
}

template <typename TipEl>
    Matrica<TipEl>& Matrica<TipEl>::operator -=(const Matrica& m)
{
    Matrica<TipEl> nova = *this - m;
    for(int i{}; i < m.size(); i++)
        for(int j{}; j < elementi.at(0).size(); j++) elementi.at(i).at(j)= nova.at(i).at(j);
    return *this;
}

template <typename Tip>
    Matrica<Tip> operator*(const Matrica<Tip>& m1, const Matrica<Tip>& m2)
{
    if(m2.size() != m1.at(0).size())
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    Tip nova[m1.size()][m2.at(0).size()];
    for(int i = 0; i < m1.size(); i++)
    {
        for(int j = 0; j < m2.at(0).size(); j++)
        {
            Tip sakup{};
            for(int k = 0; k < m1.at(0).size(); k++)
            {
                sakup += m1.elementi.at(i).at(j) * m2.elementi.at(i).at(j);
            }
            nova.at(i).at(j) = sakup;
        }
    }
    return nova;
}

template <typename Tip>
    Matrica<Tip> operator*(const Matrica<Tip>& m1, Tip broj)
{
    Tip nova[m1.size()][m1.at(0).size()];
    for(int i = 0; i < m1.size(); i++)
        for(int j = 0; j < m1.at(0).size(); j++)
            nova.at(i).at(j) = m1.elementi.at(i).at(j) * broj;
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
    if(m2.size() != m1.size() || m2.at(0).size() != m1.at(0).size()())
        throw std::domain_error("Matrice nisu saglasne za oduzimanje");
    Tip nova[m1.size()][m1.at(0).size()];
    for(int i = 0; i < m1.size(); i++)
        for(int j = 0; j < m1.at(0).size(); j++)
            nova[i][j] = m1.elementi[i][j] - m2.elementi[i][j];
    return nova;
}

template <typename Tip>
    Matrica<Tip> operator+(const Matrica<Tip>& m1, const Matrica<Tip>& m2)
{
    if(m2.size() != m1.size() || m2.at(0).size() != m1.at(0).size()())
        throw std::domain_error("Matrice nisu saglasne za sabiranje");
    Tip nova[m1.size()][m1.at(0).size()];
    for(int i = 0; i < m1.size(); i++)
        for(int j = 0; j < m1.at(0).size(); j++)
            nova[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
    return nova;
}

template < typename TipEl >
    Matrica < TipEl > ::operator std::string() const {
        using std::to_string;
        std::string s = "{";
        for (int i = 0; i < elementi.size(); i++) {
            s += "{";
            for (int j = 0; j < elementi.at(0).size(); j++) {
                s += to_string(elementi[i][j]);
                if (j != elementi.at(0).size() - 1) s += ",";
            }
            s += "}";
            if (i != elementi.size() - 1) s += ",";
        }
        return s += "}";
    }

template <typename TipEl>
    TipEl& Matrica <TipEl>::operator()(int i, int j) {
        if (i < 1 || i > elementi.size() || j < 1 || j > elementi.at(0).size())
            throw std::range_error("Neispravan indeks");
        return elementi[i - 1][j - 1];
    }
template <typename TipEl>
    const TipEl Matrica <TipEl>::operator()(int i, int j) const 
    {
        if (i < 1 || i > elementi.size() || j < 1 || j > elementi.at(0).size())
            throw std::range_error("Neispravan indeks");
        return elementi[i - 1][j - 1];
    }

int main() 
{
    
    return 0;
}
