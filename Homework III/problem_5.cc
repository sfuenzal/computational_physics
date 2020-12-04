#include <iostream>
#include <new>

using namespace std;

class polynomial
{
        float * pointer;
    public:
        polynomial() : pointer(new float) {}
        polynomial (const float& str) : pointer(new float(str)) {}
        ~polynomial () {delete pointer;}
        const float& content() const {return *pointer;}
};

int main()
{
    int n;
    cout << "Please enter the degree of the polinomial: " << endl;
    cin >> n;

    polynomial degree_polynomial(n);

    cout << "" << endl;

    cout << "Polynomial degree = " << degree_polynomial.content() << endl;

    cout << "" << endl;
    
    float * coefficients;

    coefficients = new (nothrow) float[n];

    cout << "Enter the coefficients of the polynomial (there should be n + 1 terms, where n is the degree of the polynomial): " << endl;
    
    for (int i = 0; i <= n; ++i)
    {
        cin >> coefficients[i];
    }

    cout << "" << endl;

    cout << "Polynomial coefficients: " << endl;

    for (int i = 0; i <= n; ++i)
    {
        polynomial coefficients_polynomial(coefficients[i]);
        cout << "x^" << i << ": " << coefficients_polynomial.content() << endl;
    }
    
    return 0;
}