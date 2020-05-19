/* -----------------------------------------------------------------------------------------------------------
FILE NAME:          Polynomial.cpp
DESCRIPTION:        Class Implementation File
USAGE:              ./poly_class
COMPILER:           GNU g++ compiler on Linux
NOTES:              Functions // Member functions are included in this file.
                    Related files: poly_class.cpp and Polynomial.h

MODIFICATION HISTORY:
Author                          Date                Version         Version Notes
---------------                 ----------          --------        ------------------
Jefferson Phillips Retana       2019-10-28          1.0             Original version
Jefferson Phillips Retana       2019-10-30          1.1             Implementation of first functions - Modification during lecture
Jefferson Phillips Retana       2019-11-02          1.2             Implementation of operator overloading.
Jefferson Phillips Retana       2019-11-02          1.3             erase_coef_data() added.
Jefferson Phillips Retana       2019-11-02          1.4             Output function modified.
Jefferson Phillips Retana       2019-11-02          1.5             Function headers added.
Jefferson Phillips Retana       2019-11-02          1.6             erase_coef_data updated as a friend.
Jefferson Phillips Retana       2019-11-04          1.7             Input/Output overloaded operators added
Jefferson Phillips Retana       2019-11-05          1.8             == overloaded operators added
Jefferson Phillips Retana       2019-11-06          1.9             -- operator included
Jefferson Phillips Retana       2019-11-06          2.0             ++ operator included
Jefferson Phillips Retana       2019-11-06          2.1             ++ postfix operator included
Jefferson Phillips Retana       2019-11-06          2.2             Copy Constructor Added
Jefferson Phillips Retana       2019-11-07          2.3             Superscripts added to overloaded << operator
 ----------------------------------------------------------------------------------------------------------- */

//Preprocessor directives:
#include "Polynomial.h" //Header file

