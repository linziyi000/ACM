#include <bits/stdc++.h>
using namespace std;

const int maxn=233333;
typedef long long ll;

int rec[maxn],sum[maxn];

int main() {
	int n; scanf("%d",&n);
	for(int i=0;i<n;++i) {
		int x; scanf("%d",&x);
		++rec[x];
	}
	for(int i=1;i<=200000;++i)
		sum[i]=sum[i-1]+rec[i];
	ll ans=0;
	for(int i=1;i<=200000;++i) if(rec[i]) {
		ll tans=0;
		for(int j=i;j<=200000;j+=i)
			tans+=(ll)(sum[min(j+i-1,200000)]-sum[j-1])*j;
		ans=max(ans,tans);
	}
	printf("%I64d\n",ans);
	return 0;
}
