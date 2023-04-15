#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <iostream>
#include <vector>

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

void initOpenCV() {
    // for stopping logging info in console
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);
    // for stopping warnings in console
    set_dummy_error_handler();
}

class Interface {
public:
    virtual void applyAll() = 0;
    virtual void writeImg() const = 0;
    virtual istream& read(istream& in) = 0;
    virtual ostream& print(ostream& out) const = 0;
};

class Image: public Interface {
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

    istream& read(istream& in);
    ostream& print(ostream& out) const;

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

    string getName() const;
    string getPath() const;
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

istream& Image::read(istream &in) {
    if(!this->name.empty()) this->name.clear();
    if(!this->path.empty()) this->path.clear();
    cout<<"Enter name: \n";
    in>>this->name;
    cout<<"Do you want to use relative path? (1:yes 0:no)?\n";
    int temp;
    cin>>temp;
    in.get();
    if(temp == 0)
    {
        this->absolute = true;
        cout<<"Enter path to image: \n";
        // to get \n from buffer

        getline(in,this->path);
        // deleting "" from path
        if(this->path[0] == '"') this->path.erase(0,1), this->path.pop_back();
    }
    else this->path = "../Images/";

    return in;
}

ostream& Image::print(ostream &out) const {
    out<<"Name: "<<this->name<<endl;
    if(this->absolute == false) out<<"Path to image: "<<this->path + this->name<<endl;
    else out<<"Path to image: "<<this->path<<endl;

    return out;
}

istream& operator>>(istream& in, Image& obj) {
    return obj.read(in);
}

ostream& operator<<(ostream& out, const Image& obj) {
    return obj.print(out);
}

Image::~Image() {
    if(!this->name.empty()) this->name.clear();
    if(!this->path.empty()) this->path.clear();
    this->absolute = false;
}

string Image::extension(string word) const {
    return word.substr(word.find('.'),word.length());
}

string Image::withoutExtension(string word) const {
    return word.substr(0,word.find('.'));
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
    try {
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
    }
    catch (...) {cout<<"~ OUTPUT FAILED\n";}
}

void Image::showImg(const Mat& image) const {
    try {
        cv::namedWindow("Image",cv::WINDOW_NORMAL);
//        using this function makes the window not have a title bar
//        cv::setWindowProperty("Image",cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
        double aspect_ratio = static_cast<double>(image.cols)/image.rows;
        cv::resizeWindow("Image",static_cast<int>(540*aspect_ratio),540);
        imshow("Image",image);

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

string Image::getName() const {
    return name;
}

string Image::getPath() const {
    return path;
}

class Effect: virtual public Image {
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

    istream& read(istream& in);
    ostream& print(ostream& out) const;

    void blurImg();
    void bwImg();
    void cartoonImg();
    void writeImg() const;
    void applyAll();

    void setBlurAmount(int blurAmount);
    void setBlackWhite(bool blackWhite);
    void setCartoon(bool cartoon);
};

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

istream& Effect::read(istream &in) {
    this->Image::read(in);
    cout<<"Are there effects applied on the image? (yes:1 no:0) \n";
    in>>this->effect;
    cout<<"Do you want to blur the image? (yes:1 no:0)?\n";
    int temp;
    in>>temp;
    in.get();
    if(temp == 1)
    {
        cout<<"Enter blur amount: \n";
        in>>this->blurAmount;
    }
    cout<<"Do you want to apply Black and White effect to the image? (yes:1 no:0)?\n";
    in>>this->blackWhite;
    cout<<"Do you want to apply Cartoon effect to the image? (yes:1 no:0)?\n";
    in>>this->cartoon;
    this->readImg();

    return in;
}

ostream& Effect::print(ostream &out) const {
    this->Image::print(out);
    if(this->effect == true) out<<"Has effects applied\n";
    else out<<"Doesn't have effects applied\n";
    out<<"Blur amount: "<<this->blurAmount<<endl;
    if(this->blackWhite == true) out<<"Has Black and White effect applied\n";
    else out<<"Doesn't have Black and White effect applied\n";
    if(this->cartoon) out<<"Has Cartoon effect applied\n";
    else out<<"Doesn't have Cartoon effect applied\n";

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

void Effect::setBlurAmount(int blurAmount) {
    this->blurAmount = blurAmount;
}

void Effect::setBlackWhite(bool blackWhite) {
    this->blackWhite = blackWhite;
}

void Effect::setCartoon(bool cartoon) {
    this->cartoon = cartoon;
}

class Adjustment: virtual public Image {
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

    istream& read(istream& in);
    ostream& print(ostream& out) const;

    void brightnessImg();
    void contrastImg();
    void hueImg();
    void writeImg() const;
    void applyAll();

    void setBrightness(double brightness);
    void setContrast(double contrast);
    void setHue(int hue);
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

istream& Adjustment::read(istream &in) {
    this->Image::read(in);
    cout<<"Is the image adjusted? (yes:1 no:0)\n";
    in>>this->adjustment;
    in.get();
    cout<<"Enter brightness [-100,100]: \n";
    in>>this->brightness;
    in.get();
    cout<<"Enter contrast [0,10]: \n\t1 = nothing changes\n\t[0,1) = lower contrast\n\t(1,10] = higher contrast\n";
    in>>this->contrast;
    in.get();
    cout<<"Enter hue [0,180]: \n";
    in>>this->hue;
    in.get();
    this->readImg();

    return in;
}

ostream& Adjustment::print(ostream &out) const {
    this->Image::print(out);
    if(this->adjustment == true) out<<"Has adjustments applied\n";
    else out<<"Doesn't have adjustments applied\n";
    out<<"Brightness value: "<<this->brightness<<endl;
    out<<"Contrast value: "<<this->contrast<<endl;
    out<<"Hue value: "<<this->hue<<endl;

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

void Adjustment::setBrightness(double brightness) {
    this->brightness = brightness;
}

void Adjustment::setContrast(double contrast) {
    this->contrast = contrast;
}

void Adjustment::setHue(int hue) {
    this->hue = hue;
}
// TODO set bool effect and adjustment when changing one of them

class Edited: public Effect, public Adjustment {
private:
    bool edited;
    string date;
public:
    Edited(string name = "cat.png", string path = "../Images/",bool absolute = false,bool effect = false, int blurAmount = 0, bool blackWhite = false, bool cartoon = false,
           bool adjustment = false,double brightness = 0, double contrast = 1, int hue = 0, bool edited = false, string date = "13/06/1826");

    Edited(const Edited& obj);
    Edited &operator=(const Edited& obj);
    ~Edited();

    istream& read(istream& in);
    ostream& print(ostream& out) const;

    void writeImg() const;
    void applyAll();
};

Edited::Edited(string name, string path, bool absolute, bool effect, int blurAmount, bool blackWhite, bool cartoon,
               bool adjustment, double brightness, double contrast, int hue, bool edited, string date): Image(name,path,absolute),
                                                                                                       Effect(name,path,absolute,effect,blurAmount,blackWhite,cartoon),
                                                                                                       Adjustment(name,path,absolute,adjustment,brightness,contrast,hue) {
    this->edited = edited;
    this->date = date;
    this->readImg();
}

Edited::Edited(const Edited &obj): Image(obj), Effect(obj), Adjustment(obj) {
    this->edited = obj.edited;
    this->date = obj.date;
    this->readImg();
}

Edited& Edited::operator=(const Edited &obj) {
    if(this != &obj)
    {
        Effect::operator=(obj);
        Adjustment::operator=(obj);
        this->edited = obj.edited;
        this->date = obj.date;
        this->readImg();
    }
    return *this;
}

Edited::~Edited() {
    this->edited = false;
    if(!this->date.empty()) this->date.clear();
}

istream& Edited::read(istream &in) {
    this->Effect::read(in);

    cout<<"Is the image adjusted? (yes:1 no:0)\n";
    in>>this->adjustment;
    in.get();
    cout<<"Enter brightness [-100,100]: \n";
    in>>this->brightness;
    in.get();
    cout<<"Enter contrast [0,10]: \n\t1 = nothing changes\n\t[0,1) = lower contrast\n\t(1,10] = higher contrast\n";
    in>>this->contrast;
    in.get();
    cout<<"Enter hue [0,180]: \n";
    in>>this->hue;
    in.get();

    cout<<"Is the image edited (yes:1 no:0)?\n";
    in>>this->edited;
    in.get();
    cout<<"Enter date of edited image: \n";
    std::getline(in,this->date);

    this->readImg();
    return in;
}

ostream& Edited::print(ostream &out) const {
    this->Effect::print(out);

    if(this->adjustment == true) out<<"Has adjustments applied\n";
    else out<<"Doesn't have adjustments applied\n";
    out<<"Brightness value: "<<this->brightness<<endl;
    out<<"Contrast value: "<<this->contrast<<endl;
    out<<"Hue value: "<<this->hue<<endl;

    if(this->edited == true) out<<"Is edited\n";
    else out<<"Is not edited\n";

    out<<"Date of completion: "<<this->date<<endl;

    return out;
}

void Edited::writeImg() const {
    try {
        string full_path = "../Edited Images/" + this->withoutExtension(this->name) + "_Edited" + this->extension(this->name);
        cv::imwrite(full_path,this->img);
    }
    catch (...) {cout<<"~ WRITING IMAGE FAILED\n";}
}

void Edited::applyAll() {
    this->brightnessImg();
    this->contrastImg();
    this->hueImg();

    this->blurImg();
    this->bwImg();
    this->cartoonImg();
}

class Software {
private:
    Image* image;
    bool favorite, goBack;

public:
    Image* getImage() {return this->image;}

    friend istream& operator>>(istream& in, Software& obj);
    friend ostream& operator<<(ostream& out, const Software& obj);

    bool isGoBack() const;
};

istream& operator>>(istream& in, Software& obj) {
    obj.goBack = false;

    for(int i=0;i<10;i++) cout<<"-";
    cout<<" CREATE ";
    for(int i=0;i<10;i++) cout<<"-";
    cout<<endl;

    cout<<"1. Effects\n";
    cout<<"2. Adjustments\n";
    cout<<"3. Editing\n";
    cout<<"0. Go back\n";

    int temp;
    cin>>temp;
    cin.get();

    switch (temp) {
        case 0:
        {
            obj.goBack = true;
            break;
        }
        case 1:
        {
            obj.image = new Effect();
            break;
        }
        case 2:
        {
            obj.image = new Adjustment();
            break;
        }
        case 3:
        {
            obj.image = new Edited();
            break;
        }
        default:
            cout<<"~ INVALID OPTION\n";
    }

    if(obj.goBack == false)
    {
        in>>*obj.image;
        cout<<"Is this a favorite image (yes:1 no:0)?\n";
        in>>obj.favorite;
    }

    return in;
}

ostream& operator<<(ostream& out, const Software& obj) {
    out<<*obj.image<<endl;

    if(obj.favorite == true) out<<"Is a favorite image\n";
    else out<<"Is not a favorite image\n";

    return out;
}

bool Software::isGoBack() const {
    return this->goBack;
}

class Menu {
private:
    std::vector<Software*> files;
public:
    Menu(){initOpenCV(); this->engine();}

    void showMenu() const;
    void showEffects() const;
    void showAdjustments() const;
    void engine();
    void effectEngine(int index);
    void adjustmentEngine(int index);
    bool verifyIndex(int index) const;
    void displayEngine(int index);
    void displayOptions();
    void displayEdit();
    void editEngine(int index);
};

bool Menu::verifyIndex(int index) const {
    if(index < 0 || index >= files.size())
        return false;
    return true;
}

void Menu::displayEdit() {
    for(int i=0;i<10;i++) cout<<"-";
    cout<<" CHOOSE OPTION ";
    for(int i=0;i<10;i++) cout<<"-";
    cout<<endl;

    cout<<"1. Effects\n";
    cout<<"2. Adjustments\n";
    cout<<"3. Apply all changes\n";
    cout<<"4. Reset image\n";
    cout<<"0. Go back\n";
}

void Menu::editEngine(int index) {
    system("CLS");
    this->displayEdit();

    while(true)
    {
        int option;
        cout<<"Enter option: \n";
        cin>>option;
        cin.get();
        switch (option) {
            case 1:
            {
                system("CLS");
                this->effectEngine(index);
                this->displayEdit();
                break;
            }
            case 2:
            {
                system("CLS");
                this->adjustmentEngine(index);
                this->displayEdit();
                break;
            }
            case 3:
            {
                system("CLS");
                this->files[index]->getImage()->applyAll();
                cout<<"~ CHANGES APPLIED SUCCESSFULLY\n";
                this->displayEdit();
                break;
            }
            case 4:
            {
                system("CLS");
                this->files[index]->getImage()->readImg();
                cout<<"~ IMAGE RESET SUCCESSFULLY\n";
                this->displayEdit();
                break;
            }
            case 0:
            {
                system("CLS");
                return;
            }
            default:
                cout<<"~ INVALID OPTION\n";
        }
    }
}

void Menu::showEffects() const {
    for(int i=0;i<10;i++) cout<<"-";
    cout<<" CHOOSE EFFECT ";
    for(int i=0;i<10;i++) cout<<"-";
    cout<<endl;

    cout<<"1. Blur\n";
    cout<<"2. Black and White\n";
    cout<<"3. Cartoon\n";
    cout<<"0. Go back\n";
}

void Menu::showAdjustments() const {
    for(int i=0;i<10;i++) cout<<"-";
    cout<<" CHOOSE ADJUSTMENT ";
    for(int i=0;i<10;i++) cout<<"-";
    cout<<endl;

    cout<<"1. Brightness\n";
    cout<<"2. Contrast\n";
    cout<<"3. Hue\n";
    cout<<"0. Go back\n";
}

void Menu::effectEngine(int index) {
    system("CLS");
    this->showEffects();

    while(true)
    {
        int option;
        cout<<"Enter option: \n";
        cin>>option;
        cin.get();
        switch (option) {
            case 1:
            {
                system("CLS");
                int temp;
                cout<<"Enter blur amount: \n";
                cin>>temp;
                cin.get();
                if(dynamic_cast<Effect*>(files[index]->getImage()) != NULL)
                {
                    dynamic_cast<Effect*>(files[index]->getImage())->setBlurAmount(temp);
                    cout<<"~ EFFECT WAS APPLIED SUCCESSFULLY\n";
                }
                else cout<<"~ OBJECT IS NOT OF TYPE EFFECT OR EDITING\n";
                this->showEffects();
                break;
            }
            case 2:
            {
                system("CLS");
                bool temp;
                cout<<"Do you want to apply Black and White effect to the image (yes:1 no:0)?\n";
                cin>>temp;
                cin.get();
                if(dynamic_cast<Effect*>(files[index]->getImage()) != NULL)
                {
                    dynamic_cast<Effect*>(files[index]->getImage())->setBlackWhite(temp);
                    cout<<"~ EFFECT WAS APPLIED SUCCESSFULLY\n";
                }
                else cout<<"~ OBJECT IS NOT OF TYPE EFFECT OR EDITING\n";
                this->showEffects();
                break;
            }
            case 3:
            {
                system("CLS");
                bool temp;
                cout<<"Do you want to apply Cartoon effect to the image (yes:1 no:0)?\n";
                cin>>temp;
                cin.get();
                if(dynamic_cast<Effect*>(files[index]->getImage()) != NULL)
                {
                    dynamic_cast<Effect*>(files[index]->getImage())->setBlackWhite(temp);
                    cout<<"~ EFFECT WAS APPLIED SUCCESSFULLY\n";
                }
                else cout<<"~ OBJECT IS NOT OF TYPE EFFECT OR EDITING\n";
                this->showEffects();
                break;
            }
            case 0:
            {
                system("CLS");
                return;
            }
            default:
                cout<<"~ INVALID OPTION\n";
        }
    }
}

void Menu::adjustmentEngine(int index) {
    system("CLS");
    this->showAdjustments();

    while(true)
    {
        int option;
        cout<<"Enter option: \n";
        cin>>option;
        cin.get();
        switch (option) {
            case 1:
            {
                system("CLS");
                double temp;
                cout<<"Enter Brightness [-100,100]: \n";
                cin>>temp;
                cin.get();
                if(dynamic_cast<Adjustment*>(files[index]->getImage()) != NULL)
                {
                    dynamic_cast<Adjustment*>(files[index]->getImage())->setBrightness(temp);
                    cout<<"~ ADJUSTMENT WAS APPLIED SUCCESSFULLY\n";
                }
                else cout<<"~ OBJECT IS NOT OF TYPE EFFECT OR EDITING\n";
                this->showAdjustments();
                break;
            }
            case 2:
            {
                system("CLS");
                double temp;
                cout<<"Enter contrast [0,10]: \n\t1 = nothing changes\n\t[0,1) = lower contrast\n\t(1,10] = higher contrast\n";
                cin>>temp;
                cin.get();
                if(dynamic_cast<Adjustment*>(files[index]->getImage()) != NULL)
                {
                    dynamic_cast<Adjustment*>(files[index]->getImage())->setContrast(temp);
                    cout<<"~ ADJUSTMENT WAS APPLIED SUCCESSFULLY\n";
                }
                else cout<<"~ OBJECT IS NOT OF TYPE ADJUSTMENT OR EDITING\n";
                this->showAdjustments();
                break;
            }
            case 3:
            {
                system("CLS");
                int temp;
                cout<<"Enter hue [0,180]: \n";
                cin>>temp;
                cin.get();
                if(dynamic_cast<Adjustment*>(files[index]->getImage()) != NULL)
                {
                    dynamic_cast<Adjustment*>(files[index]->getImage())->setHue(temp);
                    cout<<"~ ADJUSTMENT WAS APPLIED SUCCESSFULLY\n";
                }
                else cout<<"~ OBJECT IS NOT OF TYPE ADJUSTMENT OR EDITING\n";
                this->showAdjustments();
                break;
            }
            case 0:
            {
                return;
            }
            default:
                cout<<"~ INVALID OPTION\n";
        }
    }
}

void Menu::displayOptions() {
    for(int i=0;i<10;i++) cout<<"-";
    cout<<" CHOOSE OPTION ";
    for(int i=0;i<10;i++) cout<<"-";
    cout<<endl;

    cout<<"1. INFO\n";
    cout<<"2. SHOW\n";
    cout<<"3. SAVE\n";
    cout<<"0. Go back\n";
}

void Menu::displayEngine(int index) {
    system("CLS");
    this->displayOptions();

    while(true)
    {
        int option;
        cout<<"Enter option: \n";
        cin>>option;
        cin.get();
        switch (option) {
            case 1:
            {
                system("CLS");
                cout<<*this->files[index]->getImage()<<endl;
                this->displayOptions();
                break;
            }
            case 2:
            {
                system("CLS");
                this->files[index]->getImage()->showImg();
                this->displayOptions();
                break;
            }
            case 3:
            {
                system("CLS");
                this->files[index]->getImage()->writeImg();
                cout<<"~ IMAGE WAS SAVED SUCCESSFULLY\n";
                this->displayOptions();
                break;
            }
            case 0:
            {
                system("CLS");
                return;
            }
            default:
                cout<<"~ INVALID OPTION\n";
        }
    }
}

void Menu::showMenu() const {
    for(int i=0;i<10;i++) cout<<"-";
    cout<<" MENU ";
    for(int i=0;i<10;i++) cout<<"-";
    cout<<endl;

    cout<<"1. Create new image\n"; // create a new object with effects adjs or all
    cout<<"2. Edit image\n"; // Edit an effect/ Adjustment/ or all
    cout<<"3. Delete image\n";
    cout<<"4. Display image\n"; // Info/Image on screen/save to location
    cout<<"0. Exit\n";
}

void Menu::engine() {
    this->showMenu();

    while(true)
    {
//        system("CLS");
        int option;
        cout<<"Enter option: \n";
        cin>>option;
        cin.get();
        switch (option) {
            case 0:
            {
                return;
            }
            case 1:
            {
                system("CLS");
                Software* s = new Software();
                cin>>*s;
                if(s->isGoBack() == false) this->files.push_back(s);
                else delete s;
//                system("CLS");
                this->showMenu();
                break;
            }
            case 2:
            {
                system("CLS");
                int index;
                if(!files.empty())
                {
                    for(int i=0;i<files.size();i++)
                        cout<<"Image: "<<i<<"\n\tName: "<<files[i]->getImage()->getName()<<"\n\tPath: "<<files[i]->getImage()->getPath()<<endl;
                    cout<<"Give index: \n";
                    cin>>index;
                    cin.get();
                    if(this->verifyIndex(index))
                    {
                        this->editEngine(index);
                    }
                    else cout<<"~ INVALID INDEX\n";
                }
                else cout<<"~ NO IMAGES\n";
//                system("CLS");
                this->showMenu();
                break;
            }
            case 3:
            {
                system("CLS");
                int index;
                if(!files.empty())
                {
                    for(int i=0;i<files.size();i++)
                        cout<<"Image: "<<i<<"\n\tName: "<<files[i]->getImage()->getName()<<"\n\tPath: "<<files[i]->getImage()->getPath()<<endl;
                    cout<<"Give index: \n";
                    cin>>index;
                    cin.get();
                    if(this->verifyIndex(index))
                    {
                        this->files.erase(this->files.begin() + index);
                        cout<<"~ IMAGE DELETED SUCCESSFULLY\n";
                    }
                    else cout<<"~ INVALID INDEX\n";
                }
                else cout<<"~ NO IMAGES\n";
                this->showMenu();
                break;
            }
            case 4:
            {
                system("CLS");
                int index;
                if(!files.empty())
                {
                    for(int i=0;i<files.size();i++)
                        cout<<"Image: "<<i<<"\n\tName: "<<files[i]->getImage()->getName()<<"\n\tPath: "<<files[i]->getImage()->getPath()<<endl;
                    cout<<"Give index: \n";
                    cin>>index;
                    cin.get();
                    if(this->verifyIndex(index))
                    {
                        this->displayEngine(index);
                    }
                    else cout<<"~ INVALID INDEX\n";
                }
                else cout<<"~ NO IMAGES\n";
//                system("CLS");
                this->showMenu();
                break;
            }
            default:
            {
                cout<<"~ INVALID OPTION\n";
            }
        }
    }
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

    Menu m;

    return 0;
}

/*
- virtual la toti destructorii
- la typeinfo si typeid nevoie de destructor virtual, ptc e nevoie de o metoda virtuala
- la ultima clasa din mostenirea din diamant daca nu trecem toti constructorii: Baza, Stanga, Dreapta, si nu trecem Baza atunci se cheama cel default si numele va avea valoarea din constructorul de la baza default.
- la downcasting, daca dynamic_cast intoarce NULL se poate apela o metoda care nu acceseaza atribute.

- ORDINE: static_cast, mostenire virtuala, dynamic_cast
 */

// TODO see system("CLS") - how to improve, because it doesnt always clear screen when switching menus