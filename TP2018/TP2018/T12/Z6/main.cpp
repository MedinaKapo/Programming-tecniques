/* 
    TP 16/17 (Tutorijal 12, Zadatak 6)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<iomanip>
#include<cstring>
#include<stdexcept>
#include<new>
#include<string>
using namespace std;
template<typename TipEl>
class Matrica{
	int br_redova,br_kolona;
	TipEl **elementi;
	char ime_matrice;
	static TipEl **AlocirajMemoriju(int br_redova,int br_kolona);
	static void DelaocirajMemoriju(TipEl **elementi,int br_redova);
	void KopirajElemente(TipEl **elementi);
	void TestIndeksa(int a,int b){
		if(a<1 || a>br_redova || b<1 || b>br_kolona)
		throw range_error("Neispravan indeks");
	}
	public:
	Matrica(int br_redova,int br_kolona,char ime=0);
	Matrica(const Matrica &m);
	Matrica(Matrica &&m);
	~Matrica(){DelaocirajMemoriju(elementi,br_redova);}
	Matrica &operator=(const Matrica &m);
	Matrica &operator=(Matrica &&m);
	//void Unesi();
	//void Ispisi(int sirina_ispisa)const;
	TipEl* operator[](int indeks)const{
		/*if(indeks<0 || indeks>br_redova)
		throw range_error("Neispravan indeks");*/
		
		return elementi[indeks];
	}
	TipEl* &operator[](int indeks){
		/*if(indeks<0 || indeks>br_redova)
		throw range_error("Neispravan indeks");*/
		return elementi[indeks];
	}
	TipEl &operator()(int a,int b){
		TestIndeksa(a,b);
		return elementi[a-1][b-1];
	}
	TipEl operator()(int a,int b)const{
		//TestIndeksa(a,b);
		if(a<0 || a>br_redova || b<0 || b>br_kolona)
		throw range_error("Neispravan indeks");
		return elementi[a-1][b-1];
	}
	friend ostream &operator<<(ostream &tok,const Matrica &m){
		int sirina=tok.width();
		for(int i=0;i<m.br_redova;i++){
			for(int j=0;j<m.br_kolona;j++)
			tok<<setw(sirina)<<m.elementi[i][j];
			tok<<endl;
		}
		return tok;
	}
	friend istream &operator>>(istream &tok,Matrica &m){
		for(int i=0;i<m.br_redova;i++){
			for(int j=0;j<m.br_kolona;j++){
			cout<<m.ime_matrice<<"("<<i+1<<","<<j+1<<") = ";
			tok>>m.elementi[i][j];}
		}
		return tok;
	}
	template<typename Tip2>
	friend Matrica<Tip2>operator+(const Matrica<Tip2>&m1,const Matrica<Tip2>&m2);
	template<typename Tip2>
	friend Matrica<Tip2>operator-(const Matrica<Tip2>&m1,const Matrica<Tip2>&m2);
	template<typename Tip2>
	friend Matrica<Tip2>operator*(const Matrica<Tip2>&m1,const Matrica<Tip2>&m2);
	template<typename Tip2>
	Matrica<Tip2>&operator+=(const Matrica<Tip2>&m2){
		if(br_redova!=m2.br_redova || br_kolona!=m2.br_kolona)
		throw  range_error("Matrice nemaju jednake dimenzije!");
		for(int i=0;i<br_redova;i++){
			for(int j=0;j<br_kolona;j++){
				elementi[i][j]=elementi[i][j]+m2.elementi[i][j];
			}
		}
		return *this;
	}
	template<typename Tip2>
	Matrica<Tip2>&operator-=(const Matrica<Tip2>&m2){
		if(br_redova!=m2.br_redova || br_kolona!=m2.br_kolona)
		throw range_error("Matrice nemaju jednake dimenzije!");
		for(int i=0;i<br_redova;i++){
			for(int j=0;j<br_kolona;j++){
				elementi[i][j]=elementi[i][j]-m2.elementi[i][j];
			}
		}
		return *this;
	}
	template<typename Tip2>
	friend Matrica<Tip2>&operator*=(Matrica<Tip2> &m1,const Matrica<Tip2>&m2)/*{
		if(br_kolona!=m2.br_redova)
		throw range_error("Matrice nisu saglasne za mnozenje!");
		Tip2 suma{};
		for(int i=0;i<br_redova;i++){
			for(int j=0;j<m2.br_kolona;j++){
				elementi[i][j]=0;
				for(int k=0;k<br_kolona;k++){
					elementi[i][j]=elementi[i][j]+elementi[i][k]*m2.elementi[k][j];
				}
				
			}
		}
		return *this;
	}*/;
	template<typename Tip2>
	friend Matrica<Tip2>operator*(Matrica<Tip2>&m1,int n);
	template<typename Tip2>
	friend Matrica<Tip2>&operator*=(Matrica<Tip2>&m,int n);
