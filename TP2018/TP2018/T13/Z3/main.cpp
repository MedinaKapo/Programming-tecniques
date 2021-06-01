/* 
    TP 16/17 (Tutorijal 13, Zadatak 3)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<string>
#include<stdexcept>
#include<vector>
#include<algorithm>   
using namespace std;
class ApstraktniStudent{
	protected:
	string ime,prezime;
	int index,brojpolozenih;
	double prosjek;
	public:
	ApstraktniStudent(string ime1,string prezime1,int index1):ime(ime1),prezime(prezime1),index(index1){
		brojpolozenih=0;
		prosjek=5;
	}
	virtual ~ApstraktniStudent(){};
	string DajIme()const{return ime;}
	string DajPrezime()const{return prezime;}
	int DajBrojIndeksa()const{return index;}
	int DajBrojPolozenih()const{return brojpolozenih;}
	double DajProsjek()const{return prosjek;}
	void RegistrirajIspit(int ocjena){
		if(ocjena<5 || ocjena>10)throw domain_error("Neispravna ocjena");
		else if(ocjena==5)return;
		else{
			double suma;
			suma=prosjek*brojpolozenih;
			brojpolozenih++;
			suma+=ocjena;
			prosjek=suma/brojpolozenih;
		}
	}
	void PonistniOcjene(){
		brojpolozenih=0;
		prosjek=5;
	}
	virtual void IspisiPodatke()const=0;
	virtual ApstraktniStudent *DajKopiju()const=0;
};
class StudentBachelor:public ApstraktniStudent{
	public:
	StudentBachelor(string ime,string prezime,int index):ApstraktniStudent(ime,prezime,index){}
	void IspisiPodatke()const override{
		cout<<"Student bachelor studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<","<<endl;
		cout<<"ima prosjek "<<DajProsjek()<<"."<<endl;
	}
	StudentBachelor *DajKopiju()const override{
		return new StudentBachelor(*this);
	}
};
class StudentMaster:public ApstraktniStudent{
	int diploma;
	public:
	StudentMaster(string ime,string prezime,int indeks,int diploma):ApstraktniStudent(ime,prezime,indeks),diploma(diploma){}
	void IspisiPodatke()const override{
		cout<<"Student master studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<","<<endl;
		cout<<"zavrsio bachelor studij godine "<<diploma<<",ima prosjek "<<DajProsjek()<<"."<<endl;
	}
	StudentMaster *DajKopiju()const override{
		return new StudentMaster(*this);
	}
};
class Fakultet{
	vector<ApstraktniStudent*>studenti;
	bool Test(int n){
		for(int i=0;i<studenti.size();i++){
			if(studenti.at(i)->DajBrojIndeksa()==n)return true;
		}
		return false;
	}
	public:
	explicit Fakultet()=default;
	//~Fakultet(){for(auto i:studenti)delete i;}
	~Fakultet(){for(auto it=studenti.begin();it!=studenti.end();it++)delete *it;}
	
	Fakultet(const Fakultet &f){
		/*studenti.resize(f.studenti.size());
		try{
			for(int i=0;i<f.studenti.size();i++)
			studenti.push_back(f.studenti.at(i)->DajKopiju());
		}
		catch(...){
			for(int i=0;i<f.studenti.size();i++)delete studenti.at(i);
			studenti.resize(0);throw;
		}*/
		for(int i=0;i<f.studenti.size();i++)studenti.push_back(f.studenti.at(i)->DajKopiju());
	}
	Fakultet &operator=(const Fakultet &f){
		if(&f!=this){
			for(int i=0;i<studenti.size();i++)delete studenti.at(i);
			studenti.resize(0);
			studenti.resize(f.studenti.size());
			for(int i=0;i<f.studenti.size();i++)studenti.at(i)=f.studenti.at(i)->DajKopiju();
		}
		return *this;
	}
	
