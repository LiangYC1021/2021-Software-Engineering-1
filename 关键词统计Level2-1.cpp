#include<bits/stdc++.h>
#include<iostream>
#define inf 1e18+5
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const int N=1e5+5;
string Key[105]={"","auto","break","case","char","const","continue","default","do",
"double","else","enum","extern","float","for","goto","if",
"int","long","register","return","short","signed","sizeof","static",
"struct","switch","typedef","union","unsigned","void","volatile","while"};
//there are 32 keywords

int tot_num,swi_num,case_num;
vector<int>Swich;
inline bool match(string s)
{
	string res="NULL";
	rep(i,1,32){
		if(s==Key[i]){
			res=Key[i];
			break;
		}
	}
	if(res=="switch"&&case_num){
		Swich.push_back(case_num);
		case_num=0;
	}
	if(res=="case")case_num++;
	if(res!="NULL"){
		tot_num++;
		return true;
	}
	return false;
}
inline void check(string s)
{
	int len=s.size();
	s+="$$$$$$$$$";
	//Prevent overflow
	for(int i=0;i<len;i++){
		for(int j=8;j>=2;j--){
			if(match(s.substr(i,j))){
				i+=j-1;
				break;
			}
		}		
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	string s;
	while(getline(cin,s)){
		check(s);
	}
	
	if(case_num)Swich.push_back(case_num);
	cout<<"total num: "<<tot_num<<endl;
	cout<<"switch num: "<<Swich.size()<<endl;
	cout<<"case num: ";
	for(int i=0;i<Swich.size();i++){
		if(i!=Swich.size()-1)cout<<Swich[i]<<" ";
		else cout<<Swich[i]<<endl;
	}
	return 0;
}