/*	Matrica<Tip2>&operator*=(int n){
		for(int i=0;i<br_redova;i++){
			for(int j=0;j<br_kolona;j++)
			elementi[i][j]=elementi[i][j]*n;
		}
		return *this;
	}*/
	template<typename Tip2>
	friend Matrica<Tip2>operator*(int n,Matrica<Tip2>&m);
	operator string()const{
		string vracam;
		vracam.push_back('{');
		for(int i=0;i<br_redova;i++){
			vracam.push_back('{');
			for(int j=0;j<br_kolona;j++){
				string pom=to_string((int)elementi[i][j]);
				vracam+=pom;
				if(j<br_redova-1)vracam.push_back(',');
			}
			vracam.push_back('}');
			if(i<br_redova-1)
			vracam.push_back(',');
		}
		vracam.push_back('}');
		return vracam;
	}
};
template<typename TipEl>
TipEl **Matrica<TipEl>::AlocirajMemoriju(int br_redova,int br_kolona){
	TipEl **elementi(new TipEl*[br_redova]{});
	try{
		for(int i=0;i<br_redova;i++)elementi[i]=new TipEl[br_kolona];
	}
	catch(...){
		DelaocirajMemoriju(elementi,br_redova);
		throw;
	}
	return elementi;
}
template<typename TipEl>
void Matrica<TipEl>::DelaocirajMemoriju(TipEl **elementi,int br_redova){
	for(int i=0;i<br_redova;i++)delete[]elementi[i];
	delete[]elementi;
}
template<typename TipEl>
Matrica<TipEl>::Matrica(int br_redova,int br_kolona,char ime):
br_redova(br_redova),br_kolona(br_kolona),ime_matrice(ime),
elementi(AlocirajMemoriju(br_redova,br_kolona)){}
template<typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi){
	for(int i=0;i<br_redova;i++)
	for(int j=0;j<br_kolona;j++)
	Matrica::elementi[i][j]=elementi[i][j];
}
template<typename TipEl>
Matrica<TipEl>::Matrica(const Matrica<TipEl>&m):br_redova(m.br_redova),
br_kolona(m.br_kolona),ime_matrice(m.ime_matrice),
elementi(AlocirajMemoriju(m.br_redova,m.br_kolona)){
	KopirajElemente(m.elementi);
}
template<typename TipEl>
Matrica<TipEl>::Matrica(Matrica<TipEl>&&m):br_redova(m.br_redova),
br_kolona(m.br_kolona),elementi(m.elementi),ime_matrice(m.ime_matrice){
	m.br_redova=0;m.elementi=nullptr;
}
template<typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator=(const Matrica<TipEl> &m){
	if(br_redova<m.br_redova || br_kolona<m.br_kolona){
		TipEl **novi_prostor(AlocirajMemoriju(m.br_redova,m.br_kolona));
		DelaocirajMemoriju(elementi,br_redova);
		elementi=novi_prostor;
	}
	else if(br_redova>m.br_redova)
	for(int i=m.br_redova;i<br_redova;i++)delete elementi[i];
	br_redova=m.br_redova;br_kolona=m.br_kolona;
	ime_matrice=m.ime_matrice;
	KopirajElemente(m.elementi);
	return *this;
}
template<typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator=(Matrica<TipEl> &&m){
	swap(br_redova,m.br_redova);swap(br_kolona,m.br_kolona);
	swap(ime_matrice,m.ime_matrice);
	swap(elementi,m.elementi);
	return *this;
}
/*template<typename TipEl>
void Matrica<TipEl>::Unesi(){
	for(int i=0;i<br_redova;i++)
	for(int j=0;j<br_kolona;j++){
		cout<<ime_matrice<<"("<<i+1<<","<<j+1<<") = ";
		cin>>elementi[i][j];
	}
}*/
/*template<typename TipEl>
void Matrica<TipEl>::Ispisi(int sirina_ispisa)const{
	for(int i=0;i<br_redova;i++){
		for(int j=0;j<br_kolona;j++)
		cout<<setw(sirina_ispisa)<<elementi[i][j];
		cout<<endl;
	}
}*/
template<typename TipEl>
Matrica<TipEl>operator+(const Matrica<TipEl>&m1,const Matrica<TipEl>&m2){
	if(m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona)
	throw domain_error("Matrice nemaju jednake dimenzije!");
	Matrica<TipEl>m3(m1.br_redova,m1.br_kolona);
	for(int i=0;i<m1.br_redova;i++)
	for(int j=0;j<m1.br_kolona;j++)
	m3.elementi[i][j]=m1.elementi[i][j]+m2.elementi[i][j];
	return m3;
}
template<typename TipEl>
Matrica<TipEl>operator-(const Matrica<TipEl>&m1,const Matrica<TipEl>&m2){
	if(m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona)
	throw domain_error("Matrice nemaju jednake dimenzije!");
	Matrica<TipEl>m3(m1.br_redova,m1.br_kolona);
	for(int i=0;i<m1.br_redova;i++)
	for(int j=0;j<m1.br_kolona;j++)
	m3.elementi[i][j]=m1.elementi[i][j]-m2.elementi[i][j];
	return m3;
}
template<typename TipEl>
Matrica<TipEl>operator*(const Matrica<TipEl>&m1,const Matrica<TipEl>&m2){
	if(m1.br_kolona!=m2.br_redova)
	throw domain_error("Matrice nisu saglasne za mnozenje");
	Matrica<TipEl>m3(m1.br_kolona,m2.br_redova);
	TipEl suma{};
	for(int i=0;i<m1.br_redova;i++){
		for(int j=0;j<m2.br_kolona;j++){
			m3.elementi[i][j]=0;
			for(int k=0;k<m1.br_kolona;k++){
				m3.elementi[i][j]+=m1.elementi[i][k]*m2.elementi[k][j];
			}
		}
	}
	return m3;
}
/*template<typename TipEl>
Matrica<TipEl>&operator+=(const Matrica<TipEl>&m2){
	if(m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona)
	throw domain_error("Matrice nemaju jednake dimenzije!");
	for(int i=0;i<m1.br_redova;i++){
		for(int j=0;j<m1.br_kolona;j++)
		m1.elementi[i][j]+=m2.elementi[i][j];
	}
	return m1;
}*/
/*template<typename TipEl>
Matrica<TipEl>&operator-=(Matrica<TipEl>&m1,const Matrica<TipEl>&m2){
	if(m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona)
	throw domain_error("Matrice nemaju jednake dimenzije!");
	for(int i=0;i<m1.br_redova;i++){
		for(int j=0;j<m1.br_kolona;j++)
		m1.elementi[i][j]-=m2.elementi[i][j];
	}
	return m1;
}*/
template<typename TipEl>
Matrica<TipEl>&operator*=(Matrica<TipEl>&m1,const Matrica<TipEl>&m2){
	if(m1.br_kolona!=m2.br_redova)
	throw domain_error("Matrice nisu saglasne za mnozenje");
	Matrica<TipEl>pom(m1.br_kolona,m2.br_redova);
	for(int i=0;i<m1.br_redova;i++){
		for(int j=0;j<m2.br_kolona;j++){
			pom.elementi[i][j]=0;
			for(int k=0;k<m1.br_kolona;k++){
				pom.elementi[i][j]+=m1.elementi[i][k]*m2.elementi[k][j];
			}
		}
	}
	m1=pom;
	return m1;
}
template<typename TipEl>
Matrica<TipEl>operator*(Matrica<TipEl>&m,int n){
	Matrica<TipEl>m1(m.br_redova,m.br_kolona);
	for(int i=0;i<m.br_redova;i++){
		for(int j=0;j<m.br_kolona;j++)
		m1.elementi[i][j]=m.elementi[i][j]*n;
	}
	return m1;
}
template<typename TipEl>
Matrica<TipEl> operator*(int n,Matrica<TipEl>&m){
	return m*n;
}
template<typename TipEl>
Matrica<TipEl>&operator*=(Matrica<TipEl>&m,int n){
	for(int i=0;i<m.br_redova;i++){
		for(int j=0;j<m.br_kolona;j++)
		m.elementi[i][j]=m.elementi[i][j]*n;
	}
	return m;
}
int main ()
{
	int m,n;
	cout<<"Unesi broj redova i kolona matrice:\n";
	cin>>m>>n;
	try{
		Matrica<double>a(m,n,'A'),b(m,n,'B');
		cout<<"Unesi matricu A:\n";
		cin>>a;
		cout<<"Unesi matricu B:\n";
		cin>>b;
		cout<<"Zbir ove dvije matrice je:\n";
		cout<<setw(7)<<a+b;
		a*=3;
		cout<<endl;
		cout<<setw(7)<<a;
		cout<<endl;
		a*=b;
		cout<<setw(7)<<a;
		cout<<endl;
		Matrica<double>c(m,n,'C'),d(m,n,'D');
		c=a*b;
		cout<<setw(7)<<c;
		cout<<endl;
		d=c*3;
		cout<<setw(7)<<d;
		cout<<endl;
		a+=d;
		cout<<setw(7)<<a;
		cout<<endl;
		cout<<b(1,1)<<endl;
		cout<<*b[1]<<endl;
		a-=d;
		cout<<setw(7)<<a; 
		cout<<endl; 
		cout<<setw(7)<<a-d;  
		cout<<endl;
		cout<<string(b)<<endl;
		const Matrica<double>e(a);
		cout<<setw(7)<<e;
		
	}
	catch(bad_alloc){
		cout<<"Nema dovoljno memorije!\n";
	}
	catch(range_error izuzetak){
		cout<<izuzetak.what()<<endl;
	}
	catch(domain_error izuzetak1){
		cout<<izuzetak1.what()<<endl;
	}
	return 0;
}