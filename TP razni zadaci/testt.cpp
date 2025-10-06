#include <iostream>

#include <iostream>
class Foo {
    int x, y;
public:
    Foo() { std::cout << "A" << std::endl; x = 1; y = 2; }
    Foo(int x, int y) { std::cout << "B" << std::endl; Foo::x = x; Foo::y = y; }
    void Modify(int z) { x *= z; y *= z; }
    int GetX() { return x + 10; }
    int GetY() { return y - 5; }
    void Display() { std::cout << x + y << " " << x - y << std::endl; }
};
class Bar {
    int x;
    Foo y;
public:
    Bar(int y) { std::cout << "C" << std::endl; x = y; }
    Bar(int x, int y, int z) : y(x, z) { std::cout << "D" << std::endl; Bar::x = y; }
    int GetX() { return x; }
    Foo GetY() { return y; }
    void Display() { std::cout << x << std::endl; y.Display(); }
};
int main() {
    Foo a; Foo b(3, 2);
    std::cout << a.GetX() << " " << a.GetY() << std::endl;
    std::cout << b.GetX() << " " << b.GetY() << std::endl;
    a.Display(); b.Display();
    Foo c = a;
    c.Modify(2);
    a.Display(); c.Display();
    Bar d(2); Bar e(1, 5, 3);
    std::cout << d.GetX() << " " << d.GetY().GetX() << " " << d.GetY().GetY() << std::endl;
    e.Display();
    Foo f[4]; Foo g[3]{Foo(3, 2), Foo(1, 1), Foo(2, 2)};
    f[2].Display(); g[1].Display();
    Foo *p, *q;
    p = new Foo(10, 10); q = p;
    q->Modify(3); p->Display();
    return 0;
}

