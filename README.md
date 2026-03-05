# math_d 
### A Hardware-Optimized, Minimalist Math Library in C

This library is a collection of high-performance numerical methods and mathematical approximations, designed with a focus on **FPU efficiency**, **branchless programming**, and **low-level bit manipulation**.

## ✨ Key Features

* **⚡ High-Performance Trig:** Sine approximation using a 13th-degree Taylor Series, optimized via **Horner's Method** for minimal CPU cycles.
* **🔌 Plug-and-Play Engines:** Universal Derivative and Integral engines using C function pointers (`typedef double (*MathFunc)(double)`).
* **🛠️ Hardware Hacks:** * **Branchless Absolute Value:** Uses IEEE 754 bit-masking to avoid pipeline stalls.
    * **Hex-Float Optimization:** Employs `0x1p-16` for numerical stability and lightning-fast FPU divisions.
* **🏎️ Optimized Integration:** Implementation of the Trapezoidal Rule with a 50% reduction in redundant function calls.
* **🎮 L1-Cache Optimized 4x4 Matrices:** Continuous memory layout (`float m[16]`) perfectly matching standard 64-byte cache lines to eliminate cache misses during simulation loops.
* **🚀 Zero-Branching Matrix Ops:** Fully loop-unrolled addition, subtraction, and multiplication functions for maximum instruction throughput.
* **🤖 Auto-Vectorization Ready:** Matrix multiplication uses the row-linear combination method, explicitly designed to trigger compiler-level SIMD (SSE/AVX/NEON) optimizations (-O3) without manual intrinsics.

## 🛠️ Usage

```c
#include "math_d.h"

// Example 1: Calculate the slope of sine at 30 degrees
double slope = diff_d(sin_d, 0.5235); 

// Example 2: Calculate the area of sine from 0 to PI
double area = integral_d(sin_d, 0, 3.1415);

// Example 3: Hardware-optimized matrix operations
mat4 matA, matB, result;

mat4_identity(&matA); // Initialize as identity matrix
mat4_identity(&matB);

// Multiply matrices (SIMD-friendly, unrolled)
mat4_multiply(&result, &matA, &matB);

// Example 4: Integer Square Root (Newton-Raphson, requires hardware division)
unsigned int root_v1 = sqrtv1_d(1024); // Expected: 32

// Example 5: Fast Inverse Square Root Hack (Requires FPU, Quake III style)
unsigned int root_v2 = sqrtv2_d(1024); // Expected: 32

// Example 6: Pure Bitwise Square Root (No division, no FPU, best for bare-metal)
unsigned int root_v3 = sqrtv3_d(1024); // Expected: 32
```

## Build & Run
```
gcc main.c math_d.c -o math_test -O3
./math_test