//Fenwick Tree - https://kartikkukreja.wordpress.com/2013/12/02/range-updates-with-bit-fenwick-tree/
//Below implementation is for Range updates and Range queries

int n;                  //value of n as per question, generally taken as input
int bit1[n+5], bit2[n+5];
 
//Complexity is O(n)
void initialise(int n) {
    for(int i=1; i<=n; ++i) bit1[i] = 0LL;
    for(int i=1; i<=n; ++i) bit2[i] = 0LL;
}

//Complexity is 4*O(log n)
void U1(int idx, int x, int n) {
    while (idx <= n) {
        bit1[idx] += x;
        idx += (idx & -idx);
    }
}
 
void U2(int idx, int x, int n) {
    while (idx <= n) {
        bit2[idx] += x;
        idx += (idx & -idx);
    }
}
 
void update(int u, int v, int w, int n) {
    U1(u, w, n);
    U1(v+1, -w, n);
    U2(u, w*(u-1), n);
    U2(v+1, -w*v, n);
}
 
//Complexity is 4*O(log n)
int Q1(int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += bit1[idx];
        idx -= (idx & -idx);
    }
    return sum;
}
 
int Q2(int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += bit2[idx];
        idx -= (idx & -idx);
    }
    return sum;
}
 
int Q3(int u) {
    return Q1(u)*u - Q2(u);
}
 
int query(int u, int v) {
    return Q3(v) - Q3(u-1);
}