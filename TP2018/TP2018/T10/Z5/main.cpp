/*
    TP 16/17 (Tutorijal 10, Zadatak 5)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;
class Ugao
{
	int stepeni,minute,sekunde;
	public:
	double PretvoriURadijane(double x)const{return (x*4*atan(1))/180.;}
	double PretvoriUStepene(double x)const{return (x*180.)/(4*atan(1));}
	void Preljevanje(int &stepen,int &minuta,int &sekunda){
		if(stepen==360)stepen=0;
		if(sekunda==60){
			sekunda=0;minuta++;
		}
		if(minuta==60){
			minuta=0;stepen++;
		}
		if(sekunda>60){
			while(sekunda>60){sekunda-=60;++minuta;}
		}
		if(minuta>60){
			while(minuta>60){minuta-=60;++stepen;}
		}
		if(stepen>360){
			while(stepen>=360)stepen-=360;
		}
		if(sekunda<0){
			while(sekunda<0)sekunda+=60;
			--minuta;
		}
		if(minuta<0){
			while(minuta<0)minuta+=60;
			--stepen;
		}
		if(stepen<0){
			while(stepen<0)stepen+=360;
		}
	}
	Ugao(double radijani=0){
		double stepen=PretvoriUStepene(radijani);
		stepeni=(int)stepen;
		double minuta=(stepen*60.-(int)stepen*60.);
		minute=(int)minuta;
		double sekunda=(minuta*60.-(int)minuta*60.);
		sekunde=(int)sekunda;
	}
	Ugao(int stepen,int minuta,int sekunda){
		stepeni=stepen;minute=minuta;sekunde=sekunda;
		Preljevanje(stepeni,minute,sekunde);
	}
	void Postavi(double radijani){
		double stepen=PretvoriUStepene(radijani);
		stepeni=(int)stepen;
		double minuta=(stepen*60.-(int)stepen*60.);
		minute=(int)minuta;
		double sekunda=(minuta*60.-(int)minuta*60.);
		sekunde=(int)sekunda;
	}
	void Postavi(int stepen,int minuta,int sekunda){
		stepeni=stepen;
		minute=minuta;
		sekunde=sekunda;
		Preljevanje(stepeni,minute,sekunde);
	}
	double DajRadijane()const{
		double stepen=0,minuta=0,sekunda=0;
		double radijani=0;
		stepen=PretvoriURadijane(stepeni);
		radijani+=stepen;
		minuta=PretvoriURadijane(minute);
		radijani+=minuta/60.;
		sekunda=PretvoriURadijane(sekunde);
		radijani+=sekunda/3600.;
		return radijani;
	}
	void OcitajKlasicneJedinice(int &stepen,int &minuta,int &sekunda){
		stepen=stepeni;
		minuta=minute;
		sekunda=sekunde;
	}
	int DajStepene()const{return stepeni;}
	int DajMinute()const{return minute;}
	int DajSekunde()const{return sekunde;}
	void Ispisi()const{
		cout<<fixed<<setprecision(5)<<this->DajRadijane()<<endl;
	}
	void IspisiKlasicno()const{
		cout<<this->DajStepene()<<"deg "<<this->DajMinute()<<"min "<<this->DajSekunde()<<"sec"<<endl;
	}
	Ugao &SaberiSa(const Ugao &u){
		this->stepeni+=u.DajStepene();this->minute+=u.DajMinute();this->sekunde+=u.DajSekunde();
		Preljevanje(stepeni,minute,sekunde);return *this;
	}
	Ugao &PomnoziSa(double x){
		this->stepeni*=x;this->minute*=x;this->sekunde*=x;Preljevanje(stepeni,minute,sekunde);return *this;
	}
	friend Ugao ZbirUglova(const Ugao &u1,const Ugao &u2){
		
		Ugao u3=Ugao(u1.DajStepene()+u2.DajStepene(),u1.DajMinute()+u2.DajMinute(),u1.DajSekunde()+u2.DajSekunde());
		int stepen,minuta,sekunda;
		stepen=u3.DajStepene();minuta=u3.DajMinute();sekunda=u3.DajSekunde();u3.Preljevanje(stepen,minuta,sekunda);
		return u3;
	}
	friend Ugao ProduktUglaSaBrojem(const Ugao &u,double x){
		Ugao u1=(Ugao(u.DajStepene(),u.DajMinute(),u.DajSekunde()*x));
		int stepen,minuta,sekunda;
		stepen=u1.DajStepene();minuta=u1.DajMinute();sekunda=u1.DajSekunde();u1.Preljevanje(stepen,minuta,sekunda);
		return u1;
	}

	
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
