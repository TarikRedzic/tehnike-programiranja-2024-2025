#include <algorithm>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <deque>

template <typename Tip1, typename Tip2>
class AsocijativniNiz
{
    std::deque<std::pair<Tip1, Tip2>> niz;
public:
    AsocijativniNiz(std::initializer_list<std::pair<Tip1, Tip2>> lista);
    ~AsocijativniNiz(){
        niz.clear();
    }
    Tip2& operator[](const Tip1& first);
    const Tip2& operator[](const Tip1& first) const;
    auto begin(){
        return niz.begin();
    }
    auto end(){
        return niz.end();
    }
    std::pair<Tip1, Tip2>& operator++();
};

int main()
{
   AsocijativniNiz<std::string, int> stanovnistvo{{"Sarajevo", 450000}, {"Mostar", 100000},
    {"Banja Luka", 230000}, {"Bihac", 50000}};
    std::cout << stanovnistvo["Sarajevo"] << std::endl;
    int razlika = stanovnistvo["Banja Luka"] - stanovnistvo["Mostar"];
    stanovnistvo["Tuzla"] = 120000;
    for(auto e : stanovnistvo) std::cout << e.first << ": " << e.second << std::endl;
        return 0;
}

template <typename Tip1, typename Tip2>
Tip2& AsocijativniNiz<Tip1, Tip2>::operator[](const Tip1& first)
{
    for(auto& e:niz){
        if(e.first == first) return e.second;
    }
    niz.push_back({first, Tip2()});
    return niz.back().second;
}

template <typename Tip1, typename Tip2>
    const Tip2 &AsocijativniNiz<Tip1, Tip2>::operator[](const Tip1 &kljuc) const {
    for(const auto &e : niz)
    if(e.first == kljuc) return e.second;
    throw std::range_error("Kljuc nije nadjen!");
}
template <typename Tip1, typename Tip2>
AsocijativniNiz<Tip1, Tip2>::AsocijativniNiz(std::initializer_list<std::pair<Tip1, Tip2>> lista)
{
    for(auto e: lista){niz.push_back({e.first, e.second});};
}