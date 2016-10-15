# include <bits/stdc++.h>
# include <ext/rope>
using namespace std;
using namespace __gnu_cxx;

int main(){
    char s[] = "123456";
    rope<char> *r = new rope<char>(s, 7);
    r->replace(3, "7"); // replace
    cout << *r << endl;
    r->insert(4,"456465"); // insert
    cout << *r << endl; 
    r->erase(4,5); // delete  st, length
    cout << *r << endl;

    rope<char> *q = new rope<char>(*r);
    cout << *q << endl;
    rope<char> p = *q + *r ;  // add
    cout << p << endl;
    return 0;
}
