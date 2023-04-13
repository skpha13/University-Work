#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <iostream>

using cv::Mat;
using cv::samples::findFile;
using cv::IMREAD_COLOR;
using cv::waitKey;

using std::string;
using std::cout;
using std::cin;
using std::istream;
using std::ostream;
using std::endl;

// block of code to disable opencv warnings
int dummy_error_handler(int status
        , char const* func_name
        , char const* err_msg
        , char const* file_name
        , int line
        , void* userdata)
{
    //Do nothing -- will suppress console output
    return 0;   //Return value is not used
}

// sets warning display off
void set_dummy_error_handler()
{
    cv::redirectError(dummy_error_handler);
}

// sets warning display on
void reset_error_handler()
{
    cv::redirectError(nullptr);
}

class IOInterface {
public:
    virtual void applyAll() = 0;
    virtual void writeImg() const = 0;
};

class Image: public IOInterface {
protected:
    // boolean for image finding
    bool absolute;
    string name,path;
    Mat img;
public:
    Image(string name = "cat.png", string path = "../Images/", bool absolute = false);
    Image(const Image& obj);
    Image& operator=(const Image& obj);
    // virtual to call derivative destructors
    virtual ~Image();

    friend istream& operator>>(istream& in, Image& obj);
    friend ostream& operator<<(ostream& out, const Image& obj);

    string extension(string word) const;
    string withoutExtension(string word) const;
    void readImg();
    void showImg() const;
    void showImg(const Mat& img) const;
    void writeImg() const;
    void saveShow() const;
    void applyAll();
};

Image::Image(string name,string path, bool absolute) {
    this->name = name;
    this->path = path;
    this->absolute = absolute;
}

Image::Image(const Image &obj) {
    this->name = obj.name;
    this->path = obj.path;
    this->absolute = obj.absolute;
}

Image& Image::operator=(const Image &obj) {
    if (this != &obj)
    {
        if(!this->name.empty()) this->name.clear();
        this->name = obj.name;
        if(!this->path.empty()) this->path.clear();
        this->path = obj.path;
        this->absolute = obj.absolute;
    }
    return *this;
}

istream& operator>>(istream& in, Image& obj) {
    if(!obj.name.empty()) obj.name.clear();
    if(!obj.path.empty()) obj.path.clear();
    cout<<"Enter name: \n";
    in>>obj.name;
    cout<<"Do you want to use relative path? (1:yes 0:no)?\n";
    int temp;
    cin>>temp;
    in.get();
    if(temp == 0)
    {
        obj.absolute = true;
        cout<<"Enter path to image: \n";
        // to get \n from buffer

        getline(in,obj.path);
        // deleting "" from path
        if(obj.path[0] == '"') obj.path.erase(0,1), obj.path.pop_back();
    }
    else obj.path = "../Images/";

    return in;
}

ostream& operator<<(ostream& out, const Image& obj) {
    out<<"Name: "<<obj.name<<endl;
    out<<"Path to image: "<<obj.path + obj.name<<endl;

    return out;
}

Image::~Image() {
    if(!this->name.empty()) this->name.clear();
    if(!this->path.empty()) this->path.clear();
    this->absolute = false;
}

string Image::extension(string word) const {
    return word.substr(word.find("."),word.length());
}

string Image::withoutExtension(string word) const {
    return word.substr(0,word.find("."));
}

void Image::readImg() {
    string image_path;
    try {
        if(this->absolute == false)
        {
            string full_name = this->path + this->name;
            // silent mode true to suppress errors
            image_path = findFile(full_name,true,true);
        }
        else image_path = findFile(this->path,true,true);

        Mat temp = imread(image_path, IMREAD_COLOR);
        img.create(temp.rows,temp.cols,temp.type());
        cv::resize(img,img,temp.size());
        temp.copyTo(img);
    }
    catch(...) {cout<<"~ INVALID PATH\n"; /*return Mat::zeros(540,540,CV_8UC3);*/}
    // CV_8UC3 = 8 bit unsigned integer with 3 channels (RGB)
}

