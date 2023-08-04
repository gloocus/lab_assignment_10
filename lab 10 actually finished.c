#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET 26
#define BUFF 1024

// Trie structure
struct Trie
{	
    struct Trie *children[ALPHABET];
    int count;
};
// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *tmp = malloc(sizeof(struct Trie));
    for(int i = 0; i < ALPHABET; i++){
        tmp -> children[i] = NULL;
    }
    tmp -> count = 0;
    return tmp;

}
// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int len = strlen(word), i = 0;
    struct Trie *tmp = pTrie;
    for(i = 0; i < len; i++){
        if(tmp -> children[word[i] - 'a'] == NULL)
            tmp -> children[word[i] - 'a'] = createTrie();
        tmp = tmp -> children[word[i] - 'a'];
    }
    tmp -> count++;
    return;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* curr = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            return 0;
        }
        curr = curr->children[index];
    }
    return curr->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL) {
            return NULL;
    }
    for (int i = 0; i < ALPHABET; i++) {
        if (pTrie->children[i] != NULL) {
            deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *fp = fopen(filename, "r");
    int dataSz = 0, i = 0;
    char tmp[BUFF];
    if(fp != NULL){
        fscanf(fp, "%d\n", &dataSz);
        while(fscanf(fp, "%s", tmp) != EOF){
            pInWords[i] = malloc(strlen(tmp) + 1);
            strcpy(pInWords[i], tmp);
            i++;
        }
    }
    fclose(fp);
    return dataSz;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}