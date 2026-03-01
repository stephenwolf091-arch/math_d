# math_d 
### A Hardware-Optimized, Minimalist Math Library in C

This library is a collection of high-performance numerical methods and mathematical approximations, designed with a focus on **FPU efficiency**, **branchless programming**, and **low-level bit manipulation**.

## ✨ Key Features

* **⚡ High-Performance Trig:** Sine approximation using a 13th-degree Taylor Series, optimized via **Horner's Method** for minimal CPU cycles.
* **🔌 Plug-and-Play Engines:** Universal Derivative and Integral engines using C function pointers (`typedef double (*MathFunc)(double)`).
* **🛠️ Hardware Hacks:** * **Branchless Absolute Value:** Uses IEEE 754 bit-masking to avoid pipeline stalls.
    * **Hex-Float Optimization:** Employs `0x1p-16` for numerical stability and lightning-fast FPU divisions.
* **🏎️ Optimized Integration:** Implementation of the Trapezoidal Rule with a 50% reduction in redundant function calls.

## 🛠️ Usage

```c
#include "math_d.h"

// Example: Calculate the slope of sine at 30 degrees
double slope = diff_d(sin_d, 0.5235); 

// Example: Calculate the area of sine from 0 to PI
double area = integral_d(sin_d, 0, 3.1415);
