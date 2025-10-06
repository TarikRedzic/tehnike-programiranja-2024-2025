#include <iostream>
#include <iomanip>
class Sat {   int ukupno = 0; 
public:   static bool DaLiJeIspravno(int sati, int minute, int sekunde);   Sat& Postavi(int sati, int minute, int sekunde);   Sat& PostaviNormalizirano(int sati, int minute, int sekunde);   Sat &Sljedeci() { return PomjeriZa(1); }   Sat &Prethodni() { return PomjeriZa(-1); }   Sat &PomjeriZa(int pomak);   void Ispisi() const;   int DajSate() const { return ukupno / 3600; }   int DajMinute() const { return (ukupno % 3600) / 60; }   int DajSekunde() const { return ukupno % 60; }   friend int BrojSekundiIzmedju(const Sat &s1, const Sat &s2);   static int Razmak(const Sat &s1, const Sat &s2); }; 
bool Sat::DaLiJeIspravno(int sati, int minute, int sekunde) {   return sati >= 0 && sati <= 23 && minute >= 0 
    && minute <= 59 && sekunde >=0 && sekunde <= 59; }
    Sat &Sat::Postavi(int sati, int minute, int sekunde) {   if(!DaLiJeIspravno(sati, minute, sekunde)) throw std::domain_error("Neispravno vrijeme");   ukupno = 3600 * sati + 60 * minute + sekunde;   return *this; }
    Sat &Sat::PostaviNormalizirano(int sati, int minute, int sekunde) {   int ukupno = (3600 * sati + 60 * minute + sekunde) % 86400;   if(ukupno < 0) ukupno += 86400;   return *this; }
Sat &Sat::PomjeriZa(int pomak) {   int ukupno = (ukupno + pomak) % 86400;   if(ukupno < 0) ukupno += 86400;   return *this; }
void Sat::Ispisi() const {   char stara_ispuna = std::cout.fill('0');   std::cout << std::setw(2) << DajSate() << ":" << std::setw(2) << DajMinute() << ":"     << std::setw(2) << DajSekunde();   std::cout.fill(stara_ispuna); } 
int BrojSekundiIzmedju(const Sat &s1, const Sat &s2) {   return s1.ukupno - s2.ukupno; } 
int Sat::Razmak(const Sat &s1, const Sat &s2) {   return BrojSekundiIzmedju(s1, s2); }