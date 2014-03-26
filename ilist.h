#ifndef _INCLUDE_ILIST_H_
#define _INCLUDE_ILIST_H_

/*----------------------------------------------------------------------------*/
/* include */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

/*----------------------------------------------------------------------------*/
/* inner list */
/*----------------------------------------------------------------------------*/
typedef struct IINNERLIST iinnerlist;
struct IINNERLIST
{
  void *item;
  iinnerlist *prev;
  iinnerlist *next;
};
iinnerlist *iinnerlist_new(void);
void iinnerlist_free(iinnerlist *_l);

/*----------------------------------------------------------------------------*/
/* list */
/*----------------------------------------------------------------------------*/
typedef struct ILIST
{
  size_t size;
  iinnerlist *head;
  iinnerlist *tail;
  iinnerlist *next;
} ilist;

/* new/free */
ilist *ilist_new(void);
void ilist_free(ilist *_l);
void ilist_free_func(ilist *_l, void (*free_func)(void *));

/* shift/unshift */
void *ilist_shift(ilist *_l);
size_t ilist_unshift(ilist *_l, void *_item);

/* push/pop */
void *ilist_pop(ilist *_l);
size_t ilist_push(ilist *_l, void *_item);

/* remove/insert */
void *ilist_remove(ilist *_l);
void *ilist_remove_at(ilist *_l, int _i);
void ilist_insert(ilist *_l, void *_item);
void ilist_insert_at(ilist *_l, int _i, void *_item);

/* peek */
size_t ilist_size(ilist *_l);
void *ilist_head(ilist *_l);
void *ilist_tail(ilist *_l);
void *ilist_peek(ilist *_l, int _i);

/* succ */
void *ilist_succ(ilist *_l);

/* clear */
void ilist_clear(ilist *_l);
void ilist_clear_func(ilist *_l, void (*free_func)(void *));

#endif /* _INCLUDE_ILIST_H_ */
