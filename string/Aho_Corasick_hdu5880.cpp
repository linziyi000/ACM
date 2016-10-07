# include <bits/stdc++.h>
using namespace std;
const int N = 1000000 + 100 , C = 26 ;
inline int get(char c){
	if (c>='a'&&c<='z') return c-'a';
	if (c>='A'&&c<='Z') return c-'A';
	return 26;
}

struct Aho_Corasick{
	int next[N][C], fail[N], last[N], length[N];
	int cnt, root;
	int ans[N];
	queue<int> q;
	int new_node(){
		cnt++;
		for(int i=0;i<C;i++)
			next[cnt][i] = -1;
		fail[cnt] = last[cnt] = -1;
		length[cnt] = 0;
		return cnt;
	}
	void init(){
		cnt = -1;
		root = new_node();
	}
	void push(char *s){
		int m = strlen(s);
		int now = root;
		for(int i=0;i<m;i++){
			int c = get(s[i]);
			if (next[now][c]==-1)
				next[now][c] = new_node();
			now = next[now][c];
		}
		length[now] = m;
	}

	void getfail(){
		fail[root] = last[root] = root;

		for(int i=0;i<C;i++){
			int &u = next[root][i];
			if (u!=-1){
				fail[u] = last[u] = root;
				q.push(u);
			}else
				u = root;
		}
		
		while(!q.empty()){
			int cur = q.front(); q.pop();
			for(int i=0;i<C;i++){
				int &u = next[cur][i];
				if (u!=-1){
					fail[u] = next[fail[cur]][i];
					q.push(u);
					last[u] = length[fail[u]] ? fail[u]: last[fail[u]];
				}else
					u = next[fail[cur]][i];
			}
		}
	}

	void solve(char *s){
		int now = root;
		for(int i=0;s[i];i++) ans[i] = 0;
		for(int i=0;s[i];i++){
			int c = get(s[i]);
			
			if (c==26) now = now;
			else{
				now = next[now][c];
				int tp = now;
				while(tp != root){
					if (length[tp]){
						ans[i-length[tp]+1] --;
						ans[i+1]++;
					}
					tp = last[tp];
				}
			}
		}
		int tans=0;
		for(int i=0;s[i];i++){
			tans += ans[i];
			if (tans<0) s[i] = '*';
		}

		puts(s);
	}
};
Aho_Corasick AC;

int n;
char s[N];

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d ",&n);
		AC.init();
		for(int i=0;i<n;i++){
			gets(s);
			AC.push(s);
		}
		AC.getfail();
		gets(s);
		AC.solve(s);
	}
	return 0;
}
