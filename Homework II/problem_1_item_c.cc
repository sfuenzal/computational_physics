#include <iostream>

using namespace std;

void hanoi_towers (int n, char initial_rod, char final_rod, char backup_rod)
{
    if (n > 0)
    {
        hanoi_towers (n-1, initial_rod, backup_rod, final_rod);
        cout << "Move stack " << n << " from " << initial_rod << " to " << final_rod << endl;
        hanoi_towers (n-1, backup_rod, final_rod, initial_rod);
    }
}


int main()
{
   int number_of_stacks;
   cout << "Please insert the numbers of stacks to solve the Hanoi Towers puzzle" << endl;
   cin >> number_of_stacks;
   char first_rod = 'A', second_rod = 'B', third_rod = 'C';
   hanoi_towers (number_of_stacks, first_rod, second_rod, third_rod);
}