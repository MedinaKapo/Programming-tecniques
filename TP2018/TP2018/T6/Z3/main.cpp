/*
    TP 2018/2019: Tutorijal 6, Zadatak 3

	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
	i sugestije saljite na mail: khodzic2@etf.unsa.ba

	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include<stdexcept>
#include<new>
using namespace std;
//nestajalo mi je interneta,pa stalno mi je izlazilo not saved dok sam radila tutorijal a i c9 je nesto bio cudan
void UnistiMatricu(int **mat,int n)
{
	if(!mat)return;
	for(int i=0; i<n; i++)delete[]mat[i];
	delete[] mat;
}
int **KreirajTrougao(int n) 
{
	if(n<=0)throw domain_error("Broj redova mora biti pozitivan");
	int **mat=new int*[n];
	for(int i=0; i<n; i++)mat[i]=nullptr;
	try {
		for(int i=0; i<n; i++) {
			mat[i]=new int[2*i+1];
			/*}
			for(int i=0;i<n;i++){*/
			for(int j=0; j<2*i+1; j++) {
				if(j==0 || j==2*i)mat[i][j]=i+1;
				else if(j==(2*i)/2)mat[i][j]=1;
				else if(j<(2*i)/2)mat[i][j]=mat[i][j-1]-1;
				else if(j>(2*i)/2)mat[i][j]=mat[i][j-1]+1;
			}
		}
	} catch(bad_alloc) {
		UnistiMatricu(mat,n);
		throw;
	}

	catch(domain_error) {
		throw;
	}
	return mat;
}
int main ()
{
	try {
		int n;
		int **a=nullptr;
		cout<<"Koliko zelite redova: ";
		cin>>n;
		try {
			a=KreirajTrougao(n);
			for(int i=0; i<n; i++) {
				for(int j=0; j<2*i+1; j++) {
					cout<<a[i][j]<<" ";
				}
				cout<<endl;
			}
			UnistiMatricu(a,n);
		} catch(bad_alloc) {
			cout<<"Izuzetak: Nedovoljno memorije!"<<endl;
		} catch(domain_error izuzetak) {
			cout<<"Izuzetak: "<<izuzetak.what()<<endl;
		}
	} catch(...) {
		cout<<"Izuzetak: Nedovoljno memorije!"<<endl;
	}
	return 0;
}
