#include <stdlib.h>
#include <time.h>
// The function randperm randomly permutes the first N elements
// of an array r
// code from @melrobin

int randperm(int *r,int N)
{
    int i,j;
    int temp;
    srand(time(0));

    for (i = N-1; i >= 0; --i){
    
            //generate a random number [0, n-1]
            j = rand() % (i+1);
                                                               
            //swap the last element with element at random index
                                                                                
            temp = r[i];
            r[i] = r[j];
            r[j] = temp;
        }
}
