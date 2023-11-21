#ifdef STREAMING_JUDGE
#include"io.h"
#define next_token io.next_token
#else
#include<string>
#include<iostream>
std::string next_token(){std::string s;std::cin>>s;return s;}
#endif

#include<cstdio>
#include<cstdlib>
#include<algorithm>

#define divide 1350
#define offset 1073741824

int T[divide];  //T[i]=counts of value i in array(after hash)
int n;

int hashfun(int x,int t){
    long long int xx=x+offset;
    long long int pow=1;
    for(int i=1;i<=t;i++){
        pow=pow*divide;
    }
    return (xx%(pow*divide))/pow;
}

int find_kth_of_T(int k){
    int accumulat=0;
    for(int i=0;i<divide;i++){
        accumulat+=T[i];
        if (accumulat>=k){
            return i;
        }
    }
}

int main()
{

    int a;
    int ans[3]={0};
    int lefts=0;


    n=atoi(next_token().c_str());

    for(int i=0; i<divide; i++)
        T[i]=0;
    for(int i=0; i<n; i++){
        a=atoi(next_token().c_str());
        //printf("%d",a);
        T[hashfun(a,2)]++;
    }
    ans[0]=find_kth_of_T(n/2+1);    //find mid
    //printf("%d\n",ans[0]);

    n=atoi(next_token().c_str());
    for(int i=0; i<divide; i++)
        T[i]=0;
    for(int i=0; i<n; i++){
        a=atoi(next_token().c_str());
        if (hashfun(a,2)<ans[0]){
            lefts++;
        }else if (hashfun(a,2)==ans[0]){
            T[hashfun(a,1)]++;
        }
    }
    ans[1]=find_kth_of_T(n/2+1-lefts);    //find mid
    //printf("%d\n",ans[1]);


    n=atoi(next_token().c_str());
    for(int i=0; i<divide; i++)
        T[i]=0;
    for(int i=0; i<n; i++){
        a=atoi(next_token().c_str());
        if (hashfun(a,2)==ans[0]){
            if (hashfun(a,1)<ans[1]){
                lefts++;
            }else if (hashfun(a,1)==ans[1]){
                T[hashfun(a,0)]++;
            }
        }
    }
    ans[2]=find_kth_of_T(n/2+1-lefts);    //find mid


    int S=(ans[0]*divide+ans[1])*divide+ans[2]-offset;
    printf("%d\n",S);
    //system("pause");
}
