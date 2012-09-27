#include "ilist.h"

/*----------------------------------------------------------------------------*/
/* inner list */
/*----------------------------------------------------------------------------*/
iinnerlist *iinnerlist_new(void)
{
  iinnerlist *il;

  if( (il = (iinnerlist *)malloc(sizeof(iinnerlist))) == NULL){
    perror("iinnnerlist_new");
    exit(EXIT_FAILURE);
  }
  il->item = NULL;
  il->prev = NULL;
  il->next = NULL;

  return il;
}
void iinnerlist_free(iinnerlist *_l)
{
  if(_l != NULL){
    if(_l->item != NULL || _l->prev != NULL || _l->next != NULL){
      printf("innerlist_free: free error\n");
      exit(EXIT_FAILURE);
    }
    free(_l);
  }
}

/*----------------------------------------------------------------------------*/
/* list */
/*----------------------------------------------------------------------------*/
/* new/free */
ilist *ilist_new(void)
{
  ilist *l;

  if( (l = (ilist *)malloc(sizeof(ilist))) == NULL){
    perror("ilist_new");
    exit(EXIT_FAILURE);
  }
  l->size = 0;
  l->head = NULL;
  l->tail = NULL;

  return l;
}
void ilist_free(ilist *_l)
{
  if(_l != NULL){
    if(_l->size != 0){
      printf("ilist_free: free error\n");
      exit(EXIT_FAILURE);
    }
    free(_l);
  }
}
void ilist_free_func(ilist *_l, void (*free_func)(void *))
{
  iinnerlist *il;

  if(_l != NULL){
    /* free inner list */
    while(_l->head != NULL){
      il = (_l->head);
      _l->head = il->next;

      /* free innner list */
      free_func(il->item);
      il->item = NULL;
      il->prev = NULL;
      il->next = NULL;
      iinnerlist_free(il);
    }
    /* free self */
    _l->size = 0;
    _l->head = NULL;
    _l->tail = NULL;
    free(_l);
  }
}

/* shift/unshift */
void *ilist_shift(ilist *_l)
{
  void *item;
  iinnerlist *il;

  /* empty */
  if(_l->size == 0) return NULL;

  /* shift head */
  il = _l->head;

  item = il->item;
  il->item = NULL;

  _l->head = il->next;
  il->next = NULL;

  if(_l->head != NULL) (_l->head)->prev = NULL;
  il->prev = NULL;

  iinnerlist_free(il);

  _l->size--;
  _l->next = _l->head;
  if(_l->size == 0) _l->tail = NULL;

  return item;
}
size_t ilist_unshift(ilist *_l, void *_item)
{
  iinnerlist *il = iinnerlist_new();
  il->item = _item;

  /* empty */
  if(_l->size == 0){
    _l->head = il;
    _l->tail = il;
  }
  /* not empty */
  else{
    (_l->head)->prev = il;
    il->next = _l->head;
    _l->head = il;
  }

  return ++(_l->size);
}

/* push/pop */
void *ilist_pop(ilist *_l)
{
  void *item;
  iinnerlist *il;

  /* empty */
  if(_l->size == 0) return NULL;

  /* pop tail */
  il = _l->tail;

  item = il->item;
  il->item = NULL;

  _l->tail = il->prev;
  il->prev = NULL;

  if(_l->tail != NULL) (_l->tail)->next = NULL;
  il->next = NULL;

  iinnerlist_free(il);

  _l->size--;
  _l->next = NULL;
  if(_l->size == 0) _l->head = NULL;


  return item;
}
size_t ilist_push(ilist *_l, void *_item)
{
  iinnerlist *il = iinnerlist_new();
  il->item = _item;

  /* empty */
  if(_l->size == 0){
    _l->head = il;
    _l->tail = il;
  }
  /* not empty */
  else{
    (_l->tail)->next = il;
    il->prev = _l->tail;
    _l->tail = il;
  }

  return ++(_l->size);
}

/* peek */
size_t ilist_size(ilist *_l)
{
  return _l->size;
}
void *ilist_head(ilist *_l)
{
  if(_l->size == 0) return NULL;
  _l->next = (_l->head)->next;
  return (_l->head)->item;
}
void *ilist_tail(ilist *_l)
{
  if(_l->size == 0) return NULL;
  _l->next = NULL;
  return (_l->tail)->item;
}
void *ilist_peek(ilist *_l, int _i)
{
  int i;
  iinnerlist *il;

  if(_i >=  _l->size) return NULL;

  for(il=_l->head, i=0; i<_i; il=il->next, i++);
  _l->next = il->next;

  return il->item;
}

/* succ */
void *ilist_succ(ilist *_l)
{
  void *item;

  if(_l->next == NULL) return NULL;
  item = (_l->next)->item;
  _l->next = (_l->next)->next;

  return item;
}
