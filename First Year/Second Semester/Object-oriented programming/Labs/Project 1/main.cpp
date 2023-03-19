#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

// class user
// class movie
// class series
// class actors

class Movie{
private:
    int releaseYear;
    char* name;
    float duration; // minutes
    bool isTop10;
    double rating;
    char* description;
    char ageRating; // G = general audience, R = restricted
public:
    // constructors
    Movie();
    Movie(char* name,char* description,int releaseYear,float duration,double rating,bool isTop10,char ageRating);
    Movie(char* name,char* description,int releaseYear,float duration,double rating);
    Movie(char* name,float duration,double rating,char ageRating);
    Movie(const Movie &obj);
    ~Movie();

    // operators
    Movie& operator=(const Movie &obj);
    friend ostream& operator<<(ostream& out,const Movie &obj);
    friend istream& operator>>(istream& in,Movie &obj);

    Movie &operator++();
    // without & because i don't want it to modify
    Movie operator++(int);

    // without & because i don't want it to modify
    Movie operator+(const Movie &obj);
    Movie operator+(int var);

    Movie operator-(const Movie &obj);
    Movie operator-(int var);

    // cast operator, explicit/implicit
    operator double();
    operator double() const;

    // relational operators
    bool operator==(const Movie &obj);
    bool operator<(const Movie &obj);
    bool operator>(const Movie &obj);
    bool operator<=(const Movie &obj);
    bool operator>=(const Movie &obj);

    // methods
//      method to verify if a movie is good enough (high rating + top10)
//      method to find in which era the movie is {silent,sound,golden age of cinema,blockbuster,independent,new age}
//      method to see if movie is good for kids or not
    void verifyRating() const;
    void eraOfMovie() const;
    void verifyAge() const;

    // getters
//    functionalitiesMovie(const Movie &obj) cannot access or modify with non-const fucntions
    int getReleaseYear() const;
    float getDuration() const;
    bool getIsTop10() const;
    double getRating() const;
    char getAgeRating() const;
    const char* getName() const;
    const char* getDescription() const;

    // setters
    void setReleaseYear(int releaseYear);
    void setDuration(float duration);
    void setIsTop10(bool isTop10);
    void setRating(double rating);
    void setAgeRating(char ageRating);
    void setName(char *name);
    void setDescription(char *description);
};

Movie::Movie() {
    this->releaseYear = 0;
    this->name = new char[strlen("Unnamed")+1];
    strcpy(this->name,"Unnamed");
    this->duration = 0;
    this->isTop10 = false;
    this->rating = 0;
    this->description = new char[strlen("No description given")+1];
    strcpy(this->description,"No description given");
    this->ageRating = 'R';
}

Movie::Movie(char* name,char* description,int releaseYear,float duration,double rating,bool isTop10,char ageRating) {
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
    this->description = new char[strlen(description)+1];
    strcpy(this->description,description);
    this->releaseYear = releaseYear;
    this->duration = duration;
    this->rating = rating;
    this->isTop10 = isTop10;
    this->ageRating = ageRating;
}

Movie::Movie(char* name,char* description,int releaseYear,float duration,double rating) {
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
    this->description = new char[strlen(description)+1];
    strcpy(this->description,description);
    this->releaseYear = releaseYear;
    this->duration = duration;
    this->rating = rating;
    this->isTop10 = false;
    this->ageRating = 'R';
}

Movie::Movie(char* name,float duration,double rating,char ageRating) {
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
    this->description = new char[strlen("No description given")+1];
    strcpy(this->description,"No description given");
    this->releaseYear = 0;
    this->duration = duration;
    this->rating = rating;
    this->isTop10 = false;
    this->ageRating = ageRating;
}

Movie& Movie::operator=(const Movie &obj) {
    if(this != &obj)
    {
        if(this->name != NULL)
        {
            delete[] this->name;
            this->name = NULL;
        }
        if(this->description != NULL)
        {
            delete[] this->description;
            this->description = NULL;
        }

        this->name = new char[strlen(obj.name)+1];
        strcpy(this->name,obj.name);
        this->description = new char[strlen(obj.description)+1];
        strcpy(this->description,obj.description);
        this->releaseYear = obj.releaseYear;
        this->duration = obj.duration;
        this->isTop10 = obj.isTop10;
        this->rating = obj.rating;
        this->ageRating = obj.ageRating;
    }

    return *this;
}

ostream& operator<<(ostream& out,const Movie &obj) {
    out<<"Name: "<<obj.name<<endl;
    out<<"Description: "<<obj.description<<endl;
    out<<"Release Year: "<<obj.releaseYear<<endl;
    out<<"Duration: "<<obj.duration<<" minutes"<<endl;
    out<<"Top 10: "<<obj.isTop10<<endl;
    out<<"Rating: "<<obj.rating<<endl;
    out<<"Age Rating: "<<obj.ageRating<<endl;

    return out;
}

istream& operator>>(istream& in,Movie &obj) {
    char name[50],description[256];

    cout<<"Enter name: "<<endl;
    in>>name;
    // in>> doesn't get the \n transmitted by keyboard
    // so i get rid of it using in.get()
    in.get();
    if(obj.name != NULL)
    {
        delete[] obj.name;
        obj.name = NULL;
    }
    obj.name = new char[strlen(name)+1];
    strcpy(obj.name,name);

    cout<<"Enter description: "<<endl;
    // in.getline() to read the whole line inluding \n
    in.getline(description,255);
    if(obj.description != NULL)
    {
        delete[] obj.description;
        obj.description = NULL;
    }
    obj.description = new char[strlen(description)+1];
    strcpy(obj.description,description);

    cout<<"Enter release year: "<<endl;
    in>>obj.releaseYear;

    cout<<"Enter duration(in minutes): "<<endl;
    in>>obj.duration;

    cout<<"Is it top 10? "<<endl;
    in>>obj.isTop10;

    cout<<"Rating: "<<endl;
    in>>obj.rating;

    in.get();
    cout<<"Age rating(G/R): "<<endl;
    in>>obj.ageRating;

    return in;
}

Movie &Movie::operator++() {
    this->rating += 1;
    return *this;
}

// without & because i don't want it to modify
Movie Movie::operator++(int) {
    Movie temp(*this);
    this->rating += 1;
    return temp;
}

// without & because i don't want it to modify
Movie Movie::operator+(const Movie &obj) {
    Movie temp(*this);
    temp.duration = temp.duration + obj.duration;
    return temp;
}

Movie Movie::operator+(int var) {
    Movie temp(*this);
    temp.duration = temp.duration + var;
    return temp;
}

Movie Movie::operator-(const Movie &obj) {
    Movie temp(*this);
    temp.duration = temp.duration - obj.duration;
    return temp;
}

Movie Movie::operator-(int var) {
    Movie temp(*this);
    temp.duration = temp.duration - var;
    return temp;
}

Movie::operator double() {
    return this->rating;
}

Movie::operator double() const {
    return this->rating;
}

bool Movie::operator==(const Movie &obj) {
    if(strcmp(this->name,obj.name) != 0) return false;
    if(strcmp(this->description,obj.description) != 0) return false;
    if(this->releaseYear != obj.releaseYear) return false;
    if(this->isTop10 != obj.isTop10) return false;
    if(this->rating != obj.rating) return false;
    if(this->ageRating != obj.ageRating) return false;

    return true;
}

bool Movie::operator<(const Movie &obj) {
    if(strcmp(this->name,obj.name) >= 0) return false;
    if(this->rating >= obj.rating) return false;
    if(this->isTop10 >= obj.isTop10) return false;

    return true;
}

