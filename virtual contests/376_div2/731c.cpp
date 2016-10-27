#include <bits/stdc++.h>
using namespace std;

const int maxe=233333,maxv=233333;
typedef pair<int,int> pii;

struct {
	int v,next;
} edge[maxe << 1];
int head[maxv],top;
int n,m,k,c[maxv];
inline void init() {
	memset(head,-1,sizeof(head));
	top=0;
}
inline void adde(int x,int y) {
	edge[top].v=y;
	edge[top].next=head[x];
	head[x]=top++;
}
map<int,int> cnt;

int vis[maxv];
void dfs(int p) {
	if(vis[p]) return;
	vis[p]=1;
	cnt[c[p]]++;
	for(int i=head[p];~i;i=edge[i].next) 
		dfs(edge[i].v); 
}

int main() {
	scanf("%d%d%d",&n,&m,&k);
	init();
	for(int i=1;i<=n;++i) scanf("%d",c+i);
	for(int i=0;i<m;++i) {
		int x,y; scanf("%d%d",&x,&y);
		adde(x,y); adde(y,x);
	}
	int ans=0;
	for(int i=1;i<=n;++i) {
		if(!vis[i]) {
			cnt.clear();
			dfs(i);
			int maxval=0,sum=0;
			for(pii x:cnt) {
				maxval=max(maxval,x.second);
				sum+=x.second;
			}
			ans+=sum-maxval;
		}
	}
	printf("%d\n",ans);
	return 0;
}
