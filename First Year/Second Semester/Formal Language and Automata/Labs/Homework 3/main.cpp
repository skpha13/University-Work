#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <windows.h>

class Grammar {
private:
    std::unordered_map<char,std::vector<std::string>> map;
    bool terminalLambda;
public:
    Grammar();
    void print();
    bool accept(char symbol,std::string cuvant,int index);
};

Grammar::Grammar() {
    terminalLambda = false;
    std::ifstream f("../grammar.in");
    int nrSymbol;
    f>>nrSymbol;
    f.get();
    for(int i=0;i<nrSymbol;i++)
    {
        char symbol;
        int nr;
        f>>symbol>>nr;
        for(int j=0;j<nr;j++)
        {
            std::string temp;
            f>>temp;
            if (temp == "^") terminalLambda = true;
            map[symbol].push_back(temp);
        }
    }
    f.close();
}

void Grammar::print() {
    for(auto it=map.begin();it!=map.end();it++)
    {
        std::cout<<it->first<<": ";
        for(int i=0;i<it->second.size();i++)
            std::cout<<it->second[i]<<" ";
        std::cout<<std::endl;
    }
}

bool Grammar::accept(char symbol,std::string cuvant,int index) {
    for(int i=0;i<map[symbol].size();i++)
        if(map[symbol][i][0] == cuvant[index] && map[symbol][i].length() > 1 && accept(map[symbol][i][1],cuvant,index+1))
            return true;
        else if(map[symbol][i][0] == cuvant[index] && map[symbol][i].length() == 1 && index == cuvant.length()-1)
            return true;

    if(index == cuvant.length())
    {
        for(int i=0;i<map[symbol].size();i++) {
            if(map[symbol][i] == "^")
                return true;
        }
    }

    return false;
}

class Menu {
    Grammar G;
private:

public:
    Menu();
    void print();
    void engine();
};

Menu::Menu() {
    this->engine();
}

void Menu::print() {
    std::cout<<"----- MENU -----\n";
    std::cout<<"1. Verifica cuvant\n";
    std::cout<<"2. Verifica lista cuvinte din fisier\n";
    std::cout<<"3. Afiseaza gramatica\n";
    std::cout<<"0. Exit\n";
}

void Menu::engine() {
    this->print();
    int option;
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while(true) {
        std::cout<<"Introdu optiune: \n";
        std::cin>>option;
        std::cin.get();
        switch (option) {
            case 0:
                return;
            case 1: {
                system("CLS");
                std::string temp;
                SetConsoleTextAttribute(hconsole,15);
                std::cout<<"Cuvant: \n";
                std::getline(std::cin,temp);
                if(G.accept('S',temp,0)) SetConsoleTextAttribute(hconsole,11),std::cout<<"~ ACCEPTAT\n";
                else SetConsoleTextAttribute(hconsole,12),std::cout<<"~ NEACCEPTAT\n";
                SetConsoleTextAttribute(hconsole,15);
                this->print();
                break;
            }
            case 2: {
                system("CLS");
                std::string inputName;
                std::cout<<"Introdu nume fisier: \n";
                std::getline(std::cin,inputName);
                inputName = "../" + inputName;
                std::ifstream in(inputName);
                std::string cuv;
                while(in>>cuv) {
                    SetConsoleTextAttribute(hconsole,15);
                    std::cout<<cuv<<": ";
                    if(G.accept('S',cuv,0)) SetConsoleTextAttribute(hconsole,11), std::cout<<"ACCEPTAT\n";
                    else SetConsoleTextAttribute(hconsole,12), std::cout<<"NEACCEPTAT\n";
                }
                SetConsoleTextAttribute(hconsole,15);
                this->print();
                break;
            }
            case 3: {
                system("CLS");
                G.print();
                this->print();
                break;
            }
            default: {
                system("CLS");
                std::cout<<"~ INVALID\n";
                this->print();
                break;
            }
        }
    }
}

int main() {
    Menu M;
    return 0;
}
