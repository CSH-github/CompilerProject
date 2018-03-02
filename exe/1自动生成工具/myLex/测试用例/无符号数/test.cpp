#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//函数声明
bool S1(string str,int index);
bool S2(string str,int index);
bool S3(string str,int index);
bool S4(string str,int index);
bool S5(string str,int index);
bool S6(string str,int index);
bool S7(string str,int index);


bool S1(string str,int index){	//起始态
	if(index>=str.length())//超出界限
		return false;
	if(str[index]>='0'&&str[index]<='9'){	//输入字符为'd'
		index++;
		return S2(str,index);
	}
	if(str[index]=='.'){	//输入字符为'.'
		index++;
		return S3(str,index);
	}
	if(str[index]=='e'){	//输入字符为'e'
		index++;
		return S4(str,index);
	}
	return false;
}

bool S2(string str,int index){	//终态
	if(index>=str.length())//超出界限
		return true;
	if(str[index]>='0'&&str[index]<='9'){	//输入字符为'd'
		index++;
		return S2(str,index);
	}
	if(str[index]=='.'){	//输入字符为'.'
		index++;
		return S3(str,index);
	}
	if(str[index]=='e'){	//输入字符为'e'
		index++;
		return S4(str,index);
	}
	return false;
}

bool S3(string str,int index){
	if(index>=str.length())//超出界限
		return false;
	if(str[index]>='0'&&str[index]<='9'){	//输入字符为'd'
		index++;
		return S5(str,index);
	}
	return false;
}

bool S4(string str,int index){
	if(index>=str.length())//超出界限
		return false;
	if(str[index]>='0'&&str[index]<='9'){	//输入字符为'd'
		index++;
		return S6(str,index);
	}
	if(str[index]=='+'||str[index]=='+'){	//输入字符为's'
		index++;
		return S7(str,index);
	}
	return false;
}

bool S5(string str,int index){	//终态
	if(index>=str.length())//超出界限
		return true;
	if(str[index]>='0'&&str[index]<='9'){	//输入字符为'd'
		index++;
		return S5(str,index);
	}
	if(str[index]=='e'){	//输入字符为'e'
		index++;
		return S4(str,index);
	}
	return false;
}

bool S6(string str,int index){	//终态
	if(index>=str.length())//超出界限
		return true;
	if(str[index]>='0'&&str[index]<='9'){	//输入字符为'd'
		index++;
		return S6(str,index);
	}
	return false;
}

bool S7(string str,int index){
	if(index>=str.length())//超出界限
		return false;
	if(str[index]>='0'&&str[index]<='9'){	//输入字符为'd'
		index++;
		return S6(str,index);
	}
	return false;
}

int main(){
	ifstream cin("in.txt");
	string str;	//待检测字符串
	int index=0;	//待检测字符位置
	while(cin>>str){
		index=0;
		if(S1(str,index))
			cout<<"√ "<<str<<endl;
		else
			cout<<"× "<<str<<endl;
	}
	return 0;
}
