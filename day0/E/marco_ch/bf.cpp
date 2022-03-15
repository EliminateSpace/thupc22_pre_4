#include <bits/stdc++.h>
using namespace std;
const int N=100000;
set <int> s;
set <int>::iterator it;
int t[N+5];
inline void solve(int d)
{int ans=0,lst=0;
set <int>::iterator it=s.begin();
while (1)
{ans++;lst+=d;
if (it==s.end()||(*it)>lst) break;
while (it!=s.end()&&(*it)<=lst) 
{d-=t[(*it)];it++;
if (d<=0) break;
}
if (d<=0) break;
}
printf ("%d\n",ans);
}
int main (){
	int T,op,a,b,d;
	scanf ("%d",&T);
	while (T--)
	{scanf ("%d",&op);
	if (op==1)
	{scanf ("%d%d",&a,&b);
	t[a]+=b;
	if (t[a]>N) t[a]=N;
	s.insert(a);
	}
	else
	{scanf ("%d",&d);
	solve(d);
	}
	}
	return 0;
}
	
