#include <iostream>
#include <map>

enum class Pravci {Sjever, Istok, Jug, Zapad};

class Robot
{
    Pravci smjer;
    int x, y;
public:
    Robot(): x(0), y(0), smjer(Pravci::Sjever){};
    Robot(int x, int y, Pravci smjer = Pravci::Sjever): x(x), y(y), smjer(smjer){};
    Robot& PostaviPoziciju(int x, int y){
        this->x = x; this->y = y; return *this;
    }
    Robot& PostaviPoziciju(std::pair<int, int> par){
        x = par.first; y = par.second; return *this;
    }
    Robot& PostaviOrijentaciju(Pravci s){smjer = s; return *this;};
    std::pair<int, int> DajPoziciju() const{return {x, y};};
    Pravci DajOrijentaciju()const {return smjer;};
    Robot& operator+=(int korak);
    Robot& operator-=(int korak);
    Robot operator++(int){
        Robot staro = *this; ++*this; return staro;
    }
    Robot& operator++(){
        smjer = Pravci((int(smjer) + 3) % 4);
        return *this;
    }
    Robot operator+(int n){
        Robot novi = *this; novi += n; return novi;
    }
    Robot operator-(int n){
        Robot novi = *this; novi -= n; return novi;
    }
    Robot operator--(int){
        Robot staro = *this; --*this; return staro;
    }
    Robot& operator--(){
        smjer = Pravci((int(smjer) + 1) % 4);
        return *this;
    }
    friend bool operator==(const Robot& r1, const Robot& r2);
    friend bool operator!=(const Robot& r1, const Robot& r2);
    friend std::ostream& operator<<(std::ostream& tok, Robot r);
};


int main() 
{
    Robot r1, r2(5, 3), r3(2, -1, Pravci::Istok);
    std::cout << r1 << r2 << r3;
    r1.PostaviPoziciju(3, 2);
    r2.PostaviPoziciju({2, 3}).PostaviOrijentaciju(Pravci::Zapad);
    std::cout << r1 << r2;
    std::cout << r3.DajPoziciju().first << " " << r3.DajPoziciju().second
    << " " << int(r3.DajOrijentaciju()) << std::endl;
    r1 += 10; r2 -= 5;
    std::cout << r1 << r2;
    for(int i = 1; i <= 5; i++) {
    r1++; --r2;
    std::cout << r1 << r2;
    }
    std::cout << r1 + 5 << r2 - 3;
    std::cout << r1 << r2;
    std::cout << std::boolalpha << (r1 == r2) << " " << (r1 != r2) << std::endl;
    return 0;
}


Robot& Robot::operator+=(int korak)
{
    if(int(smjer) % 2) x += korak * (int(smjer) < 2 ? 1: -1);
    else y += korak * (int(smjer) < 2 ? 1: -1);
    return *this;
}

Robot& Robot::operator-=(int korak)
{
    return *this += (-korak);
}

bool operator==(const Robot& r1, const Robot& r2)
{
    return (r1.DajOrijentaciju() == r2.DajOrijentaciju() &
        r1.DajPoziciju().first == r2.DajPoziciju().first &
        r1.DajPoziciju().second == r2.DajPoziciju().second);
}

bool operator!=(const Robot& r1, const Robot& r2)
{
    return !(r1 == r2);
}

std::ostream& operator<<(std::ostream& tok, Robot r)
{
    tok<<"Robot se nalazi na poziciji ("<<r.DajPoziciju().first<<","
        <<r.DajPoziciju().second<<") i gleda na ";
    if(r.DajOrijentaciju() == Pravci::Istok) std::cout<<"istok.\n";
    else if(r.DajOrijentaciju() == Pravci::Zapad) std::cout<<"zapad.\n";
    else if(r.DajOrijentaciju() == Pravci::Sjever) std::cout<<"sjever.\n";
    else if(r.DajOrijentaciju() == Pravci::Jug) std::cout<<"jug.\n";
    return tok;
}

/*
Robot se nalazi na poziciji (0,0) i gleda na sjever.
Robot se nalazi na poziciji (5,3) i gleda na sjever.
Robot se nalazi na poziciji (2,-1) i gleda na istok.
Robot se nalazi na poziciji (3,2) i gleda na sjever.
Robot se nalazi na poziciji (2,3) i gleda na zapad.
2 -1 1
Robot se nalazi na poziciji (3,12) i gleda na sjever.
Robot se nalazi na poziciji (7,3) i gleda na zapad.
Robot se nalazi na poziciji (3,12) i gleda na zapad.
Robot se nalazi na poziciji (7,3) i gleda na sjever.
Robot se nalazi na poziciji (3,12) i gleda na jug.
Robot se nalazi na poziciji (7,3) i gleda na istok.
Robot se nalazi na poziciji (3,12) i gleda na istok.
Robot se nalazi na poziciji (7,3) i gleda na jug.
Robot se nalazi na poziciji (3,12) i gleda na sjever.
Robot se nalazi na poziciji (7,3) i gleda na zapad.
Robot se nalazi na poziciji (3,12) i gleda na zapad.
Robot se nalazi na poziciji (7,3) i gleda na sjever.
Robot se nalazi na poziciji (-2,12) i gleda na zapad.
Robot se nalazi na poziciji (7,0) i gleda na sjever.
Robot se nalazi na poziciji (3,12) i gleda na zapad.
Robot se nalazi na poziciji (7,3) i gleda na sjever.
false true
*/