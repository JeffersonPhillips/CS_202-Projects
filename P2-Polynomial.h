/* -----------------------------------------------------------------------------------------------------------
FILE NAME:          Polynomial.h
DESCRIPTION:        Class specification file
USAGE:              ./poly_class
COMPILER:           GNU g++ compiler on Linux
NOTES:              Preprocessor directives/Class Declaration/Prototypes are included in this file
                    Related files: poly_class.cpp and Polynomial.cpp

MODIFICATION HISTORY:
Author                          Date                Version         Version Notes
---------------                 ----------          --------        ------------------
Jefferson Phillips Retana       2019-10-28          1.0             Original version
Jefferson Phillips Retana       2019-11-02          1.1             New prototypes added
Jefferson Phillips Retana       2019-11-02          1.2             erase_coef_data() added.
Jefferson Phillips Retana       2019-11-02          1.3             Function headers added.
Jefferson Phillips Retana       2019-11-04          1.4             Changes after presentation in class.
Jefferson Phillips Retana       2019-11-04          1.5             Input/Output overloaded operators added
Jefferson Phillips Retana       2019-11-04          1.6             == overloaded operators added
Jefferson Phillips Retana       2019-11-06          1.7             -- operator included
Jefferson Phillips Retana       2019-11-06          1.8             ++ operator included
Jefferson Phillips Retana       2019-11-06          2.0             ++ postfix operator included
Jefferson Phillips Retana       2019-11-07          2.1             Copy Constructor Added
Jefferson Phillips Retana       2019-11-07          3.0             Implementation of dynamic memory
Jefferson Phillips Retana       2019-11-07          3.1             Comment out dynamic memory code
 ----------------------------------------------------------------------------------------------------------- */

#ifndef _POLYNOMIAL_H
#define _POLYNOMIAL_H

//Preprocessor directives:
#include <iostream>
#include <cmath>
#include <cstring>

//Macros
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define GET_MAX_DEGREE(x,y) ((x)>(y)?(x):(y))
//#define cttr    //Comment out if no need to print constructors workflow.

//Namespaces:
using namespace std;

//Global Constant:
const char PROGRAMMER_NAME[] = "Jefferson Phillips Retana";
const int MAX_DEGREE = 10;

//External Prototypes
double get_x();
void get_bound(double []);

//Classes
class Polynomial
{
    private:
        int degree;                 //Degree of polynomial
        double coef[MAX_DEGREE];    //Coefficients

public:
    Polynomial();   //Const.
    Polynomial(Polynomial &);    //Copy Constructor
    ~Polynomial();  //Dest.

    Polynomial operator+ (const Polynomial &);
    Polynomial operator- (const Polynomial &);
    Polynomial operator* (const Polynomial &);
    const Polynomial operator= (const Polynomial &);
    Polynomial operator-- ();
    Polynomial operator++ ();
    bool operator== (const Polynomial &);
    double operator() (double);
    double operator++ (int);


    //Good fellows, AKA: friends:
    friend void erase_coef_data(Polynomial &);
    friend istream& operator>> (istream &, Polynomial &); //Overloaded >> operator
    friend ostream& operator<< (ostream &, const Polynomial &); //Overloaded << operator

    //Vestigial Functions (Not erased just to keep the records)
    void get_poly();
    void display_poly();

    void add_poly(Polynomial, Polynomial);
    void subtr_poly(Polynomial, Polynomial);
    void mult_poly(Polynomial, Polynomial);
};

#endif