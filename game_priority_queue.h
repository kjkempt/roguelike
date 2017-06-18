//
//  game_priority_queue.h
//  
//
//  Created by Kyle Kempt on 2/12/17.
//
//

#ifndef game_priority_queue_h
#define game_priority_queue_h

#include "dungeon.h"
//#include "main.h"

#include <stdio.h>
#include <stdlib.h>


//These structs are from https://rosettacode.org/wiki/Priority_queue#C
//I made a few minor tweaks to compensate the data being passed in


typedef struct {
    int priority;
    struct event *data;
} node_t;

typedef struct {
    node_t *nodes;
    int len;
    int size;
} heap_t;


void decrement_queue_priority (heap_t *h);
void push (heap_t *h, int priority, struct event *data);
struct event *pop (heap_t *h);
int peek(heap_t *h);


#endif /* game_priority_queue_h */




