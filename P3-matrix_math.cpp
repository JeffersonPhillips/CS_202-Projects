/* -----------------------------------------------------------------------------------------------------------
FILE NAME:         Matrix.h
DESCRIPTION:       Header file for matrix_math.cpp
COMPILER:          GNU g++ compiler on Linux

MODIFICATION HISTORY:
Author                      Date               Version      Version Comments
---------------             ----------         -------      --------------------
Jefferson Phillips Retana   2019-11-30         1.0          Original version
Jefferson Phillips Retana   2019-11-30         1.1          arg_count and open_file implemented
Jefferson Phillips Retana   2019-12-01         1.2          work_flow divided into two possibilities
                                                            (-command or upper-case Letter)
Jefferson Phillips Retana   2019-12-01         1.3          Exception included to catch initial possible
                                                            incorrect arguments
Jefferson Phillips Retana   2019-12-01         1.3          Open file included
Jefferson Phillips Retana   2019-12-02         1.4          Original version
Jefferson Phillips Retana   2019-12-03         2.0          Initial -commands included
Jefferson Phillips Retana   2019-12-03         2.1          -commands debugging
Jefferson Phillips Retana   2019-12-03         2.2          Display help included
Jefferson Phillips Retana   2019-12-04         2.3          Basic A (operator) B included
Jefferson Phillips Retana   2019-12-04         3.0          operator= corrected to reference Matrix
Jefferson Phillips Retana   2019-12-04         2.5          First Version of multiplication implemented
                                                            (segmentation fault as for now)
Jefferson Phillips Retana   2019-12-04         2.6          Changes on output/input functions after
                                                            presentation in class
Jefferson Phillips Retana   2019-12-04         2.7          Modification on output
                                                            (Everything is now outputted from the driver)
Jefferson Phillips Retana   2019-12-04         2.8          overloaded* operator implemented
Jefferson Phillips Retana   2019-12-05         3.0          Transpose matrix implemented
Jefferson Phillips Retana   2019-12-06         4.0          Sub Matrix and determinant implemented
 ----------------------------------------------------------------------------------------------------------- */

//Including Header file
#include "Matrix.h"

//Prototypes
void arg_count(int);
void open_ifile(ifstream&, string&);
void open_ofile(ofstream&, string&);
void display_help();

