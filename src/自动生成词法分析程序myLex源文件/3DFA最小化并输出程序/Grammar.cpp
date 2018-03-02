#include<fstream>
#include<vector>
using namespace std;
struct subset
{
	int id;
	vector<int> set;
};
class Grammar
{
public:
	Grammar(ifstream &in);
	~Grammar(void);
	int k;//状态个数
	int tc;//终结符个数
	char t[26];//终结符
	int m;//边数
	int DFA[32][128];
	int belong[32];//某个状态属于哪个子集
	bool terminal[32];//终结符表
	int terminalCount;//终结符个数
	bool Mterminal[32];//最小化后的终结符表
	int MDFA[32][128];//最小化的DFA表
	int MDFAstart;// 最小化的DFA的初态
	subset DFAsubset[32];//划分的子集
	int subsetcount;//子集的个数
	void erase();
	vector<subset> spilt(subset I);
	void min();
	bool insameset(int e,subset &v);
};

Grammar::Grammar(ifstream &in)
{
	int i,u,v;
	char a;
	memset(terminal,false,sizeof(terminal));
	memset(Mterminal,false,sizeof(Mterminal));
	for(u=0;u<32;u++)
		for(v=0;v<128;v++)
		{
			DFA[u][v]=-1;
			MDFA[u][v]=-1;
		}
	this->subsetcount=0;
	in>>this->k;//状态个数
	in>>this->tc;//终结符个数
	for(i=0;i<tc;i++)//所有终结符
		in>>t[i];
	in>>this->terminalCount;//终态个数
	for(i=0;i<this->terminalCount;i++)//标志终态
	{
		in>>u;
		terminal[u]=true;
	}
	in>>this->m;//边数
	for(i=0;i<m;i++)//构造邻接矩阵
	{
		in>>u>>a>>v;
		DFA[u][a]=v;
	}
	this->min();
}

void Grammar::min()
{
	subset start,end;
	int i,id=0;
	start.id=id++;
	end.id=id++;
	for(i=1;i<=this->k;i++)
	{
		if(terminal[i])
		{
			end.set.push_back(i);
			belong[i]=end.id;
		}
		else 
		{
			start.set.push_back(i);
			belong[i]=start.id;
		}
	}
	DFAsubset[subsetcount++]=start;
	DFAsubset[subsetcount++]=end;
	while(true)
	{
		bool flag=false;
		for(i=0;i<subsetcount;i++)
		{
			if(DFAsubset[i].set.size()<2) continue;
			vector<subset> vs=spilt(DFAsubset[i]);
			if(vs.size()>1)
			{
				flag=true;
				vs[0].id=DFAsubset[i].id;
				DFAsubset[i]=vs[0];
				for(unsigned int j=1;j<vs.size();j++)
				{
					DFAsubset[subsetcount]=vs[j];
					DFAsubset[subsetcount].id=id;
					for(unsigned int j=0;j<DFAsubset[subsetcount].set.size();j++)
						belong[DFAsubset[subsetcount].set[j]]=id;
					subsetcount++;
					id++;
				}
			}
		}
		if(!flag)
			break;
	}
	for(i=0;i<subsetcount;i++)
	{
		int j;
		for(j=0;j<tc;j++)//确定MDFA的状态转换表
			MDFA[i][t[j]]=belong[DFA[DFAsubset[i].set[0]][t[j]]];
		for(j=0;j<DFAsubset[i].set.size();j++)//确定MDFA的终态和初态
		{
			if(terminal[DFAsubset[i].set[j]])
				Mterminal[i]=true;
			if(DFAsubset[i].set[j]==1)
				MDFAstart=i;
		}
	}
}
vector<subset> Grammar::spilt(subset I)
{
	subset sub;
	vector<subset> U;
	sub.set.push_back(I.set[0]);
	U.push_back(sub);
	for(unsigned int i=1;i<I.set.size();i++)
	{
		bool flag=false;
		for(unsigned int j=0;j<U.size();j++)
			if(insameset(I.set[i],U[j]))
			{
				flag=true;
				U[j].set.push_back(I.set[i]);
				break;
			}
		if(!flag)
		{
			subset t;
			t.set.push_back(I.set[i]);
			U.push_back(t);
		}
	}
	return U;
}
bool Grammar::insameset(int e,subset &u)
{
	int s=u.set[0];
	for(int i=0;i<tc;i++)
		if(belong[DFA[e][t[i]]]!=belong[DFA[s][t[i]]])
			return false;
	return true;
}
void Grammar::erase()
{
}

Grammar::~Grammar(void)
{
}
