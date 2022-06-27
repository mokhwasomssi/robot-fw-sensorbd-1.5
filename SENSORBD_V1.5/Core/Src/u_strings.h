/*
 * u_strings.h
 *
 *  Created on: Jun 22, 2022
 *      Author: 82106
 */

#ifndef SRC_UTIL_U_STRINGS_H_
#define SRC_UTIL_U_STRINGS_H_


#include "../_typedef.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

extern bool is_string_same(const char *dest, const char* src, int length);
extern bool do_string_have(const char *src, const char* keyword);
extern bool do_char_have(const char *src, char keyword);
extern int StrtoHex(const char *param);
extern void StrtoHexStr(char* in, char* out);
extern char *string_strtok(char *_str, const char *_delim);
extern bool set_ip_string(char *buf, char *ip, char *end_token);
extern u8 *strstr_u8(u8 *str1, u8 *str2, u16 len);
extern bool is_url_string(char *url);
extern bool is_ip_string(char *ip);
extern bool get_ip(char *ip, char *dest);
extern uint16_t count_split_str(uint8_t *buffer, uint16_t len, uint8_t delim);
extern uint8_t *split_str(uint8_t *buffer, uint16_t len, uint16_t pos, uint8_t delim);
extern char *replaceAll(char *s, const char *olds, const char *news);

extern void Remove_Str(char *src, char* remv_str);


#endif /* SRC_UTIL_U_STRINGS_H_ */
