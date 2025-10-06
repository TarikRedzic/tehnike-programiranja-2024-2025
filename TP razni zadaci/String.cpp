#include <iostream>
#include <cstring>

class String
{
    char* znakovi;
    int duzina;
    void Alociraj(){znakovi = new char[duzina + 1]{};}
public:
    String(const char* niz = ""): duzina(std::strlen(niz)){
        Alociraj(); std::strcpy(znakovi, niz);
    }
    String(int n, char c): duzina(n){
        Alociraj(); for(int i{}; i < n; i++) znakovi[i] = c;
    }
    String(std::initializer_list<char> lista): duzina(lista.size()){
        Alociraj(); auto it = lista.begin(); 
        for(int i{}; i < duzina; it++, i++) znakovi[i] = *it;
    }
    String(const String& s): duzina(s.DajDuzinu()){
        Alociraj(); for(int i{}; i < duzina; i++) znakovi[i] = s.znakovi[i];
    }
    String(String&& s): duzina(s.DajDuzinu()){
        std::swap(znakovi, s.znakovi);
    }
    ~String(){delete[] znakovi;}
    String& operator=(const String& s);
    String& operator=(String&& s){
        std::swap(duzina, s.duzina); std::swap(znakovi, s.znakovi);
        return *this;
    }
    String& operator=(const char* s);
    int DajDuzinu() const{return duzina;}
    const char *begin() const { return znakovi; }
    char *begin() { return znakovi; }
    const char *end() const { return znakovi + duzina; }
    char *end() { return znakovi + duzina; }
    friend std::ostream& operator<<(std::ostream& tok, const String& s);
    friend std::istream& operator>>(std::istream& tok, String& s);
    friend std::istream& CitajCijeluLiniju(std::istream& tok, String& s);
    char& operator[](int i);
    char operator[](int i) const;
    String operator()(int i, int j);
    friend String operator+(const String& s1, const String& s2);
    String& operator +=(const String& s){
        *this = *this + s; return *this;
    }
    String& operator +=(String&& s){
        *this = *this + s; return *this;
    }
    String& operator +=(const char* s){
        *this = *this + s; return *this;
    }
    friend bool operator==(const String& s1, const String& s2){
        return s1.duzina == s2.duzina && std::strcmp(s1.znakovi, s2.znakovi) == 0;
    }
    friend bool operator!=(const String& s1, const String& s2){
        return !(s1 == s2);
    }
    friend bool operator<(const String& s1, const String& s2){
        return std::strcmp(s1.znakovi, s2.znakovi) < 0;
    }
    friend bool operator>(const String& s1, const String& s2){
        return std::strcmp(s1.znakovi, s2.znakovi) > 0;
    }
    friend bool operator<=(const String& s1, const String& s2){
        return !(s1 > s2);
    }
    friend bool operator>=(const String& s1, const String& s2){
        return !(s1 < s2);
    }
    void Kapitaliziraj(){
        for(int i = 0; i < duzina; i++) znakovi[i] = toupper(znakovi[i]);
    }
    const char* DajCString() const{
        return znakovi;
    }

};

int main()
{
    String s("makedonac");
    std::cout<<s<<std::endl;
    std::cout<<"Unesite novi string: ";
    std::cin>>s;
    std::cout<<s<<std::endl;
    std::cout<<"Unesite novi string: ";
    CitajCijeluLiniju(std::cin, s);
    std::cout<<s<<std::endl;
    return 0;
}

String& String::operator=(const String& s)
{
    auto temp = znakovi; int t = duzina; duzina = s.DajDuzinu();
    try
    {
        Alociraj(); 
        for(int i{}; i < duzina; i++) znakovi[i] = s.znakovi[i];
        delete[] temp;
    }
    catch(...)
    {
        znakovi = temp; duzina = t; throw;
    }
    return *this;
}

String& String::operator=(const char* s)
{
    auto temp = znakovi; int t = duzina; duzina = std::strlen(s);
    try
    {
        Alociraj();
        for(int i = 0; i < duzina; i++) znakovi[i] = s[i];
        delete[] temp;
    }
    catch(const std::exception& e)
    {
        znakovi = temp; duzina = t; throw;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& tok, const String& s)
{
    for(int i{}; i < s.DajDuzinu(); i++) tok<<s.znakovi[i];
    return tok;
}

std::istream& operator>>(std::istream& tok, String& s)
{
    int l = 10, duzina = 0;
    char* niz = new char[l]{}; 
    tok>>std::ws;
    while (true)
    {
        char c = tok.get();
        if(c == ' ' || c == '\n') break;
        niz[duzina++] = c;
        if(duzina == l){
            l += 10;
            char* novi = new char[l]{};
            std::strcpy(novi, niz);
            delete[] niz; niz = novi;
        }
    }
    char* novi = new char[duzina + 1]{};
    for(int i = 0; i < duzina; i++) novi[i] = niz[i];
    delete[] niz; niz = novi;
    s = niz; s.duzina = duzina;
    return tok;
}

std::istream& CitajCijeluLiniju(std::istream& tok, String& s)
{
    int l = 10, duzina = 0;
    char* niz = new char[l]{}; 
    while (true)
    {
        char c = tok.get();
        if(c == '\n') break;
        niz[duzina++] = c;
        if(duzina == l){
            l += 10;
            char* novi = new char[l]{};
            std::strcpy(novi, niz);
            delete[] niz; niz = novi;
        }
    }
    char* novi = new char[duzina + 1]{};
    for(int i = 0; i < duzina; i++) novi[i] = niz[i];
    delete[] niz; niz = novi;
    s = niz; s.duzina = duzina;
    return tok;
}

String operator+(const String& s1, const String& s2)
{
    auto temp = new char[s1.DajDuzinu() + s2.DajDuzinu() + 1];
    for(int i = 0; i < s1.DajDuzinu(); i++) temp[i] = s1.znakovi[i];
    for(int i = 0; i < s2.DajDuzinu(); i++) temp[i + s1.DajDuzinu()] = s2.znakovi[i];
    String s(temp); delete[] temp;
    return s;
}