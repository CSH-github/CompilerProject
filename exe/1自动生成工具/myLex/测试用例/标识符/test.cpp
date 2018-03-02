#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//º¯ÊýÉùÃ÷
bool S1();
bool S2();

string str;	//´ý¼ì²â×Ö·û´®
int index=0;	//´ý¼ì²â×Ö·ûÎ»ÖÃ

bool S1(){	//ÆðÊ¼Ì¬
	if(index>=str.length())//³¬³ö½çÏÞ
		return false;
	if(str[index]>='a'&&str[index]<='z'){	//ÊäÈë×Ö·ûÎª'l'
		index++;
		return S2();
	}
	return false;
}

bool S2(){	//ÖÕÌ¬
	if(index>=str.length())//³¬³ö½çÏÞ
		return true;
	if(str[index]>='a'&&str[index]<='z'){	//ÊäÈë×Ö·ûÎª'l'
		index++;
		return S2();
	}
	if(str[index]>='0'&&str[index]<='9'){	//ÊäÈë×Ö·ûÎª'd'
		index++;
		return S2();
	}
	return false;
}

int main(){
	ifstream cin("in.txt");
	while(cin>>str){
		index=0;
		if(S1())
			cout<<"¡Ì "<<str<<endl;
		else
			cout<<"¡Á "<<str<<endl;
	}
	return 0;
}
