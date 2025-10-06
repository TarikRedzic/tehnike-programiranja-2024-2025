#include <iostream>
#include <map>
#include <string>


struct Student
{
    int broj_indeksa{};
    std::string ime{};
    std::string prezime{};
    int godina_studija{};
    std::string adresa{};
    std::string telefon{};
};

class Knjiga
{
    std::string naslov, ime_pisca, zanr;
    int godina_izdavanja;
    Student* zaduzio;
public:
    Knjiga(std::string naslov, std::string ime_pisca, std::string zanr,
        int godina_izdavanja): zaduzio(nullptr), naslov(naslov), ime_pisca(ime_pisca),
        zanr(zanr), godina_izdavanja(godina_izdavanja){};
    std::string DajNaslov()const{return naslov;};
    std::string DajAutora()const{return ime_pisca;};
    std::string DajZanr()const{return zanr;};
    int DajGodinuIzdavanja()const{return godina_izdavanja;};
    void ZaduziKnjigu(Student& s){zaduzio = &s;};
    void RazduziKnjigu(){zaduzio = nullptr;};
    bool DaLiJeZaduzena(){return zaduzio != nullptr;};
    const Student& DajKodKogaJe();
    Student* DajPokKodKogaJe(){return zaduzio;};
};

class Biblioteka
{
    std::map<int, Student*> clanovi;
    std::map<int, Knjiga*> evidencija;
    static void IspisiStudenta(const Student& s);
    void Ocisti();
public:
    Biblioteka() = default;
    Biblioteka(const Biblioteka& b);
    Biblioteka(Biblioteka&& b);
    Biblioteka& operator=(const Biblioteka& b);
    Biblioteka& operator=(Biblioteka&& b);
    ~Biblioteka();
    void RegistrirajNovogStudenta(int indeks, std::string ime, std::string prezime,
        int godina_studija, std::string adresa, std::string broj_telefona);
    void RegistrirajNovuKnjigu(int ev_broj, std::string naslov, std::string ime_pisca,
        std::string zanr, int godina_izdavanja);
    Student& NadjiStudenta(int indeks);
    Knjiga& NadjiKnjigu(int indeks);
    void IzlistajStudente() const;
    void IzlistajKnjige() const;
    void ZaduziKnjigu(int ev_broj, int indeks);
    void RazduziKnjigu(int ev_broj);
    void PrikaziZaduzenja(int indeks);
};

