#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<stack>
using namespace std;
#define MaxStatue 26  //״̬��Ŀ���26
vector<string> vstr0;//��ʼ�ķ� S->AB��ΪSAB
vector<string> vstr1;//��żӵ����Ŀ S.AB SA.B SAB.

string X=""; //������е�״̬
string endStr="";//������е���̬
int CK[MaxStatue];//�ܷ����ɿգ�0δ֪��-1���ܣ�1��

bool isLR1=true;

//������Ƴ�$���ս��,����vstr0�еı��ʽ������ַ�������ǲ�����
void FindKong(){
	int i;
	//��¼��������ߵĸ���
	int gs[MaxStatue];
	memset(gs,0,sizeof(gs));

	//���Ȼ��״̬��ͨ�������ַ���
	for(i=0;i<vstr0.size();++i){
		string tmp=vstr0[i];
		for(int j=0;j<tmp.size();++j){
			if(tmp[j]>='A'&&tmp[j]<='Z'){//�Ƿ���̬
				bool find=false;//�Ƿ��Ѿ�������
				for(int k=0;k<X.size();++k){
					if(X[k]==tmp[j]){
						find=true;
						if(j==0)//������ͷ
							gs[k]++;//����ʽ����һ��
						break;
					}
				}
				//û�ҵ��Ļ��ͼӽ�ȥ		
				if(!find){
					if(j==0)//������ͷ
						gs[X.size()]++;
					X+=tmp[j];
				}
			}else{//����̬
				if(tmp[j]!='$'){//��Ϊ��
					bool find=false;//�Ƿ��Ѿ�������
					for(int k=0;k<endStr.size();++k){
						if(endStr[k]==tmp[j]){
							find=true;
							break;
						}
					}
					//û�ҵ��Ļ��ͼӽ�ȥ		
					if(!find)
						endStr+=tmp[j];
				}
			}
		}
	}
	sort(endStr.begin(),endStr.end());
	//��ʼ�������յļ���
	memset(CK,0,sizeof(CK));  //δ֪

	
	//ɾ������ʽ�ұ����к����ս���Ĳ���ʽ����ʹ��
	//ĳһ�ս������ʽ����ɾ��������Ϊ��
	//��ĳһ����ʽ���Ҳ�Ϊ�գ�$��,����Ϊ�ǣ�ɾ������ʽ
	vector<string> v_str;
	for(i=0;i<vstr0.size();++i){
		if(vstr0[i][1]>='A'&&vstr0[i][1]<='Z'){//���ս���ͱ���
			v_str.push_back(vstr0[i]);
		}else if(vstr0[i][1]=='$'){//Ϊ��
			for(int j=0;j<X.size();++j){//ɾ��
				if(X[j]==vstr0[i][0]){
					CK[j]=1;//�ܲ�����
					break;
				}
			}
		}else{//Ϊ�ս��
			for(int j=0;j<X.size();++j){//ɾ��
				if(X[j]==vstr0[i][0]){
					gs[j]--;//ɾȥ�˲���ʽ���������鲢��һ
					if(gs[j]==0)
						CK[j]=-1;//���ܲ�����
				}
			}
		}
	}
	
	//ɾ���ܲ����յĲ���ʽ
	vector<string> v_str1;
	for(i=0;i<v_str.size();++i){
		bool needDelet=false;
		for(int j=0;j<X.size();++j){
			if(v_str[i][0]==X[j]&&CK[j]==1){
				gs[j]--;
				needDelet=true;
				break;
			}
		}
		if(!needDelet)//���δȷ���ͼ���
			v_str1.push_back(v_str[i]);
	}
	v_str.clear();//�ͷ���Դ

	//ɨ�裬ֱ��û���ٱ�Ϊֹ
	while(true){
		bool ischange=false;//Ĭ��û��
		vector<string> v_str2;
		for(i=0;i<v_str1.size();++i)
			v_str2.push_back(v_str1[i]);
		v_str1.clear(); //�����v_str2��

		for(i=0;i<v_str2.size();++i){//����ÿ�����ʽ

			if(!(v_str2[i][1]>='A'&&v_str2[i][1]<='Z')){//������ս��
				for(int j=0;j<X.size();++j){//ɾ��
					if(X[j]==v_str2[i][0]){
						gs[j]--;//ɾȥ�˲���ʽ���������鲢��һ
						if(gs[j]==0)
							CK[j]=-1;//���ܲ�����
					}
				}
				ischange=true;
				continue;//��һ��
			}

			for(int k=0;k<X.size();++k){//�ҷ��ս��

				if(X[k]==v_str2[i][1]){//�ҵ�����ʽ�Ҳ��ַ���

					if(CK[k]==1){//���Բ�����
						ischange=true;
						if(v_str2[i].length()==2){//�޸ı�־��ɾ��
							for(int k0=0;k0<X.size();++k0){
								if(X[k0]==v_str2[i][0]){
									CK[k0]=1;
									break;
								}
							}
						}else{
							string tmp="";
							for(int j=0;j<v_str2[i].length();++j){
								if(j==1)
									continue;
								else
									tmp+=v_str2[i][j];
							}
							v_str1.push_back(tmp);//��ɾ��
						}
					}else if(CK[k]==-1){//���ܲ�����
						ischange=true;
						for(int k0=0;k0<X.size();++k0){
							if(X[k0]==v_str2[i][0]){
								gs[k0]--;
								if(gs[k0]==0)
									CK[k0]=-1;
								break;
							}
						}
					}else{//δ֪
						v_str1.push_back(v_str2[i]);
					}

				}//�ҵ�����ʽ�Ҳ��ַ���

			}//X����

		}//����ÿ�����ʽ
		
		if(!ischange) //û�иı�
			break;
	}//while
}

