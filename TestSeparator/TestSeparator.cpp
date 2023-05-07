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
    ---------------------
    */
    

    std::multimap<std::string, std::vector<std::string>> lineTab;
    std::vector<std::string> vec;
    std::string rec = "";

    //Zestaw danych do destowania jednego separatora
    /*std::string m_Delimeter = ";";
    std::string m_HardDelimeter = ";";
    std::string m_LightDelimeter = "";
    lineTab.insert(std::make_pair(";;;\"Ala\";;  \"ma\"  ;  \"kota\" ;;;", std::vector<std::string>{"", "", "", "\"Ala\"", "", "  \"ma\"  ", "  \"kota\" ", "", "", ""}));
    lineTab.insert(std::make_pair(";;;\"Ala\";;  \"ma\"  ;  \"kota\" ;;;", std::vector<std::string>{"", "", "", "\"Ala\"", "", "  \"ma\"  ", "  \"kota\" ", "", "", ""}));
    lineTab.insert(std::make_pair("a;b;c", std::vector<std::string>{"a", "b", "c"}));
    lineTab.insert(std::make_pair("a;;c", std::vector<std::string>{"a", "", "c"}));
    lineTab.insert(std::make_pair("a; ;c", std::vector<std::string>{"a", " ", "c"}));
    lineTab.insert(std::make_pair("a;b;c;", std::vector<std::string>{"a", "b", "c", ""}));
    lineTab.insert(std::make_pair(";a;b;c;", std::vector<std::string>{"", "a", "b", "c", ""}));
    lineTab.insert(std::make_pair(";a ; b; c;", std::vector<std::string>{"", "a ", " b", " c", ""}));
    lineTab.insert(std::make_pair("\"a\";\"b\";\"c\"", std::vector<std::string>{"\"a\"", "\"b\"", "\"c\""}));
    lineTab.insert(std::make_pair("\"aba\";\"sfb\";\"23c\"", std::vector<std::string>{"\"aba\"", "\"sfb\"", "\"23c\""}));
    lineTab.insert(std::make_pair("\"a;b;a\";\"s  fb;\";\";23 c \"", std::vector<std::string>{"\"a;b;a\"", "\"s  fb;\"", "\";23 c \""}));
    lineTab.insert(std::make_pair("\"a;b;a\";\"s  fb;\";;23 c \"", std::vector<std::string>{"\"a;b;a\"", "\"s  fb;\"", "", "23 c \""}));*/

    //Zestaw danych do destowania dwoch separatorow
    std::string m_Delimeter = "; ";
    std::string m_HardDelimeter = ";";
    std::string m_LightDelimeter = " ";
    lineTab.insert(std::make_pair(";;;\"Ala\";; \"ma\" ;  \"kota\" ;;;", std::vector<std::string>{"", "", "", "\"Ala\"", "", "\"ma\"", "\"kota\"", "", "", ""}));
    lineTab.insert(std::make_pair(";a b ; b; c;", std::vector<std::string>{"", "a", "b", "b", "c", ""}));
    lineTab.insert(std::make_pair("a; ;c", std::vector<std::string>{"a", "", "c"}));
    lineTab.insert(std::make_pair("a;b;c", std::vector<std::string>{"a", "b", "c"}));
    lineTab.insert(std::make_pair("a;;c", std::vector<std::string>{"a", "", "c"}));
    lineTab.insert(std::make_pair("a ;       ; c", std::vector<std::string>{"a", "", "c"}));
    lineTab.insert(std::make_pair("a h ;b;c;", std::vector<std::string>{"a", "h", "b", "c", ""}));
    lineTab.insert(std::make_pair(" ; a;  ;  ;   \"sh  f ;; ;  fa s\";c ;", std::vector<std::string>{"", "a", "", "", "\"sh  f ;; ;  fa s\"","c", ""}));
    lineTab.insert(std::make_pair(";a;b;c;", std::vector<std::string>{"", "a", "b", "c", ""}));
    lineTab.insert(std::make_pair("\"a\";\"b\";\"c\"", std::vector<std::string>{"\"a\"", "\"b\"", "\"c\""}));
    lineTab.insert(std::make_pair("\"a   ba\";\"sf b\";\"23c\"", std::vector<std::string>{"\"a   ba\"", "\"sf b\"", "\"23c\""}));
    lineTab.insert(std::make_pair("\"a;b;a\";\"s  fb;\";\";23 c \"", std::vector<std::string>{"\"a;b;a\"", "\"s  fb;\"", "\";23 c \""}));
    lineTab.insert(std::make_pair("\"a ;b ;a\";\"s  fb;\";;\"23 c \"", std::vector<std::string>{"\"a ;b ;a\"", "\"s  fb;\"", "", "\"23 c \""}));

    






    /*
    
    beg = 0 - poczatek wycinania
    end = 0 - koniec wycinania
    flag = 0 - flaga pilnujaca aktualnej pozycji w linii (to znaczy co aktualnie robimy: zbieramy znaki do wyciecia / sklejamy separatory)
    ignoreDelimeter = false - flaga wywolywana przez cudzyslow powodujaca ignorowanie wystapien separatorw w ciagu znakow objetych cudzyslowem
    hardDelimeterRush = false; - flaga odpowiedzialna za pilnowanie wystapien pustych wyrazow pomiedzy separatorami ciezkimi

    1. pobierz znak
    2. jesli to wartosc np."b" to
    {
        3. jesli to cudzyslow to ustaw flage ignoreDelimeter na true 
        4a. jesli flaga NIE jest ustawiona na CHARACTER_COLLECTING to ustaw flage na CHARACTER_COLLECTING oraz ustaw beg i end na ten znak, 
        4b. jesli flaga jest ustawiona na CHARACTER_COLLECTING to ustaw end na ta pozycje
    }
    5. je¿eli jednak to separator to
    {
        6. jesli ignoreDelimeter jest true to ustaw end na ta pozycje
        7a. jesli flaga jest ustawiona na CHARACTER_COLLECTING to wytnij stringa od beg do end, dodaj do tablicy, ustaw flage na DELIMETER_GLUING, 
        7b. jesli flaga NIE jest ustawiona na CHARACTER_COLLECTING i ignoreDelimeter jest false to dla separatora miekkiego pomin itearcje, dla ciezkiego sprawdz czy poprzedni nie byl ciezkim lub indeksem -1 jesli tak to dodaj pusty string jesli nie to pomin
    }
    */