int main()
{
    int a{-1}; Biblioteka bib;
    std::cout<<"1. Registruj novog studenta\n"<<
                "2. Registruj novu knjigu\n"<<
                "3. Pronadji studenta\n"<<
                "4. Pronadji knjigu\n"<<
                "5. Izlistaj sve studente\n"<<
                "6. Izlistaj sve knjige\n"<<
                "7. Zaduzi knjigu\n"<<
                "8. Razduzi knjigu\n"<<
                "9. Prikazi zaduzenja studenta\n"<<
                "0. Kraj\n";
    do
    {
        std::cout<<"Odaberite opciju: ";
        std::cin>>a;
        int indeks, godina_studija, ev_broj, godina_izdanja;
        std::string ime, prezime, adresa, telefon, naslov, zanr, autor;

        switch (a)
        {
        case 1:
            std::cout<<"Unesite broj indeksa: ";
            std::cin>>indeks; std::cin.ignore(10000, '\n');
            std::cout<<"Unesite ime: ";
            std::getline(std::cin, ime);
            std::cout<<"Unesite prezime: ";
            std::getline(std::cin, prezime);
            std::cin.clear();
            std::cout<<"Unesite godinu studija: ";
            std::cin>>godina_studija; std::cin.ignore(10000, '\n');
            std::cout<<"Unesite adresu: ";
            std::getline(std::cin, adresa);
            std::cout<<"Unesite broj telefona: ";
            std::getline(std::cin, telefon);
            std::cin.clear();
            try
            {
                bib.RegistrirajNovogStudenta(indeks, ime, prezime, godina_studija, adresa, telefon);
                std::cout<<"Student uspjesno registrovan.\n";
            }
            catch(std::exception& e)
            {
                std::cout<<"Greska: "<<e.what()<<std::endl;
            }
            break;
        case 2:
            std::cout<<"Unesite evidencijski broj knjige: ";
            std::cin>>ev_broj; std::cin.ignore(10000, '\n');
            std::cout<<"Unesite naslov knjige: ";
            std::getline(std::cin, naslov);
            std::cout<<"Unesite ime pisca: ";
            std::getline(std::cin, autor);
            std::cout<<"Unesite zanr: ";
            std::getline(std::cin, zanr); std::cin.clear();
            std::cout<<"Unesite godinu izdavanja: ";
            std::cin>>godina_izdanja; std::cin.ignore(10000, '\n');
            try
            {
                bib.RegistrirajNovuKnjigu(ev_broj, naslov, autor, zanr, godina_izdanja);
                std::cout<<"Knjiga uspjesno registrovana.\n";
            }
            catch(std::exception& e)
            {
                std::cout<<"Greska: "<<e.what()<<std::endl;
            }
            break;
        case 3:
            std::cout<<"Unesite broj indeksa studenta: ";
            std::cin>>indeks;
            try
            {
                auto& s = bib.NadjiStudenta(indeks);
                std::cout<<"Podaci o studentu:";
                std::cout<<"\nBroj indeksa: "<<indeks<<
                "\nIme i prezime: "<<s.ime<<" "<<s.prezime<<
                "\nGodina studija: "<<s.godina_studija<<
                "\nAdresa: "<<s.adresa<<
                "\nBroj telefona: "<<s.telefon<<std::endl;
            }
            catch(const std::exception& e)
            {
                std::cout << e.what() << '\n';
            }
            break;
        case 4:
            std::cout<<"Unesite evidencijski broj knjige: ";
            std::cin>>ev_broj;
            try
            {
                auto& s = bib.NadjiKnjigu(ev_broj);
                std::cout<<"Podaci o knjizi: ";
                std::cout<<"\nEvidencijski broj: "<<ev_broj<<
                "\nNaslov: "<<s.DajNaslov()<<
                "\nPisac: "<<s.DajAutora()<<
                "\nZanr: "<<s.DajZanr()<<
                "\nGodina izdavanja: "<<s.DajGodinuIzdavanja()<<std::endl;
                if(s.DajPokKodKogaJe() != nullptr)
                {
                    auto p = s.DajPokKodKogaJe();
                    std::cout<<"Zaduzena kod studenta: "<<p->ime<<" "<<p->prezime
                        <<" ("<<p->broj_indeksa<<")\n";
                }
            }
            catch(const std::exception& e)
            {
                std::cout << e.what() << '\n';
            }
            break;
        case 5:
            std::cout<<"Lista studenata";
            bib.IzlistajStudente();
            break;
        case 6:
            std::cout<<"Lista knjiga";
            bib.IzlistajKnjige();
            break;
        case 7:
            std::cout<<"Unesite evidencijski broj knjige: ";
            std::cin>>ev_broj;
            std::cout<<"Unesite broj indeksa studenta: ";
            std::cin>>indeks;
            try
            {
                bib.ZaduziKnjigu(ev_broj, indeks);
                std::cout<<"Knjiga je uspjesno zaduzena.\n";
            }
            catch(const std::exception& e)
            {
                std::cout << e.what() << '\n';
            }
            break;
        case 8:
            std::cout<<"Unesite evidencijski broj knjige: ";
            std::cin>>ev_broj;
            try
            {
                bib.RazduziKnjigu(ev_broj);
                std::cout<<"Knjiga je uspjesno razduzena.\n";
            }
            catch(const std::exception& e)
            {
                std::cout << e.what() << '\n';
            }
            break;
        case 9:
            std::cout<<"Unesite broj indeksa studenta: ";
            std::cin>>indeks;
            std::cout<<"Zaduzenja studenta (ako ih ima): ";
            bib.PrikaziZaduzenja(indeks);
            break;
        case 0:
            std::cout<<"Kraj.\n";
            return 0;
        default:
            std::cout<<"Neispravna opcija. Pokušajte ponovo.\n";
        }
        endl(std::cout);
    }
    while(a != 0);
    return 0;
}

const Student& Knjiga::DajKodKogaJe()
{
    if(zaduzio == nullptr) throw std::domain_error("Knjiga nije zaduzena");
    return *zaduzio;
}

