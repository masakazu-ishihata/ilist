# iList

自作 list ライブラリ。（しょぼい）   
ilist の i は ishihata の i です。（重要）   
気持ちとしては list の先頭、末尾をちょろちょろいじるものを作りたい。   

## Methods
### new/free

    ilist *ilist_new(void);

ilist インスタンスを生成する。

    void ilist_free(ilist *_l);

ilist _l を free する。   
ただし _l は空でないといけない。

    void ilist_free_func(ilist *_l, void (*free_func)(void *));

ilist _l を free する。   
ただし _l 内のアイテムは free_fucn によって free される。

### accessor



### shift/unshift

    void *ilist_shift(ilist *_l);

ilsit _l の先頭のアイテムを取得する。   
取得されたアイテムは _l から取り除かれる。

    size_t ilist_unshift(ilist *_l, void *_item);

ilist _l の先頭にアイテム _item を追加する。   
追加後のサイズを返す。



### pop/push

    void *ilist_pop(ilist *_l);

ilist _l の末尾のアイテムを取得する。   
取得されたアイテムは _l から取り除かれる。

    size_t ilist_push(ilist *_l, void *_item);

ilist _l の末尾にアイテム _item を追加する。   
追加後のサイズを返す。




### peek

    size_t ilist_size(ilist *_l);

ilist _l のサイズ（アイテム数）を返す。

    void *ilist_head(ilist *_l);

ilist _l の先頭のアイテムを返す。   
_l からは取り除かれない。

    void *ilist_tail(ilist *_l);

ilist _l の末尾のアイテムを返す。   
_l からは取り除かれない。

    void *ilist_succ(ilist *_l);

ilist _l から直前に取得された（見られた）アイテムの次のアイテムを返す。  
_l からは取り除かれない。   
以下の使い方の様に ilist 全体を舐めるときに便利。

    void *ilist_peek(ilist *_l);

ilist _l の直前に取得された（見られた）アイテムの次のアイテムを返す。   
_l からは取り除かれない。   
succ と異なり、この参照は次の peek, succ に影響を与えない。


### look at

    void *ilist_look_at(ilist *_l, int _i)

ilsit _l の _i 番目のアイテムを返す。   
_l からは取り除かれない。


### remove/insert

    void *ilist_remove(ilist *_l);

ilist _l の直前に取得された（見られた）アイテムを取得する。
取得されたアイテムは _l から取り除かれる。

    void *ilist_remove_at(ilist *_l, int _i);

ilist _l の _i 番目のアイテムを取得する。
取得されたアイテムは _l から取り除かれる。


    size_t ilist_insert(ilist *_l,, void *_item);

ilist _l の直前に取得された（見られた）アイテムの後ろにアイテム _item を追加する。  
追加後のサイズを返す。

    size_t ilist_insert_at(ilist *_l, void *_item, int _i);

ilist _l の _i 番目のアイテムの後ろにアイテム _item を追加する。  
追加後のサイズを返す。

### clear

    void ilist_clear(ilist *_l);

ilist _l の中身をすべて吐き出す。   
要素は free されない。

    void ilist_clear_func(ilist *_l, void (*free_func)(void));

ilist _l の中身をすべて吐き出す。   
要素は free_func によって free される。

### sort

    void ilist_sort(ilist *_l, int (*comp)(void *, void *));

ilist _l を comp を元にソートする。


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
