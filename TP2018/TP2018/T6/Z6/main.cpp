/*
    TP 2018/2019: Tutorijal 6, Zadatak 6

	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
	i sugestije saljite na mail: khodzic2@etf.unsa.ba

	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include<vector> 
#include<deque>
#include<stdexcept>
#include<new>
#include<type_traits>
using namespace std;
template<typename tip>
//nestajalo mi je interneta,pa mi je stalno izlazilo not saved,radila sam tutorijal ne znam tacno
//vise na kojim zadacima, a i c9 je bio cudan
auto KreirajDinamickuKopiju2D(tip v)->typename remove_reference<decltype(v[0][0])>::type**
{
	try {
		typename remove_reference<decltype(v[0][0])>::type **a=new typename remove_reference<decltype(v[0][0])>::type*[v.size()];
		try {
			int vel=0;
			for(int i=0; i<v.size(); i++)vel+=v[i].size();
			a[0]=new typename remove_reference<decltype(v[0][0])>::type[vel];
			for(int i=1; i<v.size(); i++)
				a[i]=a[i-1]+v[i-1].size();
			for(int i=0; i<v.size(); i++) {
				for(int j=0; j<v[i].size(); j++)
					a[i][j]=v[i][j];
			}
		}

		catch(...) {
			delete[] a;
			throw;
		}
		return a;
	} catch(...) {
		throw;
	}
}
int main ()
{

	int n;
	cout<<"Unesite broj redova kvadratne matrice: ";
	cin>>n;
	try {
		vector<deque<int>> mat;
		try {
			mat.resize(n);
			try {
				for(int i=0; i<n; i++)mat[i].resize(n);
			} catch(bad_alloc) {
				throw;
			}
		} catch(bad_alloc) {
			throw;
		}

		cout<<"Unesite elemente matrice: ";
		int br;
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				cin>>br;
				mat[i][j]=br;
			}
		}

		int **v=KreirajDinamickuKopiju2D(mat);
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				cout<<v[i][j]<<" ";
			}
			cout<<endl;
		}
		delete[] v[0];
		delete[] v;
	} catch(bad_alloc) {
		cout<<"Nedovoljno memorije"<<endl;
	}


	return 0;
}
