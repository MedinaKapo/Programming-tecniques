//TP 2017/2018: Tutorijal 2, Zadatak 4
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
    double re,im;
    complex<double>z,suma,impedansa;
    for(int i=0; i<n; i++) {
        cout<<"R"<<i+1<<" = "; 
        cin>>re;
        cout<<"X"<<i+1<<" = ";
        cin>>im;
        //z=complex<double>(re,im);
        z= {re,im};
        suma+=1./z;
        cout<<endl;
    }
    impedansa=1./suma;
    cout<<"Paralelna veza ovih elemenata ima R = "<<impedansa.real()<<" i X = "<<impedansa.imag()<<"."<<endl;
    return 0;
}
