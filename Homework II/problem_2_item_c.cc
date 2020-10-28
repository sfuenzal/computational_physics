#include <iostream>

#include <bits/stdc++.h> 

using namespace std;

int** initializeMatrix(int n) 
{
    int** temp = new int*[n];
    for(int i=0; i<n; i++)
    {
        temp[i] = new int[n];
    }
    return temp;
}

void naive_multiplication(int** A, int** B, int n)
{
    int** C = initializeMatrix(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {   
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k]*B[k][j];              
            }  
            //cout << C[i][j] << endl;
        }
    }
}


int main()
{
    ofstream times_file_2;

    int n;
    cout << "Please enter the dimension of the matrices: " << endl;
    cin >> n;

    int** A = initializeMatrix(n);
    int** B = initializeMatrix(n);

    clock_t start, end; 

    /* Recording the starting clock tick.*/
    start = clock(); 

    naive_multiplication(A, B, n);
    
    // Recording the end clock tick. 
    end = clock(); 

    // Calculating total time taken by the program. 
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    times_file_2.open ("times_file_2.txt", ios::app | ios::ate);
    times_file_2 << "Time taken by program is : " << fixed  << time_taken << setprecision(10) << endl; 
    times_file_2.close(); 
}