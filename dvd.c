// Arup Guha
// 7/22/2015
// Solution to COP 3223 Lab: Common DVDs.

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char title[100];
    int runTime;
    int idtag;
    double salePrice;
} DVD;

double getProfit(DVD* list1, int len1, DVD* list2, int len2) ;
double max(double a, double b);
DVD* get(FILE* ifp, int len);

int main() {

    FILE* ifp = fopen("dvd_test.txt", "r");
    int numCases, loop;
    fscanf(ifp, "%d", &numCases);

    // Go through each case.
    for (loop=0; loop<numCases; loop++) {

        // Read in movies.
        int len1,len2;
        fscanf(ifp, "%d", &len1);
        DVD* myMovies = get(ifp, len1);
        fscanf(ifp, "%d", &len2);
        DVD* yourMovies = get(ifp, len2);

        // Output sale price of all common movies.
        printf("%.2f\n", getProfit(myMovies, len1, yourMovies, len2));

        // Bookkeeping...
        free(myMovies);
        free(yourMovies);
    }

    fclose(ifp);
    return 0;
}

// Pre-condition: list1 is an array of length len1, list2 is an array
//                of length len2. No title appears in either list more
//                than once.
// Post-condition: Returns the sum of the sale prices of the common
//                 DVDs in both lists. Two DVDs are considered the
//                 same if their titles are identical.
double getProfit(DVD* list1, int len1, DVD* list2, int len2) {

    int i,j;
    double res = 0;

    // Go through each DVD in your collection.
    for (i=0; i<len1; i++) {

        // Look for this title in the other collection.
        for (j=0; j<len2; j++) {
            if (strcmp(list1[i].title, list2[j].title) == 0) {
                res += max(list1[i].salePrice, list2[j].salePrice);
                break;
            }
        }
    }

    // Here's what we made!
    return res;
}

// Returns the larger of a and b.
double max(double a, double b) {
    if (a > b) return a;
    return b;
}

// Reads in len DVDs from ifp and returns those store in a dynamically allocated array.
DVD* get(FILE* ifp, int len) {
    DVD* res = malloc(sizeof(DVD)*len);
    int i;
    for (i=0; i<len; i++)
        fscanf(ifp, "%s%d%d%lf", res[i].title, &(res[i].runTime), &(res[i].idtag), &(res[i].salePrice));
    return res;
}
