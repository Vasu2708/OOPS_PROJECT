
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define IOS                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);
#define mod 1000000007
#define MAX 1000005
#define pb push_back

#define deb(x) cout << #x << " = " << x << endl
#define deb2(x, y) cout << #x << " = " << x << ", " << #y << " = " << y << endl
#define deb3(x, y, z) cout << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl
#define deb4(x, y, z, w) cout << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << ", " << #w << " = " << w << endl

#define f(i, a, b) for (int i = (a); i < (b); i++)
#define fr(i, a, b) for (int i = (a); i >= (b); i--)

#define vi vector<int>
#define vvi vector<vector<int>>
#define us unordered_set
#define ld long double

#define each(a, b) for (auto &a : b)
#define yes cout << "YES" << endl
#define no cout << "NO" << endl

void slove()
{
    int n;
    cin >> n;

    vector<int> a(n);

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
  
    int count = 1;
    int max = a[0];
    for (int i = 1; i < n; i++)
    {
        if(a[i]>=max){
            max = a[i];
            count++;
        }

        
    }
    cout << count << endl;
}

int_fast32_t main()
{
    IOS;

    int t;
    cin >> t;
    while (t--)
    {
        slove();
    }
    return 0;
}
