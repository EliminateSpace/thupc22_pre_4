#include<bits/stdc++.h>

int R(int l,int r)
{
	return rand()%(r-l+1)+l;
}
int main()
{
	int T = 351493;
	printf("%d\n",T);
	for(int i=0;i<12500;++i)
	{
		printf("1 %d 0\n",i*8+1);
		printf("2 4\n");
		printf("1 %d 0\n",i*8+8);
		printf("2 4\n");
	}
	T-=12500*4;
	for(int i=1;i<=100000;++i)
		printf("2 4\n");
	T-=100000;
	T/=2;
	while(T--)
	{
		printf("1 %d %d\n",R(75000,100000),R(0,1));
		printf("2 4\n");
	}
	printf("2 4\n");
	return 0;
}