//�ַ�������ʱʹ�õĺ���
bool cmp(const char ch1,const char ch2){
	return ch1<ch2;	
}

string First_set[MaxStatue];//��¼ÿ��״̬�ļ���
int First_finish[MaxStatue];//ÿ��״̬�Ƿ�ȷ��
int Postion[MaxStatue]; //����Ӧ����̬��ĸ�����ҵ���Ӧλ��
//����ÿ���ַ�����FIRST��
string First(int index){
	string tmp="";
	int i;
	bool cKong=false;//�ܲ�����
	for(i=0;i<vstr0.size();++i){//�������ʽ
		if(X[index]==vstr0[i][0]){//�ҵ���Ӧ�ı��ʽ
			bool canKong=true;//�ܲ�����
			for(int j=1;j<vstr0[i].length();++j){//�������ʽ��ÿһ���ַ�
				if(!canKong) //���ܲ����վ��˳�
					break;
				if(vstr0[i][j]=='$'){ //���ɿ�
					tmp+='$';	
				}else if(!(vstr0[i][j]>='A'&&vstr0[i][j]<='Z')){//�ս��
					canKong=false;
					tmp+=vstr0[i][j];
				}else{
					int index2=Postion[vstr0[i][j]-'A'];
					if(CK[index2]!=1)//���ܲ�����
						canKong=false;
					if(First_finish[index2]==1)//�Ѿ����
						tmp+=First_set[index2];
					else
						if(index2!=index) //�����ݹ�
							tmp+=First(index2);//�ݹ����
				}
			}//�������ʽ��ÿһ���ַ�
			if(canKong)
				cKong=true;
		}//�ҵ���Ӧ�ı��ʽ
	}//�������ʽ

	//ȥ���ظ�����ĸ������������ɿյĻ��Ͳ�����
	string tmp2="";
	for(i=0;i<tmp.length();++i){
		if(tmp[i]=='$')
			continue;
		bool isExit=false;
		for(int j=0;j<tmp2.length();++j){
			if(tmp[i]==tmp2[j]){
				isExit=true;
				break;
			}
		}
		if(!isExit)
			tmp2+=tmp[i];
	}
	sort(tmp2.begin(),tmp2.begin()+tmp2.length(),cmp);
	if(cKong)
		tmp2+='$';

	First_set[index]=tmp2;
	First_finish[index]=1;//�ü������
	return tmp2;
}

//��ʼ��ÿ���ַ�����FIRST��
void First_init(){
	memset(First_finish,0,sizeof(First_finish));//��ʼ����ûȷ��
	int i;
	for(i=0;i<X.length();++i)//����Ӧ����̬��ĸ�����ҵ���Ӧλ��
		Postion[X[i]-'A']=i;

	for(i=0;i<X.length();++i)
		if(First_finish[i]!=1)//δ��ʼ���ͽ��г�ʼ��
			First(i);
}

