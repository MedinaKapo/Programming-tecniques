//TP 2018/2019: Zadaća 3, Zadatak 1
#include <iostream>
#include<cmath>
#include<vector>
#include<functional>
#include<stdexcept>    
#include<string>  
using namespace std;
double Tezinski(int i,int n,const vector<pair<double,double>> &par,int d,double x)
{
    int k,j; 
    n=n-1;
    if((i-d)>=1)k=i-d; 
    else k=1; 
    if((n-d)<=i)j=n-d;
    else j=i;  
    double suma=0;    
    double proizvod=1;
    for(int z=k; z<=j; z++) { 
        proizvod=1;
        for(int p=z; p<=z+d; p++) {
            if(p!=i) {
                proizvod*=1/(x-par.at(p).first);
            }
        }
        if(z%2==0)proizvod*=-1;
        suma+=proizvod;
    } 

    return suma;
}
function<double(double)>BaricentricnaInterpolacija(const vector<pair<double,double>> &par,int d)
{
    if(d<0 || d>par.size())throw domain_error("Nedozvoljen red");
    for(int i=1; i<par.size(); i++) {
        for(int j=i+1; j<par.size(); j++) {
            if(par.at(i).first==par.at(j).first)throw domain_error("Neispravni cvorovi");
        }
    }
    vector<pair<double,double>>parovi;
    parovi.resize(par.size()+1);
    for(int i=0; i<par.size(); i++) {
        parovi.at(i+1)=par.at(i);
    }
    return[parovi,d](double x) {
        double rez1=0,rez2=0,u;
        for(int i=0; i<parovi.size(); i++) {
            if(x==parovi.at(i).first)return parovi.at(i).second;
            u=double(Tezinski(i,parovi.size(),parovi,d,parovi.at(i).first)/(x-parovi.at(i).first));
            rez1+=u*parovi.at(i).second;
            rez2+=u;
        }
        double kolicnik=rez1/rez2;
        return kolicnik;
    };
}
function<double(double)>BaricentricnaInterpolacija(double f(double),double x_min,double x_max,double delta,int d)
{
    if(x_min>x_max || delta<=0)throw domain_error("Nekorektni parametri");
    if(d<0)throw domain_error("Nedozvoljen red");
    vector<pair<double,double>>cvorovi;
    pair<double,double>parovi;
    double rezultat=0;
    int koeficijent=0;
    double broj=x_min;
    while(broj!=x_max) {
        if(koeficijent>0)
        //broj=x_min+koeficijent*delta;
        broj=broj+delta;
        rezultat=f(broj);
        if(broj>=x_max)break;
        parovi=make_pair(broj,rezultat);
        cvorovi.push_back(parovi);
        koeficijent++;
    }    
    return BaricentricnaInterpolacija(cvorovi,d);
      
      
}
int main()
{
    try {
        int opcija,broj_cvorova,red_interpolacije;
        //char unos[10000];
        double unos;
        vector<pair<double,double>> parovi;
        double x,y;
        cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
        cin>>opcija;
        if(opcija==1) {
            cout<<"Unesite broj cvorova: ";
            cin>>broj_cvorova;
            cout<<"Unesite cvorove kao parove x y: ";
            parovi.resize(broj_cvorova);
            for(int i=0; i<broj_cvorova; i++) {
                cin>>x>>y;
                pair<double,double> par;
                par=make_pair(x,y);
                //parovi.push_back(par);
                parovi.at(i)=par;
            }
            cout<<"Unesite red interpolacije: ";
            cin>>red_interpolacije;
            double argument=0;
            cin.ignore(10000,'\n');
            cin.clear();
            char apostrof='"';
            for(;;) {
                cout<<"Unesite argument (ili "<<apostrof<<"kraj"<<apostrof<<" za kraj): ";
                cin>>unos;
                if(!cin)break;
                else {
                    argument=unos;
                    cout<<"f("<<argument<<") = ";
                    auto f(BaricentricnaInterpolacija(parovi,red_interpolacije));
                    cout<<f(argument)<<endl;
                }

            }
        }
        if(opcija==2) {
            cout<<"Unesite krajeve intervala i korak: ";
            double x_min,x_max,delta;
            cin>>x_min>>x_max>>delta;
            cout<<"Unesite red interpolacije: ";
            cin>>red_interpolacije;
            char apostrof='"';
            cin.ignore(10000,'\n');
            cin.clear();
            for(;;) {
                cout<<"Unesite argument (ili "<<apostrof<<"kraj"<<apostrof<<" za kraj): ";
                cin>>unos;
                if(!cin)break;
                else {
                    double argument;
                    argument=unos;
                    cout<<"f("<<argument<<") = ";
                    auto f(BaricentricnaInterpolacija([](double x) {
                        return x*x+sin(x);
                    },x_min,x_max,delta,red_interpolacije));
                    double tacna=argument*argument+sin(argument);
                    cout<<tacna;
                    cout<<" fapprox("<<argument<<") = ";
                    cout<<f(argument)<<endl;
                }
            }
        }
    } catch(domain_error izuzetak) {
        cout<<izuzetak.what()<<endl;
    }

    return 0;
}
