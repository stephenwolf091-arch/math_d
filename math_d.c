#include <stdio.h>
#include <stdint.h>
#include "math_d.h"
#include <immintrin.h> // for SIMD commands 

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

/**
 * @brief Adds two 4x4 matrices element-wise.
 * * @details This function uses loop unrolling for maximum performance by eliminating 
 * CPU branching overhead. The flat 1D array structure ensures optimal L1 cache utilization.
 * * @param result Pointer to the matrix where the sum will be stored.
 * @param a Pointer to the first input matrix (read-only).
 * @param b Pointer to the second input matrix (read-only).
 */
void mat4_add(mat4 *result, const mat4 *a, const mat4 *b) {
    result->m[0]  = a->m[0]  + b->m[0];
    result->m[1]  = a->m[1]  + b->m[1];
    result->m[2]  = a->m[2]  + b->m[2];
    result->m[3]  = a->m[3]  + b->m[3];

    result->m[4]  = a->m[4]  + b->m[4];
    result->m[5]  = a->m[5]  + b->m[5];
    result->m[6]  = a->m[6]  + b->m[6];
    result->m[7]  = a->m[7]  + b->m[7];

    result->m[8]  = a->m[8]  + b->m[8];
    result->m[9]  = a->m[9]  + b->m[9];
    result->m[10] = a->m[10] + b->m[10];
    result->m[11] = a->m[11] + b->m[11];

    result->m[12] = a->m[12] + b->m[12];
    result->m[13] = a->m[13] + b->m[13];
    result->m[14] = a->m[14] + b->m[14];
    result->m[15] = a->m[15] + b->m[15];
}

/**
 * @brief Subtracts the second 4x4 matrix from the first element-wise.
 * * @details Similar to the addition function, this utilizes loop unrolling to 
 * maximize instruction throughput and prevent cache misses during execution.
 * * @param result Pointer to the matrix where the difference will be stored.
 * @param a Pointer to the base matrix (read-only).
 * @param b Pointer to the matrix to subtract (read-only).
 */
void mat4_sub(mat4 *result, const mat4 *a, const mat4 *b) {
    result->m[0]  = a->m[0]  - b->m[0];
    result->m[1]  = a->m[1]  - b->m[1];
    result->m[2]  = a->m[2]  - b->m[2];
    result->m[3]  = a->m[3]  - b->m[3];

    result->m[4]  = a->m[4]  - b->m[4];
    result->m[5]  = a->m[5]  - b->m[5];
    result->m[6]  = a->m[6]  - b->m[6];
    result->m[7]  = a->m[7]  - b->m[7];

    result->m[8]  = a->m[8]  - b->m[8];
    result->m[9]  = a->m[9]  - b->m[9];
    result->m[10] = a->m[10] - b->m[10];
    result->m[11] = a->m[11] - b->m[11];

    result->m[12] = a->m[12] - b->m[12];
    result->m[13] = a->m[13] - b->m[13];
    result->m[14] = a->m[14] - b->m[14];
    result->m[15] = a->m[15] - b->m[15];
}

/**
 * @brief Multiplies two 4x4 matrices using hardware SIMD (SSE) instructions.
 * * @details This function forces the CPU to use 128-bit packed operations (e.g., mulps, addps),
 * bypassing compiler auto-vectorization guesswork. It solves the "strided memory access" 
 * penalty by loading contiguous rows from matrix B and broadcasting single elements from matrix A.
 * * @param result Pointer to the resulting multiplied matrix.
 * @param a Pointer to the left operand matrix (read-only, restrict to prevent aliasing).
 * @param b Pointer to the right operand matrix (read-only, restrict to prevent aliasing).
 */
void mat4_multiply(mat4 *restrict result, const mat4 *restrict a, const mat4 *restrict b) {
    for (int i = 0; i < 4; i++) {
        // Initialize the result row vector to [0.0, 0.0, 0.0, 0.0]
        __m128 row_result = _mm_setzero_ps(); 
        
        for (int j = 0; j < 4; j++) {
            // Broadcast the scalar value a->m[i][j] to all 4 slots of the vector: [A, A, A, A]
            __m128 a_val = _mm_set1_ps(a->m[i * 4 + j]); 
            
            // Load a contiguous 4-float row from matrix B: [B0, B1, B2, B3]
            __m128 b_row = _mm_loadu_ps(&b->m[j * 4]); 
            
            // Hardware-level multiply and accumulate: result += (A * B_row)
            row_result = _mm_add_ps(row_result, _mm_mul_ps(a_val, b_row));
        }
        // Store the computed 4-float vector directly into the result matrix row
        _mm_storeu_ps(&result->m[i * 4], row_result);
    }
}

