/* 
    TP 16/17 (Tutorijal 11, Zadatak 1)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
using namespace std;
class NeobicnaKlasa{
	int broj;
	public:
	explicit NeobicnaKlasa(int a){
		broj=a;
		cout<<"Direktna inicijalizacija"<<endl;
	}
	NeobicnaKlasa (double n){
		broj=n;
		cout<<"Kopirajuca inicijalizacija"<<endl;
	}  
}; 
int main ()
{
	NeobicnaKlasa k1(5);
	NeobicnaKlasa k2=5;
	return 0;
}