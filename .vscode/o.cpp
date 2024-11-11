#include <bits/stdc++.h>
using namespace std;
#define IOS                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);
#define mod 1000000007
#define MAX 1000005
#define pb push_back
#define ff first
#define ss second
#define deb(x) cout << #x << " = " << x << endl
#define deb2(x, y) cout << #x << " = " << x << ", " << #y << " = " << y << endl
#define deb3(x, y, z) cout << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl
#define deb4(x, y, z, w) cout << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << ", " << #w << " = " << w << endl

#define f(i, a, b) for (int i = (a); i < (b); i++)
#define fr(i, a, b) for (int i = (a); i >= (b); i--)

#define vi vector<int>
#define vvi vector<vector<int>>
#define dp vector<int> dp(n, -1)
#define dp2 vector<vector<int>> dp(n, vector<int>(m, -1))
#define us unordered_set
#define minheap priority_queue<int, vector<int>, greater<int>> pq;
#define ll long long
#define ld long double

#define pf push_front
#define ppf pop_front
#define ppb pop_back
#define each(a, b) for (auto &a : b)
#define yes cout << "YES" << endl
#define no cout << "NO" << endl

int main()
{
    IOS;

    int t;
    cin >> t;
    while (t--)
    {
        int a,b;
        cin>>a>>b;
         int ans =0;
        if(a>=b)  ans = a;

        else if (2*a>=b)   ans = 2 * a - b;
        
        cout<<ans<<endl;
    }
    return 0;
}