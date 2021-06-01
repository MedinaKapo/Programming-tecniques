/*
    TP 2018/2019: Tutorijal 6, Zadatak 1

	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
	i sugestije saljite na mail: khodzic2@etf.unsa.ba

	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include<cmath>
#include<limits>
#include<stdexcept>
#include<new>
using namespace std;
template<typename tip>
//nestajalo mi je interneta,pa stalno mi je izlazilo "not saved" a i c9 je bio cudan ovih dana 
tip *GenerirajStepeneDvojke(int n)
{
	tip* niz=nullptr;
	if(n<=0)throw domain_error("Broj elemenata mora biti pozitivan");
	try {
		niz=new tip[n];
		niz[0]=1;
		for(int i=1; i<n; i++) {
			niz[i]=niz[i-1]*2;
			if(niz[i]>numeric_limits<tip>::max() || niz[i-1]>niz[i])throw overflow_error("Prekoracen dozvoljeni opseg");
		}
		return niz;
	} catch(overflow_error) {
		delete[] niz;
		throw;
	} catch(bad_alloc) {
		delete[] niz;
		throw runtime_error("Alokacija nije uspjela");
	}

}
int main()
{
	try {
		int n;
		cout<<"Koliko zelite elemenata: ";
		cin>>n;
		unsigned long long int *p=GenerirajStepeneDvojke<unsigned long long int>(n);
		for(int i=0; i<n; i++)
			cout<<p[i]<<" ";
		cout<<endl;
		delete[] p;

	} catch(domain_error izuzetak) {
		cout<<"Izuzetak: "<<izuzetak.what()<<endl;
	} catch(runtime_error izuzetak1) {
		cout<<"Izuzetak: "<<izuzetak1.what()<<endl;
	} catch(overflow_error izuzetak2) {
		cout<<"Izuzetak: "<<izuzetak2.what()<<endl;
	}
	return 0;
}