bool Movie::operator>(const Movie &obj) {
    if(*this == obj) return false;
    return !(*this < obj);
}

bool Movie::operator<=(const Movie &obj) {
    return !(*this > obj);
}

bool Movie::operator>=(const Movie &obj) {
    return !(*this <= obj);
}

Movie::Movie(const Movie &obj) {
    this->releaseYear = obj.releaseYear;
    this->name = new char[strlen(obj.name)+1];
    strcpy(this->name,obj.name);
    this->duration = obj.duration;
    this->isTop10 = obj.isTop10;
    this->rating = obj.rating;
    this->description = new char[strlen(obj.description)+1];
    strcpy(this->description,obj.description);
    this->ageRating = obj.ageRating;
}

Movie::~Movie() {
    if(this->name != NULL)
    {
        delete[] this->name;
        this->name = NULL;
    }
    if(this->description != NULL)
    {
        delete[] this->description;
        this->description = NULL;
    }
}

int Movie::getReleaseYear() const{
    return releaseYear;
}

float Movie::getDuration() const{
    return duration;
}

bool Movie::getIsTop10() const{
    return isTop10;
}

double Movie::getRating() const{
    return rating;
}

char Movie::getAgeRating() const{
    return ageRating;
}

const char* Movie::getName() const {
    return name;
}

const char* Movie::getDescription() const {
    return description;
}

void Movie::setReleaseYear(int releaseYear) {
    this->releaseYear = releaseYear;
}

void Movie::setDuration(float duration) {
    this->duration = duration;
}

void Movie::setIsTop10(bool isTop10) {
    this->isTop10 = isTop10;
}

void Movie::setRating(double rating) {
    this->rating = rating;
}

void Movie::setAgeRating(char ageRating) {
    this->ageRating = ageRating;
}

void Movie::setName(char *name) {
    if(this->name != NULL)
    {
        delete[] this->name;
        this->name = NULL;
    }
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
}

void Movie::setDescription(char *description) {
    if(this->description != NULL)
    {
        delete[] this->description;
        this->description = NULL;
    }
    this->description = new char[strlen(description)+1];
    strcpy(this->description,description);
}

void Movie::verifyAge() const{
    if(this->ageRating == 'R')
        cout<<"This movie isn't recommended for kids. No-one younger than 18 years old may see a 'R' rated movie, which stands for restricted.\n";
    else
        cout<<"This movie can be watched by anyone as it is categorised as a 'G' movie, which stands for general audience.\n";
}

void Movie::eraOfMovie() const {
    if(this->releaseYear >= 1815 && this->releaseYear <= 1910) cout<<"The movie "<<this->name<<" belongs in the Pioneer era.\n";
    if(this->releaseYear >= 1911 && this->releaseYear <= 1926) cout<<"The movie "<<this->name<<" belongs in the Silent era.\n";
    if(this->releaseYear >= 1927 && this->releaseYear <= 1940) cout<<"The movie "<<this->name<<" belongs in the Sound era.\n";
    if(this->releaseYear >= 1941 && this->releaseYear <= 1954) cout<<"The movie "<<this->name<<" belongs in the Golden era.\n";
    if(this->releaseYear >= 1955 && this->releaseYear <= 1976) cout<<"The movie "<<this->name<<" belongs in the Blockbuster era.\n";
    if(this->releaseYear >= 1977 && this->releaseYear <= 1990) cout<<"The movie "<<this->name<<" belongs in the Independent era.\n";
    if(this->releaseYear >= 1991) cout<<"The movie "<<this->name<<" belongs in the New age era.\n";
}

void Movie::verifyRating() const {
    if(this->isTop10 && this->rating > 7.5)
        cout<<"This movie is highly recommended.\n";
    else
        cout<<"This movie is seen as not that appealing.\n";
}

class Series{
private:
    string name;
    int nrSeasons;
    int* nrEpisodes;
    // for every season store duration of every episode;
    vector<vector<int>> durationEpisodes;
    float rating;
    int releaseYear;
public:
    // constructors
    Series();
    Series(string name,float rating,int releaseYear);
    Series(string name,int nrSeasons,int* nrEpisodes,vector<vector<int>> durationEpisodes);
    Series(string name,int nrSeasons,int* nrEpisodes,vector<vector<int>> durationEpisodes,float rating,int releaseYear);
    Series(const Series &obj);
    ~Series();

    // operators
    friend ostream& operator<<(ostream& out,const Series &obj);
    friend istream& operator>>(istream& in,Series &obj);
    Series& operator=(const Series &obj);

    Series &operator++();
    Series operator++(int);

    Series operator+(const Series &obj);
    Series operator+(float var);

    Series operator-(const Series &obj);
    Series operator-(float var);

    operator string();
    operator string() const;

    bool operator==(const Series &obj);
    bool operator<(const Series &obj);
    bool operator>(const Series &obj);
    bool operator<=(const Series &obj);
    bool operator>=(const Series &obj);

    int operator[](int index);

    // methods
//        method to see how long a season is or the whole series
    void getLengthSeason() const;
    void getLengthSeries() const;

    // getters
    const string getName() const;
    int getNrSeasons();
    const int* getNrEpisodes() const;
    float getRating();
    int getReleaseYear();
    const vector<vector<int>> getDurationEpisodes() const;

    // setters
    void setName(string name);
    void setNrSeasons(int nrSeasons);
    void setNrEpisodes(int* nrEpisodes,int nrSeasons);
    void setRating(float rating);
    void setReleaseYear(int releaseYear);
    // done without const because it is passed by value
    void setDurationEpisodes(vector<vector<int>> durationEpisodes);
};

Series::Series() {
    this->name = "No name";
    this->nrSeasons = 0;
    this->nrEpisodes = NULL;
    this->rating = 0;
    this->releaseYear = 0;
}

Series::Series(string name,float rating,int releaseYear) {
    this->name = name;
    this->nrSeasons = 0;
    this->nrEpisodes = NULL;
    this->rating = rating;
    this->releaseYear = releaseYear;
}

Series::Series(string name,int nrSeasons,int* nrEpisodes,vector<vector<int>> durationEpisodes) {
    this->name = name;
    this->nrSeasons = nrSeasons;
    this->nrEpisodes = new int[nrSeasons];
    for(int i=0;i<nrSeasons;i++)
        this->nrEpisodes[i] = nrEpisodes[i];

    // could have used this->durationEpisodes = durationEpisodes
    for(int i=0;i<durationEpisodes.size();i++)
    {
        vector<int> temp;
        for(int j=0;j<durationEpisodes[i].size();j++)
            temp.push_back(durationEpisodes[i][j]);
        this->durationEpisodes.push_back(temp);
    }

    this->releaseYear = 0;
    this->rating = 0;
}

Series::Series(string name,int nrSeasons,int* nrEpisodes,vector<vector<int>> durationEpisodes,float rating,int releaseYear) {
    this->name = name;
    this->nrSeasons = nrSeasons;
    this->nrEpisodes = new int[nrSeasons];
    for(int i=0;i<nrSeasons;i++)
        this->nrEpisodes[i] = nrEpisodes[i];

    // could have used this->durationEpisodes = durationEpisodes
    for(int i=0;i<durationEpisodes.size();i++)
    {
        vector<int> temp;
        for(int j=0;j<durationEpisodes[i].size();j++)
            temp.push_back(durationEpisodes[i][j]);
        this->durationEpisodes.push_back(temp);
    }

    this->rating = rating;
    this->releaseYear = releaseYear;
}

