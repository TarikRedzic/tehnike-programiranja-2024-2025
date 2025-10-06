#include <iostream>
#include <cmath>
#include <memory>
#include <vector>

const double PI = atan(1) * 4;
class Lik
{
public:
    virtual ~Lik() = default;
    virtual void IspisiSpecificnosti() const = 0;
    virtual double DajObim() const = 0;
    virtual double DajPovrsinu() const = 0;
    void Ispisi() const{
        IspisiSpecificnosti();
        std::cout<<"Obim: "<<DajObim()<<" Povrsina: "<<DajPovrsinu()
            <<std::endl;
    }
};

class Krug: public Lik
{
    double r;
public:
    Krug(double r): r(r){
        if(r <= 0) throw std::domain_error("Neispravni parametri");
    }
    void IspisiSpecificnosti()const override{
        std::cout<<"Krug poluprecnika "<<r<<std::endl;
    }
    double DajObim()const override{
        return 2 * r * PI;
    }
    double DajPovrsinu()const override{
        return r * r * PI;
    }
};

class Pravougaonik: public Lik
{
    double a, b;
public:
    Pravougaonik(double a, double b){
        if(a <= 0 || b <= 0) throw std::domain_error("Neispravni parametri");
        this->a = a; this->b = b;
    }
    void IspisiSpecificnosti()const override{
        std::cout<<"Pravougaonik sa stranicama duzine "<<a<<" i "<<b<<std::endl;
    }
    double DajObim()const override{
        return 2 * (a + b);
    }
    double DajPovrsinu()const override{
        return a * b;
    }
};

class Trougao: public Lik
{
    double a, b, c;
public:
    Trougao(double a, double b, double c);
    void IspisiSpecificnosti()const override{
        std::cout<<"Trougao sa stranicama duzine "
            <<a<<", "<<b<<" i "<<c<<std::endl;
    }
    double DajObim()const override{
        return a + b + c;
    }
    double DajPovrsinu() const override{
        double s = (a + b + c)/2;
        return sqrt(s*(s - a)*(s - b)*(s - c));
    }
};

int main()
{
    std::vector<std::shared_ptr<Lik> >likovi;
    int n;
    std::cout<<"Koliko zelite likova: ";
    std::cin>>n;
    bool fail = false;
    for(int i = 0; i < n; i++, fail = false)
    {
        std::cout<<"Lik "<<i + 1<<": ";
        std::cin>>std::ws;
        char c = std::cin.get();
        if(c == 'P')
        {
            double a, b;
            std::cin>>a;
            std::cin.get();
            std::cin>>b;
            if(std::cin.peek() != ' ' && std::cin.peek() != '\n') fail = true;
            if(!std::cin) fail = true;
            else
            {
                likovi.push_back(std::make_shared<Pravougaonik>(a, b));
            }
        }
        else if(c == 'K')
        {
            double r;
            std::cin>>r;
             if(std::cin.peek() != ' ' && std::cin.peek() != '\n') fail = true;
            if(!std::cin) fail = true;
            else
            {
                likovi.push_back(std::make_shared<Krug>(r));
            }
        }
        else if(c == 'T')
        {
            double a, b, c;
            std::cin>>a;
            std::cin.get();
            std::cin>>b;
            std::cin.get();
            std::cin>>c;
            if(std::cin.peek() != ' ' && std::cin.peek() != '\n') fail = true;
            if(!std::cin) fail = true;
            else
            {
                likovi.push_back(std::make_shared<Trougao>(a, b, c));
            }
        }
        else fail = true;
        if(fail)
        {
            i--;
            std::cout<<"Pogresni podaci, ponovite unos!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            fail = false;
        }
    }
    for(const auto& s: likovi) s->Ispisi();
    return 0;
}

Trougao::Trougao(double a, double b, double c)
{
    if((a + b <= c) || (a + c <= b) || (b + c <= a) ||
            a <= 0 || b <= 0 || c <= 0)
        throw std::domain_error("Neispravni parametri");
    this->a = a; this->b = b; this->c = c;
}