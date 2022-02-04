#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

//struct
typedef struct node Node;

struct node{
Node* parent;
Node* left;
Node* right;
MY_STRING hKey;
GENERIC_VECTOR hVector;
int depth_left;
int depth_right;
};

//internal function declarations
Status node_add_words(Node* parent, MY_STRING key, MY_STRING word);
void balance_factor_add_one(Node* pNode);
Node* rebalance (Node* pNode);
Node* shift_left (Node* pNode);
Node* shift_right (Node* pNode);
void tree_print (Node* pNode, int i);
Node* max_node (Node* pNode, int max);
//function definitions
TREE tree_init_default(void)
{
	Node* pNode = (Node*)malloc(sizeof(Node));
	if(malloc != NULL)
	{
		pNode->parent = NULL;
		pNode->left = NULL;
		pNode->right = NULL;
		pNode->hKey = NULL;
		pNode->depth_left=0;
		pNode->depth_right=0;
		pNode->hVector = generic_vector_init_default(my_string_assignment,my_string_destroy);
		if(pNode->hVector != NULL)
		{
			return (TREE)pNode;
		}
		free(pNode);
	}
	return NULL;
}
Status tree_add_words(GENERIC_VECTOR hVector, TREE* phTree, MY_STRING old_key, char guess)
{
	MY_STRING temp = NULL;
	MY_STRING temp_key = NULL;
	Node* pTree = (Node*)*phTree;
	if(pTree->hKey != NULL)
	{
		tree_destroy((TREE)&(pTree->left));
		tree_destroy((TREE)&(pTree->right));
		pTree->depth_left = 0;
		pTree->depth_right = 0;
		while(generic_vector_pop_back(pTree->hVector));
		my_string_destroy(&(pTree->hKey));
	}
	int i=0;
	while(!generic_vector_empty(hVector))
	{
		my_string_assignment(&temp, generic_vector_at(hVector,generic_vector_get_size(hVector)-1));
		generic_vector_pop_back(hVector);
	//	printf("Word Added %s\n",my_string_c_str(temp));
		temp_key = my_string_init_default();
		if(!get_word_key_value(old_key, temp_key, temp, guess))
		{
			printf("ERROR in get word key value\n");
			return FAILURE;
		}
	//	printf("The key is %s\n",my_string_c_str(temp_key));
		if(!node_add_words(pTree,temp_key,temp))
		{
			printf("ERROR in adding word\n");
			return FAILURE;
		}
		pTree = rebalance(pTree);
		//tree_print(pTree,0);
		*phTree = (TREE)pTree;
		i++;
	}
	my_string_destroy(&temp);
	//tree_print(pTree,0);
	return SUCCESS;
}
MY_STRING tree_key_find(TREE hTree, GENERIC_VECTOR hVector)
{
	Node* pNode = (Node*)hTree;
	pNode = max_node(pNode, generic_vector_get_size(pNode->hVector));
	while(!generic_vector_empty(pNode->hVector))
	{
		generic_vector_push_back(hVector,generic_vector_at(pNode->hVector,generic_vector_get_size(pNode->hVector)-1));
		generic_vector_pop_back(pNode->hVector);	
	}
	return pNode->hKey;
}
Node* max_node (Node* pNode, int max)
{
	Node* max_node_left = NULL;
       	Node* max_node_right = NULL;
	Node* biggest_node;
	if(pNode->left != NULL) max_node_left = max_node(pNode->left, max);
	if(pNode->right != NULL) max_node_right = max_node(pNode->right, max);
	if(max_node_left != NULL)
	{
		if(max_node_right != NULL)
		{
			if(generic_vector_get_size(max_node_left->hVector) > generic_vector_get_size(max_node_right->hVector)) biggest_node = max_node_left;
			else biggest_node = max_node_right;
			return (generic_vector_get_size(biggest_node->hVector) > max) ? biggest_node : pNode;
		}
		else
		{
			biggest_node = max_node_left;
			return (generic_vector_get_size(biggest_node->hVector) > max) ? biggest_node : pNode;
		}
	}
 	else if(max_node_right != NULL)
	{
		biggest_node = max_node_right;
		return (generic_vector_get_size(biggest_node->hVector) > max) ? biggest_node : pNode;
	}
	return pNode;
}
void tree_destroy(TREE* phTree)
{
	Node* pNode = (Node*)*phTree;
	if(pNode == NULL) return;
	tree_destroy((TREE*)&(pNode->left));
	tree_destroy((TREE*)&(pNode->right));
	if(pNode->hVector != NULL) generic_vector_destroy(&(pNode->hVector));
	if(pNode->hVector != NULL)
	{
		printf("Error in destroying Vector\n");
		exit(1);
	}
	if(pNode->hKey != NULL)my_string_destroy(&(pNode->hKey));
	if(pNode->hKey != NULL)
	{
		printf("Error in destroying String\n");
		exit(2);
	}
	free(pNode);
	*phTree = NULL;
}
Status node_add_words(Node* parent, MY_STRING key, MY_STRING word)
{
	if(parent->hKey == NULL)
	{
		parent->hKey = key;
		generic_vector_push_back(parent->hVector, word);
		balance_factor_add_one(parent);
		return SUCCESS;
	}
	int compare = my_string_compare(key, parent->hKey);
	if(compare == 0)
	{
		my_string_destroy(&key);
		generic_vector_push_back(parent->hVector, word);
		return SUCCESS;
	}
	if(compare > 0)
	{
		if(parent->right == NULL)
		{
			Node* pRight = (Node*)tree_init_default();
			if(pRight == NULL)
			{
				my_string_destroy(&key);
				return FAILURE;
			}
			pRight->parent = parent;
			parent->right = pRight;
		}
		return node_add_words(parent->right,key,word);
	}
	else
	{
		if(parent->left == NULL)
		{
			Node* pLeft = (Node*)tree_init_default();
			if(pLeft == NULL)
			{
				my_string_destroy(&key);
				return FAILURE;
			}
			pLeft->parent = parent;
			parent->left = pLeft;
		}
		return node_add_words(parent->left,key,word);
	}
}
void balance_factor_add_one(Node* pNode)
{
	if(pNode->parent == NULL) return;
	if(pNode->parent->left == pNode)
	{
		pNode->parent->depth_left++;
		if(pNode->parent->depth_left > pNode->parent->depth_right)
		{
			balance_factor_add_one(pNode->parent);
		}	
	}
	else
	{
		pNode->parent->depth_right++;
		if(pNode->parent->depth_right > pNode->parent->depth_left)
		{
			balance_factor_add_one(pNode->parent);
		}
	}
}
Node* rebalance (Node* pNode)
{
	if(abs(pNode->depth_right - pNode->depth_left) >= 2)
	{
		while(pNode->depth_right - pNode->depth_left >= 2)
		{
			pNode = shift_left(pNode);
		}
		while(pNode->depth_left - pNode->depth_right >= 2)
		{
			pNode = shift_right(pNode);
		}
	}
	if(pNode->left != NULL) pNode->left = rebalance(pNode->left);
	if(pNode->right != NULL) pNode->right = rebalance(pNode->right);
	return pNode;
}
Node* shift_left (Node* pNode)
{
//	printf("SHIFTING LEFT\n");
//	tree_print(pNode,0);
//	printf("\n");
	while(pNode->right->left != NULL && pNode->right->left->hKey != NULL)pNode->right = shift_right(pNode->right);
//	printf("After mid shift\n");
//	tree_print(pNode,0);
	Node* parent = pNode->parent;
	Node* pNode_new = pNode->right;
//	printf("%p\n",pNode_new);
	//find out parent	
	if(parent != NULL)
	{
		if(parent->left == pNode) parent->left = pNode_new;
		else parent->right = pNode_new;
	}
	//pNode update
	pNode->right = NULL;
	pNode->depth_right = 0;
	pNode->parent = pNode_new;
	
	//pNode_new_update
	pNode_new->parent = parent;
	pNode_new->left = pNode;
	pNode_new->depth_left = pNode->depth_left + 1;
//	printf("%p\n",pNode_new);
//	printf("New Tree:\n");
//	tree_print(pNode_new,0);
//	printf("\n");

	return pNode_new;
}
Node* shift_right (Node* pNode)
{
	
//	printf("SHIFTING Right\n");
//	tree_print(pNode,0);
//	printf("\n");
	
	while(pNode->left->right != NULL && pNode->left->right->hKey != NULL)pNode->left=shift_left(pNode->left);
	Node* parent = pNode->parent;
//	printf("After mid shift\n");
//	tree_print(pNode,0);
	Node* pNode_new = pNode->left;
	//find out parent	
	if(parent != NULL)
	{
		if(parent->left == pNode) parent->left = pNode_new;
		else parent->right = pNode_new;
	}
	//pNode update
	pNode->left = NULL;
	pNode->depth_left = 0;
	pNode->parent = pNode_new;
	
	//pNode_new_update
	pNode_new->parent = parent;
	pNode_new->right = pNode;
	pNode_new->depth_right = pNode->depth_right + 1;
	
//	printf("New Tree:\n");
//	tree_print(pNode_new,0);
//	printf("\n");
	
	return pNode_new;
}
void tree_print (Node* pNode, int i)
{
	if(pNode == NULL)
	{
		return;
	}
	int j;
	for(j=0;j<i;j++)
	{
		printf("\t");
	}
	if(pNode->hKey != NULL) printf("%s has %d words with a %d depth right and %d depth left\n",my_string_c_str(pNode->hKey),generic_vector_get_size(pNode->hVector),pNode->depth_right,pNode->depth_left);
	else printf("\n");
	tree_print(pNode->left, i+1);
	tree_print(pNode->right, i+1);
}
