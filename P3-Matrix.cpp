/* ------------------------------------------------------------------------------------------------------------------
FILE NAME:         Matrix.cpp
DESCRIPTION:       Implementation file for matrix_math.cpp
COMPILER:          GNU g++ compiler on Linux
 NOTES:            This file contains the member functions definitions

MODIFICATION HISTORY:
Author                      Date               Version      Version Comments
---------------             ----------         -------      --------------------
Jefferson Phillips Retana   2019-11-30         1.0          Original version
Jefferson Phillips Retana   2019-12-01         1.1          Constructors / Destructor working properly
Jefferson Phillips Retana   2019-12-01         1.2          >> << operators implemented
Jefferson Phillips Retana   2019-12-02         1.3          Assigment operator implemented. (Doesn't work yet)
Jefferson Phillips Retana   2019-12-02         2.0          + operator implemented
Jefferson Phillips Retana   2019-12-03         2.1          Debugging + operator
Jefferson Phillips Retana   2019-12-03         2.2          Implementation of - and *
Jefferson Phillips Retana   2019-12-03         2.3          Operator changed to void
Jefferson Phillips Retana   2019-12-04         2.4          operator= corrected to reference Matrix
Jefferson Phillips Retana   2019-12-04         2.5          First Version of multiplication implemented
                                                            (segmentation fault as for now)
Jefferson Phillips Retana   2019-12-04         2.6          Multiplication is now working
Jefferson Phillips Retana   2019-12-04         2.7          Modification on output
                                                            (Everything is now outputted from the driver)
Jefferson Phillips Retana   2019-12-04         2.8          Copy Constructor added
Jefferson Phillips Retana   2019-12-05         3.0          Transpose matrix implemented
Jefferson Phillips Retana   2019-12-06         4.0          Sub Matrix and determinant implemented
------------------------------------------------------------------------------------------------------- */