Series::Series(const Series &obj) {
    this->name = obj.name;
    this->nrSeasons = obj.nrSeasons;
    this->rating = obj.rating;
    this->releaseYear = obj.releaseYear;

    // don't delete nrEpisodes
    this->nrEpisodes = new int[obj.nrSeasons];
    for(int i = 0;i<obj.nrSeasons;i++)
        this->nrEpisodes[i] = obj.nrEpisodes[i];

    if(this->durationEpisodes.empty() == 0) this->durationEpisodes.clear();
    for(int i=0;i<obj.durationEpisodes.size();i++)
    {
        vector<int> temp;
        for(int j=0;j<obj.durationEpisodes[i].size();j++)
            temp.push_back(obj.durationEpisodes[i][j]);
        this->durationEpisodes.push_back(temp);
    }
}

Series::~Series() {
    if(this->nrEpisodes != NULL)
    {
        delete[] this->nrEpisodes;
        this->nrEpisodes = NULL;
    }
    if(this->durationEpisodes.empty() == 0) this->durationEpisodes.clear();
    this->name = "";
    this->nrSeasons = 0;
    this->rating = 0;
    this->releaseYear = 0;
}

ostream& operator<<(ostream& out,const Series &obj) {
    out<<"Name: "<<obj.name<<endl;
    out<<"Release Year: "<<obj.releaseYear<<endl;
    out<<"Rating: "<<obj.rating<<endl;
    out<<"Number of Seasons: "<<obj.nrSeasons<<endl;
    out<<"Number of episodes for each season: "<<endl;
    if(obj.nrSeasons == 0) cout<<"\t0"<<endl;
    for(int i=0;i<obj.nrSeasons;i++)
        cout<<"\tSeason "<<i+1<<": "<<obj.nrEpisodes[i]<<" episodes"<<endl;

    out<<"Duration for each episode: "<<endl;
    if(obj.durationEpisodes.empty()) cout<<"\t0"<<endl;
    for(int i=0;i<obj.durationEpisodes.size();i++)
    {
        cout<<"\tFor season "<<i+1<<": "<<endl;
        for(int j=0;j<obj.durationEpisodes[i].size();j++)
            cout<<"\t\tEpisode "<<j+1<<" takes "<<obj.durationEpisodes[i][j]<<" minutes"<<endl;
    }
    return out;
}

istream& operator>>(istream& in,Series &obj) {
    cout<<"Enter name: "<<endl;
    in>>obj.name;
    cout<<"Enter release year: "<<endl;
    in>>obj.releaseYear;
    cout<<"Enter rating: "<<endl;
    in>>obj.rating;
    cout<<"Enter number of season: "<<endl;
    in>>obj.nrSeasons;
    if(obj.nrEpisodes != NULL)
    {
        delete[] obj.nrEpisodes;
        obj.nrEpisodes = NULL;
    }
    obj.nrEpisodes = new int[obj.nrSeasons];
    for(int i=0;i<obj.nrSeasons;i++)
    {
        cout<<"Enter number of episodes for season "<<i+1<<": "<<endl;
        in>>obj.nrEpisodes[i];
    }
    for(int i=0;i<obj.nrSeasons;i++)
    {
        vector<int> temp;
        cout<<"Enter duration for season "<<i+1<<" (in minutes): "<<endl;
        for(int j=0;j<obj.nrEpisodes[i];j++)
        {
            int aux;
            cout<<"\tEpisode "<<j+1<<": "<<endl;
            in>>aux;
            temp.push_back(aux);
        }
        obj.durationEpisodes.push_back(temp);
    }

    return in;
}

Series &Series::operator++() {
    this->rating += 1;
    return *this;
}

Series Series::operator++(int) {
    Series temp(*this);
    this->rating += 1;
    return temp;
}

Series Series::operator+(const Series &obj) {
    Series temp(*this);
    // for commutative relation
    if(temp.name > obj.name) temp.name += obj.name;
    else temp.name = obj.name + temp.name;
    temp.rating += obj.rating;
    return temp;
}

Series Series::operator+(float var) {
    Series temp(*this);
    temp.rating += var;
    return temp;
}

Series Series::operator-(const Series &obj) {
    Series temp(*this);
    temp.rating -= obj.rating;
    return temp;
}

Series Series::operator-(float var) {
    Series temp(*this);
    temp.rating -= var;
    return temp;
}

Series::operator string() {
    return this->name;
}

Series::operator string() const {
    return this->name;
}

bool Series::operator==(const Series &obj) {
    if(this->name != obj.name) return false;
    if(this->nrSeasons != obj.nrSeasons) return false;
    else
    {
        for(int i=0;i<this->nrSeasons;i++)
            if(this->nrEpisodes[i] != obj.nrEpisodes[i])
                return false;
    }
    if(this->durationEpisodes != obj.durationEpisodes) return false;
    if(this->rating != obj.rating) return false;
    if(this->releaseYear != obj.releaseYear) return false;

    return true;
}

bool Series::operator<(const Series &obj) {
    if(this->name >= obj.name) return false;
    // this comparation will automatically determine if nrSeasons == and nrEpisodes==
    if(this->durationEpisodes >= obj.durationEpisodes) return false;
    if(this->rating >= obj.rating) return false;
    if(this->releaseYear >= obj.releaseYear) return false;

    return true;
}

bool Series::operator<=(const Series &obj) {
    if((*this == obj) || (*this < obj)) return true;
    return false;
}

bool Series::operator>(const Series &obj) {
    return !(*this <= obj);
}

bool Series::operator>=(const Series &obj) {
    return !(*this<obj);
}

int Series::operator[](int index) {
    if(this->nrEpisodes != NULL && index >= 0 && index < this->nrSeasons)
        return this->nrEpisodes[index];
    cout<<"~ Index invalid\n";
}

Series& Series::operator=(const Series &obj) {
    if(this != &obj)
    {
        this->name = obj.name;
        this->nrSeasons = obj.nrSeasons;
        this->rating = obj.rating;
        this->releaseYear = obj.releaseYear;

        if(this->nrEpisodes != NULL)
        {
            delete[] this->nrEpisodes;
            this->nrEpisodes = NULL;
        }
        this->nrEpisodes = new int[obj.nrSeasons];
        for(int i = 0;i<obj.nrSeasons;i++)
            this->nrEpisodes[i] = obj.nrEpisodes[i];

        if(this->durationEpisodes.empty() == 0) this->durationEpisodes.clear();
        for(int i=0;i<obj.durationEpisodes.size();i++)
        {
            vector<int> temp;
            for(int j=0;j<obj.durationEpisodes[i].size();j++)
                temp.push_back(obj.durationEpisodes[i][j]);
            this->durationEpisodes.push_back(temp);
        }
    }
    return *this;
}

const string Series::getName() const {
    return this->name;
}

int Series::getNrSeasons() {
    return this->nrSeasons;
}

const int *Series::getNrEpisodes() const {
    return this->nrEpisodes;
}

float Series::getRating() {
    return this->rating;
}

int Series::getReleaseYear() {
    return this->releaseYear;
}

const vector<vector<int>> Series::getDurationEpisodes() const{
    return this->durationEpisodes;
}

void Series::setName(string name) {
    this->name = name;
}

void Series::setNrSeasons(int nrSeasons) {
    this->nrSeasons = nrSeasons;
}

void Series::setNrEpisodes(int *nrEpisodes, int nrSeasons) {
    if(this->nrEpisodes != NULL)
    {
        delete[] this->nrEpisodes;
        this->nrEpisodes = NULL;
    }
    this->nrEpisodes = new int[nrSeasons];
    for(int i=0;i<nrSeasons;i++)
        this->nrEpisodes[i] = nrEpisodes[i];
}

void Series::setRating(float rating) {
    this->rating = rating;
}

