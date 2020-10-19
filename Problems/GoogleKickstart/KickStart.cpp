#include<bits/stdc++.h>
using namespace std;

const int mod = (int)1e7+9;
#define REP0(i,n) for(int i=0;i<n;i++)
#define REP(i,a,n) for(int i=a;i<=n;i++)
#define F first
#define S second
#define endl "\n"
#define ll long long
#define pii pair<int,int>
#define vi vector<int>
#define maxpq priority_queue<int>
#define minpq priority_queue<int, vector<int>, greater<int> >
#define setbits(x) __builtin_popcountll(x)
#define inf (int)(1e18)
#define prec(x) fixed<<setprecision(x)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define all(x) x.begin(),x.end()

const int d4i[4]={-1, 0, 1, 0}, d4j[4]={0, 1, 0, -1};
const int d8i[8]={-1, -1, 0, 1, 1, 1, 0, -1}, d8j[8]={0, 1, 1, 1, 0, -1, -1, -1};

void solve(){
    string s;
    cin>>s;
    ll ans = 0,st = 0;
    string a = "KICK", b = "START";
    int n = s.size();
    for(int i=n-5;i>=0;i--){
        if(s.substr(i,5) == b) st++;
        if(s.substr(i,4) == a) ans += st;
    }
    cout<<ans<<endl;
}


int main(){
    fastio;
    int tc = 1;
    cin>>tc;
    for(int i=1;i<=tc;i++){
        cout<<"Case #"<<i<<": ";
        solve();
    }
    return 0;
}
