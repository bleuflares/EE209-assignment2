#include <assert.h> /* to use assert() */
#include <stdio.h>
#include "str.h"

/* Your task is:
1. Rewrite the body of "Part 1" functions - remove the current
body that simply calls the corresponding C standard library
function.
2. Write appropriate comment per each function
*/

/* Part 1 */
/*------------------------------------------------------------------------*/
size_t StrGetLength(const char* pcSrc)
{
  const char *pcEnd;
  assert(pcSrc); /* NULL address, 0, and FALSE are identical. */
  pcEnd = pcSrc;
  
  while (*pcEnd) /* null character and FALSE are identical. */
    pcEnd++;
  
  return (size_t)(pcEnd - pcSrc);
}

/*------------------------------------------------------------------------*/
char *StrCopy(char *pcDest, const char* pcSrc)
{
  assert(pcDest&&pcSrc);/* assert that parameters are not NULL; NuLL address, 0 and False are identical*/
  char *pcEnd = pcDest;
  while(*pcSrc)/*null character and FALSE are identical keep on until the end of the string*/
    {
      *pcEnd++ = *pcSrc++; /*copy the data stored at pcSrc to the data stored at the address of cp and increment both addresses*/
    }
  
  
  *pcEnd = '\0';/*add NULL at the end of the string*/
  return pcDest; /*return the address of copy*/
}

/*------------------------------------------------------------------------*/
int StrCompare(const char* pcS1, const char* pcS2)
{
  assert(pcS1&&pcS2); /* assert that parameters are not NULL; NuLL address, 0 and False are identical*/
  const char *s1 = pcS1;
  const char *s2 = pcS2;
  /*obtain the address of pcS1 and pcS2*/
  while (*s1 == *s2 && *s1)//keep on until they are same and one of them do not end
    {
      s1++;/*increment both address of s1 and s2*/
      s2++;
    }
  if (*s1 < *s2) /*return value set depending on the comparision of character saved at the address*/
    return -1;
  else if (*s1>*s2)
    return 1;
  else
    return 0;
	/* TODO: fill this function */
}
/*------------------------------------------------------------------------*/
char *StrSearch(const char* pcHaystack, const char *pcNeedle)
{
  assert(pcHaystack&&pcNeedle); /* assert that parameters are not NULL; NuLL address, 0 and False are identical*/
  char *pcEnd = (char *)pcHaystack;/*get the address of pcHaycheck*/
  char *s1, *s2;
  if (!*pcNeedle) /*string stored at pcNeedle is null*/
    return pcEnd;
  
  while (*pcEnd)
    {
      s1 = pcEnd; /*assign currently searching position to s1 at every iteration*/
	  s2 = (char *)pcNeedle; /*assign original value to s2 at every iteration*/
      
	  while (*s1 && *s2 && *s1 == *s2) /*keep searching while both s1 and s2 are not null and have same character*/
	{
	  s1++, s2++;
	  if (!*s2) /* We found Needle; stop searching when s2 gets to the end and return the address*/
	    return pcEnd;
	}
	  pcEnd++; /*Needle not found search from the next character of pcHaystack*/
    }
  return NULL; /*Needle not found until the end of the Haystack*/

}

/*------------------------------------------------------------------------*/
char *StrConcat(char *pcDest, const char* pcSrc)
{
	assert(pcDest&&pcSrc); /* assert that parameters are not NULL; NuLL address, 0 and False are identical*/
	char *pcEnd = pcDest; /*get the address of pcDest*/
	while (*pcEnd) /*get to the end of pcDest*/
		pcEnd++;
	while (*pcSrc) /*concaternate the string stored at pcSrc to pcDest*/
		*pcEnd++ = *pcSrc++;
	return pcDest; /*return the address of concaternated string*/
	
	/* TODO: fill this function */
}
