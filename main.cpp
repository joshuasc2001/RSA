#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include "bigInt.h"

using namespace std;

int main()
{
    bigInt p, q, n, e, phi, d, k, cipher, decipher;
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
        e=19967;
        if(cin.fail() || e < 0)
        {
            cout<<"Invalid key, try again with positive integers."<<endl;
            exit(1);
        }

    }
    while(GCD(e, phi, d, k)!= 1 || e==1);

    if(d < 0)
    {
        d+=phi;
    }

    message.assign( (istreambuf_iterator<char>(messageFile) ),(istreambuf_iterator<char>()));

    cout<<"the message to be encrypted is: "<<message<<endl;

    for(int_64 i=0; i<message.length(); i++)
    {
        char x = message.at(i);
        int_64 temp = int(x);
        cipher = modularExponent(temp, e, n);
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
        decipher = modularExponent(temp, d, n);
        deciphered = deciphered + char(decipher);
        content.erase(0, pos + delimiter.length());
    }

    decryptedFile<< deciphered;
    decryptedFile.close();
    cout <<"\nMessage has been decrypted" << endl;

    return 0;
}
