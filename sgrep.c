#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* for skeleton code */
#include <unistd.h> /* for getopt */
#include "str.h"

#define FIND_STR        "-f"
#define REPLACE_STR     "-r"
#define DIFF_STR        "-d"

#define MAX_STR_LEN 1023

#define FALSE 0
#define TRUE  1

typedef enum {
	INVALID,
	FIND,
	REPLACE,
	DIFF
} CommandType;

/*
* Fill out your functions here (If you need)
*/

/*--------------------------------------------------------------------*/
/* PrintUsage()
print out the usage of the Simple Grep Program                     */
/*--------------------------------------------------------------------*/
void
PrintUsage(const char* argv0)
{
  const static char *fmt =
    "Simple Grep (sgrep) Usage:\n"
    "%s [COMMAND] [OPTIONS]...\n"
    "\nCOMMNAD\n"
    "\tFind: -f [search-string]\n"
    "\tReplace: -r [string1] [string2]\n"
    "\tDiff: -d [file1] [file2]\n";
  
  printf(fmt, argv0);
}
/*-------------------------------------------------------------------*/
/* DoFind()
Your task:
1. Do argument validation
- String or file argument length is no more than 1023
- If you encounter a command-line argument that's too long,
print out "Error: argument is too long"

2. Read the each line from standard input (stdin)
- If you encounter a line larger than 1023 bytes,
print out "Error: input line is too long"
- Error message should be printed out to standard error (stderr)

3. Check & print out the line contains a given string (search-string)

Tips:
- fgets() is an useful function to read characters from file. Note
that the fget() reads until newline or the end-of-file is reached.
- fprintf(sderr, ...) should be useful for printing out error
message to standard error

NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int
DoFind(const char *pcSearch)
{
  char buf[MAX_STR_LEN + 2];
  int len;
  int lenarg = StrGetLength(pcSearch);
  
  if ((lenarg > MAX_STR_LEN))
    {
      fprintf(stderr, "Error: argument is too long\n");
      return FALSE;
    }
  /* Read the line by line from stdin*/
  while (fgets(buf, sizeof(buf), stdin)) {
    /* check input line length and prints error if its too long*/
    if ((len = StrGetLength(buf)) > MAX_STR_LEN) {
      fprintf(stderr, "Error: input line is too long\n");
      return FALSE;
    }
    if (StrSearch(buf, pcSearch))
      fprintf(stdout,"%s", buf);
    /* if designated string exists in the line, print the string line*/
    
  }
  
  return TRUE;
}
/*-------------------------------------------------------------------*/
/* DoReplace()
   Your task:
   1. Do argument validation
   - String length is no more than 1023
- If you encounter a command-line argument that's too long,
print out "Error: argument is too long"
- If word1 is an empty string,
print out "Error: Can't replace an empty substring"

2. Read the each line from standard input (stdin)
- If you encounter a line larger than 1023 bytes,
print out "Error: input line is too long"
- Error message should be printed out to standard error (stderr)

3. Replace the string and print out the replaced string

NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int
DoReplace(const char *pcString1, const char *pcString2)
{
  char buf[MAX_STR_LEN + 2];
  int len;
  int lenstr1 = StrGetLength(pcString1);
  int lenstr2 = StrGetLength(pcString2);
  /* returns error if the length of the argument is longer than MAX_STR_LEN*/
  if ((lenstr1 > MAX_STR_LEN) || (lenstr2 > MAX_STR_LEN))
    {
      fprintf(stderr, "Error: argument is too long\n");
      return FALSE;
    }
  /* returns error if and empty string is an input for replacement*/
  if (lenstr1 == 0)
    {
      fprintf(stderr, "Error: Can't replace an empty substring\n");
      return FALSE;
    }
  /* Read the line by line from stdin*/
  while (fgets(buf, sizeof(buf), stdin)) {
    if ((len = StrGetLength(buf)) > MAX_STR_LEN) {
      fprintf(stderr, "Error: input line is too long\n");
      return FALSE;
      /* check input line length and prints error if its too long*/
    }
    size_t lenstr1 = StrGetLength(pcString1);
    size_t lenstr2 = StrGetLength(pcString2);
    char * position = buf;
    char temp[MAX_STR_LEN + 2];
    
    while (StrSearch(position, pcString1)) /* keep on searching if string from the current position contains pcString1*/
      {
	position = StrSearch(position, pcString1); /*move on to the position where the string to be replaced is poisitioned*/
	StrCopy(temp, position + lenstr1);
	StrCopy(position, pcString2);
	StrCopy(position+lenstr2, temp);
	/*copy the strings past the string to be replaced and paste it after replacing the string*/
      }
    fprintf(stdout, "%s", buf);
    /*print the string(if it is replaced, print the replaced string)*/
  }
  
  return TRUE;
}
/*-------------------------------------------------------------------*/
/* DoDiff()
   Your task:
1. Do argument validation
- file name length is no more than 1023
- If a command-line argument is too long,
print out "Error: arugment is too long" to stderr

2. Open the two files
- The name of files are given by two parameters
- If you fail to open either file, print out error messsage
- Error message: "Error: failed to open file [filename]\n"
- Error message should be printed out to stderr

3. Read the each line from each file
- If you encounter a line larger than 1023 bytes,
print out "Error: input line [filename] is too long"
- Error message should be printed out to stderr

4. Compare the two files (file1, file2) line by line

5. Print out any different line with the following format
file1@linenumber:file1's line
file2@linenumber:file2's line

6. If one of the files ends earlier than the other, print out an
error message "Error: [filename] ends early at line XX", where
XX is the final line number of [filename].

NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int
DoDiff(const char *file1, const char *file2)
{
  int len;
  int lenarg1 = StrGetLength(file1);
  int lenarg2 = StrGetLength(file2);
  FILE *fp1 = NULL;
  FILE *fp2 = NULL;
  
  if ((lenarg1 > MAX_STR_LEN || lenarg2>MAX_STR_LEN))
    {
      fprintf(stderr, "Error: argument is too long\n");
      return FALSE;
    }
  if ((fp1 = fopen(file1, "r")) == NULL)
    {
      fprintf(stderr, "Error: failed to open file %s \n", file1);
      return FALSE;
    }
  /*print error if we fail to open the first file*/
  if ((fp2 = fopen(file2, "r")) == NULL)
    {
      fprintf(stderr, "Error: failed to open file %s \n", file2);
      return FALSE;
    }
  /*print error if we fail to open the second file*/
  char buf1[MAX_STR_LEN + 2];
  char buf2[MAX_STR_LEN + 2];
  int num = 1;
  while (fgets(buf1, sizeof(buf1), fp1) && fgets(buf2, sizeof(buf2), fp2)) {
    /* Read each file the line by line*/
    if ((len = StrGetLength(buf1)) > MAX_STR_LEN) {
      fprintf(stderr, "Error: input line %s is too long\n", file1);
      return FALSE;
    }
    /* returns error if the length of the line inside file1 is longer than MAX_STR_LEN*/
    else if ((len = StrGetLength(buf2)) > MAX_STR_LEN) {
      fprintf(stderr, "Error: input line %s is too long\n", file2);
      return FALSE;
    }
    /* returns error if the length of the line inside file2 is longer than MAX_STR_LEN*/
    if (StrCompare(buf1, buf2))
      {
	fprintf(stdout, "file1@%d:%s", num, buf1);
	fprintf(stdout, "file2@%d:%s", num, buf2);
      }
    /*compare the input lines of each file and print if they are identical*/
    num++;
    
  }
  if (!fgets(buf1, sizeof(buf1), fp1) && fgets(buf2, sizeof(buf2), fp2))
    {
      fprintf(stderr, "Error: %s ends early at line %d\n",file1, num-1);
    }
  /*print error if file 1 finishes earlier*/
  else if (fgets(buf1, sizeof(buf1), fp1) && !fgets(buf2, sizeof(buf2), fp2))
    {
      fprintf(stderr, "Error: %s ends early at line %d\n", file2, num - 1);
    }
  /*print error if file 2 finishes earlier*/
  fclose(fp1);
  fclose(fp2);
  return TRUE;
}
/*-------------------------------------------------------------------*/
/* CommandCheck()
- Parse the command and check number of argument.
- It returns the command type number
- This function only checks number of argument.
- If the unknown function is given or the number of argument is
different from required number, this function returns FALSE.

Note: You SHOULD check the argument rule later                    */
/*-------------------------------------------------------------------*/
int
CommandCheck(const int argc, const char *argv1)
{
  int cmdtype = INVALID;
  
  /* check minimum number of argument */
  if (argc < 3)
    return cmdtype;
  
  /* check command type */
  if (strcmp(argv1, FIND_STR) == 0) {
    if (argc != 3)
      return FALSE;
    cmdtype = FIND;
  }
  else if (strcmp(argv1, REPLACE_STR) == 0) {
    if (argc != 4)
      return FALSE;
    cmdtype = REPLACE;
  }
  else if (strcmp(argv1, DIFF_STR) == 0) {
    if (argc != 4)
      return FALSE;
    cmdtype = DIFF;
  }
  
  return cmdtype;
}
/*-------------------------------------------------------------------*/
int
main(const int argc, const char *argv[])
{
  int type, ret;
  
  /* Do argument check and parsing */
  if (!(type = CommandCheck(argc, argv[1]))) {
    fprintf(stderr, "Error: argument parsing error\n");
    PrintUsage(argv[0]);
    return (EXIT_FAILURE);
  }
  
  /* Do appropriate job */
  switch (type) {
  case FIND:
    ret = DoFind(argv[2]);
    break;
  case REPLACE:
    ret = DoReplace(argv[2], argv[3]);
    break;
  case DIFF:
    ret = DoDiff(argv[2], argv[3]);
    break;
  }
  
  return (ret) ? EXIT_SUCCESS : EXIT_FAILURE;
}
