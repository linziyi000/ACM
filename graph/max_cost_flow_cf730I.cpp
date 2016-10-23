# include <bits/stdc++.h>
using namespace std;
const int N = 3333, INF = N*2;
struct edge{
	int t,next,c,w;
}e[N<<3];

int head[N], cnt;
void init(){
	memset(head,-1,sizeof(head));
	cnt = 0;
}
inline void add(int s,int t,int c,int w){
	e[cnt] = (edge){t, head[s], c,  w}; head[s] = cnt++;
	e[cnt] = (edge){s, head[t], 0, -w}; head[t] = cnt++;
}
int a[N], b[N];
int n,p,s;
int work[N];
int S,E;
int dis[N], mark[N];

int spfa(){
	queue<int> q;
	for(int i=1;i<=E;i++) dis[i] = -0x3f3f3f3f;
	memset(mark,0,sizeof(int) * (E + 5));
	dis[S] = 0;
	mark[S] = 1;
	q.push(S);

	
	for(int x=q.front();!q.empty(); q.pop()){
		x=q.front();
		for(int i=head[x];~i;i=e[i].next){
			if (e[i].c && dis[e[i].t] < dis[x] + e[i].w){
				dis[e[i].t] = dis[x] + e[i].w;
				if (!mark[e[i].t]){
					mark[e[i].t] = 1;
					q.push(e[i].t);
				}
			}
		}
		mark[x] = 0;
	}
	return dis[E] >= -1;
}


int dinic(int x,int low){
	if (x==E)
		return low;
	mark[x] = 1;
	
	int a;
	for(int &i=work[x];~i;i=e[i].next){
		int u = e[i].t;
		if (!mark[u] && e[i].c && dis[u] == dis[x] + e[i].w){
			if ( ( a=dinic(u,  min(e[i].c, low) ) ) > 0){
				e[i].c -= a;
				e[i^1].c += a;
				
				return a;
			}
		}
	}
	mark[x] = 0;
	return 0;
}

int max_cost_flow(){
	int sum = 0, a;
	while(spfa()){
		memcpy(work, head, sizeof(int) * (E + 5));
		memset(mark, 0, sizeof(int) * (E + 5));
		while((a=dinic(S, INF))) {
			sum += dis[E];
			memset(mark, 0, sizeof(int) * (E + 5));
			//cout << "0" <<endl;
		}
			
	}
	return sum;
}

int main(){
	while(~scanf("%d%d%d",&n,&p,&s)){
		for(int i=1;i<=n;i++) scanf("%d",a+i);
		for(int i=1;i<=n;i++) scanf("%d",b+i);
		init();
		S = 0; E = n+3;
		add(S, n+1, p, 0);
		add(S, n+2, s, 0);
		for(int i=1;i<=n;i++){
			add(n+1, i, 1, a[i]);
			add(n+2, i, 1, b[i]);
			add(i, E, 1, 0);
		}

		printf("%d\n",max_cost_flow());
		for(int i=head[n+1];~i;i=e[i].next)
			if (e[i].c == 0 && e[i].t) printf("%d ",e[i].t);
		puts("");
		for(int i=head[n+2];~i;i=e[i].next)
			if (e[i].c == 0 && e[i].t) printf("%d ",e[i].t);
		puts("");
	}
	return 0;
}
