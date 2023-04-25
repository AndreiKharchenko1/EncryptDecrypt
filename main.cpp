
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <math.h>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

bool is_prime(int num) {
    if (num < 2) {
        return false;
    }
    int root = sqrt(num);
    for (int i = 2; i <= root; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int generate_prime() {
    int num;
    do {
        num = rand() % 1000 + 1;
    } while (!is_prime(num));
    return num;
}
vector<int> generate_primes(int n) {
    vector<bool> sieve(n+1, true);
    sieve[0] = sieve[1] = false;


    for (int i = 2; i*i <= n; i++) {
        if (sieve[i]) {
            for (int j = i*i; j <= n; j += i) {
                sieve[j] = false;
            }
        }
    }

    // collect all primes in a vector
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (sieve[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int generate_public_key(int p, int q) {
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1) {
            break;
        } else {
            e++;
        }
    }
    return e;
}
int generate_private_key(int phi, int e) {
    int d = 0;
    int k = 1;
    while (true) {
        d = (k * phi + 1) / e;
        if (d * e == k * phi + 1) {
            break;
        }
        k++;
    }
    return d;
}

int chartoint(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 1;
    } else {
        // If the character is not a latin alphabet character, return 0
        return 0;
    }
}

// Function to translate numbers 1-26 into latin alphabet characters
char inttochar(int n) {
    if (n >= 1 && n <= 26) {
        return n + 'a' - 1;
    } else {
        // If the number is not between 1 and 26, return null character
        if(n == -2){
    return 'z';
        } else if(n == -1){
      return 'y';
        } else if(n == 0){
       return 'x';
        };
    }
}


void calculate_private_key(int p, int q, int e, int& n, int& d) {
    n = p * q;
    int phi = (p - 1) * (q - 1);
    int k = 1;
    while ((1 + k * phi) % e != 0) {
        k++;
    }
    d = (1 + k * phi) / e;
}

void encrypt_public_private_key(string message, int n, int e) {
    int length = message.length();
    int messagearray[length];
    int encrypted_message[length];
    string script = "";
    cout << "Message is: 0" ;
    for(int i = 0; i < length; i++) {
        messagearray[i] = chartoint(message.at(i));
    }
    for(int j = 0; j < length; j++) {
        encrypted_message[j] = fmod(pow(messagearray[j], e), n);
        cout <<"," <<encrypted_message[j];
    }
    for(int k = 0; k < length; k++) {
        script += inttochar(encrypted_message[k]);
    }
}

string decrypt_public_private_key(int array[], int length, int n, int d) {
    string decrypted_message = "";

    int decryptedmessage[length];
    for(int a = 0; a < length; a++) {
        decryptedmessage[a] = fmod(pow(array[a], d), n);

    }
    for(int A = 0; A < length; A++) {
        decrypted_message += inttochar(decryptedmessage[A]);
    }
    return decrypted_message;
}

void generate_keys(int& n, int& e, int& d) {
  vector<int> primes = generate_primes(1000); // generate primes up to 1000
int p =generate_prime();
int q =generate_prime();
 n = p * q;
int phi = (p - 1) * (q - 1);
 e = generate_public_key(p, q);
 d = generate_private_key(phi, e);
}

string encrypt_modulate(string message) {
    string encrypted_message = "";

    int length = message.length();
    int encrypted[length];
    for(int a=0; a<length; a++){
      encrypted[a] = (7 * chartoint(message.at(a)) + 7) % 26 + 1;
    }
    for(int b=0; b<length; b++){
      encrypted_message += inttochar(encrypted[b]);
    }
    return encrypted_message;
}

string decrypt_modulate(string message) {
    string decrypted_message = "";
    int length = message.length();
    int decrypted[length];
    for(int a=0; a<length; a++){

     decrypted[a] = ((chartoint(message.at(a)) - 1) *15)%26 -1;
    }
    for(int b=0; b<length; b++){
     decrypted_message += inttochar(decrypted[b]);
    }

    return decrypted_message;
}

string encrypt_caesar_shift(string message) {
    string encrypted_message = "";
    int length = message.length();
    int encrypt[length];
    for(int i=0;i<length; i++){
       encrypt[i]=(chartoint(message.at(i)) + 3) %26;
    }
    for(int j=0; j<length; j++){
       encrypted_message += inttochar(encrypt[j]);
    }

    return encrypted_message;
}

string decrypt_caesar_shift(string message) {
    string decrypted_message = "";
    int length = message.length();
    int decrypt[length];
    for(int i=0;i<length; i++){
       decrypt[i]=(chartoint(message.at(i)) - 3 + 26) %26;
    }
    for(int j=0; j<length; j++){

       decrypted_message += inttochar(decrypt[j]);
    }
    return decrypted_message;
}
void keyD();  void modD(); void CesD(); void keyE(); void modE(); void CesE();
int main(){
    char sign;
  cout << "Press E to encrypt via public key, Press R to encrypt via modular expansion, Press T to encrypt via Cesarian \n ";
  cout << "Press D to decrypt via public key, Press F to decrypt via modular expansion, Press G to decrypt via Cesarian \n";
  cin >> sign;
  switch(sign){
   case 'E' : keyE();
   case 'R' : modE();
   case 'T' : CesE();
   case 'D' : keyD();
   case 'F' : modD();
   case 'G' : CesD();
  }
}
void CesD(){
   string Mensaje;
    cout << "\n Enter Message : ";
    cin >> Mensaje;
    cout << "\n Decrypted Message is : " << decrypt_caesar_shift(Mensaje) << endl;
main();
}
void modD(){
    string Mensaje;
    cout << "\n Enter Message : ";
    cin >> Mensaje;
    cout << "\n Decrypted Message is : " << decrypt_modulate(Mensaje) << endl;
main();

}
void keyE(){
    string Mensaje;
    int n, e, d;
    cout << "\n Enter Message : ";
    cin >> Mensaje;
    generate_keys(n, e, d);
    encrypt_public_private_key(Mensaje, n, e);
    cout << "\nPublic key (n,e) is : (" << n << ", " << e << ")" << endl;
    cout << "\n Private key (d) is : (" << d << ")" << endl;
    main();
}

void keyD(){
    const int MAX_SIZE = 100;
    int arr[MAX_SIZE];
    int num;
    char comma;

    cout << "Enter integers separated by commas: ";

    int i = 0;
    while (cin >> num) {
        arr[i++] = num;
        if (cin.peek() == ',') {
            cin >> comma; // discard comma
        } else {
            break; // end of input
        }
    }

    int n, d;
    cout << "\n Public key (n) : ";
    cin >> n;
    cout << "\Private key (d) : ";
    cin >> d;
    cout << "\nDecrypted Message is : " << decrypt_public_private_key(arr, 100, n, d) << endl;
    main();
}
void modE(){
    string Mensaje;
    cout << "\n Enter Message : ";
    cin >> Mensaje;
    cout << "\n Encrypted Message is : " << encrypt_modulate(Mensaje) << endl;
main();
}
void CesE(){
    string Mensaje;
    cout << "\n Enter Message : ";
    cin >> Mensaje;
    cout << "\n Encrypted Message is : " << encrypt_caesar_shift(Mensaje) << endl;
main();
}
