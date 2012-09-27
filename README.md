# iList

自作 list ライブラリ。（しょぼい）   
ilist の i は ishihata の i です。（重要）   
気持ちとしては list の先頭、末尾をちょろちょろいじるものを作りたい。   

## Methods
### new/free
* ilist *ilist_new(void);
* void ilist_free(ilist *_l);
* void ilist_free_func(ilist *_l, void (*free_func)(void *));

### shift/unshift
* void *ilist_shift(ilist *_l);
* size_t ilist_unshift(ilist *_l, void *_item);

## pop/push
* void *ilist_pop(ilist *_l);
* size_t ilist_push(ilist *_l, void *_item);

## peek
*    size_t ilist_size(ilist *_l);
*    void *ilist_head(ilist *_l);
*    void *ilist_tail(ilist *_l);
*    void *ilist_peek(ilist *_l, int _i);
*    void *ilist_succ(ilist *_l);

## succ
*    void *ilist_succ(ilist *_l);

## 使い方

以下みたいな感じで使うとよい気がする。

    ilist *l = ilist_new();
    int i, *p;

    /* unshift */
    for(i=0; i<10; i++){
      p = (int *)malloc(sizeof(int));
      *p = i;
      ilist_unshift(l, p);
    }

    /* push */
    for(i=0; i<10; i++){
      p = (int *)malloc(sizeof(int));
      *p = i;
      ilist_push(l, p);
    }

    /* succ */
    for(p=ilist_head(l); p != NULL; p=ilist_succ(l)){
      printf("%d\n", *p);
    }

    /* free */
    ilist_free_func(l, free);
