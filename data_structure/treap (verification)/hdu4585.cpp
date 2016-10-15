#include <bits/stdc++.h>
using namespace std;

#define MAXN 233333 

int n,k[5000010];

// insert(x) : 插入x，如果已经存在返回false，否则返回true
// count(x) : <=x的元素共有多少个
// k_th(x) : 第k个是几，下标1起，x<=0||x>n均返回-1。
// del(x) : 删除x，成功删除返回true，否则false。 
struct node {
	int l,r,key,fix,size;
};
struct treap {
    node h[MAXN];
    int root,num;
    void init() { srand(time(0)); num=root=0; }
    void rot_l(int &x) {
    	int R=h[x].r,L=h[x].l; 
        h[x].size=h[x].size-h[R].size+h[h[R].l].size;
        h[R].size+=h[L].size+1;
        h[x].r=h[R].l,h[R].l=x;
        x=R;
    }
    void rot_r(int &x) {
    	int L=h[x].l,R=h[x].r;
        h[x].size=h[x].size-h[L].size+h[h[L].r].size;
        h[L].size+=h[R].size+1;
        h[x].l=h[L].r,h[L].r=x;
        x=L; 
	}
	bool insert(int key) { return insert(root,key); }
    bool insert(int &k,int key) {
        if (!k) {
            k=++num;
            h[k].l=h[k].r=0,h[k].size=1;
            h[k].key=key,h[k].fix=rand();
            return true;
        }
        if (h[k].key==key) return false;
        if (h[k].key>key) {
            if (!insert(h[k].l,key)) return false;
            h[k].size++;
            if (h[h[k].l].fix>h[k].fix) rot_r(k); 
            return true;
        } 
		else {
            if (!insert(h[k].r,key)) return false;
            h[k].size++;
            if (h[h[k].r].fix>h[k].fix) rot_l(k); 
            return true;
        }
    }
	int count(int key) { 
        int g=0,k=root;
        while (k) {
            if (h[k].key>key) k=h[k].l;
            else g+=h[h[k].l].size+1,k=h[k].r;
    	}
        return g;
    }
    int k_th(int kth) { 
        int g=0,k=root;
        if (h[root].size<kth || kth<=0) return -1; 
        while (h[h[k].l].size+g+1!=kth)
        {
            if (h[h[k].l].size+g+1>=kth) k=h[k].l;
            else g+=h[h[k].l].size+1,k=h[k].r;
        }     
        return h[k].key;          
	}
	bool del(int key) { return del(root,key); }
	bool del(int &k,int key) { 
        if (!k) return false;
        if (h[k].key>key) {
            if (!del(h[k].l,key)) return false;
            h[k].size--; 
        }
        else if (h[k].key<key) {
            if (!del(h[k].r,key)) return false;
            h[k].size--;  
        }
        else {
            if (!h[k].l && !h[k].r) k=0;
            else if (!h[k].l) k=h[k].r; 
            else if (!h[k].r) k=h[k].l;
            else if (h[h[k].l].fix<h[h[k].r].fix) {
                rot_l(k);
                if (!del(h[k].l,key)) return false;
                h[k].size--;
            }  
			else {
			    rot_r(k);
                if (!del(h[k].r,key)) return false;
                h[k].size--;
		    } 
        }
    	return true;
    }       
} mytreap;


int main() {
	const int inf=1000000000;
	while(scanf("%d",&n),n) {
		mytreap.init();
		mytreap.insert(inf);
		for(int i=1;i<=n;++i) {
			int x,y; scanf("%d%d",&x,&y);
			k[y]=x; mytreap.insert(y);
			int ord=mytreap.count(y);
			int t1=mytreap.k_th(ord-1),t2=mytreap.k_th(ord+1);
			printf("%d ",x);
			if(t1==-1) printf("%d\n",t2==inf?1:k[t2]);
			else if(t2==-1) printf("%d\n",k[t1]);
			else printf("%d\n",t2-y>=y-t1?k[t1]:k[t2]);
			//printf("%d\n",ord); 
		}
	}
	return 0;
}
