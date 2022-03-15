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
    printf("%d\n",T);
    for(int i=1;i<=10000;++i)
        p[i]=i*5;
    for(int i=50001;i<=100000;++i)
        p[i]=i;
    std::random_shuffle(p+50001,p+100001);
    std::random_shuffle(p+1,p+10001);
    for(int i=1;i<=10000;++i)
        printf("1 %d 0\n",p[i]);
    for(int i=50001;i<=100000;++i)
    {
        printf("1 %d 0\n",p[i]);
        for(int j=5;j<=9;j+=1)
            printf("2 %d\n",j);
    }
    int tot=0;
    for(int i=310001;i<=T;++i)
    {
        int op=R(1,1000)<=5?1:2;
        if(now==100000)op=2;
        if(op==1)
        {
            int x,y;
            x=R(50001,100000);
            y=1;
            ++tot;
            printf("%d %d %d\n",op,x,y);
        }
        if(op==2)
        {
            int d=R(5,20+tot/2);
            printf("%d %d\n",op,d);
        }
    }
    return 0;
}