#include <stdio.h>
#include <math.h>

/*
Tendo o solo como plano XY e o eixo Z em direção ao centro da terra ... Crie 3 funções :

float ang@(float acx, float acy, float acz);

A função recebe os valores de aceleração em cada um dos eixos x', y', z' do acelerômetro 

E retorna o ângulo em relação aos eixos da terra e do acelerômetro
*/

#include <stdio.h>
#include <math.h>
#include <stdint.h>

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
    float squared;
    float result;
    float term;
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
    
    return (result);
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int f_isnan(double x)
{
    return (x != x);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int f_isinf(double x)
{
    return !isnan(x) && isnan(x - x);
}

//////////////////////////////////////float f_loor(float x)///////////////////////////////////////////////
float f_loor(float x)
{
    int i;

    i = (int) x;
    if (x < 0 && x != i) 
        i--;
    return ((float) i);
}

//////////////////////////////////int f_signbit(float x)/////////////////////////////////////////////

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

////////////////////////////////////float ang_x(float acx, float acy, float acz)////////////////////////////////////////

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
    printf("%f\n", atanf(2/1)); // output: 0.785398
    printf("%fresultado\n", f_atan(2,1)); // output: 0.785398
    printf("%fui\n", atan2(2,1)); // output: 0.785398

    printf("%f\n", atanf(0.5f)); // output: 0.463648
    printf("%f\n", atanf(2)); // output: 1.107149
    printf("%f\n", atanf(-0.5f)); // output: -0.463648
    printf("%f\n", atanf(-2500)); // output: -1.107149
    printf("%f\n", atan(-2500));

    printf("%f acos\n", f_acosf(0.5));
    printf("%f acos\n", acos(0.5));
    
    return 0;
}