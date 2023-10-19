/*
STUDENT 1: Javier Carballal Morgade       LOGIN 1: javier.carballal.morgade@udc.es
STUDENT 2: Diego Martínez Novoa           LOGIN 2: diego.martinez6@udc.es
STUDENT 3: Ana Barrera Novas              LOGIN 3: ana.barrera@udc.es
GROUP: 6.1
DATE: 21/10/23
*/

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

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

void copyArray(int source[], int dest[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}


void test() {
    int size = 20;
    int v[size], w[size];
    printf("\n===============================\n");
    printf("\n\nCheck algorithms:\n");

    printf("\n\nRandom initialization:\n");
    random_init(v, size);
    copyArray(v, w, size);
    print_array(v, size);
    printf("\nIs sorted? %d\n", is_sorted(v, size));

    printf("\nInsertion sort\n");
    InsertionSort(v, size);
    print_array(v, size);
    printf("\nIs sorted? %d\n", is_sorted(v, size));

    printf("\nShell sort\n");
    ShellSort(w, size);
    print_array(w, size);
    printf("\nIs sorted? %d\n", is_sorted(w, size));
}


void calculateTime(double *totalTime, int testArray[], int size, void (*sortingAlg)(int v[], int n)){
    double t1, t2, difference;

    t1 = microseconds(); //start measure
    sortingAlg(testArray, size);
    t2 = microseconds(); //stop measure
    
    difference = t2 - t1;;
    if(difference >= 500){ //big times
        *totalTime += difference; //sumar al totalTime1
    }
    else{ //small times
        t1 = microseconds(); //start measure
        for(int k = 0; k < 1000; k++){ //repeat 1000 times
            sortingAlg(testArray, size);
        }
        t2 = microseconds(); //stop measure
        *totalTime += (t2 - t1) / 1000;
    }
}


void execTimes(int rep) {
    int sizes[7] = {500, 1000, 2000, 4000, 8000, 16000, 32000};
    printf("\n\nExecution times in microseconds\nRepetitions: %d\n", rep);

    double totalTime;
    int a, i, j;

    for(a = 0; a < 6; a++){
        double meandivdiff = 0;
        
        if(a % 2 == 0){
            printf("\nINSERTION SORT:\n");
            printf("%6s%16s%20s%15s%15s\n", "Size", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
        }else{
            printf("\nSHELL SORT:\n");
            printf("%6s%16s%20s%15s%15s\n", "Size", "t(n)", "t(n)/n^0.8", "t(n)/n", "t(n)/n^1.2");
        }
        
        for (i=0; i<7; i++) { //iterate through the different sizes
            
            int testArray[sizes[i]];
            totalTime = 0;

            for(j = 0; j < rep; j++){ //make the given repetitions
                
                random_init(testArray, sizes[i]);
                
                if(a % 2 == 0){
                    calculateTime(&totalTime, testArray, sizes[i], InsertionSort);
                }
                else{
                    calculateTime(&totalTime, testArray, sizes[i], ShellSort);
                }
            }
            totalTime = totalTime/rep;


            if(a % 2 == 0){
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


int main() {
    init_seed();
    test();
    execTimes(20);
    return 0;
}
