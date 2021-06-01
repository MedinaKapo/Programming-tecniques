/*
    TP 16/17 (Tutorijal 7, Zadatak 2)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include<algorithm>
#include<stdexcept>
#include<cstring>
#include<new>
using namespace std;
int main () 
{
	int n;
	cout<<"Koliko zelite recenica: ";
	cin>>n;
	cin.ignore(10000,'\n');
	char **recenice=nullptr;
	try {
		cout<<"Unesite recenice:"<<endl;
		recenice=new char*[n];
		for(int i=0; i<n; i++) {
			char radni_prostor[1000];
			cin.getline(radni_prostor,sizeof radni_prostor);
			recenice[i]=new char[strlen(radni_prostor)+1];
			strcpy(recenice[i],radni_prostor);
		}
		cout<<"Sortirane recenice: "<<endl;
		sort(recenice,recenice+n,[](const char *a,const char *b) {
			if(strcmp(a,b)<0)return true;
			return false;
		}); 
		for(int i=0; i<n; i++)   
			cout<<recenice[i]<<endl;
		for(int i=0; i<n; i++)
			delete[]recenice[i];
		delete[] recenice;
	} catch(bad_alloc) {
		cout<<"Problemi s memorijom!"<<endl;
		delete[] recenice;
	}
	return 0;
}
