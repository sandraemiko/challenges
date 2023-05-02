#include <stdio.h>
#include <math.h>
#include <stdint.h>

///////////////////////////////////float f_abs(float num)//////////////////////////////////////////
/*The f_abs function is a mathematical function that returns the absolute value of a floating-point number.
In other words, if the number is positive, it returns the number itself, otherwise, it returns the negative value of the number*/

float f_abs(float num)
 {
    if (num < 0)
        return(-num);
    else
        return(num);
}

/////////////////////////////////float f_same_sign(float x, float y)/////////////////////////////////////
/*The 'f_same_sign' function is a mathematical function that takes two floating-point values as input and 
returns the absolute value of the first value if both values have the same sign (positive or negative), and 
the first value itself if they have different signs*/

float f_same_sign(float x, float y) 
{
   if ((x < 0 && y > 0) || (x > 0 && y < 0)) 
        return (-x);
    else 
        return (x); 
}

///////////////////////////////float f_atan_taylor(float x)////////////////////////////////////////
/*The function 'f_atan_taylor' is an implementation of the Taylor series for the arctangent function
(atan). The Taylor series is an infinite series that can be used to approximate a function around a specific point.*/

float f_atan_taylor(float x)
{
    float squared;
    float result;
    float term;
    int i;
    
    squared = x * x;
    result = x;
    term = x;
    i = 3;
    while(f_abs(term) > 1e-10f)
    {
        term = term * (-squared) / ((float)i);
        result += term;
         i += 2;
    }
    
    return (result);
}

//////////////////////////////////float f_power(float b, int exp)////////////////////////////////////////
/*The "f_power" function is a mathematical function that calculates the power of a real number "b" raised
 to an integer exponent "exp".*/


float f_power(float b, int exp) 
{
    float result;
	 
    result = 1;
    while (exp != 0)
	{
        if (exp % 2 == 1)
            result *= b;
        b *= b;
        exp /= 2;
    }
    return(result);
}

///////////////////////////////float atan_chebyshev(float x)///////////////////////////////////////
/*The function "f_atan_chebyshev" is an implementation of the Chebyshev approximation series method
to calculate the arctangent function (atan) of a real number "x"*/

float f_atan_chebyshev(float x)
{
    float pi;
    float result;
    float squared;
    float t;
    float u;
    int i;
    
    pi = M_PI;
    if (x > 1)
        result = pi / 2 - f_atan_chebyshev(1 / x);
    else if (x < -1)
        result = -pi / 2 - f_atan_chebyshev(1 / x);
    else 
    {
        squared = x * x;
        t = 0;
        u = 0;
        i = 1000;        
        while(i >= 0)
        {
            t = 1 / (2 * i + 1);
            u = t * (squared * u + f_power(-1, i));
            i--;
        }
        result = x * u;
    }
    return (result);
}

/////////////////////////////////float atanf(float x)//////////////////////////////////////////////////
/*The function "atanf" is a mathematical function that calculates the arctangent (atan) of a real number
 "x". It uses different approximation methods depending on the value of "x". If the absolute value of "x" 
 is less than 0.1, the "f_atan_taylor" function is used. Otherwise, if "x" is between 0.1 and 1.0, the 
 "f_atan_chebyshev" function is used. If "x" is between -1.0 and -0.1, the "f_atan_chebyshev" function 
 is used with the argument -x and the result is negative. If "x" is greater than 1.0, the "f_atan_chebyshev" 
 function is used with the argument 1/x and the result is adjusted to return the arctangent of the original 
 value. If "x" is less than -1.0, the "f_atan_chebyshev" function is used with the argument 1/(-x) and the 
 result is adjusted to return the negative of the arctangent of the original value. If "x" is equal to 0,
 the function returns 0.*/

