/* TP, 2018/2019, Zadaća 1, Zadatak 3

	NAPOMENA: ulaz/izlaz za zadatke je specificiran
	javnim autotestovima. Zalbe za ne analiziranje testova
	se ne uvazavaju!

	NAPOMENA: nece svi (javni) testovi sa zamgera biti
	dostupni na c9.
*/
#include <iostream>
#include<vector>
#include<iomanip>
#include<stdexcept>   
//using namespace std;
using std::cout;
using std::cin;
using std::endl; 
using std::vector;
using std::fixed;
using std::right;
using std::setw;
using std::domain_error;

int BrojRedova(vector<vector<int>> matrica)
{
	return matrica.size();
}
int BrojKolona(vector<vector<int>> matrica)
{
	return matrica.at(0).size();
}
vector<vector<int>> KreirajMatricu(int br_redova,int br_kolona)
{
	return vector<vector<int>> (br_redova,vector<int>(br_kolona));
}
vector<vector<int>> UnesiMatricu(int br_redova,int br_kolona)
{
	auto m(KreirajMatricu(br_redova,br_kolona));
	for(int i=0; i<br_redova; i++) {
		for(int j=0; j<br_kolona; j++) {
			cin>>m.at(i).at(j);
		}
	}
	return m;
}
bool GrbavaMatrica(vector<vector<int>> matrica)
{
	int redovi=BrojRedova(matrica);
	vector<int> kolone;
	if(matrica.size()==0)return false;
	for(int i=0; i<redovi; i++) {
		kolone.push_back(matrica.at(i).size());
	}
	for(int i=0; i<redovi; i++) {
		for(int j=0; j<redovi; j++) {
			if(kolone.at(i)!=kolone.at(j)) {
				return true;
			}
		}
	}
	return false;
}
int NajvecaSirina(vector<vector<int>> m)
{
	int brojac,max=0;
	for(int i=0; i<m.size(); i++) {
		for(int j=0; j<m.at(i).size(); j++) {
			brojac=0;
			if(m.at(i).at(j)<0) {
				m.at(i).at(j)*=(-1);
				brojac=1;

			}
			while(m.at(i).at(j)!=0) {
				m.at(i).at(j)/=10;
				brojac++;
			}
			if(brojac>max)max=brojac;
		}
	}
	return max;
}
void IspisiMatricu(vector<vector<int>> m)
{

	int max=NajvecaSirina(m);
	for(int i=0; i<BrojRedova(m); i++) {
		for(int j=0; j<BrojKolona(m); j++) {
			cout<<fixed<<setw(max+1)<<right<<m.at(i).at(j);
		}
		cout<<endl;
	}
}

vector<vector<int>> KroneckerovProizvod(vector<vector<int>> matrica1,vector<vector<int>> matrica2)
{
	try {
		if(GrbavaMatrica(matrica1) && GrbavaMatrica(matrica2)==false)throw domain_error("Prvi parametar nema formu matrice");
		else if(GrbavaMatrica(matrica2) && GrbavaMatrica(matrica1)==false)throw domain_error("Drugi parametar nema formu matrice");
		else if(GrbavaMatrica(matrica1) && GrbavaMatrica(matrica2))throw domain_error("Parametri nemaju formu matrice");
	} catch(domain_error izuzetak) {
		throw;
	}
	int m1,n1,m2,n2,m3,n3;
	m1=BrojRedova(matrica1);
	//osim opreza kada su grbave matrice u pitanju,treba se obratiti paznja sta ako je jedna od matrica formata 0x0
	//tada je lako naci da je broj redova jednak 0,medjutim program ce vjerovatno ili da krahira ili da posalje izuzetak
	//onda kada budemo pristupali broju kolona takve matrice. Zato,sljedeci ifovi ispituju upravo ovaj slucaj
	if(m1==0)n1=0;
	else
		n1=BrojKolona(matrica1);
	m2=BrojRedova(matrica2);
	if(m2==0)n2=0;
	else
		n2=BrojKolona(matrica2);
	m3=m1*m2;
	n3=n1*n2;
	int uslov1=0,uslov2=0;
	auto proizvod(KreirajMatricu(m3,n3));
	for(int i=0; i<m1; i++) {
		for(int j=0; j<m2; j++) {
			for(int k=0; k<n1; k++) {
				for(int z=0; z<n2; z++) {
					if(uslov2==n1*n2) {
						uslov1=0;
						uslov2=0;
					}
					proizvod.at(uslov1).at(uslov2)=matrica1.at(i).at(k)*matrica2.at(j).at(z);
					uslov2++;
				}
				if(uslov2==n1*n2) {
					uslov2=0;
					uslov1++;
				}
			}

			if(uslov1==m1*m2)break;
		}
	}

	return proizvod;
}


int main ()
{
	try {
		cout<<"Unesite dimenzije prve matrice:"<<endl;
		int m1,n1;
		cin>>m1>>n1;
		cout<<"Unesite elemente prve matrice:"<<endl;
		auto A(UnesiMatricu(m1,n1));
		int m2,n2;
		cout<<"Unesite dimenzije druge matrice:"<<endl;
		cin>>m2>>n2;
		cout<<"Unesite elemente druge matrice:"<<endl;
		auto B(UnesiMatricu(m2,n2));
		cout<<"Njihov Kroneckerov proizvod glasi:"<<endl;
		vector<vector<int>> matrica;
		matrica=KroneckerovProizvod(A,B);
		IspisiMatricu(matrica);
	} catch(domain_error izuzetak) {
		cout<<izuzetak.what()<<endl;
		return 0;
	}

	return 0;
}
