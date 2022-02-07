#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

const float FLT_MAX = 0xffffffff;

typedef struct node_struct {
    int nodeindex;
    float xaxis, yaxis;
} Node;

typedef struct link_struct {
  int index, first, second;
  float distance;
  struct link_struct *next;
} Link;

int main()
{
    int nodenumber = 0, i = 0, j = 0;
    FILE *fp1 = NULL, *fp2 = NULL;
    fp1 = fopen("5node.txt", "r");
    fscanf(fp1, "%d", &nodenumber);
    Node node[nodenumber];
    for (i = 0; i < nodenumber; i++)
      fscanf(fp1, "%d%f%f", &node[i].nodeindex, &node[i].xaxis, &node[i].yaxis);
    int linkcount = 0;
    Link *head = NULL, *pre = NULL;
    float dis = 0.0;
    for (i = 0; i < nodenumber - 1; i++) {
        for (j = i + 1; j < nodenumber; j++) {
            if ((dis = hypotf(node[i].xaxis - node[j].xaxis, node[i].yaxis - 
            node[j].yaxis)) <= 1.0) {
                head = (Link *)malloc(sizeof(Link));
                head->index = linkcount;
                head->first = i; head->second = j;
                head->distance = dis;
                head->next = pre;
                pre = head;
                linkcount++;
            } else {
                continue;
            }
        }
  }
    fp2 = fopen("link.txt", "w");
    fprintf(fp2, "%d\n", linkcount);
    // reverse the linked list to output the required format
    Link *previous = NULL, *current = head, *preceding = head->next;  
    while (preceding != NULL) {
        current->next = previous;      // reverse current->next
        previous = current;            // push back previous
        current = preceding;           // push back current
        preceding = preceding->next;
    }
    current->next = previous;        //current is the last node, reverse the next pointer
    head = current;                  //new head
    Link *ptr = NULL;
    for (ptr = head; ptr != NULL; ptr = ptr->next)
        fprintf(fp2, "%d %d %d\n", ptr->index, ptr->first, ptr->second);

    for (ptr = head; ptr != NULL; ptr = ptr->next) {
        if (ptr->distance != FLT_MAX) {
            for (i = 0; i < nodenumber; i++) {
                if (powf(hypotf(node[i].xaxis - node[ptr->first].xaxis,
                node[i].yaxis - node[ptr->first].yaxis), 2)
                + powf(hypotf(node[i].xaxis - node[ptr->second].xaxis,
                node[i].yaxis - node[ptr->second].yaxis), 2) < 
                powf(hypotf(node[ptr->first].xaxis - node[ptr->second].xaxis,
                node[ptr->first].yaxis - node[ptr->second].yaxis), 2)) {
                    ptr->distance = FLT_MAX;
                    linkcount--;
                    break;
                } else {
                    continue;
                }
            }
        }
    }
    fprintf(fp2, "%d\n", linkcount);
    for (ptr = head; ptr != NULL; ptr = ptr->next) {
        if (ptr->distance != FLT_MAX)
            fprintf(fp2, "%d %d %d\n", ptr->index, ptr->first, ptr->second);
    }
    fclose(fp1); fclose(fp2);
    return 0;
}
