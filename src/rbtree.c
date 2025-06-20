#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    
    // nil 노드 생성 및 초기화
    p->nil = (node_t *)calloc(1, sizeof(node_t));
    p->nil->color = RBTREE_BLACK;
    p->nil->parent = p->nil;
    p->nil->left = p->nil;
    p->nil->right = p->nil;
    
    // 빈 트리 초기화
    p->root = p->nil;
    
    return p;
}

void delete_all_nodes(node_t *node, node_t *nil) {
    if (node == nil) {
        return;  // nil 노드에 도달하면 중단
    }
    
    // 자식들부터 먼저 해제 (후위 순회)
    delete_all_nodes(node->left, nil);
    delete_all_nodes(node->right, nil);
    
    // 자식들이 모두 해제된 후에 현재 노드 해제
    free(node);
}

void delete_rbtree(rbtree *t) {
    // 1. 모든 실제 노드들 해제
    delete_all_nodes(t->root, t->nil);
    
    // 2. nil 노드 해제
    free(t->nil);
    
    // 3. 트리 구조체 해제
    free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
