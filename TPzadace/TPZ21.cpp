//TP 2024/2025: Zadaća 2, Zadatak 1
#include <array>
#include <iostream>
#include <limits>
#include <string>

namespace Robot
{
    enum class Smjer {Sjever, Sjeveroistok, Istok, Jugoistok, Jug, Jugozapad, Zapad,
    Sjeverozapad};
    enum class SmjerRotacije {Nalijevo, Nadesno};
    enum class KodoviGresaka {PogresnaKomanda, NedostajeParametar, SuvisanParametar,
    NeispravanParametar};
    enum class Komande {Aktiviraj, Deaktiviraj, Nalijevo, Nadesno, Idi, Kraj};
    // Ovdje će ići i deklaracije raznih pomoćnih stvari koje će Vam trebati za
    // potrebe implementacije robota...
    bool status = true;
    int x{}, y{};
    Smjer orijentacija{};
    std::string GdjeJeOkrenut(Smjer smjer = orijentacija);
    bool Kretanje_Sjever(int korak); bool Kretanje_Istok(int korak);
    bool Kretanje_Jug(int korak); bool Kretanje_Zapad(int korak);
    bool (*Pomjeri[4])(int korak){Kretanje_Sjever, Kretanje_Istok, Kretanje_Jug, Kretanje_Zapad};

    bool Aktiviraj();
    bool Deaktiviraj();
    void Rotiraj(SmjerRotacije na_koju_stranu, int za_koliko = 1);
    bool Idi(int korak = 1);
    void IspisiPoziciju();
    std::array<int, 2> OcitajPoziciju();
    Smjer OcitajOrijentaciju();
    void PrijaviGresku(KodoviGresaka kod_greske);
    bool IzvrsiKomandu(Komande komanda, int parametar = 0);
    bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske);
}

int main()
{
    while(true)
    {
        Robot::Komande k{};
        int p{1};
        Robot::KodoviGresaka g{};
        if(Robot::UnosKomande(k, p, g)) Robot::IzvrsiKomandu(k, p);
        else Robot::PrijaviGresku(g);
        if(k == Robot::Komande::Kraj) break;
    }
    std::cout<<"Dovidjenja!\n";
    return 0;
}

