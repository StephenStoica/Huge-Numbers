#include "huge.h"
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

//Constructors
    huge::huge() {
	memset(value, 0, sizeof(value));
	value[0] = 1;
	negative = false;
}

    huge::huge(long long nr) {
	memset(value, 0, sizeof(value));
	negative = nr < 0;
	nr = abs(nr);
	do {
		value[++value[0]] = nr%BASE;
		nr /= BASE;
	} while (nr);
}

    huge::huge(const huge& other) {
	memset(value, 0, sizeof(value));
	value[0] = other.value[0];
	for (int i = 1; i <= value[0]; i++)
		value[i] = other.value[i];
    negative = other.negative;
}

    huge::huge(char *st){
        int i = 0;
        while(st[i] - 48 <= 9 && st[i] - 48 >= 0) i++;
        value[0] = i;
        for(i ; i>=1 ; i--)
        {
            value[i] = st[value[0]-i] - 48;
        }
        for(i = value[0]; i >= 1; i--){
            if(value[i] == 0)  value[0]--;
        }
        negative = 0;
    }
//Printing
    void huge::printC() {
	if(negative)  printf("-");
	for (int i = value[0]; i >= 1; i--)
		printf("%d", value[i]);
}

    int huge::returnSize(){
        return value[0];
    }

    int huge::returnDigit(int k){
        if(k == 0 || k >= MAX_DIGITS)  return 0;
        else    return value[value[0] - k + 1];
    }

    bool huge::returnNegative(){
        return negative;
    }

//Utility
    void huge::copy(huge& other){
    for(int i = 0; i <= value[0]; i++)
        other.value[i] = value[i];
    other.negative = negative;
}

    int huge::compare(const huge& other) {
    if (negative && !other.negative)    return -1;
    if (!negative && other.negative)    return 1;
	if (value[0]>other.value[0]) if(negative && other.negative) return -1; else return 1;
	if (value[0]<other.value[0]) if(negative && other.negative) return 1; else return -1;
	for (int i = value[0]; i >= 1; --i) {
		if (value[i] > other.value[i])	if(negative && other.negative) return -1;   else  return 1;
		if (value[i] < other.value[i])	if(negative && other.negative) return 1;   else  return -1;
	}
	return 0;
}

