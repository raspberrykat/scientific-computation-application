#include <stdio.h> // memasukan standard input-output library
#include <string.h> // memasukan string library
#include <stdlib.h> // memasukkan standard library untuk memory allocation

#define ALPHABET_SIZE 26 // menentukan size alphabet, yaitu dengan value 26
#define MAX_WORD 101 // menentukan panjang maksimal suatu kata, yaitu dengan value 101
#define MAX_DESC 1001 // menentukan panjang maksimal suatu deskripsi slang, yaitu dengan value 1001

struct node{ // membuat struct node dalam trie
    struct node *children[ALPHABET_SIZE]; // pointer yang mewakili node child dalam trie
    char *description; // pointer yang menyimpan deskripsi slang
    int end; //varible untuk menentukan akhir dari sebuah kata (mengeluarkan output dalam bentuk 0 dan 1)
};

void struct node *createNode{
    struct node *newNode = NULL;
	newNode = (struct node *)malloc(sizeof(struct node));

    if (newNode){
        newNode->end = 0;

        for (int i = 0; i < ALPHABET_SIZE; i++){
            newNode->children[i] = NULL;
        }
        newNode->description = NULL;
    }

    return newNode;
}

void lowerCase(char *word){
    for (int i = 0; word[i]; i++){
        if (word[i] >= 'A' && word[i] <= 'Z'){
            word[i] = word[i] + 32;
        }
    }
}

void insert(struct node *root, const char *key, const char *desc){
    int level;
    int length = strlen(key);
    int index;

    struct node *trie = root;

    for (level = 0; level < length; level++){
        index = key[level] - 'a';
        if (!trie->children[index]) {
            trie->children[index] = createNode();
        }
        trie = trie->children[index];
    }

    if (trie->end){
        // word exists (update desc)
        if (trie->description){
            free(trie->description);	
		}
		
        trie->description = (char *)malloc(strlen(desc) + 1);
        strcpy(trie->description, desc);
        printf("Successfully updated a slang word.\n");
    }
	else{
        // word doesnt exist
        trie->end = 1;
        
        if (trie->description){
        	free (trie->description);
		}
		
        trie->description = (char *)malloc(strlen(desc) + 1);
        strcpy(trie->description, desc);
        printf("Successfully released new slang word.\n");
    }
}

void search(struct node *root, const char *key){
    int level;
    int length = strlen(key);
    int index;
    struct node *trie = root;

    for (level = 0; level < length; level++){
        index = key[level] - 'a';
        if (!trie->children[index]){
            printf("There is no word \"%s\" in the dictionary.\n", key);
            return;
        }
        trie = trie->children[index];
    }

    if (trie != NULL && trie->end){
        printf("Slang word	: %s\n", key);
        printf("Description	: %s\n", trie->description);
    }
	else{
        printf("There is no word \"%s\" in the dictionary.\n", key);
    }
}

void printPrefix(node *newNode, char *prefix, char *temp, int depth, int *count){
	if (newNode->end){
        temp[depth] = NULL;
        printf("%d. %s%s\n", ++(*count), prefix, temp);
    }
    
    for (int i = 0; i < ALPHABET_SIZE; i++){
        if (newNode->children[i] != NULL){
            temp[depth] = i + 'a';
            printPrefix(newNode->children[i], prefix, temp, depth + 1, count);
        }
    }
}

void viewPrefix(node *root){
    char prefix[MAX_WORD];
    
    printf("Input a prefix to be searched: ");
    scanf("%s", prefix);
    
    node* curr = root;
    
    for (int i = 0; i < strlen(prefix); i++){
        int index = prefix[i] - 'a';
        if (!curr->children[index]){
            printf("There is no prefix \"%s\" in the dictionary.\n", prefix); puts("");
            return;
        }
        curr = curr->children[index];
    }
    
    printf("Words starts with \"%s\":\n", prefix);
    
    char temp[MAX_WORD];
    int count = 0;
    
    printPrefix(curr, prefix, temp, 0, &count);
    puts("");
}

void viewAll(node *root, char *temp, int depth, int *count){
    if (root == NULL){
        printf ("There is no slang word yet in the dictionary.\n");
		return;
	}
	
    if (root->end){
        temp[depth] = '\0';
        printf("%d. %s\n", ++(*count), temp);
    }
    
    for (int i = 0; i < ALPHABET_SIZE; i++){
        if (root->children[i] != NULL){
            temp[depth] = i + 'a';
            viewAll(root->children[i], temp, depth + 1, count);
        }
    }
}

int validateSlang(const char *slang){
    int len = strlen(slang);

    if (len <= 1){
        return 0;
    }

    for (int i = 0; i < len; i++){
        if (slang[i] == ' ') {
            return 0;
        }
    }

    return 1;
}

int validateDescription(const char *description){
    int len = strlen(description);
    int wordCount = 0;

    for (int i = 0; i < len; i++){
        if (description[i] == ' '){
            wordCount++;
        }
    }
    
    if (wordCount == 0){
    	return 0;
	}
    else if (wordCount >= 1){
    	return 1;
	}
}

int main(){
    struct node *root = createNode();
    int choice;
    char word[MAX_WORD];
    char desc[MAX_DESC];

    while (1){
        printf("1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix word\n");
        printf("4. View all slang words\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
		
        if (choice == 1){
            printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
            scanf("%s", word);
            while (validateSlang(word) == 0){
                printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
                scanf("%s", word);
            }
            
            printf("Input a new slang word description [Must be more than 2 words]: ");
            scanf(" %[^\n]s", desc);
            while (strlen(desc) <= 1 || validateDescription(desc) == 0){
           		printf("Input a new slang word description [Must be more than 2 words]: ");
            	scanf(" %[^\n]s", desc);
            }
                
            insert(root, word, desc);
            printf("Press enter to continue...\n"); getchar(); getchar();
  		}
        else if (choice == 2){
        	printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
            scanf("%s", word);
            while (validateSlang(word) == 0){
                printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
                scanf("%s", word);
            }
                
            search(root, word);
			printf("Press enter to continue...\n"); getchar(); getchar();
		}    
		else if (choice == 3){
			viewPrefix(root);
			printf("Press enter to continue...\n"); getchar(); getchar();
		}
		else if (choice == 4){
			char temp[MAX_WORD];
			int count = 0;
			
			printf ("List of all slang words in the dictionary:\n");
			viewAll(root, temp, 0, &count);
			printf("Press enter to continue...\n"); getchar(); getchar();
		}
		else if (choice == 5){
			printf("Thank you... Have a nice day :)\n");
            exit(0);
		}
        else{
        	printf("Invalid choice!\n");
		}
	}

    return 0;
}

