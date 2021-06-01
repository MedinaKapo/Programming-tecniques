/* 
    TP 16/17 (Tutorijal 7, Zadatak 3)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include<cstring>
#include<new>
#include<stdexcept>
#include<algorithm>
using namespace std;


int main ()
{
	int n;
	cout<<"Koliko zelite recenica: ";
	cin>>n;
	cin.ignore(1000,'\n');  
	string **recenice=nullptr;
	
		cout<<"Unesite recenice:"<<endl;
		try{
		recenice=new string*[n]{};
		try{
			for(int i=0;i<n;i++){ 
				//recenice[i]=new string();
		/*	}
		for(int i=0;i<n;i++){*/
			string radni_prostor; 
			getline(cin,radni_prostor);
			recenice[i]=new string(radni_prostor);
		}
		sort(recenice,recenice+n,[](const string *a,const string *b){
			if(*a<*b)return true;
			return false;
		});
		cout<<"Sortirane recenice:"<<endl;
		for(int i=0;i<n;i++)
		cout<<*recenice[i]<<endl;
		for(int i=0;i<n;i++)delete recenice[i];
		delete[] recenice;
	}
	catch(...){
		delete[] recenice;
		throw;
	} 
		}
	catch(bad_alloc){
		cout<<"Problemi s memorijom!"<<endl;
	}

	return 0;
}