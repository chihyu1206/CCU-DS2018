#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 100;

void init(int **&map, int r, int c, int *&a, int *&b, int p);
int myhash(char *str, int count, int r, int c, int p, int *a, int *b);
void insert(int **map, int r, int c, int p, char *str, int *a, int *b);
void query(int **map, int r, int c, int p, char *str, int *a, int *b);

int main(void) {
    FILE *rinfp = NULL, *wdfp = NULL;
    // open the input file to read the row, column, prime, and text. 
    if (!(rinfp = fopen("input.txt", "r"))) {
        fprintf(stderr, "reading input.txt failed\n");
        exit(-1);
    }
    // write the data file to store each word by line.
    if (!(wdfp = fopen("data.txt", "w"))) {
        fprintf(stderr, "writing data.txt failed\n");
        exit(-1);
    }
    int row = 0, column = 0, prime = 0, i = 0, j = 0, count = 0;
    fscanf(rinfp, "%d%d%d", &row, &column, &prime);// read the row, column, prime number.
    char buf[N];
    memset(buf, '\0', sizeof(buf));
    while (fscanf(rinfp, "%s", buf) != EOF) {
        for (i = 0; i < strlen(buf); i++) 
        buf[i] = (char)tolower(buf[i]);       //convert each alphabet to lower.
        if (!isalpha(buf[strlen(buf) - 1])) {  //if the last word is not an alphabet(such as comma), convert to '\0'
            buf[strlen(buf) - 1] = '\0';
        }
        fprintf(wdfp, "%s\n", buf);
        memset(buf, '\0', sizeof(buf));
    }
    fclose(rinfp); fclose(wdfp);
    rinfp = wdfp = NULL;
    int **map = NULL, *a = NULL, *b = NULL;
    init(map, row, column, a, b, prime);  //initialize each array
    FILE *rdfp = fopen("data.txt", "r");
    if (!rdfp) {
        fprintf(stderr, "reading data.txt failed\n");
        exit(-1);
    }
    memset(buf, '\0', sizeof(buf));
    while (fgets(buf, N, rdfp) != NULL) {
        buf[strlen(buf) - 1] = '\0';
        insert(map, row, column, prime, buf, a, b);  //insert hashed string number to map and update.
        memset(buf, '\0', sizeof(buf));
    } 
    fclose(rdfp); rdfp = NULL;

    while (fgets(buf, N, stdin) != NULL) {
        buf[strlen(buf) - 1] = '\0';
        query(map, row, column, prime, buf, a, b);
    }
    return 0;
}

void init(int **&map, int r, int c, int *&a, int *&b, int p) {
    map = new int *[r];  //dynamically allocate the map, a, b array by the given row and column value.
    int i = 0, j = 0;
    for (i = 0; i < r; i++)
        map[i] = new int [c];
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            map[i][j] = 0;
    a = new int[r];
    b = new int[r];
    srand((unsigned int)(time(NULL)));  //randomly choose the number from [1 , p - 1]
    for (i = 0; i < r; i++)
        a[i] = rand() % (p - 1) + 1;
    for (i = 0; i < r; i++)
        b[i] = rand() % (p - 1) + 1;
}

int myhash(char *str, int count, int r, int c, int p, int *a, int *b) {
    string key(str);
    hash<string> hasher;
    unsigned int ret = hasher(key);
    return (a[count] * ret + b[count]) % p % c;
}

void insert(int **map, int r, int c, int p, char *str, int *a, int *b) {
    int minIndex = 0, count = 0;
    int mini = map[count][myhash(str, count, r, c, p, a, b)];
    for (count = 0; count < r; count++) {
        //find minimum value
        if (map[count][myhash(str, count, r, c, p, a, b)] < mini) {  
            mini = min(mini, map[count][myhash(str, count, r, c, p, a, b)]);
        }
    }
    for (count = 0; count < r; count++)
        //increment each element which is equal to minimum value by 1.
        if (map[count][myhash(str, count, r, c, p, a, b)] == mini) 
            map[count][myhash(str, count, r, c, p, a, b)]++;
}

void query(int **map, int r, int c, int p, char *str, int *a, int *b) {
    int minIndex = 0, count = 0;
    int mini = map[count][myhash(str, count, r, c, p, a, b)];
    for (count = 0; count < r; count++)
        mini = min(mini, map[count][myhash(str, count, r, c, p, a, b)]);
    printf("%d\n", mini);  //print the minimum number.
}