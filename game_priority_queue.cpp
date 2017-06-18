//
//  game_priority_queue.c
//  
//
//  Created by Kyle Kempt on 2/12/17.
//
//

#include "game_priority_queue.h"
//#include "dungeon.h"
//#include "main.h"



void decrement_queue_priority (heap_t *h) //decrement each priority by 1, indicating a turn has passed
{

    for(int i = 1; i < h->len + 1; i++)
    {
        if(h->nodes[i].priority == 0)
        {
            h->nodes[i].priority = 0;
        }
        else
        {
        h->nodes[i].priority--;
        }
    }
}



//Code for these two functions (push, pop) are from
//https://rosettacode.org/wiki/Priority_queue#C
//The other two functions are my own work building off what was given



void push (heap_t *h, int priority, struct event *data) {
    if (h->len + 1 >= h->size) {
        h->size = h->size ? h->size * 2 : 4;
        h->nodes = (node_t *)realloc(h->nodes, h->size * sizeof (node_t));
    }
    int i = h->len + 1;
    int j = i / 2;
    while (i > 1 && h->nodes[j].priority > priority) {
        h->nodes[i] = h->nodes[j];
        i = j;
        j = j / 2;
    }
    
    
    h->nodes[i].priority = priority;
    h->nodes[i].data = data;
    h->len++;
}

struct event *pop (heap_t *h) {
    int i, j, k;
    if (!h->len) {
        return NULL;
    }
    
    
    
    
    struct event *data = h->nodes[1].data;
    
    
    
    h->nodes[1] = h->nodes[h->len];
    h->len--;
    i = 1;
    while (1) {
        k = i;
        j = 2 * i;
        if (j <= h->len && h->nodes[j].priority < h->nodes[k].priority) {
            k = j;
        }
        if (j + 1 <= h->len && h->nodes[j + 1].priority < h->nodes[k].priority) {
            k = j + 1;
        }
        if (k == i) {
            break;
        }
        h->nodes[i] = h->nodes[k];
        i = k;
    }
    h->nodes[i] = h->nodes[h->len + 1];
    return data;
}


//++++++++++++++++++++++++++++++++





int peek(heap_t *h)
{
    //printf("%d\n",h->nodes[1].priority);
    
    if(h->nodes[1].priority == 0)
    {
        return 1;
    }
    return 0;
}