void Series::setReleaseYear(int releaseYear) {
    this->releaseYear = releaseYear;
}

// done without const because it is passed by value
void Series::setDurationEpisodes(vector<vector<int>> durationEpisodes) {
    this->durationEpisodes = durationEpisodes;
}

void Series::getLengthSeason() const {
    int sum = 0,indexSeason = 0;
    cout<<"Enter number of season: "<<endl;
    cin>>indexSeason;
    indexSeason--;
    cin.get();
    for(int i=0;i<this->durationEpisodes[indexSeason].size();i++)
        sum += this->durationEpisodes[indexSeason][i];
    cout<<"Season "<<indexSeason+1<<" takes "<<sum<<" minutes to watch\n";
}

void Series::getLengthSeries() const {
    int sum = 0;
    for(int i=0;i<this->durationEpisodes.size();i++)
        for(int j=0;j<this->durationEpisodes[i].size();j++)
            sum += this->durationEpisodes[i][j];
    cout<<"The whole series takes "<<sum<<" minutes to watch\n";
}

class User {
private:
    static int contorID;
    const int idUser;
    string lastName,firstName;
    vector<string> watched;
    int year;
public:
    // constructors
    User();
    User(string lastName,string firstName);
    User(string lastName,string firstName,int year);
    User(string lastName,string firstName,int year,vector<string> watched);
    User(const User &obj);
    ~User();

    // operators
    User& operator=(const User &obj);
    friend ostream& operator<<(ostream& out,const User &obj);
    friend istream& operator>>(istream& in,User &obj);

    User &operator++();
    User operator++(int);

    User operator+(const User &obj);
    User operator+(int year);
    User operator-(const User &obj);
    User operator-(int year);

    operator string();
    operator string() const;

    string operator[](int index);

    bool operator==(const User &obj);
    bool operator<(const User &obj);

    // methods
//        method to format name
//        method to show his age, and restrictions
//  formatName not const because i need to modify it
    void formatName();
    void ageRestriction(int currentYear) const;

    // getters
    int getIdUser();
    static int getContorId();
    const string getLastName() const;
    const string getFirstName() const;
    const vector<string> getWatched() const;
    int getYear();

    // setters
    void setLastName(string lastName);
    void setFirstName(string firstName);
    void setWatched(vector<string> watched);
    void setYear(int year);
};

// global declaration for static variable
int User::contorID = 100000000;
// using initializer list
User::User():idUser(contorID++) {
    this->lastName = "None";
    this->firstName = "None";
    this->year = 0;
}

User::User(string lastName,string firstName):idUser(contorID++) {
    this->lastName = lastName;
    this->firstName = firstName;
    this->year = 0;
}

User::User(string lastName,string firstName,int year):idUser(contorID++) {
    this->lastName = lastName;
    this->firstName = firstName;
    this->year = year;
}

User::User(string lastName,string firstName,int year,vector<string> watched):idUser(contorID++) {
    this->lastName = lastName;
    this->firstName = firstName;
    this->year = year;
    for(int i=0;i<watched.size();i++)
        this->watched.push_back(watched[i]);
}

User::User(const User &obj):idUser(contorID++) {
    this->lastName = obj.lastName;
    this->firstName = obj.firstName;
    this->year = obj.year;
    for(int i=0;i<obj.watched.size();i++)
        this->watched.push_back(obj.watched[i]);
}

User::~User() {
    contorID--;
    if(this->lastName.empty() == 0) this->lastName.clear();
    if(this->firstName.empty() == 0) this->firstName.clear();
    this->year = 0;
    if(this->watched.empty() == 0) this->watched.clear();
}

User& User::operator=(const User &obj) {
    if(this != &obj)
    {
        this->lastName = obj.lastName;
        this->firstName = obj.firstName;
        this->year = obj.year;
        if(this->watched.empty() == 0) this->watched.clear();
        for(int i=0;i<obj.watched.size();i++)
            this->watched.push_back(obj.watched[i]);
    }
    return *this;
}

ostream& operator<<(ostream& out,const User &obj) {
    out<<"Last name: "<<obj.lastName<<endl;
    out<<"First name: "<<obj.firstName<<endl;
    out<<"ID: "<<obj.idUser<<endl;
    out<<"Born in year: "<<obj.year<<endl;
    out<<"Has watched: "<<endl;
    for(int i=0;i<obj.watched.size();i++)
        out<<"\t - "<<obj.watched[i]<<endl;

    return out;
}

istream& operator>>(istream& in,User &obj) {
    int temp;
    string tempString;

    cout<<"Enter last name: "<<endl;
    in>>obj.lastName;
    cout<<"Enter first name: "<<endl;
    in>>obj.firstName;
    cout<<"Enter year in which he was born: "<<endl;
    in>>obj.year;

    if(obj.watched.empty() == 0) obj.watched.clear();
    cout<<"Enter how many movies he has watched: "<<endl;
    in>>temp;
    // to get rid off \n character after number
    in.get();
    for(int i=0;i<temp;i++)
    {
        cout<<"\tEnter movie "<<i+1<<": "<<endl;
        // to read full line with spaces
        getline(in,tempString);
        obj.watched.push_back(tempString);
    }

    return in;
}

User &User::operator++() {
    this->year += 1;
    return *this;
}

User User::operator++(int) {
    User temp(*this);
    this->year += 1;
    return temp;
}

User User::operator+(const User &obj) {
    User temp(*this);
    temp.year += obj.year;
    return temp;
}

User User::operator+(int year) {
    User temp(*this);
    temp.year += year;
    return temp;
}

User User::operator-(const User &obj) {
    User temp(*this);
    temp.year -= obj.year;
    return temp;
}

User User::operator-(int year) {
    User temp(*this);
    temp.year -= year;
    return temp;
}

User::operator string() {
    return this->lastName;
}

User::operator string() const {
    return this->lastName;
}

string User::operator[](int index) {
    if(this->watched.empty() == 0 && index >= 0 && index < this->watched.size())
        return this->watched[index];
    cout<<"~ Index invalid\n";
}

bool User::operator==(const User &obj) {
    if(this->idUser != obj.idUser) return false;
    if(this->lastName != obj.lastName) return false;
    if(this->firstName != obj.firstName) return false;
    if(this->watched != obj.watched) return false;
    if(this->year != obj.year) return false;

    return true;
}

bool User::operator<(const User &obj) {
    if(this->year >= obj.year) return false;
    if(this->lastName >= obj.lastName) return false;
    if(this->firstName >= obj.firstName) return false;
    if(this->watched >= obj.watched) return false;

    return true;
}

int User::getIdUser() {
    return this->idUser;
}

int User::getContorId() {
    return contorID;
}

const string User::getLastName() const {
    return this->lastName;
}

const string User::getFirstName() const {
    return this->firstName;
}

const vector<string> User::getWatched() const {
    return this->watched;
}

int User::getYear() {
    return this->year;
}

void User::setLastName(string lastName) {
    this->lastName = lastName;
}

void User::setFirstName(string firstName) {
    this->firstName = firstName;
}

void User::setWatched(vector<string> watched) {
    this->watched = watched;
}

void User::setYear(int year) {
    this->year = year;
}

void User::formatName() {
    if(this->lastName.empty() == 0)
    {
        this->lastName[0] = toupper(this->lastName[0]);
        for(int i=1;i<this->lastName.size();i++)
            this->lastName[i] = tolower(this->lastName[i]);
    }

    if(this->firstName.empty() == 0)
    {
        this->firstName[0] = toupper(this->firstName[0]);
        for(int i=1;i<this->firstName.size();i++)
            this->firstName[i] = tolower(this->firstName[i]);
    }
}

