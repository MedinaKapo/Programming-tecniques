//TP 2016/2017: Tutorijal 1, Zadatak 1
#include <iostream>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;
int main ()
{ 
    int a,b,c,d;
    cout<<"Unesite duzinu, sirinu i dubinu bazena u metrima: ";
    cin>>a>>b>>c;
    cout<<"Unesite sirinu plocice u centimetrima: ";
    cin>>d;
    int povrsina1,povrsina2,povrsina3,povrsina4;
    povrsina1=a*b*100*100;
    povrsina2=a*c*100*100;  
    povrsina3=b*c*100*100;
    povrsina4=d*d;
    if(povrsina1%povrsina4==0 && povrsina2%povrsina4==0 && povrsina3%povrsina4==0) {
        //ako ovaj uslov jeste ispunjen,to opet nije dovoljno jer treba se provjeriti po duzini da li plocice mogu stati
        double duzina1,duzina2,duzina3;
        duzina1=a/(d/100.); 
        duzina2=b/(d/100.);
        duzina3=c/(d/100.);
        if(duzina1-(int)duzina1==0 && duzina2-(int)duzina2==0 && duzina3-(int)duzina3==0) {
            int broj=(povrsina1+2*povrsina2+2*povrsina3)/povrsina4;
            cout<<"\nZa poplocavanje bazena dimenzija "<<a<<"x"<<b<<"x"<<c<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm"<<endl;
            cout<<"potrebno je "<<broj<<" plocica.";
        } else {
            cout<<"\nPoplocavanje bazena dimenzija "<<a<<"x"<<b<<"x"<<c<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm"<<endl;
            cout<<"nije izvodljivo bez lomljenja plocica!";
        }
    } else {
        cout<<"\nPoplocavanje bazena dimenzija "<<a<<"x"<<b<<"x"<<c<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm"<<endl;
        cout<<"nije izvodljivo bez lomljenja plocica!";
    }
    return 0;
}
