//TP 2017/2018: Tutorijal 2, Zadatak 3
#include <iostream>
#include<complex>
using namespace std;
/*using std::cin;
using std::cout;
using std::endl;
using std::complex;*/
int main ()
{
    int n;
    cout<<"Unesite broj elemenata: "<<endl;
    cin>>n;
    complex<double> suma,impedansa; 
    complex<double> z; 
    double re,im;
    //z=complex<double>(re,im);
    z={re,im};
    for(int i=0;i<n;i++){
        cout<<"Z_"<<i+1<<" = ";
        cin>>z;
        suma+=(1./z);
    }
    cout<<endl;
    impedansa=1./suma;
    cout<<"Paralelna veza ovih elemenata ima impedansu Z_ = "<<impedansa<<"."<<endl;
	return 0;
}
