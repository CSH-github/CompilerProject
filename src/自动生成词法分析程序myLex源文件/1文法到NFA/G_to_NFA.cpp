#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
string intTochar(int n){
	string str="";
	do{
		str=char('0'+(n%10))+str;
		n/=10;
	}while(n>0);
	return str;
}
int main(){
	ifstream cin("in.txt");
	ofstream cout("out1.txt");
	vector<string> vout; //����ַ���
	vector<string> zfj; //�ַ���
	string start="";//��ʼ״̬
	string end="Z";//����״̬
	int a[26];

	int stateNum=1;//״̬��������ʼ���н���״̬
	int nextIndex=1;//z�±�Ϊ0
	memset(a,0,sizeof(a));

	string s1,s2,s3;
	cin>>s1>>s2>>s3;
	start=s1;
	if(s3!="NULL")
		zfj.push_back(s2);
	
	do{
		//״̬�����ᳬ��25��
		if(a[s1[0]-'A']==0){
			a[s1[0]-'A']=nextIndex;
			stateNum++;
			nextIndex++;
		}
		
		string tmp=intTochar(a[s1[0]-'A'])+" ";

		if(s3=="NULL"){
			tmp+=intTochar(0)+" "+s2;
		}else{
			if(a[s3[0]-'A']==0){
				a[s3[0]-'A']=nextIndex;
				stateNum++;
				nextIndex++;
			}
			tmp+=intTochar(a[s3[0]-'A'])+" "+s2;
		}
		vout.push_back(tmp);

		//����ַ���
		if(s2!="NULL"){
			bool needAdd=true;
			for(int j=0;j<zfj.size();++j){
				if(zfj[j]==s2){
					needAdd=false;
					break;
				}
			}
			if(needAdd)
				zfj.push_back(s2);
		}

	}while(cin>>s1>>s2>>s3);

	//״̬���� ��ʼ״̬ ����״̬
	cout<<stateNum<<" "<<a[start[0]-'A']<<" "<<0<<endl;
	//�ַ������� �ַ���
	cout<<zfj.size()<<" ";
	for(int i=0;i<zfj.size();++i)
		cout<<zfj[i]<<" ";
	cout<<endl;
	//���״̬1 Ŀ��״̬1 ��ֵ1
	for(int j=0;j<vout.size();++j){
		cout<<vout[j]<<endl;
	}
	return 0;
}
