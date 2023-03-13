#include <iostream>
#include <string.h>

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

    // methods

    // getters
    int getReleaseYear();
    float getDuration();
    bool getIsTop10();
    double getRating();
    char getAgeRating();
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
    // in.getline() to read the whole line until \n
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

    cout<<"Age rating: "<<endl;
    in>>obj.ageRating;

    return in;
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

int Movie::getReleaseYear() {
    return releaseYear;
}

float Movie::getDuration() {
    return duration;
}

bool Movie::getIsTop10() {
    return isTop10;
}

double Movie::getRating() {
    return rating;
}

char Movie::getAgeRating() {
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

int main() {
    Movie film("Spargerea",126,9.03,'G');
    cout<<film<<endl;

    Movie film2;
    film2 = film;
    cout<<film2<<endl;

    Movie film3;
    cin>>film3;
    cout<<endl<<film3;
    return 0;
}
