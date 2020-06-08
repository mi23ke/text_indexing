#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int set_indx (char*, int*);   //function to set word indexes in index array
void sort_fntn(char *, int *,int a);   //function to sort words indirectly
void print_fntn (char*, int*, int a);   //function to print data
void srch_fntn (char*, int*, char*, int a);  //search function

int main()
{
   char inputTxt [10000];   //array to hold text input
   //char singleWrd [100];   //array to hold a single word
   int indxArry [1000];     //array to hold word indexes for sorting
   char srch_wrd[100];
   int wrd_cnt;              //variable to hold the number of words found
   char * a;
   int * b;
   a = inputTxt;
   b = indxArry;
   printf ("Please enter the text: ");   //prompt for user to enter text
   scanf("%[^\n]s", inputTxt);           //storing input in char array
   wrd_cnt = set_indx(a, b);             //computing number of words
   printf("Words and indexes: %d\n", wrd_cnt);
   print_fntn(a, b, wrd_cnt);           //print data presorted
   sort_fntn(a, b, wrd_cnt);            //sorting data
   printf("The sorted data:\n");
   print_fntn(a, b, wrd_cnt);            //printing sorted data
   printf("Binary Search, ------ Enter words to search for, stop with -1:\n");
   int x = 1;
   char exit[] = ("-1");
   while (x == 1)
   {
     getchar();           //clearing input buffer
     scanf("%[^\n]s", srch_wrd);     //reading word to search
     if (!strcmp(exit,srch_wrd))     //checking input string for exit value of -1
        break;                      //entering exit command if user enters -1
     srch_fntn (a, b, srch_wrd, wrd_cnt);      //calling search function
   }
   return 0;
}
int set_indx (char* input , int* indexes)    //function used to set word indexes
{
   int i = 0, j = 0, wrd_count = 0;
   do
   {
      if (input[i] == '\0')                   //checking input for empty string
         break;
      if ((input[i] != ' ') && (input[i] != '\n'))
      {                                                //looking for first character
         indexes[j] = i;                              //if char found, save index
         wrd_count = wrd_count + 1;                   //counting number of words
         j++;
         i++;
         while ((input[i] != ' ') && (input[i] != '\n'))     //moving along 1 word to next word
            i++;
      }
      else
         i++;
   }while (input[i] != '\n');       //keep loop going until new line char is found
   return wrd_count;
}

void sort_fntn(char* input, int* indexes,int c)    //indirect insertion sort
{
   int i, j, temp;
   char key[100], sub[100];      //temp arrays for coparing words
   for (j = 1; j < c; j++)
   {
      i = j - 1;
      sscanf(&input[indexes[i]], "%s", sub);   //first word to compare
      sscanf(&input[indexes[j]], "%s", key);  //second word to compare
      int cmpr = strcasecmp(key,sub);       //making initial comparison
      while ((i >= 0) && (cmpr < 0))
      {
        temp = indexes[i+1];
        indexes[i+1] = indexes[i];             //comparing the rest of the words
        indexes[i] = temp;
        i = i -1;
        if(i>=0){
          sscanf(&input[indexes[i]], "%s",sub);
          cmpr = strcasecmp(key, sub); }
      }
   }
}
void print_fntn(char* input, int* indexes, int c)      //function to print data
{
   printf("  i |index[i]|  word\n");
   printf("----|--------|--------------\n");           //printing data header
   int i, j, k, l;
   for (i = 0; i < c; i++)
   {
      char temp[100];      //temp array to print string with lowercase letters and special chars removed
      j = indexes[i];      //setting j to beginning of each word
      k = 0;
      sscanf(&input[indexes[i]], "%s", temp); //scanning one word at a time
      for (l = 0; l<strlen(temp);l++)
      {
         if (!(isdigit(temp[l])) && !(isalpha(temp[l])))
            temp[l] = '\0';        //removing special characters
         else
            temp[l] = tolower(temp[l]);
      }     //setting each letter to lower case if needed
      printf("%4d|%8d|  %s\n", i, indexes[i], temp);   //printing i, index and word
   }
   printf("\n\n");
}
void srch_fntn(char* input, int* indexes, char* sw, int c)
{
   int left = 0, right = c - 1, m, l, iteration = 1;  //setting left to first word and right to last word
   char temp1[100];                                  //variable to hold middle word
   printf("(Original: %s)\n", sw);
   while (left <= right)                             //binary search
   {
      m = (left+right)/2;
      sscanf(&input[indexes[m]], "%s", temp1);
      for (l = 0; l<strlen(sw); l++)
      {
         if (!(isdigit(sw[l])) && !(isalpha(sw[l])))     //cleaning up the search word
            sw[l] = '\0';
         else
            sw[l] = tolower(sw[l]);
      }
      for (l = 0; l<strlen(temp1); l++)
      {
         if (!(isdigit(temp1[l])) && !(isalpha(temp1[l])))    //cleaning up word to compare to search word
            temp1[l] = '\0';
         else
            temp1[l] = tolower(temp1[l]);
      }
      if (strcmp(temp1, sw) == 0)         //for when a match is found
      {
         printf("Cleaned: %s - found (%d iterations)\n", sw, iteration);
         break;
      }
      if (strcmp(temp1, sw) < 0)
         left = m+1;
      else
         right = m-1;
      iteration++;
   }
   if (strcmp(temp1, sw) != 0)
      printf("Cleaned: %s - not found (%d iterations)\n", sw, iteration-1);    //print when word is not found
}
