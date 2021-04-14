#include <stdlib.h>
#include "UnionFind.h"

typedef struct item_t Item;

struct item_t{
	Item *parent;
	size_t index;
};

struct union_find_t{
	Item **items;
	size_t nbTrees;
	size_t total_size;
};

Item* itemCreate(Item* parent,size_t index);
void itemFree(Item* item);

Item* itemCreate(Item* parent,size_t index)
{
	Item* new_item = malloc(sizeof(Item));
	if(!new_item){
	return NULL;
	}

	new_item->parent = parent;
	new_item->index = index;

	return new_item;
}

UnionFind* ufCreate(size_t n_items){
	UnionFind* new_unionFind = malloc(sizeof(UnionFind));
	if (!new_unionFind) {
	return NULL;
	}


	Item** items_array = malloc(sizeof(Item*)*n_items);
	if(!items_array){
	return NULL;
	}

	for(size_t j=0;j<n_items;j++){
		items_array[j] = itemCreate(NULL,j);
	}

	new_unionFind->items = items_array;
	new_unionFind->nbTrees = n_items;
	new_unionFind->total_size = n_items;

	return new_unionFind;
}

void ufFree(UnionFind* union_find){
	Item** items_array = union_find->items;
	for(size_t i=0 ; i<union_find->total_size ; i++){
		free(items_array[i]);
	}

	free(items_array);
	free(union_find);

}

ufStatus ufUnion(UnionFind* union_find, size_t item1, size_t item2){
	Item** items_array = union_find->items;

	Item* item01 = items_array[item1];
	Item* item02 = items_array[item2];

	if(item01 == NULL || item02 == NULL)
		return UF_ERROR;

	Item* root1 = item01;
	Item* root2 = item02;

	int rank1 = 0;
	int rank2 = 0;

	while(root1->parent != NULL || root2->parent != NULL){

		if(root1->parent != NULL){
		root1 = root1->parent;
		rank1++;
		}

		if(root2->parent != NULL){
		root2 = root2->parent;
		rank2++;
		}
	}

	if(root1==root2){
		return UF_SAME;
	}

	union_find->nbTrees -= 1;

	if(rank1 >= rank2){
		root2->parent = root1;
		return UF_MERGED;
	}else{
		root1->parent = root2;
		return UF_MERGED;
	}
}
size_t ufFind(const UnionFind* union_find, size_t item){
	Item** items_array = union_find->items;
	Item* item01 = items_array[item];
	Item *representant = item01;

	if(item01->parent == NULL){
		return item01->index;
	}


	while(representant->parent != NULL){
		representant = representant->parent;
	}

	item01->parent = representant;

	return representant->index;
}
size_t ufComponentsCount(const UnionFind* union_find){
	return union_find->nbTrees;
}
