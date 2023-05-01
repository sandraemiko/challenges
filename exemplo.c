#include <stdio.h>
#include <math.h>

///////////////////////////////////float f_abs(float num)//////////////////////////////////////////
float f_abs(float num)
 {
    if (num < 0)
        return(-num);
    else
        return(num);
}

/////////////////////////////////float f_same_sign(float x, float y)/////////////////////////////////////

float f_same_sign(float x, float y) 
{
   if ((x < 0 && y > 0) || (x > 0 && y < 0)) 
        return (-x);
    else 
        return (x);
    
}

///////////////////////////////float f_atan_taylor(float x)////////////////////////////////////////

float f_atan_taylor(float x)
{
    float squared = x * x;
    float result = x;
    float term = x;
    int i;
    
    squared = x * x;
    result = x;
    term = x;
    i = 3;
    while(f_abs(term) > 1e-7f)
    {
        term = term * (-squared) / ((float)i);
        result += term;
         i += 2;
    }
    
    return result;
}

//////////////////////////////////float f_power(float b, int exp)////////////////////////////////////////

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

float f_atan_chebyshev(float x)
{
    float pi = M_PI;
    float result;
    float squared;
    float t;
    float u;
    int i;
    
    if (x > 1)
        result = pi / 2 - f_atan_chebyshev(1 / x);
    else if (x < -1)
        result = -pi / 2 - f_atan_chebyshev(1 / x);
    else 
    {
        squared = x * x;
        t = 0;
        u = 0;
        i = 14;        
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

/////////////////////////////////////float f_atan(float y, float x)///////////////////////////////////////////

float f_atan(float y, float x)     
{
    int x_sign;
    int y_sign;
    float atan;

    if (x < 0) 
        x_sign = -1;
    else 
        x_sign = 1;
    if (y < 0) 
        y_sign = -1;
    else 
        y_sign = 1;
    if (x == 0) 
    {
        if (y > 0) 
            return(M_PI/2.0);
        if (y == 0) 
            return(0.0);
        return (-M_PI/2.0);
    }
    atan = f_same_sign(atanf(f_abs(y) /f_abs(x)), y_sign);
    if (x < 0) 
        return(atan + f_same_sign(M_PI, y_sign));
    return(atan);
}

////////////////////////////float f_sqrt_newton(float n, float x, float tol)//////////////////////////////////////////

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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    printf("%f\n", atanf(1/1)); // output: 0.785398
    printf("%f\n", f_atan(1,1)); // output: 0.785398
    printf("%fui\n", atan2(1,1)); // output: 0.785398

    printf("%f\n", atanf(0.5f)); // output: 0.463648
    printf("%f\n", atanf(2)); // output: 1.107149
    printf("%f\n", atanf(-0.5f)); // output: -0.463648
    printf("%f\n", atanf(-2500)); // output: -1.107149
    printf("%f\n", atan(-2500));

    printf("%f acos\n", f_acosf(0.5));
    printf("%f acos\n", acos(0.5));
    
    return 0;
}