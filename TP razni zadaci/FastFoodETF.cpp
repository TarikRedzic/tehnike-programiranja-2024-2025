#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
class Obrok 
{
    std::string naziv;
    double cijena;
    std::string narucioc;
public:
    Obrok(std::string naziv, double cijena, std::string narucioc) :
        naziv(naziv), cijena(cijena), narucioc(narucioc) {}
    std::string DajNazivObroka() const { return naziv; }
    double DajCijenuObroka() const { return cijena; }
    virtual double DajUkupnuCijenu() const {return DajCijenuObroka();}
    std::string DajNarucioca() const { return narucioc; }
    virtual void Ispisi() const {
        std::cout << narucioc << " je narucio " << naziv << " i treba platiti "
        << cijena << " KM.\n";
    }
    virtual Obrok* DajKopiju(){return new Obrok(*this);}
};

class ObrokSaPicem: public Obrok
{
    std::string naziv_pica;
    double cijena_pica;
public:
    ObrokSaPicem(std::string naziv, double cijena, std::string narucioc,
        std::string naziv_pica, double cijena_pica): Obrok(naziv, cijena, narucioc),
            naziv_pica(naziv_pica), cijena_pica(cijena_pica){}
    std::string DajNazivPica() const{return naziv_pica;}
    double DajCijenuPica() const{return cijena_pica;}
    inline double DajUkupnuCijenu() const{return cijena_pica + DajCijenuObroka();}
    void Ispisi() const override{
        std::cout << DajNarucioca() << " je narucio " << DajNazivObroka()
        <<" i "<<naziv_pica<< " i treba platiti "
        << this->DajUkupnuCijenu() << " KM.\n";
        std::cout<<"Pice: "<<cijena_pica<<"\n";
    }
    ObrokSaPicem* DajKopiju(){return new ObrokSaPicem(*this);}
};

class Narudzbe 
{
    int broj_narudzbi, kapacitet;
    Obrok **obroci;
public:
    Narudzbe() : broj_narudzbi(0), kapacitet(20), obroci(new Obrok*[kapacitet]()) {}
    ~Narudzbe() { 
        for(int i = 0; i < broj_narudzbi; i++) delete obroci[i];
        delete[] obroci; 
    }
    Narudzbe(const Narudzbe &n) : broj_narudzbi(n.broj_narudzbi),
    kapacitet(n.kapacitet), obroci(new Obrok*[kapacitet]) {
        for(int i = 0; i < broj_narudzbi; i++) obroci[i] = n.obroci[i]->DajKopiju();
    }
    Narudzbe(Narudzbe&& n){
        std::swap(kapacitet, n.kapacitet); std::swap(broj_narudzbi, n.broj_narudzbi);
        std::swap(obroci, n.obroci);
    }
    Narudzbe &operator =(const Narudzbe &n) = delete;
    void NaruciObrokSaPicem(std::string naziv, double cijena, std::string narucioc,
        std::string naziv_pica, double cijena_pica)
    {
        if(broj_narudzbi == kapacitet)
        {
            auto temp = new Obrok*[kapacitet += 20]();
            std::copy(obroci, obroci + broj_narudzbi, temp);
            delete[] obroci; obroci = temp; temp = nullptr;
        }
        obroci[broj_narudzbi++] = new ObrokSaPicem(naziv, cijena, narucioc,
                naziv_pica, cijena_pica);
    }
    void NaruciObrok(std::string naziv, double cijena, std::string narucioc) {
        if(broj_narudzbi == kapacitet)
        {
            auto temp = new Obrok*[kapacitet += 20]();
            std::copy(obroci, obroci + broj_narudzbi, temp);
            delete[] obroci; obroci = temp; temp = nullptr;
        }
        obroci[broj_narudzbi++] = new Obrok(naziv, cijena, narucioc);
    }
    const Obrok &operator[] (int redni_broj) const {
        return *obroci[redni_broj];
    }
    bool operator!(){return !broj_narudzbi;}
    friend Narudzbe operator+(Narudzbe n1, Narudzbe n2){
        auto temp = new Obrok*[n1.kapacitet + n2.kapacitet];
        for(int i = 0; i < n1.broj_narudzbi; i++) temp[i] = n1.obroci[i]->DajKopiju();
        for(int i = 0; i < n2.broj_narudzbi; i++) 
            temp[i + n1.broj_narudzbi] = n2.obroci[i]->DajKopiju();
        delete[] n1.obroci; n1.obroci = temp; temp = nullptr;
        n1.kapacitet += n2.kapacitet; n1.broj_narudzbi += n2.broj_narudzbi;
    }
    double operator()(const std::string& s){
        int br{};
        for(int i = 0; i < broj_narudzbi; i++)
            if(obroci[i]->DajNarucioca() == s) br += obroci[i]->DajUkupnuCijenu();
        return br;
    }
    void UcitajIzDatoteka(std::string dat1, std::string dat2);
};



int main() 
{
    Narudzbe etf_fast_food;
    etf_fast_food.NaruciObrok("burek", 2.5, "Brus Li");
    etf_fast_food.UcitajIzDatoteka("narudzbe.txt", "cjenovnik.txt");
    for(int i = 0; i < 5; i++)
        etf_fast_food[i].Ispisi();
    return 0;
}

void Narudzbe::UcitajIzDatoteka(std::string imena, std::string cijene)
{
    std::ifstream osobe(imena), iznosi(cijene);
    std::string per, food, pice{};
    double cijena_pica, cijena_hrane;
    while(std::getline(osobe, per))
    {
        std::getline(osobe, food);
        std::getline(osobe, pice);
        /*if(osobe.peek() != '\n')
        {
            std::getline(osobe, pice);
            std::string temp;
            double t;
            while(std::getline(iznosi, temp))
            {
                if(temp == pice){
                    iznosi>>cijena_pica; break;
                }
                else iznosi>>t;
                iznosi.ignore(10000, '\n');
            }
            if(iznosi.eof()) throw std::logic_error("Nema odgovarajuce cijene");
            if(iznosi.fail()) throw std::logic_error("Problemi sa citanjem");
        }
        //treba dodat kod da trazi cijenu hrane*/
        iznosi.seekg(0, std::ios::beg);
        std::string temp;
        double t;
        bool oba = false; if(pice != std::string{})oba = true;
        while(std::getline(iznosi, temp))
        {
            std::cout<<temp<<std::endl;
            if(temp == food){
                iznosi>>cijena_hrane; std::cout<<cijena_hrane<<std::endl;
                if(oba) break; else oba = true;
            }
            else if(temp == pice && pice != std::string{}){
                iznosi>>cijena_pica; std::cout<<cijena_pica<<std::endl;
                if(oba) break; else oba = true;
            }
            else {iznosi>>t; }
            iznosi.ignore(10000, '\n');
        }
        if(iznosi.eof()) throw std::logic_error("Nema odgovarajuce cijene");
        if(iznosi.fail()) throw std::logic_error("Problemi sa citanjem");
        if(pice != std::string{}) NaruciObrokSaPicem(food, cijena_hrane, per,
            pice, cijena_pica);
        NaruciObrok(food, cijena_hrane, per);
    }
}