void User::ageRestriction(int currentYear) const {
    int age;
    age = currentYear - this->year;
    cout<<"Age of user is: "<<age<<endl;
    if(age<18)
    {
        cout<<"Restrictions: "<<endl;
        cout<<"\tUsers under the age of 18 are recommended to not watch the R rated Movies, which stands for Restricted,\n as it can show impactful images and showcase violence, unless they are accompanied by an adult";
    }
    else
    {
        cout<<"Restrictions: "<<endl;
        cout<<"\tThere are no restrictions, but please keep in mind that it may contain one, or more of the following:\n";
        cout<<"\t\t - Abuse\n";
        cout<<"\t\t - Sexual assault\n";
        cout<<"\t\t - Drug use\n";
        cout<<"\t\t - Violence\n";
    }
}

class Actor {
private:
    string name;
    vector<string> starsIn;
    int age;
    float salary;

public:
    // constructors
    Actor();
    Actor(string name);
    Actor(string name,int age);
    Actor(string name,int age,float salary,vector<string> starsIn);
    Actor(const Actor &obj);
    ~Actor();

    // operators
    Actor& operator=(const Actor &obj);
    friend ostream& operator<<(ostream& out,const Actor &obj);
    friend istream& operator>>(istream& in,Actor &obj);

    Actor &operator++();
    Actor operator++(int);

    Actor operator+(const Actor &obj);
    Actor operator+(int age);
    Actor operator-(const Actor &obj);
    Actor operator-(int age);

    operator string();
    operator string() const;

    bool operator==(const Actor &obj);
    bool operator<(const Actor &obj);

    string operator[](int index);

    // no & for Actor because we don't want to modify it, passed by value
    // commutative, and friend so we can access private members
    friend Actor operator+(Actor A,const Movie &obj);
    friend Actor operator+(const Movie &obj,Actor A);

    // methods
//      see if an actors stars in a given movie
//      format names of movies
// not const because i modify it's name
    void formatMovies();
    void playsIn(string movie) const;

    // setter
    void setName(string name);
    void setAge(int age);
    void setSalary(float salary);
    void setStarsIn(vector<string> starsIn);

};

Actor::Actor() {
    this->name = "None";
    this->age = 0;
    this->salary = 0;
}

Actor::Actor(string name) {
    this->name = name;
    this->age = 0;
    this->salary = 0;
}

Actor::Actor(string name, int age) {
    this->name = name;
    this->age = age;
    this->salary = 0;
}

Actor::Actor(string name, int age, float salary, vector<string> starsIn) {
    this->name = name;
    this->age = age;
    this->salary = salary;
    for(int i=0;i<starsIn.size();i++)
        this->starsIn.push_back(starsIn[i]);
}

Actor::Actor(const Actor &obj) {
    this->name = obj.name;
    this->age = obj.age;
    this->salary = obj.salary;
    for(int i=0;i<obj.starsIn.size();i++)
        this->starsIn.push_back(obj.starsIn[i]);
}

Actor::~Actor() {
    if(this->name.empty() == 0) this->name.clear();
    this->age = 0;
    this->salary = 0;
    if(this->starsIn.empty() == 0) this->starsIn.clear();
}

Actor& Actor::operator=(const Actor &obj) {
    if(this != &obj)
    {
        this->name = obj.name;
        this->age = obj.age;
        this->salary = obj.salary;
        if(this->starsIn.empty() == 0) this->starsIn.clear();
        for(int i=0;i<obj.starsIn.size();i++)
            this->starsIn.push_back(obj.starsIn[i]);
    }
    return *this;
}

void Actor::setName(string name) {
    this->name = name;
}

void Actor::setAge(int age) {
    this->age = age;
}

void Actor::setSalary(float salary) {
    this->salary = salary;
}

void Actor::setStarsIn(vector<string> starsIn) {
    if(this->starsIn.empty() == 0) this->starsIn.clear();
    this->starsIn = starsIn;
}

ostream& operator<<(ostream& out,const Actor &obj) {
    out<<"Name: "<<obj.name<<endl;
    out<<"Age: "<<obj.age<<endl;
    out<<"Salary: "<<obj.salary<<endl;
    out<<"Stars in: "<<endl;
    for(int i=0;i<obj.starsIn.size();i++)
        out<<"\t - "<<obj.starsIn[i]<<endl;

    return out;
}

istream& operator>>(istream& in,Actor &obj) {
    int temp;
    string tempString;
    cout<<"Enter name: "<<endl;
    getline(in,obj.name);
    cout<<"Enter age: "<<endl;
    in>>obj.age;
    cout<<"Enter salary: "<<endl;
    in>>obj.salary;
    cout<<"Enter number of movies in which he/she stars:\n";
    in>>temp;
    in.get();
    if(obj.starsIn.empty() == 0) obj.starsIn.clear();
    for(int i=0;i<temp;i++)
    {
        cout<<"\tEnter movie "<<i+1<<": "<<endl;
        getline(in,tempString);
        obj.starsIn.push_back(tempString);
    }

    return in;
}

Actor &Actor::operator++() {
    this->age += 1;
    return *this;
}

Actor Actor::operator++(int) {
    Actor temp(*this);
    this->age += 1;
    return temp;
}

Actor Actor::operator+(const Actor &obj) {
    Actor temp(*this);
    temp.age += obj.age;
    return temp;
}

Actor Actor::operator+(int age) {
    Actor temp(*this);
    temp.age += age;
    return temp;
}

Actor Actor::operator-(const Actor &obj) {
    Actor temp(*this);
    temp.age -= obj.age;
    return temp;
}

Actor Actor::operator-(int age) {
    Actor temp(*this);
    temp.age -= age;
    return temp;
}

Actor::operator string() {
    return this->name;
}

Actor::operator string() const {
    return this->name;
}

string Actor::operator[](int index) {
    if(this->starsIn.empty() == 0 && index >= 0 && index < this->starsIn.size())
        return this->starsIn[index];
    cout<<"~ Index invalid\n";
}

bool Actor::operator==(const Actor &obj) {
    if(this->name != obj.name) return false;
    if(this->starsIn != obj.starsIn) return false;
    if(this->age != obj.age) return false;
    if(this->salary != obj.salary) return false;

    return true;
}

bool Actor::operator<(const Actor &obj) {
    if(this->age >= obj.age) return false;
    if(this->name >= obj.name) return false;
    if(this->salary >= obj.salary) return false;
    if(this->starsIn >= obj.starsIn) return false;

    return true;
}

// no & for Actor because we want to modify it, passed by value
// commutative, and friend so we can access private members
Actor operator+(Actor A,const Movie &obj) {
    string temp;
    temp = obj.getName();
    A.starsIn.push_back(temp);
    return A;
}

Actor operator+(const Movie &obj,Actor A) {
    string temp;
    temp = obj.getName();
    A.starsIn.push_back(temp);
    return A;
}

void Actor::formatMovies() {
    for(int i=0;i<this->starsIn.size();i++)
    {
        this->starsIn[i][0] = toupper(this->starsIn[i][0]);
        for(int j=1;j<this->starsIn[i].size();j++)
            this->starsIn[i][j] = tolower(this->starsIn[i][j]);
    }
}

// const so i can use it in const function for functionalities
void Actor::playsIn(string movie) const {
    int ok = 0;
    for(int i=0;i<movie.size();i++) movie[i] = tolower(movie[i]);
    movie[0] = toupper(movie[0]);
    for(int i=0;i<this->starsIn.size();i++)
        if(movie == this->starsIn[i])
        {
            ok = 1;
            break;
        }
    if(ok) cout<<"Yes, he stars in: "<<movie;
    else cout<<"No, he doesn't star in: "<<movie;
    cout<<endl;
}

