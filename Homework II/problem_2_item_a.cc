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

void imput_matrix_1(int** A, int n)
{
    cout << "Please insert the elements of the first matrix: " << endl;
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
            cout << endl;
        }
    }
}

void imput_matrix_2(int** A, int n)
{
    cout << "Please insert the elements of the second matrix: " << endl;
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
            cout << endl;
        }
    }
}

void show_matrices(int** A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << A[i][j] << endl;
        }
    }
}

int** add_matrices (int** A, int** B, int n)
{
    int** C = initializeMatrix(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

int** substract_matrices (int** A, int** B, int n)
{
    int** C = initializeMatrix(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

int** strassen_multiplication_matrix (int** A, int** B, int n)
{
    if (n == 1)
    {
        int** C = initializeMatrix(1);
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int** C = initializeMatrix(n);
    int m = n/2;
    
    int** A11 = initializeMatrix(m);
    int** A12 = initializeMatrix(m);
    int** A21 = initializeMatrix(m);
    int** A22 = initializeMatrix(m);

    int** B11 = initializeMatrix(m);
    int** B12 = initializeMatrix(m);
    int** B21 = initializeMatrix(m);
    int** B22 = initializeMatrix(m);


    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+m];
            A21[i][j] = A[i+m][j];
            A22[i][j] = A[i+m][j+m];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+m];
            B21[i][j] = B[i+m][j];
            B22[i][j] = B[i+m][j+m];
        }
    }

    int** S1 = substract_matrices(B12, B22, m);
    int** S2 = add_matrices(A11, A12, m);
    int** S3 = add_matrices(A21, A22, m);
    int** S4 = substract_matrices(B21, B11, m);
    int** S5 = add_matrices(A11, A22, m);
    int** S6 = add_matrices(B11, B22 , m);
    int** S7 = substract_matrices(A12, A22, m);
    int** S8 = add_matrices(B21, B22, m);
    int** S9 = substract_matrices(A11, A21, m);
    int** S10 = add_matrices(B11, B12, m);

    int** P1 = strassen_multiplication_matrix(A11, S1, m);
    int** P2 = strassen_multiplication_matrix(S2, B22, m);
    int** P3 = strassen_multiplication_matrix(S3, B11, m);
    int** P4 = strassen_multiplication_matrix(A22, S4, m);
    int** P5 = strassen_multiplication_matrix(S5, S6, m);
    int** P6 = strassen_multiplication_matrix(S7, S8, m);
    int** P7 = strassen_multiplication_matrix(S9, S10, m);

    int** C11 = add_matrices(add_matrices(P5, P6, m), substract_matrices(P4, P2, m), m);
    int** C12 = add_matrices(P1, P2, m);
    int** C21 = add_matrices(P3, P4, m);
    int** C22 = add_matrices(substract_matrices(P5, P7, m), substract_matrices(P1, P3, m), m);
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j+m] = C12[i][j];
            C[i+m][j] = C21[i][j];
            C[i+m][j+m] = C22[i][j];
        }
    }
    return C;
}

int main()
{
    ofstream times_file;

    cout << "Please enter the dimension of the matrices: " << endl;
    int n;
    cin >> n;

    int** A = initializeMatrix(n); 
    int** B = initializeMatrix(n);
    
    imput_matrix_1(A, n);
    show_matrices(A, n);

    imput_matrix_2(B, n);
    show_matrices(B, n);
    
    int** C = initializeMatrix(n);
    C = strassen_multiplication_matrix(A, B, n);
    cout << "Multiplication of the matrices :" << endl;
    show_matrices(C, n);

}

