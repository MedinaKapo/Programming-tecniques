//TP 2017/2018: Tutorijal 2, Zadatak 5
#include <iostream>
#include<complex>
#include<cmath>
using namespace std;

int main ()
{
    int n;
    cout<<"Unesi broj elemenata:"<<endl;
    cin>>n;
    double z,fi,im;
    complex<double>suma,impedansa,suma1;
    for(int i=0; i<n; i++) {
        cout<<"Z"<<i+1<<" = ";
        cin>>z;
        cout<<"fi"<<i+1<<" = ";
        cin>>fi; 
        im=(fi*4*atan(1))/180;
        //suma=polar(z,im);
        suma+=1./(polar(z,im));
        cout<<endl;
    }
    impedansa=1./suma;
    cout<<"Paralelna veza ovih elemenata ima Z = "<<abs(impedansa)<<" i fi = "<<(arg(impedansa)*180)/(4*atan(1))<<"."<<endl;
    return 0;
}
