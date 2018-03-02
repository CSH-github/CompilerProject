#include"Grammar.cpp"
#include <stdio.h> 
#include<string>

string intTochar(int n){
	string str="";
	do{
		str=char('0'+(n%10))+str;
		n/=10;
	}while(n>0);
	return str;
}

void main()
{
	ifstream in("out2.txt");
	freopen("out3.txt","w",stdout);

	Grammar G(in);
	int i,k;
	//print DFA
	printf("��ʼ�Զ���Ϊ:\n    ");
	for(i=0;i<G.tc;i++)
		printf("%-4c",G.t[i]);
	printf("\n");
	for(k=1;k<=G.k;k++)
	{
		printf(" %d  ",k);
		for(i=0;i<G.tc;i++)
		{
			if(G.DFA[k][G.t[i]]!=-1)
				printf("%-4d",G.DFA[k][G.t[i]]);
			else printf("    ");
		}
		printf("\n");
	}
	printf("��ʼ״̬Ϊ:1\n����״̬Ϊ:");
	for(k=0;k<32;k++)
		if(G.terminal[k])
			printf("%d ",k);
	printf("\n");
	//print MDFA
	printf("��С��֮��Ϊ:\n    ");
	for(i=0;i<G.tc;i++)
		printf("%-4c",G.t[i]);
	printf("\n");
	for(k=0;k<G.subsetcount;k++)
	{
		printf(" %d  ",k+1);
		for(i=0;i<G.tc;i++)
		{
			if(G.MDFA[k][G.t[i]]!=-1)
				printf("%-4d",G.MDFA[k][G.t[i]]+1);
			else printf("    ");
		}
		printf("\n");
	}
	printf("��ʼ״̬��:%d\n",G.MDFAstart+1); 
	printf("����״̬Ϊ:");
	for(k=0;k<G.subsetcount;k++)
		if(G.Mterminal[k])
			printf("%d ",k+1);
	printf("\n");

	/*�������*/
	ofstream cout("test.cpp");

	cout<<"#include<iostream>"<<endl;
	cout<<"#include<fstream>"<<endl;
	cout<<"#include<string>"<<endl;
	cout<<"using namespace std;"<<endl;
	
	cout<<endl;

	cout<<"//��������"<<endl;
	for(k=0;k<G.subsetcount;k++)
		cout<<"bool S"<<intTochar(k+1)<<"(string str,int index);"<<endl;
	cout<<endl;
	
	cout<<endl;

	//�������
	for(k=0;k<G.subsetcount;k++)
	{
		cout<<"bool S"<<intTochar(k+1)<<"(string str,int index){";
		if(k==G.MDFAstart)
			cout<<"	//��ʼ̬";
		if(G.Mterminal[k])
			cout<<"	//��̬";
		cout<<endl;
		
		cout<<"	if(index>=str.length())//��������"<<endl;
		if(G.Mterminal[k])//��̬
			cout<<"		return true;"<<endl;
		else
			cout<<"		return false;"<<endl;

		for(i=0;i<G.tc;i++)
		{
			if(G.MDFA[k][G.t[i]]!=-1){
				cout<<"	if(str[index]=='"<<G.t[i]<<"'){	//�����ַ�Ϊ'"<<G.t[i]<<"'"<<endl;
				cout<<"		index++;"<<endl;
				cout<<"		return S"<<intTochar(G.MDFA[k][G.t[i]]+1)<<"(str,index);"<<endl;
				cout<<"	}"<<endl;
			}
		}
		cout<<"	return false;"<<endl;
		cout<<"}"<<endl<<endl;
	}

	//���������
	cout<<"int main(){"<<endl;
	cout<<"	ifstream cin(\"in.txt\");"<<endl;
	cout<<"	string str;	//������ַ���"<<endl;
	cout<<"	int index=0;	//������ַ�λ��"<<endl;
	cout<<"	while(cin>>str){"<<endl;
	cout<<"		index=0;"<<endl;
	cout<<"		if(S1(str,index))"<<endl;
	cout<<"			cout<<\"�� \"<<str<<endl;"<<endl;
	cout<<"		else"<<endl;
	cout<<"			cout<<\"�� \"<<str<<endl;"<<endl;
	cout<<"	}"<<endl;
	cout<<"	return 0;"<<endl;
	cout<<"}"<<endl;

}
