/*
    TP 2018/2019: Tutorijal 6, Zadatak 2

	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
	i sugestije saljite na mail: khodzic2@etf.unsa.ba

	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include<vector>
#include<stdexcept>
#include<new>
using namespace std;
template<typename tip1>
//nestajalo mi je interneta,ne znam tacno koji zadatak,uglavnom radila sam tutorijal
//i stalno mi je izlazilo not saved
int duzina(tip1 p1,tip1 p2)
{
	int brojac=0;
	while(p1!=p2) {
		brojac++; 
		p1++;
	}
	return brojac;
}
template<typename tip>
auto KreirajIzvrnutiNiz(tip p1,tip p2)->typename remove_reference<decltype(*p1)>::type*
{
	int vel=duzina(p1,p2);
	typename remove_reference<decltype(*p1)>::type *d;
	try {
		d=new typename remove_reference<decltype(*p1)>::type[vel];
		while(p1!=p2) {
			d[--vel]=*p1++;
		}
		return d;
	} catch(bad_alloc) {
		throw;
	} 
}
int main ()
{

	int n;
	cout<<"Koliko zelite elemenata: ";
	cin>>n;
	try {
		double *p=new double[n];
		delete[] p;
		cout<<"Unesite elemente: ";
		double br;
		try{
		vector<double> v;
		for(int i=0; i<n; i++) {
			cin>>br;
			v.push_back(br);
		}
		p=KreirajIzvrnutiNiz(v.begin(),v.end());
		cout<<"Kreirani niz: ";
		for(int i=0; i<n; i++)
			cout<<p[i]<<" ";
		delete[] p;
	}
catch(bad_alloc){
	throw;
}
}
	catch(bad_alloc) {
		cout<<"Nedovoljno memorije!"<<endl;
	}


	return 0;
}
