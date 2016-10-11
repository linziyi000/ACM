#include <bits/stdc++.h>
using namespace std;

const int maxlen=3000;
int n,data[maxlen];
struct bigint {
	int data[maxlen];
	void mul(int b) {
		for(int i=0;i<maxlen;++i)
			data[i]*=b;
		for(int i=0;i<maxlen-1;++i) {
			data[i+1]+=data[i]/10;
			data[i]%=10;
		}
	}
	int div(int b) {
		int rem=0;
		for(int i=maxlen-1;i>=0;--i) {
			rem=rem*10+data[i];
			data[i]=rem/b;
			rem%=b;
		} 
		return rem;
	}
	void out() {
		int flg=0;
		for(int i=maxlen-1;i>=0;--i) 
			if(flg|=data[i]) printf("%d",data[i]);
		if(!flg) putchar('0');
	}
} ans;

void C(int x,int y) {
	y=min(y,x-y);
	for(int i=0;i<y;++i)
		ans.mul(x-i);
	for(int i=0;i<y;++i)
		ans.div(i+1); 
}

int main() {
	scanf("%d",&n);
	ans.data[0]=1;
	int rem=n-2,t=n;
	for(int i=1;i<=n;++i) {
		int x;
		scanf("%d",&x);
		if(~x) {
			C(rem,x-1);
			rem-=x-1;
			--t;
		}
	}
	while(rem-->0) ans.mul(t);
	ans.out();
	return 0;
}
