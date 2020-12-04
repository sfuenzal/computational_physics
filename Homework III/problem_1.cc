#include <iostream>

using namespace std;

class three_dimensional_vector
{
    public:
        float x, y, z, cte, dot;
        three_dimensional_vector () {}
        three_dimensional_vector (float a, float b, float c, float d) : x(a), y(b), z(c), cte(d) {}
};


three_dimensional_vector operator* (const three_dimensional_vector& lhs, const three_dimensional_vector& rhs)
{
    three_dimensional_vector multiplication_by_scalar;
    multiplication_by_scalar.x = lhs.cte*rhs.x;
    multiplication_by_scalar.y = lhs.cte*rhs.y;
    multiplication_by_scalar.z = lhs.cte*rhs.z;
    return multiplication_by_scalar;
}


three_dimensional_vector operator+ (const three_dimensional_vector& lhs, const three_dimensional_vector& rhs)
{
    three_dimensional_vector sum_components;
    sum_components.x = lhs.x + rhs.x;
    sum_components.y = lhs.y + rhs.y;
    sum_components.z = lhs.z + rhs.z;
    return sum_components;
}


three_dimensional_vector operator> (const three_dimensional_vector& lhs, const three_dimensional_vector& rhs)
{
    three_dimensional_vector dot_product;
    dot_product.dot = lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
    return dot_product;
}

three_dimensional_vector operator- (const three_dimensional_vector& lhs, const three_dimensional_vector& rhs)
{
    three_dimensional_vector vector_product;
    vector_product.x = lhs.y*rhs.z - lhs.z*rhs.y;
    vector_product.y = lhs.z*rhs.x - lhs.x*rhs.z;
    vector_product.z = lhs.x*rhs.y - lhs.y*rhs.x;
    return vector_product;
}

int main()
{
    
    float c;
    cout << "Please enter a constant: " << endl;
    cin >> c;

    float v1x, v1y, v1z, v2x, v2y, v2z;
    cout << "Please enter the components of the first vector: " << endl;
    cin >> v1x >> v1y >> v1z;
    cout << "Please enter the components of the second vector: " << endl;
    cin >> v2x >> v2y >> v2z;

    three_dimensional_vector v1 (v1x, v1y, v1z, c);
    three_dimensional_vector v2 (v2x, v2y, v2z, c);
    
    three_dimensional_vector multiplication_by_scalar_1;
    three_dimensional_vector multiplication_by_scalar_2;
    three_dimensional_vector sum_result;
    three_dimensional_vector dot_product_result;
    three_dimensional_vector vector_product_result;
    
    multiplication_by_scalar_1 = v1 * v1;
    multiplication_by_scalar_2 = v2 * v2;
    sum_result = v1 + v2;
    dot_product_result = v1 > v2;
    vector_product_result = v1 - v2;
    
    cout << "Basic three-dimensional vector algebra: " << endl;
    cout << "c = " << c << endl;
    cout << "v1 = " << "(" << v1x << ", " << v1y << ", " << v1z << ")" << endl;
    cout << "v2 = " << "(" << v2x << ", " << v2y << ", " << v2z << ")" << endl;
    cout << "c*v1 = " << "(" << multiplication_by_scalar_1.x << ", "  << multiplication_by_scalar_1.y << ", " << multiplication_by_scalar_1.z << ")" << endl;
    cout << "c*v2 = " << "(" << multiplication_by_scalar_2.x << ", "  << multiplication_by_scalar_2.y << ", " << multiplication_by_scalar_2.z << ")" << endl;
    cout << "v1 + v2 = " << "(" << sum_result.x << ", "  << sum_result.y << ", " << sum_result.z << ")" << endl;
    cout << "v1 * v2 = " << dot_product_result.dot << endl;
    cout << "v1 x v2 = " << "(" << vector_product_result.x << ", " << vector_product_result.y << ", " << vector_product_result.z << ")" << endl;
    
    return 0;
}