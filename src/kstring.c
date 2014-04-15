/* kstring.c
 * extension to the C string library that maintains some basic information
 *
 * author: michael blockley <michael@sss.co.nz>
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <kstring.h>

#define MAGIC		0x0BADC0DE
#define MAGIC_MASK	0xFFFFFFFF
#define MAGIC_LEN	sizeof(uint32_t)
#define LEN_LEN		sizeof(size_t)       

#define MAGICFY(x)        ((MAGIC_MASK & x) | MAGIC)

#define KSTR_GET_MAGIC(x) (*((uint32_t*)x))
#define KSTR_GET_LEN(x)   (*((size_t*)(x + MAGIC_LEN)))
#define KSTR_GET_STR(x)   ((char*)(x + MAGIC_LEN + LEN_LEN))

#define STR_GET_START(x)  (x - MAGIC_LEN - LEN_LEN)
#define STR_GET_MAGIC(x)  (*((uint32_t*)STR_GET_START(x)))
#define STR_GET_LEN(x)    (*((size_t*)(x - LEN_LEN)))

/* kstring_new
 * creates a new kstring fromt the give C string
 *
 * param str: the string to convert
 * return: a new kstring or NULL
 *         NULL indicates insufficient memory
 */
const char *kstring_new(const char *str)
{
	assert(str);
	return kstring_newl(str, strlen(str));
}/* end: kstring_new */

/* kstring_newl
 * creates a new kstring fromt the give C string assuming the given length
 * is correct
 *
 * param str: the string to convert
 * param len: the length of the string
 * return: a new kstring or NULL
 *         NULL indicates insufficient memory
 */
const char *kstring_newl(const char *str, size_t len)
{
	char *ret;
	
	assert(str);

	ret = malloc(MAGIC_LEN + LEN_LEN + len + 1);
	if(!ret)
		return NULL;
	KSTR_GET_MAGIC(ret) = MAGICFY(len);
	KSTR_GET_LEN(ret) = len;
	strncpy(KSTR_GET_STR(ret), str, len);
	KSTR_GET_STR(ret)[len] = '\0';

	return KSTR_GET_STR(ret);
}/* end: kstring_newl */

/* kstring destroy
 * will check if the given string is a kstring, if it is it will free all
 * the associated information, if it is not it will free the string pointer
 *
 * parm str: the string to free
 */
void kstring_destroy(const char *str)
{
	assert(str);

	if(is_kstring(str))
		free((void*)STR_GET_START(str));
	else
		free((void*)str);
}/* end: kstring_destroy */

/* is_kstring
 * checks if the given C string is infact kstring (relies on MAGIC NUMBERS)
 * so could fail in the in odd case
 *
 * parm str: the string to check
 * return: 0 if not a kstring else something else
 */
uint8_t is_kstring(const char *str)
{
	assert(str);
	return MAGICFY(STR_GET_LEN(str)) == STR_GET_MAGIC(str) && 
			str[STR_GET_LEN(str)] == '\0';
}/* end: is_kstring */

/* kstrlen
 * will return the stored length if is a kstring otherwise will perform 
 * strlen
 *
 * param string: the string to check
 * return: the length of the string
 */
size_t kstrlen(const char *str)
{
	assert(str);

	if(is_kstring(str))
		return STR_GET_LEN(str);
	return strlen(str);
}/* end: kstrlen */

/* kstrcat
 * will return a string that is the concatination of the two given strings
 *
 * param a: the first string
 * param b: the second string
 * return: either the concatination of the strings else NULL
 *         NULL indicates insufficient memory
 */
const char *kstrcat(const char *a, const char *b)
{
	char *ret;
	size_t len, alen;

	assert(a && b);
	
	len = (alen = kstrlen(a)) + kstrlen(b);
	ret = malloc(MAGIC_LEN + LEN_LEN + len + 1);
	if(!ret)
		return NULL;
	KSTR_GET_MAGIC(ret) = MAGICFY(len);
	KSTR_GET_LEN(ret) = len;
	strncpy(KSTR_GET_STR(ret), a, alen);
	strncpy(KSTR_GET_STR(ret) + alen, b, len - alen);
	KSTR_GET_STR(ret)[len] = '\0';

	return KSTR_GET_STR(ret);
}/* end: kstrcat */
