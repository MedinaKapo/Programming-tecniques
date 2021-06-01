/* TP, 2018/2019, Zadaća 1, Zadatak 4

	NAPOMENA: ulaz/izlaz za zadatke je specificiran
	javnim autotestovima. Zalbe za ne analiziranje testova
	se ne uvazavaju!

	NAPOMENA: nece svi (javni) testovi sa zamgera biti
	dostupni na c9.
*/
#include <iostream>
#include<string>
#include<vector>
//using namespace std;  
using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::endl;
bool Simetricna(string s)
{
	int duzina=s.length();
	if(duzina<2)return false;
	for(int i=0; i<duzina; i++) {
		if(s.at(i)!=s.at(duzina-i-1)) {
			if(s.at(i)>='A' && s.at(i)<='Z' && s.at(duzina-i-1)>='a' && s.at(duzina-i-1)<='z')s.at(i)+=32;
			else if(s.at(i)>='a' && s.at(i)<='z' && s.at(duzina-i-1)>='A' && s.at(duzina-i-1)<='Z')s.at(duzina-i-1)+=32;
			if(s.at(i)!=s.at(duzina-i-1))return false;
		}
	}
	return true;
}
vector<string> NadjiSimetricneRijeci(string s)
{
	vector<string> v;
	int i=0;
	int razmak=0;
	string rijec;
	int pocetak=0,kraj,broj=0; 
	while(i!=s.length()) {
		if((s.at(i)==' ' || s.at(i)=='.' || s.at(i)==',' || i==s.length()-1 || s.at(i)=='!' || s.at(i)=='?' || s.at(i)=='-' || s.at(i)==9)) {
			if(broj==0 && i+1!=s.length())kraj=razmak;
			else if(i+1==s.length())kraj=razmak+1;
			else
				kraj=razmak-1;
			rijec=s.substr(pocetak,kraj);

			if(Simetricna(rijec))v.push_back(rijec);
			pocetak=i+1;
			razmak=0;
			broj++;
		}
		i++;
		razmak++;
	}
	return v;
}
int main ()
{
	string recenica;
	cout<<"Unesite recenicu: "<<endl;
	getline(cin,recenica);
	vector<string> simetricne=NadjiSimetricneRijeci(recenica);
	if(simetricne.size()==0)cout<<"Recenica ne sadrzi simetricne rijeci!"<<endl;
	else {
		cout<<"Simetricne rijeci unutar recenice su: "<<endl;
		for(int i=0; i<simetricne.size(); i++) {
			cout<<simetricne.at(i)<<endl;
		}
	}
	return 0;
}
