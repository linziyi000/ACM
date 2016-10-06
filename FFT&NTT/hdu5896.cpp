// NTT + CDQ

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P = 1004535809;
const int N = 6e5, M = 524288;

int pow_mod(int a,ll b=P-2,int mod=P){
    ll x = a, ans = 1;
    if (a==1) return 1;
    do{
        if (b&1) ans=ans*x%mod;
        x=x*x%mod;
    }while(b>>=1);
    return ans;
}

int find_primitive_number(int p){
    int fac[20],m=0;
    int q=p-1;
    for(int i=2;i<=q;i++)
    if (q%i==0){
        fac[m++] = i;
        while(q%i==0) q/=i;
    }
    q = p-1;
    for(int g=2;;g++){
        int flg = 1;
        for(int i=0;i<m;i++){
            if (pow_mod(g,q/fac[i],p)==1){
                flg = 0; break;
            }
        }
        if (flg) return g;
    }
    return 1;
}

struct F{
    int x;
    F(int _x=0):x(_x){}
 	
    F operator*(const F& tt)const{
        return F( (int) ( (ll)x * tt.x % P ) );
    }
    F operator+(const F& tt)const{
        F ans(x+tt.x);
        if (ans.x>=P)
            ans.x -= P;
        return ans;
    }
    F operator-(const F& tt)const{
        F ans(x-tt.x);
        if (ans.x<0)
            ans.x += P;
        return ans;
    }
    F ni(){
        return F(pow_mod(x, P-2));
    }
};

const int GP = find_primitive_number(P);

void ntt(F y[],int len,int on){
    for(int i = 1, j = len >> 1; i < len -1; i++){
        if (i < j) swap(y[i], y[j]);
        int k = len >> 1;
        while(j >= k){
            j -= k;
            k >>= 1;
        }
        j += k;
    }

    int gp = pow_mod(GP, (P-1) / len);

    for(int i=2; i <= len; i <<= 1){
        F gn = F(pow_mod(gp, len / i));
        if (on == -1) gn = gn.ni();
        for(int j=0;j<len;j+=i){
            F g = F(1);
            for(int k = j; k < j+ (i>>1); k++){
                F u = y[k];
                F t = g * y[ k + (i>>1) ];
                y[k] = u + t;
                y[k + (i>>1)] = u - t;
                g = g * gn;
            }
        }
    }

    if (on == -1){
        F ni( pow_mod(len, P-2) );
        for(int i = 0; i < len; i++) y[i] = y[i]*ni;
    }
}

int a[N], b[N], n;
int f[N], h[N];
ll rev[N],fac[N];

void init(){
	fac[0] = 1;
	rev[0] = 1;
	int n = M;
	for(int i=1;i<=n;i++){
		h[i] = pow_mod(i,i-2)*(ll)pow_mod(fac[i-1]) % P;
		fac[i] = fac[i-1]*(ll)i % P;
		rev[i] = pow_mod(i);
	}
}

void solve(int l,int r){
	if (l==r){
		f[l] = (ll)f[l]*rev[l] % P;
		return;
	}
	int mid = (l+r) >> 1;
	solve(l, mid);
	int len = 1;
	while(len <= r-l) len <<= 1;

	for(int i=0;i<len;i++) 
		a[i] = b[i] = 0;
	for(int i=l;i<=mid;i++)
		a[i-l] = f[i];
	for(int i=1;i<=r;i++)
		b[i-1] = h[i];

	ntt((F*)a, len, 1);
	ntt((F*)b, len, 1);
	for(int i=0;i<len;i++)
		a[i] = (ll)a[i] * b[i] % P;
	ntt((F*)a, len, -1);

	for(int i=mid+1;i<=r;i++)
		f[i] = (f[i] + a[i-l-1]) % P;
	
	solve(mid+1, r);
}

int main(){
	init();
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		memset(f,0,sizeof(f));
        f[0] = 1;
		solve(0,n);
        ll ans = f[n]*fac[n]%P;
        ans = pow_mod(2,(ll)n*(n-1)/2) - ans + P;
        ans %= P;
		printf("%d\n",ans);
	}
	return 0;
}