//Operators
    //Calculations
        //Operator "+"
            huge huge::operator + (long long k){
    huge temp(k), cpy;
    copy(cpy);
    return cpy + temp;
}

            void huge::operator += (long long k){
                *this = *this + k;
            }

            huge huge::operator + (huge& other) {
	huge temp;
	if(negative && other.negative){temp.negative = 1;}
	else{
        huge cpy;
        copy(cpy);
        if(negative)    return other - cpy;
        if(other.negative)    return cpy - other;
	}
	temp.value[0] = value[0]>other.value[0] ? value[0] : other.value[0];
	int tr = 0, aux;
	for (int i = 1; i <= temp.value[0]; ++i) {
		aux = value[i] + other.value[i] + tr;
		temp.value[i] = aux % BASE;
		tr = aux / BASE;
	}
	if (tr)
		temp.value[++temp.value[0]] = tr;
	return temp;
}

            void huge::operator += (huge& other){
                *this = *this + other;
            }

        //Operator "-"
            huge huge::operator - (long long k){
    huge temp(k), cpy;
    copy(cpy);
    return cpy - temp;
}

            void huge::operator -= (long long k){
                *this = *this - k;
            }

            huge huge::operator - (huge& other) {
    huge temp, zero(0 * 1ll);
    if(compare(other) == 0) return zero;
    if(negative || other.negative){
        huge cpy, ocpy;
        copy(cpy);other.copy(ocpy);
        if(negative && !other.negative){ocpy.negative = 1; return cpy + ocpy;}
        if(!negative && other.negative){ocpy.negative = 0; return cpy + ocpy;}
        if(negative && other.negative){cpy.negative = 0;ocpy.negative = 0; return ocpy - cpy;}
	}
	int limit = max(value[0], other.value[0]);
	temp.value[0] = limit; int tr = 0, aux;
    if(compare(other) == -1){
        temp.negative = 1;
        for(int i = 1; i <= limit; i++){
            if(other.value[i] < value[i] + tr)    aux = other.value[i] + 10 - value[i] - tr;
                else    aux = other.value[i] - value[i] - tr;
            if(other.value[i] < value[i] + tr)    tr = 1;
                else    tr = 0;
            temp.value[i] = aux;
        }
        for(int i = limit; i >= 1; i--){
            if(temp.value[i] == 0)  temp.value[0]--;
                else    break;
        }
    }else{
        temp.negative = 0;
        for(int i = 1; i <= limit; i++){
            if(value[i] < other.value[i] + tr)    aux = value[i] + 10 - other.value[i] - tr;
                else    aux = value[i] - other.value[i] - tr;
            if(value[i] < other.value[i] + tr)    tr = 1;
                else    tr = 0;
            temp.value[i] = aux;
        }
        for(int i = limit; i >= 1; i--){
            if(temp.value[i] == 0)  temp.value[0]--;
                else    break;
        }
    }
    return temp;
}

            void huge::operator -= (huge& other){
                *this = *this - other;
            }

        //Operator "*"
            huge huge::operator * (long long k){
    huge temp(k), cpy;
    copy(cpy);
    return cpy * temp;
}

            void huge::operator *= (long long k){
                *this = *this * k;
            }

            huge huge::operator * (huge& other){
    huge temp;  temp.value[0] = value[0] + other.value[0];
    for(int i = 1; i <= other.value[0]; i++)
        for(int j = 1; j <= value[0]; j++)
            temp.value[i + j - 1] += other.value[i] * value[j];
    for(int i = 1; i <= temp.value[0]; i++){
        temp.value[i+1] += temp.value[i] / 10;
        temp.value[i] = temp.value[i] % 10;
    }
    for(int i = temp.value[0]; i >= 1; i--)
        if(temp.value[i] == 0)  temp.value[0]--;
        else break;
    if((negative && !other.negative) || (!negative && other.negative))
        temp.negative = 1;
    return temp;
}

            void huge::operator *= (huge& other){
                *this = *this * other;
            }

        //Operator "/"
            huge huge::operator / (long long k){
    huge temp;  temp.value[0] = value[0]; int tr = 0; bool neg = k < 0; k = abs(k);
    for(int i = value[0]; i >= 1; i--){
        tr += value[i];
        temp.value[i] = tr / k;
        tr -= tr/k*k;
        tr *= 10;
    }
    for(int i = value[0]; i >= 1; i--)
        if(temp.value[i] == 0)  temp.value[0]--;
        else break;
    if((negative && !neg) || (!negative && neg))
        temp.negative = 1;
    return temp;
}

            void huge::operator /= (long long k){
                *this = *this / k;
            }

            huge huge::operator / (huge& other){
    huge cpy, ocpy; copy(cpy); int comp = cpy.compare(other), res = 0;
    other.copy(ocpy);
    while(comp == 1 || comp == 0){
        cpy = cpy - ocpy;
        res++;
        comp = cpy.compare(other);
    }
    return res;
}

            void huge::operator /= (huge& other){
                *this = *this / other;
            }

        //Operator "%"

            huge huge::operator % (long long k){
    huge temp;  temp.value[0] = value[0]; int tr = 0; k = abs(k);
    for(int i = value[0]; i >= 1; i--){
        tr += value[i];
        temp.value[i] = tr / k;
        tr -= tr/k*k;
        tr *= 10;
    }
    if(negative == true)
        tr=-tr;
    return tr/10;
}

            void huge::operator %= (long long k){
                *this = *this % k;
            }

            huge huge::operator % (huge& other){
    huge cpy, ocpy; copy(cpy); int comp = cpy.compare(other), res = 0;
    other.copy(ocpy);
    while(comp == 1 || comp == 0){
        cpy = cpy - ocpy;
        res++;
        comp = cpy.compare(other);
    }
    return cpy;
}

            void huge::operator %= (huge& other){
                *this = *this % other;
            }

    //Comparisons
        //Smaller ("<")
            bool huge::operator < (long long k){
                huge temp(k);
                return compare(temp) == -1;
            }

            bool huge::operator < (huge& other){
                return compare(other) == -1;
            }

        //Smaller or equal ("<=")
            bool huge::operator <= (long long k){
                huge temp(k);
                return compare(temp) != 1;
            }

            bool huge::operator <= (huge& other){
                return compare(other) != 1;
            }

        //Bigger (">")
            bool huge::operator > (long long k){
                huge temp(k);
                return compare(temp) == 1;
            }

            bool huge::operator > (huge& other){
                return compare(other) == 1;
            }

        //Bigger or equal (">=")
            bool huge::operator >= (long long k){
                huge temp(k);
                return compare(temp) != -1;
            }

            bool huge::operator >= (huge& other){
                return compare(other) != -1;
            }

        //Equal ("==")
            bool huge::operator == (long long k){
                huge temp(k);
                return compare(temp) == 0;
            }

            bool huge::operator == (huge& other){
                return compare(other) == 0;
            }

        //Different ("!=")
            bool huge::operator != (long long k){
                huge temp(k);
                return compare(temp) != 0;
            }

            bool huge::operator != (huge& other){
                return compare(other) != 0;
            }