float atanf(float x)
{
    float result;
    
    if (f_abs(x) < 0.1)
        result = f_atan_taylor(x);
    else if (x >= 0.1 && x <= 1.0)
        result = f_atan_chebyshev(x);
    else if (x >= -1.0 && x <= -0.1)
        result = -f_atan_chebyshev(-x);
    else if (x > 1.0)
    {
        result = f_atan_chebyshev(1 / x);
        result = M_PI / 2 - result;
    } 
    else if (x < -1.0)
    {
        result = f_atan_chebyshev(1 / (-x));
        result = -M_PI / 2 - result;
    } 
    else
        result = 0; 
    return (result);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*The "f_isnan" function is a function that checks whether a floating-point number "x" is a NaN (Not a Number) 
value. It uses a property of the NaN value, which is that it is the only value that is different from itself.*/

int f_isnan(double x)
{
    return (x != x);
}

///////////////////////////////////////int f_isinf(double x)///////////////////////////////////////////
/*The function "f_isinf" is a function that checks if a floating-point number "x" is an infinite value.*/

int f_isinf(double x)
{
    return (!isnan(x) && isnan(x - x));
}

//////////////////////////////////////float f_loor(float x)///////////////////////////////////////////////
/*The function 'f_loor' is a mathematical function that returns the largest integer less than or equal to 
a floating-point number 'x'. It does this by converting 'x' to an integer 'i' and then checking if 'x' is
negative and has a non-zero fractional part. In this case, 'i' is decremented by 1 to obtain the largest
integer less than or equal to 'x'. The function returns the converted value of 'i' back to a floating-point
number.*/

float f_loor(float x)
{
    int i;

    i = (int) x;
    if (x < 0 && x != i) 
        i--;
    return ((float) i);       
}

//////////////////////////////////int f_signbit(float x)/////////////////////////////////////////////
/*The function "f_signbit" is a function that determines the sign of a floating-point number "x".*/

int f_signbit(float x)
 {
    union {
        float f;
        uint32_t i;
    } u;
    u.f = x;
    return (u.i >> 31);
}


/////////////////////////////float f_mod(float x, float y)////////////////////////////////////////////
/*The function "f_mod" is a mathematical function that returns the remainder of dividing a floating-point
number "x" by another floating-point number "y".*/

float f_mod(float x, float y)
{
    float result;

    if (y == 0) 
        return (NAN);
    result = x - y * f_loor(x / y);
    if (result == 0)
    {
        if (f_signbit(x) != f_signbit(y)) 
            return (-0.0);
        else 
            return (0.0);
        
    }
    return (result);
}

/////////////////////////////////////float f_atan(float y, float x)///////////////////////////////////////////
/*The function "f_atan" is a mathematical function that calculates the arctangent of two floating-point numbers
"y" and "x" and returns the result in radians. The function begins by checking if the arguments are NaN 
(not a number) or infinite, returning NaN if this is the case. It then determines the quadrant of the Cartesian 
coordinate (x, y) by calculating the angle with the "atanf" function and adjusting the result based on the quadrant
to obtain the correct angle in the Cartesian plane. Finally, the function ensures that the resulting angle is within
the interval [-π, π] and returns it.*/

float f_atan(float y, float x)     
{
    int quadrant;
    float angle;
    
    if (f_isnan(x) || f_isnan(y)) 
        return (NAN);
    if (f_isinf(x) && f_isinf(y)) 
        return (NAN);
    if (x == 0 && y == 0) 
        return (NAN);
    quadrant = 0;
    if (x < 0)
        quadrant = 2;
    if (y < 0) 
        quadrant = quadrant + 1;
    angle = atanf(f_abs(y / x));;
    switch (quadrant) 
    {
        case 1: angle = M_PI - angle; break;
        case 2: angle = angle + M_PI; break;
        case 3: angle = -angle - M_PI; break;
    }
    angle = f_mod(angle, 2 * M_PI);
    if (angle < -M_PI) 
        angle += 2 * M_PI;
    if (angle > M_PI) 
        angle -= 2 * M_PI;
    return (angle);
}

////////////////////////////float f_sqrt_newton(float n, float x, float tol)//////////////////////////////////////////
/*The function "f_sqrt_newton" is a function that calculates the square root of a floating-point number "n" using the Newton-Raphson method.*/

float f_sqrt_newton(float n, float x, float tol) 
{
    float new_x;

    if (n < 0) 
        return(NAN);
    else if (n == 0) 
        return(0);
    else if (f_abs(f_power(x,2) - n) <= tol) 
        return(x);
    else 
    {
        new_x = (x + n / x) / 2.0;
        return(f_sqrt_newton(n, new_x, tol));
    }
}


///////////////////////////////////////////float f_acosf(float x) ///////////////////////////////////////////
/*The "f_acosf" function is a mathematical function that calculates the arccosine of a floating-point number
"x" and returns the result in radians.*/

float f_acosf(float x) 
{
	float t;
    float rooting;
    float tol;
	
    tol = 1e-6;
	if (x < -1 || x > 1) 
        return(NAN);
    else if (x == -1) 
        return(M_PI); 
    else if (x == 1) 
        return(0); 
    else 
	{
        rooting = 1 - f_power(x,2);
		t = f_sqrt_newton(rooting,7,tol)/x; 
        if (t > 1)
			return(M_PI/2 - atanf(1/t));
		else
			return(atanf(t)); 
	}
}

////////////////////////////////////float ang_x(float acx, float acy, float acz)////////////////////////////////////////
/*The "ang_x" function is a function that calculates the angle of a 3D vector represented by its x, y, and z coordinates.
First, the function calculates the magnitude of the vector using the Newton-Raphson method for square root. Then, it 
calculates the cosine of the angle by dividing the x coordinate by the value of the vector magnitude. The sine is then
calculated from the cosine, again using the Newton-Raphson method. Finally, the function returns the arctangent of the
sine and cosine to obtain the angle in radians.*/

float ang_x(float acx, float acy, float acz)
{
    float G;
    float cos;
    float sin;
    float tol;
    float rooting_G;
    float rooting_sin;
    
    tol = 1e-6;
    rooting_G =f_power(acx,2) + f_power(acy,2) + f_power(acz,2);
    G = f_sqrt_newton(rooting_G, rooting_G/2,tol);
    cos = acx/G;
    rooting_sin = 1 - f_power(cos , 2); 
    sin = f_sqrt_newton(rooting_sin,rooting_sin/2, tol);
    return(f_atan(sin, cos));
}

//////////////////////////////float ang_y(float acx, float acy, float acz)///////////////////////////////////////////////

float ang_y(float acx, float acy, float acz)
{
    float G;
    float cos;
    float sin;
    float tol;
    float rooting_G;
    float rooting_sin;
    
    tol = 1e-6;
    rooting_G = f_power(acx,2) + f_power(acy,2) + f_power(acz,2);
    G = f_sqrt_newton(rooting_G, rooting_G/2,tol);
    cos = acy/G;
    rooting_sin = 1 - f_power(cos , 2); 
    sin = f_sqrt_newton(rooting_sin,rooting_sin/2, tol);
    return(f_atan(sin, cos));
}

/////////////////////////////////float ang_z(float acx, float acy, float acz)////////////////////////////////////////////
/*The 'ang_z' function is a function that calculates the angle between a 3D vector and the z-axis. First, the function 
calculates the magnitude of the vector using the Newton-Raphson method for square roots. Then, it calculates the cosine
of the angle by dividing the z-coordinate by the value of the vector magnitude. Finally, the function returns the arccosine
to obtain the angle in radians*/

float ang_z(float acx, float acy, float acz) 
{
    float G; 
    float tol; 
    float rooting_G; 
    float cos; 

    tol = 1e-6;
    rooting_G = f_power(acx,2) + f_power(acy,2) + f_power(acz,2);
    G = f_sqrt_newton(rooting_G, rooting_G/2,tol);
    cos = acz/G;
    return(f_acosf(cos));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    printf("%f\n", atanf(2)); 
    printf("%fresultado\n", f_atan(2,1)); 
    printf("%fui\n", atan2(2,1)); 

    printf("%f\n", atanf(0.5f)); 
    printf("%f\n", atanf(2)); 
    printf("%f\n", atanf(-0.5f)); 
    printf("%f\n", atanf(-2500)); 
    printf("%f\n", atan(-2500));

    printf("%f acos\n", f_acosf(0.5));
    printf("%f acos\n", acos(0.5));
    
    return 0;
}