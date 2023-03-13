#include <iostream>
#include <string.h>

using namespace std;

// class user
// class movie
// class series
// class actors

class Movie{
private:
    int realeaseYear;
    char* name;
    float duration; // minutes
    bool isSeen,isTop10;
    double rating;
    char* description;
    char ageRating; // G = general audience, R = restricted
public:
    // constructors
    Movie();
    Movie(const Movie &obj);
    ~Movie();
    // operators

    // methods

    // getters
    int getRealeaseYear();
    float getDuration();
    bool getIsSeen();
    bool getIsTop10();
    double getRating();
    char getAgeRating();
    const char* getName() const;
    const char* getDescription() const;

    // setters
};

Movie::Movie() {
    this->realeaseYear = 0;
    this->name = new char[strlen("Unnamed")+1];
    strcpy(this->name,"Unnamed");
    this->duration = 0;
    this->isSeen = false;
    this->isTop10 = false;
    this->rating = 0;
    this->description = new char[strlen("No description given")+1];
    strcpy(this->description,"No description given");
    this->ageRating = 'R';
}

Movie::Movie(const Movie &obj) {
    this->realeaseYear = obj.realeaseYear;
    this->name = new char[strlen(obj.name)+1];
    strcpy(this->name,obj.name);
    this->duration = obj.duration;
    this->isSeen = obj.isSeen;
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

int Movie::getRealeaseYear() {
    return realeaseYear;
}

float Movie::getDuration() {
    return duration;
}

bool Movie::getIsSeen() {
    return isSeen;
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

int main() {
    Movie film;
    cout<<film.getName()<<" "<<film.getDescription()<<endl;
    cout<<film.getRealeaseYear()<<" "<<film.getAgeRating()<<" "<<film.getDuration()<<" "<<film.getIsSeen()<<" "<<film.getIsTop10();
    cout<<" "<<film.getRating()<<endl;
    return 0;
}
