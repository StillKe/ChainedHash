#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
	HashTable *createHashTable() {
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
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
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode) {
        newNode->pair = (KeyValuePair *)malloc(sizeof(KeyValuePair));
        if (newNode->pair) {
            newNode->pair->key = strdup(key);
            newNode->pair->value = value;
            newNode->next = NULL;

           
            if (table->buckets[index] == NULL) {
                table->buckets[index] = newNode;
            } else {
               
                Node *current = table->buckets[index];
                while (current->next) {
                    current = current->next;
                }
                current->next = newNode;
            }
        }
    }
}

/* Get value associated with key */
int getValue(HashTable *table, const char *key) {
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
    HashTable *table = createHashTable();
    char input[100];
    char key[100];
    char *endPtr;
    long value;

    while (1) {
        printf("Enter key (or 'quit' to exit): ");
        if (!fgets(input, sizeof(input), stdin) || strcmp(input, "quit\n") == 0) {
            break;
        }

       
        if (sscanf(input, "%s", key) != 1) {
            break;
        }

        printf("Enter value: ");
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }

  
        errno = 0;
        value = strtol(input, &endPtr, 10);
        if (errno != 0 || *endPtr != '\n') {
            printf("Invalid value format. Please enter an integer.\n");
            continue;
        }

        insert(table, key, (int)value);
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

    /* Free memory */
    for (i = 0; i < TABLE_SIZE; i++) {
        Node *current = table->buckets[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp->pair->key);
            free(temp->pair);
            free(temp);
        }
    }
    free(table);

    return 0;
}
