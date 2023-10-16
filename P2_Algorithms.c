/*
STUDENT 1: Javier Carballal Morgade       LOGIN 1: javier.carballal.morgade@udc.es
STUDENT 2: Diego Martínez Novoa           LOGIN 2: diego.martinez6@udc.es
STUDENT 3: Ana Barrera Novas              LOGIN 3: ana.barrera@udc.es
GROUP: 6.1
DATE: 30/09/23
*/

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

//PRUEBA

void InsertionSort (int v[], int n){
    int i, x, j;
    for (i=1;i<n;i++){
        x=v[i];
        j=i-1;
        while (j>=0 && v[j]>x){
            v[j+1] = v[j];
            j=j-1;
        }
        v [j+1] = x;
    }
}

void ShellSort (int v[], int n){
    int increment=n, i, tmp, j;
    bool keepgoing;
    while (increment!=1){
        increment = increment/2;
        for (i=increment; i<n;i++){
            tmp = v[i];
            j=i;
            keepgoing=true;
            while (j-increment >=0 && keepgoing){
                if (tmp < v[j-increment]){
                    v[j] = v[j-increment];
                    j = j-increment;
                }else keepgoing = false;
            }
            v[j]=tmp;
        }
    }
}


void print_array(int v[], int n){
    int i;
    for (i=0; i<n; i++){
        printf("%3d ", v[i]);
    }
}

bool is_sorted (int v[], int n){
    int i;
    for (i=0; i<n-1;i++){
        if (v[i]>v[i+1]) return false;
    }
    return true;
}


void init_seed() {
    srand(time(NULL));
/* set the seed of a new sequence of pseudo-random integers */
}

void random_init(int v [], int n) {
    int i, m=2*n+1;
    for (i=0; i < n; i++)
    v[i] = (rand() % m) - n;
    /* generate pseudo-random numbers between -n and +n */
}

double microseconds() { /* obtains the system time in microseconds */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
    return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}


void test() {
    int a, b, size = 20;
    int v[size];
    printf("\n\nCheck algorithms:\n");
    for (int i=0; i<2; i++) {
        random_init(v, size);
        printf("\n\nRandom initialization:\n");
        print_array(v, size);
        printf("\nIs sorted? %d\n", is_sorted(v, size));
        if(i == 0){
            InsertionSort(v, size);
            printf("\nInsertion sort\n");
        }
        else{
            ShellSort(v, size);
            printf("\nShell sort\n");
        }
        print_array(v, size);
        printf("\nIs sorted? %d\n", is_sorted(v, size));
    }
}



//P1
/*
void test3(int rep) {
    int sizes[7] = {500, 1000, 2000, 4000, 8000, 16000, 32000};
    printf("\n\ntest 3 (execution times in microseconds)\nRepetitions: %d\n", rep);

    double totalTime;
    double testTimeA;
    double testTimeB;
    int a, i, j, k;

    for(a = 0; a < 2; a++){
        double meandivdiff = 0;
        
        printf("\nALGORITHM %d:\n\n", a+1);
        if(a == 0){
            printf("%6s%16s%20s%15s%15s\n", "Size", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
        }else{
            printf("%6s%16s%20s%15s%15s\n", "Size", "t(n)", "t(n)/n^0.8", "t(n)/n", "t(n)/n^1.2");
        }
        
        for (i=0; i<7; i++) { //iterate through the different sizes
            
            int testArray[sizes[i]];
            totalTime = 0;

            for(j = 0; j < rep; j++){ //make the given repetitions
                random_init(testArray, sizes[i]);
                
                if(a == 0){ //take first measure
                    testTimeA = microseconds(); //start measure
                    maxSubSum1(testArray, sizes[i]);
                    testTimeB = microseconds(); //stop measure
                }else{
                    testTimeA = microseconds(); //start measure
                    maxSubSum2(testArray, sizes[i]);
                    testTimeB = microseconds(); //stop measure
                }
                
                if(testTimeB - testTimeA >= 500){ //big times
                    totalTime += testTimeB - testTimeA; //sumar al totalTime1
                }
                else{ //small times
                    if(a == 0){
                        testTimeA = microseconds(); //start measure
                        for(k = 0; k < 1000; k++){ //repeat 1000 times
                            maxSubSum1(testArray, sizes[i]);
                        }
                        testTimeB = microseconds(); //stop measure
                    }else{
                        testTimeA = microseconds(); //start measure
                        for(k = 0; k < 1000; k++){ //repeat 1000 times
                            maxSubSum2(testArray, sizes[i]);
                        }
                        testTimeB = microseconds(); //stop measure
                    }
                    totalTime += (testTimeB - testTimeA) / 1000;
                }
            }
            totalTime = totalTime/rep;
            if(a == 0){
                printf("  %-5d%15.3lf%20.6lf%15.6lf%15.6lf\n", sizes[i], totalTime, totalTime/(pow(sizes[i],1.8)), totalTime/(pow(sizes[i],2)), totalTime/(pow(sizes[i],2.2)));
                meandivdiff += totalTime/(pow(sizes[i],2));
            }else{
                printf("  %-5d%15.3lf%20.6lf%15.6lf%15.6lf\n", sizes[i], totalTime, totalTime/(pow(sizes[i],0.8)), totalTime/sizes[i], totalTime/(pow(sizes[i],1.2)));
                meandivdiff += totalTime/sizes[i];
            }
        }
        printf("%57.6lf\n", meandivdiff/7);
    }
}
*/

int main() {
    init_seed();
    test();
    return 0;
}
