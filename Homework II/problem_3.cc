#include <iostream>
#include <bits/stdc++.h> 

using namespace std;

double square_root_1(double min, double max, double N)
{
    if (min <= max)
    {
        double mid = (min + max)/2;
    
    if ( (mid * mid <= N) and ( (mid + 1) * (mid + 1) > N ))
    
    {
        return mid;
    }

    else if (mid * mid < N)
    {
        return square_root_1(mid + 1, max, N);    
    }

    else
    {
        return square_root_1(min, mid -1, N);
    }
    }
    return min;
}

double square_root_2(double n)
{
    double x = n;
    double final = 0.0000001;

    while (x - n / x > final)
    {
        x = (x + n / x) / 2;
    }
    return x;
}

int main()
{
    double n;
    cout << "Please insert a number: " << endl;
    cin >> n;
    cout << fixed << setprecision(6) << "The square root of the number is (first method): " << square_root_1(0, n, n) << endl;
    cout << fixed << setprecision(6) << "The square root of the number is (Babylonian method): " << square_root_2(n) << endl;
}