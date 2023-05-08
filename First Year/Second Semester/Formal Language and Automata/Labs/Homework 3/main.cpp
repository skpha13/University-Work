#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class Grammar {
private:
    std::unordered_map<char,std::vector<std::string>> map;
    bool terminalLambda;
public:
    Grammar();
    void print();
    bool accept(char symbol,std::string cuvant);
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

bool Grammar::accept(char symbol,std::string cuvant) {
    if(cuvant.size() == 0 && terminalLambda) return true;

    if(cuvant.size() == 1) {
        for(auto it:map)
            for(int i=0;i<it.second.size();i++) {
                std::cout<<cuvant<<" "<<it.second[i]<<std::endl;
                if(it.second[i][0] == cuvant[0] && terminalLambda) return true;
                if(it.second[i] == cuvant) return true;
            }
        return false;
    }

    for(int i=0;i<map[symbol].size();i++)
        if(map[symbol][i][0] == cuvant[0] && accept(map[symbol][i][1],cuvant.erase(0,1)))
            return true;
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
                std::cout<<"Cuvant: \n";
                std::getline(std::cin,temp);
                if(G.accept('S',temp)) std::cout<<"~ ACCEPTAT\n";
                else std::cout<<"~ NEACCEPTAT\n";
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
                    std::cout<<cuv<<": ";
                    if(G.accept('S',cuv)) std::cout<<"ACCEPTAT\n";
                    else std::cout<<"NEACCEPTAT\n";
                }
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