//����ָ���ַ�����FIRST��,�㷨��P80����ڲ���str,����string,$��ʾ��
string FIRST_str(string str){
	bool canKong=true;//�ܲ�����
	int i;
	string tmp="";
	for(i=0;i<str.length();++i){//�������ʽ��ÿһ���ַ�
		if(!canKong) //���ܲ����վ��˳�
			break;
		if(str[i]=='$'){ //���ɿ�
			tmp+='$';	
		}else if(!(str[i]>='A'&&str[i]<='Z')){//�ս��
			canKong=false;
			tmp+=str[i];
		}else{//
			int index2=Postion[str[i]-'A'];
			if(CK[index2]!=1)//���ܲ�����
				canKong=false;
			tmp+=First_set[index2];
		}
	}//�������ʽ��ÿһ���ַ�

	//ȥ���ظ�����ĸ������������ɿյĻ��Ͳ�����
	string tmp2="";
	for(i=0;i<tmp.length();++i){
		if(tmp[i]=='$')
			continue;
		bool isExit=false;
		for(int j=0;j<tmp2.length();++j){
			if(tmp[i]==tmp2[j]){
				isExit=true;
				break;
			}
		}
		if(!isExit)
			tmp2+=tmp[i];
	}
	sort(tmp2.begin(),tmp2.begin()+tmp2.length(),cmp);
	if(canKong)
		tmp2+='$';
	return tmp2;
}

//CLOSURE(I)���������ݽṹ     ��p144
struct Node{  //��Ŀ�ڵ�
	vector<string> vState;//״̬
};
vector<Node> vNode; //������е���Ŀ


//����Ŀ���Ͻ�����չ���ҵ�A->.B��B->.c...
vector<string> vtmp;//��ŵݹ��ҵ���ĿԪ��
int added[200];//��¼��Ӧ����ʽ�Ƿ�����
void findNext(char ch){
	for(int i=0;i<vstr1.size();++i){
		if(vstr1[i][0]==ch&&vstr1[i][1]=='.'){//�ҵ�����ʽ
			if(vstr1[i].length()==2){//s->.
				vtmp.push_back(vstr1[i]);
			}else if(vstr1[i][2]>='A'&&vstr1[i][2]<='Z'){//���ս��
				if(added[i]==0){
					vtmp.push_back(vstr1[i]);
					added[i]=1;
					findNext(vstr1[i][2]);//�ݹ麯��
				}
			}else //�ս��
				vtmp.push_back(vstr1[i]);
		}
	}
}

//�ַ����ȽϺ���
bool cmp2(const string s1,const string s2){
	return s1<s2;
}
//CLOSURE(I)����
void CLOSURE(Node& node){
	int i;
	for(i=0;i<node.vState.size();++i){
		string tmp=node.vState[i];
		int j=tmp.find('.'); //�ҵ����λ��
		if(tmp[j+1]>='A'&&tmp[j+1]<='Z'){//���ս��
			vtmp.clear();//���
			memset(added,0,sizeof(added));//��ʼ����û��ʹ�ù�
			findNext(tmp[j+1]); //�ݹ������չ
			//������ĿA->aBp,a ����CLOSURE(I)��B->r �ǲ���ʽ��b ����FIRST(pa),��B->.r,b
			int j2=tmp.find(',');
			string str_p="";
			int i0;
			for(i0=j+2;i0<j2;++i0)
				str_p+=tmp[i0];
			string str_pa=str_p+tmp[j2+1];
			string str_first_pa=FIRST_str(str_pa);//����First(pa)
			
			for(int k=0;k<vtmp.size();++k){ //����ڵ��У���ʱ��S.AB����ʽ
				if(vtmp[k][0]!=tmp[j+1])
					continue;
				for( int k1=0;k1<str_first_pa.size();++k1){
					string addstr=vtmp[k]+','+str_first_pa[k1];
					bool find=false;
					for(int j=0;j<node.vState.size();++j){
						if(addstr==node.vState[j]){
							find=true;
							break;
						}
					}
					if(!find){
						node.vState.push_back(addstr);
					}
				}
			}
		}
	}
	sort(node.vState.begin(),node.vState.end(),cmp2); //���ַ�˳������
}

