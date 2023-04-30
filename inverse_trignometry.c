#include <stdio.h>
#include <string.h>
#include <math.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Faça as funções: 

float acosf(float x)
int   acosi(float x)

return: arc cosseno do ângulo x

Funções permitidas: NENHUMA
Prazo 28/04
*/
//////////////////////////////////////// PROTOTYPE ///////////////////////////////////////////////////

float sqrt_newton (float n, int aprox);
float power(float b, int exp);
float atanf_taylor (float x, int n);
float f_acosf(float x);
int f_acosi(float x);
 
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{

	float x = 0.5;
	int arccos_x = f_acosi(x);

	printf ("%i \n", arccos_x);
}

///////////////////////////////////////float sqrt_newton//////////////////////////////////////////////

float sqrt_newton (float n, int aprox)
{
	float result;
	float i;

	result = n;
	i = 1;
	if(n < 0)
		return (NAN);
	else if ( n == 0)
		return (0);
	else
	{
		while (i<= aprox)
		{
			result = result - (result * result - n)/(2* result);
			i++;
		}
		return (result);
	}
}

///////////////////////////////////////float power(float b, int exp)///////////////////////////////////////////

float power(float b, int exp) 
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
    return (result);
}

////////////////////////////////////float atanf_taylor (float x, int n) ////////////////////////////////////////

float atanf_taylor (float x, int n) 
{
   float result;
   int sign;
   int i;

    result = 0;
	sign = 1;
	i = 0;
	while(n > i) 
	{
		result += sign * (power(x, (2*i+1)) / (2*i+1));
		sign *= -1;
		i++;
	}
	return (result);
}

//////////////////////////////////////float f_acosf(float x) ////////////////////////////////////////

float f_acosf(float x) 
{
	float t;
	
	if (x < -1 || x > 1) 
        return (NAN);
    else if (x == -1) 
        return (M_PI); 
    else if (x == 1) 
        return (0); 
    else 
	{
		t = sqrt_newton((1 - x * x),7)/x; 
		if (t > 1)
			return (M_PI/2 - atanf_taylor(1/t,12));
		else
			return (atanf_taylor(t,12)); 
	}
}

/////////////////////////////////////int f_acosi(float x)/////////////////////////////////////////

int f_acosi(float x)
 {
	int result;

	result = 0;
    if (x < -1 || x > 1) 
        return (0); 
    else 
	{
		result = (int)(f_acosf(x) * 180 / M_PI);
		return (result);
	}
}