//Including Header file
#include "Matrix.h"

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix::Matrix()
DESCRIPTION:       Matrix Constructor
RETURNS:           Nothing
------------------------------------------------------------------------------- */
Matrix::Matrix()
{
    #ifdef TEST
        cout << "Constructor Running here\n";
    #endif

    rows = 0;
    cols = 0;
    matarray = nullptr;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix(int, int)
DESCRIPTION:       Overloaded Matrix Constructor
RETURNS:           Nothing
------------------------------------------------------------------------------- */
Matrix::Matrix(int r, int c)
{
    #ifdef TEST
        cout << "Constructor Running here\n";
    #endif

    rows = r;
    cols = c;

    matarray = new int*[rows];
    for (int i = 0; i < rows; i++)
        matarray[i] = new int[cols];
}

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix(Matrix &obj)
DESCRIPTION:       Copy Constructor
RETURNS:           Nothing
------------------------------------------------------------------------------- */
Matrix::Matrix(Matrix &obj)
{
    #ifdef TEST
        cout << "Constructor Running here\n";
    #endif
    rows = obj.rows;
    cols = obj.cols;

    obj.matarray = new int*[obj.rows];
    for (int i = 0; i < obj.rows; i++)
        obj.matarray[i] = new int[obj.cols];

    for (int i =0; i < obj.rows; i++)
    {
        for(int j = 0; j < obj.cols; j++)
        {
            matarray[i][j] = obj.matarray[i][j];
        }
    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          ~Matrix()
DESCRIPTION:       Destructor
RETURNS:           Nothing
NOTES:             Inherited classes will also run this destructor eventually
------------------------------------------------------------------------------- */
Matrix::~Matrix()
{
    #ifdef TEST
    cout << "Destructor running here\n";
    #endif

    if( matarray!= nullptr)
    {
            for (int i = 0; i < rows; i++)
                delete[] matarray[i];

            delete[] matarray;
    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator>>(istream &, Matrix &)
DESCRIPTION:       Overloading the >> operator
RETURNS:           istream
 ------------------------------------------------------------------------------- */
istream &operator>>(istream &in, Matrix &matrix)
{
    matrix.~Matrix();

    in >> matrix.rows;
    in.ignore(3);
    in >> matrix.cols;

    matrix.matarray = new int*[matrix.rows];
    for (int i = 0; i < matrix.rows; i++)
        matrix.matarray[i] = new int[matrix.cols];

    for (int i =0; i < matrix.rows; i++)
    {
        for(int j = 0; j < matrix.cols; j++)
        {
            in >> matrix.matarray[i][j];
        }
    }

    return in;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator<<(ostream &, const Matrix &)
DESCRIPTION:       Overloading the << operator
RETURNS:           ostream
------------------------------------------------------------------------------- */
ostream &operator<<(ostream & out, const Matrix &matrix)
{
    out << setw(6) << matrix.rows <<" X " << matrix.cols << endl;

    for (int i = 0; i < matrix.rows; i++)
    {
        for(int j = 0; j < matrix.cols; j++)
        {
            out << setw(6) << matrix.matarray[i][j];
        }
        out << endl;
    }
    return out;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator<<(ostream &, const Matrix &)
DESCRIPTION:       Overloading the << operator
RETURNS:           *this (Pointer to the calling object)
NOTES:             Major problems before the correct code
                    (Segmentation fault can be a problem)
------------------------------------------------------------------------------- */
Matrix& Matrix::operator=(const Matrix &right)
{
    if(this != &right)  //If they both point to the same address, dont do it.
    {
        //Deleting matarray
        if( matarray!= nullptr)
        {
            for (int i = 0; i < rows; i++)
                delete[] matarray[i];

            delete[] matarray;
        }

        //Assigning values
        rows = right.rows;
        cols = right.cols;

        //Re-initializing matarray
        this->matarray = new int*[rows];
        for (int i = 0; i < rows; i++)
            this->matarray[i] = new int[cols];

        //Copying values to the matarray
        for (int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                this->matarray[i][j] = right.matarray[i][j];
            }
        }
    }
    return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION:          is_empty()
DESCRIPTION:       Check if the Matrix has being initialized yet
RETURNS:           Boolean expresion
 ------------------------------------------------------------------------------- */
bool Matrix::is_empty()
{
    bool emptiness = false;

    if (rows == 0 && matarray == nullptr)
        emptiness = true;

    return emptiness;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator==(const Matrix_ops &)
DESCRIPTION:       Checks for equality between two matrices
RETURNS:           Bool
 ------------------------------------------------------------------------------- */
bool Matrix_ops::operator==(const Matrix_ops & m2)
{
    bool equality = true;

    //Checking Size
    if(rows != m2.rows || cols != m2.cols)
        return false;

    //Checking elements
    for (int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if (matarray[i][j] != m2.matarray[i][j])
                return false;
        }
    }
    return equality;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix_ops Matrix_ops::operator+(const Matrix_ops &)
DESCRIPTION:       Adds two matrices
RETURNS:           Matrix_ops object holding the result
 ------------------------------------------------------------------------------- */
Matrix_ops Matrix_ops::operator+(const Matrix_ops &m2)
{
    Matrix_ops result;

    if(rows != m2.rows || cols != m2.cols)
    {
        cout << "\nERROR/IMPOSSIBLE ACTION: Matrices of different sizes cannot be added.\n";
        return result;
    }

    result.rows= rows;
    result.cols= cols;

    result.matarray = new int*[result.rows];
    for (int i = 0; i < rows; i++)
        result.matarray[i] = new int[result.cols];

    for (int i = 0; i < result.rows; i++)
    {
        for (int j = 0; j < result.cols; j++)
        {
            result.matarray[i][j] = matarray[i][j] + m2.matarray[i][j];
        }
    }

    return result;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix_ops Matrix_ops::operator-(const Matrix_ops &)
DESCRIPTION:       Subtracts two matrices
RETURNS:           Matrix_ops object holding the result
 ------------------------------------------------------------------------------- */
Matrix_ops Matrix_ops::operator-(const Matrix_ops &m2)
{
    Matrix_ops result;

    if(rows != m2.rows || cols != m2.cols)
    {
        cout << "\nERROR/IMPOSSIBLE ACTION: Matrices of different sizes cannot be subtracted.\n";
        return result;
    }

    result.rows= rows;
    result.cols= cols;

    result.matarray = new int*[result.rows];
    for (int i = 0; i < rows; i++)
        result.matarray[i] = new int[result.cols];

    for (int i = 0; i < result.rows; i++)
    {
        for (int j = 0; j < result.cols; j++)
        {
            result.matarray[i][j] = matarray[i][j] - m2.matarray[i][j];
        }
    }

    return result;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator*(const Matrix_ops &m2)
DESCRIPTION:       Adds two matrices
RETURNS:           Matrix_ops object holding the result
NOTES:             Dimensions -> (M x N) X (N x P) = (M x P)
                   A new matrix is created which will be returned (Constructors sets everything to zero)
 ------------------------------------------------------------------------------- */
Matrix_ops Matrix_ops::operator*(const Matrix_ops &m2)
{
    Matrix_ops result;

    if(cols != m2.rows)
    {
        cout << "\nERROR/IMPOSSIBLE ACTION: The number of columns Matrix1 must equal the rows in Matrix2.\n";
        return result;
        //Additional Info:
        //https://i2.wp.com/www.mathbootcamps.com/wp-content/
        // uploads/matrix-product-is-defined.jpg?resize=558%2C349
    }

    result.rows= rows;
    result.cols= m2.cols;

    result.matarray = new int*[result.rows];
    for (int i = 0; i < rows; i++)
        result.matarray[i] = new int[result.cols];

    for (int i = 0; i < result.rows; i++)
    {
        for (int j = 0; j < result.cols; j++)
        {
            for (int k = 0; k < cols; k++)
            {
                result.matarray[i][j] += matarray[i][k] * m2.matarray[k][j];
            }
        }
    }

    return result;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator*(int)
DESCRIPTION:       Overloaded * operator. It multiplies a matrix times a scalar.
RETURNS:           Matix_ops Object
 ------------------------------------------------------------------------------- */
Matrix_ops Matrix_ops::operator*(int scalar)
{
    Matrix_ops result(rows, cols);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.matarray[i][j] = matarray[i][j] * scalar;

    return result;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator/(int)
DESCRIPTION:       / operator. It divides a matrix by a scalar.
RETURNS:           Matix_ops Object
 ------------------------------------------------------------------------------- */
Matrix_ops Matrix_ops::operator/(int scalar)
{
    Matrix_ops result(rows, cols);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.matarray[i][j] = matarray[i][j] / scalar;

    return result;
}

/* -----------------------------------------------------------------------------
FUNCTION:          trans(const Matrix_ops &)
DESCRIPTION:       Transpose a matrix,
RETURNS:           Matix_ops Object
 ------------------------------------------------------------------------------- */
Matrix_ops Matrix_ops::trans()
{
    Matrix_ops result(cols, rows); //Initializing Matrix the other way around

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.matarray[j][i] = matarray[i][j];

    return result;
}

/* -----------------------------------------------------------------------------
FUNCTION:          sub_mat()
DESCRIPTION:       Calculates the submatrix of a matrix,
RETURNS:           Matix_ops Object
NOTES:             i and j are integers. They represent the number of row and column which will be cut put
 ------------------------------------------------------------------------------- */
Matrix_ops Matrix_ops::sub_mat(int r, int c)
{
    Matrix_ops result(rows-1, cols-1);  //Matrix will have -1 dimensions

    //r and c are the numbers of the rows and columns, they are not subscripts. So:
    r--;
    c--;

    if(r > result.rows || c > result.cols)
    {
        cout << "\nERROR/IMPOSSIBLE ACTION: Check the dimensions of the inputted matrix." << endl;
        exit(7);
    }

    int iprime = 0;
    for (int i = 0; i < rows; i++)
    {
        int jprime = 0;
        for (int j = 0; j < cols; j++)
        {
            if (c!=j && r!=i)
                result.matarray[iprime][jprime] = matarray[i][j];
            if (c!=j) jprime++;
        }
        if (r!=i) iprime++;
    }

    return result;
}

/* -----------------------------------------------------------------------------
FUNCTION:          det()
DESCRIPTION:       Calculates matrix determinant
RETURNS:           Double (Determinant)
NOTES:             Source code based on:
                   "Determinant of a Square Matrix"
                   By:          Paul Bourke
                   Published:   June 2001

                   This is a recursive function
------------------------------------------------------------------------------- */
double Matrix_ops::det()
{
    int i, j, j1, j2;
    double det = 0;
    int **m = nullptr;

    if(rows != cols)
    {
        cout << "\nERROR/IMPOSSIBLE ACTION: Matrix is not squared" << endl;
        return 0;
    }

    if (rows < 1)
        return 0;

    else if (rows == 1)
        det = matarray[0][0];

    else if (rows == 2)
        det = matarray[0][0] * matarray[1][1] - matarray[1][0] * matarray[0][1];

    else {
        det = 0;
        for (j1 = 0; j1 < rows; j1++)
        {
            m = static_cast<int **>(malloc((rows - 1) * sizeof(double *)));
            for (i = 0; i < rows - 1; i++)
                m[i] = static_cast<int *>(malloc((rows - 1) * sizeof(double)));

            for (i = 1; i < rows; i++)
            {
                j2 = 0;
                for (j = 0; j < rows; j++)
                {
                    if (j == j1)
                        continue;
                    m[i-1][j2] = matarray[i][j];
                    j2++;
                }
            }

            Matrix_ops *matprt;
            matprt = new Matrix_ops(rows-1, rows -1);
            for (int k = 0; k < rows-1; k++)
                for(int z = 0; z < rows-1; z++)
                    matprt->matarray[k][z] = m[k][z];

            det += pow(-1.0, 1.0 + j1 + 1.0) * matarray[0][j1] * matprt->det();
            for (i = 0; i < rows-1; i++)
                free(m[i]);
            free(m);
        }
    }

    return(det);
}

/* -----------------------------------------------------------------------------
FUNCTION:          adj()
DESCRIPTION:       Calculates matrix determinant
RETURNS:           Matrix
NOTES:             Source code based on:
                   "Inverse of a square matrix"
                   By:          Paul Bourke
                   Published:   August 2002

                   This is the transposed cofactor of A
-------------------------------------------------------------------------------*/
Matrix_ops Matrix_ops::adj()
{
    Matrix_ops cofactor(rows, cols);
    Matrix_ops result(rows, cols);

    //---------------------------------------
    //Calculating the cofactor
    //---------------------------------------

    int i, j, ii, jj, i1, j1;
    int det;
    int **c;

    c = static_cast<int **>(malloc((rows - 1) * sizeof(double *)));

    for (i=0;i<rows-1;i++)
        c[i] = static_cast<int *>(malloc((rows - 1) * sizeof(double)));
    for (j=0;j<rows;j++)
    {
        for (i=0;i<rows;i++)
        {
            /* Form the adjoint a_ij */
            i1 = 0;
            for (ii=0;ii<rows;ii++)
            {
                if (ii == i)
                    continue;
                j1 = 0;
                for (jj=0;jj<rows;jj++)
                {
                    if (jj == j)
                        continue;
                    c[i1][j1] = matarray[ii][jj];
                    j1++;
                }
                i1++;
            }

            //We need the determinant
            Matrix_ops *matprt;
            matprt = new Matrix_ops(rows-1, rows -1);
            for (int k = 0; k < rows-1; k++)
                for(int z = 0; z < rows-1; z++)
                    matprt->matarray[k][z] = c[k][z];

            det = matprt->det();

            /* Fill in the elements of the cofactor */
            cofactor.matarray[i][j] = pow(-1.0, i + j + 2.0) * det;
        }
    }

    for (i=0;i<rows-1;i++)
        free(c[i]);
    free(c);

    //Getting the transposed cofactor
    result = cofactor.trans();
    return result;
}

/* -----------------------------------------------------------------------------
FUNCTION:          inv()
DESCRIPTION:       Calculates matrix inverse
RETURNS:           Matrix
NOTES:             Source code based on:
                   "Inverse of a square matrix"
                   By:          Paul Bourke
                   Published:   August 2002

                   (1/det(A)) * adjA
-------------------------------------------------------------------------------*/
Matrix_ops Matrix_ops::inv()
{
    Matrix_ops result(rows, cols);

    result = this->adj() * (1.0/this->det());

    return result;
}