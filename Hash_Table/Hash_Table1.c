#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

/* Structure representing a key-value pair */
typedef struct KeyValuePair {
    char *key;
    int value;
} KeyValuePair;

/* Structure representing a node in the hash table */
typedef struct Node {
    KeyValuePair *pair;
    struct Node *next;
} Node;

/* Structure representing the hash table */
typedef struct HashTable {
    Node *buckets[TABLE_SIZE];
} HashTable;

/* Hash function */
unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key++;
    }
    return hash % TABLE_SIZE;
}

/* Initialize hash table */
int i;
	HashTable* create_hash_table() {
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    if (table) {
        for (i = 0; i < TABLE_SIZE; i++) {
            table->buckets[i] = NULL;
        }
    }
    return table;
}

/* Insert key-value pair into hash table */
void insert(HashTable *table, const char *key, int value) {
    unsigned int index = hash(key);
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node) {
        new_node->pair = (KeyValuePair*)malloc(sizeof(KeyValuePair));
        if (new_node->pair) {
            new_node->pair->key = strdup(key);
            new_node->pair->value = value;
            new_node->next = table->buckets[index];
            table->buckets[index] = new_node;
        }
    }
}

/* Get value associated with key */
int get(HashTable *table, const char *key) {
    unsigned int index = hash(key);
    Node *current = table->buckets[index];
    while (current) {
        if (strcmp(current->pair->key, key) == 0) {
            return current->pair->value;
        }
        current = current->next;
    }
    return -1; /* Key not found */
}

/* Main function */
int main() {
    HashTable *table = create_hash_table();
    char key[100];
    int value;

    while (1) {
        printf("Enter key (or 'quit' to exit): ");
        scanf("%s", key);
        if (strcmp(key, "quit") == 0) {
            break;
        }

        printf("Enter value: ");
        scanf("%d", &value);

        insert(table, key, value);
    }

    /* Retrieve values */
    printf("\nKey-Value pairs in hash table:\n");
    for (i = 0; i < TABLE_SIZE; i++) {
        Node *current = table->buckets[i];
        while (current) {
            printf("Key: %s, Value: %d\n", current->pair->key, current->pair->value);
            current = current->next;
        }
    }

    return 0;
}
