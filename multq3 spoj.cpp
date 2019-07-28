#include<bits/stdc++.h>
using namespace std;
const long long maxx = 1e5+5;
struct Tree
{
	Tree(){};
	long long mod0 , mod1 , mod2;
};
Tree trees[4*maxx];
long long lazy[4*maxx];

void build(long long low , long long high , long long node)
{
	if(low == high){
		trees[node].mod0 = 1;
		trees[node].mod1 = 0;
		trees[node].mod2 = 0;
		return;
 	}
 	long long mid = (low + high ) / 2 ;
 	build(low , mid , 2*node + 1) ;
 	build(mid + 1 , high , 2*node + 2) ;
 	trees[node].mod0 = trees[2*node+1].mod0 + trees[2*node + 2].mod0 ;
}

void propogate(long long node , long long low , long long high)
{
    if(lazy[node] == 1){
        long long pmod0 = trees[node].mod0;
		long long pmod1 = trees[node].mod1;
		long long pmod2 = trees[node].mod2;
		trees[node].mod1 = pmod0;
		trees[node].mod2 = pmod1;
		trees[node].mod0 = pmod2;
		if(low != high){
			lazy[2*node+1]+=1;
			lazy[2*node+2]+=1;
			lazy[2*node+1]%=3;
			lazy[2*node+2]%=3;
		}
    }
    else if(lazy[node] == 2){
        long long pmod0 = trees[node].mod0;
		long long pmod1 = trees[node].mod1;
		long long pmod2 = trees[node].mod2;
		trees[node].mod2 = pmod0;
		trees[node].mod0 = pmod1;
		trees[node].mod1 = pmod2;
        if(low != high){
			lazy[2*node+1]+=2;
			lazy[2*node+2]+=2;
			lazy[2*node+1]%=3;
			lazy[2*node+2]%=3;
		}
    }
     lazy[node] = 0 ;
}

void update(long long low , long long high , long long node , long long st , long long endd)
{
	if(lazy[node]!=0){
		propogate(node , low  , high) ;
	}
	if(st > high or endd < low ) return  ;
	if(st <= low and endd >= high){
		long long pmod0 = trees[node].mod0;
		long long pmod1 = trees[node].mod1;
		long long pmod2 = trees[node].mod2;
		trees[node].mod1 = pmod0;
		trees[node].mod2 = pmod1;
		trees[node].mod0 = pmod2;
		if(low != high){
			lazy[2*node+1]+=1 ;
			lazy[2*node+1]%=3 ;
			lazy[2*node+2]+=1 ;
			lazy[2*node+2]%=3 ;
		}
		return ;
	}
	long long mid = (low + high ) / 2 ;
	update(low , mid , 2*node+1 , st , endd) ;
	update(mid+1 , high , 2*node+2 , st , endd) ;
	trees[node].mod0 = trees[2*node+1].mod0 + trees[2*node+2].mod0;
	trees[node].mod1 = trees[2*node+1].mod1 + trees[2*node+2].mod1;
	trees[node].mod2 = trees[2*node+1].mod2 + trees[2*node+2].mod2;
}

long long query(long long low , long long high , long long node  , long long st , long long endd)
{
	if(lazy[node]) propogate(node , low , high);
	if(st > high or endd < low ) return 0 ;
	if(st <= low and endd >= high){
		long long res = trees[node].mod0;
		return res;
	}
	long long mid = (low + high ) / 2;
	long long left = query(low , mid , 2*node + 1 , st , endd) ;
	long long right= query(mid+1 , high , 2*node +2 , st , endd) ;
	long long ziz = left + right ;
	return ziz ;
}

int main(int argc, char const *argv[])
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	long long n , q ;
	cin >> n >> q ;
	build(0 , n-1 , 0);
	std::vector<long long > v;
	while(q--)
	{
		long long x , a , b ;
		cin >> x >> a >> b;
		if(x == 0){
			update(0 , n-1 , 0 , a , b);
		}
		else if(x == 1){
			long long foo = query(0 , n-1 , 0 , a , b) ;
			v.push_back(foo);
		}
	}
	for(auto &x : v){
		cout << x << endl ;
	}
	return 0;
}
