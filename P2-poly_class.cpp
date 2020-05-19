/* -----------------------------------------------------------------------------------------------------------
FILE NAME:          poly_class.cpp
DESCRIPTION:        Driver File
USAGE:              ./poly_class
COMPILER:           GNU g++ compiler on Linux
NOTES:              Main function and flow of execution is in this file.
                    Related files: Polynomial.cpp and Polynomial.h

MODIFICATION HISTORY:
Author                          Date                Version         Version Notes
---------------                 ----------          --------        ------------------
Jefferson Phillips Retana       2019-10-28          1.0             Original version
Jefferson Phillips Retana       2019-10-30          1.1             Implementation of first functions - Modification during lecture
Jefferson Phillips Retana       2019-10-30          1.2             Implementation of operator overloading.
Jefferson Phillips Retana       2019-11-02          1.3             Function headers added.
Jefferson Phillips Retana       2019-11-02          1.4             First overloaded operators added.
Jefferson Phillips Retana       2019-11-02          1.5             erase_coef_data added to driver.
Jefferson Phillips Retana       2019-11-04          1.6             Changes after presentation in class.
Jefferson Phillips Retana       2019-11-04          1.7             Input/Output overloaded operators added
Jefferson Phillips Retana       2019-11-04          1.8             == overloaded operators added
Jefferson Phillips Retana       2019-11-06          1.9             -- operator included
Jefferson Phillips Retana       2019-11-06          2.0             ++ operator included
Jefferson Phillips Retana       2019-11-06          2.1             ++ postfix operator included
Jefferson Phillips Retana       2019-11-07          3.0             Implementation of dynamic memory
Jefferson Phillips Retana       2019-11-07          3.1             Comment out dynamic memory code
 ----------------------------------------------------------------------------------------------------------- */

//Preprocessor directives:
#include "Polynomial.h" //Header file

/* -----------------------------------------------------------------------------
FUNCTION:          main()
DESCRIPTION:       Main function of the program. Controls workflow.
RETURNS:           Integer value (0).
NOTES:
------------------------------------------------------------------------------- */
int main()
{
    cout << "\n--------------------------------------------------" << endl;
    cout << "Hello there. Welcome to the polynomial calculator" << endl;
    cout << "--------------------------------------------------" << endl << endl;

/*  Dynamic Memory: (Intent)
    //Creating Pointers
    Polynomial *polyptr = nullptr;
    Polynomial *fptr = nullptr;
    Polynomial *gptr = nullptr;

    //Dynamically allocating new points
    fptr = new Polynomial();
    gptr = new Polynomial;
    gptr = new Polynomial;
    polyptr = new Polynomial;
*/

    Polynomial poly[3], f, g;
    double x = 0;
    double objeval;
    double def_int;

    for(int i = 0; i < 2; i++)
    {
        cin >> poly[i];
        cout <<  poly[i] << endl << endl;
    }

//    erase_coef_data(poly[2]);
//    poly[2].add_poly(poly[0], poly[1]); //Adding 2 polynomials and storing the result in 3rd element of the array
//    poly[2].display_poly();

    cout << "Poly #1  +  Poly #2    :  ";
    poly[2] = poly[0] + poly[1];
    cout << poly[2] << endl;

//    erase_coef_data(poly[2]);
//    poly[2].subtr_poly(poly[0], poly[1]); //Subtracting 2 polynomials and storing the result in 3rd element of the array
//    poly[2].display_poly();

    cout << "Poly #1  -  Poly #2    :  ";
    erase_coef_data(poly[2]);   //Deleting all cumulative garbage
    poly[2] = poly[0] - poly[1];
    cout << poly[2] << endl;

//    erase_coef_data(poly[2]);   //Deleting all cumulative garbage
//    poly[2].mult_poly(poly[0], poly[1]); //Multiplying 2 polynomials and storing the result in 3rd element of the array
//    poly[2].display_poly();

    cout << "Poly #1  *  Poly #2    :  ";
    erase_coef_data(poly[2]);   //Deleting all cumulative garbage
    poly[2] = poly[0] * poly[1];
    cout << poly[2] << endl;

    cout << "Poly #1  =  Poly #2 ?  :  ";
    if (poly[0] == poly[1])             //Using == overloaded operator
        cout << "Yes, they are the same!" << endl;
    else
        cout << "No, they are different polynomials!" << endl;
    cout << endl;

//Object evaluation

    x = get_x();        //Getting x for 1st object evaluation
    f = poly[0];        //Poly #1 = f
    objeval = f(x);     //Get / Print Object Eval.
    cout << "When x = "<< x << ",  f(x) is   :  " << objeval << endl;

    x = get_x();        //Getting x for 2nd object evaluation
    g = poly[1];        //POly #2 = g
    objeval = g(x);     //Get / Print Object eval
    cout << "When x = "<< x << ",  g(x) is   :  " << objeval << endl << endl;

    erase_coef_data(poly[2]);   //Deleting all cumulative garbage
    poly[2] = --f;
    cout << "Differentiation, f'(x) :  ";
    cout << poly[2] << endl;

    erase_coef_data(poly[2]);   //Deleting all cumulative garbage
    poly[2] = --g;
    cout << "Differentiation, g'(x) :  ";
    cout << poly[2] << endl << endl;


    erase_coef_data(poly[2]);   //Deleting all cumulative garbage
    poly[2] = ++f;
    cout << "Indef Integration, F(x):  ";
    cout << poly[2]  << " +C" << endl;

    def_int = poly[2]++;
    cout << "Def Integration, f(x)  :  " << def_int << endl << endl;

    erase_coef_data(poly[2]);   //Deleting all cumulative garbage
    poly[2] = ++g;
    cout << "Indef Integration, G(x):  ";
    cout << poly[2]  << " +C" << endl;

    def_int = poly[2]++;
    cout << "Def Integration, g(x)  :  " << def_int << endl;

    //Time Stamp
    cout << endl;
    cout << "Programmed by: " << PROGRAMMER_NAME << " -- ";
    cout << __DATE__ << "  " __TIME__ << endl;
    cout << endl;

    return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          get_x()
DESCRIPTION:       Gets x value for the object evaluation.
RETURNS:           Double value (x).
NOTES:             Prompts the user about Object Eval. Validates input.
------------------------------------------------------------------------------- */
double get_x()
{
    double x = 0;
    bool loop = true;
    static int poly_num = 1;

    cout << "Poly #" << poly_num << " ObjEva. Input x:  ";

    while (loop)     //Getting x / Input validation
    {
        if (cin >> x)
            loop = false;
        else
            {
            cout << "Please input a valid value for x: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
    poly_num++;
    return x;
}

/* -----------------------------------------------------------------------------
FUNCTION:          get_bound()
DESCRIPTION:       Gets upper and lower bound for the definite integration.
RETURNS:           Nothing
NOTES:             Prompts the user about definite integral Validates input.
------------------------------------------------------------------------------- */
void get_bound(double bounds[2])
{
    cout << "Def Int f. Lower bound :  ";
    if(!(cin >> bounds[0]))
    {
        cout << "Wrong Input, setting lower bound to zero" << endl;
        bounds[0] = 0;
    }

    cout << "Def Int g. Lower bound :  ";
    if(!(cin >> bounds[1]))
    {
        cout << "Wrong Input, setting upper bound to zero" << endl;
        bounds[1] = 0;
    }
}