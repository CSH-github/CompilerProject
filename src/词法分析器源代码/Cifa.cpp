#include<iostream>
#include<fstream>
#include<string>
using namespace std;

string str;
int index=0;
int token_index=1;
ofstream out("token.txt");

//��ý�����ǣ����ؽ�����λ�ã����ǣ�����-1
int getJieFu(){
	if(index>=str.length())  //ɨ����󷵻�
		return -1;
	if(str[index]==','||str[index]==';'||str[index]=='{'||str[index]=='}')
		return index;
	else
		return -1;
}
//�����������ǣ����ؽ�����λ�ã����ǣ�����-1
int getYunSuanfFu(){
	if(index>=str.length())  //ɨ����󷵻�
		return -1;
	if(str[index]=='+'||str[index]=='-'||str[index]=='*'||str[index]=='/'
		||str[index]=='%'||str[index]=='='||str[index]=='('||str[index]==')')
		return index;
	if(str[index]=='>'||str[index]=='<'){
		if(index+1>=str.length())  //ɨ����󷵻�
			return index;
		else{
			if(str[index+1]=='=') //>=����<=
				return index+1;
			else //>����<
				return index;
		}
	}
	return -1;
}

//�ж��Ƿ��Ǳ�ʶ��2
bool isBiaozhifu2(string str,int index){	//��̬
	if(index>=str.length())//��������
		return true;
	if(str[index]>='a'&&str[index]<='z'){	//�����ַ�Ϊ'l'
		index++;
		return isBiaozhifu2(str,index);
	}
	if(str[index]>='0'&&str[index]<='9'){	//�����ַ�Ϊ'd'
		index++;
		return isBiaozhifu2(str,index);
	}
	return false;
}

//�ж��Ƿ��Ǳ�ʶ��
bool isBiaozhifu(string str,int index){	//��ʼ̬
	if(index>=str.length())//��������
		return false;
	if(str[index]>='a'&&str[index]<='z'){	//�����ַ�Ϊ'l'
		index++;
		return isBiaozhifu2(str,index);
	}
	return false;
}

string gjz_strs[]={//�ؼ��ֱ�
"bool",
"break",
"case",
"catch",
"char",
"class",
"const",
"continue",
"default",
"delete",
"do",
"double",
"else",
"false",
"float",
"for",
"if",
"int",
"long",
"main",
"namespace",
"new",
"private",
"protected",
"public",
"return",
"short",
"sizeof",
"static",
"struct",
"switch",
"this",
"throw",
"true",
"try",
"void",
"while",
"mdw"};
//�ж��Ƿ��ǹؼ���
bool isGuanJiZi(string dealStr){
	for(int i=0;;i++){
		if(gjz_strs[i]=="mdw") //������
			return false;
		if(gjz_strs[i]==dealStr)//�鵽��
			return true;
	}
}


//�Ƿ��ǳ�����������
bool S1(string str,int index);
bool S2(string str,int index);
bool S3(string str,int index);
bool S4(string str,int index);
bool S5(string str,int index);
bool S6(string str,int index);
bool S7(string str,int index);


bool S1(string str,int index){	//��ʼ̬
	if(index>=str.length())//��������
		return false;
	if(str[index]>='0'&&str[index]<='9'){	//�����ַ�Ϊ'd'
		index++;
		return S2(str,index);
	}
	if(str[index]=='.'){	//�����ַ�Ϊ'.'
		index++;
		return S3(str,index);
	}
	if(str[index]=='e'){	//�����ַ�Ϊ'e'
		index++;
		return S4(str,index);
	}
	return false;
}

bool S2(string str,int index){	//��̬
	if(index>=str.length())//��������
		return true;
	if(str[index]>='0'&&str[index]<='9'){	//�����ַ�Ϊ'd'
		index++;
		return S2(str,index);
	}
	if(str[index]=='.'){	//�����ַ�Ϊ'.'
		index++;
		return S3(str,index);
	}
	if(str[index]=='e'){	//�����ַ�Ϊ'e'
		index++;
		return S4(str,index);
	}
	return false;
}

bool S3(string str,int index){
	if(index>=str.length())//��������
		return false;
	if(str[index]>='0'&&str[index]<='9'){	//�����ַ�Ϊ'd'
		index++;
		return S5(str,index);
	}
	return false;
}

bool S4(string str,int index){
	if(index>=str.length())//��������
		return false;
	if(str[index]>='0'&&str[index]<='9'){	//�����ַ�Ϊ'd'
		index++;
		return S6(str,index);
	}
	if(str[index]=='+'||str[index]=='-'){	//�����ַ�Ϊ's'
		index++;
		return S7(str,index);
	}
	return false;
}

bool S5(string str,int index){	//��̬
	if(index>=str.length())//��������
		return true;
	if(str[index]>='0'&&str[index]<='9'){	//�����ַ�Ϊ'd'
		index++;
		return S5(str,index);
	}
	if(str[index]=='e'){	//�����ַ�Ϊ'e'
		index++;
		return S4(str,index);
	}
	return false;
}

bool S6(string str,int index){	//��̬
	if(index>=str.length())//��������
		return true;
	if(str[index]>='0'&&str[index]<='9'){	//�����ַ�Ϊ'd'
		index++;
		return S6(str,index);
	}
	return false;
}

bool S7(string str,int index){
	if(index>=str.length())//��������
		return false;
	if(str[index]>='0'&&str[index]<='9'){	//�����ַ�Ϊ'd'
		index++;
		return S6(str,index);
	}
	return false;
}

