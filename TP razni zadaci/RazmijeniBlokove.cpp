#include <iostream>
#include <list>
#include <vector>

template <typename It1, typename It2> 
    void RazmijeniBlokove(It1 p1, It1 k1, It2 p2)
{
    int vel{};
    for(auto t = p1; t != k1; vel++, t++);
    for(; p1 != k1; p1++, p2++)
    {
        auto t = *p1;
        *p1 = *p2;
        *p2 = t;
    }
}

int main()
{
    std::vector<int> v{1,2,3,4,5};
    std::list<int> l{2,2,1,0,1};
    RazmijeniBlokove(v.begin(), v.end(), l.begin());
    for(auto s: v){std::cout<<s<<" ";};
    endl(std::cout);
    for(auto s: l){std::cout<<s<<" ";};
    return 0;
}
