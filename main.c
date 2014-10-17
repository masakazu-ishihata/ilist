#include <stdio.h>
#include <stdlib.h>
#include "ilist.h"

/* comp for int */
int int_comp(void *a, void *b)
{
  return (*(int *)a > *(int *)b);
};
int int_comp_rev(void *a, void *b)
{
  return int_comp(b, a);
};

/* main */
int main(void)
{
  ilist *a, *b;
  int i, *p;

  a = ilist_new();
  b = ilist_new();

  /*------------------------------------*/
  /* init */
  /*------------------------------------*/
  printf("<<<< initialize >>>>\n");
  for(i=0; i<10; i++){
    p = (int *)malloc(sizeof(int));
    *p = i;
    ilist_push(i % 2 == 0 ? a : b, p);
  }

  /* before */
  printf("list a = ");
  for(p=ilist_head(a); p!=NULL; p=ilist_succ(a))
    printf("%3d", *p);
  printf("\n");

  printf("list b = ");
  for(p=ilist_head(b); p!=NULL; p=ilist_succ(b))
    printf("%3d", *p);
  printf("\n");

  /*------------------------------------*/
  /* connect */
  /*------------------------------------*/
  printf("<<<< connect a & b >>>>\n");
  ilist_connect(a, b);

  /* after */
  printf("list a = ");
  for(p=ilist_head(a); p!=NULL; p=ilist_succ(a))
    printf("%3d", *p);
  printf("\n");

  printf("list b = ");
  for(p=ilist_head(b); p!=NULL; p=ilist_succ(b))
    printf("%3d", *p);
  printf("\n");

  /*------------------------------------*/
  /* sort */
  /*------------------------------------*/
  printf("<<<< sort a >>>>\n");
  ilist_sort(a, int_comp);
  printf("list a = ");
  for(p=ilist_head(a); p!=NULL; p=ilist_succ(a))
    printf("%3d", *p);
  printf("\n");
  ilist_sort(a, int_comp_rev);
  printf("list a = ");
  for(p=ilist_head(a); p!=NULL; p=ilist_succ(a))
    printf("%3d", *p);
  printf("\n");

  /*------------------------------------*/
  /* free */
  /*------------------------------------*/
  printf("<<<< free a >>>>\n");
  ilist_free_func(a, free);
  printf("<<<< free b >>>>\n");
  ilist_free_func(b, free);

  /*------------------------------------*/
  /* import / export */
  /*------------------------------------*/
  printf("<<<< import / export >>>>\n");
  a = ilist_import("test.txt");
  ilist_export(stdout, a);
  ilist_free_func(a, free);

  return 0;
};
