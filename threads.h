#ifndef THREADS_H
#define THREADS_H

#include "q.h"

extern struct TCB_t *runQ;

void startThread(struct TCB_t *thread, void (*function)(void))
{
	void *stack = (void *)malloc(8192);
	thread = (struct TCB_t *)malloc(sizeof(struct TCB_t));
	init_TCB(thread, function, stack, 8192);

	addQueue(&runQ, thread);
}

void run()
{

	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(runQ->context));

}

void yield()
{
	// puts("1. yield function");
	struct TCB_t *temp = runQ;
	// puts("-. rotate queue");
	rotateQueue(&runQ);

	// puts("-. swap context");
	swapcontext(&(temp->context), &(runQ->context));
}

#endif
