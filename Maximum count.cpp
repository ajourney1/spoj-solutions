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

/// https://www.spoj.com/problems/KGSS/
struct Tree
{
    Tree(){}
    ll maxx , smaxx ;
};
const ll maxx = 100005;
ll arr[100005] ;
Tree Tree[4*maxx] ;
void build(ll low , ll high , ll node)
{
    if(low == high){
        Tree[node].maxx = arr[low];
        Tree[node].smaxx= -1;
        return ;
    }
    ll mid = (low + high ) / 2 ;
    build(low , mid , 2*node+1) ;
    build(mid+1 , high , 2*node+2) ;
    vl res ;
    res.cl ;
    ll leftleft = Tree[2*node+1].maxx;
    ll leftright = Tree[2*node+1].smaxx;
    ll rightleft = Tree[2*node+2].maxx;
    ll rightright = Tree[2*node+2].smaxx;
    res.pb(leftleft) ; res.pb(leftright) ; res.pb(rightleft) ; res.pb(rightright) ;
    sort(all(res)) ;
    ll firstmaxx = -1 , secondmaxx = -1;
    firstmaxx = res[3];
    secondmaxx= res[2];
    Tree[node].maxx = firstmaxx ;
    Tree[node].smaxx= secondmaxx;
}
pll query(ll low , ll high , ll node , ll st , ll endd)
{
    if(low > endd or high < st){
        pll foo = {-1 , -1 } ;
        return foo ;
    }
    if(st <= low and endd >= high){
        pll foo = {Tree[node].maxx , Tree[node].smaxx};
        return foo ;
    }
    ll mid = (low + high) / 2;
    pll left = query(low , mid , 2*node +1 , st , endd) ;
    pll right= query(mid+1 , high , 2*node + 2 , st , endd) ;
    ll a = left.fi , b = left.se , c = right.fi , d = right.se ;
    vl ans ;
    ans.cl ;
    ans.pb(a) ;
    ans.pb(b);
    ans.pb(c);
    ans.pb(d);
    sort(all(ans));
    ll fmaxx = ans[3] ;
    ll semaxx= ans[2] ;
    pll ziz = {fmaxx , semaxx} ;
    return ziz ;
}
void update(ll low , ll high , ll node , ll ind , ll val)
{
    if(low > high ) return ;
    if(ind > high or ind < low ) return ;
    if(low == high and low == ind){
        arr[ind] = val ;
        Tree[node].maxx = val;
        Tree[node].smaxx= -1;
        return ;
    }
    ll mid = (low + high) / 2 ;
    update(low , mid , 2*node+1 , ind , val) ;
    update(mid + 1 , high , 2*node + 2 , ind , val ) ;
    vl res ;
    res.cl ;
    ll leftleft = Tree[2*node+1].maxx;
    ll leftright = Tree[2*node+1].smaxx;
    ll rightleft = Tree[2*node+2].maxx;
    ll rightright = Tree[2*node+2].smaxx;
    res.pb(leftleft) ; res.pb(leftright) ; res.pb(rightleft) ; res.pb(rightright) ;
    sort(all(res)) ;
    ll firstmaxx = -1 , secondmaxx = -1;
    firstmaxx = res[3];
    secondmaxx= res[2];
    Tree[node].maxx = firstmaxx ;
    Tree[node].smaxx= secondmaxx;
}
int main()
{
    ios;
    ll n;
    cin >> n;
    forn(i , 0 , n-1 ) cin >> arr[i] ;
    ll q;
    build(0 , n-1 , 0) ;
    ///forn(i , 0 , 8) cout << Tree[i].maxx << " " << Tree[i].smaxx << el ;
    cin >> q;
    while(q--){
        char c ;
        cin >> c;
        if(c == 'Q'){
            ll x , y  ;
            cin >> x >> y;
            --x ;
            --y;
            pll foo = query(0 , n-1 , 0 , x , y);
            ll ans = foo.fi  + foo.se ;
            cout << ans << el ;
        }
        else if(c == 'U'){
            ll x , val ;
            cin >> x >> val ;
            --x ;
            update(0 , n-1 , 0 , x , val) ;
        }
    }
}



