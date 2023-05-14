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

int n,q;
struct node{
	int l,r,id;
	
	bool operator < (const node &a){
		return (l / Bsize == a.l / Bsize) ? (r < a.r) : (l / Bsize < a.l / Bsize);
	}
};

vector<node> query;
int ans[MAX];
int st[MAX << 2][2];
int lazy[MAX << 2][2];
int a[MAX];

void lazyupdate(int id,int l,int r,bool c){
	if(lazy[id][c] == 0)return;
	
	st[id][c] += lazy[id][c];
	if(l != r){
		lazy[id << 1][c] += lazy[id][c];
		lazy[id << 1 | 1][c] += lazy[id][c];
	}
	lazy[id][c] = 0;
}
void update(int u,int v,int val,bool c,int id = 1,int l = 1,int r = n){
	
	if(u > v)return;
	lazyupdate(id,l,r,c);
	if(u > r || v < l)return;
	if(u <= l && r <= v){
		lazy[id][c] += val;
		lazyupdate(id,l,r,c);
		return;
 	}
 	int m = l + r >> 1;
 	update(u,v,val,c,id << 1,l,m);
 	update(u,v,val,c,id << 1 | 1,m + 1,r);
 	st[id][c] = max(st[id << 1][c],st[id << 1 | 1][c]);
}

int get(int u,int v,bool c,int id = 1,int l = 1,int r = n){
	lazyupdate(id,l,r,c);
	if(u > r || v < l)return 0;
	if(u <= l && r <= v)return st[id][c];
	int m = l + r >> 1;
	return max(get(u,v,c,id << 1,l,m),get(u,v,c,id << 1 | 1,m + 1,r));
}

int L = 1,R = 1;

void add(int id){

	int u = a[id];
	
	int r = 0,l = 0;
	if(u < n)
		r = get(u + 1,u + 1,0);
	if(u > 1)
		l = get(u - 1,u - 1,1);
	
	
	update(u - l,u,r + 1,0);
	update(u,u + r,l + 1,1);
}

void del(int id){
	int u = a[id];
	
	int r = 0,l = 0;
	if(u < n)
		r = get(u + 1,u + 1,0);
	if(u > 1)
		l = get(u - 1,u - 1,1);
	
	//cout<<l<<" "<<r<<' '<<id<<'\n';
	update(u - l,u,-r - 1,0);
	update(u,u + r,-l - 1,1);
	
}
signed main(){
	
	read();
	
	freopen("D.inp","r",stdin);
	freopen("D.ans","w",stdout);
	
	cin>>n>>q;
	
	for(int i = 1;i <= n;i++){
		cin>>a[i];
	}	
	
	
	/*for(int i = 1;i <= n;i++){
		add(i);
		cout<<a[i]<<" \n";
		for(int j = 1;j <= n;j++){
			cout<<get(j,0)<<" ";
		}
		cout<<"\n";
		for(int j = 1;j <= n;j++){
			cout<<get(j,1)<<" ";
		}
		
		cout<<"\n\n";
	}
	
	
	for(int i = 1;i <= n;i++){
		del(i);
		cout<<a[i]<<" \n";
		for(int j = 1;j <= n;j++){
			cout<<get(j,0)<<" ";
		}
		cout<<"\n";
		for(int j = 1;j <= n;j++){
			cout<<get(j,1)<<" ";
		}
		
		cout<<"\n\n";
	}*/
	
	for(int i = 0;i < MAX;i++){
		st[i][0] = 0;
		st[i][1] = 0;
	}
	for(int i = 1,l,r;i <= q;i++){
		cin>>l>>r;
		query.push_back({l,r,i});
	}
	
	sort(query.begin(),query.end());
	
	
	add(1);
	for(auto e : query){
		int l = e.l;
		int r = e.r;
		int id = e.id;
		
		while(L < l)del(L++);
		while(L > l)add(--L);
		while(R < r)add(++R);
		while(R > r)del(R--);
		
		ans[id] = max(get(1,n,0),get(1,n,1));
		
	}
	
	for(int i = 1;i <= q;i++)cout<<ans[i]<<"\n";
	 
	
}
