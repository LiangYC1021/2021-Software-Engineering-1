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

int tot_num,swi_num,case_num;
int elseif_num,else_num;
vector<int>Swich;//the case num of each "Swich" Keyword
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
			break;	
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
	if(res=="if" || res=="else")ie.push_back(res);
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
		if(s[i]=='{')ie.push_back("{");
		if(s[i]=='}')ie.push_back("}");
		for(int j=8;j>=2;j--){
			if(match(s.substr(i,j))){
				i+=j-1;
				break;
			}
		}		
	}
}

inline void special_check(string s)
{
	int len=s.size();
	s+="$$$$";
	int temp_if=0,temp_else=0;
	for(int i=0;i<len;i++){
		if(s.substr(i,2)=="if")temp_if++;
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
//		cout<<ie[i]<<'\n';
		if(ie[i]=="}"){
			if(stk.top()!="else"){//失配，该情况不计数 
				while(!stk.empty()){
					if(stk.top()=="{"){
						stk.pop();
						break;
					}
					stk.pop();
				} 
			}
			else while(!stk.empty()){
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

int main()
{
	freopen("test.txt","r",stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	string s;
	while(getline(cin,s)){
		s=Pre(s);
		check(s);
		special_check(s);
	}
	
	if(case_num)Swich.push_back(case_num);
	cout<<"total num: "<<tot_num<<endl;
	cout<<"switch num: "<<Swich.size()<<endl;
	cout<<"case num: ";
	for(int i=0;i<Swich.size();i++){
		if(i!=Swich.size()-1)cout<<Swich[i]<<" ";
		else cout<<Swich[i];
	}
	cout<<endl;
	Count_ie_num();//count the number of "if else" or "if else_if else"
	cout<<"if-else num: "<<else_num<<endl;
	cout<<"if-elseif-else num: "<<elseif_num<<endl;
	
	return 0;
}

