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

//�����Ϳ�ʼ״̬������״̬
int K,S,Z;

//�ַ���
int strSize;
string strs[MaxStr];

//����NFA���
struct NFA_Node{
	int state;//״̬0,1,2,3....
	string str;//�����״̬��Ҫ���ַ���
	NFA_Node* pNext;
};

//����NFAͷ���
struct NFA_Head{
	NFA_Node* pHead;
}NFA_Heads[MaxState];

//���뼯�ϣ�������չ��ļ��ϣ���-1��β
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

//���뼯�ϣ�����Move(mystr)��ļ��ϣ���-1��β
void move(int a[],string mystr){

	int ta[MaxState];
	//ta[0]=-1;
	int gs=0;

	//�����еĵ���б�������
	int index=0;
	while(a[index]!=-1){
		NFA_Node* pNode=NFA_Heads[a[index]].pHead;
		while(pNode){
			if(pNode->str==mystr){//������Ҫ����Ļ�
				//�Ƿ��Ѿ�����
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

//DFA����
int Newstate[MaxState2][MaxState];
int MaxStateNum=0;
int IsDeal[MaxState2];
int endState[MaxState2];

//����DFA���
struct DFA_Node{
	int state;//״̬0,1,2,3....
	string str;//�����״̬��Ҫ���ַ���
	DFA_Node* pNext;
};

//����DFAͷ���
struct DFA_Head{
	DFA_Node* pHead;
}DFA_Heads[MaxState2];



//�ж�ĳ�������ǲ����Ѿ�����,���ڵĻ������±��
int isExitSet(int a[]){
	for(int i=0;i<MaxStateNum;++i){
		bool isfit=true;
		//ɨ���ж��Ƿ��ڼ�����
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

//��ĳ�����ϼ��뵽�¼�����
void addSet(int a[]){
	for(int i=0;;++i){
		Newstate[MaxStateNum][i]=a[i];
		if(a[i]==Z)//��̬
			endState[MaxStateNum]=1;
		if(a[i]==-1)
			break;
	}
	MaxStateNum++;
}

//������װ�����ַ���
string intTochar(int n){
	string str="";
	do{
		str=char('0'+(n%10))+str;
		n/=10;
	}while(n>0);
	return str;
}


int visited[MaxState];//��¼DFA��ÿ�����Ƿ񵽹�
//��ȱ���DFA,��ǵ��Ƿ��߹�
void dfs_DFA(int index)
{ 
	visited[index]=1;
	for(DFA_Node* pNode=DFA_Heads[index].pHead;;pNode=pNode->pNext){
		if(pNode==NULL)
			break;
		if(visited[pNode->state]==0)//��û�з��ʹ� 
			dfs_DFA(pNode->state);
	}
}

int nowIndex=0; //��ǰҪ���Ľڵ�
int visited2[MaxState];//��¼DFA��ÿ�����Ƿ񵽹�

//��ȱ���DFA,����ǰ�ĵ��ܷ񵽴��յ�
void  dfs_DFA2(int index)
{ 
	visited2[index]=1;
	for(DFA_Node* pNode=DFA_Heads[index].pHead;;pNode=pNode->pNext){
		if(pNode==NULL)
			break;
		if(visited[nowIndex]==1){ //�Ѿ�ȷ�����Ե����յ�
			return;
		}
		if(endState[pNode->state]==1){//�����յ�
			visited[nowIndex]=1;
			return;
		}else if(visited2[pNode->state]==0){//û���ʹ�
			dfs_DFA2(pNode->state);
		}
	}
}


int main(){
	ifstream cin("out1.txt");
	ofstream cout("out2.txt");

	//�������Ϳ�ʼ״̬������״̬
	cin>>K>>S>>Z;
	
	//���ַ���
	cin>>strSize;
	for(int i0=0;i0<strSize;++i0){
		cin>>strs[i0];
	}

	//��ʼ���ڽӾ���
	int from,to; 
	string str;
	while(cin>>from>>to>>str){
		//��ʼ��
		NFA_Node* node=new NFA_Node;
		node->state=to;
		node->str=str;
		//ͷ�巨
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
	
	//NFA to DFA�㷨���Ӽ������㷨������ԭ����P59��
	//string sets[MaxState];
	//int setsSize=0;
	
	//����
	/*
		������չ����

		����һ��ȫ��set��vector
		��ȫ��vector�з���һ����ʼ������
		Ȼ�����������������������ĵ����set�У���û�д������棬������ڣ�����һ��
		
		Move����
		���ݼ��ϣ������еĵ������е��������Moveһ�ߣ���������µļ��ϣ���ô�ͷ��������

	*/

	//1 ��ʼ����closure(S)Ϊ�����е�Ψһ��Ա����������δ��ǵġ�
	int a[MaxState];
	a[0]=S;
	a[1]=-1;
	closure(a);
	addSet(a);
	
	memset(IsDeal,0,sizeof(IsDeal));//ȫ��δ���
	memset(endState,0,sizeof(endState));//��̬

	//ѭ��

	//����ַ�������
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
		//�ַ���
		for(int i2=0;i2<strSize;++i2){
			string  mystr=strs[i2];
			int ta[MaxState];
			//��������
			for(int i3=0;i3<MaxState;++i3){
				ta[i3]=	Newstate[dealIndex][i3];
			}

			move(ta,mystr);
			closure(ta);

			string str_out="";
			int addIndex=isExitSet(ta);
			if(addIndex!=-1){
	
				//�����
				vfrom.push_back(dealIndex);
				vstr.push_back(mystr);
				vto.push_back(addIndex);
				
				//�ѵ�����DFA��
				int from=dealIndex;
				int to=addIndex;

				//��ʼ��
				DFA_Node* node=new DFA_Node;
				node->state=to;
				node->str=mystr;
				//ͷ�巨
				node->pNext=DFA_Heads[from].pHead;
				DFA_Heads[from].pHead=node;

			}else{
				addSet(ta);	
				addIndex=isExitSet(ta);
				
				//�����
				vfrom.push_back(dealIndex);
				vstr.push_back(mystr);
				vto.push_back(addIndex);

				//�ѵ�����DFA��
				int from=dealIndex;
				int to=addIndex;

				//��ʼ��
				DFA_Node* node=new DFA_Node;
				node->state=to;
				node->str=mystr;
				//ͷ�巨
				node->pNext=DFA_Heads[from].pHead;
				DFA_Heads[from].pHead=node;

			}
		}
	}
	 
	/*
		��������״̬ ��P60
		����״̬��1 ���Զ����Ŀ�ʼ״����0��ʼ��̬�������κ����봮Ҳ���ܵ�����Ǹ�״̬
				  2 �����״̬ û��ͨ·������̬
	*/

	memset(visited,0,sizeof(visited));//��ʼʱ�����ܵ���
	//ȥ�����ܵ����״̬
	dfs_DFA(0);
	
	//�����ܵ���״̬�������ܲ��ܵ����յ�
	for(int i7=0;i7<MaxStateNum;++i7){
		nowIndex=i7;
		if(visited[nowIndex]==1){//�ܵ���
			if(endState[nowIndex]==0){//��̬���ÿ��ǣ����Ƿ���̬
				visited[nowIndex]=0;
				memset(visited2,0,sizeof(visited2));//��ʼʱ�����ܵ���
				dfs_DFA2(nowIndex); //����ܵ���Ļ���������Ϊ1
			}
		}

	}


	int stateNums=0;
	for(int i8=0;i8<MaxStateNum;++i8){
		stateNums+=visited[i8];
	}

	//�������
	cout<<stateNums<<endl;

	//����ַ���
	cout<<strSize<<endl;
	for(int i4=0;i4<strSize;++i4){
		cout<<strs[i4]<<" ";
	}
	cout<<endl;

	//Ҫƫ�Ƶĸ���
	int front[MaxState];//��¼DFA��ÿ�����Ƿ񵽹�
	memset(front,0,sizeof(front));
	for(int i9=1;i9<MaxStateNum;++i9){
		front[i9]=front[i9-1];
		if(visited[i9-1]==0)//ǰ��Ĳ��ܴﵽ
			front[i9]++;
	}

	string tmp;
	int gs=0;//��̬����
	//��̬
	for(int i5=0;i5<MaxStateNum;++i5){
		if(	endState[i5]==1&&visited[i5]==1){ //�ܹ��������̬
			gs++;
			tmp+=intTochar(i5+1-front[i5])+" ";
		}
	}
	cout<<gs<<endl;
	cout<<tmp<<endl;

	//�����
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