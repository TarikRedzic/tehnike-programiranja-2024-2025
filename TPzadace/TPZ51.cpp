#include <array>
#include <iostream>

class Datum
{
    int dan, mjesec, godina, slovno;
    const char imena_mjeseci[12][10]{"Januar", "Februar", "Mart", "April", "Maj", "Juni",
        "Juli", "August", "Septembar", "Oktobar", "Novembar", "Decembar"};
    const char imena_dana[7][12]{"Ponedjeljak", "Utorak", "Srijeda", "Cetvrtak",
        "Petak", "Subota", "Nedjelja"};
    static std::array<int, 12> dani_u_mjesecu;
    int BrojPrestupnih(int g);
    bool IspravanDatum(int dan, int mjesec, int godina);
    static int DaniOdPocetkaGodine(int d, int m, int g);
    static int DanNula(int d, int m, int g);
public:
    enum Mjeseci {Januar = 1, Februar, Mart, April, Maj, Juni, Juli, August, Septembar,
    Oktobar, Novembar, Decembar};
    enum Dani {Ponedjeljak = 1, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja};
    Datum(int dan, int mjesec, int godina){
        Postavi(dan, mjesec, godina);
    }
    Datum(int dan, Mjeseci mjesec, int godina){
        Postavi(dan, mjesec, godina);
    }
    Datum& Postavi(int dan, int mjesec, int godina);
    Datum& Postavi(int dan, Mjeseci mjesec, int godina);
    int DajDan() const{return dan;}
    Mjeseci DajMjesec() const{return Mjeseci(mjesec);}
    int DajGodinu() const{return godina;}
    const char* DajImeMjeseca() const;
    Dani DajDanUSedmici() const;
    const char* DajImeDanaUSedmici() const{
        return imena_dana[DajDanUSedmici() - 1];
    }
    Datum operator+(int n);
    Datum operator-(int n);
    Datum operator++(int){
        Datum novo = *this; ++*this; return novo;
    }
    Datum& operator++();
    Datum operator--(int){
        Datum novo = *this; --*this; return novo;
    }
    Datum& operator--();
    Datum& operator+=(int n);
    Datum& operator-=(int n);
    operator std::string() const;
    explicit operator int() const{
        return DanNula(DajDan(), mjesec, DajGodinu());
    }
    friend bool operator ==(const Datum& dat1, const Datum& dat2);
    friend bool operator !=(const Datum& dat1, const Datum& dat2);
    friend bool operator >=(const Datum& dat1, const Datum& dat2);
    friend bool operator <=(const Datum& dat1, const Datum& dat2);
    friend bool operator >(const Datum& dat1, const Datum& dat2);
    friend bool operator <(const Datum& dat1, const Datum& dat2);
    friend std::ostream& operator<<(std::ostream& tok, const Datum d);
    friend std::istream& operator>>(std::istream& tok, Datum& d);
    friend int operator-(Datum d1, Datum d2);
};

