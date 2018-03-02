#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//º¯ÊýÉùÃ÷
bool S1(string str,int index);
bool S2(string str,int index);


bool S1(string str,int index){	//ÆðÊ¼Ì¬
	if(index>=str.length())//³¬³ö½çÏÞ
		return false;
	if(str[index]=='l'){	//ÊäÈë×Ö·ûÎª'l'
		index++;
		return S2(str,index);
	}
	return false;
}

bool S2(string str,int index){	//ÖÕÌ¬
	if(index>=str.length())//³¬³ö½çÏÞ
		return true;
	if(str[index]=='l'){	//ÊäÈë×Ö·ûÎª'l'
		index++;
		return S2(str,index);
	}
	if(str[index]=='d'){	//ÊäÈë×Ö·ûÎª'd'
		index++;
		return S2(str,index);
	}
	return false;
}

int main(){
	ifstream cin("in.txt");
	string str;	//´ý¼ì²â×Ö·û´®
	int index=0;	//´ý¼ì²â×Ö·ûÎ»ÖÃ
	while(cin>>str){
		index=0;
		if(S1(str,index))
			cout<<"¡Ì "<<str<<endl;
		else
			cout<<"¡Á "<<str<<endl;
	}
	return 0;
}
