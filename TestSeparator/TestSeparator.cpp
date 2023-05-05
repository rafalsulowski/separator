#include <iostream>
#include <string>
#include <map>
#include <vector>

int main()
{   
    /*
    ---------------------
    Separatorem jest TYLKO ;
    
    a;b;c   -> |a|b|c|
    a;;b    -> |a||c|
    a ; b;  -> |a | b||
    ;a ;b;  -> ||a |b||


    Separatorem jest spacja i  ,
    a,b c      -> |a|b|c|
    a   ,b c -> |a|b|c|
    a,   b c -> |a|b|c|
    a     , ,   b c -> |a|b|c|
    

    Separatorem jest spacja, tabulator i  ,
    a\t\t\t\    , b   |a|b|  


    Separatorem jest TYLKO spacja
    a,b c      -> |a,b|c|
    a   ,b c -> |a|,b|c|
    a,   b c -> |a,|b|c|
    a   ,   b c -> |a|,|b|c|
    a  , ,   b c -> |a|,|,||b|c|
    a\t , b   |a\t|,|b|  
    

    biale znaki jako separatory nalezy skleic!


    Algorytm:

    1. wczytaj najbli¿szy separator
    2. wytnij stringa od beg do separator
    3. ustaw beg na separator
    4. dodaj wyciety framgent do wektora
    5. Jeœli separatorem jest znak bia³y to beg ustaw na nastêpny znak znacz¹cy (sprawdzjac przy okazji czy nie wystapilo wiecej niz jedno wystapienie separatora ciezkiego
    jesli wystapilo to dodaj tyle pustych wyrazow do tablicy



    ---------------------
    */
    
    std::multimap<std::string, std::vector<std::string>> lineTab;
    std::vector<std::string> vec;
    std::string rec = "";


    //Zestaw danych do destowania dwoch separatorow
    std::string m_Delimeter = ";";
    std::string m_HardDelimeter = ";";
    std::string m_LightDelimeter = "";
    lineTab.insert(std::make_pair(";;;\"Ala\";;  \"ma\"  ;  \"kota\" ;;;", std::vector<std::string>{"", "", "", "\"Ala\"", "", "  \"ma\"  ", "  \"kota\" ", "", "", ""}));
    lineTab.insert(std::make_pair(";;;\"Ala\";;  \"ma\"  ;  \"kota\" ;;;", std::vector<std::string>{"", "", "", "\"Ala\"", "", "  \"ma\"  ", "  \"kota\" ", "", "", ""}));
    /*lineTab.push_back("\"kota\";psa;;;");
    lineTab.push_back("\"Ala\";\"ma\";\"kota\"");
    lineTab.push_back("\"Ala\"  ;  \"ma\"  ;  \"kota\"");
    lineTab.push_back(";\"Ala\"  ;  \"ma\"  ;  \"kota\"");
    lineTab.push_back(";\"Ala\"  ;  \"ma\"  ;  \"kota\";;");
    lineTab.push_back(";;\"Ala\"  ;  \"ma\"  ;  \"kota\";");
    lineTab.push_back("\"Ala\";;  \"ma\"  ;;  \"kota\"   ;;\"psa\"");*/







    /*
    
    beg = 0
    end = 0
    flag = nullptr
    quoteCounter = 0
    ignoreDelimeter = false

    pobierz znak

    jesli to wartosc np."b" && flaga NIE jest ustawiona na CHARACTER_COLLECTING to ustaw flage na CHARACTER_COLLECTING oraz ustaw beg i end na ten znak, jesli to cudzyslow to ustaw flage ignoreDelimeter na true, jesli nie to ustaw na false 
    jesli to wartosc i flaga jest ustawiona na CHARACTER_COLLECTING to ustaw end na ta pozycje


    jesli to separator i ignoreDelimeter jest true to ustaw end na ta pozycje
    w przeciwnym raze {
            jesli to separator i flaga jest ustawiona na CHARACTER_COLLECTING i ignoreDelimeter jest false to wytnij stringa od beg do end, dodaj do tablicy, ustaw flage na DELIMETER_GLUING, 
           jesli to separator i flaga NIE jest ustawiona na CHARACTER_COLLECTING i ignoreDelimeter jest false to dla separatora miekkiego pomin itearcje, dla ciezkiego sprawdz czy poprzedni nie byl ciezkim lub indeksem -1 jesli tak to dodaj pusty string jesli nie to pomin
        }
    */



#define CHARACTER_COLLECTING 1
#define DELIMETER_GLUING 2

    for (const auto& elem : lineTab)
    {
        std::string line = elem.first;

        std::cout << "Badanie linii: \'" << line << "\'\t";

        int beg = 0;
        int end = 0;
        int flag = 0;
        bool ignoreDelimeter = false;
        std::string rec;
        vec.clear();
        for (int i = 0; i < line.size(); i++)
        {
            if (m_Delimeter.find(line[i]) == -1)
            { //znak to jakas wartosc
                if (line[i] == '"') //jesli to cudzyslow to wlaczmy ignorowanie separatorow
                    ignoreDelimeter = !ignoreDelimeter;

                if (flag != CHARACTER_COLLECTING)
                { //jesli wczesniej nie bylo znaku to teraz zaczynami gromadzic
                    flag = CHARACTER_COLLECTING;
                    beg = end = i;
                }
                else if (flag == CHARACTER_COLLECTING)
                { //rozszerzanie zakresu substringa
                    end = i;
                }
            }
            else if (m_Delimeter.find(line[i]) != -1)
            { //znak to separator
                if (ignoreDelimeter)
                { //jesli jestesmy w srodku zdania to ignorujemy separatory
                    end = i;
                }
                else
                {
                    if (flag == CHARACTER_COLLECTING)
                    { //jesli separator ale do tej pory zbieralismy znaki to wytnij!
                        rec = line.substr(beg, end - beg + 1);
                        vec.push_back(rec);
                    }
                    else if (flag != CHARACTER_COLLECTING)
                    {
                        if (m_LightDelimeter.find(line[i]) != -1)
                        { //dla separatora miekkiego pomin
                            continue;
                        }
                        else if (m_HardDelimeter.find(line[i]) != -1)
                        { //dla separatora ciezkiego analizuj
                            if (i == 0 || m_HardDelimeter.find(line[i - 1]) != -1)
                            { //poprzednij znak to poczatek linii lub separator ciezki, dodajemy pusty string
                                vec.push_back("");
                            }
                            else 
                            { //jesli nie to pomin
                                continue;
                            }
                        }
                    }
                    flag = DELIMETER_GLUING;
                }
            }
        }

        if (m_HardDelimeter.find(line[line.size() - 1]) != -1)
        {
            vec.push_back("");
        }
        else if (flag == CHARACTER_COLLECTING) 
        {
            rec = line.substr(beg, end - beg + 1);
            vec.push_back(rec);
        }

        std::cout << "Rozwaizanie: ";
        for (auto el : vec)
            std::cout << "\'" << el << "\'  ";

        if(elem.second == vec)
            printf("\x1B[32mWektor zgodny");
        else
            printf("\x1B[31mWektor rozny od oczekiwanego");
        printf("\x1B[37m\t\t");

        std::cout << "\n\n\n";
    }
}







