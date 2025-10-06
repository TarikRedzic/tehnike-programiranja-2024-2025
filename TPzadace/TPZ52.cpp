#include <cmath>
#include <functional>
#include <initializer_list>
#include <iostream>

const double PI = atan(1) * 4;

class FourierovRed
{
    double* a, *b;
    int N;
    double T;
    void Alociraj(int k);
    void Dealociraj();
public:
    FourierovRed(double T, std::initializer_list<double> m, 
        std::initializer_list<double> s);
    FourierovRed(int N, double T, std::function<double(int)> f1,
        std::function<double(int)> f2);
    FourierovRed(int N, double p, double q, std::function<double(double)> f,
        int M);
    ~FourierovRed(){
        Dealociraj();
    }
    double operator()(double x);
    std::pair<double, double> operator[](int k) const;
    std::pair<double&, double&> operator[](int k);
};

int main()
{
    FourierovRed f(10, 0, 2 * PI, [](double x){return x*x;}, 100);
    FourierovRed p(10, 2 * PI, 
        [](int k){return k == 0? ((8*PI*PI) / 3) : 4. /(k*k);},
        [](int k){return (-4*PI)/k;});
    FourierovRed g(2 * PI, {26.3203, 4.00132, 1.00132, 0.445763, 0.25132, 0.161322, 0.112436, 0.0829614, 0.0638327, 0.05072},
        {-12.5622, -6.27491, -4.17638, -3.12504, -2.49257, -2.06953, -1.76616, -1.53758, -1.35886});
    std::cout<<f[4].first<<std::endl;
    std::cout<<f[4].second<<std::endl;
    std::cout<<f(3)<<std::endl;
    std::cout<<"----------\n";
    std::cout<<p[4].first<<std::endl;
    std::cout<<p[4].second<<std::endl;
    std::cout<<p(3)<<std::endl;
    std::cout<<"----------\n";
    /*for(int i = 0; i < 10; i++) std::cout<<f[i].first<<std::endl;
    std::cout<<"----------\n";
    for(int i = 0; i < 10; i++) std::cout<<f[i].second<<std::endl;*/
    std::cout<<"----------\n";
    std::cout<<g[4].first<<std::endl;
    std::cout<<g[4].second<<std::endl;
    std::cout<<g(3)<<std::endl;
    return 0;
}

void FourierovRed::Alociraj(int k)
{
    a = new double[k]();
    try
    {
        b = new double[k]();
    }
    catch(...)
    {
        delete[] a;
        throw;
    }
}

void FourierovRed::Dealociraj()
{
    delete[] a;
    delete[] b;
}

FourierovRed::FourierovRed(double T, std::initializer_list<double> m, 
        std::initializer_list<double> s): a(nullptr), b(nullptr), T(T)
{
    N = (m.size() >= s.size() + 1? m.size() : s.size() + 1);
    Alociraj(N);
    auto p = m.begin();
    auto q = s.begin();
    for(int i{}; i < m.size(); i++) a[i] = *p++;
    b[0] = 0;
    for(int i{1}; i <= s.size(); i++) b[i] = *q++;
}

FourierovRed::FourierovRed(int N, double T, std::function<double(int)> f1,
        std::function<double(int)> f2): a(nullptr), b(nullptr), T(T), N(N)
{
    if(N <= 0) throw std::domain_error("Stepen mora biti pozitivan");
    Alociraj(N);
    b[0] = 0;
    for(int i = 0; i < N; i++) a[i] = f1(i);
    for(int i = 1; i < N; i++) b[i] = f2(i);
}

//RADI NE DIRAJ NISTA
FourierovRed::FourierovRed(int N, double p, double q, std::function<double(double)> f,
        int M): a(nullptr), b(nullptr), N(N)
{
    if(q < p) throw std::range_error("Neispravan interval");
    if(N <= 0) throw std::domain_error("Stepen mora biti pozitivan");
    if(M <= 0) throw std::domain_error("Broj podintervala mora biti pozitivan");
    T = q - p;
    Alociraj(N);
    for(int k = 0; k < N; k++)
    {
        double temp = ((f(p) + f(q)) / M) * cos((2*k*PI*p) / T);
        double suma{};
        for(int i = 1; i < M; i++)
        {
            double x = p + (i * T) / M;
            //suma += f(x) * cos((2 * k * PI * x) / T);
            suma += f(x) * cos(2 * k * PI * (p / T + double(i) / M));
        }
        temp += (2 * suma) / M;
        a[k] = temp;
    }
    b[0] = 0;
    for(int k = 1; k < N; k++)
    {
        double temp = ((f(p) + f(q)) / M) * sin((2*k*PI*p) / T);
        double suma{};
        for(int i = 1; i < M; i++)
        {
            double x = p + (i * T) / M;
            //suma += f(x) * sin((2 * k * PI * x) / T);
            suma += f(x) * sin(2 * k * PI * (p / T + double(i) / M));
        }
        temp += (2 * suma) / M;
        b[k] = temp;
    }
} 

double FourierovRed::operator()(double x)
{
    double y = a[0] / 2, suma{};
    for(int k = 1; k < N ; k++)
    {
        suma += a[k] * cos((2*k*PI*x) / T);
        suma += b[k] * sin((2*k*PI*x) / T);
    }
    return y + suma;
}

std::pair<double&, double&> FourierovRed::operator[](int k)
{
    if(k < 0 || k >= N) throw std::range_error("Neispravan indeks");
    return {a[k], b[k]};
}

std::pair<double, double> FourierovRed::operator[](int k) const
{
    if(k < 0 || k >= N) throw std::range_error("Neispravan indeks");
    return {a[k], b[k]}; 
}