void Image::showImg() const {
//    try {
//        Mat img = this->readImg();
        cv::namedWindow("Image",cv::WINDOW_NORMAL);
//        using this function makes the window not have a title bar
//        cv::setWindowProperty("Image",cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
        double aspect_ratio = static_cast<double>(img.cols)/img.rows;
        cv::resizeWindow("Image",static_cast<int>(540*aspect_ratio),540);
        imshow("Image",img);

//        Wait for a keystroke in the window
        int k = waitKey(0);
//        27 is ascii code for esc and waitKey returns an int
        if(k == 27)
        {
            cv::destroyAllWindows();
            return ;
        }
//    }
//    catch (...) {cout<<"~ OUTPUT FAILED\n";}
}

void Image::showImg(const Mat& img) const {
    try {
        cv::namedWindow("Image",cv::WINDOW_NORMAL);
//        using this function makes the window not have a title bar
//        cv::setWindowProperty("Image",cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
        double aspect_ratio = static_cast<double>(img.cols)/img.rows;
        cv::resizeWindow("Image",static_cast<int>(540*aspect_ratio),540);
        imshow("Image",img);

//        Wait for a keystroke in the window
        int k = waitKey(0);
//        27 is ascii code for esc and waitKey returns an int
        if(k == 27)
        {
            cv::destroyAllWindows();
            return ;
        }
    }
    catch (...) {cout<<"~ OUTPUT FAILED\n";}
}

void Image::writeImg() const {
    try {
        // basically does nothing because there is nothing applied to that image
//        Mat img = this->readImg();
        string full_path = this->path + this->name;
        cv::imwrite(full_path,img);
    }
    catch (...) {cout<<"~ WRITING IMAGE FAILED\n";}
}

void Image::saveShow() const {
    cout<<"Show image on screen (yes:1 no:0)?\n";
    int temp;
    cin>>temp;
    cin.get();
    if(temp == 1) this->showImg();

    cout<<"Save image (yes:1 no:0)?\n";
    cin>>temp;
    cin.get();
    if(temp == 1) this->writeImg();
}

void Image::applyAll() {
    cout<<"~ NOTHING TO APPLY\n";
}

class Effect:public virtual Image {
protected:
    int blurAmount;
    bool effect, blackWhite, cartoon;
public:
    Effect(string name = "cat.png",string path = "../Images/",bool absolute = false, bool effect = false,
           int blurAmount = 0, bool blackWhite = false, bool cartoon = false);
    Effect(const Effect& obj);
    Effect& operator=(const Effect& obj);
    // override specifier ensures that the function is virtual and is overriding a virtual function from a base class
    virtual ~Effect() override;

    friend istream& operator>>(istream& in, Effect& obj);
    friend ostream& operator<<(ostream& out, const Effect& obj);

    void blurImg();
    void bwImg();
    void cartoonImg();
    void writeImg() const;
    void applyAll();
};

//    TODO Edited class inheritance
//    TODO Menu class
//    TODO override writeImg() function

Effect::Effect(string name, string path, bool absolute, bool effect, int blurAmount, bool blackWhite, bool cartoon):
        Image(name,path,absolute)
{
    this->effect = effect;
    this->blurAmount = blurAmount;
    this->blackWhite = blackWhite;
    this->cartoon = cartoon;
    this->readImg();
}

Effect::Effect(const Effect &obj):Image(obj) {
    this->effect = obj.effect;
    this->blurAmount = obj.blurAmount;
    this->blackWhite = obj.blackWhite;
    this->cartoon = obj.cartoon;
    this->readImg();
}

Effect& Effect::operator=(const Effect &obj) {
    if(this != &obj)
    {
        Image::operator=(obj);
        this->effect = obj.effect;
        this->blurAmount = obj.blurAmount;
        this->blackWhite = obj.blackWhite;
        this->cartoon = obj.cartoon;
        this->readImg();
    }
    return *this;
}

istream& operator>>(istream& in, Effect& obj) {
    in>>(Image&)obj;
    cout<<"Are there effects applied on the image? (yes:1 no:0) \n";
    in>>obj.effect;
    cout<<"Do you want to blur the image? (yes:1 no:0)?\n";
    int temp;
    in>>temp;
    in.get();
    if(temp == 1)
    {
        cout<<"Enter blur amount: \n";
        in>>obj.blurAmount;
    }
    cout<<"Do you want to apply Black and White effect to the image? (yes:1 no:0)?\n";
    in>>obj.blackWhite;
    cout<<"Do you want to apply Cartoon effect to the image? (yes:1 no:0)?\n";
    in>>obj.cartoon;
    obj.readImg();

    return in;
}

