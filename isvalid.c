#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <arpa/inet.h>

#include "std.h"
#include "isvalid.h"


csc_bool_t csc_isValid_hex(const char *word)
{   char ch = *word;
    if (ch == '\0')
        return(FALSE);
    while((ch = *(word++)) != '\0')
    {	if (!((ch>='0' && ch<='9') || (ch>='a' && ch<='f') || (ch>='A' && ch<='F')))
            return(FALSE);
	}
    return(TRUE);
}


csc_bool_t csc_isValid_int(const char *word)
{   char ch = *word;
	if (ch=='-')
		ch = *(++word);
    if (ch == '\0')
        return(FALSE);
    while((ch = *(word++)) != '\0')
        if (ch<'0' || ch>'9')
            return(FALSE);
    return(TRUE);
}


csc_bool_t csc_isValidRange_int(const char *word, int min, int max, int *value)
{	int val;
	if (!csc_isValid_int(word))
		return FALSE;
	val = atoi(word);
	if (val<min || val>max)
		return FALSE;
	*value = val;
	return TRUE;
}


csc_bool_t csc_isValid_float(const char *str)
{   int has_point, has_e, has_num;
    char ch;
    ch = *str;
    if (ch=='-' || ch=='+')
        str++;
    has_point = FALSE;
    has_e = FALSE;
    has_num = FALSE;
    while ((ch=*(str++)) != '\0')   switch(ch)
    {   case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': 
            has_num = TRUE;
            break;
        case 'e': case 'E':
            if (has_e || !has_num)
                return(FALSE);
            if (*str=='-' || *str=='+')
                str++;
            has_e = TRUE;
            has_num = FALSE;
            break;
        case '.':
            if (has_point || has_e)
                return(FALSE);
            has_point = TRUE;
            break;
        default:
            return(FALSE);
    }
    return(has_num);
}


csc_bool_t csc_isValidRange_float(const char *word, double min, double max, double *value)
{	double val;
	if (!csc_isValid_float(word))
		return FALSE;
	val = atof(word);
	if (val<min || val>max)
		return FALSE;
	*value = val;
	return TRUE;
}


csc_bool_t csc_isValid_ipV4(const char *str)
{   struct sockaddr_in sa;
    return inet_pton(AF_INET, str, &(sa.sin_addr)) != 0;
}

csc_bool_t csc_isValid_ipV6(const char *str)
{   struct sockaddr_in6 sa;
    return inet_pton(AF_INET6, str, &(sa.sin6_addr)) != 0;
}


csc_bool_t csc_isValid_domain(const char *str)
{   int sLen=strlen(str);
    int segLen, i;
 
// Look at the ends of the domain name.
    if ( str[0] == '.'
       || str[sLen-1] == '.'
       || sLen > 253
       ) 
    {   return FALSE;
    }
 
// Look at each character in turn.
    segLen = 0;
    for(i=0; i<sLen; i++)
    {   if (str[i] == '.')
        {   if (segLen == 0)
                return FALSE;
            segLen=0;
        }
        else if (  isalnum(str[i])
                || str[i]=='-' && segLen!=0 && i+1<sLen && str[i+1]!='.'
                )
        {   if (++segLen > 63)
                return FALSE;
        }
        else
            return FALSE; //invalid char...
    }
 
    return TRUE;
}


csc_bool_t csc_isValid_decentRelPath(const char *str)
{   int segLen;
    const char *p;
    int ch;
 
// Test each char of 'str' in turn.
    p = str;
    segLen = 0;
    while (ch = *(p++))
    {
        if (isalnum(ch) || ch=='_' || ch==',')
        {   segLen++;
        }
        else if (ch == '/')
        { // Path segment consisting of zero or more dots not allowed.
            if (segLen == 0)
                return FALSE;
            else
                segLen = 0;
        }
        else if (ch == '.')
        {  // Here we do not increment segLen.
        }
        else if (ch == '-')
        { // Path segements beginning with '-' are not allowed.
            if (segLen == 0)
                return FALSE;
        }
        else
            return FALSE;
    }
 
// Path should not be empty or end with a slash or consist only of dots.
    if (segLen == 0)
        return FALSE;
 
// Its all good if we got this far.
    return TRUE;
}


csc_bool_t csc_isValid_decentPath(const char *str)
{   if (*str == '/')
        str++;
    return csc_isValid_decentRelPath(str);
}


csc_bool_t csc_isValid_decentAbsPath(const char *str)
{   if (*str != '/')
        return FALSE;
    else
        return csc_isValid_decentRelPath(str+1);
}
