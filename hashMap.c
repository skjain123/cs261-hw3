#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>
#include <assert.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{  
	/*write this*/

	struct hashLink* current;
	struct hashLink* next;

	int i;
	
	for (i = 0; i < ht->tableSize; i++) {

		if (ht->table[i] != NULL) {
			current = ht->table[i];

			while (current != NULL) {
				next = current->next;
				free(current);
				current = next;	
			}

			next = current;
			free(next);
		}
	}

	free(ht->table);
	ht->count=0;
	ht->table=0;
	ht->tableSize=0;
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/

	int index = (int) abs(stringHash1(k)) % ht->tableSize;

	struct hashLink* new = (struct hashLink*) malloc(sizeof(struct hashLink));
	assert(new);

	new->key = k;
	new->value = v;
	new->next = ht->table[index];

	ht->table[index] = new;

	ht->count++;
}

ValueType* atMap (struct hashMap * ht, KeyType k)
{ /*write this?*/
	
	int index = (int) abs(stringHash1(k)) % ht->tableSize;

	ValueType* at = &(ht->table[index]->value);
	return at;

}

int containsKey (struct hashMap * ht, KeyType k)
{  /*write this*/
	int index = (int) abs(stringHash1(k)) % ht->tableSize;

	return (int)(ht->table[index] != NULL);
}

void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/
	
	int index = (int) abs(stringHash1(k)) % ht->tableSize;
	
	struct hashLink *current;
	struct hashLink *t;

	current = ht->table[index];
	t = ht->table[index];

	while(current != NULL) {
		t = current->next;
		free(current);	
		ht->count--;
		current = t;
	}

	t = current;
	free(t);
	ht->count--;
	ht->tableSize--;

}

int sizeMap (struct hashMap *ht)
{  /*write this*/
	return ht->count;
}

int capacityMap(struct hashMap *ht)
{  /*write this*/
	return ht->tableSize;
}

int emptyBuckets(struct hashMap *ht)
{  /*write this*/

	int i;
	int counter = 0;

	for (i = 0; i < ht->tableSize; i++) {
		if (ht->table[i] != NULL) {
			counter++;
		}
	}

	return counter;
}

float tableLoad(struct hashMap *ht)
{  /*write this*/
	return (float) sizeMap(ht) / (float) capacityMap(ht);
}
