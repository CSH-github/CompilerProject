#include<iostream>
#include<fstream>
#include<string>
using namespace std;

string str;
int index=0;
int token_index=1;
ofstream out("token.txt");

//获得界符，是：返回结束的位置，不是：返回-1
int getJieFu(){
	if(index>=str.length())  //扫描完后返回
		return -1;
	if(str[index]==','||str[index]==';'||str[index]=='{'||str[index]=='}')
		return index;
	else
		return -1;
}
//获得运算符，是：返回结束的位置，不是：返回-1
int getYunSuanfFu(){
	if(index>=str.length())  //扫描完后返回
		return -1;
	if(str[index]=='+'||str[index]=='-'||str[index]=='*'||str[index]=='/'
		||str[index]=='%'||str[index]=='='||str[index]=='('||str[index]==')')
		return index;
	if(str[index]=='>'||str[index]=='<'){
		if(index+1>=str.length())  //扫描完后返回
			return index;
		else{
			if(str[index+1]=='=') //>=或者<=
				return index+1;
			else //>或者<
				return index;
		}
	}
	return -1;
}

//判断是否是标识符2
bool isBiaozhifu2(string str,int index){	//终态
	if(index>=str.length())//超出界限
		return true;
	if(str[index]>='a'&&str[index]<='z'){	//输入字符为'l'
		index++;
		return isBiaozhifu2(str,index);
	}
	if(str[index]>='0'&&str[index]<='9'){	//输入字符为'd'
		index++;
		return isBiaozhifu2(str,index);
	}
	return false;
}

//判断是否是标识符
bool isBiaozhifu(string str,int index){	//起始态
	if(index>=str.length())//超出界限
		return false;
	if(str[index]>='a'&&str[index]<='z'){	//输入字符为'l'
		index++;
		return isBiaozhifu2(str,index);
	}
	return false;
}

string gjz_strs[]={//关键字表
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
//判断是否是关键字
bool isGuanJiZi(string dealStr){
	for(int i=0;;i++){
		if(gjz_strs[i]=="mdw") //查完了
			return false;
		if(gjz_strs[i]==dealStr)//查到了
			return true;
	}
}


//是否是常数函数声明
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
	if(str[index]=='+'||str[index]=='-'){	//输入字符为's'
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

//是否是常数
bool isChangShu(string dealStr){
	//return false;
	return S1(dealStr,0);
}

void cifa(){
	while(index<str.length()){
		
		bool isDealed=false; //记录是否处理过

		while(str[index]==' '||str[index]==9||str[index]==10||str[index]==14){ //过滤空格,Tab,换行符
			index++;
			if(index>=str.length())  //扫描完后返回
				return;
		}
	

		if(str[index]=='/'){//去掉注释
			if(index+1<str.length()&&str[index+1]=='*'){//去掉 /**/注释
				index+=2;
				while(true){
					if(index+1>=str.length())  //扫描完后返回
						return;
					if(str[index]=='*'&&str[index+1]=='/') //结束符号 */
						break;
					index+=1; //扫描下面两个字符
				}
				isDealed=true;
				index+=2;
			}else if(index+1<str.length()&&str[index+1]=='/'){//去掉 //注释
				index+=2;
				while(true){
					if(index>=str.length())  //扫描完后返回
						return;
					if(str[index]==10){ //换行符
						//index++; //去掉10和14
						break;
					}
					index++; //扫描下面一个字符
				}
				isDealed=true;
				index+=1;
			}
		}
		
		while(str[index]==' '||str[index]==9||str[index]==10||str[index]==14){ //过滤空格,Tab,换行符
			index++;
			if(index>=str.length())  //扫描完后返回
				return;
		}
		
		int srt_index=0;
		//是否是界符
		int index1=getJieFu();
		if(index1!=-1){//找到界符
			string tmp="";
			for(srt_index=index;srt_index<=index1;++srt_index)
				tmp+=str[srt_index];
			cout<<"(界符,"<<tmp<<")"<<endl;
			out<<token_index++<<" "<<5<<" "<<tmp<<endl;
			isDealed=true;
			index=index1+1;
			
		}


		//是否是运算符
		index1=getYunSuanfFu();
		if(index1!=-1){//找到运算符
			string tmp="";
			for(srt_index=index;srt_index<=index1;++srt_index)
				tmp+=str[srt_index];
			if(!(index1+1<str.length()&&(tmp=="/"&&str[index+1]=='/'))){//如果不是//
				cout<<"(运算符,"<<tmp<<")"<<endl;
				out<<token_index++<<" "<<4<<" "<<tmp<<endl;
				index=index1+1;
			}
			isDealed=true;
		}

		if(index>=str.length())  //扫描完后返回
			return;

		if(str[index]>='a'&&str[index]<='z'){//是否是标识符、关键字
			string dealStr="";//要处理的字符串
			dealStr+=str[index];//加入待处理的串
			index++;
			while(index<str.length()){
				if(str[index]==' '||str[index]==9||str[index]==10||str[index]==14||
				getJieFu()!=-1||getYunSuanfFu()!=-1)
					break;//遇到分隔符
				else {
					dealStr+=str[index];//加入待处理的串
					index++;	
				}
			}
			if(isBiaozhifu(dealStr,0)){ //是否是标识符
				if(isGuanJiZi(dealStr)){ //查询关键字表，判断是否是关键字
					cout<<"(关键字,"<<dealStr<<")"<<endl;
					out<<token_index++<<" "<<1<<" "<<dealStr<<endl;
				}else{
					cout<<"(标识符,"<<dealStr<<")"<<endl;
					out<<token_index++<<" "<<2<<" "<<dealStr<<endl;
				}
			}else{
				cout<<"非法标识符："<<dealStr<<endl;
				out<<token_index++<<" "<<0<<" "<<dealStr<<endl;
			}
		}else if((str[index]>='0'&&str[index]<='9')||str[index]=='.'||str[index]=='e'){ //是否是无符号常数
			string dealStr="";//要处理的字符串
			dealStr+=str[index];//加入待处理的串
			index++;
			while(index<str.length()){
				if(str[index]==' '||str[index]==9||str[index]==10||str[index]==14||
					getJieFu()!=-1||getYunSuanfFu()!=-1){
					if((str[index]=='+'||str[index]=='-')&&
						str[index-1]=='e'&&str[index-2]>='0'&&str[index-2]<='9'){//3.14e+5防止+被当做加减
							dealStr+=str[index];//加入待处理的串
							index++;	
					}else
						break;//遇到分隔符
				}else {
					dealStr+=str[index];//加入待处理的串
					index++;	
				}
			}
			if(isChangShu(dealStr)){ //是否是常数
				cout<<"(常数,"<<dealStr<<")"<<endl;
				out<<token_index++<<" "<<3<<" "<<dealStr<<endl;
			}else{
				cout<<"非法常数："<<dealStr<<endl;
				out<<token_index++<<" "<<0<<" "<<dealStr<<endl;
			}
		
		}else{//其他未定义
			if(!isDealed){
				cout<<"非法字符："<<str[index]<<endl;
				out<<token_index++<<" "<<0<<" "<<str[index]<<endl;
				index++;
			}
		}
	
	}//while循环
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


