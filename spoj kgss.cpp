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

const ll maxx = 1e5+5;
ll arr[maxx];
const ll inf = 3e18;
struct Tree
{
    ll maxx , smaxx;
    Tree (){};
};
ll n , q ;
Tree trees[4*maxx];

bool op(const ll &a , const ll &b)
{
    return a > b ;
};

void build(ll low , ll high , ll ind)
{
    if(low == high){
        trees[ind].maxx = arr[low];
        trees[ind].smaxx= -inf;
        return ;
    }
    ll mid = (low + high ) / 2 ;
    build(low , mid , 2*ind+1) ;
    build(mid + 1 , high , 2*ind + 2) ;
    ll leftmax = trees[2*ind+1].maxx;
    ll leftsmax= trees[2*ind+1].smaxx;
    ll rightmax= trees[2*ind+2].maxx;
    ll rightsmax=trees[2*ind+2].smaxx;
    vl res = {leftmax , rightmax , leftsmax , rightsmax} ;
    sort(all(res) ,op);
    trees[ind].maxx = res[0];
    trees[ind].smaxx= res[1];
    return ;
}

pll query(ll low , ll high , ll ind , ll st , ll endd)
{
    if(low > endd or high < st){
        pll res = {-inf , -inf};
        return res;
    }
    if(st <= low and endd >= high){
        pll res = {trees[ind].maxx , trees[ind].smaxx};
        return res;
    }
    ll mid = (low + high) / 2 ;
    pll leftt = query(low , mid , 2*ind + 1 , st , endd) ;
    pll rightt= query(mid+1 , high , 2*ind+2 , st , endd);
    vl res = {leftt.fi , leftt.se , rightt.fi , rightt.se} ;
    sort(all(res) , op) ;
    pll ziz = {res[0] , res[1]} ;
    return ziz ;
}

void update(ll low , ll high ,ll ind,  ll st , ll endd , ll val)
{
    if(low > endd or high < st) return ;
    if(st <= low and endd >= high){
        trees[ind].smaxx = -inf;
        trees[ind].maxx  = val ;
        return ;
    }
    ll mid = (low + high) / 2 ;
    update(low , mid ,2*ind+1 , st , endd , val ) ;
    update(mid+1 , high ,2*ind+2 , st , endd , val ) ;
    ll leftmax = trees[2*ind+1].maxx;
    ll leftsmax= trees[2*ind+1].smaxx;
    ll rightmax= trees[2*ind+2].maxx;
    ll rightsmax=trees[2*ind+2].smaxx;
    vl res = {leftmax , leftsmax , rightmax , rightsmax};
    sort(all(res) , op) ;
    trees[ind].maxx = res[0];
    trees[ind].smaxx= res[1] ;
    return ;
}

int main()
{
    ios;
    cin >> n ;
    forn(i , 0  , n - 1 ){
       cin >> arr[i] ;
    }
    build(0 , n -1 , 0 );
    cin >> q;
    while(q--){
        char c ;
        cin >> c;
        if(c == 'Q'){
            ll x , y ;
            cin >> x >> y;
            --x;
            --y;
            pll foo = query(0 , n-1 , 0 , x , y);
            ll sum = foo.fi + foo.se;
            cout << sum << el ;
        }
        else if(c == 'U'){
            ll ind , val ;
            cin >> ind >> val ;
            --ind ;
            update(0 , n-1 , 0 , ind , ind , val);
        }
    }
    return 0;
}
