// C++ implementation of Karatsuba algorithm for bit string multiplication. 

#include<iostream> 

#include<stdio.h> 

#include<bitset>

#include<math.h>

#include<chrono>

  

using namespace std; 



int n0;

  

// FOLLOWING TWO FUNCTIONS ARE COPIED FROM http://goo.gl/q0OhZ 

// Helper method: given two unequal sized bit strings, converts them to 

// same length by adding leading 0s in the smaller string. Returns the 

// the new length 

int makeEqualLength(string &str1, string &str2) 

{ 

    int len1 = str1.size(); 

    int len2 = str2.size(); 

    if (len1 < len2) 

    { 

        for (int i = 0 ; i < len2 - len1 ; i++) 

            str1 = '0' + str1; 

        return len2; 

    } 

    else if (len1 > len2) 

    { 

        for (int i = 0 ; i < len1 - len2 ; i++) 

            str2 = '0' + str2; 

    } 

    return len1; // If len1 >= len2 

} 

  

// The main function that adds two bit sequences and returns the addition 

string addBitStrings( string first, string second ) 

{ 

    string result;  // To store the sum bits 

  

    // make the lengths same before adding 

    int length = makeEqualLength(first, second); 

    int carry = 0;  // Initialize carry 

  

    // Add all bits one by one 

    for (int i = length-1 ; i >= 0 ; i--) 

    { 

        int firstBit = first.at(i) - '0'; 

        int secondBit = second.at(i) - '0'; 

  

        // boolean expression for sum of 3 bits 

        int sum = (firstBit ^ secondBit ^ carry)+'0'; 

  

        result = (char)sum + result; 

  

        // boolean expression for 3-bit addition 

        carry = (firstBit&secondBit) | (secondBit&carry) | (firstBit&carry); 

    } 

  

    // if overflow, then add a leading 1 

    if (carry)  result = '1' + result; 

  

    return result; 

} 

  

// A utility function to multiply single bits of strings a and b 

int multiplyiSingleBit(string a, string b) 

{  return (a[0] - '0')*(b[0] - '0');  } 

 

string gradeSchool(string X, string Y) {

    string a = "0";

    for (int i = X.length()-1; i >= 0; i--) {

        if (X.at(i) == '1') {

            string p = Y;

            

            for (int j = i+1; j < X.length(); j++) {

                p += '0';

            }

            

            a = addBitStrings(a, p);

        }

    }

    return a;

}

  

// The main function that multiplies two bit strings X and Y and returns 

// result as long integer 

long long int multiply(string X, string Y) 

{ 

    // Find the maximum of lengths of x and Y and make length 

    // of smaller string same as that of larger string 

    int n = makeEqualLength(X, Y); 

  

    // Base cases 

    /*if (n == 0) return 0; 

    if (n == 1) return multiplyiSingleBit(X, Y);*/

    

    if (n < n0) {

        string a = gradeSchool(X, Y);
        return stoll(a, nullptr, 2);

    }

  

    int fh = n/2;   // First half of string, floor(n/2) 

    int sh = (n-fh); // Second half of string, ceil(n/2) 

  

    // Find the first half and second half of first string. 

    // Refer http://goo.gl/lLmgn for substr method 

    string Xl = X.substr(0, fh); 

    string Xr = X.substr(fh, sh); 

  

    // Find the first half and second half of second string 

    string Yl = Y.substr(0, fh); 

    string Yr = Y.substr(fh, sh); 

  

    // Recursively calculate the three products of inputs of size n/2 

    long long int P1 = multiply(Xl, Yl); 

    long long int P2 = multiply(Xr, Yr); 

    long long int P3 = multiply(addBitStrings(Xl, Xr), addBitStrings(Yl, Yr)); 

  

    // Combine the three products to get the final result. 

    return P1*(1<<(2*sh)) + (P3 - P1 - P2)*(1<<sh) + P2; 

}



string runMultiply(string X, string Y){

    long long int a = multiply(X, Y);

    bitset<32> b(a);

    return b.to_string();

}



string binGenerator(int size) {

    string ret;

    for (int i = 0; i < size; i++) {

        ret += rand() % 2 + '0';

    }

    

    return ret;

}

  

// Driver program to test aboev functions 

int main() 

{ 

    for (int j = 1; j <= 5; j ++) {

        n0 = pow(2, j);

        cout << "n0 = " << j << endl;

        for (int i = 1; i <= 13; i++) {

            int digit_num = pow(2, i);

            string a = binGenerator(digit_num);

            string b = binGenerator(digit_num);

            

            auto start_1 = std::chrono::system_clock::now();

            string r1 = runMultiply(a, b);

            auto end_1 = std::chrono::system_clock::now();

            auto elapsed_1 = end_1 - start_1;
            
            auto start_2 = std::chrono::system_clock::now();
            runMultiply(a,b);
            auto end_2 = std::chrono::system_clock::now();
            
            auto elapsed_2 = end_2 - start_2;
            
            auto start_3 = std::chrono::system_clock::now();
            runMultiply(a,b);
            auto end_3 = std::chrono::system_clock::now();
            
            auto elapsed_3 = end_3 - start_3;
            
            auto elapsed = (elapsed_1 + elapsed_2 + elapsed_3) / 3.0;
            

            /*auto start_2 = std::chrono::system_clock::now();

            string r2 = gradeSchool(a, b);

            auto end_2 = std::chrono::system_clock::now();

            auto elapsed_2 = end_2 - start_2;*/

        

            //cout << i << ", ";

            cout << elapsed.count() << endl;

        }

    }

} 