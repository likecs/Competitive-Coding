/***
 *  Merge Sort Algorithm for vector<long long int>.
 *
 *  Usage -
 *  For call use function call-
 *    sort(<name of vector>,0,<size of vector>);
 *
 *  Testing done on https://www.codechef.com/problems/TSORT .
 *  https://www.codechef.com/viewsolution/18002414 . Passed.
 *  Time Complexicity - O(n logn).
 *  Space Complexicity - O(n).
 ***/
void merge(vector <long long int> &v, long long int startIndex,long long int mid,long long int endIndex)
{
    long long int k=startIndex;
    vector <long long int> a;
    vector <long long int> b;
    a.clear();
    b.clear();
    a.assign(v.begin()+startIndex, v.begin()+mid);
    b.assign(v.begin()+mid, v.begin()+endIndex);
    long long int i=0,l1=mid-startIndex;
    long long int j=0,l2=endIndex-mid;

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

void sort(vector <long long int> &v,long long int startIndex,long long int endIndex)
//sort v with index in range [l,r).
{
    if(startIndex>=endIndex-1)
        return;

    long long int mid=startIndex+(endIndex-startIndex)/2;
    sort(v,startIndex,mid);
    sort(v,mid,endIndex);
    merge(v,startIndex,mid,endIndex);
}

