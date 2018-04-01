//Testing done on https://www.codechef.com/problems/TSORT .
//https://www.codechef.com/viewsolution/18002412 . Passed.
#include<vector>
#include<bits/stdc++.h>
using namespace std;

//Time Complexicity - O(n logn).
//Space Complexicity - O(n).

typedef long long int lli;
void merge(vector <lli> &v,lli startIndex,lli mid,lli endIndex)
{
    lli k=startIndex;
    vector <lli> a;
    vector <lli> b;
    a.clear();
    b.clear();
    a.assign(v.begin()+startIndex, v.begin()+mid);
    b.assign(v.begin()+mid, v.begin()+endIndex);
    lli i=0,l1=mid-startIndex;
    lli j=0,l2=endIndex-mid;

    while(i<l1&&j<l2)
    {
        if(a[i]<b[j])
        {
            v[k++]=a[i++];
        }
        else
        {
            v[k++]=b[j++];
        }
    }

    while(i<l1)
    {
        v[k++]=a[i++];
    }

    while(j<l2)
    {
        v[k++]=b[j++];
    }
}

void sort(vector <lli> &v,lli startIndex,lli endIndex)//[l,r);
{
    if(startIndex>=endIndex-1)
        return;

    lli mid=startIndex+(endIndex-startIndex)/2;
    sort(v,startIndex,mid);
    sort(v,mid,endIndex);
    merge(v,startIndex,mid,endIndex);
}

