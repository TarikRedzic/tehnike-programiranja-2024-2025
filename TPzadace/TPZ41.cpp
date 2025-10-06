#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

const double PI (4*atan(1));
class Kugla
{
    double x, y, z, r;
    static bool Tolerancija(double x, double y, double epsilon = 1e-10){
        return std::fabs(x - y) <= epsilon * (std::fabs(x) + std::fabs(y));
    }
    static bool Dodir(const Kugla &k1, const Kugla &k2){
        if(Kugla::Tolerancija(RastojanjeCentara(k1, k2),
            fabs(k1.DajPoluprecnik() - k2.DajPoluprecnik()))) return true;
        return false;
    }
public:
    explicit Kugla(double r = 0){
        PostaviPoluprecnik(r); PostaviX(0);
        PostaviY(0); PostaviZ(0);
    }
    Kugla(double x, double y, double z, double r = 0){
        PostaviPoluprecnik(r); PostaviX(x);
        PostaviY(y); PostaviZ(z);
    }
    explicit Kugla(const std::tuple<double, double, double> &centar, double r = 0){
        PostaviPoluprecnik(r); PostaviX(std::get<0>(centar));
        PostaviY(std::get<1>(centar)); PostaviZ(std::get<2>(centar));
    }
    double DajX() const{return x;};
    double DajY() const{return y;};
    double DajZ() const{return z;};
    std::tuple<double, double, double> DajCentar() const{
        return {DajX(), DajY(), DajZ()};
    }
    double DajPoluprecnik() const{return r;};
    double DajPovrsinu() const{return 4 * r * r * PI;};
    double DajZapreminu() const{return (4 * PI * r * r * r)/3;};
    Kugla &PostaviX(double x){
        Kugla::x = x; return *this;
    }
    Kugla &PostaviY(double y){
        Kugla::y = y; return *this;
    }
    Kugla &PostaviZ(double z){
        Kugla::z = z; return *this;
    }
    Kugla &PostaviCentar(double x, double y, double z){
        PostaviX(x); PostaviY(y); PostaviZ(z); return *this;
    }
    Kugla &PostaviCentar(const std::tuple<double, double, double> &centar){
        PostaviX(std::get<0>(centar));PostaviY(std::get<1>(centar));
        PostaviZ(std::get<2>(centar)); return *this;
    }
    Kugla &PostaviPoluprecnik(double r){
        if(r < 0) throw std::domain_error("Ilegalan poluprecnik");
        Kugla::r = r; return *this;
    }
    void Ispisi() const{
        std::cout<<"{("<<DajX()<<","<<DajY()<<","<<DajZ()<<"),"<<
        DajPoluprecnik()<<"}\n";
    }
    void Transliraj(double delta_x, double delta_y, double delta_z){
        PostaviX(DajX() + delta_x); PostaviY(DajY() + delta_y);
        PostaviZ(DajZ() + delta_z);
    }
    friend bool DaLiSuIdenticne(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSuPodudarne(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSuKoncentricne(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSeDodirujuIzvana(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSeDodirujuIznutra(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSePreklapaju(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSeSijeku(const Kugla &k1, const Kugla &k2);
    bool DaLiSadrzi(const Kugla &k) const;
    friend double RastojanjeCentara(const Kugla &k1, const Kugla &k2);
};

int main()
{
    int n{};
    std::cout<<"Unesite broj kugla: ";
    std::cin>>n;
    std::vector<std::shared_ptr<Kugla>> v(n, nullptr);
    for(int i{}; i < n; i++)
    {
        double x, y, z, r;
        std::cout<<"Unesite centar "<<i+1<<". kugle: ";
        std::cin>>x>>y>>z;
        std::cout<<"Unesite poluprecnik "<<i+1<<". kugle: ";
        std::cin>>r;
        if(!std::cin)
        {
            std::cout<<"Neispravan unos\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            i--; continue;
        }
        try
        {
            v.at(i) = std::make_shared<Kugla>(Kugla({x,y,z}, r));
        }
        catch(std::exception& e)
        {
            std::cout<<e.what()<<std::endl;
            i--; continue;
        }
    }
        std::cout<<"Unesite parametre translacije (delta_x,delta_y,delta_z): ";
        double dx, dy, dz;
        std::cin>>dx>>dy>>dz;
        std::transform(v.begin(), v.end(), v.begin(), [&](std::shared_ptr<Kugla> el){
            el->Transliraj(dx, dy, dz);
            return el;
        });
        std::sort(v.begin(), v.end(), [](std::shared_ptr<Kugla> p1, std::shared_ptr<Kugla> p2){
            return p1->DajPoluprecnik() < p2->DajPoluprecnik();
        });
        std::cout<<"Kugle nakon obavljenje transformacije imaju sljedece vrijednosti: ";
        std::for_each(v.begin(), v.end(), [](std::shared_ptr<Kugla> el){
            el->Ispisi();
        });
        std::cout<<"Kugla sa najvecom povrsinom je: ";
        auto temp = std::max_element(v.begin(), v.end(), [](std::shared_ptr<Kugla> p1, std::shared_ptr<Kugla> p2){
            return p1->DajPoluprecnik() < p2->DajPoluprecnik();
        });
        (*temp)->Ispisi();
        int pr{}, i{};
        std::for_each(v.begin(), v.end(), [&](std::shared_ptr<Kugla> p1){
            i++;
            std::for_each(v.begin() + i, v.end(), [&p1, &pr](std::shared_ptr<Kugla> p2){
                if(DaLiSeSijeku(*p1, *p2)){
                    std::cout<<"Presjecaju se kugle: ";
                    p1->Ispisi(); p2->Ispisi();
                    pr++;
                } 
            });
        });
        if(!pr) std::cout<<"Ne postoje kugle koje se presjecaju!";
    return 0;
}

bool DaLiSuIdenticne(const Kugla &k1, const Kugla &k2)
{
    if(DaLiSuPodudarne(k1, k2) && DaLiSuKoncentricne(k1, k2))
        return true;
    return false;
}
bool DaLiSuPodudarne(const Kugla &k1, const Kugla &k2)
{
    if(Kugla::Tolerancija(k1.DajPoluprecnik(), k2.DajPoluprecnik())) return true;
    return false;
}

bool DaLiSuKoncentricne(const Kugla &k1, const Kugla &k2)
{
    if(Kugla::Tolerancija(k1.DajX(), k2.DajX()) &&
        Kugla::Tolerancija(k1.DajY(), k2.DajY()) &&
        Kugla::Tolerancija(k1.DajZ(), k2.DajZ())) return true;
    return false;
}

double RastojanjeCentara(const Kugla &k1, const Kugla &k2)
{
    double dx{k1.DajX() - k2.DajX()}, dy{k1.DajY() - k2.DajY()},
    dz{k1.DajZ() - k2.DajZ()};
    return sqrt(dx * dx + dy * dy + dz * dz);
}

bool DaLiSeDodirujuIzvana(const Kugla &k1, const Kugla &k2)
{
    if(!(Kugla::Tolerancija(RastojanjeCentara(k1, k2),
            fabs(k1.DajPoluprecnik() + k2.DajPoluprecnik()))) || DaLiSuIdenticne(k1, k2)) return false;
    bool veci(k1.DajPoluprecnik() > k2.DajPoluprecnik());
    return veci ? (k1.DajPoluprecnik() <= RastojanjeCentara(k1, k2)):
                (k2.DajPoluprecnik() <= RastojanjeCentara(k1, k2));
}

bool DaLiSeDodirujuIznutra(const Kugla &k1, const Kugla &k2)
{
    if(!(Kugla::Tolerancija(RastojanjeCentara(k1, k2),
            fabs(k1.DajPoluprecnik() - k2.DajPoluprecnik()))) || DaLiSuIdenticne(k1, k2)) return false;
    bool veci(k1.DajPoluprecnik() > k2.DajPoluprecnik());
    return veci ? (k1.DajPoluprecnik() >= RastojanjeCentara(k1, k2)):
                (k2.DajPoluprecnik() >= RastojanjeCentara(k1, k2));
}

bool DaLiSePreklapaju(const Kugla &k1, const Kugla &k2)
{
    if(k1.DajPoluprecnik() > k2.DajPoluprecnik() ? k1.DaLiSadrzi(k2):
        k2.DaLiSadrzi(k1)) return true;
    if(DaLiSeSijeku(k1, k2)) return true;
    return false;
}

bool Kugla::DaLiSadrzi(const Kugla &k) const
{
    return (DajX() + DajPoluprecnik() >= k.DajX() + k.DajPoluprecnik() &&
            DajX() - DajPoluprecnik() <= k.DajX() - k.DajPoluprecnik() &&
            DajY() + DajPoluprecnik() >= k.DajY() + k.DajPoluprecnik() &&
            DajY() - DajPoluprecnik() <= k.DajY() - k.DajPoluprecnik() &&
            DajZ() + DajPoluprecnik() >= k.DajZ() + k.DajPoluprecnik() &&
            DajZ() - DajPoluprecnik() <= k.DajZ() - k.DajPoluprecnik());
}

bool DaLiSeSijeku(const Kugla &k1, const Kugla &k2)
{
    if((fabs(k1.DajPoluprecnik() - k2.DajPoluprecnik()) < RastojanjeCentara(k1, k2)) &&
        (RastojanjeCentara(k1, k2) < k1.DajPoluprecnik() + k2.DajPoluprecnik()) &&
        !(DaLiSeDodirujuIzvana(k1, k2) && DaLiSeDodirujuIznutra(k1, k2))) 
        return true;
    return false;

}