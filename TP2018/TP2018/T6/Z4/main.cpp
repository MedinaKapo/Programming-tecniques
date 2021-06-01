/*
    TP 2018/2019: Tutorijal 6, Zadatak 4

	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
	i sugestije saljite na mail: khodzic2@etf.unsa.ba

	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include<stdexcept>
#include<new>
using namespace std;
//nestajalo mi je interneta,pa mi je stalno izlazilo not saved dok sam radila tutorijal, a i c9 je bio cudan
void UnistiMatricu(int **mat,int n)
{
	delete[]mat[0]; 
	delete[] mat;
}
int **KreirajTrougao(int n)
{
	if(n<=0)throw domain_error("Broj redova mora biti pozitivan");
	int **a=nullptr;
	int vel=0;
	for(int i=0; i<n; i++)vel+=2*i+1;
	try {
		a=new int*[n];
		try {
			a[0]=new int[vel];
			//	a[0]=new int[n*n];
			for(int i=1; i<n; i++)
				a[i]=a[i-1]+2*i-1;
			for(int i=0; i<n; i++) {
				for(int j=0; j<2*i+1; j++) {
					if(j==0 || j==2*i)a[i][j]=i+1;
					else if(j==(2*i)/2)a[i][j]=1;
					else if(j<(2*i)/2)a[i][j]=a[i][j-1]-1;
					else if(j>(2*i)/2)a[i][j]=a[i][j-1]+1;
				}
			}
			return a;
		} catch(...) {
			throw;
		}
	} catch(bad_alloc) {
		delete[] a;
		//cout<<"Problemi sa memorijom!"<<endl;
		throw;
	}

}
int main ()
{
	try {
		int n;
		cout<<"Koliko zelite redova: ";
		cin>>n;
		try {
			int **a=KreirajTrougao(n);
			for(int i=0; i<n; i++) {
				for(int j=0; j<2*i+1; j++) {
					cout<<a[i][j]<<" ";
				}
				cout<<endl;
			}
			UnistiMatricu(a,n);
		} catch(bad_alloc) {
			cout<<"Izuzetak: Nedovoljno memorije!"<<endl;
			//UnistiMatricu(a,n);
		}
	} catch(bad_alloc) {
		cout<<"Izuzetak: Nedovoljno memorije!"<<endl;

	} catch(domain_error izuzetak) {
		cout<<"Izuzetak: "<<izuzetak.what()<<endl;
	}

	return 0;
}
