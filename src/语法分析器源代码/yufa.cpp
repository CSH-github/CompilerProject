#include<iostream>
#include<fstream>
using namespace std;
#include "test2.cpp"

int main(){
	ifstream cin("token.txt");
	init();//��ʼ��
	//ofstream cout("result.txt");

	int type;
	string val;
	bool isFit=false;
	string dealStr="";
	bool findfh=false;
	int token_index;
	string out_str="";
	string last_str="";
	while(cin>>token_index>>type>>val){
		last_str=val;
		findfh=false;
		isFit=false;
		out_str+=val+" ";
		//cout<<val<<endl;
		//�Էֺ�Ϊ��λ����
		if(type==0){//����
			cout<<"token.txt�е�"<<token_index<<"�д��ڴ���"<<endl;
			isFit=false;
			break;
		}else{//�Ǵ���
			if(val==";"){
				findfh=true;
				isFit=Yufa(dealStr);
				if(!isFit){
					cout<<"����Ĵ�����"<<out_str<<endl;
					break;
				}
				out_str="";
				dealStr="";//���
			}else{
				bool find=false;
				if(type==1){//�ؼ���
					if(val=="int"||val=="float"||val=="double"){//a��ʾ��������
						dealStr+='a';
						find=true;
					}
					if(val=="if"||val=="while"){//g��ʾ if��while
						dealStr+='g';
						find=true;
					}
				}
				
				if(type==2){//��ʶ��
					dealStr+='b';
					find=true;
				}
		
	
				if(type==3){//����
					dealStr+='e';
					find=true;
				}

				if(type==4){//�������
					if(val=="+"||val=="-"||val=="*"||val=="/"||val=="%"){//d��ʾ�����
						dealStr+='d';
						find=true;
					}
					if(val=="<"||val==">"||val=="<="||val==">="){//f��ʾ��ϵ�����
						dealStr+='f';
						find=true;
					}
				}
				
				if(val=="="||val=="("||val==")"){
					dealStr+=val;
					find=true;
				}

				if(!find){
					cout<<"�����﷨��֧�� token ����"<<val<<endl;
					isFit=false;
					break;
				}
			}
		}//�Ǵ���
	}//while
	
	if(isFit)
		cout<<"�����﷨��"<<endl;
	
	if(last_str!=";") 
		cout<<"��βȱ�ٷֺţ�"<<endl;

	system("pause");

	return 0;
}
