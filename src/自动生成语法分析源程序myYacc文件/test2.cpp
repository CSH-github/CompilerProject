#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<vector>
using namespace std;

#define acc 140406

//LR(1)分析表
int Action[100][100];//Action表,0表示出错,正数表示Si,负数表示ri,140406表示结束
int Goto[100][100];//Goto表

//相关变量
vector<string> vstr0;//初始文法 S->AB记为SAB
string X="ZETF"; //存放所有的状态
string endStr="()*+i";//存放所有的终态

//找到非终态符号在Action中的下标，找不到返回-1
int find_endStr(char ch){
	if(ch=='#')
		return endStr.length();
	for(int i=0;i<endStr.length();++i)
	if(ch==endStr[i])
		return i;
	return -1;
}

void init(){//初始化
	//初始化Action表,Goto表
	Action[0][0]=4;
	Action[0][1]=0;
	Action[0][2]=0;
	Action[0][3]=0;
	Action[0][4]=5;
	Action[0][5]=0;
	Action[1][0]=0;
	Action[1][1]=0;
	Action[1][2]=0;
	Action[1][3]=6;
	Action[1][4]=0;
	Action[1][5]=140406;
	Action[2][0]=0;
	Action[2][1]=0;
	Action[2][2]=7;
	Action[2][3]=-2;
	Action[2][4]=0;
	Action[2][5]=-2;
	Action[3][0]=0;
	Action[3][1]=0;
	Action[3][2]=-4;
	Action[3][3]=-4;
	Action[3][4]=0;
	Action[3][5]=-4;
	Action[4][0]=11;
	Action[4][1]=0;
	Action[4][2]=0;
	Action[4][3]=0;
	Action[4][4]=12;
	Action[4][5]=0;
	Action[5][0]=0;
	Action[5][1]=0;
	Action[5][2]=-6;
	Action[5][3]=-6;
	Action[5][4]=0;
	Action[5][5]=-6;
	Action[6][0]=4;
	Action[6][1]=0;
	Action[6][2]=0;
	Action[6][3]=0;
	Action[6][4]=5;
	Action[6][5]=0;
	Action[7][0]=4;
	Action[7][1]=0;
	Action[7][2]=0;
	Action[7][3]=0;
	Action[7][4]=5;
	Action[7][5]=0;
	Action[8][0]=0;
	Action[8][1]=15;
	Action[8][2]=0;
	Action[8][3]=16;
	Action[8][4]=0;
	Action[8][5]=0;
	Action[9][0]=0;
	Action[9][1]=-2;
	Action[9][2]=17;
	Action[9][3]=-2;
	Action[9][4]=0;
	Action[9][5]=0;
	Action[10][0]=0;
	Action[10][1]=-4;
	Action[10][2]=-4;
	Action[10][3]=-4;
	Action[10][4]=0;
	Action[10][5]=0;
	Action[11][0]=11;
	Action[11][1]=0;
	Action[11][2]=0;
	Action[11][3]=0;
	Action[11][4]=12;
	Action[11][5]=0;
	Action[12][0]=0;
	Action[12][1]=-6;
	Action[12][2]=-6;
	Action[12][3]=-6;
	Action[12][4]=0;
	Action[12][5]=0;
	Action[13][0]=0;
	Action[13][1]=0;
	Action[13][2]=7;
	Action[13][3]=-1;
	Action[13][4]=0;
	Action[13][5]=-1;
	Action[14][0]=0;
	Action[14][1]=0;
	Action[14][2]=-3;
	Action[14][3]=-3;
	Action[14][4]=0;
	Action[14][5]=-3;
	Action[15][0]=0;
	Action[15][1]=0;
	Action[15][2]=-5;
	Action[15][3]=-5;
	Action[15][4]=0;
	Action[15][5]=-5;
	Action[16][0]=11;
	Action[16][1]=0;
	Action[16][2]=0;
	Action[16][3]=0;
	Action[16][4]=12;
	Action[16][5]=0;
	Action[17][0]=11;
	Action[17][1]=0;
	Action[17][2]=0;
	Action[17][3]=0;
	Action[17][4]=12;
	Action[17][5]=0;
	Action[18][0]=0;
	Action[18][1]=21;
	Action[18][2]=0;
	Action[18][3]=16;
	Action[18][4]=0;
	Action[18][5]=0;
	Action[19][0]=0;
	Action[19][1]=-1;
	Action[19][2]=17;
	Action[19][3]=-1;
	Action[19][4]=0;
	Action[19][5]=0;
	Action[20][0]=0;
	Action[20][1]=-3;
	Action[20][2]=-3;
	Action[20][3]=-3;
	Action[20][4]=0;
	Action[20][5]=0;
	Action[21][0]=0;
	Action[21][1]=-5;
	Action[21][2]=-5;
	Action[21][3]=-5;
	Action[21][4]=0;
	Action[21][5]=0;
	Action[22][0]=0;
	Action[22][1]=0;
	Action[22][2]=0;
	Action[22][3]=0;
	Action[22][4]=0;
	Action[22][5]=0;
	Goto[0][0]=0;
	Goto[0][1]=1;
	Goto[0][2]=2;
	Goto[0][3]=3;
	Goto[0][4]=0;
	Goto[1][0]=0;
	Goto[1][1]=0;
	Goto[1][2]=0;
	Goto[1][3]=0;
	Goto[1][4]=0;
	Goto[2][0]=0;
	Goto[2][1]=0;
	Goto[2][2]=0;
	Goto[2][3]=0;
	Goto[2][4]=0;
	Goto[3][0]=0;
	Goto[3][1]=0;
	Goto[3][2]=0;
	Goto[3][3]=0;
	Goto[3][4]=0;
	Goto[4][0]=0;
	Goto[4][1]=8;
	Goto[4][2]=9;
	Goto[4][3]=10;
	Goto[4][4]=0;
	Goto[5][0]=0;
	Goto[5][1]=0;
	Goto[5][2]=0;
	Goto[5][3]=0;
	Goto[5][4]=0;
	Goto[6][0]=0;
	Goto[6][1]=0;
	Goto[6][2]=13;
	Goto[6][3]=3;
	Goto[6][4]=0;
	Goto[7][0]=0;
	Goto[7][1]=0;
	Goto[7][2]=0;
	Goto[7][3]=14;
	Goto[7][4]=0;
	Goto[8][0]=0;
	Goto[8][1]=0;
	Goto[8][2]=0;
	Goto[8][3]=0;
	Goto[8][4]=0;
	Goto[9][0]=0;
	Goto[9][1]=0;
	Goto[9][2]=0;
	Goto[9][3]=0;
	Goto[9][4]=0;
	Goto[10][0]=0;
	Goto[10][1]=0;
	Goto[10][2]=0;
	Goto[10][3]=0;
	Goto[10][4]=0;
	Goto[11][0]=0;
	Goto[11][1]=18;
	Goto[11][2]=9;
	Goto[11][3]=10;
	Goto[11][4]=0;
	Goto[12][0]=0;
	Goto[12][1]=0;
	Goto[12][2]=0;
	Goto[12][3]=0;
	Goto[12][4]=0;
	Goto[13][0]=0;
	Goto[13][1]=0;
	Goto[13][2]=0;
	Goto[13][3]=0;
	Goto[13][4]=0;
	Goto[14][0]=0;
	Goto[14][1]=0;
	Goto[14][2]=0;
	Goto[14][3]=0;
	Goto[14][4]=0;
	Goto[15][0]=0;
	Goto[15][1]=0;
	Goto[15][2]=0;
	Goto[15][3]=0;
	Goto[15][4]=0;
	Goto[16][0]=0;
	Goto[16][1]=0;
	Goto[16][2]=19;
	Goto[16][3]=10;
	Goto[16][4]=0;
	Goto[17][0]=0;
	Goto[17][1]=0;
	Goto[17][2]=0;
	Goto[17][3]=20;
	Goto[17][4]=0;
	Goto[18][0]=0;
	Goto[18][1]=0;
	Goto[18][2]=0;
	Goto[18][3]=0;
	Goto[18][4]=0;
	Goto[19][0]=0;
	Goto[19][1]=0;
	Goto[19][2]=0;
	Goto[19][3]=0;
	Goto[19][4]=0;
	Goto[20][0]=0;
	Goto[20][1]=0;
	Goto[20][2]=0;
	Goto[20][3]=0;
	Goto[20][4]=0;
	Goto[21][0]=0;
	Goto[21][1]=0;
	Goto[21][2]=0;
	Goto[21][3]=0;
	Goto[21][4]=0;
	Goto[22][0]=0;
	Goto[22][1]=0;
	Goto[22][2]=0;
	Goto[22][3]=0;
	Goto[22][4]=0;
	vstr0.push_back("ZE");
	vstr0.push_back("EE+T");
	vstr0.push_back("ET");
	vstr0.push_back("TT*F");
	vstr0.push_back("TF");
	vstr0.push_back("F(E)");
	vstr0.push_back("Fi");
}

