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
#define ms(x) memset(x , 0ll, so x)
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

const ll maxx = 1e5 + 5 ;
ll arr[maxx] ;
ll treee[4*maxx] , lazy[4*maxx] ;

void update(ll low , ll high , ll node , ll st , ll endd , ll val)
{
    if(lazy[node]){
        treee[node]+= lazy[node] * (high - low + 1) ;
        if(low != high){
          lazy[2*node+1]+=lazy[node];
          lazy[2*node+2]+=lazy[node];
        }
        lazy[node] = 0 ;
    }
    if(low > endd or high < st) return ;
    if(st <= low and endd >= high){
        treee[node]+= (high - low + 1) * val ;
        if(low != high){
           lazy[2*node+1]+= val ;
           lazy[2*node+2]+= val ;
        }
        return ;
    }
    ll mid = (low + high) / 2 ;
    update(low , mid , 2*node + 1 , st , endd , val);
    update(mid+1 , high , 2*node+2 , st , endd , val) ;
    treee[node] = treee[2*node+1] + treee[2*node+2];
    return ;
}

ll query(ll low , ll high , ll node , ll st , ll endd)
{
    if(lazy[node]){
        treee[node]+= lazy[node] * (high - low + 1) ;
        if(low != high){
           lazy[2*node+1]+=lazy[node];
           lazy[2*node+2]+=lazy[node];
        }
        lazy[node] = 0 ;
    }
    if(low > endd or high < st) return 0 ;
    if(st <= low and endd >= high){
        return treee[node];
    }
    ll mid = (low + high ) / 2 ;
    ll leftt = query(low , mid , 2*node+1 , st , endd) ;
    ll right = query(mid + 1 , high , 2*node+2 , st , endd) ;
    ll foo = leftt  + right ;
    return foo ;
}

void solve()
{
    ms(treee) ;
    ms(lazy) ;
    ll n , qq ;
    cin >> n >> qq;
    while(qq--)
    {
        ll x;
        cin >> x;
        if(x == 0){
            ll p , q , v ;
            cin >> p >> q >> v;
            --p ;
            --q ;
            update(0 , n-1 , 0 , p , q , v);
        }
        else if(x == 1){
            ll p , q;
            cin >> p >> q;
            --p;
            --q;
            ll foo = query(0 , n - 1 , 0 , p , q ) ;
            cout << foo << el ;
        }
    }
}

int main()
{
    ios;
    ll t;
    cin >> t;
    while(t--) solve();
}





























