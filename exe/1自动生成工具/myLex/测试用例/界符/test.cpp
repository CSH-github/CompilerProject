#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//��������
bool S1();
bool S2();

string str;	//������ַ���
int index=0;	//������ַ�λ��

bool S1(){	//��ʼ̬
	if(index>=str.length())//��������
		return false;
	if(str[index]==','){	//�����ַ�Ϊ','
		index++;
		return S2();
	}
	if(str[index]==';'){	//�����ַ�Ϊ';'
		index++;
		return S2();
	}
	if(str[index]=='('){	//�����ַ�Ϊ'('
		index++;
		return S2();
	}
	if(str[index]==')'){	//�����ַ�Ϊ')'
		index++;
		return S2();
	}
	if(str[index]=='{'){	//�����ַ�Ϊ'{'
		index++;
		return S2();
	}
	if(str[index]=='}'){	//�����ַ�Ϊ'}'
		index++;
		return S2();
	}
	return false;
}

bool S2(){	//��̬
	if(index>=str.length())//��������
		return true;
	return false;
}

int main(){
	ifstream cin("in.txt");
	while(cin>>str){
		index=0;
		if(S1())
			cout<<"�� "<<str<<endl;
		else
			cout<<"�� "<<str<<endl;
	}
	return 0;
}
