#ifndef STRINGHELPERS_H_INCLUDED
#define STRINGHELPERS_H_INCLUDED
bool str_starts_with(const char *pre, const char *str);
int atoi(const char *s);
bool char_is_digit(const char c);
char* str_extract_int(const char *str);
#endif