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

    size_t ilist_size(ilist *_l);

ilist _l のサイズ数を得る。

    void  *ilist_head(ilist *_l);

ilist _l の先頭のアイテムを得る。  
_l からアイテムは取り除かれない。

    void  *ilist_tail(ilist *_l);

ilist _l の末尾のアイテムを得る。
_l からアイテムは取り除かれない。

    void  *ilist_succ(ilist *_l);

ilist _l の直前の参照の次のアイテムを得る。
_l からアイテムは取り除かれない。

    void  *ilist_peek(ilist *_l);

ilist _l の直前の参照の次のアイテムを見る。  
_l からアイテムは取り除かれない。  
この操作は参照として扱わない。

    void  *ilist_look_at(ilist *_l, size_t _i);

ilist _l の _i 番目のアイテムを得る。  
_l からアイテムは取り除かれない。

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


### import / export

    void ilist_export(FILE *_fp, ilist *_l);

ilist _l の内容を _fp に書き出す。  
ただしアイテムは char * 型とする。

    ilist *ilist_import(const char *_file);

_file の各行を ilist 形式で読み込む。  
各行が１つのアイテムとして扱われる。

### macro

    ILIST_FOR(v, l)
    // for(v=ilist_head(l); v!=NULL; v=ilist_succ(l))

    ILIST_WHILE(v, l)
    // while((v=ilist_shift(l)) != NULL)

よく使う for 文と while 文をマクロ化したもの。