/* -----------------------------------------------------------------------------
FUNCTION:          Polynomial()
DESCRIPTION:       Polynomial class constructor.
RETURNS:           Nothing.
NOTES:             This function initializes the values of the objects' elements.
------------------------------------------------------------------------------- */
Polynomial::Polynomial()    //Constructor
{
#ifdef cttr
    cout << "Constructor running here." << endl;
#endif
    //Initialize everything to zero.
    degree = 0;
    for(int i = 0; i < ARRAY_SIZE(coef); i++)
        coef[i] = 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Polynomial()
DESCRIPTION:       Polynomial class constructor.
RETURNS:           Nothing.
NOTES:             Overloaded cnostrcutor.
------------------------------------------------------------------------------- */
Polynomial::Polynomial(Polynomial &)    //overloaded Constructor
{
#ifdef cttr
    cout << "Overloaded constructor running here." << endl;
#endif
    //Initialize everything to zero.
    degree = 0;
    for(int i = 0; i < ARRAY_SIZE(coef); i++)
        coef[i] = 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          ~Polynomial()
DESCRIPTION:       Polynomial class destructor.
RETURNS:           Nothing.
NOTES:             Function runs when object is destroyed.
------------------------------------------------------------------------------- */
Polynomial::~Polynomial()   //Destructor
{
#ifdef cttr
    cout << "Destructor running here." << endl;
#endif

    //Nothing to be deleted. No dinamic memory used
}

/* -----------------------------------------------------------------------------
FUNCTION:          istream operator >> (Polynomial &)
DESCRIPTION:       Gets polynomials from the user.
RETURNS:           Nothing.
NOTES:              Replaces "get_poly"
------------------------------------------------------------------------------- */
istream &operator>>(istream &strm, Polynomial &pol)
{
    static int n;   //Track saved Polynomial
    bool keeplooping = true;
    while(keeplooping)
    {
        cout << "Degree of Polynomial #"  << n+1 << ":  ";
        strm >> pol.degree;

        if(pol.degree <= 5) //Max degree = 10 (Multiplication requires double)
            keeplooping = false;
        else
            cout << "For now, Max Degree = 5. Please reenter." << endl;
    }

    cout << "Enter " << pol.degree+1 << " coefficients   :  ";
        for(int i = pol.degree; i >=0 ; i--)
        strm >> pol.coef[i];

    n++;
    return strm;
}

/* -----------------------------------------------------------------------------
FUNCTION:           ostream& operator<< (ostream &, const Polynomial &)
DESCRIPTION:        Print polynomials to screen.
RETURNS:            Nothing.
NOTES:NOTES:        To display properly in PuTTY, you need to set:
                    Change Settings > Translation:  UTF-8
                    Change Settings > Appearance > Font: Consolas or DejaVu Sans Mono
------------------------------------------------------------------------------- */
ostream &operator<<(ostream &strm, const Polynomial &pol)
{
    static int n;   //Track printing Polynomial

    const char* expo[10] = {                                    // Array of Unicode characters 0 - 9
            "\u2070", "\u00B9", "\u00B2", "\u00B3", "\u2074",   //Coded by Ed Corbett
            "\u2075", "\u2076", "\u2077", "\u2078", "\u2079"};  //exp_test.cpp

    if (n<2)        //Dont print againg afer the second have being printed
        cout << "Polynomial #" << ++n << " is       :  ";

    for(int i = pol.degree; i>=0; i--)
    {
        if (pol.coef[i] != 0)
        {
            if (i < pol.degree)
            {
                if (pol.coef[i] >= 0) cout << " +";
                else cout << " ";
            }
            strm << pol.coef[i];

            if (i > 1) cout << "x" <<expo[i];
            if (i == 1) cout << "x";
        }
    }
    return strm;
}

/* -----------------------------------------------------------------------------
FUNCTION:           const Polynomial operator= (const Polynomial &);
DESCRIPTION:        Overloads = operator to assign one polynomial to another.
RETURNS:            Class object.
NOTES:              Const so the function dont change the values in p1
------------------------------------------------------------------------------- */
const Polynomial Polynomial::operator=(const Polynomial &p1)
{
    if (this != &p1)
    {
        degree = p1.degree;

        for(int i = p1.degree; i >= 0; i--)
        coef[i] = p1.coef[i];
    }
    return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION:           Polynomial::operator+ (const Polynomial &)
DESCRIPTION:        Overloads + operator to add two polynomials.
RETURNS:            Class object.
NOTES:              Substitutes add_poly()
------------------------------------------------------------------------------- */
Polynomial Polynomial::operator+(const Polynomial & p1)
{
    Polynomial p2;

    p2.degree = GET_MAX_DEGREE(degree, p1.degree);

    for(int i = p2.degree; i >= 0; i--)        //i = degree because of the last term in the polynomial (no x)
        p2.coef[i] = coef[i] + p1.coef[i];

    return p2;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Polynomial::operator- (const Polynomial &)
DESCRIPTION:       Overloads - operator to subtract two polynomials.
RETURNS:           Class object.
NOTES:             Substitutes subtr_poly()
------------------------------------------------------------------------------- */
Polynomial Polynomial::operator-(const Polynomial & p1)
{
    Polynomial p2;

    p2.degree = GET_MAX_DEGREE(degree, p1.degree);

    for(int i = p2.degree; i >= 0; i--)        //i = degree because of the last term in the polynomial (no x)
        p2.coef[i] = coef[i] - p1.coef[i];

    return p2;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Polynomial::operator* (const Polynomial &)
DESCRIPTION:       Overloads - operator to subtract two polynomials.
RETURNS:           Class object.
NOTES:             Substitutes subtr_poly()
-------------------------------------------------------------------------------*/
Polynomial Polynomial::operator* (const Polynomial & p1)
{
    Polynomial p2;

    p2.degree = degree + p1.degree;

    for(int i = p1.degree; i >= 0; i--)
    {
        for(int j = p2.degree; j >=0; j--)
        {
            p2.coef[i+j] += coef[i] * p1.coef[j];
        }
    }
    return p2;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Double operator() (double);
DESCRIPTION:       Overloads () operator to evaluate an object.
RETURNS:           Double value (x)
NOTES:
-------------------------------------------------------------------------------*/
double Polynomial::operator()(double x)
{
    double result = 0;
    for (int i = degree; i >= 0; i--)
    {
        result += coef[i] * pow(x, i);
    }

    return result;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator== (const Polynomial &)
DESCRIPTION:       Set all member of a private array to zero.
RETURNS:           bool
NOTES:
------------------------------------------------------------------------------- */
bool Polynomial::operator==(const Polynomial &p1)
{
    bool poly_equal = true;
    int maxdegree =  GET_MAX_DEGREE(degree, p1.degree);
    //The degrees stored might differ, but if the the first values
    //of any polynomial are zero, the polynomials might still be equivalent.
    //If indeeed there is a first value=0,
    //the following loop works because all the values were initialized to zero.

    for(int i = maxdegree; i >= 0; i--)
    {
        if (coef[i] != p1.coef[i])
            poly_equal = false;
    }

    return poly_equal;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Polynomial::operator--()
DESCRIPTION:       Derivation of a polynomial
RETURNS:           Polynomial
NOTES:             Prefix
------------------------------------------------------------------------------- */
Polynomial Polynomial::operator--()
{
    Polynomial p1;
    p1.degree = degree-1;

    for(int i = 1; i <= degree; i++)
    {
        p1.coef[(i-1)] = coef[i]*i;
    }

    return p1;
}
/* -----------------------------------------------------------------------------
FUNCTION:          Polynomial::operator++()
DESCRIPTION:       Integration of a polynomial
RETURNS:           Polynomial
NOTES:             Prefix
------------------------------------------------------------------------------- */
Polynomial Polynomial::operator++()
{
    Polynomial p1;
    p1.degree = degree+1;

    for(int i = 0; i <= degree; i++)
    {
        p1.coef[i+1] = coef[i]/(i+1);
    }

    return p1;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Polynomial::operator++()
DESCRIPTION:       Integration of a polynomial
RETURNS:           Polynomial
NOTES:             Postfix
------------------------------------------------------------------------------- */
double Polynomial::operator++(int)
{
    double def_int = 0;
    double bounds[2];

    get_bound(bounds);

    for(int i= degree; i >= 0; i--)
    {
        def_int += coef[i] * pow(bounds[1], i);
        def_int -= coef[i] * pow(bounds[0], i);
    }

    return def_int;
}

/* -----------------------------------------------------------------------------
FUNCTION:          erase_coef_data()
DESCRIPTION:       Set all member of a private array to zero.
RETURNS:           Nothing.
NOTES:
------------------------------------------------------------------------------- */
void erase_coef_data(Polynomial & p1)
{
    for(int i = 0; i < ARRAY_SIZE(p1.coef); i++)
        p1.coef[i] = 0;
}


/*
Vestigial Functions from now on.
*/

/* -----------------------------------------------------------------------------
FUNCTION:          get_poly()
DESCRIPTION:       Gets polynomials from the user.
RETURNS:           Nothing.
NOTES:
------------------------------------------------------------------------------- */
void Polynomial::get_poly()
{
    static int n;   //Track saved Polynomial
    bool keeplooping = true;
    while(keeplooping)
    {
        cout << "Degree of Polynomial #"  << n+1 << ":  ";
        cin >> degree;

        if(degree <= 5) //Max degree = 10 (Multiplication requires double)
            keeplooping = false;
        else
            cout << "For now, Max Degree = 5. Please reenter." << endl;
    }

    cout << "Enter " << degree+1 << " coefficients   :  ";
    for(int i = degree; i >=0 ; i--)
        cin >> coef[i];

    n++;
}

/* -----------------------------------------------------------------------------
FUNCTION:          display_poly()
DESCRIPTION:       Print polynomials to screen.
RETURNS:           Nothing.
NOTES:
------------------------------------------------------------------------------- */
void Polynomial::display_poly()
{
    static int n;   //Track printing Polynomial

    if (n<2)
        cout << "Polynomial #" << ++n << " is       :  ";

    for(int i = degree; i>=0; i--)
    {
        if (coef[i] != 0)
        {
            if (i < degree)
            {
                if (coef[i] >= 0) cout << " +";
                else cout << " ";
            }
            cout << coef[i];

            if (i > 1) cout << "x^" << i;
            if (i == 1) cout << "x";
        }
    }
    cout << endl;
}

/* -----------------------------------------------------------------------------
FUNCTION:          add_poly()
DESCRIPTION:       Adds two polynomials.
RETURNS:           Nothing.
NOTES:
------------------------------------------------------------------------------- */
void Polynomial::add_poly(Polynomial p0, Polynomial p1)
{
    cout << "Poly #1  +  Poly #2    :  ";
    degree = GET_MAX_DEGREE(p0.degree, p1.degree);

    for(int i = degree; i >= 0; i--)        //i = degree because of the last term in the polynomial
        coef[i] = p0.coef[i] + p1.coef[i];

}

/* -----------------------------------------------------------------------------
FUNCTION:          subtr_poly()
DESCRIPTION:       Subtracts two polynomials.
RETURNS:           Nothing.
NOTES:
------------------------------------------------------------------------------- */
void Polynomial::subtr_poly(Polynomial p0, Polynomial p1)
{
    cout << "Poly #1  -  Poly #2    :  ";
    degree = GET_MAX_DEGREE(p0.degree, p1.degree);

    for(int i = degree; i >= 0; i--)
        coef[i] = p0.coef[i] - p1.coef[i];

}

/* -----------------------------------------------------------------------------
FUNCTION:          mult_poly()
DESCRIPTION:       Multiplies two polynomials.
RETURNS:           Nothing.
NOTES:
------------------------------------------------------------------------------- */
void Polynomial::mult_poly(Polynomial p0 , Polynomial p1)
{
    cout << "Poly #1  *  Poly #2    :  ";
    degree = p0.degree + p1.degree;

    for(int i = degree; i >= 0; i--)
    {
        for(int j = degree; j >=0; j--)
        {
            coef[i+j] += p0.coef[i] * p1.coef[j];
        }
    }
}