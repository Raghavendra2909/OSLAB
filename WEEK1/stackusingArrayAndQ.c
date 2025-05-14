#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// Stack implementation using an array
typedef struct {
    int arr[MAX];
    int top;
} Stack;

void push(Stack *stack, int value) {
    if (stack->top == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
    printf("Pushed %d to stack\n", value);
}

int pop(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

void displayStack(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}

// Queue implementation using an array
typedef struct {
    int arr[MAX];
    int front, rear;
} Queue;

void enqueue(Queue *queue, int value) {
    if (queue->rear == MAX - 1) {
        printf("Queue Overflow\n");
        return;
    }
    if (queue->front == -1) queue->front = 0;
    queue->arr[++queue->rear] = value;
    printf("Enqueued %d to queue\n", value);
}

int dequeue(Queue *queue) {
    if (queue->front == -1 || queue->front > queue->rear) {
        printf("Queue Underflow\n");
        return -1;
    }
    return queue->arr[queue->front++];
}

void displayQueue(Queue *queue) {
    if (queue->front == -1 || queue->front > queue->rear) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->arr[i]);
    }
    printf("\n");
}

int main() {
    Stack stack = {.top = -1};
    Queue queue = {.front = -1, .rear = -1};

    // Stack operations
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    displayStack(&stack);
    printf("Popped from stack: %d\n", pop(&stack));
    displayStack(&stack);

    // Queue operations
    enqueue(&queue, 40);
    enqueue(&queue, 50);
    enqueue(&queue, 60);
    displayQueue(&queue);
    printf("Dequeued from queue: %d\n", dequeue(&queue));
    displayQueue(&queue);

    return 0;
}

/*
Output:
Pushed 10 to stack
Pushed 20 to stack
Pushed 30 to stack
Stack elements: 30 20 10 
Popped from stack: 30
Stack elements: 20 10 
Enqueued 40 to queue
Enqueued 50 to queue
Enqueued 60 to queue
Queue elements: 40 50 60 
Dequeued from queue: 40
Queue elements: 50 60 
*/