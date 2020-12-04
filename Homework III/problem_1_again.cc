#include <iostream>

using namespace std;

class three_dimensional_vector
{
    public:
        float x, y, z, cte, dot;
        three_dimensional_vector () {}
        three_dimensional_vector (float a, float b, float c, float d) : x(a), y(b), z(c), cte(d) {}
        three_dimensional_vector operator * (const three_dimensional_vector& component); //Multiplication by a scalar
        three_dimensional_vector operator + (const three_dimensional_vector& component); //Addition of the two vectors
        three_dimensional_vector operator < (const three_dimensional_vector& component); //Dot product
        three_dimensional_vector operator - (const three_dimensional_vector& component); //Vector product        
};

three_dimensional_vector three_dimensional_vector::operator* (const three_dimensional_vector& component)
{
    three_dimensional_vector multiplication_by_scalar;
    multiplication_by_scalar.x = component.cte*component.x;
    multiplication_by_scalar.y = component.cte*component.y;
    multiplication_by_scalar.z = component.cte*component.z;
    return multiplication_by_scalar;
}

three_dimensional_vector three_dimensional_vector::operator+ (const three_dimensional_vector& component)
{
    three_dimensional_vector sum_components;
    sum_components.x = x + component.x;
    sum_components.y = y + component.y;
    sum_components.z = z + component.z;
    return sum_components;
}

three_dimensional_vector three_dimensional_vector::operator< (const three_dimensional_vector& component)
{
    three_dimensional_vector dot_product;
    dot_product.dot = x*component.x + y*component.y + z*component.z;
    return dot_product;
}

three_dimensional_vector three_dimensional_vector::operator- (const three_dimensional_vector& component)
{
    three_dimensional_vector vector_product;
    vector_product.x = y*component.z - z*component.y;
    vector_product.y = z*component.x - x*component.z;
    vector_product.z = x*component.y - y*component.x;
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
    dot_product_result = v1 < v2;
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