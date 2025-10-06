#include <cmath>
#include <iostream>

class Vektor3d {
    double x, y, z;
    public: 
    Vektor3d & Postavi(double x, double y, double z) {
        Vektor3d::x = x;
        Vektor3d::y = y;
        Vektor3d::z = z;
        return * this;
    }
    Vektor3d & PostaviX(double x) {
        Vektor3d::x = x;
        return * this;
    }
    Vektor3d & PostaviY(double y) {
        Vektor3d::y = y;
        return * this;
    }
    Vektor3d & PostaviZ(double z) {
        Vektor3d::z = z;
        return * this;
    }
    void Ocitaj(double & x, double & y, double & z) const {
        x = Vektor3d::x;
        y = Vektor3d::y;
        z = Vektor3d::z;
    }
    void Ispisi() const {
        std::cout << "{" << x << "," << y << "," << z << "}";
    }
    double DajX() const {
        return x;
    }
    double DajY() const {
        return y;
    }
    double DajZ() const {
        return z;
    }
    double DajDuzinu() const {
        return std::sqrt(x * x + y * y + z * z);
    }
    Vektor3d & PomnoziSaSkalarom(double s) {
        x *= s;
        y *= s;
        z *= s;
        return * this;
    }
    Vektor3d & SaberiSa(const Vektor3d & v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return * this;
    }
    friend Vektor3d ZbirVektora(const Vektor3d & v1,
        const Vektor3d & v2);
};

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) 
{   
    Vektor3d v3;   
    v3.x = v1.x + v2.x; v3.y = v1.y + v2.y; v3.z = v1.z + v2.z;
    return v3; 
}

int main() {
    auto NR = []() {
        std::cout << std::endl;
    };
    Vektor3d v1, v2;
    v1.Postavi(2, 5, 4);
    v1.Ispisi();
    NR(); // {2,5,4}
    double x, y, z;
    v1.Ocitaj(x, y, z);
    std::cout << x << " " << y << " " << z << std::endl; // 2 5 4
    std::cout << v1.DajX() << " " << v1.DajY() << " " << v1.DajZ() << std::endl; // 2 5 4
    v1.PostaviX(5);
    v1.PostaviY(-4);
    v1.PostaviZ(6);
    v1.Ispisi();
    NR(); // {5,-4,6}
    v1.PostaviX(3).PostaviY(0).PostaviZ(2).Ispisi();
    NR(); // {3,0,2}
    std::cout << v1.DajDuzinu() << std::endl; // 3.60555
    v2.Postavi(-8, 3, -9).Ispisi();
    NR(); // {-8,3,-9}
    v1.PomnoziSaSkalarom(3).SaberiSa(v2).PomnoziSaSkalarom(-1).Ispisi();
    NR(); // {-1,-3,3}
    v1.Ispisi();
    NR(); // {-1,-3,3}
    Vektor3d v3 = ZbirVektora(v1, v2);
    v3.Ispisi();
    NR(); // {-9,0,-6}
    ZbirVektora(v1, v2).Ispisi();
    NR(); // {-9,0,-6}
    const Vektor3d v4 = v3;
    v4.Ispisi();
    NR(); // {-9,0,-6}
    v4.Ocitaj(x, y, z);
    std::cout << x << " " << y << " " << z << std::endl; // -9 0 -6
    std::cout << v4.DajX() << " " << v4.DajY() << " " << v4.DajZ() << std::endl; // -9 0 -6
    std::cout << v4.DajDuzinu() << std::endl; // 10.8167
    return 0;
}