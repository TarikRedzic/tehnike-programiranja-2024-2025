//TP 2024/2025: Zadaća 1, Zadatak 4
#include <array>
#include <cctype>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::array<std::vector<std::string>, 100> RazvrstajRijeciPoDuzini(std::string);

int main ()
{
    std::string s;
    std::cout<<"Unesite recenicu: ";
    std::getline(std::cin, s);
    std::array<std::vector<std::string>, 100> niz;
    try
    {
        niz = RazvrstajRijeciPoDuzini(s);
    }
    catch(std::range_error greska) 
    {
        std::cout<<"Greska: Recenica sadrzi predugacku rijec!";
        return 1;
    }
    for(int i{}; i < 100; i++)
        if(niz.at(i).size() != 0)
        {
            std::cout<<"Duzina "<<i<<": ";
            for(int j{}; j < niz.at(i).size(); j++)
                std::cout<<niz.at(i).at(j)<<(j == niz.at(i).size() - 1 ? "\n" : " ");
        }

	return 0;
}

std::array<std::vector<std::string>, 100> RazvrstajRijeciPoDuzini(std::string s)
{
    std::array<std::vector<std::string>, 100> niz;
    std::string temp;
    for(int i{}; i < s.size(); i++)
        if((s.at(i) >= '0' && s.at(i) <= '9') || (s.at(i) >= 'A' && s.at(i) <= 'Z') || (s.at(i) >= 'a' && s.at(i) <= 'z'))
            temp += toupper(s.at(i));
        else if(temp.size() > 0 && temp.size() < 100)
        {
            niz.at(temp.size()).push_back(temp);
            temp.clear();
        }
        else if(temp.size() >= 100)
            throw std::range_error("Predugacka rijec!");

    if(temp.size() > 0 && temp.size() < 100)
        niz.at(temp.size()).push_back(temp);
    else if(temp.size() >= 100)
        throw std::range_error("Predugacka rijec!");
    
    return niz;
}

//test