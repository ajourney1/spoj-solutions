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
const ll maxx = 1e5;

/// https://www.spoj.com/problems/LITE/

ll Tree[4*maxx] , lazy[4*maxx]  ;
ll n , m ;

void propagate(ll node , ll l , ll r)
{
    if(l!=r){
        lazy[2*node+1]+=1;
        lazy[2*node+1]%=2;
        lazy[2*node+2]+=1;
        lazy[2*node+2]%=2;
    }
    lazy[node] = 0 ;
    Tree[node] = (r - l + 1) - Tree[node];
}
void update(ll low , ll high , ll node , ll i , ll j)
{
    if(lazy[node] != 0){
        /// there are some updates from the past which haven't been propagated yet.
        propagate(node , low , high);
    }
    if(i > high or j <low ){
        return ;
    }
    if(i <= low and j >= high){
        Tree[node] = (high - low + 1 ) - Tree[node] ;
        if(low != high){
            lazy[2*node+1]+=1;
            lazy[2*node+1]%=2;
            lazy[2*node+2]+=1;
            lazy[2*node+2]%=2;
        }
        return ;
    }
    ll mid = (low + high ) / 2 ;
    update(low , mid , 2*node+1 , i , j ) ;
    update(mid+1 , high , 2*node+2  ,i , j);
    Tree[node] = Tree[2*node+1] + Tree[2*node+2] ;
}

ll query(ll low , ll high , ll node , ll i , ll j)
{
    if(lazy[node] != 0){
        propagate(node , low , high) ;
    }
    if(j < low or i > high) return 0 ;
    if(i <= low and j >= high){
        return Tree[node] ;
    }
    ll mid = (low + high) / 2 ;
    ll left = query(low , mid , 2*node + 1 , i , j ) ;
    ll right= query(mid+1 , high , 2*node + 2  , i , j ) ;
    return left + right ;
}
int main()
{
    ios;
    cin >> n >> m ;
    vl ans;
    while(m--){
        ll x , l , r ;
        cin >> x >> l >> r;
        --l ;
        --r;
        if(x == 0) {
            update(0 , n-1 , 0 , l , r) ;
        }
        else if(x == 1){
            ll foo = query(0 , n-1 , 0 , l , r) ;
            ans.pb(foo) ;
        }
    }
    for(auto x : ans) {
        cout << x << el ;
    }
    ro ;
}


