#include <cmath>
#include <iostream>

class Vektor3d {
    double v[3];
    public: 
    Vektor3d & Postavi(double x, double y, double z) {
        v[0] = x;
        v[1] = y;
        v[2] = z;
        return * this;
    }
    Vektor3d & PostaviX(double x) {
        v[0] = x;
        return * this;
    }
    Vektor3d & PostaviY(double y) {
        v[1] = y;
        return * this;
    }
    Vektor3d & PostaviZ(double z) {
        v[2] = z;
        return * this;
    }
    void Ocitaj(double & x, double & y, double & z) const {
        x = v[0];
        y = v[1];
        z = v[2];
    }
    void Ispisi() const {
        std::cout << "{" << v[0] << "," << v[1] << "," << v[2] << "}";
    }
    double DajX() const {
        return v[0];
    }
    double DajY() const {
        return v[1];
    }
    double DajZ() const {
        return v[2];
    }
    double DajDuzinu() const {
        return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }
    Vektor3d & PomnoziSaSkalarom(double s) {
        v[0] *= s;
        v[1] *= s;
        v[2] *= s;
        return * this;
    }
    Vektor3d & SaberiSa(const Vektor3d & w) {
        v[0] += w.v[0];
        v[1] += w.v[1];
        v[2] += w.v[2];
        return * this;
    }
    friend Vektor3d ZbirVektora(const Vektor3d & v1,
        const Vektor3d & v2);
};

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) 
{   
    Vektor3d v3;   
    v3.v[0] = v1.v[0] + v2.v[0]; v3.v[1] = v1.v[1] + v2.v[1]; v3.v[2] = v1.v[2] + v2.v[2];
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