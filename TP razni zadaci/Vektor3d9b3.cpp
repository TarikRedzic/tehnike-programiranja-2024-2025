#include <cmath>
#include <iostream>

class Vektor3d {
    double d, phi, theta;
    public: 
    Vektor3d & Postavi(double x, double y, double z) {
        d = std::sqrt(x*x + y*y + z*z);
        theta = acos(z/d);
        phi = atan2(y, x);
        return * this;
    }
    Vektor3d & PostaviX(double x) {
        Postavi(x, DajY(), DajZ());
        return * this;
    }
    Vektor3d & PostaviY(double y) {
        Postavi(DajX(), y, DajZ());
        return * this;
    }
    Vektor3d & PostaviZ(double z) {
        Postavi(DajX(), DajY(), z);
        return * this;
    }
    void Ocitaj(double & x, double & y, double & z) const {
        x = DajX();
        y = DajY();
        z = DajZ();
    }
    void Ispisi() const {
        std::cout << "{" << DajX() << "," << DajY() << "," << DajZ() << "}";
    }
    double DajX() const {
        return d * sin(theta) * cos(phi);
    }
    double DajY() const {
        double y = d * sin(phi) * sin(theta);
        return (fabs(y) < 0.0000001 ? 0: y);
    }
    double DajZ() const {
        return d * cos(theta);
    }
    double DajDuzinu() const {
        return d;
    }
    Vektor3d & PomnoziSaSkalarom(double s) {
        double x{DajX() * s}, y{DajY() * s}, z{DajZ() * s};
        return Postavi(x, y, z);
    }
    Vektor3d & SaberiSa(const Vektor3d & w) {
        double x{DajX() + w.DajX()},
        y{DajY() + w.DajY()}, z{DajZ() + w.DajZ()};
        return Postavi(x, y, z);
    }
};

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) 
{   
    Vektor3d v3;   
    v3.Postavi(v1.DajX() + v2.DajX(), v1.DajY() + v2.DajY(), v1.DajZ() + v2.DajZ());
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