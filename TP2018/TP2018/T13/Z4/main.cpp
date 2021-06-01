/*
    TP 16/17 (Tutorijal 13, Zadatak 4)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<vector>  
#include<stdexcept>
using namespace std;
class ApstraktniStudent
{
protected:
	string ime,prezime;
	int index,brojpolozenih;
	double prosjek;
public:
	ApstraktniStudent(string ime,string prezime,int index):ime(ime),prezime(prezime),index(index)
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
		if(ocjena<5 || ocjena>10)throw domain_error("Nesipravna ocjena");
		else if(ocjena==5)return;
		else {
			double suma;
			suma=brojpolozenih*prosjek;
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
public:
	StudentMaster(string ime,string prezime,int index,int diploma):ApstraktniStudent(ime,prezime,index),diploma(diploma) {}
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
class Student  
{ 
	ApstraktniStudent *p;
	void Test()const
	{
		if(!p)throw logic_error("Nespecificiran tip");
	}
public:
	Student():p(nullptr) {}
	~Student()
	{
		delete p;
	}
	Student(const ApstraktniStudent &s):p(s.DajKopiju()) {}
	Student(const Student  &s)
	{
		if(!s.p)p=nullptr;
		else p=s.p->DajKopiju();
	}
	Student(Student &&s)
	{
		p=s.p;
		s.p=nullptr;
	}
	Student &operator=(const Student &s)
	{
		ApstraktniStudent *novi(nullptr);
		if(s.p!=nullptr)novi=s.p->DajKopiju();
		delete p;
		p=novi;
		return *this;
	}
	Student &operator=(Student &&s)
	{
		swap(p,s.p);
		return *this;
	}
	void IspisiPodatke()const
	{
		Test();
		p->IspisiPodatke();
	}
	string DajIme()const
	{
		Test();
		return p->DajIme();
	}
	string DajPrezime()const
	{
		Test();
		return p->DajPrezime();
	}
	int DajBrojIndeksa()const
	{
		Test();
		return p->DajBrojIndeksa();
	}
	int DajBrojPolozenih()const
	{
		Test();
		return p->DajBrojPolozenih();
	}
	double DajProsjek()const
	{
		Test();
		return p->DajProsjek();
	}
	void RegistrirajIspit(int ocjena)
	{
		Test();
		p->RegistrirajIspit(ocjena);
	}
	void PonistiOcjene()const
	{
		Test();
		p->PonistiOcjene();
	}
};
int main ()
{
	Student s1,s2;
	s1=StudentBachelor("miki","maus",2121);
	s2=StudentMaster("minie","maus",3222,2016);
	s1.RegistrirajIspit(6);
	s2.RegistrirajIspit(8);
	s2.RegistrirajIspit(9);
	s1.IspisiPodatke();s2.IspisiPodatke();
	s1=s2;
	s1.IspisiPodatke();
//	s2(s1);
	s2.IspisiPodatke();
	//s1(move(s2)); 
	s1.IspisiPodatke();
	s1=(move(s2));
	s1.IspisiPodatke();
	cout<<s1.DajIme()<<" "<<s1.DajPrezime()<<" "<<s1.DajProsjek()<<" "<<s1.DajBrojIndeksa()<<" "<<s1.DajBrojPolozenih()<<endl;
	s2.PonistiOcjene();
	s2.IspisiPodatke();
	return 0;
}
