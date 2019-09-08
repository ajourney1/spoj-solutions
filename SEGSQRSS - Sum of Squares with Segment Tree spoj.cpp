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
struct treee
{
    ll sum ;
    ll sqsum;
    treee(){};
};

treee st[4*maxx];
ll lazy[4*maxx][2];
ll arr[maxx];

void build(ll low , ll high , ll node)
{
    if(low == high){
        st[node].sum = arr[low];
        st[node].sqsum=arr[low]*arr[low];
        return;
    }
    ll mid = (low + high ) / 2 ;
    build(low , mid , 2*node+1) ;
    build(mid + 1 , high , 2*node+2) ;
    st[node].sum = st[2*node+1].sum + st[2*node+2].sum;
    st[node].sqsum=st[2*node+1].sqsum+st[2*node+2].sqsum;
    return ;
}

ll query(ll low , ll high , ll node , ll stt , ll endd)
{
    if(lazy[node][0])
    {
        st[node].sum = (high - low + 1) * lazy[node][0];
        st[node].sqsum= (high-low+1) * lazy[node][0] * lazy[node][0];
        if(low != high){
            lazy[2*node+1][0] = lazy[node][0];
            lazy[2*node+2][0] = lazy[node][0];
        }
        lazy[node][0] = 0 ;
    }
    if(lazy[node][1]){
        ll prev = st[node].sum;
        st[node].sum += (high - low + 1) * lazy[node][1];
        st[node].sqsum= st[node].sqsum + (high - low + 1) * lazy[node][1] * lazy[node][1] + 2 * lazy[node][1] * prev;
        if(low != high){
            lazy[2*node][1] += lazy[node][1] ;
            lazy[2*node][1] += lazy[node][1];
        }
        lazy[node][1] = 0 ;
    }
    if(stt > high or endd < low) return 0 ;
    if(low >= stt and high <= endd){
        return st[node].sqsum;
    }
    ll mid = (low + high) / 2 ;
    ll leftt = query(low , mid , 2*node + 1 , stt , endd) ;
    ll right = query(mid+1 , high , 2*node+2 , stt , endd) ;
    ll foo = leftt + right ;
    return foo ;
}

void update0(ll low , ll high , ll node , ll stt , ll endd , ll val)
{
    if(lazy[node][0]){
        ///cout << "hello\n" ;
        st[node].sum = (high - low + 1) * lazy[node][0];
        st[node].sqsum= (high-low+1) * lazy[node][0] * lazy[node][0];
        if(low != high){
            lazy[2*node+1][0] = lazy[node][0];
            lazy[2*node+2][0] = lazy[node][0];
        }
        lazy[node][0] = 0 ;
    }
    if(lazy[node][1]){
        ///cout << "hello\n" ;
        ll prev = st[node].sum;
        st[node].sum += (high - low + 1) * lazy[node][1];
        st[node].sqsum= st[node].sqsum + (high - low + 1) * lazy[node][1] * lazy[node][1] + 2 * lazy[node][1] * prev;
        if(low != high){
            lazy[2*node][1] += lazy[node][1] ;
            lazy[2*node][1] += lazy[node][1];
        }
        lazy[node][1] = 0 ;
    }
    if(stt > high or endd < low) return ;
    if(low >= stt and high <= endd){
        ll prev = st[node].sum;
        st[node].sum = (high - low + 1) * val ;
        st[node].sqsum= (high - low + 1) * val * val ;
        ///cout << "node " << node << " sum " << st[node].sum << " sq " << st[node].sqsum << el ;
        if(low != high){
            lazy[2*node+1][0] = val ;
            lazy[2*node+2][0] = val ;
        }
        return ;
    }
    ll mid = (low  + high ) / 2;
    update0(low , mid , 2*node + 1 , stt  , endd , val ) ;
    update0(mid + 1 , high , 2*node  + 2 , stt , endd , val ) ;
    st[node].sum = st[2*node+1].sum + st[2*node+2].sum;
    st[node].sqsum = st[2*node+1].sqsum  + st[2*node+2].sqsum ;
    return ;
}

void update1(ll low , ll high  , ll node , ll stt , ll endd , ll val)
{

    if(lazy[node][0]){
        st[node].sum = (high - low + 1) * lazy[node][0];
        st[node].sqsum= (high-low+1) * lazy[node][0] * lazy[node][0];
        if(low != high){
            lazy[2*node+1][0] = lazy[node][0];
            lazy[2*node+2][0] = lazy[node][0];
        }
        lazy[node][0] = 0 ;
    }
    if(lazy[node][1]){
        ll prev = st[node].sum;
        st[node].sum += (high - low + 1) * lazy[node][1];
        st[node].sqsum= st[node].sqsum + (high - low + 1) * lazy[node][1] * lazy[node][1] + 2 * lazy[node][1] * prev;
        if(low != high){
            lazy[2*node][1] += lazy[node][1] ;
            lazy[2*node][1] += lazy[node][1];
        }
        lazy[node][1] = 0 ;
    }
    if(stt > high or endd < low) return ;
    if(low >= stt and high <= endd){
        ll prev = st[node].sum;
        st[node].sum += (high - low + 1) * val ;
        st[node].sqsum= st[node].sqsum + (high - low + 1) * val * val + 2 * val * prev;
        if(low != high){
            lazy[2*node+1][1] += val ;
            lazy[2*node+2][1] += val ;
        }
        return ;
    }
    ll mid = (low  + high ) / 2;
    update1(low , mid , 2*node + 1 , stt  , endd , val ) ;
    update1(mid + 1 , high , 2*node  + 2 , stt , endd , val ) ;
    st[node].sum = st[2*node+1].sum + st[2*node+2].sum;
    st[node].sqsum = st[2*node+1].sqsum  + st[2*node+2].sqsum ;
}

ll cnt = 0 ;
void solve()
{
    ++cnt ;
    ll n , q ;
    cin >> n >> q ;
    ms(arr);
    ms(st);
    ms(lazy);
    forn(i , 0 , n - 1 ) cin >> arr[i] ;
    build(0 , n-1 , 0) ;
    vl ans;
    ans.cl;
    while(q--){
        ll x;
        cin >> x ;
        if(x == 2){
            ll a , b ;
            cin >> a >> b ;
            --a ;
            --b ;
            ll foo = query(0 , n-1 , 0 , a , b);
            ans.pb(foo);
        }
        else if(x == 0){
            ll a , b ;
            cin >> a >> b ;
            ll x;
            cin >> x;
            --a;
            --b;
            update0(0 , n - 1 , 0 , a , b , x) ;
        }
        else if(x == 1){
            ll a , b;
            cin >> a >> b ;
            ll x;
            cin >> x;
            --a ;
            --b;
            update1(0 , n-1 , 0 , a , b , x) ;
        }
    }
    cout << "Case "<<cnt<<":\n";
    for(auto &x : ans) cout << x << el ;
}

int main()
{
    //ios;
    ll t;
    cin >> t;
    while(t--) solve();
    ro ;
}





























