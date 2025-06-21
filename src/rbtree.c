#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));

  // nil 노드 생성 및 초기화
  p->nil = (node_t *)calloc(1, sizeof(node_t));
  p->nil->color = RBTREE_BLACK;
  p->nil->parent = p->nil; // nil을 NULL처럼 사용
  p->nil->left = p->nil;
  p->nil->right = p->nil;

  // 빈 트리 초기화
  p->root = p->nil;

  return p;
}

void delete_all_nodes(node_t *node, node_t *nil)
{
  if (node == nil)
  {
    return; // nil 노드에 도달하면 중단
  }

  // 재귀를 사용하여 자식들부터 먼저 해제 (후위 순회)
  delete_all_nodes(node->left, nil);
  delete_all_nodes(node->right, nil);

  // 자식들이 모두 해제된 후에 현재 노드 해제
  free(node);
}

void delete_rbtree(rbtree *t)
{
  // 1. 모든 실제 노드들 해제
  delete_all_nodes(t->root, t->nil);

  // 2. nil 노드 해제
  free(t->nil);

  // 3. 트리 구조체 해제
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // 1. 새 노드 생성
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  new_node->key = key;
  new_node->color = RBTREE_RED; // 새 노드는 RED로 시작
  new_node->left = t->nil;
  new_node->right = t->nil;
  new_node->parent = t->nil;

  // 2. 빈 트리라면 루트로 설정
  if (t->root == t->nil)
  {
    t->root = new_node;
    new_node->color = RBTREE_BLACK; // 루트는 항상 BLACK
    return new_node;
  }

  // 3. BST와 같은 방식으로 삽입 위치 찾기
  node_t *current = t->root; // root부터
  node_t *parent = t->nil;   // 우선 nil로 초기화

  while (current != t->nil)
  { // 트리의 끝까지
    parent = current;
    if (key <= current->key)
    { // multiset이므로 같은 값도 왼쪽에
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }

  // 4. 부모 노드에 연결
  new_node->parent = parent;
  if (key <= parent->key)
  {
    parent->left = new_node;
  }
  else
  {
    parent->right = new_node;
  }

  // 새 노드가 루트 노드가 아니고, 부모 색이 red일 때
  while (new_node != t->root && new_node->parent->color == RBTREE_RED)
  {

    // 부모가 조부모의 왼쪽 자식인 경우
    if (new_node->parent == new_node->parent->parent->left)
    {
      node_t *uncle = new_node->parent->parent->right; // 삼촌 노드

      // Case 1: 삼촌이 RED
      if (uncle->color == RBTREE_RED)
      {
        new_node->parent->color = RBTREE_BLACK;       // 부모 색 변경
        uncle->color = RBTREE_BLACK;                  // 삼촌 색 변경
        new_node->parent->parent->color = RBTREE_RED; // 조부모 색 변경
        new_node = new_node->parent->parent;          // 조부모로 다시 이동

        // 색칠로 해결
      }
      // Case 2: 삼촌이 BLACK
      else
      {
        // Case 2-1: 새 노드가 부모의 오른쪽 자식 (지그재그)
        if (new_node == new_node->parent->right)
        {
          // 회전 필요
        }
        // Case 2-2: 새 노드가 부모의 왼쪽 자식 (일직선)
        // 회전 필요
      }
    }
    // 부모가 조부모의 오른쪽 자식인 경우 (위와 대칭)
    else
    {
      node_t *uncle = new_node->parent->parent->left; // 삼촌 노드

      // Case 3: 삼촌이 RED
      if (uncle->color == RBTREE_RED)
      {
        new_node->parent->color = RBTREE_BLACK;       // 부모 색 변경
        uncle->color = RBTREE_BLACK;                  // 삼촌 색 변경
        new_node->parent->parent->color = RBTREE_RED; // 조부모 색 변경
        new_node = new_node->parent->parent;          // 조부모로 다시 이동
        // 색칠로 해결 (Case 1과 동일)
      }
      // Case 4: 삼촌이 BLACK
      else
      {
        // Case 4-1: 새 노드가 부모의 왼쪽 자식 (지그재그)
        if (new_node == new_node->parent->left)
        {
          // 회전 필요
        }
        // Case 4-2: 새 노드가 부모의 오른쪽 자식 (일직선)
        // 회전 필요
      }
    }
  }

  return new_node;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  node_t *current = t->root;

  while (current != t->nil)
  {
    if (key == current->key)
    {
      return current; // 찾음
    }
    else if (key < current->key)
    {
      current = current->left; // 왼쪽으로
    }
    else
    {
      current = current->right; // 오른쪽으로
    }
  }

  return NULL; // 못 찾음
}

node_t *rbtree_min(const rbtree *t)
{
  if (t->root == t->nil)
  {
    return NULL; // 빈 트리
  }

  node_t *current = t->root;

  // 가장 왼쪽으로 계속 이동
  while (current->left != t->nil)
  {
    current = current->left;
  }

  return current; // 가장 작은 값
}

node_t *rbtree_max(const rbtree *t)
{
  if (t->root == t->nil)
  {
    return NULL; // 빈 트리
  }

  node_t *current = t->root;

  // 가장 오른쪽으로 계속 이동
  while (current->right != t->nil)
  {
    current = current->right;
  }

  return current; // 가장 큰 값
}

int rbtree_erase(rbtree *t, node_t *p)
{
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  return 0;
}
