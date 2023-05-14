#include<bits/stdc++.h>

using namespace std;

#define read() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define day() time_t now = time(0);char* x = ctime(&now);cerr<<"Right Now Is : "<<x<<"\n"

#define ii pair<int,int>
#define X first
#define Y second 

const long long MAX = (int)2e5 + 5;
const long long INF = (int)1e9;
const long long MOD = (int)1e9 + 7;
const long long Bsize = 450;
// 450

int n,q;
struct node{
	int l,r,id;
	
	bool operator < (const node &a){
		return r < a.r;
	}
};

vector<node> qr[Bsize + 2];
int ans[MAX];
int a[MAX];

struct non{
	int u,v,x,y;
};
stack<non> h;
int uu[Bsize + 2];
bool dd[MAX];
int par[MAX];
int sizz[MAX];
int cnt[MAX];

int find(int u){
	return (u == par[u] ? u : par[u] = find(par[u]));
}
void add(int val){
	
	dd[val] = 1;
	sizz[val] = 1;
	cnt[1]++;
	uu[0]++;

	int u = val + 1;
	int x = find(val);
	int y = find(u);

	h.push({x,y,sizz[x],sizz[y]});
		
	if(sizz[y] != 0){
		par[x] = y;
				
		uu[sizz[x] / Bsize]--;
		uu[sizz[y] / Bsize]--;
		cnt[sizz[x]]--;
		cnt[sizz[y]]--;
		sizz[y] += sizz[x];
		uu[sizz[y] / Bsize]++;
		cnt[sizz[y]]++;
	}
	

	u = val - 1;
	
	x = find(val);
	y = find(u);

	h.push({x,y,sizz[x],sizz[y]});
		
	if(sizz[y] != 0){
		par[x] = y;
				
		uu[sizz[x] / Bsize]--;
		uu[sizz[y] / Bsize]--;
		cnt[sizz[x]]--;
		cnt[sizz[y]]--;
		sizz[y] += sizz[x];
		uu[sizz[y] / Bsize]++;
		cnt[sizz[y]]++;
	}
}
void del(int val){
	
	int u = val - 1;
	
		
	int x = h.top().u;
	int y = h.top().v;
	int xz = h.top().x;
	int yz = h.top().y;
		
	h.pop();
		
	if(yz != 0){
		cnt[xz + yz]--;
		uu[(xz + yz) / Bsize]--;
		sizz[x] = xz;
		sizz[y] = yz;
		cnt[sizz[x]]++;
		cnt[sizz[y]]++;
		uu[sizz[x] / Bsize]++;
		uu[sizz[y] / Bsize]++;
		par[x] = x;
	}
		
	
	
	u = val + 1;
	
	x = h.top().u;
	y = h.top().v;
	xz = h.top().x;
	yz = h.top().y;
		
	h.pop();
		
	if(yz != 0){
		cnt[xz + yz]--;
		uu[(xz + yz) / Bsize]--;
		sizz[x] = xz;
		sizz[y] = yz;
		cnt[sizz[x]]++;
		cnt[sizz[y]]++;
		uu[sizz[x] / Bsize]++;
		uu[sizz[y] / Bsize]++;
		par[x] = x;
	}
	
	//cout<<dd[val]<<" "<<sizz[val]<<'\n';
	
	dd[val] = 0;
	sizz[val] = 0;
	cnt[1]--;
	uu[0]--;
	
}
int get(){
	
	
	for(int i = n / Bsize;i >= 0;i--){
		if(uu[i]){
			
			int f = (i + 1) * Bsize - 1;
			if(f > n)
				f = n;
			for(int j = f;j >= i * Bsize;j--){
				if(j == 0)continue;
				if(cnt[j]){
					return j;
				}
			}
		}
	}
	
}

void print(){
	for(int i = 1;i <= n;i++)cout<<cnt[i]<<" ";
	cout<<'\n';
}
signed main(){
	
	read();
	
	freopen("D.inp","r",stdin);
	freopen("D.out","w",stdout);
	
	cin>>n>>q;
	
	for(int i = 1;i <= n;i++){
		cin>>a[i];
	}	
	
	for(int i = 1,l,r;i <= q;i++){
		cin>>l>>r;
		qr[l / Bsize].push_back({l,r,i});
	}
	
	for(int i = 0;i < Bsize;i++){
		if(qr[i].size()){
			sort(qr[i].begin(),qr[i].end());
		}
	}
	

	for(int i = 0;i <= n / Bsize;i++){
		
		for(int j = 1;j <= n;j++){
			par[j] = j;
			sizz[j] = 0;
			dd[j] = 0;
			cnt[j] = 0;
			uu[j / Bsize] = 0;
		}
		
		while(h.size())h.pop();
		
		int ll = Bsize * (i + 1) - 1;
		for(auto e : qr[i]){
			int l = e.l;
			int r = e.r;
			int id = e.id;
			
			if(r / Bsize == l / Bsize){
				
				for(int j = l;j <= r;j++)add(a[j]);
				ans[id] = get();
				for(int j = r;j >= l;j--)del(a[j]);
				
			}else{
				
				while(ll < r)add(a[++ll]);
				
				int clii = Bsize * (i + 1);
				if(clii > n + 1)clii = n + 1;
				for(int j = l;j < clii;j++){
					add(a[j]);
				}

				ans[id] = get();
				
				clii = Bsize * (i + 1);
				if(clii > n + 1)clii = n + 1;
				for(int j = clii - 1;j >= l;j--){
					del(a[j]);
				}
				
			}
		}
		
	}
	
	
	for(int i = 1;i <= q;i++)cout<<ans[i]<<"\n";
	 
	
}
























