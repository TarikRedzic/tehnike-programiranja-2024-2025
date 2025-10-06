#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

class Temperature
{
    std::list<int> nize, vise;
    int najniza, najvisa;
public:
    Temperature(int min, int max);
    void RegistrirajTemperature(std::pair<int, int> par);
    void BrisiSve(){nize.clear(); vise.clear();};
    void BrisiNegativneTemperature();
    int DajBrojRegistriranihTemperatura() const{return nize.size();};
    int DajMinimalnuTemperaturu() const{
        if(nize.size() == 0) throw std::logic_error("Nema registriranih temperatura");
        return *(std::min_element(nize.begin(), nize.end()));
    }
    int DajMaksimalnuTemperaturu() const{
        if(vise.size() == 0) throw std::logic_error("Nema registriranih temperatura");
        return *(std::max_element(vise.begin(), vise.end()));
    }
    int DajBrojTemperaturaVecihOd(int temp) const;
    int DajBrojTemperaturaManjihOd(int temp) const;
    bool operator!() const{
        return !vise.size();
    }
    Temperature& operator++();
    Temperature operator++(int);
    Temperature& operator--();
    Temperature operator--(int);
    std::vector<int> operator*();
    std::vector<int> operator-();
    std::vector<int> operator+();
    std::pair<int, int> operator[](int p);
    friend Temperature operator+(Temperature X, int Y);
    friend Temperature operator-(Temperature X, int Y);
    friend Temperature operator+(int Y, Temperature X);
    friend Temperature operator-(int Y, Temperature X); 
    Temperature& operator+=(int Y);
    Temperature& operator-=(int Y);
    friend bool operator ==(const Temperature& t1, const Temperature& t2);
    friend bool operator !=(const Temperature& t1, const Temperature& t2);
    friend std::ostream& operator<<(std::ostream& tok, Temperature t);
    template <typename Tip>
        friend Temperature operator+(Temperature X, Tip Y) = delete;
    template <typename Tip> 
        friend Temperature operator-(Temperature X, Tip Y) = delete;
};

int main()
{
    Temperature h(-10, 20);
    h.RegistrirajTemperature({11, 15});
    h.RegistrirajTemperature({-3, -1});
    h.RegistrirajTemperature({13, 17});
    h.RegistrirajTemperature({-4, 0});
    h.RegistrirajTemperature({-5, -3});
    h.RegistrirajTemperature({-1, 3});
    auto v = -h;
    auto u = *h;
    Temperature m = h + 2; 
    Temperature k = h - 1;
    for(int i: v) std::cout<<i<<"  --  ";
    endl(std::cout);
    for(int i: u) std::cout<<i<<"  --  ";
    endl(std::cout);
    std::cout<<"M: \n"<<m<<std::endl;
    std::cout<<"K: \n"<<k<<std::endl;
    std::cout<<"H: \n"<<h<<std::endl;
    h.BrisiNegativneTemperature();
    std::cout<<"H: \n"<<h<<std::endl;
    
    return 0;
}

Temperature::Temperature(int min, int max)
{
    if(min > max) throw std::range_error("Nekorektne temperature");
    najniza = min; najvisa = max;
}

void Temperature::RegistrirajTemperature(std::pair<int, int> par)
{
    if(par.first < najniza || par.second > najvisa || par.first > par.second) 
        throw std::range_error("Nekorektne temperature");
    vise.push_back(par.second); nize.push_back(par.first);
}

void Temperature::BrisiNegativneTemperature()
{
    std::vector<std::pair<int, int>> v, v2;;
    std::vector<int> tempv(vise.begin(), vise.end());
    std::vector<int> tempn(nize.begin(), nize.end());
    std::transform(tempn.begin(), tempn.end(), tempv.begin(), std::back_inserter(v),
        std::bind(std::make_pair<const int&, const int&>, std::placeholders::_1, std::placeholders::_2));
    std::remove_copy_if(v.begin(), v.end(), std::back_inserter(v2),
        std::bind(std::logical_and<bool>(),
            std::bind(std::less<int>(),
                std::bind(&std::pair<int, int>::first, std::placeholders::_1), 0),
            std::bind(std::less<int>(),
                std::bind(&std::pair<int, int>::second, std::placeholders::_1), 0)));
    nize.clear(); vise.clear();
    std::transform(v2.begin(), v2.end(), std::back_inserter(nize),
        std::bind(&std::pair<int, int>::first, std::placeholders::_1));
    std::transform(v2.begin(), v2.end(), std::back_inserter(vise),
        std::bind(&std::pair<int, int>::second, std::placeholders::_1));
}

int Temperature::DajBrojTemperaturaVecihOd(int temp) const
{
    if(!vise.size()) throw std::logic_error("Nema registriranih temperatura");
    return std::count_if(vise.begin(), vise.end(), 
        std::bind(std::greater<int>(), std::placeholders::_1, temp));

}

int Temperature::DajBrojTemperaturaManjihOd(int temp) const
{
    if(!nize.size()) throw std::logic_error("Nema registriranih temperatura");
    return std::count_if(nize.begin(), nize.end(), 
        std::bind(std::less<int>(), std::placeholders::_1, temp));
}

Temperature& Temperature::operator++()
{
    std::vector<int> v(nize.size(), 1);
    std::transform(nize.begin(), nize.end(), v.begin(), v.begin(), std::plus<int>());
    if (!std::equal(v.begin(), v.end(), vise.begin(), std::less_equal<int>()))
        throw std::logic_error("Ilegalna operacija");
    std::copy(v.begin(), v.end(), nize.begin());
    return *this;
}

