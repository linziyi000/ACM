#include <bits/stdc++.h>
using namespace std;

char s[233][233];
char tmp[233];
char flg[233];
int n,m;

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%s",s[i]);
	int fail=0;
	for(int i=1;i<=m;++i) {
		int x; scanf("%d",&x);
		flg[x]=1;
		if(i==1) strcpy(tmp,s[x]);
		else {
			if(strlen(s[x])!=strlen(tmp)) {
				fail=1;
				break;
			}
			for(int j=0;s[x][j];++j)
				if(tmp[j]!='?' && tmp[j]!=s[x][j])
					tmp[j]='?';
		}
	}
	if(fail) {
		puts("No");
		return 0;
	}
	for(int i=1;i<=n;++i) if(!flg[i]) {
		if(strlen(s[i])!=strlen(tmp)) continue;
		int suc=1;
		for(int j=0;s[i][j] && suc;++j)
			if(tmp[j]!='?' && tmp[j]!=s[i][j])
				suc=0;
		if(suc) {
			fail=1;
			break;
		}
	}
	if(fail) {
		puts("No");
		return 0;
	}
	puts("Yes");
	puts(tmp);
	return 0;
}
