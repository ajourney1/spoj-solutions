#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
typedef long long ll;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#define ios ios_base::sync_with_stdio(0) ; cin.tie(0) ; cout.tie(0)
#define so sizeof
#define pb push_back
#define cl clear() ;
#define vl vector<ll>
#define sz size()
#define len length()
#define emp empty()
#define el endl;cout.flush()
#define be begin()
#define fi first
#define se second
#define br break
#define en end()
#define ro return 0
#define br break
#define eb emplace_back
#define con continue
#define ms(x) memset(x , 0, so x)
#define all(x) (x).be , (x).en
#define acc(x) accumulate((x).be , (x).en , 0ll)
#define forn(i,a,b) for(ll i=a;i<=b;++i)
#define rng_58 mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define vll vector<pair<ll,ll> >
#define pll pair<ll,ll>
#define plll pair<ll,pair<ll,ll>>
#define plvl pair<pair<ll,ll> ,ll>
#define mp make_pair
#define trace3(a,b,c) cerr <<"a is " << a << " b is " << b << " c is " << c << el;
#define trace4(a,b,c,d) cerr <<"a is " << a << " b is " << b << " c is " << c <<" d is " << d << el ;
#define trace5(a,b,c,d,e) cerr <<"a is " << a << " b is " << b << " c is " << c <<" d is " << d << " e is " << e << el;
#define trace6(a,b,c,d,e,f) cerr <<"a is " << a << " b is " << b << " c is " << c <<" d is " << d << " e is " << e << " f is " << f << el ;

/// https://www.spoj.com/problems/FREQUENT/

struct Tree
{
    ll maxxfreq ;
    ll eleleft ;
    ll eleright;
    ll longpreflen;
    ll longsufflen;
    Tree(){};
};
const ll maxx = 100005;
ll arr[maxx] ;
Tree trees[4*maxx] ;
const ll minn = -1e18 ;
const ll maxxx = 1e18;
void build(ll low , ll high , ll node)
{
    if(low == high){
        trees[node].maxxfreq = 1;
        trees[node].eleleft = arr[low];
        trees[node].eleright= arr[low];
        trees[node].longpreflen= 1 ;
        trees[node].longsufflen = 1;
        return ;
    }
    ll mid = (low + high ) / 2 ;
    build(low , mid , 2*node + 1);
    build(mid+1 , high , 2*node + 2) ;
    trees[node].eleleft = trees[2*node + 1].eleleft;
    trees[node].eleright= trees[2*node + 2].eleright;
    if(trees[2*node+1].eleleft != trees[2*node+1].eleright){
        trees[node].longpreflen = trees[2*node+1].longpreflen ;
    }
    if(trees[2*node+2].eleleft != trees[2*node+2].eleright){
        trees[node].longsufflen = trees[2*node+2].longsufflen;
    }
    if(trees[2*node+1].eleleft == trees[2*node+1].eleright){
        if(trees[2*node+1].eleright != trees[2*node+2].eleleft){
            trees[node].longpreflen = trees[2*node+1].longpreflen ;
        }
        if(trees[2*node+1].eleright == trees[2*node+2].eleleft){
            trees[node].longpreflen = trees[2*node+1].longpreflen + trees[2*node+2].longpreflen;
        }
    }
    if(trees[2*node+2].eleleft == trees[2*node+2].eleright){
        if(trees[2*node+2].eleleft != trees[2*node+1].eleright){
            trees[node].longsufflen = trees[2*node+2].longsufflen;
        }
        if(trees[2*node+2].eleleft == trees[2*node+1].eleright){
            trees[node].longsufflen = trees[2*node+2].longsufflen + trees[2*node+1].longsufflen;
        }
    }
    if(trees[2*node+1].eleright != trees[2*node+2].eleleft){
        ll leftmax = trees[2*node+1].maxxfreq;
        ll rightmax= trees[2*node+2].maxxfreq;
        if(leftmax >= rightmax){
            trees[node].maxxfreq = leftmax;
        }
        else if(leftmax < rightmax){
            trees[node].maxxfreq = rightmax;
        }
    }
    if(trees[2*node+1].eleright == trees[2*node+2].eleleft){
        ll leftmax = trees[2*node+1].maxxfreq;
        ll rightmax= trees[2*node+2].maxxfreq;
        ll overlaplen = trees[2*node+1].longsufflen + trees[2*node+2].longpreflen ;
        trees[node].maxxfreq = max(leftmax , max(rightmax , overlaplen));
    }
    return ;
}

Tree query(ll low , ll high , ll node , ll st , ll endd)
{
    if(low > high){
        Tree foo;
        foo.maxxfreq = 0 ;
        foo.longpreflen = 0 ;
        foo.longsufflen = 0 ;
        foo.eleleft = minn + minn ;
        foo.eleright = minn;
        return foo;
    }
    if(st > high or endd < low){
        Tree foo;
        foo.maxxfreq = 0 ;
        foo.longpreflen = 0 ;
        foo.longsufflen = 0 ;
        foo.eleleft = minn + minn ;
        foo.eleright = minn;
        return foo;
    }
    if(st <= low and endd >= high){
        return trees[node] ;
    }
    ll mid = (low + high) / 2 ;
    Tree left = query(low , mid , 2*node +1 , st , endd) ;
    Tree right= query(mid+1,high,2*node+2 , st , endd) ;
    Tree foo ;
    foo.eleleft = left.eleleft ;
    foo.eleright = right.eleright ;
    if(left.eleleft != left.eleright){
        foo.longpreflen = left.longpreflen;
    }
    if(right.eleleft != right.eleright){
        foo.longsufflen = right.longsufflen;
    }
    if(left.eleleft == left.eleright){
        if(left.eleright != right.eleleft){
            foo.longpreflen = left.longpreflen;
        }
        else if(left.eleright == right.eleleft){
            foo.longpreflen = left.longpreflen + right.longpreflen;
        }
    }
    if(right.eleleft == right.eleright){
        if(right.eleleft != left.eleright){
            foo.longsufflen = right.longsufflen;
        }
        else if(right.eleleft == left.eleright){
            foo.longsufflen = right.longsufflen + left.longsufflen;
        }
    }
    if(left.eleright != right.eleleft){
        ll leftmax = left.maxxfreq;
        ll rightmax= right.maxxfreq;
        foo.maxxfreq = max(leftmax , rightmax);
    }
    if(left.eleright == right.eleleft){
        ll leftmax = left.maxxfreq;
        ll rightmax= right.maxxfreq;
        ll overlap = left.longsufflen + right.longpreflen;
        foo.maxxfreq = max(leftmax , max(rightmax , overlap));
    }
    return foo;
}

int main()
{
    ios;
    while(1){
    ms(arr);
    ms(trees);
    ll n ,q ;
    cin >> n ;
    if(n == 0) br ;
    cin >> q;
    forn(i , 0 , n-1) cin >> arr[i] ;
    build(0 , n-1 , 0) ;
    vl ans ;
    ans.cl ;
    while(q--){
        ll i , j ;
        cin >> i ;
        if(i == 0) br ;
        cin >> j ;
        --i ;
        --j ;
        Tree foo = query(0 , n-1 , 0 , i , j ) ;
        ll res = foo.maxxfreq;
        ans.pb(res);
    }
    for(auto &x : ans) {
        cout << x << endl;
    }
   }
}
