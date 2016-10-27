#include <bits/stdc++.h>
using namespace std;

const int maxn=233333;

int n,data[maxn],dp[maxn],sum[maxn];

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",data+i);
	for(int i=1;i<=n;++i)
		sum[i]=sum[i-1]+data[i]; 
	for(int i=n;i>=1;--i) {
		dp[i]=sum[i+1]-dp[i+1];
		if(i+2<=n) dp[i]=max(dp[i],dp[i+1]);
	}
	/*for(int i=1;i<=n;++i) printf("%d ",dp[i]);
	puts("");*/
	printf("%d\n",dp[1]);
	return 0;
}
