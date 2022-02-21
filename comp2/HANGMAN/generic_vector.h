#ifndef GENERIC_VECTOR_H
#define GENEREIC_VECTOR_H

#include "status.h"
#include "generic.h"

typedef void* GENERIC_VECTOR;

GENERIC_VECTOR generic_vector_init_default(
	Status(*item_assignment)(ITEM* pLeft, ITEM right),
	void (*item_destroy)(ITEM* phItem)); 


Status generic_vector_push_back(GENERIC_VECTOR hVector, ITEM value);

int generic_vector_get_size(GENERIC_VECTOR hVector);
int generic_vector_get_capacity(GENERIC_VECTOR hVector);

ITEM generic_vector_at(GENERIC_VECTOR hVector, int index);

Status generic_vector_pop_back(GENERIC_VECTOR hVector);
Boolean generic_vector_empty(GENERIC_VECTOR hVector);


void generic_vector_destroy(GENERIC_VECTOR* phVector);
#endif
