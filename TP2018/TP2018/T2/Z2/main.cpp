//TP 2017/2018: Tutorijal 2, Zadatak 2
#include<iostream>
#include<vector>
using namespace std;
/*using std::cin;
using std::cout;
using std::endl;
using std::vector;*/
bool TestPerioda(vector<double> v,int p)
{
    for(int i=0; i<v.size(); i++) { 
        if(p<1 || p>=v.size())return false;
        if(i+p>=v.size())break;
        if(v.at(i)!=v.at(i+p))return false;
    }
    return true;
}
int OdrediOsnovniPeriod(vector<double> v)
{
    vector<int>periodi;
    int osnovni;
    for(int i=1; i<=v.size(); i++) {
        if(TestPerioda(v,i)==true)periodi.push_back(i);
        /*if(TestPerioda(v,i)==true) {
        return i;
            osnovni=i;
            break;
        }*/

    }
    // verzija sa vektorom perioda
    if(periodi.size()==0)osnovni=0;
    else {
        osnovni=periodi.at(0);
        for(int i=0; i<periodi.size(); i++) {
            if(periodi.at(i)<osnovni)osnovni=periodi.at(i);
        }
    }
    return osnovni;
}
int main()
{
    cout<<"Unesite slijed brojeva (0 za kraj): ";
    double n;
    vector<double>v;
    do {
        cin>>n;
        if(n!=0)v.push_back(n);
        if(n==0)break;
    } while(n!=0);
    int period;
    period=OdrediOsnovniPeriod(v);
    if(period!=0) {
        cout<<"Slijed je periodican sa osnovnim periodom "<<period<<"."<<endl;
    } else cout<<"Slijed nije periodican!"<<endl;
    return 0;
}
