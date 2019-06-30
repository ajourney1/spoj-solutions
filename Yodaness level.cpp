#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
typedef int ll;
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
const ll maxx = 30005;
ll arr[30005] ,Tree[4*maxx] , brr[maxx];

void update(ll low , ll high , ll node , ll val , ll ind )
{
    //cout << "low is " << low << " high is " << high << " node is " << node << " ind is " << ind << el ;
    if(low > high) return ;
    if(ind > high or ind < low ) return ;
    if(low == high and low == ind) {
       // cout << "xxx\n" ;
        brr[low] = 1 ;
        Tree[node] = 1 ;
        return ;
    }
    ll mid = (low + high )  / 2 ;
    update(low , mid , 2*node + 1 , val , ind);
    update(mid +1 , high , 2 * node + 2 , val , ind) ;
    Tree[node] = Tree[2*node+1] + Tree[2*node+2] ;
   // cout << "here node is " << node << " val is " << Tree[node] << el ;
    return ;
}

ll query(ll low , ll high , ll node , ll st  , ll endd)
{
    //trace5(low , high , node, st , endd) ;
    if(st > endd ) return 0 ;
    if(low > endd or high < st) return 0 ;
    if(st <= low and endd >= high) return Tree[node] ;
    ll mid = (low + high) / 2 ;
    ll left = query(low , mid , 2*node + 1 , st , endd);
    ll right= query(mid + 1 , high , 2*node + 2 , st , endd) ;
    return left + right ;
}
void solve()
{
    ll n ;
    cin >> n;
    unordered_map<string , ll > mpp;
    mpp.cl ;
    forn(i , 1 , n ) {
       string s ;
       cin >> s ;
       mpp[s] = i-1 ;
    }
    ms(arr) ;
    ms(brr) ;
    ms(Tree);
    forn(i , 1 , n ) {
       string s ;
       cin >> s ;
       ll foo = mpp[s] ;
       arr[i-1] = foo ;
    }
    ll ans = 0 ;
    forn(i , 0 , n-1){
       if(i == 0 ) {
          update(0 , n-1 , 0 , 1 , arr[i]) ;
       }
       else {
         ll foo = query(0 , n-1 , 0 , arr[i] + 1 , n-1 ) ;
         ans = ans + foo ;
         update(0 , n-1 , 0 , 1 , arr[i]) ;
       }
    }
    cout << ans << el ;
}
int main()
{
    ios;
    ll t ;
    cin >> t;
    while(t--) solve();
}
