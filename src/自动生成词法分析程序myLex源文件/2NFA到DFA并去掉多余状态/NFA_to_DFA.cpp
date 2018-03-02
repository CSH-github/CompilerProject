#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;
#define  MaxState 26
#define	 MaxState2 400
#define  MaxStr   150

//个数和开始状态，结束状态
int K,S,Z;

//字符串
int strSize;
string strs[MaxStr];

//定义NFA结点
struct NFA_Node{
	int state;//状态0,1,2,3....
	string str;//到这个状态需要的字符串
	NFA_Node* pNext;
};

//定义NFA头结点
struct NFA_Head{
	NFA_Node* pHead;
}NFA_Heads[MaxState];

//输入集合，返回扩展后的集合，以-1结尾
void  closure(int a[]){
	int ta[MaxState];
	int gs=0;
	for(int i=0;;i++){
		ta[i]=a[i];
		if(ta[i]==-1)
			break;
		else
			gs++;
	}
	
	for(int j=0;;j++){
		if(j>=gs)
			break;
		NFA_Node* pNode=NFA_Heads[ta[j]].pHead;
		while(pNode){
			if(pNode->str=="NULL"){
				int index=pNode->state;
				bool isexit=false;
				for(int k=0;k<gs;++k){
					if(ta[k]==index){
						isexit=true;
						break;
					}
				}
				if(!isexit){
					ta[gs]=index;
					gs++;
				}
			}
			pNode=pNode->pNext;
		}
	}

	sort(ta,ta+gs);
	ta[gs]=-1;
	
	for(int g=0;g<=gs;++g)
		a[g]=ta[g];

}

//输入集合，返回Move(mystr)后的集合，以-1结尾
void move(int a[],string mystr){

	int ta[MaxState];
	//ta[0]=-1;
	int gs=0;

	//对所有的点进行遍历操作
	int index=0;
	while(a[index]!=-1){
		NFA_Node* pNode=NFA_Heads[a[index]].pHead;
		while(pNode){
			if(pNode->str==mystr){//若果需要加入的话
				//是否已经存在
				bool isexit=false;
				for(int k=0;k<gs;k++){
					if(ta[k]==pNode->state){
						isexit=true;
						break;
					}
				}
				if(!isexit){
					ta[gs]=pNode->state;
					gs++;
				}
			}
			pNode=pNode->pNext;
		}

		index++;
	}

	
	sort(ta,ta+gs);
	ta[gs]=-1;
	
	for(int g=0;g<=gs;++g)
		a[g]=ta[g];

}

//DFA定义
int Newstate[MaxState2][MaxState];
int MaxStateNum=0;
int IsDeal[MaxState2];
int endState[MaxState2];

//定义DFA结点
struct DFA_Node{
	int state;//状态0,1,2,3....
	string str;//到这个状态需要的字符串
	DFA_Node* pNext;
};

//定义DFA头结点
struct DFA_Head{
	DFA_Node* pHead;
}DFA_Heads[MaxState2];



//判断某个集合是不是已经存在,存在的话返回下标号
int isExitSet(int a[]){
	for(int i=0;i<MaxStateNum;++i){
		bool isfit=true;
		//扫描判断是否在集合中
		for(int j=0;;j++){
			if(a[j]!=Newstate[i][j]){
				isfit=false;
				break;
			}
			if(a[j]==-1)
				break;
		}

		if(isfit)
			return i;
	}
	return -1;
}

//将某个集合加入到新集合中
void addSet(int a[]){
	for(int i=0;;++i){
		Newstate[MaxStateNum][i]=a[i];
		if(a[i]==Z)//终态
			endState[MaxStateNum]=1;
		if(a[i]==-1)
			break;
	}
	MaxStateNum++;
}

//将数字装换成字符串
string intTochar(int n){
	string str="";
	do{
		str=char('0'+(n%10))+str;
		n/=10;
	}while(n>0);
	return str;
}


int visited[MaxState];//记录DFA的每个点是否到过
//深度遍历DFA,标记点是否走过
void dfs_DFA(int index)
{ 
	visited[index]=1;
	for(DFA_Node* pNode=DFA_Heads[index].pHead;;pNode=pNode->pNext){
		if(pNode==NULL)
			break;
		if(visited[pNode->state]==0)//点没有访问过 
			dfs_DFA(pNode->state);
	}
}

int nowIndex=0; //当前要检测的节点
int visited2[MaxState];//记录DFA的每个点是否到过

//深度遍历DFA,看当前的点能否到达终点
void  dfs_DFA2(int index)
{ 
	visited2[index]=1;
	for(DFA_Node* pNode=DFA_Heads[index].pHead;;pNode=pNode->pNext){
		if(pNode==NULL)
			break;
		if(visited[nowIndex]==1){ //已经确定可以到达终点
			return;
		}
		if(endState[pNode->state]==1){//到达终点
			visited[nowIndex]=1;
			return;
		}else if(visited2[pNode->state]==0){//没访问过
			dfs_DFA2(pNode->state);
		}
	}
}