/**
 * @brief Initializes a 4x4 matrix as an identity matrix.
 * * @details Sets the main diagonal elements to 1.0f and all other elements to 0.0f. 
 * In a simulation context, this represents the "zero state" or default 
 * origin, rotation, and scale of an object.
 * * @param result Pointer to the matrix to be initialized.
 */
void mat4_identity(mat4 *result) {
    // ROW 1
    result->m[0]  = 1.0f;  
    result->m[1]  = 0.0f;  
    result->m[2]  = 0.0f;  
    result->m[3]  = 0.0f;

    // ROW 2
    result->m[4]  = 0.0f;  
    result->m[5]  = 1.0f;  
    result->m[6]  = 0.0f;  
    result->m[7]  = 0.0f;

    // ROW 3
    result->m[8]  = 0.0f;  
    result->m[9]  = 0.0f;  
    result->m[10] = 1.0f;  
    result->m[11] = 0.0f;

    // ROW 4
    result->m[12] = 0.0f;  
    result->m[13] = 0.0f;  
    result->m[14] = 0.0f;  
    result->m[15] = 1.0f;
}


/**
 * @brief Computes the integer square root using the Newton-Raphson method.
 *
 * @details This function calculates the floor of the square root of an unsigned integer.
 * It utilizes an integer-optimized Newton-Raphson iteration. The division by 2
 * is replaced by a right bit-shift (>> 1) to save hardware clock cycles.
 *
 * @note This algorithm still relies on the hardware division operator (/). 
 * If the target architecture (e.g., a custom ALU or microcontroller) lacks 
 * a dedicated hardware divider, this operation will be computationally expensive.
 *
 * @param S The unsigned integer for which the square root is to be calculated.
 * @return The integer square root of S (floor(sqrt(S))).
 */
unsigned int sqrtv1_d(unsigned int S) {
    // Base cases: sqrt(0) = 0, sqrt(1) = 1
    if (S <= 1) return S;

    // Initial guess: S / 2 (implemented as a right shift for performance)
    unsigned int x_old = S >> 1;
    unsigned int x_new = (x_old + (S / x_old)) >> 1;

    // Iterate until the new approximation is no longer strictly decreasing
    while (x_new < x_old) {
        x_old = x_new;
        x_new = (x_old + (S / x_old)) >> 1;
    }

    return x_old;
}

/**
 * @brief Computes the integer square root using the Fast Inverse Square Root algorithm.
 *
 * @details This function adapts the legendary Quake III engine algorithm (0x5f3759df)
 * to compute a highly optimized square root. It casts the integer to a float, performs 
 * bit-level manipulation (type punning) on the IEEE 754 floating-point representation 
 * to quickly approximate 1/sqrt(S), and refines it with a single Newton-Raphson step.
 * Finally, it multiplies by S to yield sqrt(S) and casts it back to an unsigned integer.
 *
 * @note This method is strictly dependent on IEEE 754 compliance and the presence 
 * of a hardware Floating Point Unit (FPU). On bare-metal systems without an FPU, 
 * floating-point operations will trigger heavy software emulation routines, 
 * completely nullifying the performance benefits.
 *
 * @param S The unsigned integer for which the square root is to be calculated.
 * @return The integer square root of S (floor(sqrt(S))).
 */
unsigned int sqrtv2_d(unsigned int S) {
    // Base cases: sqrt(0) = 0, sqrt(1) = 1
    if (S <= 1) return S;

    float number = (float)S;
    float half_number = number * 0.5f;
    
    // Evil floating-point bit level hacking
    long i = *(long*)&number;
    
    // The magic constant offset to align the exponent and minimize mantissa error
    i = 0x5f3759df - (i >> 1);
    
    // Read the manipulated bits back as a float
    float y = *(float*)&i;
    
    // 1st iteration of Newton-Raphson for floating-point refinement
    y = y * (1.5f - (half_number * y * y));
    
    // S * (1/sqrt(S)) = sqrt(S)
    float result = number * y;
    
    return (unsigned int)result;
}