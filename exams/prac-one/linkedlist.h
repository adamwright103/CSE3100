#ifndef LINKEDLIST_H
#define LINKEDLIST_H

enum ErrorNumber
{
  ERR_OK,
  ERR_NOMEM,
  ERR_NOREVERSE,
  ERR_END
};

void error_message(enum ErrorNumber errno);

typedef struct node_tag
{
  int v;
  struct node_tag *next;
} node;

node *new_node(int v);
node *prepend(node *head, node *newnode);
node *find_last(node *head);
node *append(node *head, node *newnode);
node *delete_list(node *head);
void print_list(node *head);
node *reverse_list(node *head);

#endif