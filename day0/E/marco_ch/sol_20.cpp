#include <bits/stdc++.h>
#define lc (pos<<1)
#define rc (pos<<1|1)
using namespace std;
const int X=20;
const int N=300000;
int t[N+5];
bool vis[N+5];
int g,st,ed,ans;
bool tag;
set <int> s;
struct small_seg
{int nxt[N+5];
inline int find(int p)
{if (nxt[p]==p) return p;
return nxt[p]=find(nxt[p]);
}
inline void init()
{for (int i=1;i<=100000+X;i++) nxt[i]=i;
}
}T[X+1];
inline void work()
{if (g>X)
{for (int i=st;i<ed;i+=g)
{ans++;
int tg=0;
for (int j=i;j<i+g;j+=X)
{int x=min(i+g-j,X);
if (j>100000) break;
if (T[x].nxt[j]^j) {tg=1;break;}
}
if (!tg) {tag=0;return;}
}
return;
}
int w=T[g].find(st);
if (w+g-1>=ed) {ans+=(ed-st+1)/g;return;}
tag=0;ans+=((w-st)/g+1);
}
inline void solve(int d)
{int cur=0,c=d;ans=0;
set <int>::iterator it=s.begin();it++;
while (1)
{int pos=cur+1,nxt=(*it),rd=(nxt-pos)/c+1;
nxt=pos+rd*c-1;tag=1;st=pos;ed=nxt;g=c;
work();
if (!tag) break;
while (it!=s.end()&&(*it)<=nxt)
{c-=t[(*it)];it++;
if (c<=0) break;
}
if (c<=0) break;
cur=nxt;
}
printf ("%d\n",ans);
}
int main (){
	int Ti,op,a,b,d,i,j;
	scanf ("%d",&Ti);
	for (i=1;i<=X;i++) T[i].init();
	s.insert(0);
	s.insert(N+1);
	while (Ti--)
	{scanf ("%d",&op);
	if (op==1)
	{scanf ("%d%d",&a,&b);
	for (i=1;i<=X;i++)
	{for (j=a;j>=a-i+1&&j>=1;j--)
	{if (T[i].nxt[j]==j) T[i].nxt[j]=T[i].find(j+i);
	}
	}
	if (b>0&&t[a]==0) s.insert(a);
	t[a]+=b;
	if (t[a]>N) t[a]=N;
	}
	else
	{scanf ("%d",&d);
	solve(d);
	}
	}
	return 0;
}
	
