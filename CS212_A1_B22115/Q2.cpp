#include<bits/stdc++.h>
using namespace std;
bool bins2D(int v[][20],int target){
    int si = 0;
    int sj = 19;

    int col = 20;
    int row = 15;

    while(si<15 && sj>=0){
        if(v[si][sj] == target) {
            cout<<"Found"<<endl;
            cout<<"Row: "<<si+1<<" Col: "<<sj+1<<endl;
            return true;
        }
        else if(v[si][sj] > target) sj--;
        else si++;
    }
    return false;
}
int main(){
    int arr[15][20];
    int k=0;
    for(int i=0;i<15;i++){
        for(int j=0;i<20;j++){
            arr[i][j]=k++;
        }
    }
    int target;
    cout<<"Enter input: ";
    cin>>target;
    if(!bins2D(arr,target)) cout<<"Not Found";
}   