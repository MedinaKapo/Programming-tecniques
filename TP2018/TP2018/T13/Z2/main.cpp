/*
    TP 16/17 (Tutorijal 13, Zadatak 2)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream> 
#include<string>
#include<stdexcept> 
using namespace std; 
class ApstraktniStudent
{
protected:
	string ime,prezime;
	int index,brojpolozenih;
	double prosjek;
public:
	ApstraktniStudent(string ime1,string prezime1,int index1):ime(ime1),prezime(prezime1),index(index1)
	{
		brojpolozenih=0;
		prosjek=5;
	}
	virtual ~ApstraktniStudent() {};
	string DajIme()const
	{
		return ime;
	}
	string DajPrezime()const
	{
		return prezime;
	}
	int DajBrojIndeksa()const
	{ 
		return index;
	}
	int DajBrojPolozenih()const
	{
		return brojpolozenih;
	}
	double DajProsjek()const 
	{
		return prosjek; 
	}
	void RegistrirajIspit(int ocjena)
	{
		if(ocjena<5 || ocjena>10)throw domain_error("Neispravna ocjena");
		else if(ocjena==5)return;
		else {
			double suma;
			suma=prosjek*brojpolozenih;
			brojpolozenih++;  
			suma+=ocjena;
			prosjek=suma/brojpolozenih;
		}
	}
	void PonistiOcjene()
	{
		brojpolozenih=0;
		prosjek=5;
	}
	virtual void IspisiPodatke()const=0;
	virtual ApstraktniStudent *DajKopiju()const=0;
};
class StudentBachelor:public ApstraktniStudent
{
public:
	StudentBachelor(string ime,string prezime,int index):ApstraktniStudent(ime,prezime,index) {}
	void IspisiPodatke()const override
	{
		cout<<"Student bachelor studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<","<<endl;
		cout<<"ima prosjek "<<DajProsjek()<<"."<<endl;
	}
	StudentBachelor *DajKopiju()const override
	{
		return new StudentBachelor(*this);
	}
};
class StudentMaster:public ApstraktniStudent
{
	int diploma;
	//int DajDiplomu()const{return diploma;}
public:
	StudentMaster(string ime,string prezime,int indeks,int diploma1):ApstraktniStudent(ime,prezime,indeks),diploma(diploma1){}
	void IspisiPodatke()const override
	{
		cout<<"Student master studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<","<<endl;
		cout<<"zavrsio bachelor studij godine "<<diploma<<",ima prosjek "<<DajProsjek()<<"."<<endl;
	}
	StudentMaster *DajKopiju()const override
	{
		return new StudentMaster(*this);
	}

};
int main ()
{
	StudentBachelor s1("winnie","pooh",1234);
	s1.RegistrirajIspit(8);
	s1.RegistrirajIspit(6);
	s1.RegistrirajIspit(5);
	cout<<s1.DajIme()<<" "<<s1.DajPrezime()<<" "<<s1.DajBrojIndeksa()<<" "<<s1.DajBrojPolozenih()<<" "<<s1.DajProsjek()<<endl;
	s1.IspisiPodatke();
	StudentMaster s2("johnny","bravo",4321,2010);
	s2.RegistrirajIspit(6); 
	s2.RegistrirajIspit(7); 
	s2.RegistrirajIspit(5);
	s2.RegistrirajIspit(7);
	cout<<s2.DajIme()<<" "<<s2.DajPrezime()<<" "<<s2.DajBrojIndeksa()<<" "<<s2.DajBrojPolozenih()<<" "<<s2.DajProsjek()<<endl;
	s2.IspisiPodatke();
	s1.PonistiOcjene();
	s1.IspisiPodatke();
	return 0;
}
