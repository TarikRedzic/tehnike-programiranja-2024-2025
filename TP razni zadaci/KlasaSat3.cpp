#include <iomanip>
#include <iostream>

class Sat
{
    int sati, minute, sekunde;
public:
    Sat():sati(0), minute(0), sekunde(0){};
    Sat(int sati, int minute, int sekunde){
        PostaviNormalizirano(sati, minute, sekunde);
    }
    static bool DaLiJeIspravno(const int, const int, const int);
    Sat& operator+=(int n);
    Sat operator+(int n);
    Sat operator++(int);
    Sat& operator++();
    Sat& operator-=(int n);
    Sat operator-(int n);
    Sat operator--(int);
    Sat& operator--();
    friend std::ostream& operator<<(std::ostream& tok, const Sat& s);
    Sat& Postavi(int, int, int);
    Sat& PostaviNormalizirano(int, int, int);
    int DajSate() const{return sati;};
    int DajMinute() const {return minute;};
    int DajSekunde() const {return sekunde;};
    friend Sat operator-(const Sat& s1, const Sat& s2);
};



int main() {
    Sat s1(20, 4, 39), s2(25, 150, 290);
    std::cout << s1 << " " << s2 << std::endl; // 20:04:39 03:34:50
    ++s1;
    std::cout << s1 << std::endl; // 20:04:40
    std::cout << ++s1 << std::endl; // 20:04:41
    s1++;
    std::cout << s1 << std::endl; // 20:04:42
    std::cout << s1++ << std::endl; // 20:04:42
    std::cout << s1 << std::endl; // 20:04:43
    --s1;
    std::cout << s1 << std::endl; // 20:04:42
    std::cout << --s1 << std::endl; // 20:04:41
    s1--;
    std::cout << s1 << std::endl; // 20:04:40
    std::cout << s1-- << std::endl; // 20:04:40
    std::cout << s1 << std::endl; // 20:04:39
    ++++++s1;
    std::cout << s1 << std::endl; // 20:04:42
    s1 += 25000;
    std::cout << s1 << std::endl; // 03:01:22
    s1 -= 25000;
    std::cout << s1 << std::endl; // 20:04:42
    std::cout << s1 - s2 << std::endl; // 59392
    std::cout << s1 + 100 << std::endl; // 20:06:22
    std::cout << s1 << std::endl; // 20:04:42
    std::cout << s1 - 100 << std::endl; // 20:03:02
    std::cout << s1 << std::endl; // 20:04:42
    s2 = s1 += 100;
    std::cout << s2 << std::endl; // 20:06:22
    return 0;

}

bool Sat::DaLiJeIspravno(int sat, int minut, int sekund)
{
    if(sat > 23 || sat < 0) return false;
    if(minut > 59 || minut < 0) return false;
    if(sekund > 59 || sekund < 0) return false;
    return true;
}

Sat& Sat::Postavi(int sat, int min, int sek)
{
    if(!DaLiJeIspravno(sat, min, sek)) throw std::domain_error("Neispravno vrijeme");
    sati = sat; minute = min; sekunde = sek;
    return *this;
}

Sat& Sat::PostaviNormalizirano(int sat, int min, int sek)
{
    int ukupno = (3600 * sat + 60 * min + sek) % 86400;   
    if(ukupno < 0) ukupno += 86400;   
    Sat::sati = ukupno / 3600;   
    Sat::minute = (ukupno % 3600) / 60;   
    Sat::sekunde = ukupno % 60;   
    return *this;
}

Sat& Sat::operator+=(int n)
{
    return PostaviNormalizirano(sati, minute, sekunde + n);
}

Sat Sat::operator++(int)
{
    Sat staro = *this;
    *this += 1;
    return staro;
}

Sat& Sat::operator++()
{
    return *this += 1;
}

Sat& Sat::operator-=(int n)
{
    return PostaviNormalizirano(sati, minute, sekunde - n);
}

Sat Sat::operator--(int)
{
    Sat staro = *this;
    *this -= 1;
    return staro;
}

Sat& Sat::operator--()
{
    return *this -= 1;
}

Sat Sat::operator-(int n)
{
    Sat novo = *this;
    novo -= n;
    return novo;
}

Sat Sat::operator+(int n)
{
    Sat novo = *this;
    novo += n;
    return novo;
}


std::ostream& operator<<(std::ostream& tok, const Sat& s)
{
    tok<<std::setw(2)<<std::setfill('0')<<s.DajSate()<<
        ":"<<std::setw(2)<<std::setfill('0')<<s.DajMinute()<<
        ":"<<std::setw(2)<<std::setfill('0')<<s.DajSekunde()<<std::endl;
    return tok;
}

Sat operator-(const Sat& s1, const Sat& s2)
{
    int sek1{s1.DajSate() * 3600 + s1.DajMinute() * 60 + s1.DajSekunde()},
        sek2{s2.DajSate() * 3600 + s2.DajMinute() * 60 + s2.DajSekunde()};
    return {0, 0, sek1-sek2};
}
