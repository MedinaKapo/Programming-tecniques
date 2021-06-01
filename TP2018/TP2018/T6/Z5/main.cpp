/*
    TP 2018/2019: Tutorijal 6, Zadatak 5

	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
	i sugestije saljite na mail: khodzic2@etf.unsa.ba

	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include<stdexcept>
#include<new>
#include<memory>
#include<vector>
#include<deque>
#include<type_traits>
using namespace std;
template<typename tip1>
//nestajalo mi je  interneta,pa mi je stalno izlazilo not saved dok sam radila tutorijal,a i c9 je bio cudan
void UnistiMatricu(tip1 v,int n)
{
	for(int i=0; i<n; i++)delete[]v[i];
	delete[]v;
} 
template<typename tip>
auto KreirajDinamickuKopiju2D(tip v)->typename remove_reference<decltype(v[0][0])>::type**
{
	typename remove_reference<decltype(v[0][0])>::type**a;
	try {
		a=new typename remove_reference<decltype(v[0][0])>::type*[v.size()];
		try {
			for(int i=0; i<v.size(); i++) {
				a[i]=new typename remove_reference<decltype(v[0][0])>::type[v[i].size()];
			}
			for(int i=0; i<v.size(); i++) {
				for(int j=0; j<v[i].size(); j++) {
					a[i][j]=v[i][j];
				}
			}

		} catch(bad_alloc) {
			for(int i=0; i<v.size(); i++)delete[] a[i];
			delete[] a;
			throw;
		}

		return a;
	} catch(bad_alloc) {
		throw;
	}

}
int main ()
{
	int n;
	cout<<"Unesite broj redova kvadratne matrice: ";
	cin>>n;
	int br;
	try {
		vector<deque<int>> mat;

		try {
			mat.resize(n);
			try {

				for(int i=0; i<n; i++)mat.at(i).resize(n);
			} catch(bad_alloc) {
				throw;

			}
		} catch(bad_alloc) {
			throw;
		}
		cout<<"Unesite elemente matrice: ";
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				cin>>br;
				mat[i][j]=br;
			}
		}
		try {
			int **v=KreirajDinamickuKopiju2D(mat);
			for(int i=0; i<n; i++) {
				for(int j=0; j<n; j++) {
					cout<<v[i][j]<<" ";
				}
				cout<<endl;
			}
			UnistiMatricu(v,n);
		} catch(bad_alloc izuzetak) {
			cout<<"Izuzetak: "<<izuzetak.what()<<endl;
		}
	}

	catch(...) {
		cout<<"Nedovoljno memorije"<<endl;
	}

	return 0;
}
