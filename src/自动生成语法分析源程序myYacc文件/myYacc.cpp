#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<stack>
using namespace std;
#define MaxStatue 26  //状态数目最多26
vector<string> vstr0;//初始文法 S->AB记为SAB
vector<string> vstr1;//存放加点的项目 S.AB SA.B SAB.

string X=""; //存放所有的状态
string endStr="";//存放所有的终态
int CK[MaxStatue];//能否生成空，0未知，-1不能，1能

bool isLR1=true;

//求出能推出$的终结符,输入vstr0中的表达式，输出字符串表和是产生空
void FindKong(){
	int i;
	//记录产生试左边的个数
	int gs[MaxStatue];
	memset(gs,0,sizeof(gs));

	//首先获得状态，通过解析字符串
	for(i=0;i<vstr0.size();++i){
		string tmp=vstr0[i];
		for(int j=0;j<tmp.size();++j){
			if(tmp[j]>='A'&&tmp[j]<='Z'){//是非终态
				bool find=false;//是否已经存在了
				for(int k=0;k<X.size();++k){
					if(X[k]==tmp[j]){
						find=true;
						if(j==0)//以它开头
							gs[k]++;//产生式增加一个
						break;
					}
				}
				//没找到的话就加进去		
				if(!find){
					if(j==0)//以它开头
						gs[X.size()]++;
					X+=tmp[j];
				}
			}else{//是终态
				if(tmp[j]!='$'){//不为空
					bool find=false;//是否已经存在了
					for(int k=0;k<endStr.size();++k){
						if(endStr[k]==tmp[j]){
							find=true;
							break;
						}
					}
					//没找到的话就加进去		
					if(!find)
						endStr+=tmp[j];
				}
			}
		}
	}
	sort(endStr.begin(),endStr.end());
	//初始化产生空的集合
	memset(CK,0,sizeof(CK));  //未知

	
	//删除产生式右边所有含有终结符的产生式，若使得
	//某一终结符产生式都被删除，则标记为否
	//若某一产生式的右部为空（$）,则标记为是，删除产生式
	vector<string> v_str;
	for(i=0;i<vstr0.size();++i){
		if(vstr0[i][1]>='A'&&vstr0[i][1]<='Z'){//非终结符就保留
			v_str.push_back(vstr0[i]);
		}else if(vstr0[i][1]=='$'){//为空
			for(int j=0;j<X.size();++j){//删除
				if(X[j]==vstr0[i][0]){
					CK[j]=1;//能产生空
					break;
				}
			}
		}else{//为终结符
			for(int j=0;j<X.size();++j){//删除
				if(X[j]==vstr0[i][0]){
					gs[j]--;//删去此产生式，个数数组并减一
					if(gs[j]==0)
						CK[j]=-1;//不能产生空
				}
			}
		}
	}
	
	//删除能产生空的产生式
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
		if(!needDelet)//如果未确定就加入
			v_str1.push_back(v_str[i]);
	}
	v_str.clear();//释放资源

	//扫描，直到没有再变为止
	while(true){
		bool ischange=false;//默认没变
		vector<string> v_str2;
		for(i=0;i<v_str1.size();++i)
			v_str2.push_back(v_str1[i]);
		v_str1.clear(); //存放在v_str2中

		for(i=0;i<v_str2.size();++i){//遍历每个表达式

			if(!(v_str2[i][1]>='A'&&v_str2[i][1]<='Z')){//如果是终结符
				for(int j=0;j<X.size();++j){//删除
					if(X[j]==v_str2[i][0]){
						gs[j]--;//删去此产生式，个数数组并减一
						if(gs[j]==0)
							CK[j]=-1;//不能产生空
					}
				}
				ischange=true;
				continue;//下一个
			}

			for(int k=0;k<X.size();++k){//找非终结符

				if(X[k]==v_str2[i][1]){//找到产生式右部字符串

					if(CK[k]==1){//可以产生空
						ischange=true;
						if(v_str2[i].length()==2){//修改标志并删除
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
							v_str1.push_back(tmp);//不删除
						}
					}else if(CK[k]==-1){//不能产生空
						ischange=true;
						for(int k0=0;k0<X.size();++k0){
							if(X[k0]==v_str2[i][0]){
								gs[k0]--;
								if(gs[k0]==0)
									CK[k0]=-1;
								break;
							}
						}
					}else{//未知
						v_str1.push_back(v_str2[i]);
					}

				}//找到产生式右部字符串

			}//X遍历

		}//遍历每个表达式
		
		if(!ischange) //没有改变
			break;
	}//while
}

//字符串排序时使用的函数
bool cmp(const char ch1,const char ch2){
	return ch1<ch2;	
}

