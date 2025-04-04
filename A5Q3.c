#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char data[MAX_SIZE][20]; // Store binary strings
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int isFull(Queue *q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

void enqueue(Queue *q, const char *binary) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_SIZE;
    }
    strcpy(q->data[q->rear], binary);
}

char* dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        exit(1);
    }
    char* binary = q->data[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_SIZE;
    }
    return binary;
}

void generateBinaryNumbers(int n) {
    Queue q;
    initQueue(&q);
    
    // Start with the first binary number
    enqueue(&q, "1");
    
    printf("Binary numbers from 1 to %d:\n", n);
    for (int i = 1; i <= n; i++) {
        // Dequeue and print the front
        char* current = dequeue(&q);
        printf("%s%s", current, i < n ? ", " : "\n");
        
        // Generate next two binary numbers
        char next1[20], next2[20];
        strcpy(next1, current);
        strcat(next1, "0");
        enqueue(&q, next1);
        
        strcpy(next2, current);
        strcat(next2, "1");
        enqueue(&q, next2);
    }
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    
    generateBinaryNumbers(n);
    
    return 0;
}
