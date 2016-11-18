#include <vector>
#include <cmath>
using namespace std;
const double EPS = 1E-8;
typedef vector<double> vec;
typedef vector<vec> mat;

// solve Ax = b, A is a n*n matrix
vec gauss_jordan(const mat& A, const vec& b) {
  int n = A.size();
  mat B(n, vec(n+1));
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++) B[i][j] = A[i][j];
  // augmented matrices
  for (int i=0; i<n; i++) B[i][n] = b[i];

  for (int i=0; i<n; i++) {
    int pivot = i;
    for (int j=i; j<n; j++) {
      if (abs(B[j][i]) > abs(B[pivot][i])) pivot = j;
    }
    swap(B[i], B[pivot]);

    // no solution, or infinite solution
    if (abs(B[i][i]) < EPS) return vec();

    for (int j=i+1; j<=n; j++) B[i][j] /= B[i][i];
    for (int j=0; j<n; j++) {
      if (i != j) {
        for (int k = i+1; k<=n; k++) B[j][k] -= B[j][i] * B[i][k];
      }
    }
  }
  vec x(n);
  for (int i=0; i<n; i++) x[i] = B[i][n];
  return x;
}

int main() {
  return 0;
}
