#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn=233333;
#define pb push_back


ll r;
int n;
int l[maxn],t[maxn];
vector<ll> ans;

int main() {
	scanf("%d%I64d",&n,&r); 
	for(int i=1;i<=n;++i) scanf("%d",l+i);
	for(int i=1;i<=n;++i) scanf("%d",t+i);
	ll med=0,t=0,fail=0,tot=0;
	for(int i=1;i<=n && !fail;++i) {
		if(med>=l[i]) {
			med-=l[i];
			t+=l[i];
		}
		else {
			int tl=l[i],tt=::t[i];
			if(med>0) {
				tl-=med; tt-=med; t+=med; med=0;
			}
			int medtime=(2*tl-tt);
			if(medtime>tt) 
				fail=1;
			else if(medtime>0) {
				tot+=(medtime+r-1)/r;
				//ans.pb(t+tt-medtime);
				med=(medtime+r-1)/r*r-medtime;
				t+=tt;
			}
			else t+=tl*2;
		}
	}
	if(!fail && tot<=100000) {
		med=0; t=0; fail=0; tot=0;
		for(int i=1;i<=n && !fail;++i) {
			if(med>=l[i]) {
				med-=l[i];
				t+=l[i];
			}
			else {
				int tl=l[i],tt=::t[i];
				if(med>0) {
					tl-=med; tt-=med; t+=med; med=0;
				}
				int medtime=(2*tl-tt);
				if(medtime>tt) 
					fail=1;
				else if(medtime>0) {
					tot+=(medtime+r-1)/r;
					t+=tt-medtime;
					for(ll j=0;j<medtime;j+=r)
						ans.pb(t+j); 
					med=(medtime+r-1)/r*r-medtime;
					t+=medtime;
				}
				else {
					t+=tl*2;
				}
			}
		}
	}
	if(fail) puts("-1");
	else {
		printf("%I64d\n",tot);
		if(tot<=1000000)
			for(ll x:ans) printf("%I64d ",x);
		puts(""); 
	}
	return 0;
}
