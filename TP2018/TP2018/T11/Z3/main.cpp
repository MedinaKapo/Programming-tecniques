/* 
    TP 16/17 (Tutorijal 11, Zadatak 3)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<stdexcept>
#include<cstring>
#include<iomanip>
using namespace std;
class Tim{
	char ime_tima[20];
	int broj_odigranih,broj_pobjeda,broj_nerijesenih,broj_poraza,broj_datih,broj_primljenih,broj_poena;
	int broj_utakmica;
	public:
	Tim(const char naziv[]){
		if(strlen(naziv)>20)throw range_error("Predugacko ime tima");
		else{
			strcpy(ime_tima,naziv);
			broj_datih=0;broj_odigranih=0;broj_pobjeda=0;broj_nerijesenih=0;broj_poraza=0;broj_primljenih=0;broj_poena=0;
		}
	}
	void ObradiUtakmicu(int Broj_datih,int Broj_primljenih); 
	const char *DajImeTima()const{return ime_tima;}
	int DajBrojPoena()const{return /*broj_pobjeda*3+broj_nerijesenih;*/broj_poena;}
	int DajGolRazliku()const{return broj_datih-broj_primljenih;}
	int DajBrojUtakmica()const{return /*broj_pobjeda+broj_poraza+broj_nerijesenih;*/broj_odigranih;}
	void IspisiPodatke()const;
};
void Tim::ObradiUtakmicu(int Broj_datih,int Broj_primljenih){
	if(Broj_datih<0 || Broj_primljenih<0)throw range_error("Neispravan broj golova");
	if(Broj_datih>Broj_primljenih)
		broj_pobjeda++;
	else if(Broj_datih==Broj_primljenih)broj_nerijesenih++;
	else broj_poraza++;
	broj_datih+=Broj_datih;
	broj_primljenih+=Broj_primljenih;
	broj_odigranih++;
	broj_poena=broj_pobjeda*3+broj_nerijesenih;
}
void Tim::IspisiPodatke()const{
	cout<<left<<setw(20)<<DajImeTima();
	cout<<right<<setw(4)<<DajBrojUtakmica();
	cout<<setw(4)<<broj_pobjeda;
	cout<<setw(4)<<broj_nerijesenih;
	cout<<setw(4)<<broj_poraza;
	cout<<setw(4)<<broj_datih;
	cout<<setw(4)<<broj_primljenih;
	cout<<setw(4)<<DajBrojPoena()<<endl;
}
int main ()
{ 
	
	try{
		Tim t1("Sarajevo");
		Tim t2("Velez");
		t1.ObradiUtakmicu(1,0);
		t2.ObradiUtakmicu(0,2);
		t1.IspisiPodatke();
		t2.IspisiPodatke();
		cout<<t1.DajBrojPoena()<<endl;
		cout<<t2.DajBrojPoena()<<endl;
		cout<<t1.DajBrojUtakmica()<<endl;
		cout<<t2.DajBrojUtakmica()<<endl;
		cout<<t1.DajGolRazliku()<<endl;
		cout<<t2.DajGolRazliku()<<endl;
		cout<<t1.DajImeTima()<<endl;
		cout<<t2.DajImeTima()<<endl;
		t1.ObradiUtakmicu(-5,12228);
	}
	catch(range_error izuzetak){
		cout<<izuzetak.what()<<endl;
	}
	return 0;
}