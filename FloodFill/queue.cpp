#include "stdafx.h"
#include "queue.h"


/*
int main() {
	Queue q1;
	q1.qTop = 0;
	q1.qBot = 0;
	short int i;
	for (i = 0; i < MAX_Q_SIZE; i++) {
		pushQueue(&q1 , i+1);
		printf("Top: %d Bot: %d\n", q1.qTop, q1.qBot);
	}
	for (i = q1.qTop; i < q1.qBot; i++) {
		printf("The top value of the queue is: %d\n", popQueue(&q1));
		printf("The current qTop is: %d and qBot is: %d\n", q1.qTop, q1.qBot);
	}

	return 0;
}
*/

void emptyQueue(Queue *emptyMe) {
	if (emptyMe->qTop != emptyMe->qBot)
		emptyMe->qTop = emptyMe->qBot;
}

void pushQueue(Queue *addToMe, short int addMe) {
	addToMe->content[addToMe->qBot] = addMe;
	addToMe->qBot = (addToMe->qBot)%MAX_Q_SIZE + 1;
}

short int popQueue(Queue *unqueueMe) {
	short int first = unqueueMe->content[unqueueMe->qTop];
	unqueueMe->qTop = (unqueueMe->qTop)%MAX_Q_SIZE + 1;
	return first;
}

Queue cloneQueue(Queue cloneMe) {
	short int i = 0;
	Queue Clone;
	if (cloneMe.qBot < cloneMe.qTop)
		cloneMe.qBot += MAX_Q_SIZE;
	for (i=0; i < cloneMe.qBot-cloneMe.qTop; i++)
		Clone.content[i] = cloneMe.content[(cloneMe.qTop+i)%MAX_Q_SIZE];
	Clone.qTop = 0;
	Clone.qBot = i;
	return Clone;
}
