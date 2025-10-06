#include <iostream>

class ApstraktniStudent
{
    std::string ime, prezime;
    int indeks;
    int br_polozenih;
    double prosjek;
public:
    ApstraktniStudent(std::string ime, std::string prezime, int indeks):
        ime(ime), prezime(prezime), indeks(indeks){
            PonistiOcjene();
        }
    virtual ~ApstraktniStudent() = default;
    std::string DajIme() const{ return ime;}
    std::string DajPrezime() const{ return prezime;}
    int DajBrojIndeksa() const{ return indeks;}
    int DajBrojPolozenih() const{return br_polozenih;}
    double DajProsjek() const{return prosjek;}
    void RegistrirajIspit(int ocjena);
    void PonistiOcjene(){
        br_polozenih = 0; prosjek = 5;
    }
    virtual void IspisiPodatke() const = 0;
    virtual ApstraktniStudent* DajKopiju() = 0;
};

class StudentBachelor: public ApstraktniStudent
{
public:
    StudentBachelor(std::string ime, std::string prezime, int indeks):
        ApstraktniStudent(ime, prezime, indeks){}
    void IspisiPodatke() const override;
    StudentBachelor* DajKopiju() override;
};

class StudentMaster: public ApstraktniStudent
{
    int godina_dipl;
public:
    StudentMaster(std::string ime, std::string prezime, int indeks,
        int godina_dipl): ApstraktniStudent(ime, prezime, indeks),
            godina_dipl(godina_dipl){}
    StudentMaster* DajKopiju() override;
    void IspisiPodatke() const override;
};

template <typename TipIzuzetka, typename FunkcijskiTip>
    void TestirajIzuzetak(FunkcijskiTip akcija) 
{
    try { akcija(); }
    catch(TipIzuzetka &e) { std::cout << e.what() << std::endl; }
}

int main()
{
    StudentBachelor s1("Dusko", "Dugousko", 1234);
    s1.RegistrirajIspit(7); s1.RegistrirajIspit(6); s1.RegistrirajIspit(5);
    s1.RegistrirajIspit(10); s1.RegistrirajIspit(7);
    std::cout << s1.DajIme() << " " << s1.DajPrezime() << " " << s1.DajBrojIndeksa()
    << " " << s1.DajBrojPolozenih() << " " << s1.DajProsjek() << std::endl;
    s1.IspisiPodatke();
    TestirajIzuzetak<std::domain_error>([&]() { s1.RegistrirajIspit(4); });
    TestirajIzuzetak<std::domain_error>([&]() { s1.RegistrirajIspit(11); });
    s1.PonistiOcjene();
    std::cout << s1.DajIme() << " " << s1.DajPrezime() << " " << s1.DajBrojIndeksa()
    << " " << s1.DajBrojPolozenih() << " " << s1.DajProsjek() << std::endl;
    s1.IspisiPodatke();
    StudentMaster s2("Paja", "Patak", 4312, 2015);
    s2.RegistrirajIspit(7); s2.RegistrirajIspit(6); s2.RegistrirajIspit(5);
    s2.RegistrirajIspit(10); s2.RegistrirajIspit(7);
    std::cout << s2.DajIme() << " " << s2.DajPrezime() << " " << s2.DajBrojIndeksa()
    << " " << s2.DajBrojPolozenih() << " " << s2.DajProsjek() << std::endl;
    s2.IspisiPodatke();
    TestirajIzuzetak<std::domain_error>([&]() { s2.RegistrirajIspit(4); });
    TestirajIzuzetak<std::domain_error>([&]() { s2.RegistrirajIspit(11); });
    s2.PonistiOcjene();
    std::cout << s2.DajIme() << " " << s2.DajPrezime() << " " << s2.DajBrojIndeksa()
    << " " << s2.DajBrojPolozenih() << " " << s2.DajProsjek() << std::endl;
    s2.IspisiPodatke();
    ApstraktniStudent *ps = new StudentBachelor("Dusko", "Dugousko", 1234);
    ps->RegistrirajIspit(7); ps->RegistrirajIspit(6); ps->RegistrirajIspit(5);
    ps->RegistrirajIspit(10); ps->RegistrirajIspit(7);
    std::cout << ps->DajIme() << " " << ps->DajPrezime() << " " << ps->DajBrojIndeksa()
    << " " << ps->DajBrojPolozenih() << " " << ps->DajProsjek() << std::endl;
    ps->IspisiPodatke();
    ApstraktniStudent *pskopija = ps->DajKopiju();
    pskopija->IspisiPodatke();
    delete ps; delete pskopija;
    ps = new StudentMaster("Paja", "Patak", 4312, 2015);
    ps->RegistrirajIspit(7); ps->RegistrirajIspit(6); ps->RegistrirajIspit(5);
    ps->RegistrirajIspit(10); ps->RegistrirajIspit(7);
    std::cout << ps->DajIme() << " " << ps->DajPrezime() << " " << ps->DajBrojIndeksa()
    << " " << ps->DajBrojPolozenih() << " " << ps->DajProsjek() << std::endl;
    ps->IspisiPodatke();
    pskopija = ps->DajKopiju(); pskopija->IspisiPodatke();
    delete ps; delete pskopija;
    return 0;

}

void ApstraktniStudent::RegistrirajIspit(int ocjena)
{
    if(ocjena == 5) return;
    else if(ocjena < 5 || ocjena > 10) 
        throw std::domain_error("Neispravna ocjena");
    prosjek = ((prosjek * br_polozenih) + ocjena) / (br_polozenih + 1);
    br_polozenih++;
}

void StudentBachelor::IspisiPodatke() const
{
    std::cout<<"Student bachelor studija "<<DajIme()<<" "
        <<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()
        <<", ima prosjek "<<DajProsjek()<<".\n";
}

void StudentMaster::IspisiPodatke() const
{
    std::cout<<"Student master studija "<<DajIme()<<" "
        <<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()
        <<", zavrsio bachelor studij godine "<<godina_dipl
        <<", ima prosjek "<<DajProsjek()<<".\n";
}

StudentBachelor* StudentBachelor::DajKopiju()
{
    return new StudentBachelor(*this);
}

StudentMaster* StudentMaster::DajKopiju()
{
    return new StudentMaster(*this);
}