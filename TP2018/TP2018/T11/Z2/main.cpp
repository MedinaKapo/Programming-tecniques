/* 
    TP 16/17 (Tutorijal 11, Zadatak 2)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<stdexcept>
using namespace std;
class StedniRacun{
	double x;
	static int BrojAktivnih,BrojKreiranih;
	public:
	StedniRacun(double s=0){ 
		Postavi(s);
		BrojAktivnih++;
		BrojKreiranih++;
	}
	StedniRacun(const StedniRacun &s){
		if(s.x<0)throw logic_error("Nedozvoljeno pocetno stanje");
		x=s.x;
		BrojAktivnih++;
		BrojKreiranih++;
	}
	void Postavi(double s){if(s<0)throw logic_error("Nedozvoljeno pocetno stanje");else x=s;}
	double Ulozi(double iznos);
	double Podigni(double iznos);
	double DajStanje()const;
	double ObracunajKamatu(double iznos);
	static int DajBrojKreiranih(){return BrojKreiranih;}
	static int DajBrojAktivnih(){return BrojAktivnih;}
	~StedniRacun(){BrojAktivnih--;}
};
int StedniRacun::BrojAktivnih=0;
int StedniRacun::BrojKreiranih=0;
double StedniRacun::DajStanje()const{
	return x;
}
double StedniRacun::Ulozi(double iznos){
	x+=iznos;
	if(x<0){x-=iznos;throw logic_error("Transakcija odbijena");}
}
double StedniRacun::Podigni(double iznos){
	if(iznos>DajStanje())throw logic_error("Transakcija odbijena");
	x-=iznos;
}
double StedniRacun::ObracunajKamatu(double iznos){
	if(iznos<0)throw logic_error("Nedozvoljena kamatna stopa");
	iznos/=100;
	double stanje=DajStanje()*iznos;
	x+=stanje;
	return x;
} 
int main ()
{
	StedniRacun a(1000),b(5000);
	cout<<a.DajStanje()<<endl;
	cout<<b.DajStanje()<<endl;
	a.Ulozi(500);
	b.Podigni(1000);
	cout<<a.DajStanje()<<endl; 
	cout<<b.DajStanje()<<endl;
	a.ObracunajKamatu(5);
	b.ObracunajKamatu(10);
	cout<<a.DajStanje()<<endl;
	cout<<b.DajStanje()<<endl;
	a.Postavi(12500);
	cout<<a.DajStanje()<<endl;
	cout<<"Broj kreiranih "<<StedniRacun::DajBrojKreiranih()<<" a aktivnih "<<StedniRacun::DajBrojAktivnih()<<endl;
	
	
	return 0;
}