// 4 functions for every class to show functionalities
class Functionalities {
private:
    bool ret;

public:
    // constructor
    Functionalities();

    // methods
    void showMovie();
    void showSeries();
    void showUser();
    void showActor();

    void functionalitiesMovie(const Movie &obj);
    void functionalitiesSeries(const Series &obj);
    // not const because i modify it's name
    void functionalitiesUser(User &obj);
    // not const because i modify it's name
    void functionalitiesActor(Actor &obj);

    // getter
    bool getReturn() {return this->ret;}
    // setter
    void setReturn(bool ret){this->ret = ret;}
};

Functionalities::Functionalities() {
    this->ret = false;
}

void Functionalities::showMovie() {
    for(int i=0;i<10;i++) cout<<"-";
    cout<<" FUNCTIONALITIES ";
    for(int i=0;i<10;i++) cout<<"-";
    cout<<endl;

    cout<<"1. Find in which era the movie belongs to \n";
    cout<<"2. Find if the movie is appropriate for kids \n";
    cout<<"3. See if it's a highly rated film \n";
    cout<<"0. Go back\n";
}

void Functionalities::showSeries() {
    for(int i=0;i<10;i++) cout<<"-";
    cout<<" FUNCTIONALITIES ";
    for(int i=0;i<10;i++) cout<<"-";
    cout<<endl;

    cout<<"1. See how long a season is\n";
    cout<<"2. See how long the whole series is \n";
    cout<<"0. Go back\n";
}

void Functionalities::showUser() {
    for(int i=0;i<10;i++) cout<<"-";
    cout<<" FUNCTIONALITIES ";
    for(int i=0;i<10;i++) cout<<"-";
    cout<<endl;

    cout<<"1. Format name of user\n";
    cout<<"2. See age restrictions \n";
    cout<<"0. Go back\n";
}

void Functionalities::showActor() {
    for(int i=0;i<10;i++) cout<<"-";
    cout<<" FUNCTIONALITIES ";
    for(int i=0;i<10;i++) cout<<"-";
    cout<<endl;

    cout<<"1. Format names of movies\n";
    cout<<"2. See if he plays in a movie \n";
    cout<<"0. Go back\n";
}

void Functionalities::functionalitiesMovie(const Movie &obj) {
    this->showMovie();
    while(true)
    {
        int option;
        cout<<"Enter option: "<<endl;
        cin>>option;
        cin.get();

        switch (option) {
            case 0:
            {
                this->ret = true;
                return;
            }

            case 1:
            {
                obj.eraOfMovie();
                this->showMovie();
                break;
            }

            case 2:
            {
                obj.verifyAge();
                this->showMovie();
                break;
            }

            case 3:
            {
                obj.verifyRating();
                this->showMovie();
                break;
            }

            default:
                cout<<"Options is not valid, please enter another number\n";
        }
    }
}

void Functionalities::functionalitiesSeries(const Series &obj) {
    this->showSeries();
    while(true)
    {
        int option;
        cout<<"Enter option: "<<endl;
        cin>>option;
        cin.get();

        switch (option) {
            case 0:
            {
                this->ret = true;
                return;
            }

            case 1:
            {
                obj.getLengthSeason();
                this->showSeries();
                break;
            }

            case 2:
            {
                obj.getLengthSeries();
                this->showSeries();
                break;
            }

            default:
                cout<<"Options is not valid, please enter another number\n";
        }
    }
}

void Functionalities::functionalitiesUser(User &obj) {
    this->showUser();
    while(true)
    {
        int option;
        cout<<"Enter option: "<<endl;
        cin>>option;
        cin.get();

        switch (option) {
            case 0:
            {
                this->ret = true;
                return;
            }

            case 1:
            {
                obj.formatName();
                this->showUser();
                break;
            }

            case 2:
            {
                obj.ageRestriction(2023);
                this->showUser();
                break;
            }

            default:
                cout<<"Options is not valid, please enter another number\n";
        }
    }
}

void Functionalities::functionalitiesActor(Actor &obj) {
    this->showActor();
    while(true)
    {
        int option;
        cout<<"Enter option: "<<endl;
        cin>>option;
        cin.get();

        switch (option) {
            case 0:
            {
                this->ret = true;
                return;
            }

            case 1:
            {
                obj.formatMovies();
                this->showActor();
                break;
            }

            case 2:
            {
                string temp;
                cout<<"Enter movie: \n";
                getline(cin,temp);
                obj.playsIn(temp);
                this->showActor();
                break;
            }

            default:
                cout<<"Options is not valid, please enter another number\n";
        }
    }
}

class SubMenu {
private:
    string keyWord;
    bool back;
    vector<Movie*> movies;
    vector<Series*> series;
    vector<User*> users;
    vector<Actor*> actors;

public:
    // constructors
//    didn't make constructor with no parameters because i don't need it
//    i add only addresses in vector
    SubMenu(string _class, vector<Movie*> movies);
    SubMenu(string _class, vector<Series*> series);
    SubMenu(string _class, vector<User*> users);
    SubMenu(string _class, vector<Actor*> actors);
    ~SubMenu();

    // methods
    void showSubMenu();
//    overloading for submenuEngine for every class
    void submenuEngine(vector<Movie*> &movies);
    void submenuEngine(vector<Series*> &series);
    void submenuEngine(vector<User*> &users);
    void submenuEngine(vector<Actor*> &actors);
//    overloading for all types of vector
    bool verifyIndex(const vector<Movie*> &movies,int index);
    bool verifyIndex(const vector<Series*> &series,int index);
    bool verifyIndex(const vector<User*> &users,int index);
    bool verifyIndex(const vector<Actor*> &actors,int index);

    // getter
    bool getBack(){return this->back;}

    // setter
    void setBack(bool back){this->back = back;}
};

void SubMenu::showSubMenu() {
    for(int i=0;i<10;i++) cout<<"-";
    cout<<" SUB-MENU ";
    for(int i=0;i<10;i++) cout<<"-";
    cout<<endl;

    cout<<"1. Add "<<this->keyWord<<endl;
    cout<<"2. Delete "<<this->keyWord<<endl;
    cout<<"3. Update "<<this->keyWord<<endl;
    cout<<"4. Print "<<this->keyWord<<endl;
    cout<<"5. Functionalities for "<<this->keyWord<<endl;
    cout<<"0. Go back\n";
}

void SubMenu::submenuEngine(vector<Movie*> &movies) {
    this->showSubMenu();
    while (true)
    {
        int option;
        cout<<"Enter option: "<<endl;
        cin>>option;
        cin.get();
        switch (option)
        {
            case 0:
                this->back = true;
                return;
            case 1:
            {
                // read obj and add to vector
                Movie *mov = new Movie();
                cin>>*mov;
                // i add only addresses in vector
                movies.push_back(mov);
                this->showSubMenu();
                break;
            }
            case 2:
            {
                // delete object at given index from vector
                int index;
                cout<<"Give index of movie(starting from 0): "<<endl;
                cin>>index;
                cin.get();
                if(this->verifyIndex(movies,index)) movies.erase(movies.begin() + index);
                else cout<<"~ Index invalid\n";
                this->showSubMenu();
                break;
            }
            case 3:
            {
                // update object at given index
                int index;
                char tempName[255];
                cout<<"Give index of movie(starting from 0): \n";
                cin>>index;
                cin.get();
                if (this->verifyIndex(movies,index))
                {
                    cout<<"Enter new name for movie: \n";
                    cin.getline(tempName,255);
                    movies[index]->setName(tempName);
                    cout<<*movies[index]<<endl;
                    cout<<"Movie was updated successfully\n";
                }
                else cout<<"~ Index invalid\n";
                this->showSubMenu();
                break;
            }
            case 4:
            {
                // print objects info on screen
                for(int i=0;i<movies.size();i++)
                {
                    cout<<"--- MOVIE "<<i+1<<" ---\n";
                    cout<<*movies[i]<<endl;
                }
                this->showSubMenu();
                break;
            }
            case 5:
            {
                int index;
                Functionalities F;

                cout<<"Give index of movie(starting from 0): \n";
                cin>>index;
                cin.get();
                if (this->verifyIndex(movies,index))
                {
                    F.functionalitiesMovie(*movies[index]);
                    if(F.getReturn() == false) return;
                    F.setReturn(false);
                }
                else cout<<"~ Index invalid\n";
                this->showSubMenu();
                break;
            }
            default:
                cout<<"Options is not valid, please enter another number\n";
        }
    }
}