int main(){
	ifstream cin("out1.txt");
	ofstream cout("out2.txt");

	//读个数和开始状态，结束状态
	cin>>K>>S>>Z;
	
	//读字符集
	cin>>strSize;
	for(int i0=0;i0<strSize;++i0){
		cin>>strs[i0];
	}

	//初始化邻接矩阵
	int from,to; 
	string str;
	while(cin>>from>>to>>str){
		//初始化
		NFA_Node* node=new NFA_Node;
		node->state=to;
		node->str=str;
		//头插法
		node->pNext=NFA_Heads[from].pHead;
		NFA_Heads[from].pHead=node;
	}
	
	/*for(int i=0;i<statue_num;++i){
		NFA_Node* pNode=NFA_Heads[i].pHead;
		while(pNode){
			cout<<i<<" "<<pNode->state<<" "<<pNode->str<<endl;
			pNode=pNode->pNext;
		}
	}*/
	
	//NFA to DFA算法，子集构造算法，编译原理书P59上
	//string sets[MaxState];
	//int setsSize=0;
	
	//流程
	/*
		集合扩展操作

		定义一个全局set和vector
		在全局vector中放入一个初始话集合
		然后掉用深度收索，将搜索到的点放入set中，点没有存在里面，如果存在，则下一个
		
		Move操作
		根据集合，将所有的点用所有的输入可能Move一边，如果产生新的集合，那么就放入队列中

	*/

	//1 开始，令closure(S)为集合中的唯一成员，并且它是未标记的。
	int a[MaxState];
	a[0]=S;
	a[1]=-1;
	closure(a);
	addSet(a);
	
	memset(IsDeal,0,sizeof(IsDeal));//全部未标记
	memset(endState,0,sizeof(endState));//终态

	//循环

	//输出字符串向量
	vector<int> vfrom;
	vector<string> vstr;
	vector<int> vto;

	while(true){
		int dealIndex=-1;
		for(int i1=0;i1<MaxStateNum;++i1){
			if(IsDeal[i1]==0){
				IsDeal[i1]=1;
				dealIndex=i1;
				break;
			}
		}
		if(dealIndex==-1)
			break;
		//字符串
		for(int i2=0;i2<strSize;++i2){
			string  mystr=strs[i2];
			int ta[MaxState];
			//拷贝数组
			for(int i3=0;i3<MaxState;++i3){
				ta[i3]=	Newstate[dealIndex][i3];
			}

			move(ta,mystr);
			closure(ta);

			string str_out="";
			int addIndex=isExitSet(ta);
			if(addIndex!=-1){
	
				//保存边
				vfrom.push_back(dealIndex);
				vstr.push_back(mystr);
				vto.push_back(addIndex);
				
				//把点加入的DFA中
				int from=dealIndex;
				int to=addIndex;

				//初始化
				DFA_Node* node=new DFA_Node;
				node->state=to;
				node->str=mystr;
				//头插法
				node->pNext=DFA_Heads[from].pHead;
				DFA_Heads[from].pHead=node;

			}else{
				addSet(ta);	
				addIndex=isExitSet(ta);
				
				//保存边
				vfrom.push_back(dealIndex);
				vstr.push_back(mystr);
				vto.push_back(addIndex);

				//把点加入的DFA中
				int from=dealIndex;
				int to=addIndex;

				//初始化
				DFA_Node* node=new DFA_Node;
				node->state=to;
				node->str=mystr;
				//头插法
				node->pNext=DFA_Heads[from].pHead;
				DFA_Heads[from].pHead=node;

			}
		}
	}
	 
	/*
		消除多余状态 书P60
		无用状态：1 从自动机的开始状（从0开始）态出发，任何输入串也不能到达的那个状态
				  2 从这个状态 没有通路到达终态
	*/

	memset(visited,0,sizeof(visited));//开始时都不能到达
	//去掉不能到达的状态
	dfs_DFA(0);
	
	//遍历能到的状态，看看能不能到达终点
	for(int i7=0;i7<MaxStateNum;++i7){
		nowIndex=i7;
		if(visited[nowIndex]==1){//能到达
			if(endState[nowIndex]==0){//终态不用考虑，考虑非终态
				visited[nowIndex]=0;
				memset(visited2,0,sizeof(visited2));//开始时都不能到达
				dfs_DFA2(nowIndex); //如果能到达的话在再设置为1
			}
		}

	}


	int stateNums=0;
	for(int i8=0;i8<MaxStateNum;++i8){
		stateNums+=visited[i8];
	}

	//输出个数
	cout<<stateNums<<endl;

	//输出字符集
	cout<<strSize<<endl;
	for(int i4=0;i4<strSize;++i4){
		cout<<strs[i4]<<" ";
	}
	cout<<endl;

	//要偏移的个数
	int front[MaxState];//记录DFA的每个点是否到过
	memset(front,0,sizeof(front));
	for(int i9=1;i9<MaxStateNum;++i9){
		front[i9]=front[i9-1];
		if(visited[i9-1]==0)//前面的不能达到
			front[i9]++;
	}

	string tmp;
	int gs=0;//终态个数
	//终态
	for(int i5=0;i5<MaxStateNum;++i5){
		if(	endState[i5]==1&&visited[i5]==1){ //能够到达的终态
			gs++;
			tmp+=intTochar(i5+1-front[i5])+" ";
		}
	}
	cout<<gs<<endl;
	cout<<tmp<<endl;

	//输出边
	vector<string> vout;
	for(int i10=0;i10<vfrom.size();++i10){
		if(visited[vfrom[i10]]==1&&visited[vto[i10]]==1){
			string str_out=intTochar(vfrom[i10]+1-front[vfrom[i10]])+" "+vstr[i10]+" "+intTochar(vto[i10]+1-front[vto[i10]]);
			vout.push_back(str_out);
		}
	}
	
	cout<<vout.size()<<endl;
	for(int i6=0;i6<vout.size();++i6){
		cout<<vout[i6]<<endl;
	}
	

	return 0;
}