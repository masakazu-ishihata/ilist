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

## 使い方
