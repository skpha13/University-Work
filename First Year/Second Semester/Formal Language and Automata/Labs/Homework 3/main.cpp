#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class Grammar {
private:
    std::unordered_map<char,std::vector<std::string>> map;
public:
    Grammar();
    void print();
    bool accept(char symbol,std::string cuvant);
};

Grammar::Grammar() {
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
    if(cuvant.size() == 0) {
        
    }
}

class Menu {
private:

public:

};

int main() {
    Grammar G;
    G.print();
    return 0;
}
