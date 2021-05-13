//Author:   Joshua Conneely.
//For:      CS319 Project.
//Date:     13/05/2021
//Email:    j.conneely6@nuigalway.ie
//GitHub:   https://github.com/joshuasc2001/RSA


#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

using namespace std;
typedef unsigned long long int int_64;

int_64 modularMultiplication(int_64 i, int_64 j, int_64 k)
{
    int_64 n=0;
    i=i%k;

    while(j>0)
    {
        if(j%2==1)
        {
            n=(n+i)%k;
        }

        i=(i*2)%k;
        j/=2;
    }

    n=n%k;
    return n;
}

int_64 modularExponent(int_64 base, int_64 e, int_64 m)
{
    int_64 n = 1;

    if(m == 0)
    {
        return 0;
    }

    base %= m;

    while (e> 0)
    {
        if (e%2==1)
        {
            n=modularMultiplication(n, base, m);
        }

        base=modularMultiplication(base, base, m);
        e = e/2;
    }

    return n;
}

int_64 GCD(int_64 a, int_64 b, int_64 &d, int_64 &k)
{
    int_64 d1, k1, r;

    if(b == 0)
    {
        d=1;
        k=0;
        return a;
    }
    r= GCD(b, a%b, d1, k1);
    k= d1-(a/b)*k1;
    d= k1;
    return r;
}

int main()
{
    int_64 p, q, n, e, phi, d, k, cipher, decipher;
    string enciphered, deciphered, message, delimiter = " ", token, content;
    ifstream messageFile("message.txt");
    ifstream ifs("ecnrypted.txt");
    ofstream ecnryptedFile("ecnrypted.txt");
    ofstream decryptedFile("decrypted.txt");

    p=665123;
    q=705403;


    n=p*q;
    phi=(p-1)*(q-1);

    //check to see is co prime to phi and also not equal 1, this also sets the values for d and k
    do
    {
        cout<<"Enter the encryption key: ";
        cin>>e;
        e=19967;//remove
        if(cin.fail() || e < 0)
        {
            cout<<"Invalid key please try again "<<endl;
            exit(1);
        }

    }
    while(GCD(e, phi, d, k)!= 1 || e==1);

    message.assign( (istreambuf_iterator<char>(messageFile) ),(istreambuf_iterator<char>()));

    cout<<"the message to be encrypted is: "<<message<<endl;

    if(d < 0)
    {
        d+=phi;
    }

    for(int_64 i=0; i<message.length(); i++)//encrypting each char and then appending them to a string
    {
        char x = message.at(i);
        int_64 temp = int(x);
        cipher = modularExponent(temp, e, n);
        enciphered = enciphered + to_string(cipher) + " " ;
    }

    cout<<"\nMessage has been encrypted"<<endl;
    ecnryptedFile << enciphered;//outputs file
    ecnryptedFile.close();

    content.assign( (istreambuf_iterator<char>(ifs) ),(istreambuf_iterator<char>()));//reads in file into string

    size_t pos = 0;//parses the string and decrypts it before adding it to another string as words
    while ((pos = content.find(delimiter)) != string::npos)
    {
        token = content.substr(0, pos);
        int_64 temp = stoull(token);
        decipher = modularExponent(temp, d, n);
        deciphered = deciphered + char(decipher);
        content.erase(0, pos + delimiter.length());
    }

    decryptedFile<< deciphered;//outputs the file
    decryptedFile.close();
    cout <<"\nMessage has been decrypted" << endl;

    return 0;
}
