#include <stdlib.h>
#include "UnionFind.h"

typedef struct tree_node_t TreeNode;

struct tree_node_t{
  size_t nodeIndex;
  TreeNode* parent;
};

struct union_find_t{
  TreeNode** nodes;
  size_t totalTrees;
  size_t size;
};

static TreeNode* newNode(size_t,TreeNode*);

UnionFind* ufCreate(size_t n_items){
  UnionFind* unionFind = malloc(sizeof(UnionFind));
  if(unionFind == NULL)
    abort();

  TreeNode** nodesTable = malloc(n_items*sizeof(TreeNode*));
  if(nodesTable == NULL)
    abort();

  for(size_t i = 0; i < n_items ; i++){
    nodesTable[i] = newNode(i,NULL);
  }

  unionFind->nodes = nodesTable;
  unionFind->totalTrees = n_items;
  unionFind->size = n_items;

  return unionFind;
}

void ufFree(UnionFind* union_find){
  for(size_t i = 0; i < union_find->size; i++)
    free(union_find->nodes[i]);

  free(union_find->nodes);

  free(union_find);
}

ufStatus ufUnion(UnionFind* union_find, size_t item1, size_t item2){
  TreeNode** nodes = union_find->nodes;

  TreeNode* tree1 = nodes[item1];
  TreeNode* tree2 = nodes[item2];

  if(tree1 == NULL || tree2 == NULL)
    return UF_ERROR;

  TreeNode* rootTree1 = tree1;
  TreeNode* rootTree2 = tree2;
  int depthNode1 = 0;
  int depthNode2 = 0;

  while(rootTree1->parent != NULL || rootTree2->parent != NULL){
    if(rootTree1->parent != NULL){
      depthNode1++;
      rootTree1 = rootTree1->parent;
    }

    if(rootTree2->parent != NULL){
      depthNode2++;
      rootTree2 = rootTree2->parent;
    }
  }

  if(rootTree1 == rootTree2)
    return UF_SAME;

  if(depthNode2 < depthNode1)
    rootTree1->parent = rootTree2;
  else
    rootTree2->parent = rootTree1;

  union_find->totalTrees--;
  return UF_MERGED;
}

size_t ufFind(const UnionFind* union_find, size_t item){
  TreeNode* tree = union_find->nodes[item];
  if(tree->parent == NULL)
    return tree->nodeIndex;

  TreeNode* copy = tree;

  while(copy->parent != NULL)
    copy = copy->parent;

  tree->parent = copy;
  return tree->parent->nodeIndex;
}

size_t ufComponentsCount(const UnionFind* union_find){
  return union_find->totalTrees;
}

static TreeNode* newNode(size_t nodeIndex, TreeNode* parent){
  TreeNode* toReturn = (TreeNode*)malloc(sizeof(TreeNode));
  if(toReturn == NULL)
    abort();

  toReturn->nodeIndex = nodeIndex;
  toReturn->parent = parent;

  return toReturn;
}
