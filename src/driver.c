#include "rbtree.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    // 트리 생성 테스트
    rbtree *t = new_rbtree();
    
    printf("트리 생성 완료\n");
    printf("root: %p\n", (void*)t->root);
    printf("nil: %p\n", (void*)t->nil);
    printf("nil->color: %d (0=RED, 1=BLACK)\n", t->nil->color);
    printf("root == nil ? %s\n", (t->root == t->nil) ? "YES" : "NO");
    
    // 메모리 해제
    delete_rbtree(t);
    printf("트리 삭제 완료\n");
    
    return 0;
}