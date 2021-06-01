/*
    TP 16/17 (Tutorijal 9, Zadatak 4)

	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include<stdexcept>
using namespace std;
class Sat
{
	int sati,minute,sekunde;
public:
	static bool DaLiJeIspravno(int sati,int minute,int sekunde);
	void Postavi(int sati,int minute,int sekunde);
	void PostaviNormalizirano(int sati,int minute,int sekunde);
	Sat Sljedeci();
	Sat Prethodni();
	Sat PomjeriZa(int broj);
	void Ispisi()const;
	int DajSate()const;
	int DajMinute()const;
	int DajSekunde()const;
	friend int BrojSekundiIzmedju(const Sat &s1,const Sat &s2);
	static int Razmak(const Sat &s1,const Sat &s2);

};
int Sat::DajSate()const
{
	return sati;
}
int BrojSekundiIzmedju(const Sat &s1,const Sat &s2)
{
	int sekunde1,sekunde2;
	sekunde1=s1.sekunde+s1.minute*60+s1.sati*3600;
	sekunde2=s2.sekunde+s2.minute*60+s2.sati*3600;
	int razlika=(sekunde1-sekunde2);
	return razlika;
}
bool Sat::DaLiJeIspravno(int h,int m,int s)
{
	if(h<0 || h>=24 || m<0 || m>=60 || s<0 || s>=60)return false;
	return true;
}
void Sat::Postavi(int h,int m,int s)
{
	if(DaLiJeIspravno(h,m,s)==false)throw domain_error("Neispravno vrijeme");
	Sat::sati=h;
	Sat::minute=m;
	Sat::sekunde=s;
}
Sat Sat::Sljedeci()
{
	sekunde++;
	if(sekunde==60) {
		sekunde=0;
		minute++;
	}
	if(minute==60) {
		minute=0;
		sati++;
	}
	if(sati==24)sati=0;
	return *this;
}
Sat Sat::Prethodni()
{
	sekunde--;
	if(sekunde<0) {
		sekunde=59;
		minute--;
	}
	if(minute<0) {
		minute=59;
		sati--;
	}
	if(sati<0)sati=23;
	return *this;
}
void Sat::Ispisi()const
{
	if(DajSate()<10)cout<<"0";
	cout<<DajSate()<<":";
	if(DajMinute()<10)cout<<"0";
	cout<<DajMinute()<<":";
	if(DajSekunde()<10)cout<<"0";
	cout<<DajSekunde()<<endl;
}
int Sat::Razmak(const Sat &s1,const Sat &s2)
{
	int sekunde1,sekunde2,razlika;
	sekunde1=s1.sekunde+s1.minute*60+s1.sati*3600;
	sekunde2=s2.sekunde+s2.minute*60+s2.sati*3600;
	razlika=(sekunde1-sekunde2);
	return razlika;
}
void Sat::PostaviNormalizirano(int h,int m,int s)
{
	if(s>60) {
		int preljev;
		preljev=s/60;
		s-=preljev*60;
		m+=preljev;
	}
	if(m>=60) {
		int preljev;
		preljev=m/60;
		m-=preljev*60;
		h+=preljev;
	}
	if(h>=24) {
		int preljev;
		preljev=h/24;
		h-=preljev*24;
	}
	if(s<0) {
		while(s<0) {
			s+=60;
			if(m==0) {
				m=59;
				if(h==0)h=23;
			} else m--;
		}
	}
	if(m<0) {
		while(m<0) {
			m+=60;
			if(h==0)h=23;
			else h--;
		}
	}
	if(h<0) {
		while(h<0)h+=24;
	}
	sati=h;
	minute=m;
	sekunde=s;

}  
Sat Sat::PomjeriZa(int broj)
{
	if(broj>0) {
		for(int i=0; i<broj; i++)Sljedeci();
	} else {
		broj*=-1;
		for(int i=0; i<broj; i++)Prethodni();
	}
	return *this;
}
int Sat::DajMinute()const
{
	return minute;
}
int Sat::DajSekunde()const
{
	return sekunde;
}
int main ()
{
	Sat s1,s2,s3;
	s1.Postavi(23,59,59);
	s1.Prethodni().Ispisi();
	cout<<endl;
	s1.Sljedeci().Ispisi();
	cout<<endl;
	s1.PomjeriZa(5).Ispisi();
	cout<<endl;
	cout<<s1.DajSate()<<" "<<s1.DajMinute()<<" "<<s1.DajSekunde()<<endl;
	s2.Postavi(4,5,6);
	int broj=BrojSekundiIzmedju(s1,s2);
	cout<<broj<<endl;
	broj=Sat::Razmak(s1,s2);
	cout<<broj<<endl;
	s3.PostaviNormalizirano(15,-30,45);
	s3.Ispisi();
	bool ispravnost=Sat::DaLiJeIspravno(4,5,45);
	cout<<ispravnost<<" ";
	ispravnost=Sat::DaLiJeIspravno(15,-30,67);
	cout<<ispravnost;


	return 0;
}
