#include<bits/stdc++.h>

using namespace std;

#define read() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define day() time_t now = time(0);char* x = ctime(&now);cerr<<"Right Now Is : "<<x<<"\n"

#define ii pair<int,int>
#define X first
#define Y second 

const long long MAX = (int)3e5 + 5;
const long long INF = (int)1e9;
const long long MOD = (int)1e9 + 7;
const long long Bsize = 450;
const string NAME = "D";

int ran(int l,int r){
	return rand() % (r - l + 1) + l;
}
void maketest(){
	
	ofstream inp((NAME + ".inp").c_str());
	
	int n = rand() % 1000 + 10;

	
	int m = rand() % 10;
	
	inp << n <<" "<<m<<'\n';
	vector<int> a(n + 1);
	
	
	for(int i = 1;i <= n;i++)a[i] = i;
	
	
	for(int i = 1;i <= 1000;i++){
		int l = ran(1,n - 1);
		int r = ran(l + 1,n);
		
		swap(a[l],a[r]);
	}
	
	for(int i = 1;i <= n;i++){
		inp << a[i] << " ";
	}
	inp << "\n";
	
	for(int i = 1;i <= m;i++){
		int l = ran(1,n - 1);
		int r = ran(l + 1,n);
		
		inp << l << " " << r << "\n";
	}
	
}
signed main(){
	
	srand(time(0));
	
	for(int i = 1;i < 1000;i++){
		
		maketest();
		
		system((NAME + "full.exe").c_str());
		system((NAME + "sub.exe").c_str());
		
		if(system(("fc " + NAME + ".out " + NAME + ".ans").c_str()) != 0){
			cout << "TEST " << i << ": WRONG\n";
			return 0;
		}
		
		cout<< " TEST" << i <<" : CORRECT\n";
	}
	
}
