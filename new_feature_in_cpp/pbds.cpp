#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using namespace std;

struct node{
    int x,id;
    node(int x=0,int id=0):x(x),id(id){}
};

struct cmp{
    bool operator()(const node &a,const node &b)const{
        return a.x<b.x || (a.x == b.x && a.id < b.id);
    }
};
// null_mapped_type
typedef tree<node, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update> Set;
typedef tree<node, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>::iterator SetIterator;

typedef tree<string, int, greater<string>, rb_tree_tag, tree_order_statistics_node_update> Map;
typedef tree<string, int, greater<string>, rb_tree_tag, tree_order_statistics_node_update>::iterator MapIterator;
void Set_test(){
    Set s;
    s.insert(node(1,1));
    s.insert(node(2,1));
    SetIterator w = s.find_by_order(1); // start from 0
    cout << w->x << " " << w->id << endl;
    cout << s.order_of_key(node(3,1)) << endl; // count nodes < K
    cout << s.order_of_key(node(2,1)) << endl; 
}
# define mp make_pair

void Map_test(){
    Map m;
    m.insert(mp("1111",1));
    m.insert(mp("2222",1));
    MapIterator q = m.find_by_order(1);
    cout << q->first << " " << q->second << endl;
    cout << m.order_of_key("12") << endl;
}
int main(){
    Set_test();
    Map_test();
    return 0;
}
