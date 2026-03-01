#include <stdio.h>
#include <stdint.h>
#include "math_d.h"

/**
 * @brief Bitwise IEEE 754 Absolute Value
 * Uses a Union-based Type Punning hack to manipulate the sign bit directly.
 * Avoids branching (if/else) to prevent CPU pipeline stalls.
 */
double abs_d(double num) {
    union {
        double d;      // Double-precision floating point view
        uint64_t i;    // 64-bit integer view for bitwise operations
    } bit_hack;

    bit_hack.d = num;
    // Mask out the 63rd bit (sign bit) using 0x7FFFFFFFFFFFFFFF
    // Result: Forces the number to be positive without an FPU comparison.
    bit_hack.i = bit_hack.i & 0x7FFFFFFFFFFFFFFF;

    return bit_hack.d;
}

/**
 * @brief Optimized Sine Function via Taylor Series (13th Degree)
 * Implements the Horner Method to minimize floating-point multiplications.
 * Designed for FMA (Fused Multiply-Add) hardware units.
 */
double sin_d(double x) {
    double x2 = x * x;

    // Pre-calculated Taylor coefficients (1/n!)
    const double c1 = -0.16666666666666666667; // -1/3!
    const double c2 =  0.00833333333333333333; //  1/5!
    const double c3 = -0.00019841269841269841; // -1/7!
    const double c4 =  0.00000275573192239858; //  1/9!
    const double c5 = -0.00000002505210838544; // -1/11!
    const double c6 =  0.00000000016059043837; //  1/13!

    // Efficient polynomial evaluation using nested multiplication
    return x * (1.0 + x2 * (c1 + x2 * (c2 + x2 * (c3 + x2 * (c4 + x2 * (c5 + x2 * c6))))));
}

/**
 * @brief Exponential Function (e^x) Implementation
 * High-performance approximation using Horner's Method up to the 8th degree.
 */
double calce_d(double exp) {
    const double c1 = 0.5;
    const double c2 = 0.16666666666666666667;
    const double c3 = 0.04166666666666666667;
    const double c4 = 0.00833333333333333333; 
    const double c5 = 0.00138888888888888889; 
    const double c6 = 0.00019841269841269841; 
    const double c7 = 0.00002480158730158730; 
    const double c8 = 0.00000275573192239859; 

    return 1.0 + exp * (1.0 + exp * (c1 + exp * (c2 + exp * (c3 + exp * (c4 + exp * (c5 + exp * (c6 + exp * (c7 + exp * c8))))))));
}

/**
 * @brief Numerical Differentiation - Central Difference Method
 * Uses a Hexadecimal Floating-Point literal (0x1p-16) for the step size 'h'.
 * Hex-floats are powers of 2, allowing the FPU to perform divisions/multiplications 
 * by simply adjusting the exponent bits, ensuring maximum precision and speed.
 */
double diff_d(MathFunc f, double x) {
    const double h = 0x1p-16; // Exact power of 2 (2^-16) for FPU efficiency
    
    // Central difference formula: [f(x + h) - f(x - h)] / 2h
    // Provides O(h^2) accuracy, significantly better than Forward Difference.
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

/**
 * @brief Numerical Integration - Optimized Trapezoidal Rule
 * Calculates the area under a curve. 
 * Optimization: Instead of calculating each trapezoid independently, internal points 
 * are summed once, reducing redundant function calls and floating-point arithmetic.
 */
double integral_d(MathFunc f, double a, double b) {
    const int N = 100000;              // Number of partitions
    double dx = (b - a) / N;           // Width of each step
    
    // Boundary points are handled separately (each belongs to only one trapezoid)
    double total_sum = (f(a) + f(b)) * 0.5;

    // Interior points belong to two adjacent trapezoids, so they have a full weight of 1.
    // This reduces the number of function calls by 50% compared to a naive implementation.
    for (int i = 1; i < N; i++) {
        total_sum += f(a + i * dx);
    }

    return total_sum * dx;
}