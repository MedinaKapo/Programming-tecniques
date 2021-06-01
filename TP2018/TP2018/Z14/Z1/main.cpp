//TP 2018/2019: Tutorijal 14, Zadatak 1
#include <iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<iomanip>
#include<cstring>
using namespace std;
struct Mjerenja {
    int dan,mjesec,godina;
    char naziv[50];
    char iznosi[50];
};
double Prosjecna(char iznos[])
{
    double prosjek=0;
    int broj=0;
    int br=0;
    int znak=1;
    for(int i=0; i<strlen(iznos); i++) {
        if(iznos[i]!=',' && iznos[i]!='\0') {
            br=0;
            while(iznos[i]!=',' && iznos[i]!='\0') {
                if(iznos[i]=='-')znak=-1;
                else {
                    br*=10;
                    br+=int(iznos[i]-'0');
                }
                i++;
                if(iznos[i]=='\0')break;
            }
            br*=znak;
            znak=1;
            prosjek+=br;
            broj++;
        }
        if(iznos[i]=='\0')break;

    }

    return prosjek/broj;
}
bool kriterij(Mjerenja &m1,Mjerenja &m2)
{
    if(m1.dan<m2.dan && m1.mjesec<m2.mjesec)return true;
    else {
        double prosjek1=0,prosjek2=0;
        prosjek1=Prosjecna(m1.iznosi);
        prosjek2=Prosjecna(m2.iznosi);
        return prosjek1<prosjek2;
    }
}
int main ()
{
    Mjerenja ucitano[50];
    ifstream ucitavanje("TEMPERATURE.TXT",ios::in);
    int i=0;
    if(!ucitavanje) {
        ucitavanje.clear();
        cout<<"Datoteka TEMPERATURE.TXT ne postoji!"<<endl;
    } else {
        for(;;) {
            if(ucitavanje.eof()) {
                ucitavanje.clear();
                ucitavanje.close();
                break;
            }
            char naziv[50];
            int dan,mjesec,godina;
            char iznosi[50];
            double mjerenje;
            char znak;
                ucitavanje>>ucitano[i].dan;
            ucitavanje>>znak;
            ucitavanje>>ucitano[i].mjesec;
            ucitavanje>>znak;
            ucitavanje>>ucitano[i].godina;
            ucitavanje.ignore(1000,'\n');
            /*ucitavanje>>znak;
            cout<<znak;*/
            ucitavanje.getline(naziv,sizeof(naziv));
            strcpy(ucitano[i].naziv,naziv);
            int j=0;
            ucitavanje.getline(iznosi,sizeof(iznosi));
            strcpy(ucitano[i].iznosi,iznosi);
            j=0;
            //i++;
        
    
            if(ucitavanje.eof()) {
                ucitavanje.clear();
                ucitavanje.close();
                break;
            }
        
            else if(ucitavanje.bad()) {
                cout<<"Problemi pri citanju datoteke TEMPERATURE.TXT"<<endl;
                break;
            }
            i++;
        }
    }
    
    sort(ucitano,ucitano+i,kriterij);
    ofstream ispisivanje("IZVJESTAJ.TXT");
    //ispisivanje.open("IZVJESTAJ.TXT",ios::out);
    if(!ispisivanje) {
        cout<<"Kreiranje datoteke IZVJESTAJ.TXT nije uspjelo"<<endl;
    } else {
        
        for(int z=0; z<i; z++) {
            ispisivanje<<ucitano[z].naziv;
            ispisivanje<<"\n";
            ispisivanje<<setw(strlen(ucitano[z].naziv)+1)<<setfill('-');
            ispisivanje<<"\n";
            ispisivanje<<"Datum mjerenja: ";
            ispisivanje<<ucitano[z].dan<<"/"<<ucitano[z].mjesec<<"/"<<ucitano[z].godina<<"\n";

            int rezultati[50],kolicina=0;
            for(int i=0; i<strlen(ucitano[z].iznosi); i++) {
                if(ucitano[z].iznosi[i]!=',' && ucitano[z].iznosi[i]!='\0') {
                    int br=0,znak=1,broj=0;
                    while(ucitano[z].iznosi[i]!=',' && ucitano[z].iznosi[i]!='\0') {
                        if(ucitano[z].iznosi[i]=='-')znak=-1;
                        else {
                            br*=10;
                            br+=(int)(ucitano[z].iznosi[i]-'0');
                        }
                        i++;
                        if(ucitano[z].iznosi[i]=='\0')break;
                    }



                    broj=br*znak;
                    rezultati[kolicina++]=broj;
                }

                if(ucitano[z].iznosi[i]=='\0')break;
            }

            sort(rezultati,rezultati+kolicina);

            ispisivanje<<"Minimalna temperatura: "<</*ucitano[z].iznosi[0]<<"\n";*/rezultati[0]<<"\n";
            ispisivanje<<"Maksimalna temperatura: "<</*ucitano[z].iznosi[strlen(ucitano[z].iznosi)-1]<<"\n";*/
                       rezultati[kolicina-1]<<"\n";
            ispisivanje<<fixed<<setprecision(2);
            ispisivanje<<"Prosjecna temperatura: "<<Prosjecna(ucitano[z].iznosi);
            ispisivanje<<"\n";
            ispisivanje<<"\n";

        }
    }
    ispisivanje.close();

    return 0;
}
