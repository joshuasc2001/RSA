#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

using namespace std;
typedef unsigned long long int int_64;


//Computes (a * b) mod c
int_64 modularMul(int_64 a, int_64 b, int_64 c)
{
    int_64 r=0;
    a=a%c;

    while(b>0)
    {
        if(b%2==1)
            r=(r+a)%c;
        a=(a*2)%c;
        b/=2;
    }
    return r%c;
}

//Does modular exponentiation
int_64 computeModExp(int_64 base, int_64 exponent, int_64 mod)
{

    if(mod == 0)
        return 0;

    base %= mod;
    int_64 r = 1;

    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            r = modularMul(r, base, mod);
        base = modularMul(base, base, mod);
        exponent /= 2;
    }
    return r;
}

int_64 extendedGCD(int_64 a, int_64 b, int_64 &d, int_64 &k)
{
    int_64 d1, k1, res;

    if(b == 0)
    {
        d = 1;
        k = 0;
        return a;
    }

    res = extendedGCD(b, a%b, d1, k1);
    k = d1 - (a/b) * k1;
    d = k1;
    return res;
}

int main()
{
    int_64 p, q, n, e, phi, d, k, cipher, decipher;
    string enciphered, deciphered, message, delimiter = " ", token, content;
    ifstream messageFile("message.txt");
    ifstream ifs("ecnrypted.txt");
    ofstream ecnryptedFile("ecnrypted.txt");
    ofstream decryptedFile("decrypted.txt");

    p=665123;//need to generate these
    q=705403;


    n=p*q;
    phi=(p-1)*(q-1);

    //check to see is co prime to phi and also not equal 1, this also sets the values for d and k
    do
    {
        //cout<<"Enter the encryption key, e: ";
        //cin>>e;
        e=19967;//for testing
        if(cin.fail() || e < 0)
        {
            cout<<"Invalid key, try again with positive integers."<<endl;
            exit(1);
        }

    }
    while(extendedGCD(e, phi, d, k) != 1 || e == 1);

    if(d < 0)
        d+=phi;

    message.assign( (istreambuf_iterator<char>(messageFile) ),(istreambuf_iterator<char>()));

    cout<<"the message to be encrypted is: "<<message<<endl;

    for(int_64 i=0; i<message.length(); i++)
    {
        char x = message.at(i);
        int_64 temp = int(x);
        cipher = computeModExp(temp, e, n);
        enciphered = enciphered + to_string(cipher) + " " ;
    }

    cout<<"\nMessage has been encrypted"<<endl;
    ecnryptedFile << enciphered;
    ecnryptedFile.close();

    content.assign( (istreambuf_iterator<char>(ifs) ),(istreambuf_iterator<char>()));

    size_t pos = 0;
    while ((pos = content.find(delimiter)) != string::npos)
    {
        token = content.substr(0, pos);
        int_64 temp = stoull(token);
        decipher = computeModExp(temp, d, n);
        deciphered = deciphered + char(decipher);
        content.erase(0, pos + delimiter.length());
    }

    decryptedFile<< deciphered;
    decryptedFile.close();
    cout <<"\nMessage has been decrypted" << endl;


    return 0;
}
