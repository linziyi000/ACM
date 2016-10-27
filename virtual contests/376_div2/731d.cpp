#include <bits/stdc++.h>
using namespace std;

int n,c;
int l,data[666666];

typedef pair<int,int> pii;
#define pb push_back
#define mp make_pair

vector<pii> ans;

bool cmp(pii a,pii b) { return a.second>b.second; }

int main() {
	scanf("%d%d",&n,&c);
	for(int i=0;i<n;++i) {
		int tl; scanf("%d",&tl);
		int equal=1;
		for(int j=0;j<tl;++j) {
			int x; scanf("%d",&x);
			if(equal && (j>=l || data[j]!=x)) {
				equal=0;
				if(j<l) ans.pb(mp(data[j],x));
			}
			data[j]=x;
		}
		if(equal && tl<l) {
			puts("-1");
			return 0;
		}
		l=tl;
	}
	int min1=0x7fffffff,max2=0; 
	for(pii x:ans) {
		if(x.first>x.second) {
			min1=min(min1,x.first);
			max2=max(max2,x.second); 
		}
	}
	if(max2!=0) {
		sort(ans.begin(),ans.end(),cmp);
		for(pii x:ans) {
			if(x.first<x.second) {
				if(x.second>=min1) min1=min(x.first,min1);
			}
		}
	}
	if(min1<=max2) puts("-1");
	else if(max2==0) puts("0");
	else printf("%d\n",c-min1+1);
	return 0;
}
