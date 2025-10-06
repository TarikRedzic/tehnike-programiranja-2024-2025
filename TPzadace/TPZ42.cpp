#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

const double PI (4*atan(1));
class NepreklapajucaKugla
{
    double x, y, z, r;
    static bool Tolerancija(double x, double y, double epsilon = 1e-10){
        return std::fabs(x - y) <= epsilon * (std::fabs(x) + std::fabs(y));
    }
    double UdaljenostOd(NepreklapajucaKugla& k);
    static NepreklapajucaKugla* posljednji;
    NepreklapajucaKugla* prije{};
    bool DaLiPreklapa();
public:
    explicit NepreklapajucaKugla(double r = 0);
    NepreklapajucaKugla(double x, double y, double z, double r = 0);
    explicit NepreklapajucaKugla(const std::tuple<double, double, double> &centar, double r = 0);
    NepreklapajucaKugla(const NepreklapajucaKugla& k) = delete;
    NepreklapajucaKugla(NepreklapajucaKugla&& k) = delete;
    NepreklapajucaKugla operator=(const NepreklapajucaKugla& k) = delete;
    NepreklapajucaKugla operator=(NepreklapajucaKugla&& k) = delete;
    ~NepreklapajucaKugla();
    double DajX() const{return x;};
    double DajY() const{return y;};
    double DajZ() const{return z;};
    std::tuple<double, double, double> DajCentar() const{
        return {DajX(), DajY(), DajZ()};
    }
    double DajPoluprecnik() const{return r;};
    double DajPovrsinu() const{return 4 * r * r * PI;};
    double DajZapreminu() const{return (4 * PI * r * r * r)/3;};
    NepreklapajucaKugla &PostaviX(double x){
        return PostaviCentar(x, DajY(), DajZ());
    }
    NepreklapajucaKugla &PostaviY(double y){
        return PostaviCentar(DajX(), y, DajZ());
    }
    NepreklapajucaKugla &PostaviZ(double z){
        return PostaviCentar(DajX(), DajY(), z);
    }
    NepreklapajucaKugla &PostaviCentar(double x, double y, double z);
    NepreklapajucaKugla &PostaviCentar(const std::tuple<double, double, double> &centar);
    NepreklapajucaKugla &PostaviPoluprecnik(double r);
    void Ispisi() const{
        std::cout<<"{("<<DajX()<<","<<DajY()<<","<<DajZ()<<"),"<<
        DajPoluprecnik()<<"}\n";
    }
    void Transliraj(double delta_x, double delta_y, double delta_z){
        PostaviCentar(DajX() + delta_x, DajY() + delta_y, DajZ() + delta_z);
    }
    bool DaLiSadrzi(const NepreklapajucaKugla &k) const;
    friend double RastojanjeCentara(const NepreklapajucaKugla &k1, const NepreklapajucaKugla &k2);
};

NepreklapajucaKugla* NepreklapajucaKugla::posljednji = nullptr;

