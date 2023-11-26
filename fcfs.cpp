#include <bits/stdc++.h>
using namespace std;

// Non - preemptive
void display(vector<int> &AT,vector<int> &BT,vector<int> &TAT,vector<int> &WT,int n){
    vector<int> CT(n);

    CT[0] = BT[0] - AT[0]; 
    
    // calculating Completion Time
    for(int i=1;i<n;i++){
        CT[i] = BT[i] + CT[i-1];
    }

    // Calculating Turnaround Time and waiting Time
    for(int i=0;i<n;i++){
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
    }

    for(int i=0;i<n;i++){
        cout<<CT[i]<<" ";
    }
    cout<<endl;
    float AVG_TAT = 0;

    for(int i=0;i<n;i++){
        cout<<TAT[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<WT[i]<<" ";
    }
    cout<<endl;
    
}

int main(){
    int n;
    cout<<"Enter the no of processes : ";
    cin>>n;

    vector<int> AT = {0,1,2,3,4};
    vector<int> BT = {2,3,5,4,6};
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
