#include<bits/stdc++.h>
#include<math.h>
using namespace std;
int random_no(int min,int max){
    
    int range = max - min + 1;
    return rand() % range + min;
}

int pivotf(vector<int> &v ,int s,int e)
{
    int pivot =s;

    int l=s,r=e;

    while(l<r){
        while(l<=e-1 && v[l] <= v[pivot] ) l++;
        while((r>=s+1 && v[r] > v[pivot]) ) r--;
        if(l<r) swap(v[l],v[r]); 
    }
    swap(v[pivot],v[r]);
    return r;
}
int random_pivot(vector<int>&v,int s,int e){
    int c=s;
    int half = s + (e-s)/2;
    int total = 20;

    int mingap=INT_MAX;
    int index = s;

    while( total-- && abs(half-c)>=1 ){
        int random_index = random_no(s,e);
        c=s;
        for(int i=s;i<=e;i++){
            if(v[i]<=v[random_index] && i != random_index) c++;
        }
        if(abs(half-c)<mingap){
            mingap = abs(half-c);
            index = random_index;
        }
    }
    swap(v[index],v[s]);
    
    int piv = pivotf(v,s,e);

    return piv;
}

void breakf(vector<int>& v,int s,int e,int& sub_problem,int inc){

    if(s>=e){
        sub_problem-=inc;
        return;
    }
    cout<<"Sub Problem: "<<sub_problem<<" Array size = "<<e-s+1<<" : ";
    for(int i=s;i<=e;i++) cout<<v[i]<<" ";
    cout<<endl;
    for(int i = s;i<e;i++){
        if(v[i]>v[i+1]) break;
        else if(v[i]<=v[i+1] && i== e-1) {
            sub_problem-=inc;
            return;
        }
    }

    
    int pivot = random_pivot(v,s,e);

    if(pivot-s < e-pivot){
        breakf(v,s,pivot-1,++sub_problem,1);
        breakf(v,pivot+1,e,sub_problem+=2,2);
    }
    else{
        breakf(v,pivot+1,e,sub_problem+=1,1);
        breakf(v,s,pivot-1,sub_problem+=2,2);
    }
}

int main(){
    vector<int> v ={1,2,3,2,2,44,656,3,3,2,5,3,1,4,5,2,4,5,2,2,5,6,67,7,8,8,5,3,2,6,3,3,3,2,3,445,2,1,4,1,1,4,5,2,1,4,3,2,2,4,434,2,132,4,42,4,4,2345534,2};
    int sub_problem = 1;
    breakf(v,0,v.size()-1,sub_problem,0);
    for(auto i:v) cout<<i<<" ";
}

// we started from 31 subproblem to 19 sub problem now