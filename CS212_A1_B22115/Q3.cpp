#include<bits/stdc++.h>
using namespace std;

int GCD(int a,int b,int &step){
    if(a == b) return a;

    if((a%11 ==0) && (b%11==0)) return GCD(a/11, b/11,++step)*11;
    else if((a%11 == 0) && (b%11 != 0) && (a%2 != 0)) return GCD(a/11, 2*b,++step);
    else if((a%11 == 0) && (b%11 != 0) && (a%2 == 0)) return GCD(a/11, abs(a-b),++step);
    else if((a%11 != 0) && (b%11 == 0) && (b%2 != 0)) return GCD(2*a,b/11,++step);
    else if((a%11 != 0) && (b%11 == 0) &&(b%2 == 0)) return GCD(abs(a-b), b/11,++step);
    if(a>b) return GCD(a-b,b,++step);
    else return GCD(a,b-a,++step);
    
}


int main(){
    int a,b ;
    int step =0;
    cin>>a>>b;
    cout<<GCD(a,b,step);
    cout<<", Steps:  "<<step;
}