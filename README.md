# Real Time Scheduler

## Theory

### Definitions

* *t_m*, *m* = 0, 1, ..., *N*: CPU time spent in task priority *m* measured in
  time-span *T*, where 0: highest priority, *N*: lowest priority.

* *T_m* defined as:

  ![T_m = \sum_{i=m}^N t_i](math/T_m.png)

  is CPU time spent in tasks with priority *m*, *m + 1*, ..., *N*.
  Therefore *T = T_0*

* Time ratio:

  ![r_m = t_m/T_m; 0<r_m<1](math/r_m.png)

### Time Scheduling

For given priority *m*, *r_m* is factorized into 2-base fraction:

![r_m = t_m/T_m \simeq Fact2(r_m) = \sum_{i=1}^M a_i 2^{-i}; a_i=0,1](math/fact2.png)

where *M* (default 8) defines accuracy of the factorization:

![|r_m - Fact2(r_m) | < 2^{-M}](math/accur.png)

Each *n*-th element of the factorized ratio *r_m* translates into distribution
of *t_m*'s time ticks in the time-span *T_m* as follows:

![i_k = 2^{n-1}-1 + 2^{n}k; n=1,...,M; k=0,1,...](math/i_k.png)

where *i_k* denotes *k*-th index of *t_m*'s tick in *T_m* time-span, corresponding
to ![2^{-n}](math/2-n.png) element of ratio *r_m*.

## Build

```
cmake -B BUILD .
cmake --build BUILD
```
