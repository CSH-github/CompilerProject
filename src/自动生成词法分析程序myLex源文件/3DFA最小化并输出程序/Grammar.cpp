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
	int k;//״̬����
	int tc;//�ս������
	char t[26];//�ս��
	int m;//����
	int DFA[32][128];
	int belong[32];//ĳ��״̬�����ĸ��Ӽ�
	bool terminal[32];//�ս����
	int terminalCount;//�ս������
	bool Mterminal[32];//��С������ս����
	int MDFA[32][128];//��С����DFA��
	int MDFAstart;// ��С����DFA�ĳ�̬
	subset DFAsubset[32];//���ֵ��Ӽ�
	int subsetcount;//�Ӽ��ĸ���
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
	in>>this->k;//״̬����
	in>>this->tc;//�ս������
	for(i=0;i<tc;i++)//�����ս��
		in>>t[i];
	in>>this->terminalCount;//��̬����
	for(i=0;i<this->terminalCount;i++)//��־��̬
	{
		in>>u;
		terminal[u]=true;
	}
	in>>this->m;//����
	for(i=0;i<m;i++)//�����ڽӾ���
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
		for(j=0;j<tc;j++)//ȷ��MDFA��״̬ת����
			MDFA[i][t[j]]=belong[DFA[DFAsubset[i].set[0]][t[j]]];
		for(j=0;j<DFAsubset[i].set.size();j++)//ȷ��MDFA����̬�ͳ�̬
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
