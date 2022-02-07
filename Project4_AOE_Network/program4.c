#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

const int N = 20;
FILE *fp1 = NULL, *fp2 = NULL;
typedef struct activity {       //AOE(Activity on Edge)
    int start;                    //starting node
    int end;                      //ending node
    int value;                    //working time
    int early;                    //earliest time
    int late;                     //latest time
    int slack;                    //slack = late-early
} Activity;

typedef struct node {
    int early, late;
} Node;

int main(void) 
{
  // Initialize
    int arr[N][N];
    Activity list[N];
    Node node_list[N];
    int Node_count = 0, Activity_count = 0, i = 0, j = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            arr[i][j] = 0;
        }
        list[i].start = list[i].end = list[i].early = list[i].slack \
        = list[i].value = node_list[i].early =0;

        list[i].late = node_list[i].late = INT_MAX;
    }
    // Read the input file
    if (!(fp1 = fopen("input.txt", "r"))) {
        fprintf(stderr, "opening input.txt failed");
        exit(-1);
    }
    fscanf(fp1, "%d", &Activity_count);
    int p1, p2, p3;
    i = 0, j = 0;
    Node_count = -1;
    for (i = 0; i < Activity_count; i++) {  // Event1(start) Event2(end) Value
        fscanf(fp1, "%d%d%d",&p1, &p2, &p3);
        list[j].start = p1;
        list[j].end = p2;
        arr[p1][p2] = list[j].value = p3;
        j++;
        if (p1 > Node_count || p2 > Node_count) {
            Node_count = (p1 > p2)? p1: p2;
        }
    }
    Node_count++; // node number = max index of input node + 1
    fclose(fp1); fp1 = NULL;
    // calculate
    int curr = 0;
    // calculate the early time
    for (i = 0; i < Node_count; i++) {
        for (j = 0; j < Node_count; j++) {
            if (arr[i][j] != 0) {  //ES(j) = max { ES(j) , ES(i) + t(i,j)}
                if (node_list[j].early < node_list[i].early + list[curr].value) {
                    node_list[j].early = node_list[i].early + list[curr].value; 
                }
                list[curr++].early = node_list[i].early;        
            }
        }
    }
    // calculate the late time
    curr = Activity_count;
    node_list[Node_count - 1].late = node_list[Node_count - 1].early;
    for (i = Node_count - 1; i >= 0; i--) {
        for (j = Node_count - 1; j >= 0; j--) {
            if (arr[i][j] != 0) {
                curr--; //LS(j) = min { LS(j) , LS(i) - t(i, j)}
                if (node_list[i].late > node_list[j].late - arr[i][j]) {
                    node_list[i].late = node_list[j].late - arr[i][j];
                }
                list[curr].late = node_list[i].late;
            }
        }
    }
    for (i = 0; i < Activity_count; i++) 
        list[i].slack = list[i].late - list[i].early;
    bool isfeasible = true;
    for (i = 0; i < Activity_count && isfeasible; i++) { 
        if (list[i].slack < 0 || list[i].early < 0 || list[i].late < 0) {  //no solution if slack < 0
            isfeasible = false;
        }
        if (list[i].start != 0 && list[i].early == 0) { //no solution if start of event != 0 && early time of event == 0 
            isfeasible = false;
        }
    }
    // output the result
    if (!(fp2 = fopen("output.txt", "w"))) {
        fprintf(stderr, "writing output.txt failed");
        exit(-1);
    }
    if (!isfeasible) {
        fprintf(fp2, "No solution\n");
    } else {
        fprintf(fp2, "%d\n", Activity_count);
        for (i = 0; i < Activity_count; i++) {
            fprintf(fp2, "%d %d %d ", list[i].early, list[i].late, list[i].slack);
            if (list[i].slack == 0)
                fprintf(fp2, "y\n");
            else
                fprintf(fp2, "n\n");
        }
    }
    fclose(fp2); fp2 = NULL;
    return 0;
}
