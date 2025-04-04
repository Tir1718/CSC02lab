#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100

typedef struct {
    char name[50];
    int priority; // 1 (Lowest) to 5 (Highest)
    char condition[100];
} Patient;

typedef struct {
    Patient patients[MAX_PATIENTS];
    int size;
} PriorityQueue;

void initQueue(PriorityQueue *pq) {
    pq->size = 0;
}

void swap(Patient *a, Patient *b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue *pq, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->patients[index].priority > pq->patients[parent].priority) {
            swap(&pq->patients[index], &pq->patients[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapifyDown(PriorityQueue *pq, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->patients[left].priority > pq->patients[largest].priority)
        largest = left;

    if (right < pq->size && pq->patients[right].priority > pq->patients[largest].priority)
        largest = right;

    if (largest != index) {
        swap(&pq->patients[index], &pq->patients[largest]);
        heapifyDown(pq, largest);
    }
}

// O(log n)
void enqueue(PriorityQueue *pq, Patient patient) {
    if (pq->size >= MAX_PATIENTS) {
        printf("Clinic is at full capacity!\n");
        return;
    }
    pq->patients[pq->size] = patient;
    heapifyUp(pq, pq->size);
    pq->size++;
    printf("%s added to queue (Priority: %d, Condition: %s)\n", 
           patient.name, patient.priority, patient.condition);
}

// O(log n)
Patient dequeue(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("No patients in queue!\n");
        Patient empty = {"", -1, ""};
        return empty;
    }
    Patient highest = pq->patients[0];
    pq->patients[0] = pq->patients[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    return highest;
}

void displayQueue(PriorityQueue *pq) {
    printf("\nCurrent Patient Queue:\n");
    printf("----------------------\n");
    for (int i = 0; i < pq->size; i++) {
        printf("%d. %s (Priority: %d, Condition: %s)\n", 
               i+1, pq->patients[i].name, 
               pq->patients[i].priority, pq->patients[i].condition);
    }
}

int main() {
    PriorityQueue clinic;
    initQueue(&clinic);

    // Sample patients arriving
    enqueue(&clinic, (Patient){"Rahul Sharma", 3, "High fever"});
    enqueue(&clinic, (Patient){"Priya Patel", 5, "Chest pain"});
    enqueue(&clinic, (Patient){"Amit Kumar", 2, "Minor cut"});
    enqueue(&clinic, (Patient){"Neha Gupta", 4, "Broken arm"});
    enqueue(&clinic, (Patient){"Sanjay Singh", 1, "Routine checkup"});

    displayQueue(&clinic);

    // Doctor seeing patients
    printf("\nDoctor is seeing patients:\n");
    printf("--------------------------\n");
    while (clinic.size > 0) {
        Patient next = dequeue(&clinic);
        printf("Now seeing: %s (Priority %d: %s)\n", 
               next.name, next.priority, next.condition);
    }

    return 0;
}
