#include "linked_list.h"

// create a node with value v
node *create_node(int v)
{
  node *p = malloc(sizeof(node)); // Allocate memory
  assert(p != NULL);              // you can be nicer

  // Set the value in the node.
  p->v = v;
  p->next = NULL;
  return p; // return
}

// TODO:
void insert(node **head, node *newnode)
{
  if ((*head) == NULL)
  {
    // fill in code below
    // head should point to new node
    *head = newnode;
    return;
  }
  node *p = (*head);
  node *q = p;
  while (p->next != NULL && newnode->v > p->v)
  {
    // fill in code below

    // itterate to find node just before wehere we want to insert
    q = p;
    p = p->next;
  }
  if (newnode->v > p->v)
  {
    // fill in code below
    // insert here
    newnode->next = p->next;
    p->next = newnode;
  }
  // fill in code below

  return;
}

// add newnode the last of the linked list determined by *head and *tail
// note **head, **tail
void insert_last(node **head, node **tail, node *newnode)
{
  if ((*head) == NULL)
  {
    (*head) = (*tail) = newnode;
  }
  else
  {
    (*tail)->next = newnode;
    (*tail) = newnode;
  }
}

// remove the first node from the list
// note **head
// return a pointer to the removed content

node *remove_first(node **head)
{
  node *p;

  p = (*head);
  if ((*head) != NULL)
    (*head) = (*head)->next;
  return p;
}

// print the list pointed by head
void print_list(node *head)
{
  node *p = head;

  while (p != NULL)
  {
    printf("%d ", p->v);
    p = p->next;
  }
  printf("\n");
}

// TODO
// merge two sorted linked list as one
node *merge(node **p1, node **p2)
{
  node *head = NULL, *tail = NULL;
  node *q1 = (*p1), *q2 = (*p2), *p;

  if (q1 == NULL && q2 == NULL)
    return NULL;
  if (q1 != NULL && q2 == NULL)
  {
    p = q1;
    (*p1) = NULL;
    return p;
  }
  if (q1 == NULL && q2 != NULL)
  {
    p = q2;
    (*p2) = NULL;
    return p;
  }

  while (q1 != NULL && q2 != NULL)
  {
    // fill in code below
    // check which node is lower then append to results llist
    // if equal does not matter which goes in
    if (q1->v < q2->v)
    {
      insert_last(&head, &tail, q1);
      q1 = q1->next;
    }
    else
    {
      insert_last(&head, &tail, q2);
      q2 = q2->next;
    }
  }
  while (q1 != NULL)
  {
    // fill in code below
    // q2 is now all inserted, can just repeatdly append q1;
    insert_last(&head, &tail, q1);
    q1 = q1->next;
  }
  while (q2 != NULL)
  {
    // fill in code below
    // ditto above but now for q2
    insert_last(&head, &tail, q2);

    q2 = q2->next;
  }
  // fill in code below
  *p1 = *p2 = NULL;

  return head;
}

int main(int argc, char *argv[])
{
  assert(argc == 2);
  int n = atoi(argv[1]);

  int a[n];
  int b[n];

  for (int i = 0; i < n; i++)
  {
    a[i] = i;
    b[i] = 2 * i;
  }

  node *p1 = NULL, *p2 = NULL;

  for (int i = 0; i < n; i++)
  {
    node *p = create_node(a[i]);
    insert(&p1, p);
  }
  print_list(p1);

  for (int i = 0; i < n; i++)
  {
    node *p = create_node(b[i]);
    insert(&p2, p);
  }
  print_list(p2);

  node *p = merge(&p1, &p2);
  print_list(p);
  printf("%p\n", p1);
  printf("%p\n", p2);

  // TODO
  // fill in code below

  return 0;
}