bool Robot::Aktiviraj()
{
    //if(Robot::status) return true;
    return (Robot::status = true);
}
bool Robot::Deaktiviraj()
{
    //if(!Robot::status) return false;
    return (Robot::status = false);
}
void Robot::Rotiraj(Robot::SmjerRotacije na_koju_stranu, int za_koliko)
{
    switch(na_koju_stranu)
    {
        case Robot::SmjerRotacije::Nadesno:
            if(za_koliko >= 0)
                Robot::orijentacija = Robot::Smjer((int(Robot::orijentacija) + za_koliko)%8);
            else
                Robot::orijentacija = Robot::Smjer((int(Robot::orijentacija) + (8 + (za_koliko % 8)))%8);
            break;
        case Robot::SmjerRotacije::Nalijevo:
            if(za_koliko >= 0)
                Robot::orijentacija = Robot::Smjer((int(Robot::orijentacija) + (8 - (za_koliko % 8)))%8);
            else
                Robot::orijentacija = Robot::Smjer((int(Robot::orijentacija) + (8 - (za_koliko % 8)))%8);
            break;
    }
}
bool Robot::Idi(int korak)
{
    int orij = int(Robot::orijentacija);
    //na samom dnu programa je vidljiva prosla implementacija ove funkcije, u "jednoj liniji"
    if(orij % 2)
    {
        bool prva = Robot::Pomjeri[((orij == 0 ? 7 : orij - 1) % 8) / 2](korak);
        bool druga = Robot::Pomjeri[((orij + 1) % 8) / 2](korak);
        if (prva && druga) return true;
        else
        {
            std::cout<<"Robot je pokusao napustiti dozvoljenu oblast\n";
            return false;
        }
    }
    else if (Robot::Pomjeri[orij / 2](korak)) return true;
    else
    {
        std::cout<<"Robot je pokusao napustiti dozvoljenu oblast\n";
        return false;
    }
}
void Robot::IspisiPoziciju()
{
    std::cout<<"Robot je "<<(Robot::status ? "aktivan," : "neaktivan,")<<" nalazi se na poziciji ("<<
        Robot::OcitajPoziciju()[0]<<","<<Robot::OcitajPoziciju()[1]<<") i gleda na "<<
        Robot::GdjeJeOkrenut()<<".\n";
}
std::string Robot::GdjeJeOkrenut(Robot::Smjer smjer)
{
    std::string strane[8]{"sjever", "sjeveroistok", "istok", "jugoistok", "jug", "jugozapad", "zapad",
        "sjeverozapad"};
    return strane[int(smjer)];
}
std::array<int, 2> Robot::OcitajPoziciju()
{
    return {Robot::x, Robot::y};
}
Robot::Smjer Robot::OcitajOrijentaciju()
{
    return Robot::orijentacija;
}
void Robot::PrijaviGresku(Robot::KodoviGresaka kod_greske)
{
    switch(kod_greske)
    {
        case Robot::KodoviGresaka::PogresnaKomanda:
            std::cout<<"Nerazumljiva komanda!\n";
            break;
        case Robot::KodoviGresaka::NedostajeParametar:
            std::cout<<"Komanda trazi parametar koji nije naveden!\n";
            break;
        case Robot::KodoviGresaka::NeispravanParametar:
            std::cout<<"Parametar komande nije ispravan!\n";
            break;
        case Robot::KodoviGresaka::SuvisanParametar:
            std::cout<<"Zadan je suvisan parametar nakon komande!\n";
            break;
    }
}
bool Robot::IzvrsiKomandu(Robot::Komande komanda, int parametar)
{
    switch(komanda)
    {
        case Robot::Komande::Kraj:
            return true;
        case Robot::Komande::Idi:
            return Robot::Idi(parametar);
        case Robot::Komande::Nalijevo:
            Robot::Rotiraj(Robot::SmjerRotacije::Nalijevo, parametar);
            return true;
        case Robot::Komande::Nadesno:
            Robot::Rotiraj(Robot::SmjerRotacije::Nadesno, parametar);
            return true;
    }
    return true;
}
bool Robot::UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske)
{
    bool uneseno = false, parun = false;
    char tempk{}, tempp{};
    std::cout<<"Unesi komandu: ";
    do
    {
        char c = std::cin.peek();
        if(c == '\n')
        {
            std::cin.ignore(10000, '\n');
            if(tempk == 'K') komanda = Robot::Komande::Kraj;
            break;
        }
        else if(c == ' ' || c == '\t') std::cin.ignore(1);
        else if(!uneseno)
        {
            if(c == 'A' || c == 'L' || c == 'D' || c == 'I' || c == 'K')
            {
                tempk = c;
                uneseno = true;
                std::cin.ignore(1, '\n');
            }
            else
            {
                std::cin.ignore(10000, '\n');
                kod_greske = Robot::KodoviGresaka::PogresnaKomanda;
                return false;
            }
        }
        else
        {
            if(tempk == 'A' && (c == '+' || c == '-'))
            {
                tempp = c;
                std::cin.ignore(1);
                c = std::cin.peek();
                if(c == '\n')
                {
                    if(tempp == '+') komanda = Robot::Komande::Aktiviraj;
                    else if (tempp == '-') komanda = Robot::Komande::Deaktiviraj;
                    std::cin.ignore(1000, '\n');
                    return true;
                }
                else if(c == ' ') parun = true;
                else
                {
                    std::cin.ignore(10000, '\n');
                    kod_greske = Robot::KodoviGresaka::PogresnaKomanda;
                    return false;
                }
            }
            else if(tempk == 'K')
            {
                komanda = Robot::Komande::Kraj;
                std::cin.ignore(10000, '\n');
                kod_greske = Robot::KodoviGresaka::SuvisanParametar;
                return true;
            }

        }
    }
    while(true);

    return true;
}
bool Robot::Kretanje_Sjever(int korak)
{
    if(!korak) return true;
    else if(korak > 0 && std::numeric_limits<int>::max() - korak < Robot::y)
        return (Robot::y = std::numeric_limits<int>::max(), false);
    else if(korak < 0 && std::numeric_limits<int>::min() - korak > Robot::y)
        return (Robot::y = std::numeric_limits<int>::min(), false);
    else return (Robot::y += korak, true);
}
bool Robot::Kretanje_Istok(int korak)
{
    if(!korak) return true;
    else if(korak > 0 && std::numeric_limits<int>::max() - korak < Robot::x)
        return (Robot::x = std::numeric_limits<int>::max(), false);
    else if(korak < 0 && std::numeric_limits<int>::min() - korak > Robot::x)
        return (Robot::x = std::numeric_limits<int>::min(), false);
    else return (Robot::x += korak, true);
}
bool Robot::Kretanje_Jug(int korak)
{
    if(!korak) return true;
    else if(korak > 0 && std::numeric_limits<int>::min() + korak > Robot::y)
        return (Robot::y = std::numeric_limits<int>::min(), false);
    else if(korak < 0 && std::numeric_limits<int>::max() + korak < Robot::y)
        return (Robot::y = std::numeric_limits<int>::max(), false);
    else return (Robot::y -= korak, true);

}
bool Robot::Kretanje_Zapad(int korak)
{
    if(!korak) return true;
    else if(korak > 0 && std::numeric_limits<int>::min() + korak > Robot::x)
        return (Robot::x = std::numeric_limits<int>::min(), false);
    else if(korak < 0 && std::numeric_limits<int>::max() + korak < Robot::x)
        return (Robot::x = std::numeric_limits<int>::max(), false);
    else return (Robot::x -= korak, true);
}

/*
bool Robot::Idi(int korak)
{
        return int(Robot::orijentacija) % 2
            ? ((int(Robot::orijentacija) % 8) > 4
                ? (Robot::Kretanje_Zapad(korak)
                    ? ((((int(Robot::orijentacija) - 6) < 0)
                        ? Robot::Kretanje_Jug(korak)
                        : Robot::Kretanje_Sjever(korak)))
                    : ((((int(Robot::orijentacija) - 6) < 0)
                        ? (Robot::Kretanje_Jug(korak), false)
                        : (Robot::Kretanje_Sjever(korak), false))))
                : (Robot::Kretanje_Istok(korak)
                    ? (((int(Robot::orijentacija) - 2) > 0)
                        ? Robot::Kretanje_Jug(korak)
                        : Robot::Kretanje_Sjever(korak))
                    : ((((int(Robot::orijentacija) - 2) > 0)
                        ? (Robot::Kretanje_Jug(korak), false)
                        : (Robot::Kretanje_Sjever(korak), false)))))
            : (int(Robot::orijentacija) % 4
                ? (int(Robot::orijentacija) -4) < 0
                    ? Robot::Kretanje_Istok(korak)
                    : Robot::Kretanje_Zapad(korak)
                : (int(Robot::orijentacija) - 4) < 0
                    ? Robot::Kretanje_Sjever(korak)
                    : Robot::Kretanje_Jug(korak));
}
*/

/*
template <typename Tip1, typename Tip2>
        bool PogresniParametri (Tip1 a, Tip2 b, KodoviGresaka &kod_greske)
        {
            if (std::remove_reference_t<decltype(b)> == <decltype(1+1)>) return false;
        }
            */
