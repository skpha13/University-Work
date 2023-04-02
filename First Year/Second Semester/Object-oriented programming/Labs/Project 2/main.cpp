#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using std::string;
using std::cout;
using std::cin;
using std::istream;
using std::ostream;
using std::endl;

class Image {
protected:
    string name,path,extension;
    double rezolutieX,rezolutieY;
public:
    Image(string name = "Unnamed",string extension = "png",string path = "Root",double rezolutieX = 0,double rezolutieY = 0);
    Image(const Image& obj);
    Image& operator=(const Image& obj);
    friend istream& operator>>(istream& in, Image& obj);
    friend ostream& operator<<(ostream& out, const Image& obj);
};

Image::Image(string name, string extension, string path, double rezolutieX, double rezolutieY) {
    this->name = name;
    this->extension = extension;
    this->path = path;
    this->rezolutieX = rezolutieX;
    this->rezolutieY = rezolutieY;
}

Image::Image(const Image &obj) {
    this->name = obj.name;
    this->extension = obj.extension;
    this->path = obj.path;
    this->rezolutieX = obj.rezolutieX;
    this->rezolutieY = obj.rezolutieY;
}

Image& Image::operator=(const Image &obj) {
    if (this != &obj)
    {
        if(!this->name.empty()) this->name.clear();
        this->name = obj.name;
        if(!this->extension.empty()) this->extension.clear();
        this->extension = obj.extension;
        if(!this->path.empty()) this->path.clear();
        this->path = obj.path;
        this->rezolutieX = obj.rezolutieX;
        this->rezolutieY = obj.rezolutieY;
    }
    return *this;
}

istream& operator>>(istream& in, Image& obj) {
    if(!obj.name.empty()) obj.name.clear();
    if(!obj.path.empty()) obj.path.clear();
    cout<<"Enter name: \n";
    in>>obj.name;
    cout<<"Specify file extension: \n";
    in>>obj.extension;
    cout<<"Enter path to image: \n";
    in>>obj.path;
    cout<<"Enter width: \n";
    in>>obj.rezolutieX;
    cout<<"Enter height: \n";
    in>>obj.rezolutieY;

    return in;
}

ostream& operator<<(ostream& out, const Image& obj) {
    out<<"Name: "<<obj.name<<"."<<obj.extension<<endl;
    out<<"Path to image: "<<obj.path<<endl;
    out<<"Width: "<<obj.rezolutieX<<" pixels\n";
    out<<"Height: "<<obj.rezolutieY<<" pixels\n";

    return out;
}

class Effect:public Image {
private:
    bool effect;
public:
    Effect(string name = "Unnamed",string extension = "png",string path = "Root",double rezolutieX = 0,double rezolutieY = 0,bool effect = 0);
    Effect(const Effect& obj);
    Effect& operator=(const Effect& obj);
    friend istream& operator>>(istream& in, Effect& obj);
    friend ostream& operator<<(ostream& out, const Effect& obj);
};

Effect::Effect(string name, string extension, string path, double rezolutieX, double rezolutieY, bool effect):
    Image(name,extension,path,rezolutieX,rezolutieY)
{
    this->effect = effect;
}

Effect::Effect(const Effect &obj):Image(obj) {
    this->effect = obj.effect;
}

Effect& Effect::operator=(const Effect &obj) {
    if(this != &obj)
    {
        Image::operator=(obj);
        this->effect = obj.effect;
    }
    return *this;
}

istream& operator>>(istream& in, Effect& obj) {
    in>>(Image&)obj;
    cout<<"Are there effects applied on the image? (yes:1 no:0) \n";
    in>>obj.effect;

    return in;
}

ostream& operator<<(ostream& out, const Effect& obj) {
    out<<(Image&)obj;
    out<<"Has effects applied: "<<obj.effect<<endl;

    return out;
}

class Adjustment:public Image {
private:
    double brightness, contrast, hue;
    bool adjustment;
public:
    Adjustment(string name = "Unnamed",string extension = "png",string path = "Root",double rezolutieX = 0,double rezolutieY = 0,
               bool adjustment = false, double brightness = 0, double contrast = 0, double  hue = 0);
    Adjustment(const Adjustment& obj);
    Adjustment& operator=(const Adjustment& obj);
    friend istream& operator>>(istream& in, Adjustment& obj);
    friend ostream& operator<<(ostream& out, const Adjustment& obj);
};

Adjustment::Adjustment(string name, string extension, string path, double rezolutieX, double rezolutieY,
                       bool adjustment, double brightness, double contrast, double hue):
        Image(name,extension,path,rezolutieX,rezolutieY)
{
    this->adjustment = adjustment;
    this->brightness = brightness;
    this->contrast = contrast;
    this->hue = hue;
}

Adjustment::Adjustment(const Adjustment &obj): Image(obj) {
    this->adjustment = obj.adjustment;
    this->brightness = obj.brightness;
    this->contrast = obj.contrast;
    this->hue = obj.hue;
}

Adjustment& Adjustment::operator=(const Adjustment &obj) {
    if(this != &obj)
    {
        Image::operator=(obj);
        this->adjustment = obj.adjustment;
        this->brightness = obj.brightness;
        this->contrast = obj.contrast;
        this->hue = obj.hue;
    }
    return *this;
}

istream& operator>>(istream& in, Adjustment& obj) {
    in>>(Image&)obj;
    cout<<"Is the image adjusted? (yes:1 no:0)\n";
    in>>obj.adjustment;
    cout<<"Enter brightness [-100,100]: \n";
    in>>obj.brightness;
    cout<<"Enter contrast [-100,100]: \n";
    in>>obj.contrast;
    cout<<"Enter hue [0,255]: \n";
    in>>obj.hue;

    return in;
}

ostream& operator<<(ostream& out, const Adjustment& obj) {
    out<<(Image&)obj;
    out<<"Has adjustments applied: "<<obj.adjustment<<endl;
    out<<"Brightness value: "<<obj.brightness<<endl;
    out<<"Contrast value: "<<obj.contrast<<endl;
    out<<"Hue value: "<<obj.hue<<endl;

    return out;
}

int main()
{
//    OPENCV TEST
    /*
    std::string image_path = samples::findFile("starry_night.jpg");
    Mat img = imread(image_path, IMREAD_COLOR);
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
    {
        imwrite("starry_night.png", img);
    }
     */

//    IMAGE TESTS
    /*Image i;
    cout<<i<<endl;
    cin>>i;
    cout<<i<<endl;
    Image i2(i);
    cout<<i2<<endl;
    Image i3;
    i3 = i2;
    cout<<i3<<endl;*/

//    EFFECT TESTS
    /*Effect e;
    cout<<e<<endl;
    cin>>e;
    cout<<e<<endl;*/

//    ADJUSTMENT TESTS
    /*Adjustment a;
    cout<<a<<endl;
    cin>>a;
    cout<<a<<endl;
    Adjustment a2;
    a2 = a;
    cout<<a2<<endl;*/

//  TODO method to find aspect ratio
    return 0;
}