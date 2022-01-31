#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
FILE *fp1 = NULL, *fp2 = NULL;
typedef struct node {
    char character;
    int frequency;
    struct node *leftChild, *rightChild;
} Node;

Node *NewNode(char val, int freq) {
    Node *ret = malloc(sizeof(Node));
    if (ret != NULL) {
        ret->leftChild = ret->rightChild = NULL;
        ret->character = val;
        ret->frequency = freq;
    }
    return ret;
}
void SwapNode(Node **a, Node **b) {   // Swap Node by pointer to pointer
    Node *t = *a;
    *a = *b;
    *b = t;
}
typedef struct stat {
    char ch;
    int freq;
} Stat;

void printCodes(Node* root, char *str) { 
    if (!root) 
        return; 
    if (root->character != '\0') 
        fprintf(fp2, "%c %d %s\n", root->character, root->frequency, str); 
    str[strlen(str)] = '0';
    printCodes(root->leftChild, str); 
    str[strlen(str) - 1] = '\0';
    str[strlen(str)] = '1';
    printCodes(root->rightChild, str); 
    str[strlen(str) - 1] = '\0';
}

void encode(Node *root, char text, char *code) {
    if (!root) return;
    if (root->character == text)
        fprintf(fp2, "%s", code);
    code[strlen(code)] = '0';
    encode(root->leftChild, text, code); 
    code[strlen(code) - 1] = '\0';

    code[strlen(code)] = '1';
    encode(root->rightChild, text, code); 
    code[strlen(code) - 1] = '\0';
}
int main(void) 
{
    typedef struct node* nodePointer;
    int MAX_QUEUE_SIZE = 100;
    nodePointer priorityQueue[MAX_QUEUE_SIZE];
    int i = 0, arr_size = 0, index = 0;
	int freq[128];               // array to count acsii code's frequency 
    memset(freq, 0, sizeof(freq));
    char str[1000];
    memset(str, '\0', sizeof(str));
    if (!(fp1 = fopen("text.txt", "r"))) {
        fprintf(stderr, "reading text.txt failed\n");
        exit(-1);
    }

    while ((str[i++] = fgetc(fp1)) != EOF);// read from input file by character
  
    for (i = 0; i < (int)strlen(str); i++) // count the frequency
        freq[str[i]]++;
    arr_size = 0;
    for (i = 0; i < 128; i++) // count the number of characters' types
        if (freq[i] != 0)
            arr_size++;
  Stat arr[arr_size];
    index = 0;
    for (i = 0; i < 128; i++) { //store in another struct in array
        if (freq[i] != 0) {
            arr[index].ch = i;
            arr[index].freq = freq[i];
            index++;
        }
    }
    for (i = 0; i < arr_size; i++) 
        priorityQueue[i] = NewNode(arr[i].ch, arr[i].freq); //make new nodes from struct which stores info 

    bool sorted = false;  //use bubble sort to make it arrange increasingly 
    int n = arr_size;
    while (!sorted) {
        sorted = true;
        for (i = 0; i < n - 1; i++) {
            if (priorityQueue[i]->frequency > priorityQueue[i + 1]->frequency) {
                SwapNode(&priorityQueue[i], &priorityQueue[i + 1]);
                sorted = false;
            }
        }
        n--;
    }
    int ncase = arr_size;
    while (ncase--) {         //min heap using priorityQueue
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->character = '\0';
        temp->frequency = priorityQueue[0]->frequency + priorityQueue[1]->frequency;
        temp->leftChild = priorityQueue[0]; temp->rightChild = priorityQueue[1];
        priorityQueue[0] = temp;
        for (i = 1; i < ncase; i++) 
            SwapNode(&priorityQueue[i], &priorityQueue[i + 1]);
        // After making new node, rearrange the queue
        if (ncase > 1) { 
            n = ncase;
            sorted = false;
            while (!sorted) {
                sorted = true;
                for (i = 0; i < n - 1; i++) {
                    if (priorityQueue[i]->frequency > priorityQueue[i + 1]->frequency) {
                        SwapNode(&priorityQueue[i], &priorityQueue[i + 1]);
                        sorted = false;
                    }
                }
                n--;
            }
        }
    }
    char bit[10];
    if (!(fp2 = fopen("code.txt", "w"))) {
        fprintf(stderr, "writing code.txt failed");
        exit(-1);
    }
    fprintf(fp2, "%d\n", arr_size);  //types of input file's characters
    memset(bit, '\0', sizeof(bit));
    printCodes(priorityQueue[0], bit); //print the codebook in preorder traversal
    for (i = 0; i < (int)strlen(str); i++) { //using huffman tree traversal to encode each input's text. 
        memset(bit, '\0', sizeof(bit));
        encode(priorityQueue[0], str[i], bit);
    }
    fprintf(fp2, "\n");
    fclose(fp1); fclose(fp2);
    fp1 = fp2 = NULL;
    return 0;
}