string First_set[MaxStatue];//记录每个状态的集合
int First_finish[MaxStatue];//每个状态是否确认
int Postion[MaxStatue]; //将对应非终态字母快速找到对应位置
//计算每个字符集的FIRST集
string First(int index){
	string tmp="";
	int i;
	bool cKong=false;//能产生空
	for(i=0;i<vstr0.size();++i){//遍历表达式
		if(X[index]==vstr0[i][0]){//找到对应的表达式
			bool canKong=true;//能产生空
			for(int j=1;j<vstr0[i].length();++j){//遍历表达式的每一个字符
				if(!canKong) //不能产生空就退出
					break;
				if(vstr0[i][j]=='$'){ //生成空
					tmp+='$';	
				}else if(!(vstr0[i][j]>='A'&&vstr0[i][j]<='Z')){//终结符
					canKong=false;
					tmp+=vstr0[i][j];
				}else{
					int index2=Postion[vstr0[i][j]-'A'];
					if(CK[index2]!=1)//不能产生空
						canKong=false;
					if(First_finish[index2]==1)//已经求出
						tmp+=First_set[index2];
					else
						if(index2!=index) //自身不递归
							tmp+=First(index2);//递归求解
				}
			}//遍历表达式的每一个字符
			if(canKong)
				cKong=true;
		}//找到对应的表达式
	}//遍历表达式

	//去掉重复的字母，如果不能生成空的话就不生成
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
	First_finish[index]=1;//该集合完成
	return tmp2;
}

//初始化每个字符集的FIRST集
void First_init(){
	memset(First_finish,0,sizeof(First_finish));//初始化都没确认
	int i;
	for(i=0;i<X.length();++i)//将对应非终态字母快速找到对应位置
		Postion[X[i]-'A']=i;

	for(i=0;i<X.length();++i)
		if(First_finish[i]!=1)//未初始化就进行初始化
			First(i);
}

