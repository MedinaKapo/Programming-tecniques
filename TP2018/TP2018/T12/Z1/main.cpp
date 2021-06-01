/* 
    TP 16/17 (Tutorijal 12, Zadatak 1)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<stdexcept>
#include<iomanip>
#include<cmath>
using namespace std;
class Sat{
	int sati,minute,sekunde;
	public:
	static bool DaLiJeIspravno(int h,int m,int s){
		if(h<0 || h>=24 || m<0 || m>=60 || s<0 || s>=60)return false;
		return true;
	}
	Sat(){
		sati=0;
		minute=0;
		sekunde=0;
	}
	Sat(int sat,int minuta,int sekunda){
		
		if(sekunda>=60){
			int preljev;
			preljev=sekunda/60;
			sekunda-=preljev*60;
			minuta+=preljev;
		}
		if(minuta>=60){
			int preljev;
			preljev=minuta/60;
			minuta-=preljev*60;
			sat+=preljev;
		}
		if(sat>=24){
			int preljev;
			preljev=sat/24;
			sat-=preljev*24;
		}
		
		if(sekunda<0){
			while(sekunda<0){
				sekunda+=60;
			
				if(minuta==0){
					minuta=59;
					if(sat==0)sat=23;
				}else minuta--;
			}
		}
	
		if(minuta<0){
			while(minuta<0){
				minuta+=60;
				if(sat==0)sat=23;
				else sat--;
			
			}
		}
		
		if(sat<0){
			while(sat<0)sat+=24;
		}
		
	
		sati=sat;
		minute=minuta;
		sekunde=sekunda;
	}
	void Postavi(int sat,int minuta,int sekunda){
		if(DaLiJeIspravno(sat,minuta,sekunda)==false)throw domain_error("Neispravno vrijeme");
		sati=sat;
		minute=minuta;
		sekunde=sekunda;
	}
	Sat &operator++(){
		sekunde++;
		if(sekunde==60){
			sekunde=0;
			minute++;
		}
		if(minute==60){
			minute=0;
			sati++;
		}
		if(sati==24)sati=0;
		return *this;
	}
	Sat &operator--(){
		sekunde--;
		if(sekunde<0){
			sekunde=59;
			minute--;
		}
		if(minute<0){
			minute=59;
			sati--;
		}
		if(sati<0)sati=23;
		return *this;
	}
	Sat operator++(int){
		Sat pomocni(*this);
		sekunde++;
		if(sekunde==60){
			sekunde=0;
			minute++;
		}
		if(minute==60){
			minute=0;
			sati++;
		}
		if(sati==24)sati=0;
		return pomocni;
	}
	Sat operator--(int){
		Sat pomocni(*this);
		sekunde--;
		if(sekunde<0){
			sekunde=59;
			minute--;
		}
		if(minute<0){
			minute=59;
			sati--;
		}
		if(sati<0)sati=23;
		return pomocni;
	}
	Sat &operator+=(int n){
		int h,min,sec;
		if(n>0){
			min=minute;
			h=sati;
			sec=sekunde+n;}
		else{
				n*=-1;
			min=minute;
			h=sati;
			sec=sekunde+n;}
		
		Sat s1(h,min,sec);
		*this=s1;
		return *this;
	}
	Sat &operator-=(int n){
		int h,min,sec;
	/*	if(n<0)n*=-1;
		int n1=n,n2=n;
		h=(int)fabs(sati-(n%3600));
		min=(int)fabs(minute-(n%3600)/60);
		sec=(int)(fabs(sekunde-(n%60)/60));*/
		/*else{
			n*=-1;
			min=this->minute;
			h=this->sati;
			sec=n-this->sekunde;
		}*/
	//	Sat s1(h,min,sec);
		//*this=s1;
		if(n<0)n*=-1;
		sec=sekunde;min=minute;h=sati;
		Sat pom(sati,minute,sekunde);
		for(int i=0;i<n;i++){
			pom--;
		}
		
		*this=pom;
		return *this;
		
		
	}
	int DajSate()const{return sati;}
	int DajMinute()const{return minute;}
	int DajSekunde()const{return sekunde;}
	friend int operator-(const Sat &s1,const Sat &s2){
		return {(s1.sati-s2.sati)*3600+(s1.minute-s2.minute)*60+s1.sekunde-s2.sekunde};
	}
	Sat operator+(int n){
		int h,m,s;
		h=sati;
		m=minute;
		s=sekunde+n;
		Sat s3(h,m,s);
		return s3;
	}
	Sat operator-(int n){
	int h,m,s;
	h=sati;
	m=minute;
	s=sekunde-n;
	Sat s3(h,m,s);
		return s3;
	}
	friend ostream &operator<<(ostream &tok,const Sat &s){
		return tok<<setfill('0')<<setw(2)<<s.DajSate()<<":"<<setw(2)<<s.DajMinute()<<":"<<setw(2)<<s.DajSekunde()<<endl;
	}
};

int main ()
{
	Sat s1(18,19,39);
	s1-=100;
	cout<<s1<<endl;
	s1+=1200;
	cout<<s1<<endl;
	Sat s2(1,1,5);
	cout<<s1+10<<endl;
	cout<<s1-10<<endl;
	s1+=-100;
	cout<<s1<<endl;
	s1-=-100;
	cout<<s1<<endl;
	cout<<s1.DajSate()<<s1.DajMinute()<<s1.DajSekunde()<<endl;
	cout<<s1-s2<<endl;
	cout<<s1<<endl;
	cout<<s2<<endl;
	s1++;
	cout<<s1<<endl; 
	s2--;
	cout<<s2<<endl; 
	++s1;
	cout<<s1<<endl;   
	--s2;
	cout<<s2<<endl;
	Sat s3=s1+5;
	cout<<s2<<endl;
	Sat s4=s2-5;
	cout<<s4<<endl;
	Sat s5;
	cout<<s5<<endl;
	s5.Postavi(1,1,1);
	cout<<s5<<endl;
	
	return 0;
}