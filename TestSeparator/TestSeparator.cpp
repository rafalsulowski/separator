#include <iostream>
#include <string>
#include <vector>

int main()
{   
    //alg. odczytu
    // a   ;  b;c
        //beg = 0
        //w petli
        //1. znajdz pozycje pierwszego separatora
        //2. zrob substr(beg, separator)
        //3. przesun beg do najblizszego znaku ktory nie jest separatorem 
        //4. dodaj wartosc do vectora


    //alg. odczytu
        //beg = 0
        //w petli
        //1. znajdz pozycje separatora
        //2. zrob substr(beg, separator)
        //3. usun jesli sa cudzyslowy z poczatku i konca
        //4. beg = separator + 1
        //5. dodaj do vectora

    std::string m_Delimeter = "; ";
    std::string LightDelimeters = " \t";
    std::string str = "a\t;          b        ;c";
    std::vector<std::string> vec;


    //"a\t"    ;   "b"    ;; "c" c


    int beg = 0;
    while (beg < str.size())
    {
        int end = str.find_first_of(m_Delimeter, beg);

        std::string buf = str.substr(beg, end - beg);
        if (end - beg == 1)
            buf = "";

        beg = str.find_first_not_of(m_Delimeter, end);
        vec.push_back(buf);
    }

    for (const auto el : vec)
    {
        std::cout << '\'' << el << '\'' << std::endl;
    }
}