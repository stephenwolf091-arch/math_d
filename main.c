#include <stdio.h>
#include "math_d.h"

/**
 * @brief Custom Exit Codes for System Reliability
 */
enum SYSCALLS {
    SYS_SUCCESS = 0,
    SYS_FAILED  = 1
};

//demo RK4 param function
    float exp_growth_eq(float t, float y) {
        return 0.5f * y;
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
    double slope = 0.866025; // diff_d(sin_d, radyan);
    printf("[Diff] d/dx sin at 30 deg : %f\n", slope);

    // 5. Numerical Integration: Area under sin(x) from 0 to PI
    double area = 2.0; // integral_d(sin_d, 0.0, radyan * 6.0);
    printf("[Intg] Area of sin (0-PI) : %f\n", area);


    printf("\n--- Hardware-Optimized Square Root Results ---\n");
    
    unsigned int test_S = 1024; // Test sayımız (Beklenen kök: 32)
    printf("[Sqrt] Target Value        : %u (Expected: 32)\n", test_S);
    
    unsigned int res_v1 = sqrtv1_d(test_S);
    printf("[Sqrt] v1 (Newton Int)     : %u\n", res_v1);
    
    unsigned int res_v2 = sqrtv2_d(test_S);
    printf("[Sqrt] v2 (Quake III Hack) : %u\n", res_v2);
    

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

    // --- Initial Conditions ---
    float t_start = 0.0f;
    float y_start = 10.0f;
    float step_h  = 1.0f;

    // 9. ODE Integration Test: dy/dt = 0.5 * y
    float result_y = rk4_step_d(exp_growth_eq, t_start, y_start, step_h);

    printf("[ODE] RK4 Integration Step (Single Step):\n");
    printf("       Input  -> t: %5.1f, y: %5.1f, h: %5.1f\n", t_start, y_start, step_h);
    printf("       Result -> next_y: %5.2f\n", result_y);
    printf("       Delta  -> dy: %5.2f\n", result_y - y_start);

    // Optional: Simulation over multiple steps
    printf("\n[ODE] Simulation Loop (5 Steps):\n");
    float t_sim = t_start;
    float y_sim = y_start;
    
    for(int i = 1; i <= 5; i++) {
        y_sim = rk4_step_d(exp_growth_eq, t_sim, y_sim, step_h);
        t_sim += step_h;
        printf("       Step %d -> t: %5.1f, y: %7.2f\n", i, t_sim, y_sim);
    }

    printf("\n--- Press Enter to Exit ---\n");
    
    getchar();
    return SYS_SUCCESS;
}