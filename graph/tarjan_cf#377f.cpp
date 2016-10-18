# include <bits/stdc++.h>
using namespace std;
const int N = 400000 + 100;

template <int maxv,int maxe>
class graph {
public:
    struct {
        int v,w,next,inv,flag;
    } edge[maxe<<1];

    struct{
        int s,e;
    } oreinted_path[N];
    int head[maxv],top;
    int v,e;
    void init() {
        memset(head,-1,sizeof(head));
        top=0;
    }
    int addedge(int x,int y,int w=1) {
        edge[top].v=y;
        edge[top].w=w;
        edge[top].next=head[x];
        edge[top].flag=0;
        return head[x]=top++;
    }
    int dfn[maxv],low[maxv],t;
    void tarjan(int p,int prev=-1) {
        dfn[p]=low[p]=t++;
        for(int i=head[p];~i;i=edge[i].next) {
            int np=edge[i].v;
            if(np==prev) continue;
            if(dfn[np]) 
                low[p]=min(low[p],dfn[np]);
            else {
                tarjan(np,p);
                low[p]=min(low[p],low[np]);
                if(low[np]>dfn[p]) {
                    edge[i].flag=1;
                    edge[edge[i].inv].flag=1;
                }
            }
        }
    }
    void tarjan() {
        memset(dfn,0,sizeof(dfn)); t=1;
        for(int i=1;i<=v;++i) 
            if(!dfn[i]) tarjan(i);
    }
    int nn=1,degree[N],scc[N];
    void dfs(int p) {
        for(int i=head[p];~i;i=edge[i].next) {
            int np=edge[i].v;
            if(scc[np]) continue;
            if(edge[i].flag) {
                scc[np]=++nn;
                ++degree[nn];
                ++degree[scc[p]];
            }
            else scc[np]=scc[p];
            dfs(np);
        }
    }

    int mark[N];
    int vis[N];

    void dfs_v(int p){
        vis[p] = 1;
        for(int i=head[p];~i;i=edge[i].next) {
            int np=edge[i].v;
            if (!mark[edge[i].w]){
                mark[edge[i].w] = 1;
                oreinted_path[edge[i].w].e = p;
                oreinted_path[edge[i].w].s = np;
            }
            if (vis[np]) 
                continue;
            else
                dfs_v(np);
        }
    }

    void oreinted(int k){
        int q;
        for(int i=1;i<=v;i++) {
            if (scc[i] == k) q=i;
            mark[i] = 0;
            vis[i] = 0;
        }
        dfs_v(q);
        printf("%d\n",cc[k]);
        for(int i=0;i<e;i++){
            printf("%d %d\n",oreinted_path[i].s,oreinted_path[i].e);
        }
    }

    int cc[N];

    void work(){
        tarjan();
        scc[1]=1;
        dfs(1);
        int c=1;
        for(int i=1;i<=v;i++)
            cc[scc[i]]++;
        for(int i=1;i<=nn;++i) 
            if (cc[i]>cc[c])
                c = i;
        oreinted(c);
    }
};

graph<N,N> g1;





int main() {
    g1.init();
    scanf("%d%d",&g1.v,&g1.e);
    for(int i=0;i<g1.e;++i) {
        int x,y;
        scanf("%d%d",&x,&y);
        int xx=g1.addedge(x,y,i),yy=g1.addedge(y,x,i);
        g1.edge[xx].inv=yy;
        g1.edge[yy].inv=xx;
    }

    g1.work();
    
    return 0;
}