Temperature Temperature::operator++(int)
{
    Temperature temp(najniza, najvisa);
    temp.nize.assign(nize.begin(), nize.end());
    temp.vise.assign(vise.begin(), vise.end());
    operator++();
    return temp;
}

Temperature& Temperature::operator--()
{
    std::vector<int> v(vise.size(), 1);
    std::transform(vise.begin(), vise.end(), v.begin(), v.begin(), std::minus<int>());
    if (!std::equal(v.begin(), v.end(), nize.begin(), std::greater_equal<int>()))
        throw std::logic_error("Ilegalna operacija");
    std::copy(v.begin(), v.end(), vise.begin());
    return *this;
}

Temperature Temperature::operator--(int)
{
    Temperature temp(najniza, najvisa);
    temp.nize.assign(nize.begin(), nize.end());
    temp.vise.assign(vise.begin(), vise.end());
    operator--();
    return temp;
}

std::pair<int, int> Temperature::operator[](int p)
{
    if(p < 1 || p > nize.size())
        throw std::range_error("Neispravan indeks");
    std::vector<int> v(nize.size());
    std::copy(nize.begin(), nize.end(), v.begin());
    int prvi = v.at(p - 1);
    std::copy(vise.begin(), vise.end(), v.begin());
    int drugi = v.at(p - 1);
    return {prvi, drugi};
}

std::vector<int> Temperature::operator*()
{
    std::vector<int> razlika(vise.begin(), vise.end());
    std::transform(razlika.begin(), razlika.end(), nize.begin(), razlika.begin(), std::minus<int>());
    return razlika;
}

Temperature operator+(Temperature X, int Y)
{
    std::vector<int> s(X.nize.size(), Y);
    std::transform(X.vise.begin(), X.vise.end(), s.begin(), X.vise.begin(), std::plus<int>());
    if (std::any_of(X.vise.begin(), X.vise.end(), 
        std::bind(std::greater<int>(), std::placeholders::_1, X.najvisa)))
            throw std::logic_error("Prekoracen dozvoljeni opseg temperatura");
    std::transform(X.nize.begin(), X.nize.end(), s.begin(), X.nize.begin(), std::plus<int>());
    return X;    
}

Temperature operator+(int Y, Temperature X)
{
    return X + Y;
}

Temperature operator-(Temperature X, int Y)
{
    std::vector<int> s(X.nize.size(), Y);
    std::transform(X.nize.begin(), X.nize.end(), s.begin(), X.nize.begin(), std::minus<int>());
    if (std::any_of(X.nize.begin(), X.nize.end(), 
        std::bind(std::less<int>(), std::placeholders::_1, X.najniza)))
            throw std::logic_error("Prekoracen dozvoljeni opseg temperatura");
    std::transform(X.vise.begin(), X.vise.end(), s.begin(), X.vise.begin(), std::minus<int>());
    return X;
}

Temperature operator-(int Y, Temperature X)
{
    Temperature novi(X.najniza, X.najvisa);
    std::vector<int> v(X.nize.size(), Y);
    novi.nize.assign(X.vise.begin(), X.vise.end());
    novi.vise.assign(X.nize.begin(), X.nize.end());
    std::transform(novi.vise.begin(), novi.vise.end(), novi.vise.begin(), 
        std::bind(std::minus<int>(), Y, std::placeholders::_1));
    std::transform(novi.nize.begin(), novi.nize.end(), novi.nize.begin(), 
        std::bind(std::minus<int>(), Y, std::placeholders::_1));
    if (std::any_of(novi.nize.begin(), novi.nize.end(), 
        std::bind(std::less<int>(), std::placeholders::_1, novi.najniza)))
            throw std::logic_error("Prekoracen dozvoljeni opseg temperatura");
    if (std::any_of(novi.vise.begin(), novi.vise.end(), 
        std::bind(std::greater<int>(), std::placeholders::_1, novi.najvisa)))
            throw std::logic_error("Prekoracen dozvoljeni opseg temperatura");
    return novi;
}

bool operator ==(const Temperature& t1, const Temperature& t2)
{
    if(t1.najvisa != t2.najvisa ||
        t1.najniza != t2.najniza) return false;
    if(t1.nize.size() == 0 && t2.nize.size() == 0) return true;
    if(t1.nize.size() != t2.nize.size())
        return false;
    if(!std::equal(t1.vise.begin(), t1.vise.end(), t2.vise.begin(), t2.vise.end())) return false;
    if(!std::equal(t1.nize.begin(), t1.nize.end(), t2.nize.begin(), t2.nize.end())) return false;
    return true;
}

bool operator !=(const Temperature& t1, const Temperature& t2)
{
    return !(t1 == t2);
}

Temperature& Temperature::operator+=(int Y)
{
    return *this = *this + Y;
}

Temperature& Temperature::operator-=(int Y)
{
    return *this = *this - Y;
}

std::vector<int> Temperature::operator-()
{
    std::vector<int> razlika(nize.size());
    std::transform(nize.begin(), nize.end(), razlika.begin(),
        std::bind(std::minus<int>(), std::placeholders::_1, najniza));
    return razlika;
}

std::vector<int> Temperature::operator+()
{
    std::vector<int> razlika(nize.size());
    std::transform(vise.begin(), vise.end(), razlika.begin(),
        std::bind(std::minus<int>(), std::placeholders::_1, najvisa));
    return razlika;
}

std::ostream& operator<<(std::ostream& tok, Temperature t)
{
    std::copy(t.nize.begin(), t.nize.end(), std::ostream_iterator<int>(tok, " "));
    tok<<" "<<std::endl;
    std::copy(t.vise.begin(), t.vise.end(), std::ostream_iterator<int>(tok, " "));
    return tok<<" "<<std::endl;
}