#define CHARACTER_COLLECTING 1
#define DELIMETER_GLUING 2

    for (const auto& elem : lineTab)
    {
        std::string line = elem.first;

        std::cout << "Linia:|" << line << "|\t";


        int beg = 0;
        int end = 0;
        int characterCollecting = false;
        bool ignoreDelimeter = false;
        bool hardDelimeterRush = true;
        std::string rec;
        vec.clear();
        for (int i = 0; i < line.size(); i++)
        {
            if (m_Delimeter.find(line[i]) == -1 || ignoreDelimeter) //znak to jakas wartosc
            {
                if (line[i] == '"') //jesli to cudzyslow to zmieniamy stan ignorowania separatorow (pierwszy cudzyslow w³¹czy ignorowanie drugi wy³¹czy)
                    ignoreDelimeter = !ignoreDelimeter;

                if (!characterCollecting) //rozpoczecia zbierania danych do wyciêcia
                {
                    characterCollecting = true;
                    hardDelimeterRush = false;
                    beg = end = i;
                }
                else if (characterCollecting) //rozszerzanie zakresu wyciêcia
                {
                    end = i;
                }
            }
            else if (m_Delimeter.find(line[i]) != -1) //znak to separator
            {
                if (characterCollecting) //wytnij zebrane dane
                {
                    rec = line.substr(beg, end - beg + 1);
                    vec.push_back(rec);

                    if (m_HardDelimeter.find(line[i]) != -1) //jeseli separator konczacy ciag znakow znaczacych jest ciezki to ustaw tymczasow¹ wartoœc pust¹ na true
                        hardDelimeterRush = true;
                    else
                        hardDelimeterRush = false;
                }
                else if (!characterCollecting)
                {
                    if (m_LightDelimeter.find(line[i]) != -1) //sklej separator miekki
                    {
                        continue;
                    }
                    else if (m_HardDelimeter.find(line[i]) != -1) //dla separatora ciezkiego:
                    {
                        if(hardDelimeterRush || i == line.size() - 1)
                        {
                            vec.push_back("");
                        }
                        else
                        {
                            hardDelimeterRush = true;
                            continue;
                        }
                    }
                }
                characterCollecting = false;
            }
        }

        /*if (m_HardDelimeter.find(line[line.size() - 1]) != -1)
        {
            vec.push_back("");
        }*/
        if (characterCollecting) 
        {
            rec = line.substr(beg, end - beg + 1);
            vec.push_back(rec);
        }





        std::cout << "Rezultat pragramu:|";
        for (auto el : vec)
            std::cout << "" << el << "|";
        std::cout << "  Oczekiwane:|";
        for (auto el : elem.second)
            std::cout << "" << el << "|";
        if(elem.second == vec)
            printf(" \x1B[32mWektor zgodny");
        else
            printf(" \x1B[31mWektor niezgodny");
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
