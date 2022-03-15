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
int p[111111];
int main()
{
    char s[111];
    int ta=io::F();
    sprintf(s,"%d.in",ta);
    freopen(s,"w",stdout);
    srand(time(0));
    int now=0;
    int T=351493;
    const int B = 170;
    printf("%d\n",T);
    for(int i=1;i<=100000/B;++i)
        p[i]=i*B;
    std::random_shuffle(p+1,p+100000/B+1);
    for(int i=1;i<=100000/B;++i)
        printf("1 %d 0\n",p[i]);
    T-=100000/B;
    for(int i=50000/B*B,j=B;j;i+=j,--j)
    {
        printf("1 %d 1\n",i);
        --T;
    }
    while(T--)
    {
        int op=R(0,2)?2:1;
        if(op==1)
        {
            int x=R(50001,100000);
            int y=0;
            printf("%d %d %d\n",op,x,y);
        }
        else
        {
            int d=R(B,B+3);
            printf("%d %d\n",op,d);
        }
    }
    return 0;
}