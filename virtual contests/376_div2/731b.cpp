#include <bits/stdc++.h>
using namespace std;

int n,data[233333];

int main() {
	scanf("%d",&n);
	int fail=0;
	for(int i=1;i<=n;++i)
		scanf("%d",data+i);
	for(int i=1;i<=n && !fail;++i) {
		if(data[i]&1) {
			if(i==n || data[i+1]==0)
				fail=1;
			else --data[i], --data[i+1];
		}
	}
	puts(fail?"NO":"YES");
	return 0;
}
