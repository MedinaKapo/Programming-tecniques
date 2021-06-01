/*
    TP 16/17 (Tutorijal 9, Zadatak 5)

	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include<stdexcept>
using namespace std;
class Sat
{
	int sekunde;
public:
	int DajSate()const;
	int DajMinute()const;
	int DajSekunde()const;
	static bool DaLiJeIspravno(int h,int m,int s);
	void Postavi(int h,int m,int s);
	void PostaviNormalizirano(int h,int m,int s);
	Sat Sljedeci();
	Sat Prethodni();
	Sat PomjeriZa(int broj);
	void Ispisi()const;
	friend int BrojSekundiIzmedju(const Sat &s1,const Sat &s2);
	static int Razmak(const Sat &s1,const Sat &s2);
};
int Sat::DajSate()const
{ 
	return sekunde/3600;
}
int Sat::DajMinute()const
{
	return (sekunde%3600)/60;
}
int Sat::DajSekunde()const
{
	return (sekunde-(sekunde/60)*60);
}
bool Sat::DaLiJeIspravno(int h,int m,int s)
{
	if(h<0 || h>=24 || m<0 || m>=60 || s<0 || s>=60)return false;
	return true;
}
void Sat::Postavi(int h,int m,int s)
{
	if(DaLiJeIspravno(h,m,s)==false)throw domain_error("Neispravno vrijeme!");
	sekunde=h*3600+m*60+s;
}
void Sat::PostaviNormalizirano(int h,int m,int s)
{
	if(s>=60) {
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
		while(s<0)s+=60;
		if(m==0) {
			m=59;
			if(h==0)h=23;
		} else m--;
	}
	if(m<0) {
		while(m<0)m+=60;
		if(h==0)h=23;
		else h--;
	}
	if(h<0) {
		while(h<0)h+=24;
	}
	sekunde=h*3600+m*60+s;
}
Sat Sat::Sljedeci()
{
	sekunde++;
	PostaviNormalizirano(DajSate(),DajMinute(),DajSekunde());
	return *this;
}
Sat Sat::Prethodni()
{
	sekunde--;
	PostaviNormalizirano(DajSate(),DajMinute(),DajSekunde());
	return *this;
}
Sat Sat::PomjeriZa(int broj)
{
	if(broj>0)
		for(int i=0; i<broj; i++)Sljedeci();
	else {
		broj*=-1;
		for(int i=0; i<broj; i++)Prethodni();

	}
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
int BrojSekundiIzmedju(const Sat &s1,const Sat &s2)
{
	int v1,v2;
	v1=s1.DajSate()*3600+s1.DajMinute()*60+s1.DajSekunde();
	v2=s2.DajSate()*3600+s2.DajMinute()*60+s2.DajSekunde();
	return v1-v2;
}
int Sat::Razmak(const Sat &s1,const Sat &s2)
{
	int v1,v2;
	v1=s1.DajSate()*3600+s1.DajMinute()*60+s1.DajSekunde();
	v2=s2.DajSate()*3600+s2.DajMinute()*60+s2.DajSekunde();
	return v1-v2;
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
