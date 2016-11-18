## Useful formula

- first kind Stirling

    the number of ways to arrange $n$ objects into $k$ nonempty cycles
    - $s(n, k) = s(n-1, k-1) + (n-1) * s(n-1, k)$
    
- second kind Stirling

    the number of ways to arrange $n$ object into $k$ nonempty subsets
    - $S(n, k) = \frac{1}{k!} \sum_{j=1}^k(-1)^{k-j} C(k,j)j^n$
    - $S(n,k) = S(n-1, k-1) + k * S(n-1, k)$
    
- catalan number

    - $C_0 = 1, C_{n+1} = \sum_{i=0}^nC_i  C_{n-1}$
    - $C_0 = 1, C_{n+1} = \frac{2(2n+1)}{n+2}C_n$
    - $C_n = \binom{2n}{n} - \binom{2n}{n+1}$
    - $C_n = \frac{1}{n+1}\binom{2n}{n}$

## Combinatorics: Box-Ball

$N$ ball, $M$ box

- ball same, box same, no empty
    $P_m(N)$
    
- ball same, box same, allow empty
    $P_m(N+M)$

- ball same, box unique, no empty
    $C(N-1, M-1)$
    
- ball same, box unique, allow empty
    $C(N+M-1, M-1)$
    
- ball unique, box same, no empty
    $S(N, M)$
- ball unique, box same, allow empty
    $\sum_{i=1}^M S(N, i)$
- ball unique, box unique, no empty
    $M! * S(N,M)$

- ball unique, box unique, allow empty
    $M^N$