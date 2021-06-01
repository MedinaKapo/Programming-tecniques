//TP 2018/2019: Zadaća 4, Zadatak 1
#include <iostream>
#include <utility>
#include<stdexcept>
#include<algorithm>
#include<cmath> 
#include<vector>  
#include<memory> 
using namespace std;  
typedef pair<double,double>Tacka;
class Trougao
{ 
    Tacka v1,v2,v3;
    static double Pomocna(const Tacka &v1,const Tacka &v2,const Tacka &v3)
    {
        return v1.first*(v2.second-v3.second)-v2.first*(v1.second-v3.second)+v3.first*(v1.second-v2.second);
        
    };
public:
    Trougao(const Tacka &t1,const Tacka &t2,const Tacka &t3):v1(t1),v2(t2),v3(t3) {}
    void Postavi(const Tacka &t1,const Tacka &t2,const Tacka &t3);
    void Postavi(int indeks,const Tacka &t);
    static int Orijentacija(const Tacka &t1,const Tacka &t2,const Tacka &t3);
    Tacka DajTjeme(int indeks)const
    {
        if(indeks==1)return v1;
        if(indeks==2)return v2;
        return v3;
    }
    double DajStranicu(int indeks)const;
    double DajUgao(int indeks)const;
    Tacka DajCentar()const;
    double DajObim()const;
    double DajPovrsinu()const;
    bool DaLiJePozitivnoOrijentiran()const;
    bool DaLiJeUnutra(const Tacka &t)const;
    void Ispisi()const;
    void Transliraj(double delta_x,double delta_y);
    void Centriraj(const Tacka &t);
    void Rotiraj(const Tacka &t,double ugao);
    void Skaliraj(const Tacka &t,double faktor);
    void Rotiraj(double ugao);
    void Skaliraj(double faktor);
    friend bool DaLiSuIdenticni(const Trougao &t1,const Trougao &t2);
    friend bool DaLiSuPodudarni(const Trougao &t1,const Trougao &t2);
    friend bool DaLiSuSlicni(const Trougao &t1,const Trougao &t2);

};
void Trougao::Postavi(const Tacka &t1,const Tacka &t2,const Tacka &t3)
{
    if(Orijentacija(t1,t2,t3)==0)throw domain_error("Nekorektne pozicije tjemena");
    v1=t1;
    v2=t2;
    v3=t3;
}
void Trougao::Postavi(int indeks,const Tacka &t)
{
    if(indeks!=1 && indeks!=2 && indeks!=3)throw range_error("Nekorektan indeks");
    if(indeks==1) {
        v1=t;
    }
    if(indeks==2) {
        v2=t;
    }
    if(indeks==3) {
        v3=t;
    }
}
int Trougao::Orijentacija(const Tacka &t1,const Tacka &t2,const Tacka &t3)
{
   /* double rezultat=t1.first*(t2.second-t3.second)-t2.first*(t1.second-t3.second)+t3.first*(t1.second-t2.second);
    static int vracam;
    if(rezultat>0)vracam=1;
    else if(rezultat<0)vracam=-1;
    else vracam=0;*/
    double rezultat=Pomocna(t1,t2,t3);
    static int vracam;
    if(rezultat<0)vracam=-1;
    if(rezultat>0)vracam=1;
    if(rezultat==0)vracam=0;
    return vracam;
}
double Trougao::DajStranicu(int indeks)const
{
    double vracam=0;
    if(indeks==1) {
        vracam=sqrt((v2.first-v3.first)*(v2.first-v3.first)+(v2.second-v3.second)*(v2.second-v3.second));
    } else if(indeks==2) {
        vracam=sqrt((v1.first-v3.first)*(v1.first-v3.first)+(v1.second-v3.second)*(v1.second-v3.second));
    } else
        vracam=sqrt((v1.first-v2.first)*(v1.first-v2.first)+(v1.second-v2.second)*(v1.second-v2.second));
    return vracam;
}
double Trougao::DajUgao(int indeks)const
{
    double vracam=0;
    double a,b,c;
    a=DajStranicu(1);
    b=DajStranicu(2);
    c=DajStranicu(3);
    if(indeks==1) {
        vracam=acos((b*b+c*c-a*a)/(2.*b*c));
    } else if(indeks==2) {
        vracam=acos((a*a+c*c-b*b)/(2.*a*c));
    } else vracam=acos((a*a+b*b-c*c)/(2.*a*b));
    return vracam;

}
Tacka Trougao::DajCentar()const
{
    Tacka vracam;
    vracam.first=(v1.first+v2.first+v3.first)/3;
    vracam.second=(v1.second+v2.second+v3.second)/3;
    return vracam;
}
double Trougao::DajObim()const
{
    double a,b,c;
    a=DajStranicu(1);
    b=DajStranicu(2);
    c=DajStranicu(3);
    double vracam;
    vracam=(a+b+c);
    return vracam;
}
double Trougao::DajPovrsinu()const
{
    //double rezultat=v1.first*(v2.second-v3.second)-v2.first*(v1.second-v3.second)+v3.first*(v1.second-v2.second);
    double rezultat=Pomocna(v1,v2,v3);
    double vracam=1/2.*fabs(rezultat);
    return vracam;
}
bool Trougao::DaLiJePozitivnoOrijentiran()const
{
    if(Orijentacija(v1,v2,v3)==1)return true;
    return false;
}
bool Trougao::DaLiJeUnutra(const Tacka &t)const
{

    const Tacka v11=v1,v12=v2,v13=v3;
    Trougao t1(v11,v12,v13);
    Trougao  t2(v11,v12,t);
    Trougao t3(v12,v13,t);
    Trougao t4(v13,v11,t);
    if(t1.DaLiJePozitivnoOrijentiran()==t2.DaLiJePozitivnoOrijentiran() && t1.DaLiJePozitivnoOrijentiran()==t3.DaLiJePozitivnoOrijentiran()
            && t1.DaLiJePozitivnoOrijentiran()==t4.DaLiJePozitivnoOrijentiran() && t2.DaLiJePozitivnoOrijentiran()==t3.DaLiJePozitivnoOrijentiran() &&
            t2.DaLiJePozitivnoOrijentiran()==t4.DaLiJePozitivnoOrijentiran() && t3.DaLiJePozitivnoOrijentiran()==t4.DaLiJePozitivnoOrijentiran())return true;
    /*double a1,a2,a3,a;
    a=t1.DajPovrsinu();
    a1=t2.DajPovrsinu();
    a2=t3.DajPovrsinu();
    a3=t4.DajPovrsinu();
    if(a==a2+a3+a1)return true;*/
    return false;
}
void Trougao::Ispisi()const
{
    cout<<"(("<<v1.first<<","<<v1.second<<"),("<<v2.first<<","<<v2.second<<"),("<<v3.first<<","<<v3.second<<"))";
}
void Trougao::Transliraj(double delta_x,double delta_y)
{
    Tacka t1,t2,t3;
    t1.first=v1.first+delta_x;
    t1.second=v1.second+delta_y;
    t2.first=v2.first+delta_x;
    t2.second=v2.second+delta_y;
    t3.first=v3.first+delta_x;
    t3.second=v3.second+delta_y;
    Postavi(t1,t2,t3);
}
void Trougao::Centriraj(const Tacka &t)
{
    Tacka centar1=DajCentar();
    Tacka &centar=centar1;
    /* v1.first-=(centar1.first-t.first);
     v1.second-=(centar1.second-t.second);
     v2.first-=(centar1.first-t.first);
     v2.second-=(centar1.second-t.second);
     v3.first-=(centar1.first-t.first);
     v3.second-=(centar1.second-t.second);*/
    Tacka t1,t2,t3;
    t1.first=v1.first-(centar1.first-t.first);
    t1.second=v1.second-(centar1.second-t.second);
    t2.first=v2.first-(centar1.first-t.first);
    t2.second=v2.second-(centar1.second-t.second);
    t3.first=v3.first-(centar1.first-t.first);
    t3.second=v3.second-(centar1.second-t.second);
    Postavi(t1,t2,t3);
}
void Trougao::Rotiraj(const Tacka &t,double ugao)
{
    Tacka t1,t2,t3;
    t1.first=(t.first+(v1.first-t.first)*cos(ugao)-(v1.second-t.second)*sin(ugao));
    t1.second=(t.second+(v1.first-t.first)*sin(ugao)+(v1.second-t.second)*cos(ugao));
    t2.first=(t.first+(v2.first-t.first)*cos(ugao)-(v2.second-t.second)*sin(ugao));
    t2.second=(t.second+(v2.first-t.first)*sin(ugao)+(v2.second-t.second)*cos(ugao));
    t3.first=(t.first+(v3.first-t.first)*cos(ugao)-(v3.second-t.second)*sin(ugao));
    t3.second=(t.second+(v3.first-t.first)*sin(ugao)+(v3.second-t.second)*cos(ugao));
    Postavi(t1,t2,t3);
}
void Trougao::Skaliraj(const Tacka &t,double faktor)
{
    if(faktor==0)throw domain_error("Nekorektan faktor skaliranja");
    Tacka t1,t2,t3;
    t1=DajTjeme(1);
    t2=DajTjeme(2);
    t3=DajTjeme(3);
    if(t1==t) {
        t2.first=(t.first+faktor*(v2.first-t.first));
        t2.second=(t.second+faktor*(v2.second-t.second));
        t3.first=(t.first+faktor*(v3.first-t.first));
        t3.second=(t.second+faktor*(v3.second-t.second));
        Postavi(t1,t2,t3);
    } else if(t2==t) {
        t1.first=(t.first+faktor*(v1.first-t.first));
        t1.second=(t.second+faktor*(v1.second-t.second));
        t3.first=(t.first+faktor*(v3.first-t.first));
        t3.second=(t.second+faktor*(v3.second-t.second));
        Postavi(t1,t2,t3);
    } else if(t3==t) {
        t1.first=(t.first+faktor*(v1.first-t.first));
        t1.second=(t.second+faktor*(v2.second-t.second));
        t2.first=(t.first+faktor*(v2.first-t.first));
        t2.second=(t.second+faktor*(v2.second-t.second));
        Postavi(t1,t2,t3);
    }

}
void Trougao::Rotiraj(double ugao)
{
    Tacka centar=DajCentar();
    Tacka t1,t2,t3;
    t1.first=(centar.first+(v1.first-centar.first)*cos(ugao)-(v1.second-centar.second)*sin(ugao));
    t1.second=(centar.second+(v1.first-centar.first)*sin(ugao)+(v1.second-centar.second)*cos(ugao));
    t2.first=(centar.first+(v2.first-centar.first)*cos(ugao)-(v2.second-centar.second)*sin(ugao));
    t2.second=(centar.second+(v2.first-centar.first)*sin(ugao)+(v2.second-centar.second)*cos(ugao));
    t3.first=(centar.first+(v3.first-centar.first)*cos(ugao)-(v3.second-centar.second)*sin(ugao));
    t3.second=(centar.second+(v3.first-centar.first)*sin(ugao)+(v3.second-centar.second)*cos(ugao));
    Postavi(t1,t2,t3);
}
void Trougao::Skaliraj(double faktor)
{
    if(faktor==0)throw domain_error("Nekorektan faktor skaliranja");
    Tacka centar=DajCentar();
    Tacka t1,t2,t3;
    t1.first=centar.first+faktor*(v1.first-centar.first);
    t1.second=centar.second+faktor*(v1.second-centar.second);
    t2.first=centar.first+faktor*(v2.first-centar.first);
    t2.second=centar.second+faktor*(v2.second-centar.second);
    t3.first=centar.first+faktor*(v3.first-centar.first);
    t3.second=centar.second+faktor*(v3.second-centar.second);
    Postavi(t1,t2,t3);

}
bool DaLiSuIdenticni(const Trougao &t1,const Trougao &t2)
{
    if((t1.v1==t2.v1 || t1.v1==t2.v2 || t1.v1==t2.v3) && (t1.v2==t2.v1 || t1.v2==t2.v2 || t1.v2==t2.v3) && (t1.v3==t2.v1 || t1.v3==t2.v2 || t1.v3==t2.v3))
        return true;
    return false;
}
bool DaLiSuSlicni(const Trougao &t1,const Trougao &t2)
{
    double ugao11,ugao21,ugao31,ugao12,ugao22,ugao23;
    ugao11=t1.DajUgao(1);
    ugao12=t2.DajUgao(1);
    ugao21=t1.DajUgao(2);
    ugao22=t2.DajUgao(2);
    ugao31=t1.DajUgao(3);
    ugao23=t2.DajUgao(3);
    double s11,s21,s31,s12,s22,s32;
    s11=t1.DajStranicu(1);
    s21=t1.DajStranicu(2);
    s31=t1.DajStranicu(3);
    s12=t2.DajStranicu(1);
    s22=t2.DajStranicu(2);
    s32=t2.DajStranicu(3);
    vector<double>stranice1{s11,s21,s31};
    vector<double>stranice2{s12,s22,s32};
    sort(stranice1.begin(),stranice1.end());
    sort(stranice2.begin(),stranice2.end());
    vector<double>uglovi1{ugao11,ugao21,ugao31};
    vector<double>uglovi2{ugao12,ugao22,ugao23};
    sort(uglovi1.begin(),uglovi1.end());
    sort(uglovi2.begin(),uglovi2.end());
    if(uglovi1.at(0)==uglovi2.at(0) && uglovi1.at(1)==uglovi2.at(1) && uglovi1.at(2)==uglovi2.at(2))return true;
    else return false;
    if(stranice1.at(0)/stranice2.at(0)==stranice1.at(1)/stranice2.at(1)) {
        if(uglovi1.at(2)==uglovi2.at(2))return true;
    } else if(stranice1.at(1)/stranice2.at(1)==stranice1.at(2)/stranice2.at(2)) {
        if(uglovi1.at(0)==uglovi2.at(0))return true;
    } else if(stranice1.at(2)/stranice2.at(2)==stranice1.at(0)/stranice2.at(0)) {
        if(uglovi1.at(1)==uglovi2.at(1))return true;
    } else return false;
    if(stranice1.at(0)/stranice2.at(0)==stranice1.at(1)/stranice2.at(1) && stranice1.at(1)/stranice2.at(1)==stranice1.at(2)/stranice2.at(2) &&
            stranice1.at(2)/stranice2.at(2)==stranice1.at(0)/stranice2.at(0))return true;
    return false;
}
bool DaLiSuPodudarni(const Trougao &t1,const Trougao &t2)
{
    double ugao11=t1.DajUgao(1),ugao12=t1.DajUgao(2),ugao13=t1.DajUgao(3);
    double ugao21=t2.DajUgao(1),ugao22=t2.DajUgao(2),ugao23=t2.DajUgao(3);
    double stranica11=t1.DajStranicu(1),stranica12=t1.DajStranicu(2),stranica13=t1.DajStranicu(3);
    double stranica21=t2.DajStranicu(1),stranica22=t2.DajStranicu(2),stranica23=t2.DajStranicu(3);
    vector<double>stranice1{stranica11,stranica12,stranica13};
    vector<double>stranice2{stranica21,stranica22,stranica23};
    vector<double>uglovi1{ugao11,ugao12,ugao13};
    vector<double>uglovi2{ugao21,ugao22,ugao23};
    sort(stranice1.begin(),stranice1.end());
    sort(stranice2.begin(),stranice2.end());
    sort(uglovi1.begin(),uglovi1.end());
    sort(uglovi2.begin(),uglovi2.end());

    if(stranice1.at(0)==stranice2.at(0) && stranice1.at(1)==stranice2.at(1)) {
        if(uglovi1.at(2)==uglovi2.at(2))return true;
    }
    if(stranice1.at(1)==stranice2.at(1) && stranice1.at(2)==stranice2.at(2)) {
        if(uglovi1.at(0)==uglovi2.at(0))return true;
    }
    if(stranice1.at(2)==stranice2.at(2) && stranice1.at(0)==stranice2.at(0)) {
        if(uglovi1.at(1)==uglovi2.at(1))return true;
    }
    //else return false;

    if(uglovi1.at(0)==uglovi2.at(0) && uglovi1.at(1)==uglovi2.at(1)) {
        if(stranice1.at(2)==stranice2.at(2))return true;
    }
    if(uglovi1.at(1)==uglovi2.at(1) && uglovi1.at(2)==uglovi2.at(2)) {
        if(stranice1.at(0)==stranice2.at(0))return true;
    }
    if(uglovi1.at(2)==uglovi2.at(2) && uglovi1.at(0)==uglovi2.at(0)) {
        if(stranice1.at(1)==stranice2.at(1))return true;
    }
    //else return false;

    if(uglovi1.at(0)==uglovi2.at(0) && uglovi1.at(1)==uglovi2.at(1)) {
        if(stranice1.at(0)==stranice2.at(0) || stranice1.at(1)==stranice2.at(1))return true;
    }
    if(uglovi1.at(1)==uglovi2.at(1) && uglovi1.at(2)==uglovi2.at(2)) {
        if(stranice1.at(1)==stranice2.at(1) || stranice1.at(2)==stranice2.at(2))
            return true;
    }
    if(uglovi1.at(0)==uglovi2.at(0) && uglovi1.at(2)==uglovi2.at(2)) {
        if(stranice1.at(0)==stranice2.at(0) || stranice1.at(2)==stranice2.at(2))return true;
    }
    //else return false;

    if(stranice1.at(2)==stranice2.at(2)) {
        if(stranice1.at(0)==stranice2.at(0) || stranice1.at(1)==stranice2.at(1))return true;
        else return false;
    }
    if(stranice1.at(0)==stranice2.at(0) && stranice1.at(1)==stranice2.at(1) && stranice2.at(2)==stranice1.at(2)) {
        return true;
    } else if(DaLiSuSlicni(t1,t2)==true)return true;
    return false;

}
int main ()
{
    /* try{
      int n;
      cout<<"Koliko zelite kreirati trouglova: ";
      cin>>n;
      vector<shared_ptr<Trougao>> vektor(n,nullptr);
      double x1,y1,x2,y2,x3,y3;
     for(int i=0;i<n;i++){
         cout<<"Unesite podatke za "<<i+1<<". trougao (x1 y1 x2 y2 x3 y3): ";
         cin>>x1>>y1>>x2>>y2>>x3>>y3;
         Tacka t1,t2,t3;
         t1=make_pair(x1,y1);
         t2=make_pair(x2,y2);
         t3=make_pair(x3,y3);
         if(Orijentacija(t1,t2,t3)==0){
             cout<<"Nekorektne pozicije tjemena, ponovite unos!"<<endl;
             i--;
         }
         Trougao ubacujem=new Trougao(t1,t2,t3);
         shared_ptr<Trougao>t=make_shared(ubacujem);
         vektor.push_back(make_shared(ubacujem));
     }
     cout<<"Unesite vektor translacije (dx dy): ";
     double dx,dy;
     cin>>dx>>dy;
     cout<<"Unesite ugao rotacije: ";
     double ugao;
     cin>>ugao;
     cout<<"Unesite faktor skaliranja: ";
     int faktor;
     cin>>faktor;
     cout<<"Trouglovi nakon obavljenih transformacija: "<<endl;
     vector<shared_ptr<Trougao>>novi(n);
     transform(vektor.begin(),vektor.end(),novi,[dx,dy,ugao,faktor](shared_ptr<Trougao> &t1){
         Tacka centar=t1->DajCentar();
         Tacka prva=t1->DajTjeme(1);
         t1->Transliraj(dx,dy);
         t1->Rotiraj(centar,ugao);
         t1->Skaliraj(prva,faktor);

     });
      sort(novi.begin(),novi.end(),[](shared_ptr<Trougao>const &t1,shared_ptr<Trougao>const  &t2){
          return (t1->DajPovrsinu()<t2->DajPovrsinu());
      });
      for_each(novi.begin(),novi.end(),[](shared_ptr<Trougao>const  &t1){
          t1->Ispisi();
          cout<<endl;
      });
      cout<<"Trougao sa najmanjim obimom: ";
      auto tmin=min_element(novi.begin(),novi.end(),[](shared_ptr<Trougao>const &t1,shared_ptr<Trougao>const &t2){
          return(t1->DajObim()<t2->DajObim());
      });

      cout<<endl;
      cout<<"Parovi identicnih trouglova: "<<endl;
      for_each(novi.begin(),novi.end(),[](shared_ptr<Trougao>const &t1,shared_ptr<Trougao>const &t2){
          if(DaLiSuIdenticni(t1,t2)==true){
                  t1->Ispisi();
                  cout<<" i ";
                  t2->Ispisi();
                  cout<<endl;}
              });
              cout<<"Parovi podudarnih trouglova: "<<endl;
              for_each(novi.begin(),novi.end(),[](shared_ptr<Trougao>const &t1,shared_ptr<Trougao>const &t2){
              if(DaLiSuPodudarni(t1,t2)==true){
                  t1->Ispisi();
                  cout<<" i ";
                  t2->Ispisi();
                  cout<<endl;
              }
          });
          cout<<"Parovi slicnih trouglova: "<<endl;
          for_each(novi.begin(),novi.end(),[](shared_ptr<Trougao>const &t1,shared_ptr<Trougao>const &t2){
              if(DaLiSuSlicni(t1,t2)==true){
                  t1->Ispisi();
                  cout<<" i ";
                  t2->Ispisi();
                  cout<<endl;
              }
          });

     }catch(domain_error izuzetak){
         cout<<izuzetak.what()<<endl;
     }
     catch(range_error izuzetak1){
         cout<<izuzetak1.what()<<endl;
     }*/





    return 0;
}