void Biblioteka::Ocisti()
{
    for(auto& par: clanovi) {delete par.second; par.second = nullptr;}
    for(auto& par: evidencija) {delete par.second; par.second = nullptr;}
    evidencija.clear();
    clanovi.clear();
}

Biblioteka::Biblioteka(const Biblioteka& b)
{
    std::map<int, Knjiga*> nova_evidencija;
    std::map<int, Student*> novi_clanovi;
    try
    {
        for(auto& par: b.evidencija)
        {
            std::pair<int, Knjiga*> n;
            n.first = par.first; n.second = new Knjiga(*par.second);
            nova_evidencija.insert(n); n.second = nullptr;
        }
    }
    catch(const std::exception& e)
    {
        for(auto& par: nova_evidencija) delete par.second;
        throw;
    }
    try
    {
        for(auto& par: b.clanovi)
        {
            std::pair<int, Student*> n;
            n.first = par.first; n.second = new Student(*par.second);
            novi_clanovi.insert(n); n.second = nullptr;
        }

    }
    catch(const std::exception& e)
    {
        for(auto& par: novi_clanovi) delete par.second;
        throw;
    }
    evidencija = nova_evidencija;
    clanovi = novi_clanovi;
}

Biblioteka::Biblioteka(Biblioteka&& b)
{
    for(auto& par: b.evidencija)
    {
        std::pair<int, Knjiga*> n;
        n.first = par.first; n.second = par.second;
        evidencija.insert(n); par.second = nullptr;
    }
    for(auto& par: b.clanovi)
    {
        std::pair<int, Student*> n;
        n.first = par.first; n.second = par.second;
        clanovi.insert(n); par.second = nullptr;
    }
    b.Ocisti();
}

Biblioteka& Biblioteka::operator=(const Biblioteka& b)
{
    std::map<int, Knjiga*> nova_evidencija;
    std::map<int, Student*> novi_clanovi;
    try
    {
        for(auto& par: b.evidencija)
        {
            std::pair<int, Knjiga*> n;
            n.first = par.first; n.second = new Knjiga(*par.second);
            nova_evidencija.insert(n);
        }
    }
    catch(const std::exception& e)
    {
        for(auto& par: nova_evidencija) {delete par.second;
        par.second = nullptr;} nova_evidencija.clear();
        throw;
    }
    try
    {
        for(auto& par: b.clanovi)
        {
            std::pair<int, Student*> n;
            n.first = par.first; n.second = new Student(*par.second);
            novi_clanovi.insert(n); n.second = nullptr;
        }
    }
    catch(const std::exception& e)
    {
        for(auto& par: nova_evidencija) {delete par.second;
        par.second = nullptr;} novi_clanovi.clear();
        throw;
    }
    for(const auto& par : b.evidencija) {
        if(par.second->DaLiJeZaduzena()) {
            int indeks = par.second->DajKodKogaJe().broj_indeksa;
            auto it_knjiga = nova_evidencija.find(par.first);
            auto it_student = novi_clanovi.find(indeks);
            if(it_knjiga != nova_evidencija.end() && it_student != novi_clanovi.end())
                it_knjiga->second->ZaduziKnjigu(*(it_student->second));
        }
    }
    Ocisti();
    evidencija = nova_evidencija;
    clanovi = novi_clanovi;
    return *this;
}

Biblioteka& Biblioteka::operator=(Biblioteka&& b)
{
    Ocisti();
    for(auto& par: b.evidencija)
    {
        std::pair<int, Knjiga*> n;
        n.first = par.first; n.second = par.second;
        par.second = nullptr;
        evidencija.insert(n);
    }
    for(auto& par: b.clanovi)
    {
        std::pair<int, Student*> n;
        n.first = par.first; n.second = par.second;
        par.second = nullptr;
        clanovi.insert(n);
    }
    return *this;
}

Biblioteka::~Biblioteka()
{
    Ocisti();
}

void Biblioteka::RegistrirajNovogStudenta(int indeks, std::string ime, std::string prezime,
        int godina_studija, std::string adresa, std::string broj_telefona)
{
    auto pretraga = clanovi.find(indeks);
    if(pretraga == clanovi.end()) clanovi.insert({indeks,
        new Student{indeks,  ime, prezime, godina_studija, adresa, broj_telefona}});
    else throw std::logic_error("Vec postoji student s tim brojem indeksa");
}