void SubMenu::submenuEngine(vector<Series*> &series) {
    this->showSubMenu();
    while (true)
    {
        int option;
        cout<<"Enter option: "<<endl;
        cin>>option;
        cin.get();
        switch (option)
        {
            case 0:
                this->back = true;
                return;
            case 1:
            {
                // read obj and add to vector
                // i add only addresses in vector
                Series *ser = new Series();
                cin>>*ser;
                series.push_back(ser);
                this->showSubMenu();
                break;
            }
            case 2:
            {
                // delete object at given index from vector
                int index;
                cout<<"Give index of series(starting from 0): "<<endl;
                cin>>index;
                cin.get();
                if(this->verifyIndex(series,index)) series.erase(series.begin() + index);
                else cout<<"~ Index invalid\n";
                this->showSubMenu();
                break;
            }
            case 3:
            {
                // update object at given index
                int index;
                char tempName[255];
                cout<<"Give index of series(starting from 0): \n";
                cin>>index;
                cin.get();
                if(this->verifyIndex(series,index))
                {
                    cout<<"Enter new name for series: \n";
                    cin.getline(tempName,255);
                    series[index]->setName(tempName);
                    cout<<*series[index]<<endl;
                    cout<<"Series was updated successfully\n";
                }
                else cout<<"~ Invalid index\n";
                this->showSubMenu();
                break;
            }
            case 4:
            {
                // print objects info on screen
                for(int i=0;i<series.size();i++)
                {
                    cout<<"--- SERIES "<<i+1<<" ---\n";
                    cout<<*series[i]<<endl;
                }
                this->showSubMenu();
                break;
            }
            case 5:
            {
                int index;
                Functionalities F;

                cout<<"Give index of series(starting from 0): "<<endl;
                cin>>index;
                cin.get();
                if(this->verifyIndex(series,index))
                {
                    F.functionalitiesSeries(*series[index]);
                    if(F.getReturn() == false) return;
                    F.setReturn(false);
                }
                else cout<<"~ Index invalid\n";
                this->showSubMenu();
                break;
            }
            default:
                cout<<"Options is not valid, please enter another number\n";
        }
    }
}

void SubMenu::submenuEngine(vector<User*> &users) {
    this->showSubMenu();
    while (true)
    {
        int option;
        cout<<"Enter option: "<<endl;
        cin>>option;
        cin.get();
        switch (option)
        {
            case 0:
                this->back = true;
                return;
            case 1:
            {
                // read obj and add to vector
                // i add only addresses in vector
                User *usr = new User();
                cin>>*usr;
                users.push_back(usr);
                this->showSubMenu();
                break;
            }
            case 2:
            {
                // delete object at given index from vector
                int index;
                cout<<"Give index of user(starting from 0): "<<endl;
                cin>>index;
                cin.get();
                if (this->verifyIndex(users,index)) users.erase(users.begin() + index);
                else cout<<"~ Invalid index\n";
                this->showSubMenu();
                break;
            }
            case 3:
            {
                // update object at given index
                int index;
                char tempName[255];
                cout<<"Give index of user(starting from 0): \n";
                cin>>index;
                cin.get();
                if(this->verifyIndex(users,index))
                {
                    cout<<"Enter new last name for user: \n";
                    cin.getline(tempName,255);
                    users[index]->setLastName(tempName);
                    cout<<*users[index]<<endl;
                    cout<<"User was updated successfully\n";
                }
                else cout<<"~ Index invalid\n";
                this->showSubMenu();
                break;
            }
            case 4:
            {
                // print objects info on screen
                for(int i=0;i<users.size();i++)
                {
                    cout<<"--- USER "<<i+1<<" ---\n";
                    cout<<*users[i]<<endl;
                }
                this->showSubMenu();
                break;
            }
            case 5:
            {
                int index;
                Functionalities F;
                cout<<"Give index of user(starting from 0): "<<endl;
                cin>>index;
                cin.get();
                if (this->verifyIndex(users,index))
                {
                    F.functionalitiesUser(*users[index]);
                    if(F.getReturn() == false) return;
                    F.setReturn(false);
                }
                else cout<<"~ Index invalid\n";
                this->showSubMenu();
                break;
            }
            default:
                cout<<"Options is not valid, please enter another number\n";
        }
    }
}

void SubMenu::submenuEngine(vector<Actor*> &actors) {
    this->showSubMenu();
    while (true)
    {
        int option;
        cout<<"Enter option: "<<endl;
        cin>>option;
        cin.get();
        switch (option)
        {
            case 0:
                this->back = true;
                return;
            case 1:
            {
                // read obj and add to vector
                // i add only addresses in vector
                Actor *act = new Actor();
                cin>>*act;
                actors.push_back(act);
                this->showSubMenu();
                break;
            }
            case 2:
            {
                // delete object at given index from vector
                int index;
                cout<<"Give index of actors(starting from 0): "<<endl;
                cin>>index;
                cin.get();
                if(this->verifyIndex(actors,index)) actors.erase(actors.begin() + index);
                else cout<<"~ Index invalid\n";
                this->showSubMenu();
                break;
            }
            case 3:
            {
                // update object at given index
                int index;
                char tempName[255];
                cout<<"Give index of actor(starting from 0): \n";
                cin>>index;
                cin.get();
                if(this->verifyIndex(actors,index))
                {
                    cout<<"Enter new last name for user: \n";
                    cin.getline(tempName,255);
                    actors[index]->setName(tempName);
                    cout<<*actors[index]<<endl;
                    cout<<"Actor was updated successfully\n";
                }
                else cout<<"~ Invalid index\n";
                this->showSubMenu();
                break;
            }
            case 4:
            {
                // print objects info on screen
                for(int i=0;i<actors.size();i++)
                {
                    cout<<"--- Actor "<<i+1<<" ---\n";
                    cout<<*actors[i]<<endl;
                }
                this->showSubMenu();
                break;
            }
            case 5:
            {
                int index;
                Functionalities F;

                cout<<"Give index of actor(starting from 0): "<<endl;
                cin>>index;
                cin.get();
                if(this->verifyIndex(actors,index))
                {
                    F.functionalitiesActor(*actors[index]);
                    if(F.getReturn() == false) return;
                    F.setReturn(false);
                    this->showSubMenu();
                }
                else cout<<"~ Index invalid\n";
                this->showSubMenu();
                break;
            }
            default:
                cout<<"Options is not valid, please enter another number\n";
        }
    }
}

SubMenu::SubMenu(string _class,vector<Movie*> movies) {
    this->keyWord = _class;
    this->back = false;
    this->movies = movies;
}

