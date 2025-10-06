#include <iostream>
#include <set>
#include <map>

template <typename T> 
    std::set<T> operator+(const std::set<T>& skup1, const std::set<T>& skup2)
{
    std::set<T> novi;
    for(auto p = skup1.begin(); p != skup1.end(); p++)
        novi.insert(*p);
    for(auto q = skup2.begin(); q != skup2.end(); q++)
        novi.insert(*q);
    return novi;
}

template <typename T> 
    const std::set<T> operator*(const std::set<T>& skup1, const std::set<T>& skup2)
{
    std::set<T> novi;
    for(auto p = skup1.begin(); p != skup1.end(); p++)
        for(auto q = skup2.begin(); q != skup2.end(); q++)
            if(*p == *q) novi.insert(*p);
    return novi;
}

template <typename Tip1, typename Tip2>
    std::set<std::pair<Tip1, Tip2>> operator%(const std::set<Tip1>& skup1, const std::set<Tip2>& skup2)
{
    std::set<std::pair<Tip1, Tip2>> novi;
    for(auto p = skup1.begin(); p != skup1.end(); p++)
        for(auto q = skup2.begin(); q != skup2.end(); q++)
            novi.insert(std::make_pair(*p, *q));
    return novi;
}

template <typename T> 
    const std::set<T> operator+=(std::set<T>& skup1, const std::set<T>& skup2)
{
    std::set<T> novi;
    for(auto p = skup1.begin(); p != skup1.end(); p++)
        novi.insert(*p);
    for(auto q = skup2.begin(); q != skup2.end(); q++)
        novi.insert(*q);
    skup1 = novi;
    return skup1;
}

template <typename T> 
    const std::set<T> operator*=(std::set<T>& skup1, const std::set<T>& skup2)
{
    std::set<T> novi;
    for(auto p = skup1.begin(); p != skup1.end(); p++)
        for(auto q = skup2.begin(); q != skup2.end(); q++)
            if(*p == *q) novi.insert(*p);
    skup1 = novi;
    return skup1;
}

template <typename TipElemenata>
    std::ostream &operator <<(std::ostream &tok, const std::set<TipElemenata> &s) 
{
    tok << "{";
    auto it = s.begin();
    while(it != s.end()) {
    tok << *it++;
    if(it != s.end()) tok << ",";
    }
    return tok << "}";
}

template <typename Tip1, typename Tip2>
    std::ostream& operator<<(std::ostream& tok, const std::pair<Tip1, Tip2>& par)
{
    tok<<"("<<par.first<<","<<par.second<<")";
    return tok;
}

int main()
{
    std::set<int> s1{3, 5, 1, 2, 8}, s2{7, 2, 8, 4};
    std::cout << s1 + s2 << std::endl; // {1,2,3,4,5,7,8}
    std::cout << s1 * s2 << std::endl; // {2,8}
    std::cout << s1 * std::set<int>{10, 20, 30} << std::endl; // {}
    s1 += s2;
    std::cout << s1 << std::endl; // {1,2,3,4,5,7,8}
    s1 *= std::set<int>{3, 4, 9};
    std::cout << s1 << std::endl; // {3,4}
    std::set<char> s3{'A', 'B'};
    std::set<int> s4{1, 2, 3};
    std::cout << s3 % s4 << std::endl; // {(A,1),(A,2),(A,3),(B,1),(B,2),(B,3)}
    return 0;
}

