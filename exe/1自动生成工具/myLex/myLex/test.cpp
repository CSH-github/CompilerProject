#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//��������
bool S1(string str,int index);
bool S2(string str,int index);


bool S1(string str,int index){	//��ʼ̬
	if(index>=str.length())//��������
		return false;
	if(str[index]=='l'){	//�����ַ�Ϊ'l'
		index++;
		return S2(str,index);
	}
	return false;
}

bool S2(string str,int index){	//��̬
	if(index>=str.length())//��������
		return true;
	if(str[index]=='l'){	//�����ַ�Ϊ'l'
		index++;
		return S2(str,index);
	}
	if(str[index]=='d'){	//�����ַ�Ϊ'd'
		index++;
		return S2(str,index);
	}
	return false;
}

int main(){
	ifstream cin("in.txt");
	string str;	//������ַ���
	int index=0;	//������ַ�λ��
	while(cin>>str){
		index=0;
		if(S1(str,index))
			cout<<"�� "<<str<<endl;
		else
			cout<<"�� "<<str<<endl;
	}
	return 0;
}
