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


void solve()
{
    ll n ;
    cin >> n ;
    ll arr[n] , brr[n+1];
    ms(arr) ;
    ms(brr) ;
    ll u ;
    cin >> u ;
    forn(i , 1 , u){
       ll low , high ;
       cin >> low >> high ;
       ll val ;
       cin >> val ;
       brr[low]+=val ;
       brr[high+1]-=val;
    }
    forn(i , 0 , n ) cerr << brr[i] << " " ;
    cerr << el ;
    arr[0] = brr[0] ;
    forn(i , 1 , n-1){
       arr[i] = arr[i-1] + brr[i] ;
    }
    ll q;
    cin >>q ;
    while(q--){
        ll x;
        cin >> x;
        cout << arr[x] << el ;
    }
    return ;
}
int main()
{
    ios;
    ll t;
    cin >> t;
    while(t--) solve();
    return 0 ;
}
