/* 
    TP 16/17 (Tutorijal 10, Zadatak 4)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;
class Ugao{
	double rad;
	public:
	double PretvoriURadijane(double x)const{return x*4*atan(1)/180.;}
	double PretvoriUStepene(double x)const{return x*180./(4*atan(1));}
	double Preljevanje(double x){
		//ili ti ga 2PI(pozivanje na znanje iz trigonometrije i svodjenje na prvi kvadrant)
		double y=2*4*atan(1);
		while(x<0)x+=y;
		while(x>y)x-=y;
		return x;
		
	}
	void Konverzija3Parametra(int &stepeni,int &minute,int &sekunde)const{
		double stepen=PretvoriUStepene(rad);
		double minuta;
		stepeni=(int)stepen;
		minuta=(stepen-(int)stepen)*60.;
		minute=(int)minuta;
		sekunde=(minuta-(int)minuta)*60+0.0000001;
		if(stepeni==360)stepeni=0;
		if(sekunde==60){
			sekunde=0;
			minute++;
		};
		
	}
	Ugao(double radijani=0){rad=radijani;rad=Preljevanje(rad);}
	//Ugao(int stepeni,int minute,int sekunde){Postavi(stepeni,minute,sekunde);}
	Ugao(int stepeni,int minute,int sekunde){
		double stepen;
		stepen=stepeni+minute/60.+sekunde/3600.;
		rad=PretvoriURadijane(stepen);
		rad=Preljevanje(rad);
	}
	void Postavi(double radijani){rad=radijani;rad=Preljevanje(rad);}
	void Postavi(int stepeni,int minute,int sekunde){
		double stepen;stepen=stepeni+minute/60.+sekunde/3600.;
		rad=PretvoriURadijane(stepen);
		rad=Preljevanje(rad);
	}
	double DajRadijane()const{return rad;}
	void OcitajKlasicneJedinice(int &stepeni,int &minute,int &sekunde)const{Konverzija3Parametra(stepeni,minute,sekunde);}
	int DajStepene()const{int stepen,minuta,sekunda;Konverzija3Parametra(stepen,minuta,sekunda);return stepen;}
	int DajMinute()const{int stepen,minuta,sekunda;Konverzija3Parametra(stepen,minuta,sekunda);return minuta;}
	int DajSekunde()const{int stepen,minuta,sekunda;Konverzija3Parametra(stepen,minuta,sekunda);return sekunda;}
	void Ispisi()const{cout<<fixed<<setprecision(5)<<DajRadijane()<<endl;}
	void IspisiKlasicno()const{cout<<this->DajStepene()<<"deg "<<this->DajMinute()<<"min "<<this->DajSekunde()<<"sec"<<endl;}
	Ugao &SaberiSa(const Ugao &u){this->rad+=u.DajRadijane();rad=Preljevanje(rad);return *this;}
	Ugao &PomnoziSa(double x){Postavi(x*rad);rad=Preljevanje(rad);return *this;}
	friend Ugao ZbirUglova(const Ugao &u1,const Ugao &u2){Ugao u3;u3=Ugao(u1.DajRadijane()+u2.DajRadijane());return u3;}
	friend Ugao ProduktUglaSaBrojem(const Ugao &u,double x){Ugao u1;u1=Ugao(u.DajRadijane()*x);return u1;}
};
int main ()
{
	Ugao u(5);
	u.Postavi(2,3,4);
	u.Ispisi();
	cout<<endl;
	cout<<u.DajRadijane()<<" "<<u.DajStepene()<<" "<<u.DajMinute()<<" "<<u.DajSekunde()<<endl;
	u.IspisiKlasicno();
	Ugao v(5);
	u.SaberiSa(v);
	u.IspisiKlasicno();
	cout<<endl;
	u.PomnoziSa(5);
	u.IspisiKlasicno();
	u.SaberiSa(5);
	u.Ispisi();
	Ugao p=ProduktUglaSaBrojem(u,5);
	p.Ispisi();
	cout<<endl;
	Ugao z=ZbirUglova(u,p);
	z.Ispisi();
	int x,y,t;
	z.OcitajKlasicneJedinice(x,y,t);
	cout<<x<<" "<<y<<" "<<t<<endl;
	v.Postavi(10);
	v.Ispisi();
	cout<<endl;
	Ugao h(1,2,3);
	h.Ispisi();
	cout<<endl;
	return 0;
}