#include<bits/stdc++.h>
#include<iostream>
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
		for(int j=8;j>=2;j--){
			if(match(s.substr(i,j))){
				i+=j-1;
				break;
			}
		}		
	}
}

inline void sepcial_check(string s)
{
	int len=s.size();
	s+="$$$$";
	int temp_if=0,temp_else=0;
	for(int i=0;i<len;i++){
		if(s.substr(i,2)=="if")temp_if++;
		if(s.substr(i,4)=="else")temp_else++;
	}
	if(temp_else && temp_if==temp_else){
		ie.pop_back();ie.pop_back();
		ie.push_back("else_if");
		//Replace "else" "if" with "else_if"
	}
}
inline void Count_ie_num()
{
	vector<string>::iterator it=ie.begin();
	it++;
	while(it!=ie.end()){
		if(*it=="else_if" && *it==*(it-1))ie.erase(it);
		else it++;
	}
	it=ie.begin();
	it++;
	while(it!=ie.end()){
		if(*it=="else_if"){
			elseif_num++;
			ie.erase(it);
		}
		else it++;
	}
	else_num=(ie.size()>>1);
	else_num-=elseif_num;
}

int main()
{
	freopen("input.txt","r",stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	string s;
	while(getline(cin,s)){
		check(s);
		sepcial_check(s);
	}
	
	if(case_num)Swich.push_back(case_num);
	cout<<"total num: "<<tot_num<<endl;
	cout<<"switch num: "<<Swich.size()<<endl;
	cout<<"case num: ";
	for(int i=0;i<Swich.size();i++){
		if(i!=Swich.size()-1)cout<<Swich[i]<<" ";
		else cout<<Swich[i]<<endl;
	}
	Count_ie_num();
	cout<<"if-else num: "<<else_num<<endl;
	cout<<"if-elseif-else num: "<<elseif_num<<endl;
		
	return 0;
}

