#include<bits/stdc++.h>
using namespace std;
#pragma optimizer(-Ofast)
#define LL long long
#define ULL unsigned long long
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
#define pll pair<LL,LL>
#define x first
#define y second
#define pi acos(-1)
#define sqr(x) ((x)*(x))
#define pdd pair<double,double>
#define MEMS(x) memset(x,-1,sizeof(x))
#define MEM(x) memset(x,0,sizeof(x))
#define less Less
#define EPS 1e-4
#define arg ARG
#define pdd pair<double,double>
#define cpdd const pdd
#define rank Rank
#define MXN 15000
//#define MXN 300005
pdd operator + (cpdd &p, cpdd &q) {
    return {p.x+q.x, p.y+q.y};
}
pdd operator - (cpdd &p) {
    return {-p.x, -p.y};
}
pdd operator - (cpdd &p, cpdd &q) {
    return (p) + (-q);
}
pdd operator * (cpdd &p,double f) {
    return {f*p.x, f*p.y};
}
double operator * (cpdd &p, cpdd &q) {
    return p.x*p.x + p.y*p.y;
}
double abs(cpdd &p) { return hypot(p.x, p.y); }
double arg(cpdd &p) { return atan2(p.y, p.x); }
double cross(cpdd &p, cpdd &q) { return p.x*q.y - p.y*q
.x; }
double cross(cpdd &p, cpdd &q, cpdd &o) { return cross(p-o, q-o); }
pdd operator * (double f, cpdd &p) { return p*f; } //!! Not f*p !!
double arc(vector<pdd> &p){
    double res=0;
    for(int i = 0;i<p.size();i++){
        res+=abs(p[i]-p[(i+1)%p.size()]);
    }
    return res;
}
double surface(vector<pdd> &p){
    double res=0;
    for(int i = 0;i<p.size();i++){
        res+=cross(p[i],p[(i+1)%p.size()]);
    }
    res=abs(res)/2;
   // printf("res:%lf\n",res);
    //for(auto it:p)
     //   printf("%lf %lf\n",it.x,it.y);
    /*if(res<0.1){
        printf("%lf\n",res);
        for(auto it:p)
        printf("%lf %lf\n",it.x,it.y);
        getchar();
    }*/
    return res;
}
double getsurface(vector<pdd> p, double dis,double target){
    vector<pdd> q;
    double last=dis;
   //printf("%lf\n",dis);
    for(int i = 0;i<p.size()-1;i++){
        while(abs(p[i+1]-p[i])>=last){
            //printf("%lf %lf\n",abs(p[i+1]-p[i]),last);
            //if(q.size()){
            //    printf("%lf %lf %lf %lf\n",p[i].x,p[i].y,q.back().x,q.back().y);
             //   getchar();
           // }
            pdd pp=p[i+1]-p[i];
            
          //  printf("%lf %lf\n",pp.x,pp.y);
            pp = pp * (1/abs(pp));
            //printf("%lf %lf\n",pp.x,pp.y);
            q.pb(p[i]+pp*last);
            p[i] = p[i] + pp * last;
           // printf("add: %lf %lf\n",p[i].x,p[i].y);
            last=target;
        }
        last-=abs(p[i+1]-p[i]);
    }
    return surface(q);
}
int main(){
    int n,k;
    scanf("%d %d",&n,&k);
    vector<pdd> v;
    for(int i = 0;i<n;i++){
        double x,y;
        scanf("%lf %lf",&x,&y);
        v.pb(mp(x,y));
    }
    double total = arc(v);
    double kunit = total / k;
   // printf("%lf\n",kunit);
    double res=1e100;
    for(int i = 0;i<n;i++){
        v.pb(*v.begin());
       // printf("%d\n",i);
        double Min=0,Max=min(abs(v[1]-v[0]),kunit);
        for(int j =0;j<100;j++){
            double mid1=(Min*2+Max)/3,mid2=(Min+Max*2)/3;
            if(getsurface(v,mid1,kunit)<getsurface(v,mid2,kunit)){
                Max=mid2;
            }
            else{
                Min=mid1;
            }
        }
        res=min(res,getsurface(v,Min,kunit));
        //for(double j = 0;j<abs(v[1]-v[0])&&j<kunit;j+=1e-6){
          //  printf("%lf\n",j);
         //   res=min(getsurface(v,j,kunit),res);
        //}
        v.erase(v.begin());
    }
    printf("%.12lf\n",res);
    return 0;
}
