//TP 2018/2019: Tutorijal 4, Zadatak 1
#include <iostream>
#include<cmath>
using namespace std;
long long int Cifre(long long int n,int &c_min,int &c_max)
{
    int vracam=0;
    long long int min=9,max=0;
    if(n==0) {
        c_max=0;
        c_min=0;
        vracam=1;  
    } 
    long long int d;
    while(n!=0) {
        d=abs(n%10);
        if(d>max) {
            c_max=d;
            max=d;
        }
        if(d<min) {
            c_min=d;
            min=d;
        }
        n/=10;
        vracam++;
    }
    return vracam;
}
int main ()
{
    long long int n;
    cout<<"Unesite broj: ";
    cin>>n;
    int c_min,c_max;
    long long int rjesenja=Cifre(n,c_min,c_max);
    cout<<"Broj "<<n<<" ima "<<rjesenja<<" cifara, najveca je "<<c_max<<" a najmanja "<<c_min<<".";
    return 0;
}
