#include <bits/stdc++.h>
using namespace std;

int n;

int main() {
	int T; scanf("%d",&T);
	while(T--) {
		char buf[233];
		scanf("%d",&n);
		if(n==1) {
			puts("! 1 1");
			fflush(stdout);
			continue;
		}
		int curmin,curmax;
		puts("? 1 2"); fflush(stdout);
		scanf("%s",buf);
		
		if(buf[0]=='<') curmin=1,curmax=2;
		else curmin=2,curmax=1;
		 
		for(int i=3;i+1<=n;i+=2) {
			printf("? %d %d\n",i,i+1);
			fflush(stdout);  
			scanf("%s",buf);
			int tmin=i,tmax=i+1;
			if(buf[0]=='>') swap(tmin,tmax);
			printf("? %d %d\n? %d %d\n",tmin,curmin,tmax,curmax);
			fflush(stdout);
			scanf("%s",buf); if(buf[0]=='<') curmin=tmin;
			scanf("%s",buf); if(buf[0]=='>') curmax=tmax;
		}
		if(n&1){ printf("? %d %d\n? %d %d\n",n,curmin,n,curmax);
		fflush(stdout);
		scanf("%s",buf); if(buf[0]=='<') curmin=n;
		scanf("%s",buf); if(buf[0]=='>') curmax=n; }
		printf("! %d %d\n",curmin,curmax);
		fflush(stdout);
	}
	return 0;
}
