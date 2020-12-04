#include <iostream>
#include <math.h>

using namespace std;

class two_times_two_matrix
{
    public:
        double a11, a12, a21, a22, cte, det;
        two_times_two_matrix () {a11 = 0; a12 = 0; a21 = 0; a22 = 0;}
        two_times_two_matrix (double a, double b, double c, double d, double e) : a11(a), a12(b), a21(c), a22(d), cte(e) {}
        two_times_two_matrix operator * (const two_times_two_matrix& component); //Determinant matrix
        two_times_two_matrix operator - (const two_times_two_matrix& component); //Inverse matrix
        two_times_two_matrix operator + (const two_times_two_matrix& component); //Multiplication of the matrix by a constant
};

two_times_two_matrix two_times_two_matrix::operator* (const two_times_two_matrix& component)
{
    two_times_two_matrix determinant;
    determinant.det = component.a11*component.a22 - component.a12*component.a21; 
    return determinant;
}

two_times_two_matrix two_times_two_matrix::operator- (const two_times_two_matrix& component)
{
    two_times_two_matrix inverse;
    inverse.a11 = pow(component.a11*component.a22 - component.a12*component.a21, -1)*component.a22;
    inverse.a12 = -pow(component.a11*component.a22 - component.a12*component.a21, -1)*component.a12;
    inverse.a21 = -pow(component.a11*component.a22 - component.a12*component.a21, -1)*component.a21;
    inverse.a22 = pow(component.a11*component.a22 - component.a12*component.a21, -1)*component.a11;
    return inverse;
}

two_times_two_matrix two_times_two_matrix::operator+ (const two_times_two_matrix& component)
{
    two_times_two_matrix multiplication_by_constant;
    multiplication_by_constant.a11 = component.cte*component.a11;
    multiplication_by_constant.a12 = component.cte*component.a12;
    multiplication_by_constant.a21 = component.cte*component.a21;
    multiplication_by_constant.a22 = component.cte*component.a22;
    return multiplication_by_constant;
}

int main()
{
    double a, b, c, d;
    cout << "Please enter the four entries of the 2x2 matrix (a11, a12, a21, a22): " << endl;
    cin >> a >> b >> c >> d;

    double constant;
    cout << "Please enter a constant: " << endl;
    cin >> constant;

    two_times_two_matrix M (a, b, c, d, constant);

    two_times_two_matrix determinant_result;
    two_times_two_matrix inverse_result;
    two_times_two_matrix multiplication_by_constant_result;

    determinant_result = M * M;
    inverse_result = M - M;
    multiplication_by_constant_result = M + M;

    cout << "det(M) = " << determinant_result.det << endl;
    
    if (determinant_result.det == 0)
    {
        cout << "There is no inverse." << endl;    
    }

    else
    {
        cout << "M^{-1} = " << "{" << "{" << inverse_result.a11 << ", " << inverse_result.a12 << "}" << ", " << "{" << inverse_result.a21 << ", " << inverse_result.a22 << "}" << "}" << endl;
    }

    cout << "c*M = " << "{" << "{" << multiplication_by_constant_result.a11 << ", " << multiplication_by_constant_result.a12 << "}" << ", " << "{"  << multiplication_by_constant_result.a21 << ", " << multiplication_by_constant_result.a22 << "}" << "}" << endl;

    return 0;    

}