/*	Fakultet &operator=(const Fakultet &f){
		swap(studenti,f.studenti);
		return *this;
	}*/
	/*Fakultet &operator=(const Fakultet &f){
		vector<ApstraktniStudent*>novi;
		novi.resize(f.studenti.size());
		try{
			for(int i=0;i<f.studenti.size();i++)novi.push_back(f.studenti.at(i));
	}
	catch(...){
		for(int i=0;i<f.studenti.size();i++)delete novi.at(i);
		novi.resize(0);throw;
	}
	for(int i=0;i<studenti.size();i++)delete studenti.at(i);
	studenti.resize(0);
	studenti.resize(novi.size());
	studenti=novi;
	return *this;
	}*/
	
	Fakultet(Fakultet &&f){
		studenti.resize(f.studenti.size());
		studenti=f.studenti;
		f.studenti.resize(0);
	}
	Fakultet &operator=(Fakultet &&f){
		for(int i=0;i<studenti.size();i++)delete studenti.at(i);
		studenti.resize(f.studenti.size());
		studenti=f.studenti;
		f.studenti.resize(0);
	//swap(studenti,f.studenti);
		return *this;
	}

	void UpisiStudenta(string ime,string prezime,int indeks){
		if(Test(indeks)==true)throw logic_error("Student sa zadanim brojem indeksa vec postoji");
		auto student=new StudentBachelor(ime,prezime,indeks);
		studenti.push_back(student);
	}
	void UpisiStudenta(string ime,string prezime,int indeks,int diploma){
		if(Test(indeks)==true)throw logic_error("Student sa zadanim brojem indeksa vec postoji");
		auto student=new StudentMaster(ime,prezime,indeks,diploma);
		studenti.push_back(student);
	}
	void ObrisiStudenta(int n){
		if(Test(n)==false)throw logic_error("Student sa zadanim brojem indeksa ne postoji");
		bool obrisano=false;
		for(auto it=studenti.begin();it!=studenti.end();it++){
			if((*it)->DajBrojIndeksa()==n){
				delete *it; 
				studenti.erase(it);
				obrisano=true;
			}
		}
		if(obrisano==false)throw logic_error("Student sa zadanim brojem indeksa ne postoji");
	}
	ApstraktniStudent &operator[](int n){
		if(Test(n)==false)throw logic_error("Student sa zadanim brojem indeksa ne postoji");
		for(auto it=studenti.begin();it!=studenti.end();it++){
			if((*it)->DajBrojIndeksa()==n)return **it;
		}
		throw logic_error("Student sa zadanim brojem indeksa ne postoji");
	}
	ApstraktniStudent &operator[](int n)const{
		//if(Test(n)==false)throw logic_error("Student sa zadanim brojem indeksa ne postoji");
		for(auto it=studenti.begin();it!=studenti.end();it++){
			if((*it)->DajBrojIndeksa()==n)return **it;
		} 
		throw logic_error("Student sa zadanim brojem indeksa ne postoji"); 
	}
	void IspisiSveStudente()const{
		vector<ApstraktniStudent*>studenti1(studenti);
		sort(studenti1.begin(),studenti1.end(),[](ApstraktniStudent *s1,ApstraktniStudent *s2){
			double prosjek1,prosjek2;prosjek1=s1->DajProsjek();prosjek2=s2->DajProsjek();
			if(prosjek1!=prosjek2)return prosjek1>prosjek2;
			else return s1->DajBrojIndeksa()<s2->DajBrojIndeksa();
		});
		//for(auto x:studenti1)x->IspisiPodatke();
		for(int i=0;i<studenti1.size();i++)studenti1.at(i)->IspisiPodatke();
	} 
}; 
int main ()
{
	StudentBachelor s1("winnie","pooh",1234);
	s1.RegistrirajIspit(7);
	s1.RegistrirajIspit(5);
	s1.RegistrirajIspit(8);
	StudentMaster s2("johhny","bravo",4321,2010);
	s2.RegistrirajIspit(6);
	s2.RegistrirajIspit(8);
	s2.RegistrirajIspit(9);
	cout<<s1.DajIme()<<" "<<s1.DajPrezime()<<" "<<s1.DajBrojIndeksa()<<" "<<s1.DajBrojPolozenih()<<endl;
	s1.IspisiPodatke();
	cout<<s2.DajIme()<<" "<<s2.DajPrezime()<<" "<<s2.DajBrojIndeksa()<<" "<<s2.DajBrojPolozenih()<<endl;
	s2.IspisiPodatke();
	Fakultet f;
	f.UpisiStudenta("Miki","Maus",3333);
	f.UpisiStudenta("Tom","Macak",4545,1998);
	Fakultet f1(f);
	Fakultet f2=f;
	Fakultet f3(move(f1));
	f.ObrisiStudenta(3333);
	f.UpisiStudenta("fifi","cvijetno",1111);
//	f.UpisiStudenta("ed","eddy",3454,2000);
	f[4545].IspisiPodatke();
	f.IspisiSveStudente();
	s1.PonistniOcjene();
	s1.IspisiPodatke();
	f=(move (f2));
	return 0;
}