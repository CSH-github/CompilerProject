/*
��С��֮��Ϊ:
    d   .   e   s   
 1  2   3   4       
 2  2   3   4       
 3  5               
 4  6           7   
 5  5       4       
 6  6               
 7  6               
��ʼ״̬��:1
����״̬Ϊ:2 5 6 
*/
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//��������
bool S1();
bool S2();
bool S3();
bool S4();
bool S5();
bool S6();
bool S7();

string str;
int index=0;

bool S1(){ //��ʼ̬
	if(index>=str.length())//��������
		return false;
	if(str[index]>='0'&&str[index]<='9'){//d
		index++;
		return S2();
	}
	if(str[index]=='.'){
		index++;
		return S3();
	}
	if(str[index]=='e'){
		index++;
		return S4();
	}
	return false;
}

bool S2(){ //��̬
	if(index>=str.length())//��������
		return true;
	if(str[index]>='0'&&str[index]<='9'){
		index++;
		return S2();
	}
	if(str[index]=='.'){
		index++;
		return S3();
	}
	if(str[index]=='e'){
		index++;
		return S4();
	}
	return false;
}

bool S3(){
	if(index>=str.length())//��������
		return false;
	if(str[index]>='0'&&str[index]<='9'){//d
		index++;
		return S5();
	}
	return false;
}

bool S4(){
	if(index>=str.length())//��������
		return false;
	if(str[index]>='0'&&str[index]<='9'){//d
		index++;
		return S6();
	}
	if(str[index]=='+'||str[index]=='-'){
		index++;
		return S7();
	}
	return false;
}

bool S5(){ //��̬
	if(index>=str.length())//��������
		return true;
	if(str[index]>='0'&&str[index]<='9'){//d
		index++;
		return S5();
	}else if(str[index]=='e'){
		index++;
		return S4();
	}else{
		return false;
	}
}

bool S6(){ //��̬
	if(index>=str.length())//��������
		return true;
	if(str[index]>='0'&&str[index]<='9'){//d
		index++;
		return S6();
	}
	return false;
}

bool S7(){
	if(index>=str.length())//��������
		return false;
	if(str[index]>='0'&&str[index]<='9'){//d
		index++;
		return S6();
	}
	return false;
}

int main(){
	ifstream cin("in.txt");
	while(cin>>str){
		index=0;
		if(S1()){
			cout<<"�� "<<str<<endl;
		}else
			cout<<"�� "<<str<<endl;
	}
	return 0;
}