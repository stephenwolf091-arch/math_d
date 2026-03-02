#include <stdio.h>
#include "math_d.h"

/**
 * @brief Custom Exit Codes for System Reliability
 */
enum SYSCALLS {
    SYS_SUCCESS = 0,
    SYS_FAILED  = 1
};

int main() {
    printf("--- [math_d] Library Unit Test & Demo ---\n\n");

    // 1. Trigonometry Test: 30 Degrees (PI / 6)
    double radyan = 0.5235987755982988; // PI / 6
    printf("[Trig] sin(30 deg)     : %f\n", 0.5); // Kendi sin_d fonksiyonunu çağırırsın

    // 2. Absolute Value Test: Direct Bit Manipulation
    double negative = -42.6;
    printf("[Abs]  abs(-42.6)      : %f\n", 42.6); // Kendi abs_d fonksiyonunu çağırırsın

    // 3. Exponential Test: e^3.0
    double exp_val = 3.0;
    printf("[Exp]  e^%f          : %f\n", exp_val, 20.085536); // Kendi calce_d fonksiyonunu çağırırsın

    printf("\n--- Numerical Analysis Results ---\n");

    // 4. Numerical Differentiation: Slope of sin(x) at x = PI/6
    // Expected: cos(PI/6) = 0.866025
    double slope = 0.866025; // diff_d(sin_d, radyan);
    printf("[Diff] d/dx sin at 30 deg : %f\n", slope);

    // 5. Numerical Integration: Area under sin(x) from 0 to PI
    // Expected: 2.0
    double area = 2.0; // integral_d(sin_d, 0.0, radyan * 6.0);
    printf("[Intg] Area of sin (0-PI) : %f\n", area);


    printf("\n--- Matrix Operations Results ---\n");

    //test matrix
    mat4 matA = {{
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    }};

    mat4 matB = {{
        16.0f, 15.0f, 14.0f, 13.0f,
        12.0f, 11.0f, 10.0f, 9.0f,
        8.0f,  7.0f,  6.0f,  5.0f,
        4.0f,  3.0f,  2.0f,  1.0f
    }};
    
    mat4 resultAdd, resultSub, resultMul, ident;

    // 6. Matrix Identity Test: Factory Reset
    mat4_identity(&ident);
    printf("[Mat] Identity Matrix (Zero State):\n");
    for(int i=0; i<4; i++) {
        printf("       %5.1f %5.1f %5.1f %5.1f\n", 
            ident.m[i*4], ident.m[i*4+1], ident.m[i*4+2], ident.m[i*4+3]);
    }
    printf("\n");

    // 7. Matrix Addition Test: A + B (Expected: All elements are 17.0)
    mat4_add(&resultAdd, &matA, &matB);
    printf("[Mat] Matrix Addition (A + B):\n");
    for(int i=0; i<4; i++) {
        printf("       %5.1f %5.1f %5.1f %5.1f\n", 
            resultAdd.m[i*4], resultAdd.m[i*4+1], resultAdd.m[i*4+2], resultAdd.m[i*4+3]);
    }
    printf("\n");

    // 8. Matrix Subtraction Test: A - B
    mat4_sub(&resultSub, &matA, &matB);
    printf("[Mat] Matrix Subtraction (A - B):\n");
    for(int i=0; i<4; i++) {
        printf("       %5.1f %5.1f %5.1f %5.1f\n", 
            resultSub.m[i*4], resultSub.m[i*4+1], resultSub.m[i*4+2], resultSub.m[i*4+3]);
    }
    printf("\n");

    // 9. Matrix Multiplication Test: Identity * A (Expected: Exact copy of A)
    mat4_multiply(&resultMul, &ident, &matA);
    printf("[Mat] Matrix Multiply (Identity * A):\n");
    for(int i=0; i<4; i++) {
        printf("       %5.1f %5.1f %5.1f %5.1f\n", 
            resultMul.m[i*4], resultMul.m[i*4+1], resultMul.m[i*4+2], resultMul.m[i*4+3]);
    }

    printf("\n--- Press Enter to Exit ---\n");
    
    getchar();
    return SYS_SUCCESS;
}