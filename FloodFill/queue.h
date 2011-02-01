#define MAX_Q_SIZE 128
#include <stdio.h>

struct Queue {
	int content[MAX_Q_SIZE];
	unsigned short int qTop;
	unsigned short int qBot;
};

void emptyQueue(Queue *emptyMe);
void pushQueue(Queue *addToMe, short int addMe);
short int popQueue(Queue *unqueueMe);
Queue cloneQueue(Queue cloneMe);