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
    printf("[Trig] sin(30 deg)     : %f\n", sin_d(radyan));

    // 2. Absolute Value Test: Direct Bit Manipulation
    double negative = -42.6;
    printf("[Abs]  abs(-42.6)      : %f\n", abs_d(negative));

    // 3. Exponential Test: e^3.0
    double exp_val = 3.0;
    printf("[Exp]  e^%f          : %f\n", exp_val, calce_d(exp_val));

    printf("\n--- Numerical Analysis Results ---\n");

    // 4. Numerical Differentiation: Slope of sin(x) at x = PI/6
    // Expected: cos(PI/6) = 0.866025
    double slope = diff_d(sin_d, radyan);
    printf("[Diff] d/dx sin at 30 deg : %f\n", slope);

    // 5. Numerical Integration: Area under sin(x) from 0 to PI
    // Expected: 2.0
    double pi = radyan * 6.0;
    double area = integral_d(sin_d, 0.0, pi);
    printf("[Intg] Area of sin (0-PI) : %f\n", area);

    printf("\n--- Press Enter to Exit ---\n");
    
    getchar();
    return SYS_SUCCESS;
}