#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ios>
#include <fstream>

const int MAX_DIGITS = 1024;
const int BASE = 10;

class huge {
private:
public:
    int value[MAX_DIGITS];
    bool negative;
	//Constructors
        huge();
        huge(long long nr);
        huge(const huge& other);
        huge(char *s);
	//Reading
	//Printing
        void printC();
        void printF(std::fstream file);
        int returnSize();
        int returnDigit(int k);
        bool returnNegative();
	//Utility
        void copy(huge& other);
        int compare(const huge& other);
	//Operators
        //Calculations
            //Operator "+"
                huge operator + (long long k);
                void operator += (long long k);
                huge operator + (huge& other);
                void operator += (huge& other);

            //Operator "-"
                huge operator - (long long k);
                void operator -= (long long k);
                huge operator - (huge& other);
                void operator -= (huge& other);

            //Operator "*"
                huge operator * (long long k);
                void operator *= (long long k);
                huge operator * (huge& other);
                void operator *= (huge& other);

            //Operator "/"
                huge operator / (long long k);
                void operator /= (long long k);
                huge operator / (huge& other);
                void operator /= (huge& other);

            //Operator "%"
                huge operator % (long long k);
                void operator %= (long long k);
                huge operator % (huge& other);
                void operator %= (huge& other);
        //Comparisons
            //Smaller ("<")
                bool operator < (long long k);
                bool operator < (huge& other);

            //Smaller or equal ("<=")
                bool operator <= (long long k);
                bool operator <= (huge& other);

            //Bigger (">")
                bool operator > (long long k);
                bool operator > (huge& other);

            //Bigger or equal (">=")
                bool operator >= (long long k);
                bool operator >= (huge& other);

            //Equal ("==")
                bool operator == (long long k);
                bool operator == (huge& other);

            //Different ("!=")
                bool operator != (long long k);
                bool operator != (huge& other);
};
