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
const ll maxx = 50005;
struct Tree
{
    ll psum ,ssum , tsum,maxsum ;
    Tree(){}
};
ll arr[maxx] ;
Tree Trees[4*maxx] ;
ll n , q ;
ll max(ll a , ll b , ll c)
{
    return max(a , max(b , c)) ;
}
const ll minn = -3e18;
void build(ll low , ll high , ll node)
{
    if(low == high){
        Trees[node].psum = arr[low] ;
        Trees[node].ssum = arr[low] ;
        Trees[node].tsum = arr[low] ;
        Trees[node].maxsum = arr[low];
        return ;
    }
    ll mid = (low + high) / 2 ;
    build(low , mid , 2*node+1);
    build(mid+1 , high , 2*node+2) ;
    Trees[node].tsum = Trees[2*node + 1 ].tsum + Trees[2*node + 2].tsum;
    Trees[node].psum = max(Trees[2*node+1].psum , Trees[2*node+1].tsum + Trees[2*node+2].psum);
    Trees[node].ssum = max(Trees[2*node+2].ssum , Trees[2*node+2].tsum + Trees[2*node+1].ssum);
    Trees[node].maxsum=max(Trees[2*node+1].maxsum , Trees[2*node+2].maxsum , Trees[2*node+1].ssum + Trees[2*node+2].psum);
    return ;
}

Tree query(ll low , ll high , ll node , ll st , ll endd)
{
    if(low > high){
        Tree ziz ;
        ziz.tsum = 0 ; ziz.psum = minn; ziz.ssum = minn ; ziz.maxsum = minn ;
        return ziz ;
    }
    if(st > high or endd < low ){
        Tree ziz ;
        ziz.tsum = 0 ; ziz.psum = minn ; ziz.ssum = minn ; ziz.maxsum = minn;
        return ziz ;
    }
    if(st <= low and endd >= high){
        return Trees[node];
    }
    ll mid = (low + high) / 2 ;
    Tree left= query(low , mid , 2*node +1 , st , endd) ;
    Tree right=query(mid + 1 , high , 2*node + 2, st , endd);
    Tree foo ;
    foo.tsum = left.tsum + right.tsum ;
    foo.psum = max(left.psum , left.tsum + right.psum);
    foo.ssum = max(right.ssum , right.tsum + left.ssum);
    foo.maxsum=max(left.maxsum , right.maxsum , left.ssum + right.psum);
    return foo ;

}

int main()
{
    ios;
    cin >> n;
    forn(i , 1 , n ) {
       cin >> arr[i-1] ;
    }
    build(0 , n-1 , 0 ) ;
    ll q;
    cin >> q;
    while(q--){
        ll i , j ;
        cin >> i >> j ;
        --i;
        --j;
        Tree foo = query(0 , n-1 , 0 , i , j) ;
        ll ans = foo.maxsum ;
        cout << ans << el;
        con ;
    }
    ro;
}
