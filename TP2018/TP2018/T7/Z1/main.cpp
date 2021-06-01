/*
    TP 16/17 (Tutorijal 7, Zadatak 1)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
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
		cout<<"Sortirane recenice:"<<endl;
		int k;
		for(int i=0; i<n; i++) {
			k=i;
			for(int j=i+1; j<n; j++) {
				if(strcmp(recenice[j],recenice[k])<0)k=j;
			}
			char*pomocni=recenice[i];
			recenice[i]=recenice[k];
			recenice[k]=pomocni;

		}
		for(int i=0; i<n; i++)cout<<recenice[i]<<endl;
		for(int i=0; i<n; i++)
			delete[] recenice[i];
		delete[] recenice;
	} catch(bad_alloc) { 
		cout<<"Problemi s memorijom!"<<endl;
		delete[] recenice;
	}

	return 0;
}
