#include <bits/stdc++.h>
using namespace std;

// Non - preemptive
void display(vector<int> &AT,vector<int> &BT,vector<int> &TAT,vector<int> &WT,int n){
   
    
}

int main(){
    int n;
    cout<<"Enter the no of processes : ";
    cin>>n;

    vector<int> AT = {0,1,3,2};
    vector<int> BT = {8,4,5,9};
    vector<int> TAT(n);
    vector<int> WT(n);

    display(AT,BT,TAT,WT,n);

    float AVG_TAT = 0;
    int sum1 = 0;

    float AVG_WT = 0;
    int sum2 = 0;
    for(int i=0;i<n;i++){
        sum1 = sum1 + TAT[i];
        sum2 = sum2 + WT[i];
    }

    AVG_TAT = (float)sum1/n;
    AVG_WT = (float)sum2/n;
    cout<<AVG_TAT<<" "<<AVG_WT<<endl;


    return 0;
}