//
//int beg = 0;
//int separator = 0;
////if (m_HardDelimeter.find(line[0]) != -1)
//    //vec.push_back("");
//
//while (separator < line.size())
//{
//    separator = line.find_first_of(m_Delimeter, beg);
//
//    if (separator == -1)
//        separator = line.size();
//
//    while (beg < separator)
//    {
//        rec += line[beg];
//        beg++;
//    }
//
//    beg++;
//    vec.push_back(rec);
//    rec = "";
//
//    if (m_LightDelimeter.find(line[separator]) != -1) //to byl lekki separator
//    {
//        beg = line.find_first_not_of(m_Delimeter, separator);
//        int counter = 0;
//
//        if (beg == -1)
//        {
//            beg = line.size();
//            counter = 1;
//        }
//
//        for (int i = separator; i < beg; i++)
//        {
//            if (m_HardDelimeter.find(line[i]) != -1)
//                counter++;
//        }
//        while (counter > 1)
//        {
//            vec.push_back("");
//            counter--;
//        }
//    }
//
//}

//int beg = 0;
//int separator = 0;
//int counter = 0;
//vec.clear();
//rec = "";
//while (beg < line.size())
//{
//    separator = line.find_first_of(m_Delimeter, beg);
//    rec = line.substr(beg, separator - beg);
//    beg = separator + 1;
//    vec.push_back(rec);

//    if (beg == line.size() && m_HardDelimeter.find(line[beg - 1]) != -1)
//    {
//        vec.push_back("");
//        break;
//    }

//    if (separator == -1)
//        break;

//    if (m_LightDelimeter.find(line[separator]) != -1) //to byl lekki separator
//    {
//        beg = line.find_first_not_of(m_Delimeter, separator);
//        counter = 0;

//        if (beg == -1)
//        {
//            beg = line.size();
//            counter = 1;
//        }

//        for (int i = separator; i < beg; i++)
//        {
//            if (m_HardDelimeter.find(line[i]) != -1)
//                counter++;
//        }
//        while (counter > 1)
//        {
//            vec.push_back("");
//            counter--;
//        }
//    }
//}