//计算指定字符串的FIRST集,算法书P80，入口参数str,返回string,$表示空
string FIRST_str(string str){
	bool canKong=true;//能产生空
	int i;
	string tmp="";
	for(i=0;i<str.length();++i){//遍历表达式的每一个字符
		if(!canKong) //不能产生空就退出
			break;
		if(str[i]=='$'){ //生成空
			tmp+='$';	
		}else if(!(str[i]>='A'&&str[i]<='Z')){//终结符
			canKong=false;
			tmp+=str[i];
		}else{//
			int index2=Postion[str[i]-'A'];
			if(CK[index2]!=1)//不能产生空
				canKong=false;
			tmp+=First_set[index2];
		}
	}//遍历表达式的每一个字符

	//去掉重复的字母，如果不能生成空的话就不生成
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

//CLOSURE(I)函数的数据结构     书p144
struct Node{  //项目节点
	vector<string> vState;//状态
};
vector<Node> vNode; //存放所有的项目


//对项目集合进行扩展，找到A->.B，B->.c...
vector<string> vtmp;//存放递归找的项目元素
int added[200];//记录对应产生式是否加入过
void findNext(char ch){
	for(int i=0;i<vstr1.size();++i){
		if(vstr1[i][0]==ch&&vstr1[i][1]=='.'){//找到产生式
			if(vstr1[i].length()==2){//s->.
				vtmp.push_back(vstr1[i]);
			}else if(vstr1[i][2]>='A'&&vstr1[i][2]<='Z'){//非终结符
				if(added[i]==0){
					vtmp.push_back(vstr1[i]);
					added[i]=1;
					findNext(vstr1[i][2]);//递归函数
				}
			}else //终结符
				vtmp.push_back(vstr1[i]);
		}
	}
}

//字符串比较函数
bool cmp2(const string s1,const string s2){
	return s1<s2;
}
//CLOSURE(I)函数
void CLOSURE(Node& node){
	int i;
	for(i=0;i<node.vState.size();++i){
		string tmp=node.vState[i];
		int j=tmp.find('.'); //找到点的位置
		if(tmp[j+1]>='A'&&tmp[j+1]<='Z'){//非终结符
			vtmp.clear();//清空
			memset(added,0,sizeof(added));//初始化，没有使用过
			findNext(tmp[j+1]); //递归进行扩展
			//若有项目A->aBp,a 属于CLOSURE(I)，B->r 是产生式，b 属于FIRST(pa),则B->.r,b
			int j2=tmp.find(',');
			string str_p="";
			int i0;
			for(i0=j+2;i0<j2;++i0)
				str_p+=tmp[i0];
			string str_pa=str_p+tmp[j2+1];
			string str_first_pa=FIRST_str(str_pa);//计算First(pa)
			
			for(int k=0;k<vtmp.size();++k){ //加入节点中，暂时是S.AB的形式
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
	sort(node.vState.begin(),node.vState.end(),cmp2); //安字符顺序排序
}

//GO(I,x)
void Go(Node& sNode,char ch,Node& eNode){//起始状态，字符，结果状态
	int i;
	for(i=0;i<sNode.vState.size();++i){//遍历集合中每个状态元素 S.aAb
		string tmp=sNode.vState[i];
		int index=tmp.find('.');
		if(tmp[index+1]==ch){//需要这个字符
			//交换
			tmp[index]=ch;
			tmp[index+1]='.';
			//加入
			eNode.vState.push_back(tmp);
		}
	}
}

//判断集合是否存在
int isExit(Node& eNode){
	string str0="";
	int i;
	for(i=0;i<eNode.vState.size();++i)//将集合转换成字符串
		str0+=eNode.vState[i];

	for(i=0;i<vNode.size();++i){//与每个集合比较
		if(vNode[i].vState.size()!=eNode.vState.size())  //个数不同，集合不同
			continue; 
		string tmp="";
		for(int j=0;j<vNode[i].vState.size();++j)
			tmp+=vNode[i].vState[j];
		if(tmp==str0)
			return i;
	}
	return -1;
}

//生成LR(1)分析表
#define acc 140406
int Action[100][100];//Action表,0表示出错,正数表示Si,负数表示ri,140406表示结束
int Goto[100][100];//Goto表

//找到非终态符号在Action中的下标，找不到返回-1
int find_endStr(char ch){
	if(ch=='#')
		return endStr.length();
	for(int i=0;i<endStr.length();++i)
		if(ch==endStr[i])
			return i;
	return -1;
}

int setIndex=0;
//构造识别活动前缀的DFA
void CreateDFA(){
	//初始化
	Node node;
	string str=vstr1[0]+",#";
	node.vState.push_back(str);
	CLOSURE(node);//求项目集的闭包

	vNode.push_back(node); //加入队列

	int i;
	cout<<"I0: "<<endl;
	for(i=0;i<node.vState.size();++i)
		cout<<node.vState[i]<<endl;
	cout<<endl;

	//int i;
	for(i=0;i<vNode.size();++i){//处理每个集合
		int j;
		int nowIndex=vNode.size();

		//处理非终态A,B,C,D...
		for(j=0;j<X.length();++j){
			Node eNode;
			Go(vNode[i],X[j],eNode);	//变换
			if(eNode.vState.size()>0){
				CLOSURE(eNode);//扩展
				int int_exit=isExit(eNode);
				if(int_exit==-1){//判断集合是否存在
					vNode.push_back(eNode);
					++setIndex;
					cout<<"I"<<i<<"-> "<<X[j]<<" ->I"<<setIndex<<endl;
					cout<<"I"<<setIndex<<": "<<endl;
					for(int i1=0;i1<eNode.vState.size();++i1)
						cout<<eNode.vState[i1]<<endl;
					cout<<endl;

					if(	Goto[i][j]!=0&&Goto[i][j]!=setIndex){
						cout<<"出错！Goto表位置上有冲突"<<endl;
						isLR1=false;
						return;
					}
					Goto[i][j]=setIndex;//添加到Goto表,GO(Ik,A)=Ij,则Goto[k,A]=j
				}else{//已经存在
					if(	Goto[i][j]!=0&&Goto[i][j]!=int_exit){
						cout<<"出错！Goto表位置上有冲突"<<endl;
						isLR1=false;
						return;
					}
					Goto[i][j]=int_exit;//添加到Goto表,GO(Ik,A)=Ij,则Goto[k,A]=j
				
				}//判断集合是否存在
			}
		}

		//处理终态，a,b,c...
		for(j=0;j<endStr.length();++j){
			Node eNode;
			Go(vNode[i],endStr[j],eNode); //变换
			if(eNode.vState.size()>0){
				CLOSURE(eNode);//扩展
				int int_exit=isExit(eNode);
				if(int_exit==-1){//判断集合是否存在
					vNode.push_back(eNode);
					++setIndex;
					cout<<"I"<<i<<"-> "<<endStr[j]<<" ->I"<<setIndex<<endl;
					cout<<"I"<<setIndex<<": "<<endl;
					for(int i1=0;i1<eNode.vState.size();++i1)
						cout<<eNode.vState[i1]<<endl;
					cout<<endl;
					
					if(	Action[i][j]!=0&&Action[i][j]!=setIndex){
						cout<<"出错！Action表位置上有冲突"<<endl;
						isLR1=false;
						return;
					}
					Action[i][j]=setIndex;//添加到Action表,GO(Ik,a)=Ij,则Action[k,a]=Sj
				}else{
					if(	Action[i][j]!=0&&Action[i][j]!=int_exit){
						cout<<"出错！Action表位置上有冲突"<<endl;
						isLR1=false;
						return;
					}
					Action[i][j]=int_exit;//添加到Action表,GO(Ik,a)=Ij,则Action[k,a]=Sj
				}//判断集合是否存在
			}

		}
	
		
		//检查规约
		for(int k=0;k<vNode[i].vState.size();++k){//若[A->x.,a]属于Ik，则设置Action[k,a]=rj
			string ss=vNode[i].vState[k];
			if(ss[ss.length()-3]=='.'){
				int ss_index=find_endStr(ss[ss.length()-1]);
				if(ss_index==-1){
					cout<<"出错！出现未识别的终结符"<<endl;
					isLR1=false;
					return;
				}else{
					//找到规约的表达式
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
						cout<<"出错！Action表位置上有冲突"<<endl;
						isLR1=false;
						return;
					}

					Action[i][ss_index]=-k1;
					
					if(ss[ss.length()-1]=='#'&&ss[0]=='Z')
						Action[i][endStr.length()]=acc;
				}
			}
		}//若[A->x.,a]属于Ik，则设置Action[k,a]=rj
	}
}



int main(){
	ifstream cin("g.txt");
	//读入拓广文法
	string str0;
	while(cin>>str0){
		vstr0.push_back(str0);
	}
	
	//添加原点，构成项目
	int i;
	for(i=0;i<vstr0.size();++i){
		if(vstr0[i].length()==2&&vstr0[i][1]=='$'){//s->$
			vstr0[i][1]='.';
			vstr1.push_back(vstr0[i]);
			vstr0[i][1]='$';
			continue;
		}
		string tmp="."+vstr0[i];
		for(int j=0;j<vstr0[i].size();++j){//长多少，插入多少次，从位置1开始，开头为产生式左部
			char t_ch=tmp[j];
			tmp[j]=tmp[j+1];
			tmp[j+1]=t_ch;
			vstr1.push_back(tmp);
		}
	}
	
	//标号
	cout<<"0对产生式标号为："<<endl;
	for(i=0;i<vstr0.size();++i){
		cout<<i<<": "<<vstr0[i]<<endl;
	}
	cout<<endl;

	//求出能产生空的非非终结符
	FindKong();

	cout<<"1求出能产生空的非非终结符："<<endl;
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
	
	//计算每个字符集的FIRST集
	cout<<"2计算每个字符集的FIRST集："<<endl;
	First_init();
	for(i=0;i<X.length();++i)
		cout<<X[i]<<": "<<First_set[i]<<endl;
	cout<<endl;

	//清空表
	memset(Action,0,sizeof(Action));
	memset(Goto,0,sizeof(Goto));

	//生成带活动前缀的DFA
	cout<<"3生成带活动前缀的DFA:"<<endl;
	CreateDFA();

	//检查是否是LR1文法
	if(!isLR1){
		cout<<"该文法不是LR1文法！"<<endl;
		system("pause");
		return 0;
	}
	cout<<endl;

	//生成LR(1)分析表
	cout<<"4生成LR(1)分析表:"<<endl;
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

	//输出Cpp文件
	/*输出代码*/
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
	cout<<"//LR(1)分析表"<<endl;
	cout<<"int Action[100][100];//Action表,0表示出错,正数表示Si,负数表示ri,140406表示结束"<<endl;
    cout<<"int Goto[100][100];//Goto表"<<endl;
	cout<<endl;
	cout<<"//相关变量"<<endl;
	cout<<"vector<string> vstr0;//初始文法 S->AB记为SAB"<<endl;
	cout<<"string X=\""<<X<<"\"; //存放所有的状态"<<endl;
	cout<<"string endStr=\""<<endStr<<"\";//存放所有的终态"<<endl;
	cout<<endl;
	//输出函数
	cout<<"//找到非终态符号在Action中的下标，找不到返回-1"<<endl;
	cout<<"int find_endStr(char ch){"<<endl;
	cout<<"	if(ch=='#')"<<endl;
	cout<<"		return endStr.length();"<<endl;
	cout<<"	for(int i=0;i<endStr.length();++i)"<<endl;
	cout<<"	if(ch==endStr[i])"<<endl;
	cout<<"		return i;"<<endl;
	cout<<"	return -1;"<<endl;
	cout<<"}"<<endl;
	cout<<endl;
	//输出函数
	cout<<"void init(){//初始化"<<endl;
	cout<<"	//初始化Action表,Goto表"<<endl;
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

	//初始化vstr0
	for(i=0;i<vstr0.size();++i){
		cout<<"	vstr0.push_back(\""<<vstr0[i]<<"\");"<<endl;
	}
	cout<<"}"<<endl;
	cout<<endl;
	//输出函数
	cout<<"bool Yufa(string inStr){//进行语法分析"<<endl;	
	cout<<"	stack<int> stack_state;//状态栈"<<endl;
	cout<<"	stack<char>  stack_fh;//符号栈"<<endl;
	cout<<"	//初始化"<<endl;
	cout<<"	stack_state.push(0);"<<endl;
	cout<<"	stack_fh.push('#');"<<endl;
	cout<<"	inStr+='#';"<<endl;
	cout<<"	for(int index=0;index<inStr.length();++index){"<<endl;
	cout<<"		char ch=inStr[index];"<<endl;
	cout<<"		int state_index=stack_state.top();//栈顶状态"<<endl;
	cout<<"		if(ch>='A'&&ch<='Z'){//非终态"<<endl;
	cout<<"			int goto_index=X.find(ch);"<<endl;
	cout<<"			if(goto_index<0||Goto[state_index][goto_index]==0){//错误状态"<<endl;
	cout<<"				cout<<\"error at \"<<index<<endl;"<<endl;
	cout<<"				return false;"<<endl;
	cout<<"			}else{//非错误状态"<<endl;
	cout<<"				stack_fh.push(ch);//字符进栈"<<endl;
	cout<<"				stack_state.push(Goto[state_index][goto_index]);//状态进栈"<<endl;
	cout<<"			}"<<endl;
	cout<<"		}else{//终态"<<endl;
	cout<<"			int action_index=find_endStr(ch);"<<endl;
	cout<<"			if(action_index<0||Action[state_index][action_index]==0){//错误状态"<<endl;
	cout<<"				cout<<\"error at \"<<index<<endl;"<<endl;
	cout<<"				return false;"<<endl;
	cout<<"			}else if(Action[state_index][action_index]==acc){//接受状态"<<endl;
	cout<<"				cout<<\"Yes\"<<endl;"<<endl;
	cout<<"				return true;"<<endl;
	cout<<"			}else if(Action[state_index][action_index]>0){//Si"<<endl;
	cout<<"				stack_fh.push(ch);//字符进栈"<<endl;
	cout<<"				stack_state.push(Action[state_index][action_index]);//状态进栈"<<endl;
	cout<<"			}else{//ri"<<endl;
	cout<<"				string t_str=vstr0[-Action[state_index][action_index]];//找到产生式"<<endl;
	cout<<"				int k=t_str.length()-1;"<<endl;
	cout<<"				if(t_str[1]=='$')"<<endl;
	cout<<"					k=0;//s-A."<<endl;
	cout<<"				for(int k0=0;k0<k;++k0){"<<endl;
	cout<<"					stack_fh.pop();//字符弹栈"<<endl;
	cout<<"					stack_state.pop();//状态弹栈"<<endl;
	cout<<"				}"<<endl;
	cout<<"				state_index=stack_state.top();	"<<endl;
	cout<<"				int goto_index=X.find(t_str[0]);"<<endl;
	cout<<"				if(goto_index<0||Goto[state_index][goto_index]==0){//错误状态"<<endl;
	cout<<"					cout<<\"eror3 at \"<<index<<endl;"<<endl;
	cout<<"					return false;"<<endl;
	cout<<"				}else{//非错误状态"<<endl;
	cout<<"					stack_fh.push(t_str[0]);//字符进栈"<<endl;
	cout<<"					stack_state.push(Goto[state_index][goto_index]);//状态进栈"<<endl;
	cout<<"				}"<<endl;
	cout<<"				index--;"<<endl;
	cout<<"			}"<<endl;
	cout<<"		}"<<endl;
	cout<<"	}"<<endl;
	cout<<"}"<<endl;

	//输出主函数
	cout<<"int main(){"<<endl;
	cout<<"	ifstream cin(\"in.txt\");"<<endl;
	cout<<"	string str;	//待检测字符串"<<endl;
	cout<<"	init();//初始化	"<<endl;
	cout<<"	while(cin>>str){"<<endl;
	cout<<"		cout<<str<<\" \";"<<endl;
	cout<<"		Yufa(str);"<<endl;
	cout<<"	}"<<endl;
	cout<<"	return 0;"<<endl;
	cout<<"}"<<endl;
	
	system("pause");

	return 0;
}