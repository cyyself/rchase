# rchase

A simple random pointer chasing benchmark written in C++.

## Why random pointer chasing?

Pointer chasing is a common operation in many applications, and we use this to analyze micro architectural features such as cache size probeing. However, some modern CPUs (Like Arm Neoverse N2) may implement some temporal prefetchers like CMC (Correlated Miss Caching) that can save the history address of memory accesses and prefetch the next memory location based on the history. This may lead to inaccurate cache size probeing results.

To mitigate this, we introduce randomness into the pointer chasing process by XORing the current pointer value with a random number before calculating the next pointer. This makes it harder for the prefetcher to predict future accesses, leading to more accurate measurements.

## How to use

```bash
make
./rchase <size_in_MB> <num_iterations>
```