int main()
{
    int n{};
    std::cout<<"Unesite broj kugli: ";
    do
    {
        std::cin>>n;
        if(n <= 0) std::cout<<"Neispravan broj kugli, unesite ponovo! ";
        else break;
    }
    while(true);
    
    std::vector<std::shared_ptr<NepreklapajucaKugla>> v(n, nullptr);
    for(int i{}; i < n; i++)
    {
        double x, y, z, r;
        std::cout<<"Unesite centar za "<<i+1<<". kuglu: ";
        
        do
        {
            std::cin>>x>>y>>z;
            if(!std::cin)
            {
                std::cout<<"Neispravan centar, unesite ponovo: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            else break;
        }
        while(true);
        std::cout<<"Unesite poluprecnik: ";
        do
        {
            std::cin>>r;
            if (r < 0) std::cout<<"Neispravan poluprecnik, unesite ponovo: ";
            else if(!std::cin)
            {
                std::cout<<"Neispravan poluprecnik, unesite ponovo: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            else break;
        }
        while(true);
        /*if(!std::cin)
        {
            std::cout<<"Neispravan unos\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            i--; continue;
        }*/
        try
        {
            v.at(i) = std::make_shared<NepreklapajucaKugla>(x,y,z,r);
        }
        catch(std::exception& e)
        {
            std::cout<<e.what()<<std::endl;
            v.at(i) = nullptr;
            i--; continue;
        }
    }
    std::sort(v.begin(), v.end(), [](std::shared_ptr<NepreklapajucaKugla> p1, std::shared_ptr<NepreklapajucaKugla> p2){
        return p1->DajPoluprecnik() < p2->DajPoluprecnik();
    });
    std::cout<<"Kugle nakon obavljenog sortiranja: ";
    std::for_each(v.begin(), v.end(), [](std::shared_ptr<NepreklapajucaKugla> el){
        el->Ispisi();
    });
    return 0;
}

NepreklapajucaKugla::NepreklapajucaKugla(double r): x(0), y(0), z(0), r(r)
{
    if(r < 0) throw std::domain_error("Ilegalan poluprecnik");
    if(DaLiPreklapa()) throw std::logic_error("Nedozvoljeno preklapanje");
    prije = posljednji;
    posljednji = this;
    
}

NepreklapajucaKugla::NepreklapajucaKugla(double x, double y, double z, double r)
    : x(x), y(y), z(z), r(r) 
{
    if(r < 0) throw std::domain_error("Ilegalan poluprecnik");
    if(DaLiPreklapa()) throw std::logic_error("Nedozvoljeno preklapanje");
    prije = posljednji;
    posljednji = this;
}

NepreklapajucaKugla::NepreklapajucaKugla(const std::tuple<double, double, double> &centar, double r)
: x(std::get<0>(centar)), y(std::get<1>(centar)), z(std::get<2>(centar)), r(r)
{
    if(r < 0) throw std::domain_error("Ilegalan poluprecnik");
    if(DaLiPreklapa()) throw std::logic_error("Nedozvoljeno preklapanje");
    prije = posljednji;
    posljednji = this;
}

bool NepreklapajucaKugla::DaLiPreklapa()
{
    auto temp = posljednji;
    while(temp != nullptr) {
        if(this != temp && (DaLiSadrzi(*temp) || UdaljenostOd(*temp) < r + temp->DajPoluprecnik() ||
        Tolerancija(UdaljenostOd(*temp), r + temp->DajPoluprecnik())))
            return true;
        temp = temp->prije;
    }
    return false;
}

bool NepreklapajucaKugla::DaLiSadrzi(const NepreklapajucaKugla &k) const
{
    return (x + r >= k.DajX() + k.DajPoluprecnik() &&
            x - r <= k.DajX() - k.DajPoluprecnik() &&
            y + r >= k.DajY() + k.DajPoluprecnik() &&
            y - r <= k.DajY() - k.DajPoluprecnik() &&
            z + r >= k.DajZ() + k.DajPoluprecnik() &&
            z - r <= k.DajZ() - k.DajPoluprecnik());
}

double RastojanjeCentara(const NepreklapajucaKugla &k1, const NepreklapajucaKugla &k2)
{
    double dx{k1.DajX() - k2.DajX()}, dy{k1.DajY() - k2.DajY()},
    dz{k1.DajZ() - k2.DajZ()};
    return sqrt(dx * dx + dy * dy + dz * dz);
}

double NepreklapajucaKugla::UdaljenostOd(NepreklapajucaKugla& k)
{
    double dx{x - k.DajX()}, dy{y - k.DajY()},
    dz{z - k.DajZ()};
    return sqrt(dx * dx + dy * dy + dz * dz);
}

NepreklapajucaKugla& NepreklapajucaKugla::PostaviCentar(double x, double y, double z)
{
    //NepreklapajucaKugla(x, y, z, r);
    double staro_x = this->x, staro_y = this->y, staro_z = this->z;
    this->x = x; this->y = y; this->z = z;
    if(DaLiPreklapa())
    {
        this->x = staro_x; this->y = staro_y; this->z = staro_z;
        throw std::logic_error("Nedozvoljeno preklapanje");
    }
    return *this;
}

NepreklapajucaKugla& NepreklapajucaKugla::PostaviCentar(const std::tuple<double, double, double> &centar)
{
    //NepreklapajucaKugla(std::get<0>(centar), std::get<1>(centar), std::get<2>(centar), DajPoluprecnik());
    double staro_x = this->x, staro_y = this->y, staro_z = this->z;
    this->x = std::get<0>(centar); this->y = std::get<1>(centar); 
    this->z = std::get<2>(centar);
    if(DaLiPreklapa())
    {
        this->x = staro_x; this->y = staro_y; this->z = staro_z;
        throw std::logic_error("Nedozvoljeno preklapanje");
    }
    return *this;
}

NepreklapajucaKugla& NepreklapajucaKugla::PostaviPoluprecnik(double r)
{
    if(r < 0) throw std::domain_error("Ilegalan poluprecnik");
    double staro_r = this->r;
    this->r = r;
    if(DaLiPreklapa())
    {
        this->r = staro_r;
        throw std::logic_error("Nedozvoljeno preklapanje");
    }
    return *this;
}

NepreklapajucaKugla::~NepreklapajucaKugla()
{
    auto pr = posljednji;
    if(pr == this) posljednji = prije;
    else
    {
        while(pr->prije != this) pr = pr->prije;
        pr->prije = prije;
    }
}