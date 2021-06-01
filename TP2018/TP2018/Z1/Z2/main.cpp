/* TP, 2018/2019, Zadaća 1, Zadatak 2

	NAPOMENA: ulaz/izlaz za zadatke je specificiran
	javnim autotestovima. Zalbe za ne analiziranje testova
	se ne uvazavaju!

	NAPOMENA: nece svi (javni) testovi sa zamgera biti
	dostupni na c9.
*/
#include <iostream>
#include<vector>   
#include<stdexcept>
#include<complex>
//using namespace std;
using std::cout; 
using std::cin;
using std::vector;
using std::endl;
using std::domain_error;
using std::range_error;
using std::complex;
vector<vector<int>> KreirajMatricu(int a,int b)
{
	return vector<vector<int>>(a,vector<int>(b));
}
bool GrbavaMatrica(vector<vector<int>> m)
{
	vector<int> kolone;
	for(int i=0; i<m.size(); i++) {
		for(int j=0; j<m.at(i).size(); j++) {
			kolone.push_back(m.at(i).size());
		}
	}
	for(int i=0; i<kolone.size(); i++) {
		if(kolone.at(0)!=kolone.at(i))return true;
	}
	return false;
}
complex<double> VrhMatrice(vector<vector<int>> m,int a,int b)
{
	double pozicijax=a,pozicijay=b;
	complex<double> vracam(pozicijax,pozicijay);
	int c=a,d=b,vrijednost;

	if(GrbavaMatrica(m) || m.size()==0 || m.at(0).size()==0)throw domain_error("Nekorektna matrica");
	if(a>m.size() || b>m.at(0).size() || a<0 || b<0)throw range_error("Nekorektna pocetna pozicija");

	vrijednost=m.at(a).at(b);

	for(int i=0; i<m.size(); i++) {
		for(int j=0; j<m.at(0).size(); j++) {
			//unutrasnji vrh
			if(c+1!=m.size() && c-1>=0 && d+1!=m.at(i).size() && d-1>=0) {
				if(vrijednost>=m.at(c-1).at(d) && vrijednost>=m.at(c-1).at(d+1) && vrijednost>=m.at(c).at(d+1) && vrijednost>=m.at(c+1).at(d+1)
				        && vrijednost>=m.at(c+1).at(d) && vrijednost>=m.at(c+1).at(d-1) && vrijednost>=m.at(c).at(d-1) && vrijednost>=m.at(c-1).at(d-1)) {
					pozicijax=c;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					break;
				} else if(m.at(c-1).at(d)>=vrijednost && m.at(c-1).at(d)>=m.at(c-1).at(d+1) && m.at(c-1).at(d)>=m.at(c).at(d+1)
				          && m.at(c-1).at(d)>=m.at(c+1).at(d+1) && m.at(c-1).at(d)>=m.at(c+1).at(d) && m.at(c-1).at(d)>=m.at(c+1).at(d-1)
				          && m.at(c-1).at(d)>=m.at(c).at(d-1) && m.at(c-1).at(d)>=m.at(c-1).at(d-1)) {
					vrijednost=m.at(c-1).at(d);
					pozicijax=c-1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					c=c-1;

				} else if(m.at(c-1).at(d+1)>=vrijednost && m.at(c-1).at(d+1)>=m.at(c).at(d+1) && m.at(c-1).at(d+1)>=m.at(c+1).at(d+1)
				          && m.at(c-1).at(d+1)>=m.at(c+1).at(d) && m.at(c-1).at(d+1)>=m.at(c+1).at(d-1) && m.at(c-1).at(d+1)>=m.at(c).at(d-1)
				          && m.at(c-1).at(d+1)>=m.at(c-1).at(d-1) && m.at(c-1).at(d+1)>=m.at(c-1).at(d)) {
					vrijednost=m.at(c-1).at(d+1);
					pozicijax=c-1;
					pozicijay=d+1;
					vracam=complex<double>(pozicijax,pozicijay);
					c=c-1;
					d=d+1;

				} else if(m.at(c).at(d+1)>=vrijednost && m.at(c).at(d+1)>=m.at(c-1).at(d) && m.at(c).at(d+1)>=m.at(c-1).at(d+1)
				          && m.at(c).at(d+1)>=m.at(c).at(d+1) && m.at(c).at(d+1)>=m.at(c+1).at(d+1) && m.at(c).at(d+1)>=m.at(c+1).at(d)
				          && m.at(c).at(d+1)>=m.at(c+1).at(d-1) && m.at(c).at(d+1)>=m.at(c).at(d-1) && m.at(c).at(d+1)>=m.at(c-1).at(d-1)
				          && m.at(c).at(d+1)>=m.at(c-1).at(d)) {
					vrijednost=m.at(c).at(d+1);
					pozicijax=c;
					pozicijay=d+1;
					vracam=complex<double>(pozicijax,pozicijay);
					d=d+1;

				} else if(m.at(c+1).at(d+1)>=vrijednost && m.at(c+1).at(d+1)>=m.at(c-1).at(d) && m.at(c+1).at(d+1)>=m.at(c-1).at(d+1)
				          && m.at(c+1).at(d+1)>=m.at(c).at(d+1) && m.at(c+1).at(d+1)>=m.at(c+1).at(d) && m.at(c+1).at(d+1)>=m.at(c+1).at(d-1)
				          && m.at(c+1).at(d+1)>=m.at(c).at(d-1) && m.at(c+1).at(d+1)>=m.at(c-1).at(d-1)) {
					vrijednost=m.at(c+1).at(d+1);
					pozicijax=c+1;
					pozicijay=d+1;
					vracam=complex<double>(pozicijax,pozicijay);
					c=c+1;
					d=d+1;

				} else if(m.at(c+1).at(d)>=vrijednost && m.at(c+1).at(d)>=m.at(c-1).at(d) && m.at(c+1).at(d)>=m.at(c-1).at(d+1)
				          && m.at(c+1).at(d)>=m.at(c).at(d+1) && m.at(c+1).at(d)>=m.at(c+1).at(d-1) && m.at(c+1).at(d)>=m.at(c+1).at(d+1)
				          && m.at(c+1).at(d)>=m.at(c).at(d-1) && m.at(c+1).at(d)>=m.at(c-1).at(d-1)) {
					vrijednost=m.at(c+1).at(d);
					pozicijax=c+1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					c=c+1;

				} else if(m.at(c+1).at(d-1)>=vrijednost && m.at(c+1).at(d-1)>=m.at(c-1).at(d) && m.at(c+1).at(d-1)>=m.at(c-1).at(d+1)
				          && m.at(c+1).at(d-1)>=m.at(c).at(d+1) && m.at(c+1).at(d-1)>=m.at(c+1).at(d+1) && m.at(c+1).at(d-1)>=m.at(c).at(d-1)
				          && m.at(c+1).at(d-1)>=m.at(c-1).at(d-1)) {
					vrijednost=m.at(c+1).at(d-1);
					pozicijax=c+1;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					c=c+1;
					d=d-1;

				} else if(m.at(c).at(d-1)>=vrijednost && m.at(c).at(d-1)>=m.at(c-1).at(d) && m.at(c).at(d-1)>=m.at(c-1).at(d+1)
				          && m.at(c).at(d-1)>=m.at(c).at(d+1) && m.at(c).at(d-1)>=m.at(c+1).at(d+1) && m.at(c).at(d-1)>=m.at(c-1).at(d-1) &&
				          m.at(c).at(d-1)>=m.at(c+1).at(d)) {
					vrijednost=m.at(c).at(d-1);
					pozicijax=c;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					d=d-1;

				} else if(m.at(c-1).at(d-1)>=vrijednost && m.at(c-1).at(d-1)>=m.at(c-1).at(d) && m.at(c-1).at(d-1)>=m.at(c-1).at(d+1)
				          && m.at(c-1).at(d-1)>=m.at(c).at(d+1) && m.at(c-1).at(d-1)>=m.at(c+1).at(d+1) && m.at(c-1).at(d-1)>=m.at(c+1).at(d)
				          && m.at(c-1).at(d-1)>=m.at(c).at(d-1)) {
					vrijednost=m.at(c-1).at(d-1);
					pozicijax=c-1;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);

					c=c-1;
					d=d-1;
				}

			}
			//rubovi
			//coskovi
			else if(d-1<0 && c-1<0 && d+1!=m.at(0).size() && c+1!=m.size()) {
				if(vrijednost>=m.at(c).at(d+1) && vrijednost>=m.at(c+1).at(d+1) && vrijednost>=m.at(c+1).at(d)) {
					pozicijax=c;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);

					break;
				} else if(m.at(c).at(d+1)>=vrijednost && m.at(c).at(d+1)>=m.at(c+1).at(d+1) && m.at(c).at(d+1)>=m.at(c+1).at(d)) {
					pozicijax=c;
					pozicijay=d+1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c).at(d+1);
					d=d+1;
				} else if(m.at(c+1).at(d+1)>=vrijednost && m.at(c+1).at(d+1)>=m.at(c).at(d+1) && m.at(c+1).at(d+1)>=m.at(c+1).at(d)) {
					pozicijax=c+1;
					pozicijay=d+1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c+1).at(d+1);
					c=c+1;
					d=d+1;
				} else if(m.at(c+1).at(d)>=vrijednost && m.at(c+1).at(d)>=m.at(c+1).at(d+1) && m.at(c+1).at(d)>=m.at(c).at(d+1)) {
					pozicijax=c+1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c+1).at(d);
					c=c+1;
				}
			} else if(d-1<0 && c+1>=m.size() && d+1!=m.at(0).size() && c-1>=0) {
				if(vrijednost>=m.at(c-1).at(d) && vrijednost>=m.at(c-1).at(d+1) && vrijednost>=m.at(c).at(d+1)) {
					pozicijax=c;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);

					break;
				} else if(m.at(c-1).at(d)>=vrijednost && m.at(c-1).at(d)>=m.at(c-1).at(d+1) && m.at(c-1).at(d)>=m.at(c).at(d+1)) {
					pozicijax=c-1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c-1).at(d);
					c=c-1;
				} else if(m.at(c-1).at(d+1)>=vrijednost && m.at(c-1).at(d+1)>=m.at(c-1).at(d) && m.at(c-1).at(d+1)>=m.at(c).at(d+1)) {
					pozicijax=c-1;
					pozicijay=d+1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c-1).at(d+1);
					c=c-1;
					d=d+1;
				} else if(m.at(c).at(d+1)>=vrijednost && m.at(c).at(d+1)>=m.at(c-1).at(d) && m.at(c).at(d+1)>=m.at(c-1).at(d+1)) {
					pozicijax=c;
					pozicijay=d+1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c).at(d+1);
					d=d+1;
				}
			} else if(c-1<=0 && d+1==m.at(0).size() && c+1!=m.size() && d-1>=0) {
				if(vrijednost>=m.at(c+1).at(d) && vrijednost>=m.at(c+1).at(d-1) && vrijednost>=m.at(c).at(d-1)) {
					pozicijax=c;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);

					break;
				} else if(m.at(c+1).at(d)>=vrijednost && m.at(c+1).at(d)>=m.at(c+1).at(d-1) && m.at(c+1).at(d)>=m.at(c).at(d-1)) {
					pozicijax=c+1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c+1).at(d);
					c=c+1;
				} else if(m.at(c+1).at(d-1)>=vrijednost && m.at(c+1).at(d-1)>=m.at(c+1).at(d) && m.at(c+1).at(d-1)>=m.at(c).at(d-1)) {
					pozicijax=c+1;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c+1).at(d-1);
					c=c+1;
					d=d-1;
				} else if(m.at(c).at(d-1)>=vrijednost && m.at(c).at(d-1)>=m.at(c+1).at(d) && m.at(c).at(d-1)>=m.at(c+1).at(d-1)) {
					pozicijax=c;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c).at(d-1);
					d=d-1;
				}

			} else if(d+1==m.at(0).size() && c+1==m.size() && c-1<0 && d-1>=0) {
				if(vrijednost>=m.at(c).at(d-1)) {
					pozicijax=c;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					break;
				} else if(m.at(c).at(d-1)>=vrijednost) {
					pozicijax=c;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c).at(d-1);
					d=d-1;
				}
			} else if(c+1==m.size() && d-1<0 && c-1<0 && d+1!=m.at(0).size()) {
				if(vrijednost>=m.at(c).at(d+1)) {
					pozicijax=c;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					break;
				} else if(m.at(c).at(d+1)>=vrijednost) {
					pozicijax=c;
					pozicijay=d+1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c).at(d+1);
					d=d+1;
				}
			} else if(c-1<0 && d+1==m.at(0).size() && d-1<0 && c+1!=m.size()) {
				if(vrijednost>=m.at(c+1).at(d)) {
					pozicijax=c;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					break;
				} else if(m.at(c+1).at(d)>=vrijednost) {
					pozicijax=c+1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c+1).at(d);
					c=c+1;
				}
			} else if(c+1==m.size() && d+1==m.at(0).size() && d-1<0 && c-1>=0) {
				if(vrijednost>=m.at(c-1).at(d)) {
					pozicijax=c;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					break;
				} else if(m.at(c-1).at(d)>=vrijednost) {
					pozicijax=c-1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c-1).at(d);
					c=c-1;
				}
			} /*else if(c+1==m.size() && c-1<0 && d+1==m.at(0).size() && d-1<0) {
				pozicijax=c;
				pozicijay=d;
				vracam=complex<double>(pozicijax,pozicijay);
				break;
			}*/ else if(c+1==m.size() && d+1==m.at(0).size() && c-1>=0 && d-1>=0) {
				if(vrijednost>=m.at(c-1).at(d) && vrijednost>=m.at(c).at(d-1) && vrijednost>=m.at(c-1).at(d-1)) {
					pozicijax=c;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					break;
				} else if(m.at(c-1).at(d)>=vrijednost && m.at(c-1).at(d)>=m.at(c).at(d-1) && m.at(c-1).at(d)>=m.at(c-1).at(d-1)) {
					pozicijax=c-1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c-1).at(d);
					c=c-1;
				} else if(m.at(c).at(d-1)>=vrijednost && m.at(c).at(d-1)>=m.at(c-1).at(d) && m.at(c).at(d-1)>=m.at(c-1).at(d-1)) {
					pozicijax=c;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c).at(d-1);
					d=d-1;
				} else if(m.at(c-1).at(d-1)>=vrijednost && m.at(c-1).at(d-1)>=m.at(c-1).at(d) && m.at(c-1).at(d-1)>=m.at(c).at(d-1)) {
					pozicijax=c-1;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c-1).at(d-1);
					c=c-1;
					d=d-1;
				}
			} else if(c-1<0 && d-1!=0 && d+1!=m.at(0).size() && c+1!=m.size()) {
				if(vrijednost>=m.at(c).at(d+1) && vrijednost>=m.at(c+1).at(d+1) && vrijednost>=m.at(c+1).at(d) && vrijednost>=m.at(c+1).at(d-1)
				        && vrijednost>=m.at(c).at(d-1)) {
					pozicijax=c;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);

					break;
				} else if(m.at(c).at(d+1)>=vrijednost && m.at(c).at(d+1)>=m.at(c+1).at(d+1) && m.at(c).at(d+1)>=m.at(c+1).at(d)
				          && m.at(c).at(d+1)>=m.at(c+1).at(d-1)) {
					pozicijax=c;
					pozicijay=d+1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c).at(d+1);
					d=d+1;
				} else if(m.at(c+1).at(d+1)>=vrijednost && m.at(c+1).at(d+1)>=m.at(c).at(d+1) && m.at(c+1).at(d+1)>=m.at(c+1).at(d)
				          && m.at(c+1).at(d+1)>=m.at(c+1).at(d-1)) {
					pozicijax=c+1;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c+1).at(d+1);
					c=c+1;
					d=d+1;
				} else if(m.at(c+1).at(d)>=vrijednost && m.at(c+1).at(d)>=m.at(c).at(d+1) && m.at(c+1).at(d)>=m.at(c+1).at(d+1)
				          && m.at(c+1).at(d)>=m.at(c+1).at(d-1) && m.at(c+1).at(d)>=m.at(c).at(d-1)) {
					pozicijax=c+1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c+1).at(d);
					c=c+1;
				} else if(m.at(c+1).at(d-1)>=vrijednost && m.at(c+1).at(d-1)>=m.at(c).at(d+1) && m.at(c+1).at(d-1)>=m.at(c+1).at(d+1)
				          && m.at(c+1).at(d-1)>=m.at(c+1).at(d) && m.at(c+1).at(d-1)>=m.at(c).at(d-1)) {
					pozicijax=c+1;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c+1).at(d-1);
					c=c+1;
					d=d-1;
				} else if(m.at(c).at(d-1)>=vrijednost && m.at(c).at(d-1)>=m.at(c).at(d+1) && m.at(c).at(d-1)>=m.at(c+1).at(d+1) &&
				          m.at(c).at(d-1)>=m.at(c+1).at(d) && m.at(c).at(d-1)>=m.at(c+1).at(d-1)) {
					pozicijax=c;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c).at(d-1);
					d=d-1;
				}
			} else	if(c+1>=m.size() && d-1!=0 && d+1!=m.at(0).size() && c-1>=0) {
				if(vrijednost>=m.at(c-1).at(d) && vrijednost>=m.at(c-1).at(d+1) && vrijednost>=m.at(c).at(d+1) && vrijednost>=m.at(c).at(d-1)
				        && vrijednost>=m.at(c-1).at(d-1)) {
					pozicijax=c;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);

					break;
				} else if(m.at(c-1).at(d)>=vrijednost && m.at(c-1).at(d)>=m.at(c-1).at(d+1) && m.at(c-1).at(d)>=m.at(c).at(d+1) &&
				          m.at(c-1).at(d)>=m.at(c-1).at(d-1)) {
					pozicijax=c-1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c-1).at(d);
					c=c-1;
				} else if(m.at(c-1).at(d+1)>=vrijednost && m.at(c-1).at(d+1)>=m.at(c-1).at(d) && m.at(c-1).at(d+1)>=m.at(c).at(d+1) &&
				          m.at(c-1).at(d+1)>=m.at(c).at(d-1) && m.at(c-1).at(d+1)>=m.at(c-1).at(d-1)) {
					pozicijax=c-1;
					pozicijay=d+1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c-1).at(d+1);
					c=c-1;
					d=d+1;
				} else  if(m.at(c).at(d+1)>=vrijednost && m.at(c).at(d+1)>=m.at(c-1).at(d) && m.at(c).at(d+1)>=m.at(c-1).at(d+1) &&
				           m.at(c).at(d+1)>=m.at(c).at(d-1) && m.at(c).at(d+1)>=m.at(c-1).at(d-1)) {
					pozicijax=c;
					pozicijay=d+1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c).at(d+1);
					d=d+1;
				} else if(m.at(c).at(d-1)>=vrijednost && m.at(c).at(d-1)>=m.at(c-1).at(d) && m.at(c).at(d-1)>=m.at(c-1).at(d+1) &&
				          m.at(c).at(d-1)>=m.at(c).at(c+1) && m.at(c).at(d-1)>=m.at(c-1).at(d-1)) {
					pozicijax=c;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c).at(d-1);
					d=d-1;
				} else if(m.at(c-1).at(d-1)>=vrijednost && m.at(c-1).at(d-1)>=m.at(c-1).at(d) && m.at(c-1).at(d-1)>=m.at(c-1).at(d+1) &&
				          m.at(c-1).at(d-1)>=m.at(c).at(d+1) && m.at(c-1).at(d-1)>=m.at(c-1).at(d)) {
					pozicijax=c-1;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c-1).at(d-1);
					c=c-1;
					d=d-1;
				}
			} else if(d-1<0 && c-1>0 && c+1<m.size() && d+1!=m.at(0).size()) {
				if(vrijednost>=m.at(c-1).at(d) && vrijednost>=m.at(c-1).at(d+1) && vrijednost>=m.at(c).at(d+1) && vrijednost>=m.at(c+1).at(d+1) &&
				        vrijednost>=m.at(c+1).at(d)) {
					pozicijax=double(c);
					pozicijay=double(d);
					vracam=complex<double>(pozicijax,pozicijay);

					break;
				} else if(m.at(c-1).at(d)>=vrijednost && m.at(c-1).at(d)>=m.at(c-1).at(d+1) && m.at(c-1).at(d)>=m.at(c).at(d+1) &&
				          m.at(c-1).at(d)>=m.at(c+1).at(d+1) && m.at(c-1).at(d)>=m.at(c+1).at(d)) {
					pozicijax=c-1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c-1).at(d);
					c=c-1;
				} else if(m.at(c-1).at(d+1)>=vrijednost && m.at(c-1).at(d+1)>=m.at(c-1).at(d) && m.at(c-1).at(d+1)>=m.at(c).at(d+1) &&
				          m.at(c-1).at(d+1)>=m.at(c+1).at(d+1) && m.at(c-1).at(d+1)>=m.at(c+1).at(d)) {
					pozicijax=c-1;
					pozicijay=d+1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c-1).at(d+1);
					c=c-1;
					d=d+1;
				} else if(m.at(c).at(d+1)>=vrijednost && m.at(c).at(d+1)>=m.at(c-1).at(d) && m.at(c).at(d+1)>=m.at(c-1).at(d+1) &&
				          m.at(c).at(d+1)>=m.at(c+1).at(d+1) && m.at(c).at(d+1)>=m.at(c+1).at(d)) {
					pozicijax=c;
					pozicijay=d+1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c).at(d+1);
					d=d+1;
				} else if(m.at(c+1).at(d+1)>=vrijednost && m.at(c+1).at(d+1)>=m.at(c-1).at(d) && m.at(c+1).at(d+1)>=m.at(c-1).at(d+1) &&
				          m.at(c+1).at(d+1)>=m.at(c).at(d+1) && m.at(c+1).at(d+1)>=m.at(c+1).at(d)) {
					pozicijax=c+1;
					pozicijay=d+1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c+1).at(d+1);
					c=c+1;
					d=d+1;
				} else if(m.at(c+1).at(d)>=vrijednost && m.at(c+1).at(d)>=m.at(c-1).at(d) && m.at(c+1).at(d)>=m.at(c-1).at(d+1) &&
				          m.at(c+1).at(d)>=m.at(c).at(d+1) && m.at(c+1).at(d)>=m.at(c+1).at(d+1)) {
					pozicijax=c+1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c+1).at(d);
					c=c+1;
				}
			} else if(d+1>=m.at(0).size() && c-1!=0 && c+1!=m.size() && d-1>=0 ) {
				if(vrijednost>=m.at(c-1).at(d) && vrijednost>=m.at(c+1).at(d) && vrijednost>=m.at(c+1).at(d-1) && vrijednost>=m.at(c).at(d-1) &&
				        vrijednost>=m.at(c-1).at(d-1)) {
					pozicijax=c-1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);

					break;
				} else if(m.at(c-1).at(d)>=vrijednost && m.at(c-1).at(d)>=m.at(c+1).at(d) && m.at(c-1).at(d)>=m.at(c+1).at(d-1) &&
				          m.at(c-1).at(d)>=m.at(c).at(d-1) && m.at(c-1).at(d)>=m.at(c-1).at(d-1)) {
					pozicijax=c-1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c-1).at(d);
					c=c-1;
				} else if(m.at(c+1).at(d)>=vrijednost && m.at(c+1).at(d)>=m.at(c-1).at(d) && m.at(c+1).at(d)>=m.at(c+1).at(d-1) &&
				          m.at(c+1).at(d)>=m.at(c).at(d-1) && m.at(c+1).at(d)>=m.at(c-1).at(d-1)) {
					pozicijax=c+1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c+1).at(d);
					c=c+1;
				} else if(m.at(c+1).at(d-1)>=vrijednost && m.at(c+1).at(d-1)>=m.at(c-1).at(d) && m.at(c+1).at(d-1)>=m.at(c+1).at(d) &&
				          m.at(c+1).at(d-1)>=m.at(c).at(d-1) && m.at(c+1).at(d-1)>=m.at(c-1).at(d-1)) {
					pozicijax=c+1;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c+1).at(d-1);
					c=c+1;
					d=d-1;
				} else if(m.at(c).at(d-1)>=vrijednost && m.at(c).at(d-1)>=m.at(c-1).at(d) && m.at(c).at(d-1)>=m.at(c+1).at(d) &&
				          m.at(c).at(d-1)>=m.at(c+1).at(d-1) && m.at(c).at(d-1)>=m.at(c-1).at(d-1)) {
					pozicijax=c;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c).at(d-1);
					d=d-1;
				} else if(m.at(c-1).at(d-1)>=vrijednost && m.at(c-1).at(d-1)>=m.at(c-1).at(d) && m.at(c-1).at(d-1)>=m.at(c+1).at(d) &&
				          m.at(c-1).at(d-1)>=m.at(c+1).at(d-1) && m.at(c-1).at(d-1)>=m.at(c).at(d-1)) {
					pozicijax=c-1;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c-1).at(d-1);
					c=c-1;
					d=d-1;
				}
			} else if(c-1<0 && c+1>=m.size() && d-1>=0 && d+1!=m.at(0).size()) {
				if(vrijednost>=m.at(c).at(d+1) && vrijednost>=m.at(c).at(d-1)) {
					pozicijax=c;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					break;
				} else if(m.at(c).at(d+1)>=vrijednost && m.at(c).at(d+1)>=m.at(c).at(d-1)) {
					pozicijax=c;
					pozicijay=d+1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c).at(d+1);
					d=d+1;
				} else if(m.at(c).at(d-1)>=vrijednost && m.at(c).at(d-1)>=m.at(c).at(d+1)) {
					pozicijax=c;
					pozicijay=d-1;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c).at(d-1);
					d=d-1;
				}
			} else if(d-1<0 && d+1>=m.at(0).size() && c-1>=0 && c+1!=m.size()) {
				if(vrijednost>=m.at(c-1).at(d) && vrijednost>=m.at(c+1).at(d)) {
					pozicijax=c;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					break;
				} else if(m.at(c-1).at(d)>=vrijednost && m.at(c-1).at(d)>=m.at(c+1).at(d)) {
					pozicijax=c-1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c-1).at(d);
					c=c-1;
				} else if(m.at(c+1).at(d)>=vrijednost && m.at(c+1).at(d)>=m.at(c-1).at(d)) {
					pozicijax=c+1;
					pozicijay=d;
					vracam=complex<double>(pozicijax,pozicijay);
					vrijednost=m.at(c+1).at(d);
					c=c+1;
				}
			}

		}
	}
	return vracam;
}
int main ()
{
	try {
		int m1,n1;
		cout<<"Unesite broj redova i kolona matrice:"<<endl;
		cin>>m1>>n1;
		cout<<"Unesite elemente matrice: "<<endl;
		auto matrica(KreirajMatricu(m1,n1));
		for(int i=0; i<m1; i++) {
			for(int j=0; j<n1; j++) {
				cin>>matrica.at(i).at(j);
			}
		}
		cout<<"Unesite poziciju odakle zapocinje pretraga:"<<endl;
		int poz1,poz2;
		cin>>poz1>>poz2;
		complex<double> vrh=VrhMatrice(matrica,poz1,poz2);
		cout<<"Nadjen je vrh matrice na poziciji "<<vrh.real()<<" "<<vrh.imag()<<endl;
		cout<<"Njegova vrijednost je "<<matrica.at(vrh.real()).at(vrh.imag())<<endl;
	} catch (domain_error izuzetak) {
		cout<<izuzetak.what()<<endl;
	} catch(range_error izuzetak) {
		cout<<"Greska: "<<izuzetak.what()<<endl;
	}
	return 0;
}
