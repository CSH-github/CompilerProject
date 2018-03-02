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
	vector<string> vout; //输出字符串
	vector<string> zfj; //字符集
	string start="";//开始状态
	string end="Z";//结束状态
	int a[26];

	int stateNum=1;//状态个数，开始就有结束状态
	int nextIndex=1;//z下标为0
	memset(a,0,sizeof(a));

	string s1,s2,s3;
	cin>>s1>>s2>>s3;
	start=s1;
	if(s3!="NULL")
		zfj.push_back(s2);
	
	do{
		//状态，不会超过25个
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

		//添加字符集
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

	//状态个数 开始状态 结束状态
	cout<<stateNum<<" "<<a[start[0]-'A']<<" "<<0<<endl;
	//字符集个数 字符集
	cout<<zfj.size()<<" ";
	for(int i=0;i<zfj.size();++i)
		cout<<zfj[i]<<" ";
	cout<<endl;
	//起点状态1 目的状态1 边值1
	for(int j=0;j<vout.size();++j){
		cout<<vout[j]<<endl;
	}
	return 0;
}
