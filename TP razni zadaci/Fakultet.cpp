#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

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

class Fakultet
{
    std::vector<ApstraktniStudent*> studenti;
    void Dealociraj();
public:
    Fakultet() = default;
    ~Fakultet();
    Fakultet(const Fakultet& f);
    Fakultet(Fakultet&& f): studenti(std::move(f.studenti)){};
    Fakultet& operator=(const Fakultet& f);
    Fakultet operator=(Fakultet&& f){
        Dealociraj(); studenti = std::move(f.studenti); return *this;
    }
    void UpisiStudenta(std::string ime, std::string prezime, int indeks);
    void UpisiStudenta(std::string ime, std::string prezime, int indeks,
        int godina_dipl);
    void ObrisiStudenta(int indeks);
    ApstraktniStudent& operator[](int indeks);
    const ApstraktniStudent& operator[](int indeks) const;
    void IspisiSveStudente() const;
};

template <typename TipIzuzetka, typename FunkcijskiTip>
    void TestirajIzuzetak(FunkcijskiTip akcija) 
{
    try { akcija(); }
    catch(TipIzuzetka &e) { std::cout << e.what() << std::endl; }
}

int main()
{
    Fakultet f1;
    f1.UpisiStudenta("Meho", "Mehic", 3412);
    f1.UpisiStudenta("Ibro", "Ibric", 3124, 2015);
    f1.UpisiStudenta("Pero", "Peric", 1243);
    f1.IspisiSveStudente();
    TestirajIzuzetak<std::logic_error>([&]() { f1.UpisiStudenta("Drugi", "Drugic", 3412); });
    f1[3412].RegistrirajIspit(7); f1[3412].RegistrirajIspit(9);
    f1[3124].RegistrirajIspit(9); f1[3124].RegistrirajIspit(10);
    f1[1243].RegistrirajIspit(8);
    f1.IspisiSveStudente();
    TestirajIzuzetak<std::logic_error>([&]() { f1[9876].IspisiPodatke(); });
    f1.ObrisiStudenta(3412);
    f1.IspisiSveStudente();
    TestirajIzuzetak<std::logic_error>([&]() { f1.ObrisiStudenta(6789); });
    Fakultet f2 = f1;
    f2.IspisiSveStudente();
    Fakultet f3 = std::move(f1);
    f3.IspisiSveStudente();
    f3.UpisiStudenta("Ivan", "Ivanic", 4312, 2016);
    f2 = f3;
    f2.IspisiSveStudente();
    f3.ObrisiStudenta(4312);
    f2 = f3;
    f2.IspisiSveStudente();
    f2 = std::move(f3);
    f2.IspisiSveStudente();
    const Fakultet f4 = f2;
    f4.IspisiSveStudente();
    f4[3124].IspisiPodatke();
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

Fakultet::~Fakultet()
{
    Dealociraj();
}

void Fakultet::Dealociraj()
{
    for(int i = 0; i < studenti.size(); i++)
        delete studenti.at(i);
    studenti.resize(0);
}

Fakultet::Fakultet(const Fakultet& f)
{
    studenti.resize(f.studenti.size());
    try
    {
        for(int i = 0; i < f.studenti.size(); i++)
            studenti.at(i) = f.studenti.at(i)->DajKopiju();
    }
    catch(const std::exception& e)
    {
        Dealociraj();
        throw;
    }
}

Fakultet& Fakultet::operator=(const Fakultet& f)
{
    Dealociraj();
    studenti.resize(f.studenti.size());
    try
    {
        for(int i = 0; i < f.studenti.size(); i++)
            studenti.at(i) = f.studenti.at(i)->DajKopiju();
    }
    catch(const std::exception& e)
    {
        Dealociraj();
        throw;
    }
    return *this;
}

void Fakultet::UpisiStudenta(std::string ime, std::string prezime, int indeks)
{
    for(int i = 0; i < studenti.size(); i++) 
        if(studenti.at(i)->DajBrojIndeksa() == indeks)
            throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
    studenti.push_back(new StudentBachelor(ime, prezime, indeks));
}

void Fakultet::UpisiStudenta(std::string ime, std::string prezime, int indeks,
        int godina_dipl)
{
    for(int i = 0; i < studenti.size(); i++) 
        if(studenti.at(i)->DajBrojIndeksa() == indeks)
            throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
    studenti.push_back(new StudentMaster(ime, prezime, indeks, godina_dipl));
}

void Fakultet::ObrisiStudenta(int indeks)
{
    for(auto p = studenti.begin(); p != studenti.end(); p++)
        if((*p)->DajBrojIndeksa() == indeks)
        {
            studenti.erase(p);
            return;
        }
    throw std::logic_error("Student sa zadanim brojem indeksa ne postoji"); 
}

ApstraktniStudent& Fakultet::operator[](int indeks)
{
    for(auto p = studenti.begin(); p != studenti.end(); p++)
        if((*p)->DajBrojIndeksa() == indeks)
            return **p;
    throw std::logic_error("Student sa zadanim brojem indeksa ne postoji"); 
}

const ApstraktniStudent& Fakultet::operator[](int indeks) const
{
    for(auto p = studenti.begin(); p != studenti.end(); p++)
        if((*p)->DajBrojIndeksa() == indeks)
            return **p;
    throw std::logic_error("Student sa zadanim brojem indeksa ne postoji"); 
}

void Fakultet::IspisiSveStudente() const
{
    auto temp = studenti;
    std::sort(temp.begin(), temp.end(), 
        [](ApstraktniStudent* s1, ApstraktniStudent* s2){
            if(s1->DajProsjek() == s2->DajProsjek()) 
                return s1->DajBrojIndeksa() < s2->DajBrojIndeksa();
            return s1->DajProsjek() > s2->DajProsjek();
        });
    for(auto p = temp.begin(); p != temp.end(); p++)
        (*p)->IspisiPodatke(), endl(std::cout);
}