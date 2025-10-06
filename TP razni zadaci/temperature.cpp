#include <algorithm>
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>

struct Mjerenje {
    int dan, mjesec, godina;
    std::string komentar;
    int min_t, max_t;
    double prosjek;
};

int main()
{
    std::ifstream fajl("TEMPERATURE.TXT");
    if(!fajl){
        std::cout<<"Fajl ne postoji!"; return 1;
    }
    Mjerenje m;
    char znak;
    std::vector<Mjerenje> mjerenja;
    while(fajl >> m.dan >> znak >> m.mjesec >> znak >> m.godina)
    {
        fajl.ignore(10000, '\n');
        std::getline(fajl, m.komentar);
        m.min_t = INT_MAX; m.max_t = INT_MIN;
        int br{};
        m.prosjek = 0;
        do
        {
            int temp;
            fajl>>temp;
            m.prosjek += temp; br++;
            if(temp > m.max_t) m.max_t = temp;
            if(temp < m.min_t) m.min_t = temp;
            if(fajl.peek() != ',') break;
            fajl.get();
        }
        while(true);
        m.prosjek /= br;
        mjerenja.push_back(m);
    }
    std::sort(mjerenja.begin(), mjerenja. end(), 
        [](const Mjerenje& m1, const Mjerenje& m2){
            if(m1.godina != m2.godina) return m1.godina < m2.godina;
            if(m1.mjesec != m2.mjesec) return m1.mjesec < m2.mjesec;
            if(m1.dan != m2.dan) return m1.dan < m2.dan;
            return m1.prosjek < m2.prosjek;
        });
    std::ofstream cou("IZVJESTAJ.TXT");
    for(int i = 0; i < mjerenja.size(); i++)
    {
        cou<<mjerenja.at(i).komentar<<std::endl;
        cou<<std::string(mjerenja.at(i).komentar.size(), '-')<<std::endl;
        cou<<"Datum mjerenja: "<<mjerenja.at(i).dan<<"/"<<
            mjerenja.at(i).mjesec<<"/"<<mjerenja.at(i).godina<<std::endl;
        cou<<"Minimalna temperatura: "<<mjerenja.at(i).min_t<<std::endl;
        cou<<"Maksimalna temperatura: "<<mjerenja.at(i).max_t<<std::endl;
        cou<<"Prosjecna temperatura: "<<mjerenja.at(i).prosjek<<std::endl;
        endl(cou);
    }

    return 0;
}
