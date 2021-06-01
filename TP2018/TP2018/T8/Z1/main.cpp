//TP 2018/2019: Tutorijal 8, Zadatak 1
#include <iostream>
#include<stdexcept>
using namespace std;
struct Vrijeme {
    int sati;
    int minute;  
    int sekunde;
};
void TestirajVrijeme(const Vrijeme &v)
{
    if(v.sati<0 || v.sati>=24)throw domain_error("Neispravno vrijeme");
    else if(v.minute<0 || v.minute>=60)throw domain_error("Neispravno vrijeme");
    else if(v.sekunde<0 || v.sekunde>=60)throw domain_error("Neispravno vrijeme");
}
void IspisiVrijeme(const Vrijeme &v)
{
    try {
        TestirajVrijeme(v);
    } catch(domain_error) {
        throw;
    }
    if(v.sati<10)cout<<"0";
    cout<<v.sati<<":";
    if(v.minute<10)cout<<"0";
    cout<<v.minute<<":";
    if(v.sekunde<10)cout<<"0";
    cout<<v.sekunde;
}
struct Vrijeme SaberiVrijeme(struct Vrijeme v1,struct Vrijeme v2)
{
    try {
        TestirajVrijeme(v1);
    } catch(domain_error) {
        throw;
    }
    try {
        TestirajVrijeme(v2);
    }

    catch(domain_error) {
        throw;
    }

    Vrijeme v3;
    double suma=v1.sati*3600+v2.sati*3600+v1.minute*60+v2.minute*60+v1.sekunde+v2.sekunde;
    int sati=(int)suma/3600;
    int minute=(suma-sati*3600)/60;
    int sekunde=suma-(sati*3600+minute*60);
    if(sati>=24)sati-=24;
    if(minute>=60)minute-=60;
    if(sekunde>=60)sekunde-=60;
    v3.sati=sati;
    v3.minute=minute;
    v3.sekunde=sekunde;
    return {v3.sati,v3.minute,v3.sekunde};
}
int main ()
{
    struct Vrijeme v1,v2;
    try {
        cout<<"Unesite prvo vrijeme (h m s): ";
        cin>>v1.sati>>v1.minute>>v1.sekunde;
        try {
            TestirajVrijeme(v1);
        } catch(domain_error) {
            throw;
        }
        cout<<"Unesite drugo vrijeme (h m s): ";
        cin>>v2.sati>>v2.minute>>v2.sekunde;
        try {
            TestirajVrijeme(v2);
        } catch(domain_error) {
            throw;
        }
        cout<<"Prvo vrijeme: ";
        IspisiVrijeme(v1);
        cout<<endl;
        cout<<"Drugo vrijeme: ";
        IspisiVrijeme(v2);
        cout<<endl;
        cout<<"Zbir vremena: ";
        IspisiVrijeme(SaberiVrijeme(v1,v2));
    } catch(domain_error) {
        cout<<"Neispravno vrijeme"<<endl;
        return 0;
    }
    return 0;
}
