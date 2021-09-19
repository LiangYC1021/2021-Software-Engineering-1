#include<bits/stdc++.h>
#include<iostream>
#include<stack> 
#include<vector>
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

int Tot_num,Swi_num,Case_num;
int elseif_num,else_num;
vector<int>Swt;//the case num of each "Switch" Keyword
vector<string>ie;//the "queue" of "if_else" or "if_elseif_else" Keywords
stack<string>stk;//the "stack" of "if_else" or "if_elseif_else" Keywords


inline string Pre(string s)
{
	string res="";
	for(int i=0;i<s.size();i++){
		if(s[i]=='"'){
			for(int j=i+1;i<s.size();j++){
				if(s[j]=='"'){
					s.erase(i,j-i+1);
					break;
				}
			}	
		}
	}	
	for(int i=0;i<s.size();i++){
		if(s[i]=='/'&&s[i+1]=='/'){
			return res;
		}
		res+=s[i];
	}
	return res;
} 

inline bool Match(string s)
{
	string res="NULL";
	rep(i,1,32){
		if(s==Key[i]){
			res=Key[i];
			break;
		}
	}
	if(res=="switch"&&Case_num){
		Swt.push_back(Case_num);
		Case_num=0;
	}
	if(res=="case")Case_num++;
	if(res=="if" || res=="else")ie.push_back(res);
	if(res!="NULL"){
		Tot_num++;
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
		if(s[i]=='{')ie.push_back("{");
		if(s[i]=='}')ie.push_back("}");
		for(int j=8;j>=2;j--){
			if(Match(s.substr(i,j))){
				i+=j-1;
				break;
			}
		}		
	}
}

inline void Special_Check(string s)
{
	int len=s.size();
	s+="$$$$";
	int temp_if=0,temp_else=0;
	for(int i=0;i<len;i++){
		if(s.substr(i,2)=="if" && temp_else)temp_if++;
		if(s.substr(i,4)=="else")temp_else++;
	}
	if(temp_else && temp_if){
		stack<string>tmp;
		bool f1=0,f2=0;
		while(f1==0 && f2==0){
			string bk=ie.back();
			ie.pop_back();
			if(bk=="if")f2=1;
			if(bk=="else")f1=1;
			if(bk!="if"&&bk!="else")tmp.push(bk);
		}
		ie.pop_back();
		ie.push_back("else_if");
		while(!tmp.empty()){
			ie.push_back(tmp.top());
			tmp.pop();
		}
		//Replace "else" "if" with "else_if"
	}
}

inline void Count_ie_num()
{
	for(int i=0;i<ie.size();i++){
		if(ie[i]=="}"){
			while(!stk.empty()){
				string tp=stk.top();
				stk.pop();
				if(tp=="{")break;
				else if(tp=="else"){
					bool flag=0;
					while(!stk.empty()){
						tp=stk.top();
						stk.pop();
						if(tp=="else_if")flag=1;
						if(tp=="if")break;
					}
					if(flag)elseif_num++;
					else else_num++;
				}
			}
		}
		else stk.push(ie[i]);
	}	
}

inline void Out(int level)
{
	if(!(1<=level && level<=4)){
		cout<<"This is an incorrect level, please enter a level between 1 and 4."<<endl;
		return;
	}	
	if(level>=1)cout<<"total num: "<<Tot_num<<endl;	
	if(level>=2){		
		if(Swt.size()>0){
			cout<<"switch num: "<<Swt.size()<<endl;
			cout<<"case num: ";	
			for(int i=0;i<Swt.size();i++){
				if(i)cout<<" ";
				cout<<Swt[i];
			}		
		}
		else cout<<"There is no Switch structure";
		cout<<endl;
	}
	if(level>=3)cout<<"if-else num: "<<else_num<<endl;
	if(level>=4)cout<<"if-elseif-else num: "<<elseif_num<<endl;			
}
int main()
{	
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	char* File_road;
	int level;
	cin>>File_road>>level;
	
	FILE* fp=freopen(File_road,"r",stdin);
	if (fp == NULL)//File not found
	{
		cout<<"File not found"<<endl;
		return 0;
	}
	
	string s;
	while(getline(cin,s)){
		s=Pre(s);
		check(s);
		Special_Check(s);
	}
	if(Case_num)Swt.push_back(Case_num);
	Count_ie_num();//count the number of "if else" or "if else_if else"
	for(int i=0;i<Swt.size();i++);
		
	Out(level);
	return 0;
}

