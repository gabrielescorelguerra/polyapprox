#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


AVL *avl_criar() {
    AVL *t;
    if (! (t = malloc (sizeof (AVL))))
        return NULL;

    t->raiz = NULL;
    return t;
}


static void subarvore_destruir(No *x) {
    if (x == NULL)
        return;
    subarvore_destruir(x->esq);
    subarvore_destruir(x->dir);
    free(x);
}

void avl_destruir(AVL *t) {
    subarvore_destruir(t->raiz);
    free(t);
}


No* no_criar(float x_ponto, float y_ponto) {
    No *no;
    if (! (no = malloc (sizeof (No))))
        return NULL;

    no->x = x_ponto;
    no->y = y_ponto;

    no->altura = 0;
    no->pos_heap = -1;

    no->pai = NULL;
    no->esq = NULL;
    no->dir = NULL;

    no->prox = NULL;
    no->ant = NULL;

    return no;
}


static No* arvore_inserir(AVL *t, No *z) {
    No *x, *y;

    x = t->raiz;
    y = NULL;

    while(x != NULL) {
        y = x;
        if(z->x < x->x)
            x = x->esq;
        else
            x = x->dir;
    }
    z->pai = y;

    if(y == NULL)
        t->raiz = z;
    else if(z->x < y->x)
        y->esq = z;
    else
        y->dir = z;

    return y;
}



static void transplante(AVL *t, No *u, No *v) {
    if(u->pai == NULL)
        t->raiz = v;
    else if(u == u->pai->esq)
        u->pai->esq = v;
    else
        u->pai->dir = v;

    if(v != NULL)
        v->pai = u->pai;
}
 

static No* arvore_minimo(No *x) {
    while(x->esq != NULL)
        x = x->esq;
    return x;
}


static No* arvore_remover(AVL *t, No *z) {
    No *x, *y;

    x = z->pai;

    if(z->esq == NULL)
        transplante(t, z, z->dir);
    else if(z->dir == NULL)
        transplante(t, z, z->esq);
    else {
        y = arvore_minimo(z->dir);

        if(y != z->dir) {
            x = y->pai;
            transplante(t, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        } else {
            x = y;
        }

        transplante(t, z, y);

        y->esq = z->esq;
        y->esq->pai = y;
        y->altura = z->altura;
    }
    return x;
}


static No* rot_esq(No *p) {
    No *q;
    q = p->dir;

    p->dir = q->esq;
    if(p->dir)
        p->dir->pai = p;

    q->esq = p;
    q->pai = p->pai;
    p->pai = q;    

    p->altura = 1 + MAX(ALT(p->esq), ALT(p->dir));
    q->altura = 1 + MAX(ALT(q->esq), ALT(q->dir));

    return q;
}


static No* rot_dir(No *p) {
    No *q;
    q = p->esq;

    p->esq = q->dir;
    if(p->esq)
        p->esq->pai = p;

    q->dir = p;
    q->pai = p->pai;
    p->pai = q;    

    p->altura = 1 + MAX(ALT(p->esq), ALT(p->dir));
    q->altura = 1 + MAX(ALT(q->esq), ALT(q->dir));

    return q;
}


static No* rot_esqdir(No *p) {
    p->esq = rot_esq(p->esq);
    p->esq->pai = p;

    return rot_dir(p);
}


static No* rot_diresq(No *p) {
    p->dir = rot_dir(p->dir);
    p->dir->pai = p;

    return rot_esq(p);
}


static No* avl_balance(No *x) {
    int fb;
    No *y;

    y = x;
    fb = ALT(x->dir) - ALT(x->esq);
    if(fb < -1) {
        if(ALT(x->esq->esq) < ALT(x->esq->dir))
            y = rot_esqdir(x);
        else
            y = rot_dir(x);
    } else if(fb > 1) {
        if(ALT(x->dir->dir) < ALT(x->dir->esq))
            y = rot_diresq(x);
        else
            y = rot_esq(x);
    }
    return y;
}


static void troca_filho(AVL *t, No *p, No *u, No *v) {
    if(p == NULL)
        t->raiz = v;
    else if(p->esq == u)
        p->esq = v;
    else
        p->dir = v;
}


void avl_inserir(AVL *t, No *z) {
    int a;
    No *x, *y, *p;

    z->altura = 0;
    x = arvore_inserir(t, z);
    
    while(x != NULL) {
        p = x->pai;
        
        a = 1 + MAX(ALT(x->esq), ALT(x->dir));
        y = avl_balance(x);

        if(y != x) { 
            y->pai = p;
            troca_filho(t, p, x, y);
            break;
        }

        if(x->altura == a) {
            break;
        }

        x->altura = a;
        x = x->pai;
    }        
}


void avl_remover(AVL *t, No *z) {
    int altura_nova;
    No *x, *y, *p;
    
    x = arvore_remover(t, z);
    free (z);

    while(x != NULL) {
        p = x->pai;
        int altura_antiga = x->altura;

        altura_nova = 1 + MAX(ALT(x->esq), ALT(x->dir));
        y = avl_balance(x);

        if(y != x) {
            y->pai = p;
            troca_filho(t, p, x, y);
            x = y;
        } else {
            x->altura = altura_nova;
        }

        if(x->altura == altura_antiga)
            break;

        x = x->pai;
    }        
}


static void inorder (No *x) {
    if (x == NULL)
        return;

    inorder (x->esq);
    printf ("(%f, %f) ", x->x, x->y);
    inorder (x->dir);
}


void inorder_tree_walk (AVL *t) {
    inorder (t->raiz);
    printf ("\n");
}
    