ostream& operator<<(ostream& out, const Effect& obj) {
    out<<(Image&)obj;
    out<<"Has effects applied: "<<obj.effect<<endl;
    out<<"Blur amount: "<<obj.blurAmount<<endl;
    return out;
}

Effect::~Effect() {
    this->effect = false;
    this->blurAmount = 0;
}

void Effect::writeImg() const {
    try {
        string full_path = "../Images with Effects/" + this->withoutExtension(this->name) + "_withEffects" + this->extension(this->name);
        cv::imwrite(full_path,this->img);
    }
    catch (...) {cout<<"~ WRITING IMAGE FAILED\n";}
}

void Effect::blurImg() {
    if(this->blurAmount > 0)
    {
        try {
            Mat blurredImage;
            // cv::GaussianBlur doesnt work with widths and heigths that are even, or 0,0
            if(this->blurAmount % 2 == 0) this->blurAmount += 1;

            cv::GaussianBlur(this->img,this->img,cv::Size(this->blurAmount,this->blurAmount),0);
//        blurredImage.copyTo(this->img);
            this->effect = true;
        }
        catch (...) {cout<<"~ APPLYING EFFECT FAILED\n";}
    }
}

void Effect::bwImg() {
    if(this->blackWhite == true)
    {
        try {
            cv::cvtColor(img,img,cv::COLOR_BGR2GRAY);
            this->effect = true;
        }
        catch (...) {cout<<"~ APPLYING EFFECT FAILED\n";}
    }
}

void Effect::cartoonImg() {
    if(this->cartoon == true)
    {
        try {
            Mat gray,tresh,edges;
            // to check if the image is already gray
            if(img.channels() != 1) cv::cvtColor(img,gray,cv::COLOR_BGR2GRAY);
            else img.copyTo(gray);

            // blur image to get a better mask for outlines
            cv::medianBlur(gray,gray,7);
            // create outline using a treshold
            cv::adaptiveThreshold(gray,tresh,255,cv::ADAPTIVE_THRESH_MEAN_C,cv::THRESH_BINARY,21,7);

            // blur initial image with a safer method
            cv::bilateralFilter(img,edges,21,250,250);

            // combine initial blurred image with the outlines
            cv::bitwise_and(edges,edges,img,tresh);
            this->effect = true;
    }
    catch (...) {cout<<"~ APPLYING EFFECT FAILED\n";}
    }
}

void Effect::applyAll() {
    this->blurImg();
    this->bwImg();
    this->cartoonImg();
}

class Adjustment:public virtual Image {
protected:
    double brightness, contrast;
    int hue;
    bool adjustment;
public:
    Adjustment(string name = "cat.png",string path = "../Images/",bool absolute = false, bool adjustment = false,
               double brightness = 0, double contrast = 1, int  hue = 0);
    Adjustment(const Adjustment& obj);
    Adjustment& operator=(const Adjustment& obj);
    // override specifier ensures that the function is virtual and is overriding a virtual function from a base class
    virtual ~Adjustment() override;

    friend istream& operator>>(istream& in, Adjustment& obj);
    friend ostream& operator<<(ostream& out, const Adjustment& obj);

    void brightnessImg();
    void contrastImg();
    void hueImg();
    void writeImg() const;
    void applyAll();
};

Adjustment::Adjustment(string name, string path,bool absolute, bool adjustment,
                       double brightness, double contrast, int hue):
        Image(name,path,absolute)
{
    this->adjustment = adjustment;
    this->brightness = brightness;
    this->contrast = contrast;
    this->hue = hue;
    this->readImg();
}

Adjustment::Adjustment(const Adjustment &obj): Image(obj) {
    this->adjustment = obj.adjustment;
    this->brightness = obj.brightness;
    this->contrast = obj.contrast;
    this->hue = obj.hue;
    this->readImg();
}

Adjustment& Adjustment::operator=(const Adjustment &obj) {
    if(this != &obj)
    {
        Image::operator=(obj);
        this->adjustment = obj.adjustment;
        this->brightness = obj.brightness;
        this->contrast = obj.contrast;
        this->hue = obj.hue;
        this->readImg();
    }
    return *this;
}