std::array<int, 12> Datum::dani_u_mjesecu{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool Prestupna(int godina) 
{
    return (godina % 4 == 0 && godina % 100 != 0 || godina % 400 == 0);
}

int Datum::DaniOdPocetkaGodine(int d, int m, int g)
{
    int brd{};
    auto dum = Datum::dani_u_mjesecu;
    for(int i = 0; i < m - 1; i++)
    {
        if(i == 1 && Prestupna(g)) brd += 29;
        else brd += dum[i];
    }
    return brd += d - 1;
}

int main()
{
    int n = -36890;
    Datum d(4, 1, 1800);
    std::cout<<d.DajImeMjeseca()<<std::endl;
    std::cout<<d.DajImeDanaUSedmici()<<std::endl;
    std::cout<<d<<" ";
    std::cout<<------d<<std::endl;
    std::cout<<++d<<std::endl;
    Datum d1(10,1,1804), d2(10,1,1905);
    std::cout<<d2-d1<<std::endl;
    std::cout<<d1 + 36890;
    std::cout<<d1 - n;
    std::cout<<d2 - 36890;
    Datum d3(12, 3, 1800);
    Datum d4(2, 3, 1800);
    d3 -= 10;
    std::cout<<d3<<std::endl;
    std::cin>>d3;
    std::cout<<d3<<std::endl;
    std::string s = d3;
    std::cout<<s<<std::endl;
    n = int(d);
    std::cout<<n<<std::endl;
    return 0;
}

std::ostream& operator<<(std::ostream& tok, const Datum d)
{
    return tok<<d.DajDan()<<"."<<d.DajImeMjeseca()<<" "<<d.DajGodinu()<<
        ".("<<d.DajImeDanaUSedmici()<<")";
}

std::istream& operator>>(std::istream& tok, Datum& d)
{
    int dan{}, mjesec{}, godina{};
    tok>>dan;
    if(tok.peek() != '/') tok.setstate(std::ios::failbit);
    tok.get();
    tok>>mjesec;
    if(tok.peek() != '/') tok.setstate(std::ios::failbit);
    tok.get();
    tok>>godina;
    if(tok && d.IspravanDatum(dan, mjesec, godina))d.Postavi(dan, mjesec, godina);
    else tok.setstate(std::ios::failbit);
    return tok;
}

int Datum::BrojPrestupnih(int g)
{
    int pr{};
    for(int i{1800}; i < g; i += 4) if(Prestupna(g)) pr++;
    return pr;
}

int Datum::DanNula(int d, int m, int g)
{
    int brd1{};
    for(int i = 1800; i < g; i++) brd1 += 365 + (Prestupna(i) ? 1 : 0);
    return brd1 += Datum::DaniOdPocetkaGodine(d, m, g);
}

Datum& Datum::Postavi(int dan, int mjesec, int godina)
{
    if(!IspravanDatum(dan, mjesec, godina))
        throw std::domain_error ("Nelegalan datum");
    this->dan = dan; this->mjesec = mjesec; this->godina = godina;
    slovno = (2 + (DanNula(dan, mjesec, godina) % 7)) % 7 + 1;
    return *this;
}

bool Datum::IspravanDatum(int dan, int mjesec, int godina)
{
    std::array<int, 12> broj_dana = dani_u_mjesecu;
    if(Prestupna(godina)) broj_dana[1]++;
    if(godina < 1800 || mjesec < 1 || mjesec > 12 || dan < 1
    || dan > broj_dana[mjesec - 1]) return false;
    return true;
}

Datum& Datum::Postavi(int dan, Mjeseci mjesec, int godina)
{
    return Datum::Postavi(dan, int(mjesec), godina);
}

const char* Datum::DajImeMjeseca() const
{
    return imena_mjeseci[int(mjesec) - 1];
}

Datum::Dani Datum::DajDanUSedmici() const
{
    return Dani(slovno);
}

Datum& Datum::operator++()
{
    return *this += 1;
}

Datum& Datum::operator--()
{
    return *this -= 1;
}

int operator-(Datum d1, Datum d2)
{
    int brd1 = Datum::DanNula(d1.dan, d1.mjesec, d1.godina);
    int brd2 = Datum::DanNula(d2.dan, d2.mjesec, d2.godina);
    return brd1 - brd2;
}

Datum Datum::operator+(int n)
{
    if (n < 0) return *this - (-n);
    int d = dan, m = mjesec, g = godina;
    while(n > 0)
    {
        if(m == 2) dani_u_mjesecu[1] = (Prestupna(g)? 29: 28);
        if(n <= dani_u_mjesecu[m - 1] - d) d += n, n = 0;
        else
        {
            n -= (dani_u_mjesecu[m - 1] - d + 1);
            d = 1; m == 12 ? m = 1, g++ : m++;
        }
    }
    return Datum(d, m, g);
}

Datum Datum::operator-(int n)
{
    if (n < 0) return *this + (-n);
    int d = dan, m = mjesec, g = godina;
    while(n > 0)
    {
        if(m == 3) dani_u_mjesecu[1] = (Prestupna(g)? 29: 28);
        if(n < d) d -= n, n = 0;
        else
        {
            n -= d;
            m == 1 ? m = 12, g-- : m--;
            d = dani_u_mjesecu[m - 1];
        }
    }
    return Datum(d, m, g);
}

Datum& Datum::operator+=(int n)
{
    if (n < 0) return *this -= (-n);
    //if (n == 1) return ++*this;
    Datum dat(dan, mjesec, godina);
    int d = (dat + n).DajDan(), m = (dat + n).mjesec, g = (dat + n).DajGodinu();
    return Postavi(d, m, g);
}

Datum& Datum::operator-=(int n)
{
    if (n < 0) return *this += (-n);
    //if (n == 1) return --*this;
    Datum dat(dan, mjesec, godina);
    int d = (dat - n).DajDan(), m = (dat - n).mjesec, g = (dat - n).DajGodinu();
    return Postavi(d, m, g);
}

bool operator ==(const Datum& dat1, const Datum& dat2)
{
    return dat1.DanNula(dat1.dan, dat1.mjesec, dat1.godina) == 
        dat2.DanNula(dat2.dan, dat2.mjesec, dat2.godina);
}

bool operator !=(const Datum& dat1, const Datum& dat2)
{
    return !(dat1 == dat2);
}

bool operator <=(const Datum& dat1, const Datum& dat2)
{
    return dat1.DanNula(dat1.dan, dat1.mjesec, dat1.godina) <= 
        dat2.DanNula(dat2.dan, dat2.mjesec, dat2.godina);
}

bool operator >=(const Datum& dat1, const Datum& dat2)
{
    return dat1.DanNula(dat1.dan, dat1.mjesec, dat1.godina) >= 
        dat2.DanNula(dat2.dan, dat2.mjesec, dat2.godina);
}

bool operator <(const Datum& dat1, const Datum& dat2)
{
    return !(dat1 >= dat2);
}

bool operator >(const Datum& dat1, const Datum& dat2)
{
    return !(dat1 <= dat2);
}

Datum::operator std::string() const
{
    std::string s;
    ((s += std::to_string(this->DajDan())) += '.') += this->DajImeMjeseca();
    ((s += ' ') += std::to_string(this->DajGodinu())) += '.';
    return ((s += "(") += this->DajImeDanaUSedmici()) += ")";
}

