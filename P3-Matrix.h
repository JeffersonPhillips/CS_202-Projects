/* -----------------------------------------------------------------------------
FILE NAME:         Matrix.h
DESCRIPTION:       Header file for matrix_math.cpp
COMPILER:          GNU g++ compiler on Linux

MODIFICATION HISTORY:
Author                      Date               Version      Version Comments                \
---------------             ----------         -------      --------------------            \
Jefferson Phillips Retana   2019-11-30         1.0          Original version
Jefferson Phillips Retana   2019-12-01         1.1          == << >> operators implemented
Jefferson Phillips Retana   2019-12-01         1.2          Debugging = operator (still doesnt work)
Jefferson Phillips Retana   2019-12-02         2.0          Inherited Matrix_ops implemented
Jefferson Phillips Retana   2019-12-03         2.1          Debugging = operator (as void function)
Jefferson Phillips Retana   2019-12-03         2.2          operator(+ - *) member functions implemented
Jefferson Phillips Retana   2019-12-04         2.3          operator= corrected to reference Matrix
Jefferson Phillips Retana   2019-12-04         2.8          Copy Constructor added
Jefferson Phillips Retana   2019-12-05         3.0          Transpose matrix implemented
 ----------------------------------------------------------------------------- */

//Enable/Disable code
//#define TEST

#ifndef MATRIX_H_
#define MATRIX_H_

//Preprocessor directives
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <cmath>

//Namespace
using namespace std;

//Global constants
const char PROGRAMMER_NAME[] = "Jefferson Phillips Retana";	// Global constant

//Mother Class
class Matrix
{
    protected:
        int rows, cols;
        int **matarray;

    public:
        Matrix();
        Matrix(int, int);
        Matrix(Matrix &obj);
        ~Matrix();
        bool is_empty();
        Matrix& operator= (const Matrix &);

    //Good fellas, AKA, friends:
    friend ostream & operator<< (ostream &, const Matrix&);
    friend istream & operator>> (istream &, Matrix&);
};

//Inherited Class
class Matrix_ops : public Matrix
{
    private:
        using Matrix :: rows;
        using Matrix :: cols;
        using Matrix :: matarray;

    public:
        using Matrix :: Matrix;
        using Matrix :: operator=;

        Matrix_ops trans();
        Matrix_ops sub_mat(int, int);
        double det();
        Matrix_ops adj();
        Matrix_ops inv();

    bool operator== (const Matrix_ops &);
    Matrix_ops operator+(const Matrix_ops &);
    Matrix_ops operator-(const Matrix_ops &);
    Matrix_ops operator*(const Matrix_ops &);
    Matrix_ops operator*(int);
    Matrix_ops operator/(int);

};


#endif