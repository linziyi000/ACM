#include <bits/stdc++.h>
using namespace std;

int main() {
	char s[233]; scanf("%s",s);
	char pre='a'; int ans=0;
	for(int i=0;s[i];++i) {
		ans+=min(abs(s[i]-pre),26-abs(s[i]-pre));
		pre=s[i];
	}
	printf("%d\n",ans);
	return 0;
}
