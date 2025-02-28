#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

void error_message(enum ErrorNumber errno)
{
  char *messages[] = {"OK", "Memory allocaton failed.",
                      "Reversing is not supported."};

  if (errno < 0 || errno > ERR_END)
    errno = ERR_END;
  printf("linkedlist: %s\n", messages[errno]);
}

node *new_node(int v)
{
  node *p = malloc(sizeof(node));
  if (p == NULL)
  {
    error_message(ERR_NOMEM);
    exit(-1);
  }
  p->v = v;
  p->next = NULL;
  return p;
}

node *prepend(node *head, node *newnode)
{
  newnode->next = head;
  return newnode;
}

node *find_last(node *head)
{
  if (head != NULL)
  {
    while (head->next != NULL)
      head = head->next;
  }
  return head;
}

node *append(node *head, node *newnode)
{
  node *p = find_last(head);

  newnode->next = NULL;
  if (p == NULL)
    return newnode;
  p->next = newnode;
  return head;
}

node *delete_list(node *head)
{
  while (head != NULL)
  {
    node *p = head->next;
    free(head);
    head = p;
  }
  return head;
}

void print_list(node *head)
{
  while (head)
  {
    printf("%d", head->v);
    head = head->next;
  }
  printf("\n");
}

node *reverse_list(node *head)
{
  if (head == NULL || head->next == NULL)
    return head;

  node *newhead = reverse_list(head->next);
  head->next->next = head;
  head->next = NULL;
  return newhead;
}