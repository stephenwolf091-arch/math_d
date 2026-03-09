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

/**
 * @brief  Calculating For RK4 Method.
 */
typedef float (*DifferentialFunc)(float, float);

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


/**
 * @file math_d.h
 * @brief A high-performance, L1-cache friendly mathematics library for physics and 3D simulations.
 * * @details This library provides fundamental mathematical structures and operations 
 * optimized for hardware-level efficiency. It specifically utilizes 1D arrays and loop 
 * unrolling to maximize CPU instruction throughput, avoid branching overhead, and 
 * perfectly align with standard CPU cache line sizes.
 */

/**
 * @brief A 4x4 matrix structure optimized for continuous memory layout.
 * * @details The matrix is represented as a single 1D array of 16 floats (64 bytes). 
 * This exactly matches the standard L1 cache line size, preventing cache misses. 
 * It uses row-major order, ensuring compatibility with hardware-level SIMD vectorization 
 * and continuous memory access.
 */
typedef struct {
    float m[16];
} __attribute__((aligned(16))) mat4;

void mat4_add(mat4 *result, const mat4 *a, const mat4 *b);

void mat4_sub(mat4 *result, const mat4 *a, const mat4 *b);

void mat4_multiply(mat4 *restrict result, const mat4 *restrict a, const mat4 *restrict b);

void mat4_identity(mat4 *result);

/**
 * @brief Computes the integer square root using the Newton-Raphson method.
 *
 * @details Calculates the floor of the square root of an unsigned integer.
 * It utilizes an integer-optimized Newton-Raphson iteration. The division by 2
 * is replaced by a right bit-shift (>> 1) to save hardware clock cycles.
 *
 * @note Relies on the hardware division operator (/). If the target architecture 
 * lacks a dedicated hardware divider, this operation will be computationally expensive.
 *
 * @param S The unsigned integer for which the square root is to be calculated.
 * @return The integer square root of S (floor(sqrt(S))).
 */
unsigned int sqrtv1_d(unsigned int S);

/**
 * @brief Computes the integer square root using the Fast Inverse Square Root algorithm.
 *
 * @details Adapts the Quake III engine algorithm (0x5f3759df) to compute a highly 
 * optimized square root. Performs bit-level manipulation (type punning) on the 
 * IEEE 754 floating-point representation to quickly approximate 1/sqrt(S), 
 * and refines it with a single Newton-Raphson step.
 *
 * @note Strictly dependent on IEEE 754 compliance and the presence of a hardware 
 * Floating Point Unit (FPU). Do not use on bare-metal systems without an FPU.
 *
 * @param S The unsigned integer for which the square root is to be calculated.
 * @return The integer square root of S (floor(sqrt(S))).
 */
unsigned int sqrtv2_d(unsigned int S);

float rk4_step_d(DifferentialFunc f, float t, float y, float h);



#endif // MATH_D_H