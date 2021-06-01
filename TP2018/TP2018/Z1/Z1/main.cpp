/* TP, 2018/2019, Zadaća 1, Zadatak 1

	NAPOMENA: ulaz/izlaz za zadatke je specificiran
	javnim autotestovima. Zalbe za ne analiziranje testova
	se ne uvazavaju!

	NAPOMENA: nece svi (javni) testovi sa zamgera biti
	dostupni na c9.
*/
#include <iostream>
#include<vector>
//using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
long long int ObrniCifre(int n)
{ 
	int  vracam=0;  
	if(n<0)n*=-1;
	while(n!=0) {
		vracam*=10;
		vracam+=n%10;
		n/=10;
	}
	return vracam;
}
long long int SumaPalindroma(int n)
{
	int brojac=0;
	if(n<0)n*=(-1); 
	int suma=n;
	while(suma!=ObrniCifre(suma)) {
		suma+=ObrniCifre(suma);
		brojac++; 
	}
	return brojac;
}
vector<int> PalindromskaOtpornost(vector<int> v)
{
	vector<int> palindromi; 
	for(int i=0; i<v.size(); i++) {
		palindromi.push_back(SumaPalindroma(v.at(i)));
	}
	return palindromi;
}

int main ()
{
	int n,br;
	cout<<"Koliko zelite unijeti elemenata: ";
	cin>>n;
	cout<<"Unesite elemente: ";
	vector<int> brojevi;
	for(int i=0; i<n; i++) {
		cin>>br;
		brojevi.push_back(br);
	}
	vector<int> palindromi=PalindromskaOtpornost(brojevi);
	for(int i=0; i<palindromi.size(); i++) {
		cout<<"Palindromska otpornost broja "<<brojevi.at(i)<<" iznosi "<<palindromi.at(i)<<endl;
	}
	return 0;
}