bool Yufa(string inStr){//进行语法分析
	stack<int> stack_state;//状态栈
	stack<char>  stack_fh;//符号栈
	//初始化
	stack_state.push(0);
	stack_fh.push('#');
	inStr+='#';
	for(int index=0;index<inStr.length();++index){
		char ch=inStr[index];
		int state_index=stack_state.top();//栈顶状态
		if(ch>='A'&&ch<='Z'){//非终态
			int goto_index=X.find(ch);
			if(goto_index<0||Goto[state_index][goto_index]==0){//错误状态
				cout<<"error at "<<index<<endl;
				return false;
			}else{//非错误状态
				stack_fh.push(ch);//字符进栈
				stack_state.push(Goto[state_index][goto_index]);//状态进栈
			}
		}else{//终态
			int action_index=find_endStr(ch);
			if(action_index<0||Action[state_index][action_index]==0){//错误状态
				cout<<"error at "<<index<<endl;
				return false;
			}else if(Action[state_index][action_index]==acc){//接受状态
				cout<<"Yes"<<endl;
				return true;
			}else if(Action[state_index][action_index]>0){//Si
				stack_fh.push(ch);//字符进栈
				stack_state.push(Action[state_index][action_index]);//状态进栈
			}else{//ri
				string t_str=vstr0[-Action[state_index][action_index]];//找到产生式
				int k=t_str.length()-1;
				if(t_str[1]=='$')
					k=0;//s-A.
				for(int k0=0;k0<k;++k0){
					stack_fh.pop();//字符弹栈
					stack_state.pop();//状态弹栈
				}
				state_index=stack_state.top();	
				int goto_index=X.find(t_str[0]);
				if(goto_index<0||Goto[state_index][goto_index]==0){//错误状态
					cout<<"eror3 at "<<index<<endl;
					return false;
				}else{//非错误状态
					stack_fh.push(t_str[0]);//字符进栈
					stack_state.push(Goto[state_index][goto_index]);//状态进栈
				}
				index--;
			}
		}
	}
}
int main(){
	ifstream cin("in.txt");
	string str;	//待检测字符串
	init();//初始化	
	while(cin>>str){
		cout<<str<<" ";
		Yufa(str);
	}
	return 0;
}
