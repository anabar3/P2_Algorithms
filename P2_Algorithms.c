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

void sorted_init(int v[], int n){
    random_init(v, n);
    InsertionSort(v, n);
}

void inverse_init(int v[], int n){
    sorted_init(v, n);
    int i, j, temp;
    for (i = 0, j = n-1; i < j; i++, j--) {
        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
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


double calculateTime(int testArray[], int size, void (*sortingAlg)(int v[], int n)){
    double t1, t2, difference;
    int copyofTest[size];
    copyArray(testArray, copyofTest, size);

    t1 = microseconds(); //start measure
    sortingAlg(testArray, size);
    t2 = microseconds(); //stop measure
    
    difference = t2 - t1;;
    if(difference >= 500){ //big times
        return difference;
    }
    else{ //small times
        double copyTime;
        int k;

        //measure copy time
        t1 = microseconds();
        for(k = 0; k < 1000; k++){ //repeat 1000 times
            copyArray(copyofTest, testArray, size);
        }
        t2 = microseconds();
        copyTime = t2 - t1;

        //measure sorting and substracting copy time
        t1 = microseconds(); //start measure
        for(k = 0; k < 1000; k++){ //repeat 1000 times
            copyArray(copyofTest, testArray, size);
            sortingAlg(testArray, size);
        }
        t2 = microseconds(); //stop measure

        return (t2-t1-copyTime)/1000;
    }
}

void print_header(int a){
    switch(a){
        case 0:
            printf("\nINSERTION SORT (Random arrays):\n");
            printf("%8s%16s%20s%15s%15s\n", "Size", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
        break;
        case 1:
            printf("\nSHELL SORT (Random arrays):\n");
            printf("%8s%16s%21s%18s%11s\n", "Size", "t(n)", "t(n)/n*log(n)", "t(n)/n*log^2(n)", "t(n)/n^2");
        break;
        case 2:
            printf("\nINSERTION SORT (Ascending order arrays):\n");
            printf("%8s%16s%20s%15s%15s\n", "Size", "t(n)", "t(n)/n^0.8", "t(n)/n", "t(n)/n^1.2");
        break;
        case 3:
            printf("\nSHELL SORT (Ascending order arrays):\n");
            printf("%8s%16s%20s%17s%13s\n", "Size", "t(n)", "t(n)/n", "t(n)/n*log(n)", "t(n)/n^2");
        break;
        case 4:
            printf("\nINSERTION SORT (Descending order arrays):\n");
            printf("%8s%16s%20s%15s%15s\n", "Size", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
        break;
        case 5:
            printf("\nSHELL SORT (Descending order arrays):\n");
            printf("%8s%16s%20s%17s%13s\n", "Size", "t(n)", "t(n)/n*log(n)", "t(n)/n*log^2(n)", "t(n)/n^2");
        break;
    }
}

void print_row(int a, double totalTime, int n, double *meandivdiff){
    char asterisk;
    if(totalTime >= 500){
        asterisk = ' ';
    }
    else{
        asterisk = '*';
    }
    
    if(a == 0 || a == 4){
        //n^2
        printf("%c   %-5d%15.3lf%20.6lf%15.6lf%15.6lf\n", asterisk, n, totalTime, totalTime/(pow(n,1.8)), totalTime/(pow(n,2)), totalTime/(pow(n,2.2)));
        *meandivdiff += totalTime/(pow(n,2));
    }else if(a == 3){
        //nlog(n)
        printf("%c   %-5d%15.3lf%20.6lf%15.6lf%15.6lf\n", asterisk, n, totalTime, totalTime/n, totalTime/(n*log(n)), totalTime/(pow(n,2)));
        *meandivdiff += totalTime/(n*log(n));
    }else if(a == 1 || a == 5){
        //n log²n
        printf("%c   %-5d%15.3lf%20.6lf%15.6lf%15.6lf\n", asterisk, n, totalTime, totalTime/n*log(n), totalTime/(n*pow(log(n),2)), totalTime/pow(n,2));
        *meandivdiff += totalTime/(n*pow(log(n),2));
    }
    else{
        //n
        printf("%c   %-5d%15.3lf%20.6lf%15.6lf%15.6lf\n", asterisk, n, totalTime, totalTime/(pow(n,0.8)), totalTime/n, totalTime/(pow(n,1.2)));
        *meandivdiff += totalTime/n;
    }
}


void execTimes(int rep) {
    int sizes[7] = {500, 1000, 2000, 4000, 8000, 16000, 32000};
    printf("\n\nExecution times in microseconds\nRepetitions: %d\n", rep);

    double totalTime, meandivdiff;
    int a, i, j, n;
    char asterisk;

    //6 DIFFERENT TABLES
    for(a = 0; a < 6; a++){
        meandivdiff = 0;
        
        //PRINT HEADER
        print_header(a);
            
        //MAKE MEASUREMENTS
        for (i=0; i<7; i++) { //iterate through the different sizes
            n = sizes[i];
            int testArray[n];
            totalTime = 0;

            for(j = 0; j < rep; j++){ //make the given repetitions
                
                if(a < 2){
                    random_init(testArray, n);
                }
                else if(a < 4){
                    sorted_init(testArray, n);
                }
                else{
                    inverse_init(testArray, n);
                }
                
                if(a % 2 == 0){
                    totalTime += calculateTime(testArray, n, InsertionSort);
                }
                else{
                    totalTime += calculateTime(testArray, n, ShellSort);
                }
            }
            totalTime /= rep;

            //PRINT ROW
            print_row(a, totalTime, n, &meandivdiff);
        }
        //Print average
        printf("%59.6lf\n", meandivdiff/7);
    }
}


int main() {
    init_seed();
    test();
    execTimes(20);
    return 0;
}
