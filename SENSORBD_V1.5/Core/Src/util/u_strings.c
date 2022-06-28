/*
 * u_strings.c
 *
 *  Created on: Jun 22, 2022
 *      Author: 82106
 */



#include "u_strings.h"


/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
bool is_string_same(const char *dest, const char *scr, int length)
{
  if(length == 0)
  {
    int i = 0;
    while(1)
    {
      if(dest[i] != scr[i])
        return false;

      if((dest[i] == '\0') || (scr[i] == '\0'))
        break;

      i++;
    }
  }
  else
  {
    for(int i=0; i<length; i++)
    {
      if(dest[i] != scr[i])
        return false;
    }
  }

  return true;
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
bool do_string_have(const char *src, const char* keyword)
{
  if(strstr(src, keyword) != null)
    return true;

  return false;
}

bool do_char_have(const char *src, char keyword)
{
  if(strchr(src, keyword) != null)
    return true;

  return false;
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
int StrtoHex(const char *param)
{
    int hex = 0;
    int count = strlen(param), i = 0;

    for(i = 0; i < count; i++){
        if(*param>= '0' && *param<= '9') hex = hex *16 + *param- '0';
        else if(*param>= 'A' && *param<= 'F') hex = hex *16 + *param- 'A' + 10;
        else if(*param>= 'a' && *param<= 'f') hex = hex *16 + *param- 'a' + 10;
        param++;
    }
    return hex;
}
void StrtoHexStr(char* in, char* out)
{
    int idx;
    int len = strlen(in);
    for(idx=0; idx<len; idx++)
    {
        sprintf(out+(idx*2), "%02x", in[idx]);
    }
}
/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
char *string_strtok(char *str, const char *delim)
{
  static char *org = NULL;
  static char *tracer = NULL;
  const char *pdelim;

  if (str != NULL) tracer = str;
  if (delim == NULL || *delim == '\0'/*NULL*/) return NULL;
  if (tracer == NULL || *tracer == '\0') return NULL;

  while (*tracer)
  {
    for (pdelim = delim; *pdelim; pdelim++)
      if (*tracer == *pdelim) break;

    if (*pdelim == '\0') break;
    tracer++;
  }

  for (org = tracer; *tracer; tracer++)
  {
    for (pdelim = delim; *pdelim; pdelim++)
      if (*tracer == *pdelim) break;

    if (*pdelim)
    {
      *tracer++ = '\0';
      break;
    }
  }
  return org;
}

void Remove_Str(char *src, char* remv_str)
{
	int len;
	char *p_pos;

	while(*src)
	{
		if(*src++ == *remv_str)
		{
			for(len = 1; *(remv_str+len); len++)
			{
				if(*src++ != *(remv_str + len)) break;
			}
			if(*(remv_str + len) == 0)
			{
				src -= len;
				for(p_pos = src; *(p_pos+len); p_pos++) *p_pos = *(p_pos+len);
				*p_pos = 0;
			}
		}
	}
}
/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
bool set_ip_string(char *buf, char *ip, char *end_token)
{
	u8 index = 0;
	char *str_ptr = buf;

	str_ptr = strtok(buf, ".");
	while(str_ptr)
	{
		ip[index++] = (char)atoi(str_ptr);

		if(index == 3)
		{
			str_ptr = strtok(NULL, end_token);
			ip[index++] = (char)atoi(str_ptr);
		}
		else str_ptr = strtok(NULL, ".");

		if(index == 4) break;
	}

	if(index == 4) return true;
	else return false;

}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
u8 *strstr_u8(u8 *str1, u8 *str2, u16 len)
{
  u16 i;
  u8 *cp = (u8 *) str1;
  u8 *s1, *s2;

  if (!*str2) return (u8 *) str1;

  for(i=0; i<len; i++)
  {
      s1 = cp;
      s2 = (u8 *) str2;

      while (*s1 && *s2 && !(*s1 - *s2)) s1++, s2++;
      if (!*s2) return cp;
      cp++;
  }

  return null;
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
bool is_url_string(char *url)
{
  int len = strlen(url);

  if(len < 4) return false;
  if(len > 96) return false;

  if(do_char_have(url, '\r') == true) return false;
  if(do_char_have(url, '\n') == true) return false;
  if(do_char_have(url, ' ') == true) return false;
  if(do_char_have(url, '$') == true) return false;
  if(do_char_have(url, '.') == false) return false;


  return true;
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
bool is_ip_string(char *ip)
{
  int num;
  char dots = 0;
  char addr[4];
  char *ptr = ip;

  if(ptr == NULL) return false;


  for(int j=0; j<4; j++)
  {
    memset(addr, 0x00, 4);

    for(int i=0; i<4; i++)
    {
      if((*ptr >= '0') && (*ptr <= '9'))
      {
        addr[i] = *ptr;
        ptr++;
      }
      else if(*ptr == '.')
      {
        dots++;
        ptr++;
        num = atoi(addr);
        if(num > 255) return false;
        break;
      }
      else
      {
        num = atoi(addr);
        if(num > 255) return false;
        if(dots != 3) return false;
        break;
      }
    }
  }

  return true;
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
bool get_ip(char *ip, char *dest)
{
	int num;
	char dots = 0;
	char addr[4];
	char *ptr = ip;

	if(ptr == NULL) return false;

	for(int j=0; j<4; j++)
	{
		memset(addr, 0x00, 4);
		for(int i=0; i<4; i++)
		{
			if((*ptr >= '0') && (*ptr <= '9'))
			{
				addr[i] = *ptr;
				ptr++;
			}
			else if(*ptr == '.')
			{
				dots++;
				ptr++;
				num = atoi(addr);
				if(num > 255) return false;
				dest[j] = num;
				break;
			}
			else
			{
				num = atoi(addr);
				if(num > 255) return false;
				if(dots != 3) return false;
				dest[j] = num;
				break;
			}
		}
	}
	return true;
}


/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
uint16_t count_split_str(uint8_t *buffer, uint16_t len, uint8_t delim)
{
  uint16_t count = 0;

  if(len == 0)
    return 0;

  for(int i=0; i<len; i++)
  {
    if(buffer[i] == delim)
      count++;
  }

  if((buffer[len-1] != delim) && (count > 0))
    count++;

  return count;
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
uint8_t *split_str(uint8_t *buffer, uint16_t len, uint16_t pos, uint8_t delim)
{
  uint16_t temp_pos=0;
  uint8_t *temp_ptr = buffer;

  for(int i=0; i<len; i++)
  {
    if(buffer[i] == delim)
    {
      if(temp_pos == pos)
        return temp_ptr;
      else
      {
        if((i+1) < len)
          temp_ptr = &buffer[i+1];
      }
      temp_pos++;
    }
  }

  return temp_ptr;
}




/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
char *replaceAll(char *s, const char *olds, const char *news)
{
  char *result, *sr;
  size_t i, count = 0;
  size_t oldlen = strlen(olds); if (oldlen < 1) return s;
  size_t newlen = strlen(news);

  if (newlen != oldlen) {
    for (i = 0; s[i] != '\0';) {
      if (memcmp(&s[i], olds, oldlen) == 0) count++, i += oldlen;
      else i++;
    }
  } else i = strlen(s);

  result = (char *) malloc(i + 1 + count * (newlen - oldlen));
  if (result == NULL) return NULL;

  sr = result;
  while (*s) {
    if (memcmp(s, olds, oldlen) == 0) {
      memcpy(sr, news, newlen);
      sr += newlen;
      s  += oldlen;
    } else *sr++ = *s++;
  }
  *sr = '\0';
  return result;
}
