#include<iostream>
#include<fstream>
using namespace std;
#include "test2.cpp"

int main(){
	ifstream cin("token.txt");
	init();//初始化
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
		//以分号为单位处理串
		if(type==0){//错误串
			cout<<"token.txt中第"<<token_index<<"行存在错误串"<<endl;
			isFit=false;
			break;
		}else{//非错误串
			if(val==";"){
				findfh=true;
				isFit=Yufa(dealStr);
				if(!isFit){
					cout<<"处理的串出错："<<out_str<<endl;
					break;
				}
				out_str="";
				dealStr="";//清空
			}else{
				bool find=false;
				if(type==1){//关键字
					if(val=="int"||val=="float"||val=="double"){//a表示变量类型
						dealStr+='a';
						find=true;
					}
					if(val=="if"||val=="while"){//g表示 if，while
						dealStr+='g';
						find=true;
					}
				}
				
				if(type==2){//标识符
					dealStr+='b';
					find=true;
				}
		
	
				if(type==3){//常数
					dealStr+='e';
					find=true;
				}

				if(type==4){//运算符符
					if(val=="+"||val=="-"||val=="*"||val=="/"||val=="%"){//d表示运算符
						dealStr+='d';
						find=true;
					}
					if(val=="<"||val==">"||val=="<="||val==">="){//f表示关系运算符
						dealStr+='f';
						find=true;
					}
				}
				
				if(val=="="||val=="("||val==")"){
					dealStr+=val;
					find=true;
				}

				if(!find){
					cout<<"精简语法不支持 token 串："<<val<<endl;
					isFit=false;
					break;
				}
			}
		}//非错误串
	}//while
	
	if(isFit)
		cout<<"符合语法！"<<endl;
	
	if(last_str!=";") 
		cout<<"结尾缺少分号！"<<endl;

	system("pause");

	return 0;
}
