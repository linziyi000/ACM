#include <bits/stdc++.h>
using namespace std;

const int maxn=6666,maxe=23333;

typedef long long ll;
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;

int n,m,w;
struct {
	int v,next;
} edge[maxe];
int head[maxn],top;
vector<pii> market[maxn];
inline void init() {
	memset(head,-1,sizeof(head));
	top=0;
}
inline void adde(int x,int y) {
	edge[top].v=y;
	edge[top].next=head[x];
	head[x]=top++;
}

int dis[maxn];
int main() {
	init();
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;++i) {
		int x,y; scanf("%d%d",&x,&y);
		adde(x,y); adde(y,x);
	}
	scanf("%d",&w);
	for(int i=0;i<w;++i) {
		int c,k,p; scanf("%d%d%d",&c,&k,&p);
		market[c].pb(mp(p,k));
	}
	int q;
	scanf("%d",&q);
	while(q--) {
		int g,r,a; scanf("%d%d%d",&g,&r,&a);
		queue<int> q; q.push(g);
		priority_queue<pii> pq;
		ll money=0;
		int tot=0;
		int ans=-1;
		memset(dis,-1,sizeof(dis));
		dis[g]=0;
		while(!q.empty()) {
			int cur=q.front(); q.pop();
			for(pii x : market[cur]) {
				pq.push(x);
				money+=(ll)x.first*x.second;
				tot+=x.second;
			}
			while(tot>r) {
				pii cur=pq.top(); pq.pop();
				if(tot-cur.second>=r) {
					tot-=cur.second;
					money-=(ll)cur.first*cur.second;
				}
				else {
					pq.push(mp(cur.first,cur.second-(tot-r)));
					money-=(ll)cur.first*(tot-r);
					tot=r;
				}
			}
			if(tot>=r&&money<=a) {
				ans=dis[cur];
				break;
			}
			for(int i=head[cur];~i;i=edge[i].next) {
				int np=edge[i].v;
				if(!~dis[np]) {
					dis[np]=dis[cur]+1;
					q.push(np);
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