istream& operator>>(istream& in, Adjustment& obj) {
    in>>(Image&)obj;
    cout<<"Is the image adjusted? (yes:1 no:0)\n";
    in>>obj.adjustment;
    in.get();
    cout<<"Enter brightness [-100,100]: \n";
    in>>obj.brightness;
    in.get();
    cout<<"Enter contrast [0,10]: \n\t1 = nothing changes\n\t[0,1) = lower contrast\n\t(1,10] = higher contrast\n";
    in>>obj.contrast;
    in.get();
    cout<<"Enter hue [0,180]: \n";
    in>>obj.hue;
    in.get();
    obj.readImg();

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

Adjustment::~Adjustment() {
    this->contrast = 0;
    this->brightness = 0;
    this->hue = 0;
    this->adjustment = false;
}

void Adjustment::writeImg() const {
    try {
        string full_path = "../Images with Adjustments/" + this->withoutExtension(this->name) + "_withAdjustments" + this->extension(this->name);
        cv::imwrite(full_path,this->img);
    }
    catch (...) {cout<<"~ WRITING IMAGE FAILED\n";}
}

void Adjustment::brightnessImg() {
    if(this->brightness != 0 && this->brightness >= -100 && this->brightness <= 100)
    {
        try {
            // rtype == -1 means same type as source image
            // alpha = contrast, beta = brightness
            img.convertTo(img,-1,1,this->brightness);
            this->adjustment = true;
        }
        catch (...) {cout<<"~ APPLYING ADJUSTMENT FAILED\n";}
    }
}

void Adjustment::contrastImg() {
    if(this->contrast >= 0 && this->contrast <= 10)
    {
        try {
            // rtype == -1 means same type as source image
            // alpha = contrast, beta = brightness
            img.convertTo(img,-1,this->contrast,0);
            this->adjustment = true;
        }
        catch (...) {cout<<"~ APPLYING ADJUSTMENT FAILED\n";}
    }
}

void Adjustment::hueImg() {
    if(this->hue != 0 && this->hue >= -100 && this->hue <= 100)
    {
        try {
            Mat hsv_img;
            // changing color space to HSV (HUE, SATURATION, VALUE)
            cv::cvtColor(img,hsv_img,cv::COLOR_BGR2HSV);

            for(int i=0;i<hsv_img.rows;i++)
                for(int j=0;j<hsv_img.cols;j++)
                {
                    // to extract hue of the current pixel
                    int h = hsv_img.at<cv::Vec3b>(i,j)[0];
                    // adding value of this->hue to h
                    h = (h + this->hue) % 180;
                    // changing pixel hue
                    hsv_img.at<cv::Vec3b>(i,j)[0] = h;
                }
            // converting back to original color space
            cv::cvtColor(hsv_img,img,cv::COLOR_HSV2BGR);
            this->adjustment = true;
        }
        catch (...) {cout<<"~ APPLYING ADJUSTMENT FAILED\n";}
    }
}

void Adjustment::applyAll() {
    this->brightnessImg();
    this->contrastImg();
    this->hueImg();
}

void initOpenCV() {
    // for stopping logging info in console
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);
    // for stopping warnings in console
    set_dummy_error_handler();
}

int main()
{
    initOpenCV();

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
    /*
    Effect e;
    cout<<e<<endl;
    cin>>e;
    cout<<e<<endl;

    Effect e;
    cin>>e;
    e.applyAll();
    e.saveShow();
    e.blurImg();
    e.bwImg();
     */

//    ADJUSTMENT TESTS
    /*Adjustment a;
    cout<<a<<endl;
    cin>>a;
    cout<<a<<endl;
    Adjustment a2;
    a2 = a;
    cout<<a2<<endl;

    Adjustment a;
    cin>>a;
    a.brightnessImg();
    a.showImg();
    a.readImg();

    a.contrastImg();
    a.showImg();
    a.readImg();

    a.hueImg();
    a.showImg();*/

    return 0;
}

/*
- virtual la toti destructorii
- la typeinfo si typeid nevoie de destructor virtual, ptc e nevoie de o metoda virtuala
- la ultima clasa din mostenirea din diamant daca nu trecem toti constructorii: Baza, Stanga, Dreapta, si nu trecem Baza atunci se cheama cel default si numele va avea valoarea din constructorul de la baza default.
- la downcasting, daca dynamic_cast intoarce NULL se poate apela o metoda care nu acceseaza atribute.

- ORDINE: static_cast, mostenire virtuala, dynamic_cast
 */

// TODO remember: readImg keeps effects stacked if you want to reset readImg again | add reset option
/* TODO questions:
    - what happens with static attributes when inherited
    - public virtual vs virtual public

 */