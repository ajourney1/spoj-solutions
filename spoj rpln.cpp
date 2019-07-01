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
const ll maxx = 1e5 + 5;
ll arr[maxx] , tres[4*maxx] ;
ll cnt = 0 ;

/// https://www.spoj.com/problems/RPLN/
void build(ll low , ll high , ll node)
{
    if(low == high) {
        tres[node] = arr[low] ;
        return ;
    }
    ll mid = (low + high) / 2 ;
    build(low , mid, 2*node+1) ;
    build(mid+1 , high , 2*node + 2 ) ;
    tres[node] = min(tres[2*node+1] , tres[2*node+2]);
    return ;
}

ll query(ll low , ll high , ll node , ll st , ll endd)
{
    if(low > high) return 3e18 ;
    if(endd < low or st > high ) return 3e18 ;
    if(st <= low and endd >= high) return tres[node];
    ll mid = low + high ;
    mid = mid /2 ;
    ll left = query(low , mid , 2*node+1 , st , endd) ;
    ll right= query(mid +1 , high, 2*node+2 , st ,endd) ;
    return min(left, right) ;
}

void solve()
{
    ++cnt ;
    ll n , q ;
    cin >> n >> q;
    forn(i , 0 , n - 1 ) cin >> arr[i] ;
    build(0 , n-1 , 0);
    vl ans ;
    while(q--){
        ll i , j ;
        cin >> i >> j ;
        --i;
        --j;
        ll foo = query(0 , n-1 , 0 , i , j ) ;
        ans.pb(foo);
    }
    cout << "Scenario #"<<cnt<<": "<<el;
    for(auto &x : ans ) {
        cout << x << el;
    }
    return ;
}
int main()
{
    ios;
    ll t;
    cin >> t;
    while(t--){
        ms(arr) ;
        ms(tres) ;
        solve();
    }
}