//GO(I,x)
void Go(Node& sNode,char ch,Node& eNode){//��ʼ״̬���ַ������״̬
	int i;
	for(i=0;i<sNode.vState.size();++i){//����������ÿ��״̬Ԫ�� S.aAb
		string tmp=sNode.vState[i];
		int index=tmp.find('.');
		if(tmp[index+1]==ch){//��Ҫ����ַ�
			//����
			tmp[index]=ch;
			tmp[index+1]='.';
			//����
			eNode.vState.push_back(tmp);
		}
	}
}

//�жϼ����Ƿ����
int isExit(Node& eNode){
	string str0="";
	int i;
	for(i=0;i<eNode.vState.size();++i)//������ת�����ַ���
		str0+=eNode.vState[i];

	for(i=0;i<vNode.size();++i){//��ÿ�����ϱȽ�
		if(vNode[i].vState.size()!=eNode.vState.size())  //������ͬ�����ϲ�ͬ
			continue; 
		string tmp="";
		for(int j=0;j<vNode[i].vState.size();++j)
			tmp+=vNode[i].vState[j];
		if(tmp==str0)
			return i;
	}
	return -1;
}

//����LR(1)������
#define acc 140406
int Action[100][100];//Action��,0��ʾ����,������ʾSi,������ʾri,140406��ʾ����
int Goto[100][100];//Goto��

//�ҵ�����̬������Action�е��±꣬�Ҳ�������-1
int find_endStr(char ch){
	if(ch=='#')
		return endStr.length();
	for(int i=0;i<endStr.length();++i)
		if(ch==endStr[i])
			return i;
	return -1;
}

int setIndex=0;
//����ʶ��ǰ׺��DFA
void CreateDFA(){
	//��ʼ��
	Node node;
	string str=vstr1[0]+",#";
	node.vState.push_back(str);
	CLOSURE(node);//����Ŀ���ıհ�

	vNode.push_back(node); //�������

	int i;
	cout<<"I0: "<<endl;
	for(i=0;i<node.vState.size();++i)
		cout<<node.vState[i]<<endl;
	cout<<endl;

	//int i;
	for(i=0;i<vNode.size();++i){//����ÿ������
		int j;
		int nowIndex=vNode.size();

		//�������̬A,B,C,D...
		for(j=0;j<X.length();++j){
			Node eNode;
			Go(vNode[i],X[j],eNode);	//�任
			if(eNode.vState.size()>0){
				CLOSURE(eNode);//��չ
				int int_exit=isExit(eNode);
				if(int_exit==-1){//�жϼ����Ƿ����
					vNode.push_back(eNode);
					++setIndex;
					cout<<"I"<<i<<"-> "<<X[j]<<" ->I"<<setIndex<<endl;
					cout<<"I"<<setIndex<<": "<<endl;
					for(int i1=0;i1<eNode.vState.size();++i1)
						cout<<eNode.vState[i1]<<endl;
					cout<<endl;

					if(	Goto[i][j]!=0&&Goto[i][j]!=setIndex){
						cout<<"����Goto��λ�����г�ͻ"<<endl;
						isLR1=false;
						return;
					}
					Goto[i][j]=setIndex;//��ӵ�Goto��,GO(Ik,A)=Ij,��Goto[k,A]=j
				}else{//�Ѿ�����
					if(	Goto[i][j]!=0&&Goto[i][j]!=int_exit){
						cout<<"����Goto��λ�����г�ͻ"<<endl;
						isLR1=false;
						return;
					}
					Goto[i][j]=int_exit;//��ӵ�Goto��,GO(Ik,A)=Ij,��Goto[k,A]=j
				
				}//�жϼ����Ƿ����
			}
		}

		//������̬��a,b,c...
		for(j=0;j<endStr.length();++j){
			Node eNode;
			Go(vNode[i],endStr[j],eNode); //�任
			if(eNode.vState.size()>0){
				CLOSURE(eNode);//��չ
				int int_exit=isExit(eNode);
				if(int_exit==-1){//�жϼ����Ƿ����
					vNode.push_back(eNode);
					++setIndex;
					cout<<"I"<<i<<"-> "<<endStr[j]<<" ->I"<<setIndex<<endl;
					cout<<"I"<<setIndex<<": "<<endl;
					for(int i1=0;i1<eNode.vState.size();++i1)
						cout<<eNode.vState[i1]<<endl;
					cout<<endl;
					
					if(	Action[i][j]!=0&&Action[i][j]!=setIndex){
						cout<<"����Action��λ�����г�ͻ"<<endl;
						isLR1=false;
						return;
					}
					Action[i][j]=setIndex;//��ӵ�Action��,GO(Ik,a)=Ij,��Action[k,a]=Sj
				}else{
					if(	Action[i][j]!=0&&Action[i][j]!=int_exit){
						cout<<"����Action��λ�����г�ͻ"<<endl;
						isLR1=false;
						return;
					}
					Action[i][j]=int_exit;//��ӵ�Action��,GO(Ik,a)=Ij,��Action[k,a]=Sj
				}//�жϼ����Ƿ����
			}

		}
	
		
		//����Լ
		for(int k=0;k<vNode[i].vState.size();++k){//��[A->x.,a]����Ik��������Action[k,a]=rj
			string ss=vNode[i].vState[k];
			if(ss[ss.length()-3]=='.'){
				int ss_index=find_endStr(ss[ss.length()-1]);
				if(ss_index==-1){
					cout<<"��������δʶ����ս��"<<endl;
					isLR1=false;
					return;
				}else{
					//�ҵ���Լ�ı��ʽ
					string find_str="";
					int k1=0;
					for(k1=0;k1<ss.length()-3;++k1)
						find_str+=ss[k1];
					if(find_str.length()==1)
						find_str+='$';
					for(k1=0;k1<vstr0.size();++k1)
						if(find_str==vstr0[k1])
							break;
				    
					if(	Action[i][ss_index]!=0&&Action[i][j]!=-k1){
						cout<<"����Action��λ�����г�ͻ"<<endl;
						isLR1=false;
						return;
					}

					Action[i][ss_index]=-k1;
					
					if(ss[ss.length()-1]=='#'&&ss[0]=='Z')
						Action[i][endStr.length()]=acc;
				}
			}
		}//��[A->x.,a]����Ik��������Action[k,a]=rj
	}
}



