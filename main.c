#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Linked List node
struct node
{
   char* key;            // key is string
   char* value;          // value is also string
   struct node* next;
};
// Function to initialize a node
void setNode(struct node* node, char* key, char* value)
{
   node->key = strdup(key);    // strdup() to duplicate string
   node->value = strdup(value);
   node->next = NULL;
}
// Structure for hash map
struct hashMap
{
   int numOfElements;         // Current number of elements in hashMap
   int capacity;              // Capacity of hashMap
   struct node** arr;         // Array of linked lists
};
// Function to initialize hash map
void initializeHashMap(struct hashMap* mp)
{
   mp->capacity = 100;        // Default capacity
   mp->numOfElements = 0;
   mp->arr = (struct node**)malloc(sizeof(struct node*) * mp->capacity);
   for (int i = 0; i < mp->capacity; i++)
   {
       mp->arr[i] = NULL;
   }
}
// Hash function
int hashFunction(struct hashMap* mp, char* key)
{
   int sum = 0;
   int factor = 31;
   for (int i = 0; i < strlen(key); i++)
   {
       sum = ((sum % mp->capacity) + (((int)key[i]) * factor) % mp->capacity) % mp->capacity;
       factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
   }
   return sum;
}
// Function to insert key-value pair into hash map
void insert(struct hashMap* mp, char* key, char* value)
{
   int bucketIndex = hashFunction(mp, key);
   struct node* newNode = (struct node*)malloc(sizeof(struct node));
   setNode(newNode, key, value);
   if (mp->arr[bucketIndex] == NULL)
   {
       mp->arr[bucketIndex] = newNode;
   }
   else
   {
       newNode->next = mp->arr[bucketIndex];
       mp->arr[bucketIndex] = newNode;
   }
   mp->numOfElements++;
}
// Function to delete key from hash map
void delete (struct hashMap* mp, char* key)
{
   int bucketIndex = hashFunction(mp, key);
   struct node* prevNode = NULL;
   struct node* currNode = mp->arr[bucketIndex];
   while (currNode != NULL)
   {
       if (strcmp(key, currNode->key) == 0)
       {
           if (prevNode == NULL)
           {
               mp->arr[bucketIndex] = currNode->next;
           }
           else
           {
               prevNode->next = currNode->next;
           }
           free(currNode->key);
           free(currNode->value);
           free(currNode);
           mp->numOfElements--;
           return;
       }
       prevNode = currNode;
       currNode = currNode->next;
   }
}
// Function to search for key in hash map
char* search(struct hashMap* mp, char* key)
{
   int bucketIndex = hashFunction(mp, key);
   struct node* bucketHead = mp->arr[bucketIndex];
   while (bucketHead != NULL)
   {
       if (strcmp(key, bucketHead->key) == 0)
       {
           return bucketHead->value;
       }
       bucketHead = bucketHead->next;
   }
   // If key not found
   return "Oops! No data found.\n";
}
// Main function
int main()
{
   // Initialize hash map
   struct hashMap* mp = (struct hashMap*)malloc(sizeof(struct hashMap));
   initializeHashMap(mp);
   // Inserting key-value pairs
   insert(mp, "Yogaholic", "Anjali");
   insert(mp, "pluto14", "Vartika");
   insert(mp, "elite_Programmer", "Manish");
   insert(mp, "GFG", "BITS");
   insert(mp, "decentBoy", "Mayank");
   // Searching and printing values
   printf("%s\n", search(mp, "elite_Programmer"));
   printf("%s\n", search(mp, "Yogaholic"));
   printf("%s\n", search(mp, "pluto14"));
   printf("%s\n", search(mp, "decentBoy"));
   printf("%s\n", search(mp, "GFG"));
   // Key not inserted
   printf("%s\n", search(mp, "randomKey"));
   // Deleting a key
   printf("\nAfter deletion : \n");
   delete (mp, "decentBoy");
   printf("%s\n", search(mp, "decentBoy"));
   return 0;
}