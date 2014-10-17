#ifndef _INCLUDE_ILIST_H_
#define _INCLUDE_ILIST_H_

/*----------------------------------------------------------------------------*/
/* include */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <istring.h>

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

/* new, free clear */
ilist *ilist_new(void);
void   ilist_free(void *_p);
void   ilist_free_func(ilist *_l, void (*free_func)(void *));
void   ilist_clear(ilist *_l);
void   ilist_clear_func(ilist *_l, void (*free_func)(void *));

/* accessor */
size_t ilist_size(ilist *_l);
void  *ilist_head(ilist *_l);
void  *ilist_tail(ilist *_l);
void  *ilist_succ(ilist *_l);
void  *ilist_peek(ilist *_l);
void  *ilist_look_at(ilist *_l, size_t _i);

/* shift, unshift */
void  *ilist_shift(ilist *_l);
size_t ilist_unshift(ilist *_l, void *_item);

/* push, pop */
void  *ilist_pop(ilist *_l);
size_t ilist_push(ilist *_l, void *_item);

/* remove, insert */
void  *ilist_remove(ilist *_l);
size_t ilist_insert(ilist *_l, void *_item);
void  *ilist_remove_at(ilist *_l, size_t _i);
size_t ilist_insert_at(ilist *_l, void *_item, size_t _i);

/* binomial operators */
void ilist_connect(ilist *_a, ilist *_b);

/* sort */
int ilist_sort(ilist *_l, int (*comp)(void *, void *));
ilist *ilist_cut_at(ilist *_l, size_t _i);
void ilist_merge(ilist *_a, ilist *_b, int (*comp)(void *, void *));

/* file */
void ilist_export(FILE *_fp, ilist *_l);
ilist *ilist_import(const char *_file);

#endif /* _INCLUDE_ILIST_H_ */