int main(){
	ifstream cin("g.txt");
	//�����ع��ķ�
	string str0;
	while(cin>>str0){
		vstr0.push_back(str0);
	}
	
	//���ԭ�㣬������Ŀ
	int i;
	for(i=0;i<vstr0.size();++i){
		if(vstr0[i].length()==2&&vstr0[i][1]=='$'){//s->$
			vstr0[i][1]='.';
			vstr1.push_back(vstr0[i]);
			vstr0[i][1]='$';
			continue;
		}
		string tmp="."+vstr0[i];
		for(int j=0;j<vstr0[i].size();++j){//�����٣�������ٴΣ���λ��1��ʼ����ͷΪ����ʽ��
			char t_ch=tmp[j];
			tmp[j]=tmp[j+1];
			tmp[j+1]=t_ch;
			vstr1.push_back(tmp);
		}
	}
	
	//���
	cout<<"0�Բ���ʽ���Ϊ��"<<endl;
	for(i=0;i<vstr0.size();++i){
		cout<<i<<": "<<vstr0[i]<<endl;
	}
	cout<<endl;

	//����ܲ����յķǷ��ս��
	FindKong();

	cout<<"1����ܲ����յķǷ��ս����"<<endl;
	for(i=0;i<X.size();++i)
		cout<<X[i]<<" ";
	cout<<endl;
	for(i=0;i<X.size();++i){
		if(CK[i]==-1)
			cout<<0<<" ";
		else
			cout<<CK[i]<<" ";
	}
	cout<<endl;
	cout<<endl;
	
	//����ÿ���ַ�����FIRST��
	cout<<"2����ÿ���ַ�����FIRST����"<<endl;
	First_init();
	for(i=0;i<X.length();++i)
		cout<<X[i]<<": "<<First_set[i]<<endl;
	cout<<endl;

	//��ձ�
	memset(Action,0,sizeof(Action));
	memset(Goto,0,sizeof(Goto));

	//���ɴ��ǰ׺��DFA
	cout<<"3���ɴ��ǰ׺��DFA:"<<endl;
	CreateDFA();

	//����Ƿ���LR1�ķ�
	if(!isLR1){
		cout<<"���ķ�����LR1�ķ���"<<endl;
		system("pause");
		return 0;
	}
	cout<<endl;

	//����LR(1)������
	cout<<"4����LR(1)������:"<<endl;
	int gs=4;
	
	for(i=0;i<endStr.length();++i)
		cout<<setw(gs-1)<<endStr[i]<<" ";
	cout<<setw(gs-1)<<"#"<<" ";
	for(i=0;i<X.length();++i)
		cout<<setw(gs)<<X[i]<<" ";
	cout<<endl;

	for(i=0;i<vNode.size();++i){
		int j;
		for(j=0;j<=endStr.length();++j){
			if(Action[i][j]>0){
				if(Action[i][j]==acc)
					cout<<setw(gs-2)<<"acc"<<" ";
				else
					cout<<setw(gs-2-(Action[i][j]/10))<<"S"<<Action[i][j]<<" ";
			}else if(Action[i][j]<0)
				cout<<setw(gs-2-(-Action[i][j])/10)<<"r"<<-Action[i][j]<<" ";
			else
				cout<<setw(gs)<<"0 ";
		}
		
		for(j=0;j<X.length();++j)
				cout<<setw(gs)<<Goto[i][j]<<" ";
		cout<<endl;
	}

	//���Cpp�ļ�
	/*�������*/
	ofstream cout("test2.cpp");

	cout<<"#include<iostream>"<<endl;
	cout<<"#include<fstream>"<<endl;
	cout<<"#include<string>"<<endl;
	cout<<"#include<stack>"<<endl;
	cout<<"#include<vector>"<<endl;
	cout<<"using namespace std;"<<endl;
	cout<<endl;
	cout<<"#define acc 140406"<<endl;
	cout<<endl;
	cout<<"//LR(1)������"<<endl;
	cout<<"int Action[100][100];//Action��,0��ʾ����,������ʾSi,������ʾri,140406��ʾ����"<<endl;
    cout<<"int Goto[100][100];//Goto��"<<endl;
	cout<<endl;
	cout<<"//��ر���"<<endl;
	cout<<"vector<string> vstr0;//��ʼ�ķ� S->AB��ΪSAB"<<endl;
	cout<<"string X=\""<<X<<"\"; //������е�״̬"<<endl;
	cout<<"string endStr=\""<<endStr<<"\";//������е���̬"<<endl;
	cout<<endl;
	//�������
	cout<<"//�ҵ�����̬������Action�е��±꣬�Ҳ�������-1"<<endl;
	cout<<"int find_endStr(char ch){"<<endl;
	cout<<"	if(ch=='#')"<<endl;
	cout<<"		return endStr.length();"<<endl;
	cout<<"	for(int i=0;i<endStr.length();++i)"<<endl;
	cout<<"	if(ch==endStr[i])"<<endl;
	cout<<"		return i;"<<endl;
	cout<<"	return -1;"<<endl;
	cout<<"}"<<endl;
	cout<<endl;
	//�������
	cout<<"void init(){//��ʼ��"<<endl;
	cout<<"	//��ʼ��Action��,Goto��"<<endl;
	for(i=0;i<=vNode.size();++i){;
		int j;
		for(j=0;j<=endStr.length();++j)
			cout<<"	Action["<<i<<"]["<<j<<"]="<<Action[i][j]<<";"<<endl;
	}
	for(i=0;i<=vNode.size();++i){;
		int j;
		for(j=0;j<=X.length();++j)
			cout<<"	Goto["<<i<<"]["<<j<<"]="<<Goto[i][j]<<";"<<endl;
	}

	//��ʼ��vstr0
	for(i=0;i<vstr0.size();++i){
		cout<<"	vstr0.push_back(\""<<vstr0[i]<<"\");"<<endl;
	}
	cout<<"}"<<endl;
	cout<<endl;
	//�������
	cout<<"bool Yufa(string inStr){//�����﷨����"<<endl;	
	cout<<"	stack<int> stack_state;//״̬ջ"<<endl;
	cout<<"	stack<char>  stack_fh;//����ջ"<<endl;
	cout<<"	//��ʼ��"<<endl;
	cout<<"	stack_state.push(0);"<<endl;
	cout<<"	stack_fh.push('#');"<<endl;
	cout<<"	inStr+='#';"<<endl;
	cout<<"	for(int index=0;index<inStr.length();++index){"<<endl;
	cout<<"		char ch=inStr[index];"<<endl;
	cout<<"		int state_index=stack_state.top();//ջ��״̬"<<endl;
	cout<<"		if(ch>='A'&&ch<='Z'){//����̬"<<endl;
	cout<<"			int goto_index=X.find(ch);"<<endl;
	cout<<"			if(goto_index<0||Goto[state_index][goto_index]==0){//����״̬"<<endl;
	cout<<"				cout<<\"error at \"<<index<<endl;"<<endl;
	cout<<"				return false;"<<endl;
	cout<<"			}else{//�Ǵ���״̬"<<endl;
	cout<<"				stack_fh.push(ch);//�ַ���ջ"<<endl;
	cout<<"				stack_state.push(Goto[state_index][goto_index]);//״̬��ջ"<<endl;
	cout<<"			}"<<endl;
	cout<<"		}else{//��̬"<<endl;
	cout<<"			int action_index=find_endStr(ch);"<<endl;
	cout<<"			if(action_index<0||Action[state_index][action_index]==0){//����״̬"<<endl;
	cout<<"				cout<<\"error at \"<<index<<endl;"<<endl;
	cout<<"				return false;"<<endl;
	cout<<"			}else if(Action[state_index][action_index]==acc){//����״̬"<<endl;
	cout<<"				cout<<\"Yes\"<<endl;"<<endl;
	cout<<"				return true;"<<endl;
	cout<<"			}else if(Action[state_index][action_index]>0){//Si"<<endl;
	cout<<"				stack_fh.push(ch);//�ַ���ջ"<<endl;
	cout<<"				stack_state.push(Action[state_index][action_index]);//״̬��ջ"<<endl;
	cout<<"			}else{//ri"<<endl;
	cout<<"				string t_str=vstr0[-Action[state_index][action_index]];//�ҵ�����ʽ"<<endl;
	cout<<"				int k=t_str.length()-1;"<<endl;
	cout<<"				if(t_str[1]=='$')"<<endl;
	cout<<"					k=0;//s-A."<<endl;
	cout<<"				for(int k0=0;k0<k;++k0){"<<endl;
	cout<<"					stack_fh.pop();//�ַ���ջ"<<endl;
	cout<<"					stack_state.pop();//״̬��ջ"<<endl;
	cout<<"				}"<<endl;
	cout<<"				state_index=stack_state.top();	"<<endl;
	cout<<"				int goto_index=X.find(t_str[0]);"<<endl;
	cout<<"				if(goto_index<0||Goto[state_index][goto_index]==0){//����״̬"<<endl;
	cout<<"					cout<<\"eror3 at \"<<index<<endl;"<<endl;
	cout<<"					return false;"<<endl;
	cout<<"				}else{//�Ǵ���״̬"<<endl;
	cout<<"					stack_fh.push(t_str[0]);//�ַ���ջ"<<endl;
	cout<<"					stack_state.push(Goto[state_index][goto_index]);//״̬��ջ"<<endl;
	cout<<"				}"<<endl;
	cout<<"				index--;"<<endl;
	cout<<"			}"<<endl;
	cout<<"		}"<<endl;
	cout<<"	}"<<endl;
	cout<<"}"<<endl;

	//���������
	cout<<"int main(){"<<endl;
	cout<<"	ifstream cin(\"in.txt\");"<<endl;
	cout<<"	string str;	//������ַ���"<<endl;
	cout<<"	init();//��ʼ��	"<<endl;
	cout<<"	while(cin>>str){"<<endl;
	cout<<"		cout<<str<<\" \";"<<endl;
	cout<<"		Yufa(str);"<<endl;
	cout<<"	}"<<endl;
	cout<<"	return 0;"<<endl;
	cout<<"}"<<endl;
	
	system("pause");

	return 0;
}