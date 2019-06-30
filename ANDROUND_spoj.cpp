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
const ll maxx = 20005;
ll arr[maxx] , Tree[4*maxx];
const ll inf = 1073741823;
/// https://www.spoj.com/problems/ANDROUND/
void build(ll low , ll high , ll ind)
{
    if(low == high){
        Tree[ind] = arr[low] ;
        return ;
    }
    ll mid = (low + high ) / 2 ;
    build(low , mid , 2*ind+1) ;
    build(mid + 1 , high , 2*ind+2) ;
    Tree[ind] = Tree[2*ind+1] & Tree[2*ind+2] ;
    return ;
}
ll query(ll low , ll high , ll st , ll endd , ll node)
{
    if(low > endd or high < st) return inf;
    if(st <= low and endd >= high){
        return Tree[node];
    }
    ll mid = (low + high)  / 2;
    ll left = query(low , mid , st , endd , 2*node + 1) ;
    ll right = query(mid+1 , high , st , endd , 2*node + 2);
    ll foo = left & right ;
    return foo ;
}
void solve()
{
    ll n , k ;
    cin >> n >> k ;
    ms(arr) ;
    ms(Tree) ;
    forn(i , 0, n-1) cin >> arr[i] ;
    build(0 , n-1 , 0);
    vl ans;
    ans.cl;
    forn(i , 0 , n-1){
       if(k >= n){
         ll foo = query(0 , n-1 , 0 , n-1 , 0) ;
         ans.pb(foo ) ;
       }
       else {
          ll res  = inf;
          ll curr = i ;
          ll right = (curr + k) % n ;
          if(right <= n-1 and right > curr){
              ll foo  = query(0 , n-1 , curr , right , 0) ;
              res = res & foo ;
          }
          if(right < curr) {
             ll foo = query(0 , n-1 , curr , n-1 , 0 ) ;
             ll soo = query(0 , n-1 , 0 , right , 0);
             res = res & foo ;
             res = res & soo ;
          }
          //if(res == inf) throw ;
          ll fromright = res;
          ll ziz = inf ;
          curr = i ;
          ll left = curr - k ;
          if(left >= 0){
            ll foo = query(0 , n-1 , left ,curr , 0 ) ;
            ziz = ziz & foo ;
          }
          else if(left < 0 ){
            ll foo = query(0 ,  n-1 , 0 , curr , 0) ;
            ll stfrom = left + n ;
            ll soo = query(0 , n-1 , stfrom , n-1 , 0 ) ;
            ziz = ziz & foo ;
            ziz = ziz & soo;
          }
          //if(ziz == inf) throw ;
          ll fin = res  & ziz ;
          ans.pb(fin);
       }
    }
    for(auto &x : ans) cout << x << " " ;
    cout << el ;
}
int main()
{
    ios;
    ll t ;
    cin >> t;
    while(t--) solve();
}
