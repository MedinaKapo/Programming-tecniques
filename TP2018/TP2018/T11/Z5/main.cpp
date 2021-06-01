/* 
    TP 16/17 (Tutorijal 11, Zadatak 5)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<iterator>
#include<iomanip>
#include<stdexcept>
#include<cstring>
#include<algorithm>
#include<vector>
#include<memory>
#include<initializer_list>
#include<string>
#include<sstream>
using namespace std;
class Tim{
	char ime_tima[20];
	int broj_odigranih,broj_datih,broj_pobjeda,broj_nerijesenih,broj_poraza,broj_primljenih,broj_poena;
	int broj_utakmica;
	public:
	Tim(const char naziv[]){
		if(strlen(naziv)>20)throw range_error("Predugacko ime tima");
		else{
			strcpy(ime_tima,naziv);
			broj_datih=0;
			broj_nerijesenih=0;
			broj_odigranih=0;
			broj_pobjeda=0;
			broj_poena=0;
			broj_primljenih=0;
			broj_poraza=0;
		}
	}
	void ObradiUtakmicu(int Broj_datih,int Broj_primljenih);
	const char *DajImeTima()const{return ime_tima;}
	int DajBrojPoena()const{return broj_pobjeda*3+broj_nerijesenih;}
	int DajGolRazliku()const{return broj_datih-broj_primljenih;}
	int DajBrojUtakmica()const{return broj_utakmica;}
	void IspisiPodatke()const;
};
class Liga{
	vector<shared_ptr<Tim>>timovi;
	public:
	Liga()=default;
	Liga(initializer_list<Tim>lista_timova){
		timovi.resize(lista_timova.size());
		int i=0;
		for(Tim t:lista_timova){
			timovi.push_back(make_shared<Tim>(t));
			i++;
		}
	}
	Liga(const Liga &l);
	Liga &operator=(const Liga &l);
	Liga(Liga &&l);
	Liga &operator=(Liga &&l);
	void DodajNoviTim(const char ime_tima[]);
	void RegistrirajUtakmicu(const char tim1[],const char tim2[],int rezultat1,int rezultat2);
	void IspisiTabelu();
	
};
Liga::Liga(const Liga &l):timovi(l.timovi.size()){
	for(int i=0;i<l.timovi.size();i++)
	timovi[i]=make_shared<Tim>(*l.timovi[i]);
}
Liga &Liga::operator=(const Liga &l){
	if(&l!=this){
	timovi.resize(l.timovi.size());
	for(int i=0;i<l.timovi.size();i++)
	timovi.at(i)=make_shared<Tim>(*l.timovi.at(i));
	}
	return *this;
}
Liga::Liga(Liga &&l):timovi(move(l.timovi)){}
Liga &Liga::operator=(Liga &&l){
	if(&l!=this){
	timovi=move(l.timovi);
	}
	return *this;
}
void Liga::DodajNoviTim(const char ime_tima[]){
	timovi.push_back(make_shared<Tim>(Tim(ime_tima)));
}
bool Sortiraj(shared_ptr<Tim> t1,shared_ptr<Tim> t2)
{
	if((t1->DajBrojPoena())!=(t2->DajBrojPoena()))return (t1->DajBrojPoena())>(t2->DajBrojPoena());
		else if(t1->DajGolRazliku()!=t2->DajGolRazliku())return (t1->DajGolRazliku())>(t2->DajGolRazliku());
		string naziv1(t1->DajImeTima()),naziv2(t2->DajImeTima());
		return strcmp(t1->DajImeTima(),t2->DajImeTima())<0;
}
bool Jednakost(const char *tim1,const char *tim2){
	while(*tim1==*tim2){
		if(*tim1!=*tim2)return false;
		tim1++;
		tim2++;
	}
	return true;
}
void Liga::RegistrirajUtakmicu(const char tim1[],const char tim2[],int rezultat1,int rezultat2){
	bool kontrola=false;
	Tim *obradi1=nullptr,*obradi2=nullptr;
	for(int i=0;i!=timovi.size();i++){
		auto it=timovi[i];
		it.get()->DajImeTima();
		
		if(strcmp(tim1,(timovi[i]).get()->DajImeTima())){
		//if(Jednakost(tim1,timovi[i].get()->DajImeTima())==true){
			kontrola=true;
			obradi1=timovi.at(i).get();
		}
	}
	if(kontrola==false)throw logic_error("Tim nije nadjen");
	kontrola=false;
	for(int i=0;i!=timovi.size();i++){
		if(strcmp(tim2,timovi.at(i).get()->DajImeTima())==0){
		//if(Jednakost(tim2,timovi[i]->DajImeTima())==true){
			kontrola=true;
			obradi2=timovi.at(i).get();
		}
	}
	if(kontrola==false)throw logic_error("Tim nije nadjen");
	obradi1->ObradiUtakmicu(rezultat1,rezultat2);
	obradi2->ObradiUtakmicu(rezultat2,rezultat1);
	cout<<timovi.size();
} 

void Liga::IspisiTabelu(){
	sort(timovi.begin(),timovi.end(),Sortiraj);
	for(int i=0;i!=timovi.size();i++)timovi[i]->IspisiPodatke();
}
void Tim::ObradiUtakmicu(int Broj_datih,int Broj_primljenih){
	if(Broj_datih<0 || Broj_primljenih<0)throw range_error("Neispravan broj golova");
	if(Broj_datih>Broj_primljenih)broj_pobjeda++;
	else if(Broj_datih==Broj_primljenih)broj_nerijesenih++;
	else broj_poraza++;
	broj_datih+=Broj_datih;
	broj_primljenih+=Broj_primljenih;
	broj_odigranih++;
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
	Liga l1{"Velez","Celik"};
	l1.RegistrirajUtakmicu("Celik","Sarajevo",2,1);

	return 0;
}