

#include <stdio.h>


void TowerOfHanoi(int n, char from_rod, char to_rod, char aux_rod);

int main()
{
    int n = 3;
  
    /*A, B and C are names of rods*/
    TowerOfHanoi(n, 'A', 'C', 'B');
    return (0); 
}

void TowerOfHanoi(int n, char from_rod, char to_rod, char aux_rod)
{
    if (n == 0)
    {
        return;
    }

    TowerOfHanoi((n - 1), from_rod, aux_rod, to_rod);
    printf("Moving disk %d from rod %c to rod %c\n", n, from_rod, to_rod);
    TowerOfHanoi((n - 1), aux_rod, to_rod, from_rod);
}