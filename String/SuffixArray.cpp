#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define N 2500003
char T[N];
int n;
int RA[N], tempRA[N];
int SA[N], tempSA[N];
int c[N];

void radixSort(int k) {
  int i, sum, maxi = max(300, n); // up to 255 ascii chars
  memset(c, 0, sizeof(c));
  for (int i=0; i<n; i++)
    c[i + k < n ? RA[i+k]: 0]++;
  for (i=sum=0; i < maxi; i++) { int t = c[i]; c[i] = sum; sum += t; }
  for (i=0; i<n; i++) tempSA[c[SA[i]+k < n ? RA[SA[i]+k]: 0]++] = SA[i];
  for (i=0; i<n; i++) SA[i] = tempSA[i];
}

void constructSA() {
  int r;
  for (int i=0;i<n; i++) RA[i] = T[i];
  for (int i=0; i<n; i++) SA[i] = i;
  for (int k=1; k<n; k<<=1) {
    radixSort(k);
    radixSort(0);
    tempRA[SA[0]] = r = 0;
    for (int i=1; i<n; i++)
      tempRA[SA[i]] =
        (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r: ++r;
    for (int i=0; i<n; i++)
      RA[i] = tempRA[i];
    if (RA[SA[n-1]] == n-1) break;
  }
}

int main() {
  n = (int)strlen(gets(T));
  T[n++] = '$';
  constructSA();
  for (int i=1; i<n; i++) printf("%d%c", SA[i], i+1<n?' ': '\n');
  return 0;
}
