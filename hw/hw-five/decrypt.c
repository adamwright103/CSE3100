#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>

#define MAX 10240
#define MAX_WORD_COUNT 60000 // we have less than 60000 words
#define MAX_WORD_LENGTH 80   // each word is less than 80 letters

// Using these two global variables can be justified :)
char words[MAX_WORD_COUNT][MAX_WORD_LENGTH]; // 2-d array to hold all the words
int word_count = 0;                          // number of words, initilized to 0

// Note the words in the dictionary file are sorted
// This fact could be useful
void read_file_to_array(char *filename)
{
  FILE *fp;

  // open the file for reading
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Cannot open file %s.\n", filename);
    exit(-1);
  }
  // make sure when each word is saved in the array words,
  // it does not ends with a '\n'
  // see how this is done using fscanf
  while (!feof(fp))
    fscanf(fp, "%s\n", words[word_count++]);
  fclose(fp);
}

// TODO
// Test wether a string word is in the dictionary
// Return 1 if word is in the dictionary
// Return 0 otherwise
// Be efficient in implementing this function
// Efficiency is needed to pass test cases in limited time
int in_dict(char *word)
{
  // have a pointer at start and end
  // move pointers based on word at middle of 2 ptrs
  int left = 0;
  int right = word_count - 1;

  while (left <= right)
  {
    int mid = left + (right - left) / 2;
    int cmp = strcmp(word, words[mid]);

    if (cmp == 0)
    {
      return 1; // Word found
    }
    else if (cmp < 0)
    {
      // if the first non-matching character in str1 is greater (in ASCII) than that of str2
      right = mid - 1;
    }
    else
    {
      // if the first non-matching character in str1 is lower (in ASCII) than that of str2
      left = mid + 1;
    }
  }

  // Word not found
  return 0;
}

// TODO
// Use key and shift to decrypt the encrypted message
// len is the length of the encrypted message
// Note the encrypted message is stored as an array of integers (not chars)
// The result is in decrypted

void decryption(unsigned char key, unsigned char shift, const int *encrypted, int len, char *decrypted)
{
  for (int i = 0; i < len / sizeof(int); i++)
  {
    decrypted[i] = (encrypted[i] ^ key) >> shift;
  }
  decrypted[len] = '\0';
}

// TODO
// calculate a score for a message msg
// the score is used to determine whether msg is the original message
int message_score(const char *msg)
{
  // calculates the number of words in the message that are in the dictionary
  int score = 0;
  char *word;
  char copy[MAX];
  strcpy(copy, msg);

  // strtok takes a 'token' of msg based on the delim
  word = strtok(copy, " ");

  // itterate over all words in message and check if they are in the dictionary
  while (word != NULL)
  {
    if (in_dict(word))
    {
      score++;
    }

    word = strtok(NULL, " ");
  }

  return score;
}

// search using all the (key, shift) combinations
// to find the original message
// result is saved in message
void search(const int *encrypted, int len, char *message)
{
  char decrypted[MAX];

  int max_score = 0;
  strcpy(message, "");
  for (unsigned char k = 0; k < 255; k++)
  {
    for (unsigned char shift = 0; shift <= 24; shift++)
    {
      decryption(k, shift, encrypted, len, decrypted);
      int score = message_score(decrypted);
      if (score > max_score)
      {
        max_score = score;
        strcpy(message, decrypted);
      }
    }
  }
}

// TODO
// read the encrypted message from the file to encrypted
// return number of bytes read
int read_encrypted(char *filename, int *encrypted)
{
  int f = open(filename, O_RDONLY);
  if (f < 0)
  {
    perror("Cannot open encrypted file");
    return -1;
  }

  int bytes = read(f, encrypted, (MAX - 1) * sizeof(int));
  if (bytes < 0)
  {
    perror("Error reading file");
    close(f);
    return -1;
  }

  close(f);
  return bytes;
}

// Do not change the main() function
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("%s encrypted-message\n", argv[0]);
    return 0;
  }

  read_file_to_array("dict.txt");

  int encrypted[MAX];
  int len = read_encrypted(argv[1], encrypted);

  char message[MAX];
  strcpy(message, "");
  search(encrypted, len, message);
  printf("%s\n", message);
  return 0;
}