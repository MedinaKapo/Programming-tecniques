/* 
    TP 16/17 (Tutorijal 12, Zadatak 4)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<cmath>
using namespace std;
class Kompleksni{
	double re,im;
	public:
	Kompleksni(double re=0,double im=0):re(re),im(im){}
	friend Kompleksni operator+(const Kompleksni &a){return a;}
	friend Kompleksni operator-(const Kompleksni &a){return {-a.re,-a.im};}
	friend Kompleksni operator+(const Kompleksni &a,const Kompleksni &b){
		return {a.re+b.re,a.im+b.im};
	}
	friend Kompleksni operator-(const Kompleksni &a,const Kompleksni &b){
		return Kompleksni(a.re-b.re,a.im-b.im);
	}
	friend Kompleksni operator*(const Kompleksni &a,const Kompleksni &b){
		return{a.re*b.re-a.im*b.im,a.re*b.im+a.im*b.re};
	}
	friend Kompleksni operator/(const Kompleksni &a,const Kompleksni &b){
		double pomocna(b.re*b.re+b.im*b.im);
		return{(a.re*b.re+a.im*b.im)/pomocna,(a.im*b.re-a.re*b.im)/pomocna};
	}
	friend bool operator==(const Kompleksni &a,const Kompleksni &b){
		return a.re==b.re && a.im==b.im;
	}
	friend bool operator!=(const Kompleksni &a,const Kompleksni &b){
		return !(a==b);
	}
	friend Kompleksni &operator+=(Kompleksni &a,const Kompleksni &b){
		a.re+=b.re;a.im+=b.im;
		return a;
	}
	friend Kompleksni &operator-=(Kompleksni &a,const Kompleksni &b){
		a.re-=b.re;a.im-=b.im;
		return a;
	}
	friend Kompleksni &operator*=(Kompleksni &a,const Kompleksni &b){
		double pomocna(a.re*b.im+a.im*b.re);
		a.re=a.re*b.re-a.im+b.im;a.im=pomocna;
		return a;
	}
	friend Kompleksni &operator/=(Kompleksni &a,const Kompleksni &b){
		double pom1(a.im*b.re-a.re*b.im),pom2(b.re*b.re+b.im*b.im);
		a.re=(a.re*b.re+a.im*b.im)/pom2;a.im=pom1/pom2;
		return a;
	}
	friend ostream &operator<<(ostream &tok,const Kompleksni &a){
		if(a.re==0 && a.im==0)tok<<"0";
		else if(a.re==0 && a.im!=0 && a.im!=1 && a.im!=-1)tok<<a.im<<"i";
		else if(a.re!=0 && a.im==0)tok<<a.re;
		else if(a.re!=0 && a.im>0 && a.im!=1)tok<<a.re<<"+"<<a.im<<"i";
		else if(a.re!=0 && a.im<0 && a.im!=-1)tok<<a.re<<a.im<<"i";
		else if(a.re!=0 && a.im==1)tok<<a.re<<"+i";
		else if(a.re!=0 && a.im==-1)tok<<a.re<<"-i";
		else if(a.re==0 && a.im==1)tok<<"i";
		else if(a.re==0 && a.im==-1)tok<<"-i";
		return tok;
	}
	friend istream &operator>>(istream &tok,Kompleksni &a);
	friend double real(const Kompleksni &a){return a.re;}
	friend double imag(const Kompleksni &a){return a.im;}
	friend double abs(const Kompleksni &a){
	return sqrt(a.re*a.re+a.im*a.im);
}
friend double arg(const Kompleksni &a){return atan2(a.im,a.re);}
friend Kompleksni conj(const Kompleksni &a){return {a.re,-a.im};}
friend Kompleksni sqrt(const Kompleksni &a){
	double rho(sqrt(abs(a))),phi(arg(a)/2);
	return {rho*cos(phi),rho*sin(phi)};
}
};
istream &operator>>(istream &tok,Kompleksni &a){
	char znak;
	tok>>ws;
	if(tok.peek()!='('){
		tok>>a.re;
		a.im=0;
	}
	else{
		tok>>znak>>a.re>>znak;
		if(znak!=',')tok.setstate(ios::failbit);
		tok>>a.im>>znak;
		if(znak!=')')tok.setstate(ios::failbit);
	}
/*	if(tok.peek()!='i'){
		tok>>a.re;
	}
	//tok>>ws;
	tok>>znak;
	if(tok.peek()=='\n'){tok>>ws;
	tok>>znak;}
	tok>>ws;
	int broj;
	if(tok.peek()=='+' || tok.peek()=='-'){
		if(znak=='\n'){
			tok>>ws;
		}
	tok>>broj;
	if(znak=='\n'){
		tok>>ws;
	}
	//tok>>ws;
	char znak1=znak;
	tok>>znak;
	//tok>>ws;
	if(tok.peek()=='i'){
		if(znak1=='-'){
			broj*=-1;
			a.im=broj;
		}
		else a.im=broj;
	}
	else a.re+=broj;
	}
	else if(tok.peek()=='\n'){a.im=0;return tok;}*/
	
	return tok;
}
int main ()
{
	cout<<Kompleksni(2,1)<<endl;
	cout<<Kompleksni(2,0)<<endl;
	cout<<Kompleksni(0,2)<<endl;
	cout<<Kompleksni(1,1)<<endl;
	cout<<Kompleksni(0,1)<<endl;
	cout<<Kompleksni(0,-1)<<endl;
	cout<<Kompleksni(1,0)<<endl;
	cout<<Kompleksni(-1,0)<<endl;
	Kompleksni k1(2,3),k2(1,2);
	cout<<k1+k2<<endl;
	k1+=k2;
	cout<<k1<<endl;
	cout<<k1-k2<<endl;
	k1=-k1;
	cout<<k1<<endl;
	k1-=k2;   
	cout<<k1<<endl; 
	cout<<k1/k2<<endl;
	cout<<k1*k2<<endl;
	k1*=k2;
	cout<<k1<<endl; 
	k1/=k2;
	cout<<k1<<endl;
	Kompleksni k3;
	cin>>k3;
	cout<<real(k3)<<" "<<imag(k3)<<" "<<abs(k3)<<" "<<arg(k3)<<" "<<conj(k3)<<" "<<sqrt(k3)<<" ";
	
	return 0;
}