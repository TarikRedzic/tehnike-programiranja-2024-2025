#include <iostream>
#include <stack>

template <typename T>
    std::ostream& operator<<(std::ostream& tok, std::stack<T> s)
{
    while(!s.empty())
    {
        tok<<s.top()<<" "; s.pop();
    }
    return tok;
}

template <typename Tip1, typename Tip2>
    auto operator-(std::stack<Tip1> s1, std::stack<Tip2> s2)
{
    if(s1.size() != s2.size()) throw std::domain_error("Stekovi razlicite velicine!");
    std::stack<decltype(s1.top() - s2.top())> novi;
    while(!s1.empty())
    {
        novi.push(s1.top() - s2.top());
        s1.pop(); s2.pop();
    }
    return novi;
}

template <typename T, typename Tip>
    std::stack<T>& operator*=(std::stack<T>& stek, Tip d)
{
    std::stack<T> back;
    while(!stek.empty())
    {
        back.push(stek.top() * d); stek.pop();
    }
    while(!back.empty())
    {
        stek.push(back.top()); back.pop();
    }
    
}

template <typename T>
    bool operator*(std::stack<T> s)
{
    return !s.empty();
}

int main()
{
    int niz1[]{1, 5, 7, 3}, niz2[]{1, 9, 0, 4};
    std::stack<int> q1, q2;
    for(auto i : niz1) q1.push(i);
    for(auto i : niz2) q2.push(i);
    std::cout << q2 << std::endl; // 4 0 9 1 (od vrha ka dnu...)
    std::cout << q1 - q2 << std::endl; // 0 -4 7 -1 (obrnut poredak!)
    q2.push(10);
    try {
    std::cout << q1 - q2;
    }
    catch(std::domain_error e) {
    std::cout << e.what() << std::endl; // Stekovi razlicite velicine!
    }
    q1 *= 3;
    std::cout << q1 << std::endl; // 9 21 15 3
    if(*q1) std::cout << "Nije prazan";
    else std::cout << "Prazan";

    return 0;
}
