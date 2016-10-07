#include <bits/stdc++.h>
using namespace std;
const int N = 200000 + 100;
const int C = 27;
typedef long long ll;
const char zz = 'z'+1;
struct State{
    State* go[C];
    State* parent;
    int l,len;
    State* extend(int ,int );
};

State statepool[N << 1];
State *cur, *last, *root, *b[N<<1];

State* new_state(int l, int len){
    memset(cur->go,0,sizeof(cur->go));
    cur->parent = NULL;
    cur->l = l;
    cur->len = len;
    return cur++;
}

State* State::extend(int c, int len){
    State* p =this;
    State* np=new_state(p->l+1, len);
    
    while( p && !p->go[c]){
        p->go[c] = np;
        p = p->parent;
    }
    
    if (!p) np->parent = root;
    else{
        State* q = p->go[c];
        if (q->l == p->l+1) np->parent = q;
        else{
            State* nq = new_state( p->l+1, len);
            memcpy( nq->go , q->go , sizeof(q->go));
            nq->parent = q->parent;
            np->parent = q->parent = nq;
            while( p && p->go[c]==q){
                p->go[c] = nq;
                p = p->parent;
            }
        }
    }
    return np;
}


void init(){
    cur = statepool;
    root = last = new_state(0, 0);
}

char s[N],t[N];
int pos,n,m;
int cnt[N<<1];

void build(){
    init();
    int len = 0;
    for(int i=0;i<pos;i++){
        len = s[i]==zz ? 0: len+1;
        last = last->extend(s[i]-'a', len);
    }
}
  
int calc(char *s){
    State *p = root;
    for(int i=0;s[i];i++){
        p = p->go[s[i] - 'a'];
        if (!p) return 0;
    }
    return min( p->l , p->len) - p->parent->l;
}

int main(){
    int T;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        pos = 0;
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++){
            scanf("%s",s+pos);
            pos += strlen(s+pos);
            s[pos++] = zz;
        }
        build();
        
        printf("Case #%d:\n",cas);
        while(m--){
            scanf("%s",t);
            printf("%d\n",calc(t));
        }
    }
    return 0;
}