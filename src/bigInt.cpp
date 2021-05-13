#include "bigInt.h"
typedef unsigned long long int int_64;

bigInt::bigInt()
{
    //ctor
}

bigInt::~bigInt()
{
    //dtor
}

bigInt &bigInt::operator=(const bigInt &i)
{
    swap(i);
    return *this;
}

int_64 modularMultiplication(int_64 a, int_64 b, int_64 c)
{
    int_64 r=0;
    a=a%c;

    while(b>0)
    {
        if(b%2==1)
        {
            r=(r+a)%c;
        }
        a=(a*2)%c;
        b/=2;
    }
    r=r%c;
    return r;
}

int_64 modularExponent(int_64 base, int_64 e, int_64 m)
{

    if(m == 0)
    {
        return 0;
    }

    base %= m;
    int_64 r = 1;

    while (e> 0)
    {
        if (e%2==1)
        {
            r=modularMultiplication(r, base, m);
        }
        base=modularMultiplication(base, base, m);
        e = e/2;
    }
    return r;
}

int_64 GCD(int_64 a, int_64 b, int_64 &d, int_64 &k)
{
    int_64 d1, k1, res;

    if(b == 0)
    {
        d=1;
        k=0;
        return a;
    }
    res= GCD(b, a%b, d1, k1);
    k= d1-(a/b)*k1;
    d= k1;
    return res;
}
