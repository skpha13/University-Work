#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int x,y,ax,ay,bx,by,ok,i,j,nr,k,l,verif;
float dist1,dist2,res;

float distance(int x,int y,int x1,int y1)
{
    return sqrt(pow(x-x1,2)+pow(y-y1,2)*1.0);
}

int main()
{
    std::cout<<std::fixed;
    std::cout<<std::setprecision(3);
    cin>>x>>y>>ax>>ay>>bx>>by;
    dist1 = distance(x,y,ax,ay);
    dist2 = distance(x,y,bx,by);
    if(dist1==(int)dist1) cout<<dist1,ok=1;
    if(dist2==(int)dist2) cout<<dist2,ok=1;

    if(ok==0)
    {
        if((x>=ax && x<=bx) || (x<=ax && x>=bx))
        {
            for(k=y;k<=1000;k++)
                if(k==ay)
                    break;
            for(l=y;l<=1000;l++)
                if(l==ay)
                    break;
            verif = 2;
        }
        if((y>=ay && y<=by) || (y<=ay && y>=by))
        {
            for(i=x;i<=1000;i++)
                if(i==ax)
                    break;
            for(j=x;j>=-1000;j--)
                if(j==ax)
                    break;
            verif = 1;
            
        }
    }
    if(verif==2)
    {
        res=abs(ay-y);
    }
    else if(verif==1)
    {
        res=abs(ax-x);
    }
    else if(ok==0) res=min(dist1,dist2);
    cout<<res;
    return 0;
}
