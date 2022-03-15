#include<bits/stdc++.h>
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io
{
	int F()
	{
		int n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
	long long G()
	{
		long long n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
}
int R(int l,int r)
{
	return rand()%(r-l+1)+l;
}
const int B=320,H=50;
const int N=222222;
const int maxn=111111;
int Div[222222];
struct IS
{
	int bsum[maxn/B+2];
	int sum[N];
	int query(int r)
	{
		cmin(r,maxn);
		int pl=Div[r];
		int ret=pl?bsum[pl-1]:0;
		ret+=sum[r];
		return ret;
	}
	int query(int l,int r)
	{
		return query(r)-query(l-1);
	}
	void add(int p,int v=1)
	{
		int pl=Div[p];
		for(int i=pl;i<=maxn/B;++i)
			bsum[i]+=v;
		for(int i=p;i<(pl+1)*B;++i)
			sum[i]+=v;
	}
}mon,mag;
struct Gap
{
	int d,l,r,xl,xr;
};
bool operator <(const Gap &x,const Gap &y)
{
	return x.xr<y.xr;
}
const int C=64;
std::set<Gap> t[H+2][C+C];
std::multiset<Gap> gaps[H+2];

void insertgap(const Gap &g)
{
	gaps[g.d].insert(g);
	int d=g.d;
	for(int i=g.l+C-1,j=g.r+C+1;i+1!=j;i>>=1,j>>=1)
	{
		if(~i&1)t[d][i^1].insert(g);
		if(j&1)t[d][j^1].insert(g);
	}
}
void insertgap(int l,int r)
{
	for(int d=1;d<=H;++d)
		if(d<=r-l+1)
		{
			if(2*d-1<=r-l+1)
			{
				insertgap((Gap){d,0,d-1,l,r});
			}
			else
			{
				int fir=(l+d-1)%d,las=r%d;
				if(fir<=las)
				{
					insertgap((Gap){d,fir,las,l,r});
				}
				else
				{
					insertgap((Gap){d,fir,d-1,l,r});
					insertgap((Gap){d,0,las,l,r});
				}
			}
		}
}
void deletegap(const Gap &g)
{
	//gaps[g.d].erase(g);
	int d=g.d;
	for(int i=g.l+C-1,j=g.r+C+1;i+1!=j;i>>=1,j>>=1)
	{
		if(~i&1)t[d][i^1].erase(g);
		if(j&1)t[d][j^1].erase(g);
	}
}
Gap query(int d,int p,int x)
{
	Gap ans=(Gap){d,0,0,0,0x3f3f3f3f};
	for(int i=p+C;i;i>>=1)
	{
		auto tmp=(t[d][i].lower_bound((Gap){d,0,0,0,x}));
		if(tmp!=t[d][i].end())
			if(*tmp<ans)ans=*tmp;
	}
	return ans;
}
int vis[N];
std::set<int> one;
int main()
{
	int T=io::F();
	for(int i=0;i<N;++i)
		Div[i]=i/B;
	for(int i=1;i<=H;++i)
	{
		insertgap((Gap){i,0,i-1,1,maxn});
	}
	one.insert(0);
	one.insert(maxn+1);
	while(T--)
	{
		int op=io::F();
		if(op==1)
		{
			int a=io::F(),b=io::F();
			mon.add(a);
			mag.add(a,b);
		}
		else
		{
			int ans=0;
			int now=0;
			int d=io::F();
			int stop=0;
			while(!stop&&d>0)
			{
				int tmp=mon.query(now+1,now+d);
				if(!tmp)
				{
					now+=d;
					stop=1;
					++ans;
					break;
				}
				int mg=mag.query(now+1,now+d);
				now+=d;
				++ans;
				d-=mg;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}