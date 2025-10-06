#include <cmath>
#include <iostream>
#include <initializer_list>

class Poligon
{
    double* x, *y;
    int tjemena;
    void Alociraj(){
        x = new double[tjemena](); y = new double[tjemena]();
    }
    void Dealociraj(){
        delete[] x; delete[] y;
    }
public:
    explicit Poligon(int br): x(nullptr), y(nullptr), tjemena(br){
        if(br < 3) throw std::range_error("Neispravan poligon");
        Alociraj();
    }
    ~Poligon(){
        Dealociraj();
    }
    Poligon(const Poligon& pol);
    Poligon(Poligon&& pol): 
        x(nullptr), y(nullptr), tjemena(pol.DajBrojTjemena())
    {
        std::swap(x, pol.x); std::swap(y, pol.y);
    }
    Poligon& operator=(const Poligon& pol);
    Poligon operator=(Poligon&& pol){
        *this = std::move(pol); return *this;
    }
    Poligon(std::initializer_list<std::pair<double, double>> lista);
    int DajBrojTjemena() const{return tjemena;}
    Poligon& PostaviTjeme(int tjeme, double iks, double ipsilon);
    Poligon& PostaviTjeme(int tjeme, std::pair<double, double> tacka);
    std::pair<double&, double&> operator[](int i);
    std::pair<double, double> operator[](int i) const;
    bool operator!() const;
    double DajObim() const;
    double DajPovrsinu() const;
};

int main()
{
    Poligon p1(3);
    p1.PostaviTjeme(1, 1, 1).PostaviTjeme(2, {5, 1}).PostaviTjeme(3, {5, 3});
    std::cout << p1.DajObim() << std::endl; // 6
    Poligon p_kopija = p1;
    std::cout << p_kopija.DajObim() << std::endl; // 6
    Poligon p2{{1, 1}, {5, 1}, {5, 3}, {1, 3}};
    std::cout << p2.DajPovrsinu() << std::endl; // 8
    auto t = p2[2];
    std::cout << t.first << " " << t.second << std::endl; // 5 1
    std::pair<int, int> t2{10, 10};
    p2[2] = t2;
    auto t3 = p2[2];
    std::cout << t3.first << " " << t3.second << std::endl; // 10 10
    p2 = p1;
    std::cout << p2.DajPovrsinu() << std::endl;
    return 0;
}

Poligon::Poligon(const Poligon& pol): 
    x(nullptr), y(nullptr), tjemena(pol.DajBrojTjemena())
{
    Alociraj();
    for(int i{}; i < tjemena; i++){
        x[i] = pol.x[i]; y[i] = pol.y[i];
    }
}


Poligon& Poligon::operator=(const Poligon& pol){
    double* tx = x; double* ty = y; int t = tjemena;
    tjemena = pol.DajBrojTjemena();
    try
    {
        Alociraj();
        for(int i{}; i < tjemena; i++){
            x[i] = pol.x[i]; y[i] = pol.y[i];
        }
    }
    catch(const std::exception& e)
    {
        x = tx; y = ty; tjemena = t;
        throw;
    }
    
}

Poligon::Poligon(std::initializer_list<std::pair<double, double>> lista):
    tjemena(lista.size()), x(nullptr), y(nullptr)
{
    if(tjemena < 3) throw std::range_error("Neispravan poligon");
    Alociraj();
    auto p = lista.begin();
    for(int i{}; i < tjemena; i++, p++){
        x[i] = p->first; y[i] = p->second;
    }
}

Poligon& Poligon::PostaviTjeme(int tjeme, double iks, double ipsilon)
{
    if(tjeme < 1 || tjeme > tjemena) throw std::range_error("Neispravan indeks");
    x[tjeme - 1] = iks; y[tjeme - 1] = ipsilon;
    return *this;
}

Poligon& Poligon::PostaviTjeme(int tjeme, std::pair<double, double> tacka)
{
    if(tjeme < 1 || tjeme > tjemena) throw std::range_error("Neispravan indeks");
    x[tjeme - 1] = tacka.first; y[tjeme - 1] = tacka.second;
    return *this;
}

std::pair<double&, double&> Poligon::operator[](int i)
{
    if(i < 1 || i > tjemena) throw std::range_error("Neispravan indeks");
    return {x[i - 1], y[i - 1]};
}

std::pair<double, double> Poligon::operator[](int i) const
{
    if(i < 1 || i > tjemena) throw std::range_error("Neispravan indeks");
    return {x[i - 1], y[i - 1]};
}

bool Poligon::operator!() const
{
    for(int i{}, j = 1; i < tjemena; i++, j++)
            if(x[i] == x[j % tjemena] && y[i] == y[j % tjemena]) 
                return true;
    return false;
}

double Poligon::DajObim() const
{
    double obim{};
    for(int i{}, j = 1; i < tjemena; i++, j++) 
        obim += sqrt((x[i] - x[j % tjemena]) * (x[i] - x[j % tjemena]) 
            + (y[i] - y[j % tjemena]) * (y[i] - y[j % tjemena]));
    return obim;
}

double Poligon::DajPovrsinu() const
{
    double povrsina{};
    for(int i{}, j = 1; i < tjemena; i++, j++)
        povrsina += (x[j % tjemena]*y[i] - x[i] * y[j % tjemena]);
    return fabs(povrsina) / 2;
}