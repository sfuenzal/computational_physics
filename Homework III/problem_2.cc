#include <iostream>
#include <math.h>
#include <iomanip>  

using namespace std;

class trigonometrics_functions
{
    public:
        double x;
        trigonometrics_functions () {}
        trigonometrics_functions (float a) : x(a) {}
        trigonometrics_functions (double argument) : x(argument) {}
        trigonometrics_functions operator * (const trigonometrics_functions& component); //sin(x)
        trigonometrics_functions operator + (const trigonometrics_functions& component); //cos(x)
        trigonometrics_functions operator < (const trigonometrics_functions& component); //tan(x)
        trigonometrics_functions operator - (const trigonometrics_functions& component); //sec(x)
        trigonometrics_functions operator > (const trigonometrics_functions& component); //csc(x)        
};

trigonometrics_functions trigonometrics_functions::operator* (const trigonometrics_functions& component)
{
    trigonometrics_functions sin_trigonometrics;
    sin_trigonometrics.x = component.x - pow(component.x, 3)/6;
    return sin_trigonometrics;
}

trigonometrics_functions trigonometrics_functions::operator+ (const trigonometrics_functions& component)
{
    trigonometrics_functions cos_trigonometrics;
    cos_trigonometrics.x = 1 - pow(component.x, 2)/2;
    return cos_trigonometrics;
}

trigonometrics_functions trigonometrics_functions::operator< (const trigonometrics_functions& component)
{
    trigonometrics_functions tan_trigonometrics;
    tan_trigonometrics.x = component.x + pow(component.x, 3)/3;
    return tan_trigonometrics;
}

trigonometrics_functions trigonometrics_functions::operator- (const trigonometrics_functions& component)
{
    trigonometrics_functions sec_trigonometrics;
    sec_trigonometrics.x = 1 + pow(component.x, 2)/2;
    return sec_trigonometrics;
}

trigonometrics_functions trigonometrics_functions::operator> (const trigonometrics_functions& component)
{
    trigonometrics_functions csc_trigonometrics;
    csc_trigonometrics.x = 1/component.x + component.x/6 + 7*pow(component.x, 3)/360;
    return csc_trigonometrics;
}

int main()
{
    double number;
    cout << "Please enter a real number (near to zero) to evaluate some trigonometrics functions: " << endl;
    cin >> number;

    trigonometrics_functions v1 (number);

    trigonometrics_functions sin_function;
    trigonometrics_functions cos_function;
    trigonometrics_functions tan_function;
    trigonometrics_functions sec_function;
    trigonometrics_functions csc_function;

    sin_function = v1 * v1;
    cos_function = v1 + v1;
    tan_function = v1 < v1;
    sec_function = v1 - v1;
    csc_function = v1 > v1;

    cout << "x = " << number << endl;
    cout << "sin(x) = " << setprecision(2) << sin_function.x << endl;
    cout << "cos(x) = " << setprecision(2) << cos_function.x << endl;
    cout << "tan(x) = " << setprecision(2) << tan_function.x << endl;
    cout << "sec(x) = " << setprecision(2) << sec_function.x << endl;
    cout << "cosec(x) = " << setprecision(2) << csc_function.x << endl;
    
    return 0;
}