#include <iostream>
#include <math.h>
#include <iomanip> 

using namespace std;

class stretch_factor_1
{
        long double beta;
    public:
        stretch_factor_1 (long double);
        long double gamma_factor_1 () {return 1/sqrt(1 - pow(beta, 2));};
};

class stretch_factor_2
{
        long double epsilon;
    public:
        stretch_factor_2 (long double);
        long double gamma_factor_2 () {return 1/sqrt(2*epsilon - pow(epsilon, 2));};
};

class fractional_error
{
        long double epsilon, beta;
    public:
        fractional_error (long double, long double);
        long double error_factor () {return (1/sqrt(2*epsilon - pow(epsilon, 2)) - 1/sqrt(1 - pow(beta, 2)))/(1/sqrt(1 - pow(beta, 2)));};
};

stretch_factor_1::stretch_factor_1 (long double a1)
{
    beta = a1;
}

stretch_factor_2::stretch_factor_2 (long double a2)
{
    epsilon = a2;
}

fractional_error::fractional_error (long double x, long double y)
{
    epsilon = x;
    beta = y;
}

int main()
{
    int n;
    cout << "Please enter the number of times that you want to evaluate the relativistic stretch-factor: " << endl;
    cin >> n;

    float counter1 = 0, counter2 = 0;
    float array_beta[n], array_epsilon[n]; 
    
    for (int i = 0; i < n; ++i)
    {
        counter1 += 0.9*pow(10, -i);
        array_beta[i] = counter1;
    }

    for (int i = 0; i < n; ++i)
    {
        counter2 = 0.1*pow(10, -i);
        array_epsilon[i] = counter2;
    }

    for (int i = 0; i < n; ++i)
    {
        stretch_factor_1 object_stretch_factor_1 (array_beta[i]);
        cout  << "gamma(beta) = " << setprecision(10) <<  object_stretch_factor_1.gamma_factor_1() << endl;
    }

    cout << "" << endl;

    for (int i = 0; i < n; ++i)
    {
        stretch_factor_2 object_stretch_factor_2 (array_epsilon[i]);
        cout << "gamma(epsilon) = " << setprecision(10) << object_stretch_factor_2.gamma_factor_2() << endl;
    }

    cout << "" << endl;

    for (int i = 0; i < n; ++i)
    {
        stretch_factor_1 object_stretch_factor_1 (array_beta[i]);
        fractional_error object_error (array_epsilon[i], array_beta[i]);

        if (object_error.error_factor() <= pow(10, -3))
        {
            cout << "gamma(beta) = " << object_stretch_factor_1.gamma_factor_1() << ", " << "fractional error = " << object_error.error_factor() << endl;
        }
    }

    return 0;
}