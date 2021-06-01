/*
    TP 16/17 (Tutorijal 11, Zadatak 4)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<iomanip>
#include<stdexcept>
#include<cstring>
#include<initializer_list>
#include<algorithm>
using namespace std;
class Tim
{
	char ime_tima[20];
	int broj_odigranih,broj_pobjeda,broj_nerijesenih,broj_poraza,broj_datih,broj_primljenih,broj_poena;
	int broj_utakmica;
public:
	Tim(const char naziv[])
	{
		if(strlen(naziv)>20)throw range_error("Predugacko ime tima");
		else {
			strcpy(ime_tima,naziv);
			broj_datih=0;
			broj_odigranih=0;
			broj_pobjeda=0;
			broj_nerijesenih=0;
			broj_poraza=0;
			broj_primljenih=0;
			broj_poena=0;

		}
	}
	void ObradiUtakmicu(int Broj_datih,int Broj_primljenih);
	const char *DajImeTima()const
	{
		return ime_tima;
	}
	int DajBrojPoena()const
	{
		return broj_pobjeda*3+broj_nerijesenih;
	}
	int DajGolRazliku()const
	{
		return broj_datih-broj_primljenih;
	}
	int DajBrojUtakmica()const
	{
		return broj_odigranih;
	}
	void IspisiPodatke()const;
};
class Liga
{
	int broj_timova;
	const int max_br_timova;
	Tim **timovi;
	static bool Jednakost(const char *tim1,const char *tim2);
public:
	explicit Liga(int velicina_lige):max_br_timova(velicina_lige),broj_timova(0),timovi(new Tim*[velicina_lige] {}) {}
	explicit Liga(initializer_list<Tim> lista_timova):timovi(nullptr),broj_timova(lista_timova.size()),max_br_timova(broj_timova)
	{
		timovi=new Tim*[max_br_timova] {};
		int i=0;
		for(Tim t:lista_timova) {
			timovi[i]=new Tim(t);
			i++;
		}

	}
	~Liga();
	Liga(const Liga &l);
	Liga &operator=(const Liga &l);
	Liga(Liga &&l);
	Liga &operator=(Liga &&l);
	void DodajNoviTim(const char ime_tima[]);
	void RegistrirajUtakmicu(const char tim1[],const char tim2[],int rezultat_1,int rezultat_2);
	void IspisiTabelu()const;

};
Liga::~Liga()
{
	for(int i=0; i<broj_timova; i++)delete timovi[i];
	delete[]timovi;
}
Liga::Liga(const Liga &l):timovi(nullptr),max_br_timova(l.max_br_timova),broj_timova(l.broj_timova)
{
	try {
		timovi=new Tim*[l.max_br_timova] {};
		for(int i=0; i<l.broj_timova; i++)timovi[i]=new Tim(*l.timovi[i]);
	} catch(...) {
		for(int i=0; i<l.broj_timova; i++)delete timovi[i];
		delete[]timovi;
		throw;
	}
}
Liga &Liga::operator=(const Liga &l)
{
	if(&l!=this){
	if(max_br_timova!=l.max_br_timova)throw logic_error("Nesaglasni kapaciteti liga");
	if(l.broj_timova>broj_timova) {
		try {
			for(int i=broj_timova; i<l.broj_timova; i++)timovi[i]=new Tim(*l.timovi[i]);
		} catch(...) {
			for(int i=broj_timova; i<l.broj_timova; i++) {
				delete timovi[i];
				timovi[i]=nullptr;
			}
			throw;
		}
	} else {
		for(int i=l.broj_timova; i<broj_timova; i++) {
			delete timovi[i];
			timovi[i]=nullptr;
		}
	}
	broj_timova=l.broj_timova;
	for(int i=0; i<broj_timova; i++)*timovi[i]=*l.timovi[i];
	}
	return *this;
}
Liga::Liga(Liga &&l):timovi(nullptr),max_br_timova(l.max_br_timova),broj_timova(l.broj_timova)
{
	timovi=l.timovi;
	l.timovi=nullptr;
	l.broj_timova=0;
}
Liga &Liga::operator=(Liga &&l)
{
	if(&l!=this){
	if(l.max_br_timova!=max_br_timova)throw logic_error("Nesaglasni kapaciteti liga");
	broj_timova=l.broj_timova;
	timovi=l.timovi;
	l.timovi=nullptr;
	l.broj_timova=0;
	}
	return *this;
}
void Liga::DodajNoviTim(const char ime_tima[])
{
	if(broj_timova==max_br_timova)throw range_error("Liga popunjena");
	for(int i=0; i<broj_timova; i++) {
		if(strcmp(ime_tima,timovi[i]->DajImeTima())==0)throw logic_error("Tim vec postoji");
	}
	timovi[broj_timova++]=new Tim(ime_tima);
}
bool Liga::Jednakost(const char *tim1,const char *tim2){
	while(*tim1!='\0' && *tim2!='\0'){
		if(*tim1!=*tim2){
			return false;
		}
		tim1++;
		tim2++; 
	}
	return true;
}
void Liga::RegistrirajUtakmicu(const char tim1[],const char tim2[],int rezultat_1,int rezultat_2)
{
	bool kontrola=false;
	Tim *obradi1=nullptr,*obradi2=nullptr;
	for(int i=0; i<broj_timova; i++) {
		if(strcmp(tim1,timovi[i]->DajImeTima())==0) {
			kontrola=true;
			obradi1=timovi[i];

		}
	/*	if(Jednakost(tim1,timovi[i]->DajImeTima())==true){
			kontrola=true;
			obradi1=timovi[i];
			break;
		}*/

	}
	if(kontrola==false)throw logic_error("Tim nije nadjen");
	kontrola=false;
	for(int i=0; i<broj_timova; i++) {
		if(strcmp(tim2,timovi[i]->DajImeTima())==0) {

			kontrola=true;
			obradi2=timovi[i];

		}
	/*	if(Jednakost(tim1,timovi[i]->DajImeTima())==true){
			kontrola=true;
			obradi2=timovi[i];
			break;
		}*/


	}
	if(kontrola==false)throw logic_error("Tim nije nadjen"); 
	obradi1->ObradiUtakmicu(rezultat_1,rezultat_2);
	obradi2->ObradiUtakmicu(rezultat_2,rezultat_1);
}
void Liga::IspisiTabelu()const
{
	sort(timovi,timovi+broj_timova,[](Tim *t1,Tim *t2) {
		if(t1->DajBrojPoena()!=t2->DajBrojPoena())return t1->DajBrojPoena()>t2->DajBrojPoena();
		else if(t1->DajGolRazliku()!=t2->DajGolRazliku())return t1->DajGolRazliku()>t2->DajGolRazliku();
		string naziv1(t1->DajImeTima()),naziv2(t2->DajImeTima());
		return naziv1<naziv2;
	});
	for(int i=0; i<broj_timova; i++)timovi[i]->IspisiPodatke();
}
void Tim::ObradiUtakmicu(int Broj_datih,int Broj_primljenih)
{
	if(Broj_datih<0 || Broj_primljenih<0)throw range_error("Neispravan broj golova");
	if(Broj_datih>Broj_primljenih)broj_pobjeda++;
	else if(Broj_datih==Broj_primljenih)broj_nerijesenih++;
	else broj_poraza++;
	broj_datih+=Broj_datih;
	broj_primljenih+=Broj_primljenih; 
	broj_odigranih++;  
}
void Tim::IspisiPodatke()const
{
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
	Liga l1{"Sarajevo","Velez"};
	Liga l2{"Zeljeznicar","Celik"};
	Liga l3(l1);
	l3.IspisiTabelu();
	l2=l1;
	l2.IspisiTabelu();
	Liga l4(move(l1));
	l4.IspisiTabelu();
	l4=move(l2);
	l4.IspisiTabelu();
	l2=l1;
	l2.IspisiTabelu();
	l1.~Liga();l2.~Liga();l3.~Liga();l4.~Liga();
	Liga l{"Celik","Borac","Jedinstvo","Zeljeznicar","Zrinjski","Sarajevo"};
	while(1) {
		try {
			l.IspisiTabelu();
			cout<<"Unesite ime prvog tima (ENTER za kraj): "<<endl;
			string rijec;
			getline(cin,rijec);
			//cin>>rijec;
			if(rijec.size()==0)break;
			cout<<"Unesite ime drugog tima (ENTER za kraj): "<<endl;
			string rijec2;
			getline(cin,rijec2);
			//cin>>rijec2;
			if(rijec2.size()==0)break;
			cout<<"Unesite broj prostignutih golova oba tima: "<<endl;
			int gol1,gol2;
			cin>>gol1>>gol2;
			cin.ignore(10000,'\n');
			cin.clear();
			l.RegistrirajUtakmicu(rijec.c_str(),rijec2.c_str(),gol1,gol2);
		} catch(logic_error izuzetak) {
			cout<<izuzetak.what()<<endl;
		} catch(range_error izuzetak1) {
			cout<<izuzetak1.what()<<endl;
		}
	}
	return 0;
}
