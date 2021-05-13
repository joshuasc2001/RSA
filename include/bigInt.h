#ifndef BIGINT_H
#define BIGINT_H


class bigInt
{
public:
    typedef unsigned long long int int_64;
    bigInt();
    ~bigInt();
    bigInt &operator=(const bigInt &i);
    int_64 modularMultiplication(int_64 a, int_64 b, int_64 c);
    int_64 modularExponent(int_64 base, int_64 e, int_64 m);
    int_64 GCD(int_64 a, int_64 b, int_64 &d, int_64 &k);

private:
    int_64 number;
};

#endif // BIGINT_H
