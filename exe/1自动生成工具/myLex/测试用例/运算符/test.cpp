#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//函数声明
bool S1();
bool S2();
bool S3();

string str;	//待检测字符串
int index=0;	//待检测字符位置

bool S1(){	//起始态
	if(index>=str.length())//超出界限
		return false;
	if(str[index]=='+'){	//输入字符为'+'
		index++;
		return S2();
	}
	if(str[index]=='-'){	//输入字符为'-'
		index++;
		return S2();
	}
	if(str[index]=='*'){	//输入字符为'*'
		index++;
		return S2();
	}
	if(str[index]=='/'){	//输入字符为'/'
		index++;
		return S2();
	}
	if(str[index]=='='){	//输入字符为'='
		index++;
		return S2();
	}
	if(str[index]=='<'){	//输入字符为'<'
		index++;
		return S3();
	}
	if(str[index]=='>'){	//输入字符为'>'
		index++;
		return S3();
	}
	return false;
}

bool S2(){	//终态
	if(index>=str.length())//超出界限
		return true;
	return false;
}

bool S3(){	//终态
	if(index>=str.length())//超出界限
		return true;
	if(str[index]=='='){	//输入字符为'='
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
			cout<<"√ "<<str<<endl;
		else
			cout<<"× "<<str<<endl;
	}
	return 0;
}
