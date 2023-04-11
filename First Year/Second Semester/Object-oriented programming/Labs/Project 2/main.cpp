#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
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

class IOInterface {
public:
    virtual istream& read(istream&) = 0;
    virtual ostream* print(ostream&) = 0;
};

class Image {
protected:
    // boolean for image finding
    bool absolute;
    string name,path,extension;
public:
    Image(string name = "Unnamed",string extension = "png",string path = "Root", bool absolute = false);
    Image(const Image& obj);
    Image& operator=(const Image& obj);
    // virtual to call derivative destructors
    virtual ~Image();

    friend istream& operator>>(istream& in, Image& obj);
    friend ostream& operator<<(ostream& out, const Image& obj);

    virtual Mat readImg() const;
    virtual void showImg() const;
};

Image::Image(string name, string extension, string path, bool absolute) {
    this->name = name;
    this->extension = extension;
    this->path = path;
    this->absolute = absolute;
}

Image::Image(const Image &obj) {
    this->name = obj.name;
    this->extension = obj.extension;
    this->path = obj.path;
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

    return in;
}

ostream& operator<<(ostream& out, const Image& obj) {
    out<<"Name: "<<obj.name<<"."<<obj.extension<<endl;
    out<<"Path to image: "<<obj.path<<endl;

    return out;
}

Image::~Image() {
    if(!this->name.empty()) this->name.clear();
    if(!this->path.empty()) this->path.clear();
    if(!this->extension.empty()) this->extension.clear();
}

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

Mat Image::readImg() const {
    string image_path;
    ::set_dummy_error_handler();
    try {
        if(this->absolute == false)
        {
            string full_name = this->name + "." + this->extension;
            // silent mode true to suppress errors
            image_path = findFile(full_name,true,true);
        }
        else image_path = findFile(path,true,true);

        Mat img = imread(image_path, IMREAD_COLOR);
        return img;
    }
    catch(...) {return cv::Mat::zeros(540,540,CV_8UC3);}
    // CV_8UC3 = 8 bit unsigned integer with 3 channels (RGB)
}

void Image::showImg() const {
    try {
        Mat img = this->readImg();
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

class Effect:public virtual Image {
protected:
    int blurAmount;
    bool effect;
public:
    Effect(string name = "Unnamed",string extension = "png",string path = "Root",bool effect = 0, int blurAmount = 0);
    Effect(const Effect& obj);
    Effect& operator=(const Effect& obj);
    // override specifier ensures that the function is virtual and is overriding a virtual function from a base class
    ~Effect() override;

    friend istream& operator>>(istream& in, Effect& obj);
    friend ostream& operator<<(ostream& out, const Effect& obj);

    virtual void blurImg() const;
};

Effect::Effect(string name, string extension, string path, bool effect, int blurAmount):
    Image(name,extension,path)
{
    this->effect = effect;
    this->blurAmount = blurAmount;
}

Effect::Effect(const Effect &obj):Image(obj) {
    this->effect = obj.effect;
    this->blurAmount = obj.blurAmount;
}

Effect& Effect::operator=(const Effect &obj) {
    if(this != &obj)
    {
        Image::operator=(obj);
        this->effect = obj.effect;
        this->blurAmount = obj.blurAmount;
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

void Effect::blurImg() const {
    try {
        Mat img = this->readImg();
        Mat blurredImage;

        cv::GaussianBlur(img,blurredImage,cv::Size(this->blurAmount,this->blurAmount),0);
        cout<<"Show image on screen (yes:1 no:0)?\n";
        int temp;
        cin>>temp;
        cin.get();
        if(temp == 1)
        {
            try {
                cv::namedWindow("Image",cv::WINDOW_NORMAL);
//        using this function makes the window not have a title bar
//        cv::setWindowProperty("Image",cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
                double aspect_ratio = static_cast<double>(blurredImage.cols)/blurredImage.rows;
                cv::resizeWindow("Image",static_cast<int>(540*aspect_ratio),540);
                imshow("Image",blurredImage);

//        Wait for a keystroke in the window
                int k = waitKey(0);
//        27 is ascii code for esc and waitKey returns an int
                if(k == 27)
                    cv::destroyAllWindows();
            }
            catch (...) {cout<<"~ OUTPUT FAILED\n";}
        }
        cout<<"Save image (yes:1 no:0)?\n";
        cin>>temp;
        cin.get();
        if(temp == 1)
        {
            img = blurredImage.clone();
            string name;
            cout<<"Enter new name for image (with extension):\n";
            // TODO method to get full path to image
            getline(cin,name);
            cv::imwrite(name,img);
            this->showImg();
        }
    }
    catch (...) {cout<<"~ APPLYING EFFECT FAILED\n";}
}

class Adjustment:public virtual Image {
protected:
    double brightness, contrast, hue;
    bool adjustment;
public:
    Adjustment(string name = "Unnamed",string extension = "png",string path = "Root", bool adjustment = false,
               double brightness = 0, double contrast = 0, double  hue = 0);
    Adjustment(const Adjustment& obj);
    Adjustment& operator=(const Adjustment& obj);
    // override specifier ensures that the function is virtual and is overriding a virtual function from a base class
    ~Adjustment() override;

    friend istream& operator>>(istream& in, Adjustment& obj);
    friend ostream& operator<<(ostream& out, const Adjustment& obj);
};

Adjustment::Adjustment(string name, string extension, string path, bool adjustment,
                       double brightness, double contrast, double hue):
        Image(name,extension,path)
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

Adjustment::~Adjustment() {
    this->contrast = 0;
    this->brightness = 0;
    this->hue = 0;
    this->adjustment = false;
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

    Effect e;
    cin>>e;
    e.blurImg();

//    TODO method to find aspect ratio
//    TODO entering wron image info then right doesnt work
//    TODO virtual destructor for base to avoid memory leaks
//    TODO rethink image reading and writing
    return 0;
}