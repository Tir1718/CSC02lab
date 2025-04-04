#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

// Initialize stack
void initStack(Stack *s) {
    s->top = -1;
}

// Check if stack is empty
bool isEmpty(Stack *s) {
    return s->top == -1;
}

// Check if stack is full
bool isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// Push to stack - O(1)
void push(Stack *s, int item) {
    if (isFull(s)) {
        printf("Stack overflow!\n");
        return;
    }
    s->data[++s->top] = item;
}

// Pop from stack - O(1)
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        exit(1);
    }
    return s->data[s->top--];
}

// Queue structure using two stacks
typedef struct {
    Stack stack1; // For enqueue
    Stack stack2; // For dequeue
} Queue;

// Initialize queue
void initQueue(Queue *q) {
    initStack(&q->stack1);
    initStack(&q->stack2);
}

// Enqueue visitor - O(1) amortized
void enqueue(Queue *q, int visitor) {
    if (isFull(&q->stack1)) {
        printf("Queue is full! Visitor %d cannot join.\n", visitor);
        return;
    }
    push(&q->stack1, visitor);
    printf("Visitor %d joined the queue\n", visitor);
}

// Dequeue visitor - O(n) worst case, O(1) amortized
int dequeue(Queue *q) {
    if (isEmpty(&q->stack1) && isEmpty(&q->stack2)) {
        printf("No visitors in queue!\n");
        return -1;
    }
    
    // If stack2 is empty, transfer all from stack1
    if (isEmpty(&q->stack2)) {
        while (!isEmpty(&q->stack1)) {
            push(&q->stack2, pop(&q->stack1));
        }
    }
    
    int visitor = pop(&q->stack2);
    printf("Visitor %d is boarding the ride\n", visitor);
    return visitor;
}

int main() {
    Queue rideQueue;
    initQueue(&rideQueue);
    
    // Simulation
    enqueue(&rideQueue, 101);
    enqueue(&rideQueue, 102);
    enqueue(&rideQueue, 103);
    
    dequeue(&rideQueue); // 101 boards
    dequeue(&rideQueue); // 102 boards
    
    enqueue(&rideQueue, 104);
    
    dequeue(&rideQueue); // 103 boards
    dequeue(&rideQueue); // 104 boards
    dequeue(&rideQueue); // Queue empty
    
    return 0;
}
