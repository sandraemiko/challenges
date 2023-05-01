#include <stdio.h>
#include <math.h>

/*
Tendo o solo como plano XY e o eixo Z em direção ao centro da terra ... Crie 3 funções :

float ang@(float acx, float acy, float acz);

A função recebe os valores de aceleração em cada um dos eixos x', y', z' do acelerômetro 

E retorna o ângulo em relação aos eixos da terra e do acelerômetro
*/

///////////////////////////////////////// PROTOTYPE ///////////////////////////////////////////////////

float f_abs(float num);
float f_power(float b, int exp);
float f_same_sign(float x, float y);
float f_atanf_taylor(float x);
float f_atan(float y, float x);
float f_acosf(float x);
float f_sqrt_newton(float n, float x, float tol); 
float ang_x(float acx, float acy, float acz);
float ang_y(float acx, float acy, float acz);
float ang_z(float acx, float acy, float acz); 

////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{

	
}

//////////////////////////////////float f_abs(float num)//////////////////////////////////////////////
float f_abs(float num)
 {
    if (num < 0)
        return(-num);
    else
        return(num);
}

//////////////////////////////float f_power(float b, int exp)////////////////////////////////////////////

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

/////////////////////////////////float f_same_sign(float x, float y)/////////////////////////////////////

float f_same_sign(float x, float y) 
{
    if ((x > 0) != (y > 0)) 
        x = -x;
    return(x);
}

/////////////////////////////////////float f_atanf_taylor(float x)/////////////////////////////////////////

float f_atanf_taylor(float x)
{
    const float eps;
    float result;
    int sign;
    float term;
    int i;

    eps = 1e-6;  
    result = 0.0;
    sign = 1;
    term = x;
    i = 1;
    while (term > eps || term < -eps)
    {
        result += sign * term;
        sign = -sign;
        i += 2;
        term = f_power(x, i) / i;
    }
    return(result);
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
    atan = f_same_sign(f_atanf_taylor(f_abs(y) / f_abs(x)), y_sign);
    if (x < 0) 
        return(atan + f_same_sign(M_PI, y_sign));
    return(atan);
}


///////////////////////////////////////////float f_acosf(float x) ///////////////////////////////////////////

float f_acosf(float x) 
{
	float t;
    float rooting;
    float tol;
	
    tol = 0.00001;
	if (x < -1 || x > 1) 
        return(NAN);
    else if (x == -1) 
        return(M_PI); 
    else if (x == 1) 
        return(0); 
    else 
	{
        rooting = 1 - f_power(x,2);
		t = sqrt_newton(rooting,7,tol)/x; 
		if (t > 1)
			return(M_PI/2 - f_atanf_taylor(1/t));
		else
			return(f_atanf_taylor(t)); 
	}
}

////////////////////////////float f_sqrt_newton(float n, float x, float tol)//////////////////////////////////////////

float f_sqrt_newton(float n, float x, float tol) 
{
    float new_x;

    if (n < 0) 
        return(NAN);
    else if (n == 0) 
        return(0);
    else if (f_abs(power(x,2) - n) <= tol) 
        return(x);
    else 
    {
        new_x = (x + n / x) / 2.0;
        return(f_sqrt_newton(n, new_x, tol));
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
    
    tol = 0.00001;
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
    
    tol = 0.00001;
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

    tol = 0.00001;
    rooting_G = f_power(acx,2) + f_power(acy,2) + f_power(acz,2);
    G = f_sqrt_newton(rooting_G, rooting_G/2,tol);
    cos = acz/G;
    return(f_acos(cos));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
