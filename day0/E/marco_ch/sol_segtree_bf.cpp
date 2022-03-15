#include <bits/stdc++.h>
#define lc (pos<<1)
#define rc (pos<<1|1)
using namespace std;
const int N=300000;
int t[N+5],gp[N+5];
int minn[4*N+5],maxn[4*N+5];
bool vis[N+5];
set <int> s,ss;
inline int getmin(int a,int b)
{if (a==-1) return b;
if (b==-1) return a;
return (a<b?a:b);
}
inline int getmax(int a,int b)
{if (a==-1) return b;
if (b==-1) return a;
return (a>b?a:b);
}
inline void update(int pos,int l,int r,int pl)
{if (l==r) {minn[pos]=maxn[pos]=gp[pl];return;}
int mid=(l+r)>>1;
if (pl<=mid) update(lc,l,mid,pl);
else update(rc,mid+1,r,pl);
minn[pos]=getmin(minn[lc],minn[rc]);
maxn[pos]=getmax(maxn[lc],maxn[rc]);
}
inline void add(int o)
{set <int>::iterator it=s.lower_bound(o);it--;
int w=(*it);
int n1=o-w-1;
int n2=gp[w]-n1-1;
gp[w]=n1;gp[o]=n2;
if (w) update(1,1,N+5,w);
update(1,1,N+5,o);
s.insert(o);
}
int ans=0,st,ed,g;
bool tag=1;
int find(int pos,int l,int r,int lp,int rp)
{if (maxn[pos]<g) return -1;
if (l==r)
{int o=(l-st)/g,y=(min(ed,l+gp[l]+1)-st)/g;
if (y-o>=2) return l;
return -1;
}
int mid=(l+r)>>1;
if (rp<=mid) return find(lc,l,mid,lp,rp);
if (lp>mid) return find(rc,mid+1,r,lp,rp);
int tp=find(lc,l,mid,lp,mid);
if (tp!=-1) return tp;
return find(rc,mid+1,r,mid+1,rp);
}
inline void work()
{set <int>::iterator itt=s.lower_bound(st);
int pl=(*itt);
if (pl>st+g-1) {tag=0;ans++;return;}
int o=find(1,1,N+5,st,min(ed,N+5));
if (o==-1) {ans+=(ed-st+1)/g;return;}
tag=0;
ans+=((o-st)/g+2); 
return;
}
inline void solve(int d)
{int cur=0,c=d;ans=0;
set <int>::iterator it=ss.begin();it++;
while (1)
{int pos=cur+1;
int nxt=(*it);
int rd=(nxt-pos)/c+1;
nxt=pos+rd*c-1;
tag=1;
st=pos;ed=nxt;g=c;
work();
if (!tag) break;
while (it!=ss.end()&&(*it)<=nxt)
{c-=t[(*it)];it++;
if (c<=0) break;
}
if (c<=0) break;
cur=nxt;
}
printf ("%d\n",ans);
}
int main (){
	//freopen ("1.in","r",stdin);
	//freopen ("1.out","w",stdout); 
	memset(minn,-1,sizeof(minn));
	memset(maxn,-1,sizeof(maxn));
	int T,op,a,b,d;
	scanf ("%d",&T);
	gp[0]=300000;
	s.insert(0);
	ss.insert(0);
	s.insert(300001);
	ss.insert(300001);
	while (T--)
	{scanf ("%d",&op);
	if (op==1)
	{scanf ("%d%d",&a,&b);
	if (!vis[a]) {vis[a]=1;add(a);}
	if (b>0&&t[a]==0) ss.insert(a);
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
	
