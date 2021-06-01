//TP 2016/2017: Tutorijal 1, Zadatak 3
#include <iostream>
#include <cmath>
#include<iomanip>
using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::setprecision; 
using std::left;  
using std::right;
using std::setfill;
using std::fixed;

int main ()
{
    int a,b; 
    cout<<"Unesite pocetnu i krajnju vrijednost: "<<endl;
    cin>>a>>b;
    if(a<b){
    cout<<"+"<<setw(10)<<setfill('-')<<"+"<<setw(11)<<setfill('-')<<"+"<<setw(11)<<setfill('-')<<"+"<<setw(12)<<setfill('-')<<"+"<<endl;
    cout<<setfill(' ');
    cout<<"|"<<setw(9)<<left<<" Brojevi"<<"|"<<setw(10)<<" Kvadrati"<<"|"<<setw(10)<<" Korijeni"<<"|"<<setw(11)<<" Logaritmi"<<"|"<<endl;
    cout<<right;
    cout<<"+"<<setw(10)<<setfill('-')<<"+"<<setw(11)<<setfill('-')<<"+"<<setw(11)<<setfill('-')<<"+"<<setw(12)<<setfill('-')<<"+"<<endl;
   cout<<setfill(' ');
   for(int i=a;i<=b;i++){
       cout<<"| "<<left<<setw(8)<<setfill(' ')<<i<<"| "<<right<<setw(8)<<i*i<<" | "<<setw(8)<<fixed<<setprecision(3)<<sqrt(i)<<" | ";
       cout<<setw(9)<<setprecision(5)<<log(i)<<" |"<<endl; 
   }
     cout<<"+"<<setw(10)<<setfill('-')<<"+"<<setw(11)<<setfill('-')<<"+"<<setw(11)<<setfill('-')<<"+"<<setw(12)<<setfill('-')<<"+"<<endl;
    }
    return 0;
}