SubMenu::SubMenu(string _class,vector<Series*> series) {
    this->keyWord = _class;
    this->back = false;
    this->series = series;
}

SubMenu::SubMenu(string _class,vector<User*> users) {
    this->keyWord = _class;
    this->back = false;
    this->users = users;
}

SubMenu::SubMenu(string _class,vector<Actor*> actors) {
    this->keyWord = _class;
    this->back = false;
    this->actors = actors;
}

SubMenu::~SubMenu() {
    this->back = false;
    if(this->keyWord.empty() == 0) this->keyWord.clear();
    if(this->movies.empty() == 0) this->movies.clear();
    if(this->series.empty() == 0) this->series.clear();
    if(this->users.empty() == 0) this->users.clear();
    if(this->actors.empty() == 0) this->actors.clear();
}

bool SubMenu::verifyIndex(const vector<Movie *> &movies,int index) {
    if(index < 0 || index >= movies.size()) return false;
    return true;
}

bool SubMenu::verifyIndex(const vector<Series *> &series,int index) {
    if(index < 0 || index >= series.size()) return false;
    return true;
}

bool SubMenu::verifyIndex(const vector<User *> &users,int index) {
    if(index < 0 || index >= users.size()) return false;
    return true;
}

bool SubMenu::verifyIndex(const vector<Actor *> &actors,int index) {
    if(index < 0 || index >= actors.size()) return false;
    return true;
}

class MainMenu {
private:
    unsigned short int nrOptions;
    vector<string> nameOptions;

public:
    // constructors
    MainMenu();
    ~MainMenu();

    // methods
    void showMainMenu();
    unsigned short int getOption();
    void processOption();
};

MainMenu::MainMenu() {
    this->nrOptions = 4;
    this->nameOptions = {"Movie","Series","User","Actor"};
}

MainMenu::~MainMenu() {
    this->nrOptions = 0;
    if(this->nameOptions.empty() == 0) this->nameOptions.clear();
}

void MainMenu::showMainMenu() {
    for(int i=0;i<10;i++) cout<<"-";
    cout<<" MENU ";
    for(int i=0;i<10;i++) cout<<"-";
    cout<<endl;
    for(int i=1;i<=this->nrOptions;i++)
        cout<<i<<". Access "<<this->nameOptions[i-1]<<" menu\n";
    cout<<"0. Exit\n";
}

unsigned short int MainMenu::getOption() {
    int temp;
    cout<<"Enter option: "<<endl;
    cin>>temp;
    cin.get();
    return temp;
}

void MainMenu::processOption() {
    // vectors for each class containing addresses to objects
    vector<Movie*> m;
    vector<Series*> s;
    vector<User*> u;
    vector<Actor*> a;

    SubMenu M("Movie",m),S("Series",s),U("User",u),A("Actor",a);

    this->showMainMenu();
    while(true)
    {
        int option = this->getOption();
        switch (option) {
            case 0:
                return;
            case 1:
            {
//              pass by reference to modify "global" vectors m,s,u,a
                M.submenuEngine(m);
                if(M.getBack() == false) return;
                M.setBack(false);
                this->showMainMenu();
                break;
            }
            case 2:
            {
                S.submenuEngine(s);
                if(S.getBack() == false) return;
                S.setBack(false);
                this->showMainMenu();
                break;
            }
            case 3:
            {
                U.submenuEngine(u);
                if(U.getBack() == false) return;
                U.setBack(false);
                this->showMainMenu();
                break;
            }
            case 4:
            {
                A.submenuEngine(a);
                if(A.getBack() == false) return;
                A.setBack(false);
                this->showMainMenu();
                break;
            }
            default:
                cout<<"Options is not valid, please enter another number\n";
        }
    }
}

int main() {
//    MOVIES TESTS:
    /*
    Movie film("Spargerea",126,9.03,'G');
    cout<<film<<endl;

    film.verifyRating();
    film.verifyAge();

    Movie film2;
    film2 = film;
    cout<<(film2 == film)<<endl;
    film2++;
    cout<<film2<<endl;
    cout<<(film2 == film)<<endl;
    float x;
    x = film;
    cout<<x<<endl;


    Movie film3;
    cin>>film3;
    cout<<endl<<film3;
    film3.eraOfMovie();
    */

//    SERIES TESTS:
    /*
    int v[] = {2,3,1};
    vector<vector<int>> m{
            {23,44},
            {15,74,22},
            {68},
    };

    vector<vector<int>> t{
            {2,5},
            {1,7,2},
            {6},
    };
    Series serial("Buciumeala",3,v,m);
    cout<<serial<<endl;

    serial.getLengthSeason();
    serial.getLengthSeries();


    Series serial2(serial);
    cout<<serial2<<endl;

    serial2.setDurationEpisodes(t);

    for(int i=0;i<serial2.getDurationEpisodes().size();i++)
    {
        for(int j=0;j<serial2.getDurationEpisodes()[i].size();j++)
            cout<<serial2.getDurationEpisodes()[i][j]<<" ";
        cout<<endl;
    }

    Series serial3;
    serial3.setNrSeasons(3);
    serial3.setNrEpisodes(v,3);
    cout<<serial3<<endl;

    Series ser1("nume",4.55,1999);

    Series ser2;
    ser2 = ser1;
    cout<<(ser2 == ser1)<<endl;
    ser2++;
    cout<<ser2<<endl;
    cout<<ser2+ser1<<endl;
    cout<<(ser2 == ser1)<<endl;
    string x;
    x = ser1;
    cout<<x<<endl;


//    Series serial3;
    cin>>serial3;
    serial3 = serial;
    cout<<serial3<<endl;
    */

//    USER TESTS:
    /*
    vector<string> t = {"test","movie"};
    User A("mihai","ciupercescu",2000,t);
    cout<<A;

    User B;
    cin>>B;
    cout<<endl<<B<<endl;

    User C;
    C = A;
    cout<<(A==A)<<endl;
    cout<<C<<endl;
    cout<<C[0]<<endl;
    string a = C;
    cout<<a<<endl;
    C++;
    cout<<(A<C)<<endl;


    B = A;
    cout<<B<<endl<<C<<endl;

    C.formatName();
    cout<<C<<endl;
    C.ageRestriction(2023);
    */

//    ACTOR TESTS:
    /*
    vector<string> x{"Sugus","Maximus"};
    Actor A1("marius",23,1000,x);

    A1.formatMovies();
    A1.playsIn("sugus");

    Actor A2(A1);
    cout<<(A1==A2)<<endl;
    cout<<++A1<<endl;
    cout<<(A1==A2)<<endl;
    cout<<A2[0]<<endl;
    string a = A2;
    cout<<a<<endl;
    cout<<A2<<endl;

    Actor A3;
    cin>>A3;
    cout<<A3<<endl;
    A3 = A1;
    cout<<A3<<endl;
    */

//    MENU TESTS

//    CC IS CALLED WHEN PUSHING BACK IN VECTOR
    /*
    User A,B;
    vector<User*> u;
    u.push_back(&A);
    u.push_back(&B);
    for(int i=0;i<u.size();i++)
        cout<<*u[i]<<endl;
    */

//    TWO CLASS ADDITION TESTS
    /*
    Movie film("Spargerea",126,9.03,'G');
    vector<string> x{"Sugus","Maximus"};
    Actor A1("marius",23,1000,x);
    cout<<A1+film<<endl;
    cout<<film+A1<<endl;
    cout<<A1<<endl;
    cout<<film<<endl;
    */

//    RUN CONFIGURATION
    /*
    MainMenu M;
    M.processOption();
    */

    return 0;
}
