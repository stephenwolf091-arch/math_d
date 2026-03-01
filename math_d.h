#ifndef MATH_D_H
#define MATH_D_H

/**
 * @file math_d.h
 * @brief High-performance, hardware-optimized minimalist math library.
 * Designed for FPU efficiency, bit-level manipulations, and numerical analysis.
 */

/* --- Function Pointer Definition --- */

/**
 * @brief Standard mathematical function signature: f(double) -> double.
 * This allows the derivative and integral engines to accept any conforming function.
 */
typedef double (*MathFunc)(double);

/* --- Core Mathematical Functions --- */

/**
 * @brief Approximates Sine using 13th-degree Taylor Series (Horner's Method).
 */
double sin_d(double radian);

/**
 * @brief Computes absolute value using IEEE 754 bit-masking (Branchless).
 */
double abs_d(double number);

/**
 * @brief Approximates e^x using 8th-degree Taylor Series (Horner's Method).
 */
double calce_d(double exp);

/* --- Numerical Analysis Engines --- */

/**
 * @brief Numerical differentiation using Central Difference Method (O(h^2) accuracy).
 * Uses FPU-optimized hexadecimal floating-point step size.
 */
double diff_d(MathFunc f, double x);

/**
 * @brief Numerical integration using Optimized Trapezoidal Rule.
 * Optimized to reduce function calls by 50% through algebraic simplification.
 */
double integral_d(MathFunc f, double begin, double end);

#endif // MATH_D_H