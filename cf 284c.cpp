#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
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
#define vlll vector<ll,pair<ll,ll>>
#define vlvl vector<pair<ll,ll>,ll>>
#define pll pair<ll,ll>
#define plll pair<ll,pair<ll,ll>>
#define plvl pair<pair<ll,ll> ,ll>
#define mp make_pair
#define trace3(a,b,c) cerr <<"a is " << a << " b is " << b << " c is " << c << el;
#define trace4(a,b,c,d) cerr <<"a is " << a << " b is " << b << " c is " << c <<" d is " << d << el ;
#define trace5(a,b,c,d,e) cerr <<"a is " << a << " b is " << b << " c is " << c <<" d is " << d << " e is " << e << el;
#define trace6(a,b,c,d,e,f) cerr <<"a is " << a << " b is " << b << " c is " << c <<" d is " << d << " e is " << e << " f is " << f << el ;

const ll maxx = 2e5 +5 ;
ll tree[4*maxx] , lazy[4*maxx] , arr[maxx] ;
ll ptr = 1;
ll ele = 1 ;
ll query(ll low , ll high , ll node , ll st , ll endd )
{
    if(lazy[node]){
        tree[node]+=(high - low + 1) * lazy[node] ;
        if(low != high){
            lazy[2*node+1]+=lazy[node];
            lazy[2*node+2]+=lazy[node] ;
        }
        lazy[node] = 0;
    }
    if(low > endd or high < st) return 0 ;
    if(st <= low and endd >= high){
        return tree[node] ;
    }
    ll mid = (low + high) / 2 ;
    ll left = query(low , mid , 2*node + 1 , st , endd) ;
    ll right = query(mid+1 , high , 2*node + 2 , st , endd)  ;
    ll ziz = left + right ;
    return ziz ;
}

void update(ll low , ll high , ll node , ll st , ll endd , ll val)
{
    if(lazy[node]){
        tree[node] += (high - low + 1) * lazy[node] ;
        if(low != high){
            lazy[2*node+1]+=lazy[node];
            lazy[2*node+2]+=lazy[node];
        }
        lazy[node] = 0 ;
    }
    if(low > endd or high < st) return ;
    if(st <= low and endd >= high){
        tree[node]+= (high - low + 1) * val;
        if(low != high){
            lazy[2*node+1]+=val ;
            lazy[2*node+2]+=val ;
        }
        return ;
    }
    ll mid = (low + high) / 2 ;
    update(low , mid  , 2*node + 1, st , endd , val) ;
    update(mid + 1 , high , 2 * node + 2 , st , endd , val ) ;
    tree[node] = tree[2*node + 1] + tree[2*node + 2] ;
    return ;
}

int main()
{
    ios;
    ll q;
    cin >> q;
    ll n  = q + 1;
    cout << fixed ;
    cout << setprecision(6) ;
    while(q--){
        ll ti ;
        cin >> ti ;
        if(ti == 1){
            ll ai , xi ;
            cin >> ai >> xi ;
            update(0 , n , 0 , 0 , ai - 1 , xi) ;
        }
        else if(ti == 2){
            ll ki ;
            cin >> ki ;
            update(0 , n , 0 , ptr , ptr , ki) ;
            ++ele;
            ++ptr;
        }
        else if(ti == 3){
            --ptr ;
            ll foo = query(0 , n , 0 , ptr , ptr) ;
            update(0 , n , 0 , ptr , ptr , -foo) ;
            --ele ;
        }
        ll ans = 0 ;
        ans = query(0 , n , 0 ,  0 , ele + 2) ;
        long double foo = double(ans) / ele ;
        cout << foo << el ;
    }
    ro ;

}





























