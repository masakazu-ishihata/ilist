#include <stdio.h>
#include <stdlib.h>
#include "ilist.h"

int comp(void *a, void *b)
{
  return (*(int *)a > *(int *)b);
};

int main(void)
{
  ilist *a, *b;
  int i, *p;

  a = ilist_new();
  b = ilist_new();

  /*------------------------------------*/
  /* connect */
  /*------------------------------------*/
  for(i=0; i<10; i++){
    p = (int *)malloc(sizeof(int));
    *p = i;

    if(i % 2 == 0){
      ilist_push(a, p);
    }else{
      ilist_push(b, p);
    }
  }

  /* before */
  printf("list a (%zd)\n", a->size);
  for(p=ilist_head(a); p!=NULL; p=ilist_succ(a)){
    printf("%d\n", *p);
  }
  printf("list b (%zd)\n", b->size);
  for(p=ilist_head(b); p!=NULL; p=ilist_succ(b)){
    printf("%d\n", *p);
  }

  /* connect */
  printf("connect a & b\n");
  ilist_connect(a, b);

  /* after */
  printf("list a (%zd)\n", a->size);
  for(p=ilist_head(a); p!=NULL; p=ilist_succ(a)){
    printf("%d\n", *p);
  }
  printf("list b (%zd)\n", b->size);
  for(p=ilist_head(b); p!=NULL; p=ilist_succ(b)){
    printf("%d\n", *p);
  }
  ilist_free(b);

  /*------------------------------------*/
  /* sort */
  /*------------------------------------*/
  printf("sort a\n");
  ilist_sort(a, comp);
  printf("list a (%zd)\n", a->size);
  for(p=ilist_head(a); p!=NULL; p=ilist_succ(a)){
    printf("%d\n", *p);
  }

  return 0;
};
