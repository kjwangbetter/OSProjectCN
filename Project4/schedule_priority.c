#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"
#include "cpu.h"



void add(char *name, int priority, int burst, struct node **head){
    Task *t_new = (Task*)malloc(sizeof(Task*));
    t_new->name = name;
    t_new->priority = priority;
    t_new->burst = burst;

    struct node *current_node, *front_node;
    current_node = *head;
    front_node = NULL;
    if(current_node==NULL)
        {
            insert(head, t_new);
            return ;
        }
    while(current_node!=NULL)
    {
        if(priority < current_node->task->priority ){
            front_node = current_node;
            current_node = current_node->next;

        }
        else{
            struct node* node_newtask = malloc(sizeof(struct node));
            node_newtask->task = t_new;
            node_newtask->next = current_node;
            if(front_node==NULL){
                    *head = node_newtask;
            }
            else{
                front_node->next = node_newtask;
            }
            return;
        }
    }
    if(current_node==NULL)
    {
        struct node* node_newtask = malloc(sizeof(struct node));
        node_newtask->task = t_new;
        node_newtask->next = NULL;
        front_node->next = node_newtask;
        return;
    }
}


void schedule(struct node **head){
    struct node* current_node;
    Task *new_task;
    current_node = *head;
    while(current_node!=NULL)
    {
        new_task = current_node->task;
        run(new_task, new_task->burst);
        current_node = current_node->next;
    }
}
