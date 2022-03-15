#include <bits/stdc++.h>
using namespace std;
int main (){
	int T;
	scanf ("%d",&T);
	assert(T>=1&&T<=351493);
	while (T--)
	{int op,a,b,d;
	scanf ("%d",&op);
	assert(op==1||op==2);
	if (op==1)
	{scanf ("%d%d",&a,&b);
	assert(a>=1&&a<=100000);
	assert(b>=0&&b<=100000); 
	}
	if (op==2)
	{scanf ("%d",&d);
	assert(d>=1&&d<=100000);
	}
	}
	return 0;
}
	