//�Ƿ��ǳ���
bool isChangShu(string dealStr){
	//return false;
	return S1(dealStr,0);
}

void cifa(){
	while(index<str.length()){
		
		bool isDealed=false; //��¼�Ƿ����

		while(str[index]==' '||str[index]==9||str[index]==10||str[index]==14){ //���˿ո�,Tab,���з�
			index++;
			if(index>=str.length())  //ɨ����󷵻�
				return;
		}
	

		if(str[index]=='/'){//ȥ��ע��
			if(index+1<str.length()&&str[index+1]=='*'){//ȥ�� /**/ע��
				index+=2;
				while(true){
					if(index+1>=str.length())  //ɨ����󷵻�
						return;
					if(str[index]=='*'&&str[index+1]=='/') //�������� */
						break;
					index+=1; //ɨ�����������ַ�
				}
				isDealed=true;
				index+=2;
			}else if(index+1<str.length()&&str[index+1]=='/'){//ȥ�� //ע��
				index+=2;
				while(true){
					if(index>=str.length())  //ɨ����󷵻�
						return;
					if(str[index]==10){ //���з�
						//index++; //ȥ��10��14
						break;
					}
					index++; //ɨ������һ���ַ�
				}
				isDealed=true;
				index+=1;
			}
		}
		
		while(str[index]==' '||str[index]==9||str[index]==10||str[index]==14){ //���˿ո�,Tab,���з�
			index++;
			if(index>=str.length())  //ɨ����󷵻�
				return;
		}
		
		int srt_index=0;
		//�Ƿ��ǽ��
		int index1=getJieFu();
		if(index1!=-1){//�ҵ����
			string tmp="";
			for(srt_index=index;srt_index<=index1;++srt_index)
				tmp+=str[srt_index];
			cout<<"(���,"<<tmp<<")"<<endl;
			out<<token_index++<<" "<<5<<" "<<tmp<<endl;
			isDealed=true;
			index=index1+1;
			
		}


		//�Ƿ��������
		index1=getYunSuanfFu();
		if(index1!=-1){//�ҵ������
			string tmp="";
			for(srt_index=index;srt_index<=index1;++srt_index)
				tmp+=str[srt_index];
			if(!(index1+1<str.length()&&(tmp=="/"&&str[index+1]=='/'))){//�������//
				cout<<"(�����,"<<tmp<<")"<<endl;
				out<<token_index++<<" "<<4<<" "<<tmp<<endl;
				index=index1+1;
			}
			isDealed=true;
		}

		if(index>=str.length())  //ɨ����󷵻�
			return;

		if(str[index]>='a'&&str[index]<='z'){//�Ƿ��Ǳ�ʶ�����ؼ���
			string dealStr="";//Ҫ������ַ���
			dealStr+=str[index];//���������Ĵ�
			index++;
			while(index<str.length()){
				if(str[index]==' '||str[index]==9||str[index]==10||str[index]==14||
				getJieFu()!=-1||getYunSuanfFu()!=-1)
					break;//�����ָ���
				else {
					dealStr+=str[index];//���������Ĵ�
					index++;	
				}
			}
			if(isBiaozhifu(dealStr,0)){ //�Ƿ��Ǳ�ʶ��
				if(isGuanJiZi(dealStr)){ //��ѯ�ؼ��ֱ��ж��Ƿ��ǹؼ���
					cout<<"(�ؼ���,"<<dealStr<<")"<<endl;
					out<<token_index++<<" "<<1<<" "<<dealStr<<endl;
				}else{
					cout<<"(��ʶ��,"<<dealStr<<")"<<endl;
					out<<token_index++<<" "<<2<<" "<<dealStr<<endl;
				}
			}else{
				cout<<"�Ƿ���ʶ����"<<dealStr<<endl;
				out<<token_index++<<" "<<0<<" "<<dealStr<<endl;
			}
		}else if((str[index]>='0'&&str[index]<='9')||str[index]=='.'||str[index]=='e'){ //�Ƿ����޷��ų���
			string dealStr="";//Ҫ������ַ���
			dealStr+=str[index];//���������Ĵ�
			index++;
			while(index<str.length()){
				if(str[index]==' '||str[index]==9||str[index]==10||str[index]==14||
					getJieFu()!=-1||getYunSuanfFu()!=-1){
					if((str[index]=='+'||str[index]=='-')&&
						str[index-1]=='e'&&str[index-2]>='0'&&str[index-2]<='9'){//3.14e+5��ֹ+�������Ӽ�
							dealStr+=str[index];//���������Ĵ�
							index++;	
					}else
						break;//�����ָ���
				}else {
					dealStr+=str[index];//���������Ĵ�
					index++;	
				}
			}
			if(isChangShu(dealStr)){ //�Ƿ��ǳ���
				cout<<"(����,"<<dealStr<<")"<<endl;
				out<<token_index++<<" "<<3<<" "<<dealStr<<endl;
			}else{
				cout<<"�Ƿ�������"<<dealStr<<endl;
				out<<token_index++<<" "<<0<<" "<<dealStr<<endl;
			}
		
		}else{//����δ����
			if(!isDealed){
				cout<<"�Ƿ��ַ���"<<str[index]<<endl;
				out<<token_index++<<" "<<0<<" "<<str[index]<<endl;
				index++;
			}
		}
	
	}//whileѭ��
}

int main(){
	ifstream cin("in.txt");
	string tmp;
	while(getline(cin,tmp)){
		str+=tmp+'\n';
	}
	cifa();	 
	system("pause");
	return 0;
}