void Biblioteka::RegistrirajNovuKnjigu(int ev_broj, std::string naslov, std::string ime_pisca,
        std::string zanr, int godina_izdavanja)
{
    auto pretraga = evidencija.find(ev_broj);
    if(pretraga == evidencija.end()) evidencija.insert({ev_broj,
        new Knjiga{naslov, ime_pisca, zanr, godina_izdavanja}});
    else throw std::logic_error("Knjiga s tim evidencijskim brojem vec postoji");
}

Student& Biblioteka::NadjiStudenta(int indeks)
{
    auto pretraga = clanovi.find(indeks);
    if(pretraga == clanovi.end()) throw std::logic_error("Student nije nadjen");
    return *(pretraga->second);
}

Knjiga& Biblioteka::NadjiKnjigu(int indeks)
{
    auto pretraga = evidencija.find(indeks);
    if(pretraga == evidencija.end()) throw std::logic_error("Knjiga nije nadjena");
    return *(pretraga->second);
}

void Biblioteka::IzlistajStudente() const
{
    for(auto& par: clanovi)
    {
        if(par.second != nullptr)
        {
            std::cout<<"Broj indeksa: "<<par.first<<std::endl;
            std::cout<<"Ime i prezime: "<<par.second->ime<<" "<<par.second->prezime<<
            "\nGodina studija: "<<par.second->godina_studija<<
            "\nAdresa: "<<par.second->adresa<<
            "\nBroj telefona: "<<par.second->telefon<<std::endl;
        }
    }
}

void Biblioteka::IzlistajKnjige() const
{
    for(auto par: evidencija)
    {
        std::cout<<"\nEvidencijski broj: "<<par.first<<
        "\nNaslov: "<<par.second->DajNaslov()<<
        "\nPisac: "<<par.second->DajAutora()<<
        "\nZanr: "<<par.second->DajZanr()<<
        "\nGodina izdavanja: "<<par.second->DajGodinuIzdavanja()<<std::endl;
        if(par.second->DajPokKodKogaJe() != nullptr)
        {
            auto p = par.second->DajPokKodKogaJe();
            std::cout<<"Zaduzena kod studenta: "<<p->ime<<" "<<p->prezime
                <<" ("<<p->broj_indeksa<<")\n";
        }
    }
}

void Biblioteka::ZaduziKnjigu(int ev_broj, int indeks)
{
    try
    {
        Knjiga& k = NadjiKnjigu(ev_broj);
        if(k.DaLiJeZaduzena()) throw std::logic_error("Knjiga vec zaduzena");
        Student& s = NadjiStudenta(indeks);
        k.ZaduziKnjigu(s);
    }
    catch(const std::logic_error& e)
    {
        if(std::string(e.what()) == "Knjiga nije nadjena") throw std::logic_error("Knjiga nije nadjena");
        else if(std::string(e.what())  == "Student nije nadjen") throw std::logic_error("Student nije nadjen");
        else throw;
    }
}

void Biblioteka::RazduziKnjigu(int ev_broj)
{
    Knjiga& k = NadjiKnjigu(ev_broj);
    if(!k.DaLiJeZaduzena()) throw std::logic_error("Knjiga nije zaduzena");
    k.RazduziKnjigu();
}

void Biblioteka::PrikaziZaduzenja(int indeks)
{
    try
    {
        const Student& s = NadjiStudenta(indeks);
        int i{};
        for(auto par: evidencija)
        {
            if(par.second->DajPokKodKogaJe() == &s)
            {
                std::cout<<"\nEvidencijski broj: "<<par.first<<
                "\nNaslov: "<<par.second->DajNaslov()<<
                "\nPisac: "<<par.second->DajAutora()<<
                "\nZanr: "<<par.second->DajZanr()<<
                "\nGodina izdavanja: "<<par.second->DajGodinuIzdavanja()<<std::endl;
                i++;
            }
        }
        if(!i) std::cout<<"\nNema zaduzenja za tog studenta!\n";
    }
    catch(const std::exception& e)
    {
        throw std::logic_error("Student nije nadjen");
    }
}
