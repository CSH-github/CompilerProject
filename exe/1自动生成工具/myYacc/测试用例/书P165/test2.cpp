#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<vector>
using namespace std;

#define acc 140406

//LR(1)������
int Action[100][100];//Action��,0��ʾ����,������ʾSi,������ʾri,140406��ʾ����
int Goto[100][100];//Goto��

//��ر���
vector<string> vstr0;//��ʼ�ķ� S->AB��ΪSAB
string X="ZA"; //������е�״̬
string endStr="abd";//������е���̬

//�ҵ�����̬������Action�е��±꣬�Ҳ�������-1
int find_endStr(char ch){
	if(ch=='#')
		return endStr.length();
	for(int i=0;i<endStr.length();++i)
	if(ch==endStr[i])
		return i;
	return -1;
}

void init(){//��ʼ��
	//��ʼ��Action��,Goto��
	Action[0][0]=2;
	Action[0][1]=0;
	Action[0][2]=0;
	Action[0][3]=-3;
	Action[1][0]=0;
	Action[1][1]=0;
	Action[1][2]=0;
	Action[1][3]=140406;
	Action[2][0]=4;
	Action[2][1]=-3;
	Action[2][2]=-3;
	Action[2][3]=0;
	Action[3][0]=0;
	Action[3][1]=5;
	Action[3][2]=6;
	Action[3][3]=0;
	Action[4][0]=4;
	Action[4][1]=-3;
	Action[4][2]=-3;
	Action[4][3]=0;
	Action[5][0]=0;
	Action[5][1]=0;
	Action[5][2]=0;
	Action[5][3]=-2;
	Action[6][0]=0;
	Action[6][1]=0;
	Action[6][2]=0;
	Action[6][3]=-1;
	Action[7][0]=0;
	Action[7][1]=8;
	Action[7][2]=9;
	Action[7][3]=0;
	Action[8][0]=0;
	Action[8][1]=-2;
	Action[8][2]=-2;
	Action[8][3]=0;
	Action[9][0]=0;
	Action[9][1]=-1;
	Action[9][2]=-1;
	Action[9][3]=0;
	Action[10][0]=0;
	Action[10][1]=0;
	Action[10][2]=0;
	Action[10][3]=0;
	Goto[0][0]=0;
	Goto[0][1]=1;
	Goto[0][2]=0;
	Goto[1][0]=0;
	Goto[1][1]=0;
	Goto[1][2]=0;
	Goto[2][0]=0;
	Goto[2][1]=3;
	Goto[2][2]=0;
	Goto[3][0]=0;
	Goto[3][1]=0;
	Goto[3][2]=0;
	Goto[4][0]=0;
	Goto[4][1]=7;
	Goto[4][2]=0;
	Goto[5][0]=0;
	Goto[5][1]=0;
	Goto[5][2]=0;
	Goto[6][0]=0;
	Goto[6][1]=0;
	Goto[6][2]=0;
	Goto[7][0]=0;
	Goto[7][1]=0;
	Goto[7][2]=0;
	Goto[8][0]=0;
	Goto[8][1]=0;
	Goto[8][2]=0;
	Goto[9][0]=0;
	Goto[9][1]=0;
	Goto[9][2]=0;
	Goto[10][0]=0;
	Goto[10][1]=0;
	Goto[10][2]=0;
	vstr0.push_back("ZA");
	vstr0.push_back("AaAd");
	vstr0.push_back("AaAb");
	vstr0.push_back("A$");
}

bool Yufa(string inStr){//�����﷨����
	stack<int> stack_state;//״̬ջ
	stack<char>  stack_fh;//����ջ
	//��ʼ��
	stack_state.push(0);
	stack_fh.push('#');
	inStr+='#';
	for(int index=0;index<inStr.length();++index){
		char ch=inStr[index];
		int state_index=stack_state.top();//ջ��״̬
		if(ch>='A'&&ch<='Z'){//����̬
			int goto_index=X.find(ch);
			if(goto_index<0||Goto[state_index][goto_index]==0){//����״̬
				cout<<"error at "<<index<<endl;
				return false;
			}else{//�Ǵ���״̬
				stack_fh.push(ch);//�ַ���ջ
				stack_state.push(Goto[state_index][goto_index]);//״̬��ջ
			}
		}else{//��̬
			int action_index=find_endStr(ch);
			if(action_index<0||Action[state_index][action_index]==0){//����״̬
				cout<<"error at "<<index<<endl;
				return false;
			}else if(Action[state_index][action_index]==acc){//����״̬
				cout<<"Yes"<<endl;
				return true;
			}else if(Action[state_index][action_index]>0){//Si
				stack_fh.push(ch);//�ַ���ջ
				stack_state.push(Action[state_index][action_index]);//״̬��ջ
			}else{//ri
				string t_str=vstr0[-Action[state_index][action_index]];//�ҵ�����ʽ
				int k=t_str.length()-1;
				if(t_str[1]=='$')
					k=0;//s-A.
				for(int k0=0;k0<k;++k0){
					stack_fh.pop();//�ַ���ջ
					stack_state.pop();//״̬��ջ
				}
				state_index=stack_state.top();	
				int goto_index=X.find(t_str[0]);
				if(goto_index<0||Goto[state_index][goto_index]==0){//����״̬
					cout<<"eror3 at "<<index<<endl;
					return false;
				}else{//�Ǵ���״̬
					stack_fh.push(t_str[0]);//�ַ���ջ
					stack_state.push(Goto[state_index][goto_index]);//״̬��ջ
				}
				index--;
			}
		}
	}
}
int main(){
	ifstream cin("in.txt");
	string str;	//������ַ���
	init();//��ʼ��	
	while(cin>>str){
		cout<<str<<" ";
		Yufa(str);
	}
	return 0;
}