/* -----------------------------------------------------------------------------
FUNCTION:          main()
DESCRIPTION:       Root function. Controls the workflow of the program.
RETURNS:           Integer value (0 if ok, 7 if error)
NOTES:             This program runs only with command line arguments
------------------------------------------------------------------------------- */
int main(int argc, char * argv[])
{
    string cmd;
    ifstream ifile;
    ofstream ofile;

    Matrix_ops mtx1, mtx2, mtx_result;

    //Exception to verify there are enough command line arguments
    try
    {
        arg_count(argc);
    }
    catch(char const* ERROR)
    {
        cout << ERROR << endl;
        return 7;
    }

    //Start operations
    //While there are still commands left (ignoring the first one)
    while(--argc)
    {
        cmd = *++argv;

        //Dividing the workflow into 2 subcategories:
        //Command starting with a dash.
        if (cmd[0] == '-')
        {
            if (cmd == "-h")
            {
                display_help();
            }
            else if (cmd == "-inp")      //-inp should read matrix file and display it to the screen.
            {
                cmd = *++argv;      //File name
                --argc;             //The next cmd line argument was read already
                open_ifile(ifile, cmd);
                cout << "\nInput file: " << cmd << endl << endl;
                ifile >> mtx1;      //Read Matrix
                cout << mtx1;       //Display matrix
            }
            else if (cmd == "-out")
            {
                cmd = *++argv;
                --argc;
                open_ofile(ofile, cmd);
                cout << "\nOutput file: " << cmd << endl << endl;

                if (!mtx_result.is_empty())  //Print the result if it has things inside
                    ofile << mtx_result;
                else                        //Print the matrix which was inputted.
                {
                    ofile << mtx1;
                    if (!mtx2.is_empty()) ofile << endl << endl << mtx2;
                }
            }
            else if (cmd == "-eq")
            {
                //Opening fie and getting first matrix
                cmd = *++argv;
                --argc;
                open_ifile(ifile, cmd);
                cout << "\n Matrix 1: " << cmd << endl;
                ifile >> mtx1;
                cout << mtx1;
                ifile.close();

                //Opening fie and getting second matrix
                cmd = *++argv;
                --argc;
                open_ifile(ifile, cmd);
                cout << "\n Matrix 2: " << cmd << endl;
                ifile >> mtx2;
                cout << mtx2;

                if (mtx1 == mtx2)
                cout << "\nThe matrices are equal to each other!\n\n";
                else
                    cout << "\nThe matrices have different dimensions or elements.\n\n";
            }
            else if (cmd == "-T")
            {
                cmd = *++argv;
                --argc;
                open_ifile(ifile, cmd);
                cout << "\n Matrix 1: " << cmd << endl;
                ifile >> mtx1;
                cout << mtx1;

                mtx_result = mtx1.trans();
                cout << "\nTRANSPOSED matrix (A^T):\n" << mtx_result;
            }
            else if (cmd == "-sub")
            {
                cmd = *++argv;
                --argc;
                open_ifile(ifile, cmd);
                cout << "\n Matrix 1: " << cmd << endl;
                ifile >> mtx1;
                cout << mtx1;

                //Getting row and column to be removed and assigning that value to integer variables
                cmd = *++argv;
                --argc;
                int i = stoi(cmd);
                cmd = *++argv;
                --argc;
                int j = stoi(cmd);

                cout << "\nSUB-MATRIX (A(i; j)) removing row " << i << " and column " << j <<  ":\n";
                mtx_result = mtx1.sub_mat(i, j);
                 cout << mtx_result;
            }
            else if (cmd == "-det")
            {
                double det;
                cmd = *++argv;
                --argc;
                open_ifile(ifile, cmd);
                cout << "\n Matrix 1: " << cmd << endl;
                ifile >> mtx1;
                cout << mtx1;

                det = mtx1.det();

                cout << "\nDETERMINANT of the matrix is (det(A)):" << det << endl;
            }
            else if (cmd == "-adj")
            {
                cmd = *++argv;
                --argc;
                open_ifile(ifile, cmd);
                cout << "\n Matrix 1: " << cmd << endl;
                ifile >> mtx1;
                cout << mtx1;

                cout << "\nADJOINT of the matrix is (adj(A)):\n";
                mtx_result = mtx1.adj();
                cout << mtx_result;

            }
            else if (cmd == "-1")
            {
                cmd = *++argv;
                --argc;
                open_ifile(ifile, cmd);
                cout << "\n Matrix 1: " << cmd << endl;
                ifile >> mtx1;
                cout << mtx1;
                Matrix_ops zero_one_matrix;

                cout << "\nINVERSE of the matrix is A^-1:\n";
                mtx_result = mtx1.inv();
                cout << mtx_result;

                cout << "\nMatrix 1 * Matrix A^-1:\n";
                zero_one_matrix =mtx1 * mtx_result;
                cout << zero_one_matrix;
            }

            else
                cout << "\nERROR/IMPOSSIBLE ACTION: Command not found" << endl;
        }

        //If first is a uppercase letter (name of a file)
        else if(isupper(cmd[0]))
        {
            //Reading and closing the first input file
            open_ifile(ifile, cmd);
            ifile >> mtx1;
            ifile.close();
            cmd = *++argv;
            --argc;

            //Selecting Operation
            if (cmd == "+")
            {
                cmd = *++argv;
                --argc;

                open_ifile(ifile, cmd);
                ifile >> mtx2;

                cout << " Matrix 1:\n"<< mtx1 << "\n Matrix 2:\n" << mtx2;
                cout << "\nADDITION of both matrices above:\n";
                mtx_result = mtx1 + mtx2;
                cout << mtx_result;
            }
            else if (cmd == "-")
            {
                cmd = *++argv;
                --argc;

                open_ifile(ifile, cmd);
                ifile >> mtx2;

                cout << " Matrix 1:\n"<< mtx1 << "\n Matrix 2:\n" << mtx2;
                cout << "\nSUBTRACTING of both matrices above:\n";
                mtx_result.operator=(mtx1 - mtx2);
                cout << mtx_result;
            }
            else if (cmd == "x" || cmd == "X")
            {
                cmd = *++argv;
                --argc;

                if (isdigit(cmd[0]))
                {
                    cout << " Matrix 1:\n" << mtx1;
                    cout << "\nMULTIPLYING matrix by SCALAR: " << cmd << endl;

                    int x = stoi(cmd);
                    mtx_result = mtx1 * x;
                    cout << mtx_result;
                }
                else
                {
                    open_ifile(ifile, cmd);
                    ifile >> mtx2;

                    cout << " Matrix 1:\n" << mtx1 << "\n Matrix 2:\n" << mtx2;
                    cout << "\nMULTIPLYING of both matrices above:\n";
                    mtx_result = mtx1 * mtx2;
                    cout << mtx_result;
                }
            }
            else if (cmd == "/")
            {
                cmd = *++argv;
                --argc;

                cout << " Matrix 1:\n" << mtx1;
                cout << "\nDIVIDING matrix by SCALAR: " << cmd << endl;

                int x = stoi(cmd);
                mtx_result = mtx1 / x;
                cout << mtx_result;
            }
            else
                cout << "\nERROR/IMPOSSIBLE ACTION: Operator not found. (Try: + - x / )." << endl;

        }

        //If not a dash nor letter, it is not a correct command line argument
        else
        {
            cout << "\nERROR/IMPOSSIBLE ACTION: Incorrect argument format." << endl;
            break;
        }
    }

    ofile.close();
    ifile.close();

    cout << endl;
    cout << "Programmed by: " << PROGRAMMER_NAME << " -- ";
    cout << __DATE__ << "  " __TIME__ << endl;
    cout << endl;

    return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          arg_count(int)
DESCRIPTION:       Verifies that there are enough arguments to proceed.
RETURNS:           Nothing
NOTES:             Throws exception if error is found.
------------------------------------------------------------------------------- */
void arg_count(int ar_num)
{
    if (ar_num < 2) //Minimum arguments -3
        throw "\nERROR/IMPOSSIBLE ACTION: Not enough arguments\n";
}

/* -----------------------------------------------------------------------------
FUNCTION:          arg_count(int)
DESCRIPTION:       Verifies that there are enough arguments to proceed.
RETURNS:           Nothing
NOTES:             Throws exception if error is found.
------------------------------------------------------------------------------- */
void open_ifile(ifstream &file, string &fname)
{
    fname += ".mtx";
    file.open(fname);
    file.seekg(0L, ios::beg);

    if (!file)
    {
        cout << "ERROR/IMPOSSIBLE ACTION: Not able to open the input file\n";
        exit(7);
    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          arg_count(int)
DESCRIPTION:       Verifies that there are enough arguments to proceed.
RETURNS:           Nothing
NOTES:             Throws exception if error is found.
------------------------------------------------------------------------------- */
void open_ofile(ofstream &file, string &fname)
{
    fname += ".mtx";
    file.open(fname);
    file.seekp(0L, ios::beg);

    if (!file)
    {
        cout << "ERROR/IMPOSSIBLE ACTION: Not able to open the output file\n";
        exit(7);
    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          display_help()
DESCRIPTION:       Displays a screen specifying how to use the program
RETURNS:           Nothing
------------------------------------------------------------------------------- */
void display_help()
{
    cout << "\n------------------------------------------------------------------------------------------\n";
    cout << "\t\t\tmatrix_math -> Program Instructions\n";
    cout << "------------------------------------------------------------------------------------------\n\n";

    cout << "This program runs with command line arguments.\n";
    cout << "Every A or B represents a .mtx file containing a matrix of the format:\n";
    cout << "\n\trows X cols" << "\n\tElements ...";
    cout << "\n\nAll file names must start with a capital letter\n";
    cout << "In you Linux Terminal, type ./matrix_math plus any of the following commands:\n\n";

    cout << "\t-h\t\t" << "Displays the help menu\n\n";
    cout << "\t-inp A\t\t" << "Read in the A.mtx file and display it to the screen.\n\n";
    cout << "\t... -out A\t" << "Write out data to named output file, (e.g., C.mtx).\n"
                                "\t\t\t(Used in conjunction with other commands.)\n\n";
    cout << "\t-eq A B\t\t" << "Read 2 .mtx files and test for equality (A == B)\n\n";

    cout << "\tA + B\t\t" << "Read and add 2 matrix files and display result. (A + B)\n\n";
    cout << "\tA - B\t\t" << "Read and subtract 2 matrix files and display result. (A - B)\n\n";
    cout << "\tA x B\t\t" << "Read and multiply 2 matrix files and display result. (A x B)\n";
    cout << "\tA x n\t\t" << "Read matrix file, multiply by n and display result. (A × n)\n";

    cout << "\tA / n\t\t" << "Read matrix file, divide by n and display result.(A / n)\n\n";
    cout << "\t-T A\t\t" << "Do the transpose of matrix. (A^T)\n\n";
    cout << "\t-1 A\t\t" << "Do the inverse of a matrix. (A−1)\n\n";
    cout << "\t-sub A i j\t\t" << "Get the submatrix of a matrix. (A(i; j))\n\n";
    cout << "\t-1 A\t\t" << "Do the inverse of a matrix. (A−1)\n\n";
    cout << "\t-adj A\t\t" << "Do the adjoint of a matrix. (adj(A))\n\n";
    cout << "\t-det A\t\t" << "Calculate determinant of a matrix. (det(A))\n\n";

    cout << "\nIf you have further questions, email jefferson_phillipsre@mail.tmcc.edu\n";
}
