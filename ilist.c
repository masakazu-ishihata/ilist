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
/* new */
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
/* free */
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
/* clear */
void ilist_clear(ilist *_l)
{
  while(ilist_pop(_l) != NULL);
}
void ilist_clear_func(ilist *_l, void (*free_func)(void *))
{
  void *p;
  while((p=ilist_pop(_l)) != NULL){
    free_func(p);
  }
}

/*----------------------------------------------------------------------------*/
/* accessor */
/*----------------------------------------------------------------------------*/
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
void *ilist_succ(ilist *_l)
{
  void *item;

  if(_l->next == NULL) return NULL;
  item = (_l->next)->item;
  _l->next = (_l->next)->next;

  return item;
}
void *ilist_peek(ilist *_l)
{
  if(_l->next == NULL)
    return NULL;
  else
    return (_l->next)->item;
}

/*----------------------------------------------------------------------------*/
/* look */
/*----------------------------------------------------------------------------*/
void *ilist_look_at(ilist *_l, int _i)
{
  int i;
  void *item;

  for(item=ilist_head(_l), i=0; item!=NULL && i<_i; item=ilist_succ(_l), i++);
  return item;
}

/*----------------------------------------------------------------------------*/
/* shift, unshift */
/*----------------------------------------------------------------------------*/
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
  if(_l->size == 0){
    _l->head = NULL;
    _l->tail = NULL;
    _l->next = NULL;
  }else{
    _l->next = (_l->head)->next;
  }

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
  _l->next = (_l->head)->next;

  return ++(_l->size);
}

/*----------------------------------------------------------------------------*/
/* push, pop */
/*----------------------------------------------------------------------------*/
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
  if(_l->size == 0) _l->head = NULL;
  _l->next = _l->tail;

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
    if(_l->tail == NULL) exit(1);
    (_l->tail)->next = il;
    il->prev = _l->tail;
    _l->tail = il;
  }
  _l->next = _l->tail;

  return ++(_l->size);
}

/*----------------------------------------------------------------------------*/
/* remove, insert */
/*----------------------------------------------------------------------------*/
void *ilist_remove(ilist *_l)
{
  void *item;
  iinnerlist *a, *b, *c;

  /* empty */
  if(_l->size == 0)
    return NULL;

  /* @ tail || no taget */
  if(_l->size == 1 || _l->next == NULL)
    return ilist_pop(_l);

  /* @ head */
  if(_l->next == (_l->head)->next)
    return ilist_shift(_l);

  /* @ inner */
  /* a -> b -> c | c = next */
  c = _l->next;
  b = c->prev;
  a = b->prev;

  /* a -> c */
  if(a != NULL) a->next = c;
  c->prev = a;

  /* remove b */
  item = b->item;
  b->prev = NULL;
  b->next = NULL;
  b->item = NULL;
  iinnerlist_free(b);
  _l->size--;

  return item;
}
size_t ilist_insert(ilist *_l, void *_item)
{
  iinnerlist *il;

  /* @ tail */
  if(_l->next == NULL)
    return ilist_push(_l, _item);

  /* @ head */
  if(_l->next == (_l->head)->next)
    return ilist_unshift(_l, _item);

  /* @ inner */
  il = iinnerlist_new();
  il->item = _item;
  il->prev = (_l->next)->prev;
  il->next = _l->next;
  ((_l->next)->prev)->next = il;
  (_l->next)->prev = il;
  _l->next = il;

  return ++_l->size;
}
void *ilist_remove_at(ilist *_l, int _i)
{
  if(ilist_look_at(_l, _i) != NULL)
    return ilist_remove(_l);
  else
    return NULL;
}
size_t ilist_insert_at(ilist *_l, void *_item, int _i)
{
  if(ilist_look_at(_l, _i) != NULL)
    return ilist_insert(_l, _item);
  else
    return 0;
}

/*----------------------------------------------------------------------------*/
/* sort */
/*----------------------------------------------------------------------------*/
int ilist_sort(ilist *_l, int (*comp)(void *, void *))
{
  ilist *a, *b;

  /* sort is no needed */
  if(_l->size < 2) return 0;

  /* split */
  a = _l;
  b = ilist_cut_at(a, a->size/2);

  /* sort */
  ilist_sort(a, comp);
  ilist_sort(b, comp);

  /* merge */
  ilist_merge(a, b, comp);
  ilist_free(b);

  return 1;
}
ilist *ilist_cut_at(ilist *_l, int _i)
{
  int i;
  iinnerlist *il;
  ilist *a;
  a = ilist_new();

  /* cannot cut */
  if(_i >= _l->size)
    return a;

  /* cut at head */
  if(_i == 0){
    ilist_connect(a, _l);
    return a;
  }

  /* cut at _i */
  for(i=0, il=_l->head; i<_i; i++, il=il->next);
  a->size = _l->size - _i;
  a->head = il;
  a->tail = _l->tail;
  a->next = NULL;

  _l->size = _i;
  _l->tail = il->prev;
  _l->next = NULL;

  (il->prev)->next = NULL;
  il->prev = NULL;

  return a;
}
void ilist_connect(ilist *_a, ilist *_b)
{
  iinnerlist *ila, *ilb;

  /* a is empty */
  if(_a->size == 0){
    _a->size = _b->size;
    _a->head = _b->head;
    _a->tail = _b->tail;
    _a->next = NULL;
  }

  /* a & b are not empty */
  else if(_a->size > 0 && _b->size > 0){
    ila = _a->tail;
    ilb = _b->head;

    ila->next = ilb;
    ilb->prev = ila;

    _a->size += _b->size;
    _a->tail = _b->tail;
  }

  /* clear b */
  _b->size = 0;
  _b->head = NULL;
  _b->tail = NULL;
  _b->next = NULL;
}

void ilist_merge(ilist *_a, ilist *_b, int (*comp)(void *, void *))
{
  ilist *l;
  void *p;

  l = ilist_new();

  while(_a->size > 0 && _b->size > 0){
    if(comp(ilist_head(_a), ilist_head(_b))){
      p = ilist_shift(_a);
    }else{
      p = ilist_shift(_b);
    }
    ilist_push(l, p);
  }
  if(_a->size > 0) ilist_connect(l, _a);
  if(_b->size > 0) ilist_connect(l, _b);

  /* l -> _a */
  ilist_connect(_a, l);
  ilist_free(l);
}
