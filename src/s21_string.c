#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *new_string = (char *)str;
  s21_size_t counter = 0;
  int flag = 0;
  while (counter < n) {
    if (new_string[counter] == c) {
      flag = 1;
      break;
    }
    ++counter;
  }
  return new_string = flag == 1 ? new_string + counter : s21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  char *string_1 = (char *)str1;
  char *string_2 = (char *)str2;
  int diff = 0;
  s21_size_t counter = 0;
  while (counter < n && diff == 0) {
    if (string_1[counter] != string_2[counter]) {
      diff = string_1[counter] - string_2[counter];
    }
    ++counter;
  }
  return diff;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *s21_dest = (char *)dest;
  const char *s21_src = (char *)src;
  for (size_t counter = 0; counter < n; ++counter) {
    *s21_dest = *s21_src;
    ++s21_dest;
    ++s21_src;
  }

  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  char *new_str = (char *)str;
  for (size_t i = 0; i < n; ++i) {
    *new_str = (char)c;
    ++new_str;
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *pointer = dest + s21_strlen(dest);
  while (n--) {
    *pointer = *src;
    ++pointer;
    ++src;
  }
  *pointer = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {  // интенсив_
  const char *res = str;
  while (*res != '\0' && *res != c) {
    ++res;
  }
  if (*res == '\0' && c != '\0') {
    res = s21_NULL;
  }
  return (char *)res;
}

int s21_strncmp(char *s1, char *s2, int n) {
  if (n == 0) return 0;
  do {
    if (*s1 != *s2++) return (*s1 - *(--s2));
    if (*s1++ == 0) break;
  } while (--n != 0);
  return 0;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  for (; (i < n) && (src[i]); ++i) {
    dest[i] = src[i];
  }
  for (; i < n; ++i) {
    dest[i] = '\0';
  }
  return dest;
}

s21_size_t s21_strcspn(const char *str, const char *sym) {
  s21_size_t result = 0;
  int f_not_find = 1;
  for (s21_size_t i = 0; str[i]; ++i) {
    for (s21_size_t j = 0; sym[j]; ++j) {
      if (str[i] == sym[j]) {
        f_not_find = 0;
        break;
      }
    }
    if (!f_not_find) {
      break;
    }
    result++;
  }
  return result;
}

char *s21_strerror(int errnum) {  // Денис
  char *result = s21_NULL;
  char *errors[] = S21_ERR_MASS;
  static char buf[100] = "EMPTY";
  if (errnum >= 0 && errnum < S21_ERR_SIZE) {
    result = errors[errnum];
  } else {
    if (S21_UNAME == 0) {
      s21_strncpy(buf, "No error information",
                  s21_strlen("No error information"));
    } else if (S21_UNAME == 1) {
      char *unknown_err = "Unknown error:";
      s21_sprintf(buf, "%s %d", unknown_err, errnum);
    }
  }
  return result == s21_NULL ? buf : result;
}

s21_size_t s21_strlen(const char *str) {  // интенсив_
  int result = 0;
  while (str[result]) {
    ++result;
  }
  return result;
}

char *s21_strpbrk(const char *str1, const char *str2) {  // Денис
  char *result = s21_NULL;
  const char *temp_str1 = str1;
  const char *temp_str2 = str2;
  int find_flag = 0;
  while (*temp_str1 != '\0') {
    while (*temp_str2 != '\0') {
      if (*temp_str2 == *temp_str1) {
        result = (char *)temp_str1;
        find_flag = 1;
        break;
      }
      ++temp_str2;
    }
    if (find_flag) {
      break;
    }
    temp_str2 = str2;
    ++temp_str1;
  }
  return result;
}

char *s21_strrchr(const char *str, int c) {  // Ульяна
  const char *res =
      str + s21_strlen(str);  // на символ '\0'( при "" будет указывать на '\0')
  while (res != str && *res != c) {
    --res;
  }
  if (res == str && *res != c) {
    res = s21_NULL;
  }
  return (char *)res;
}

char *s21_strstr(
    const char *haystack,
    const char *needle) {  // интенсив_ можно реализовать через s21_strncmp
  char *result = s21_NULL;
  int str_len = s21_strlen(haystack);
  int search_len = s21_strlen(needle);
  for (int i = 0; i < str_len - search_len + 1; ++i) {
    int count = 0;
    for (int j = 0; j < search_len; ++j) {
      if (haystack[i + j] == needle[j]) {
        ++count;
      }
    }
    if (count == search_len) {
      result = (char *)haystack + i;
      break;
    }
  }
  return result;
}

int IsDelim(char c, const char *delim) {
  int result = 0;
  const char *temp_delim = delim;
  while (*temp_delim != '\0') {
    if (*temp_delim == c) {
      result = 1;
      break;
    }
    ++temp_delim;
  }
  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *temp_str = s21_NULL;
  if (str == s21_NULL && temp_str == s21_NULL) {
    return s21_NULL;
  }
  static int f_last = 0;
  if (str != s21_NULL) {
    temp_str = str;
    f_last = 0;
  }
  while (IsDelim(*temp_str, delim)) {
    ++temp_str;
  }
  if (*temp_str == '\0') f_last = 1;
  char *temp = temp_str;
  const char *temp_dim = delim;
  int find_flag = 0;
  while (*temp_str != '\0') {
    while (*temp_dim != '\0') {
      if (*temp_dim == *temp_str) {
        find_flag = 1;
        break;
      }
      ++temp_dim;
    }
    if (find_flag) {
      break;
    }
    temp_dim = delim;
    ++temp_str;
  }
  if (find_flag) {
    *temp_str = '\0';
    ++temp_str;
  } else if (f_last) {
    temp = s21_NULL;
  } else {
    f_last = 1;
  }
  return temp;
}

void *s21_to_upper(const char *str) {
  char *str_upper = s21_NULL;
  if (str) {
    s21_size_t length = s21_strlen(str);
    str_upper = (char *)malloc(sizeof(char) * (length + 1));
    for (s21_size_t i = 0; i < s21_strlen(str); ++i) {
      char a = str[i];
      str_upper[i] = a >= 'a' && a <= 'z' ? a - 32 : a;
    }
    str_upper[length] = '\0';
  }
  return str_upper;
}

void *s21_to_lower(const char *str) {
  char *str_lower = s21_NULL;
  if (str) {
    s21_size_t length = s21_strlen(str);
    str_lower = (char *)malloc(sizeof(char) * (length + 1));
    for (s21_size_t i = 0; i < length; i++) {
      char a = str[i];
      str_lower[i] = a >= 'A' && a <= 'Z' ? a + 32 : a;
    }
    str_lower[length] = '\0';
  }
  return str_lower;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  int err = 0;
  char *new_str = s21_NULL;
  if (src && str && start_index <= (s21_strlen(src))) {
    new_str =
        (char *)calloc(s21_strlen(src) + s21_strlen(str) + 1, sizeof(char));
    s21_size_t i = 0;
    for (; i < start_index; i++) {
      new_str[i] = src[i];
    }
    s21_size_t end = i;
    for (s21_size_t j = 0; j < s21_strlen(str); j++, i++) {
      new_str[i] = str[j];
    }
    for (; end < s21_strlen(src); end++, i++) {
      new_str[i] = src[end];
    }
    new_str[s21_strlen(new_str)] = '\0';
  } else {
    err = 1;
  }
  return err ? s21_NULL : new_str;
}

/*
функция сначала определяет до какого индекса у нас идут символы, которые нужно
удалить потом если мы не дошли до конца строки мы вычисляем то же самое, но
только для конца строки
 */
void *s21_trim(const char *src, const char *trim_chars) {
  char *new_string = s21_NULL;
  if (src) {
    if (trim_chars && s21_strlen(trim_chars)) {
      s21_size_t src_len = s21_strlen(src);
      const char *src_end = src + src_len;
      while (src == s21_strpbrk(src, trim_chars)) {
        ++src;
      }
      if (src != src_end) {
        --src_end;
        while (src_end == s21_strpbrk(src_end, trim_chars)) {
          --src_end;
        }
        ++src_end;
      } else {  // так же надо выделить память под null иначе сега
        new_string = s21_NULL;
      }
      new_string = calloc(src_end - src + 1, sizeof(char));
      char *temp_str = new_string;
      while (src != src_end) {
        *(temp_str++) = *(src++);
      }
      *temp_str = '\0';
    } else {
      new_string = s21_trim(src, " \t\n");
    }
  }
  return new_string;
}

s21_size_t s21_strspn(const char *str, const char *sym) {
  s21_size_t result = 0;
  for (s21_size_t i = 0; str[i] != '\0'; ++i) {
    int f_find = 0;
    for (s21_size_t j = 0; sym[j] != '\0'; ++j) {
      if (str[i] == sym[j]) {
        f_find = 1;
        break;
      }
    }
    if (!f_find) {
      break;
    }
    result++;
  }
  return result;
}

////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//////////////////////////////////////////////////////
int ParseFlags(const char **p_format) {
  int result = 0;
  int flags_len = s21_strspn(*p_format, " +-#0");
  for (int i = 0; i < flags_len; ++i) {
    switch ((*p_format)[i]) {
      case ' ':
        result |= F_SPACE;
        break;
      case '+':
        result |= F_SIGN;
        break;
      case '-':
        result |= F_LEFT;
        break;
      case '0':
        result |= F_NULL;
        break;
      case '#':
        result |= F_HESHTAG;
        break;
    }
  }
  *p_format += flags_len;
  return result;
}

int ParseNum(const char **p_format) {
  int result = 0;
  while (*(*p_format) >= '0' && *(*p_format) <= '9') {
    result *= 10;
    result += *(*p_format) - '0';
    ++(*p_format);
  }
  return result;
}

int ParseLength(const char **p_format) {
  int result = 0;
  switch (*(*p_format)) {
    case 'h':
      ++(*p_format);
      if (*(*p_format) == 'h') {
        ++(*p_format);
        result = *p_format == s21_strpbrk(*p_format, "idouxXn")
                     ? F_SHORT_SHORT_INT
                     : -1;
      } else {
        result =
            *p_format == s21_strpbrk(*p_format, "idouxcXn") ? F_SHORT_INT : -1;
      }
      break;
    case 'L':
      ++(*p_format);
      result =
          *p_format == s21_strpbrk(*p_format, "eEfgG") ? F_LONG_DOUBLE : -1;
      break;
    case 'l':
      ++(*p_format);
      if (*(*p_format) == 'l') {
        ++(*p_format);
        result = *p_format == s21_strpbrk(*p_format, "idouxXn")
                     ? F_LONG_LONG_INT
                     : -1;
      } else if (*p_format == s21_strpbrk(*p_format, "idouxXcsn")) {
        result = F_LONG_INT;
      } else if (*p_format == s21_strpbrk(*p_format, "eEfgG")) {
        result = F_DOUBLE;
      } else {
        result = -1;
      }
      break;
    default:
      if (*p_format == s21_strpbrk(*p_format, "idouxXn")) {
        result |= F_INT;
      } else if (*p_format == s21_strpbrk(*p_format, "eEfgG")) {
        result |= F_Float;
      } else if (*(*p_format) == 's') {
        result |= F_STR;
      } else if (*(*p_format) == 'c') {
        result |= F_CHAR;
      } else if (*(*p_format) == 'p') {
        result |= F_PTR;
      } else if (*(*p_format) == 'n') {
        result |= F_N;
      } else
        result = -1;
  }
  return result;
}

int ErrFlagsInt(S21SprintfArgs *elems) {
  int result = 0;
  if (elems->format == 'i' || elems->format == 'd') {
    if (elems->flags & F_HESHTAG) elems->flags &= ~F_HESHTAG;
  } else if (elems->format == 'u') {
    if (elems->flags & F_SPACE) {
      elems->flags &= ~F_SPACE;
    }
    if (elems->flags & F_SIGN) {
      elems->flags &= ~F_SIGN;
    }
    if (elems->flags & F_HESHTAG) {
      elems->flags &= ~F_HESHTAG;
    }
  } else if (elems->format == 'p') {  //?
    // p?
  } else {
    if (elems->flags & F_SPACE) {
      elems->flags &= ~F_SPACE;
    }
    if (elems->flags & F_SIGN) {
      elems->flags &= ~F_SIGN;
    }
  }
  return result;
}

long long int GetValInt(const S21SprintfArgs *elems, va_list *args) {
  long long int result = 0;
  if (elems->length & F_SHORT_INT) {
    result = va_arg(*args, int);
  } else if (elems->length & F_INT) {
    result = va_arg(*args, int);
  } else if (elems->length & F_LONG_INT) {
    result = va_arg(*args, long int);
  } else {
    result = va_arg(*args, long long int);
  }
  return result;
}

unsigned long long int GetValUInt(const S21SprintfArgs *elems, va_list *args) {
  unsigned long long int result = 0;
  if (elems->length & F_SHORT_INT) {
    result = va_arg(*args, unsigned int);  //интересности
  } else if (elems->length & F_INT) {
    result = va_arg(*args, unsigned int);
  } else if (elems->length & F_LONG_INT) {
    result = va_arg(*args, unsigned long int);
  } else {
    result = va_arg(*args, unsigned long long int);
  }
  if (elems->format == 'p' && result == 0 && S21_UNAME == 0) {
    S21SprintfArgs *temp = (S21SprintfArgs *)elems;
    temp->flags = 0;
    temp->f_acc = 0;
    temp->acc = 0;
    temp = NULL;
  }
  return result;
}

long double GetValDouble(const S21SprintfArgs *elems, va_list *args) {
  long double result = 0;
  if (elems->length & F_DOUBLE || elems->length & F_Float) {
    result = va_arg(*args, double);
  } else {
    result = va_arg(*args, long double);
  }
  return result;
}

int MallocIntLen(const S21SprintfArgs *elems, int dig_count,
                 long long int val) {
  int result = dig_count >= elems->acc ? dig_count : elems->acc;
  if (val < 0) {
    result += 1;
  } else {
    result += ((elems->flags & F_SPACE) || (elems->flags & F_SIGN)) ? 1 : 0;
  }
  result = result >= elems->width ? result : elems->width;
  return result;
}

int MallocUIntLen(const S21SprintfArgs *elems, int dig_count,
                  unsigned long long int val) {
  int result = dig_count >= elems->acc ? dig_count : elems->acc;
  if (elems->format == 'o') {
    result +=
        ((elems->flags & F_HESHTAG) && val && dig_count >= elems->acc) ? 1 : 0;
  } else if (elems->format == 'x' || elems->format == 'X') {
    result += ((elems->flags & F_HESHTAG) && val) ? 2 : 0;
  } else if (elems->format == 'p' && (val != 0 || S21_UNAME == 1)) {
    result += (((elems->flags & F_SIGN) || (elems->flags & F_SPACE)) &&
               S21_UNAME == 0)
                  ? 1
                  : 0;
    result += 2;
  }
  result = result >= elems->width ? result : elems->width;
  return result;
}

int DigCount(long long int val) {
  int result = 0;
  while (val) {
    val /= 10;
    ++result;
  }
  return result ? result : 1;
}

int DigCountD(long double val) {
  int result = 0;
  while (val >= 1.) {
    val /= 10;
    ++result;
  }
  return result;
}

char *StrDec(long long int val) {
  char *result = s21_NULL;
  int dig_count = DigCount(val);
  result = (char *)malloc(sizeof(char) * (dig_count + 1));
  for (int i = dig_count - 1; i >= 0; --i) {
    result[i] = 48 + (val % 10);
    val /= 10;
  }
  result[dig_count] = '\0';
  return result;
}

char *StrUDec(unsigned long long int val) {
  char *result = s21_NULL;
  int dig_count = 0;
  long long int temp = val;
  while (temp) {
    temp /= 10;
    ++dig_count;
  }
  dig_count = dig_count ? dig_count : 1;
  result = (char *)malloc(sizeof(char) * (dig_count + 1));
  temp = val;
  for (int i = dig_count - 1; i >= 0; --i) {
    result[i] = 48 + (temp % 10);
    temp /= 10;
  }
  result[dig_count] = '\0';
  return result;
}

char *StrOct(unsigned long long int val) {
  char *result = s21_NULL;
  int dig_count = 0;
  long long int temp = val;
  while (temp) {
    temp /= 8;
    ++dig_count;
  }
  dig_count = dig_count ? dig_count : 1;
  result = (char *)malloc(sizeof(char) * (dig_count + 1));
  for (int i = dig_count - 1; i >= 0; --i) {
    result[i] = 48 + (val % 8);
    val /= 8;
  }
  result[dig_count] = '\0';
  return result;
}

char *StrHex(unsigned long long int val, const S21SprintfArgs *elems) {
  char *result = s21_NULL;
  if (elems->format == 'p' && val == 0 && S21_UNAME == 0) {
    result = (char *)malloc(sizeof(char) * (5 + 1));
    s21_strncpy(result, "(nil)", 5);
    result[5] = '\0';
  } else {
    int dig_count = 0;
    unsigned long long int temp = val;
    while (temp) {
      temp /= 16;
      ++dig_count;
    }
    dig_count = dig_count ? dig_count : 1;
    result = (char *)malloc(sizeof(char) * (dig_count + 1));
    for (int i = dig_count - 1; i >= 0; --i) {
      int mod = val % 16;
      if (elems->format == 'X') {
        result[i] = mod > 9 ? 65 + (mod % 10) : 48 + mod;
      } else {
        result[i] = mod > 9 ? 97 + (mod % 10) : 48 + mod;
      }
      val /= 16;
    }
    result[dig_count] = '\0';
  }
  return result;
}

char *StrUVal(unsigned long long int val, const S21SprintfArgs *elems) {
  char *result = s21_NULL;
  switch (elems->format) {
    case 'u':
      result = StrUDec(val);
      break;
    case 'o':
      result = StrOct(val);
      break;
    case 'x':
    case 'X':
    case 'p':
      result = StrHex(val, elems);
      break;
  }
  return result;
}

char *StrDouble(long double val, const S21SprintfArgs *elems) {
  char *result = s21_NULL;
  long double val_int_part = elems->acc ? floorl(val) : roundl(val);
  long double val_mantis = val - floorl(val);
  if (elems->acc) {
    for (int j = 0; j < elems->acc; ++j) val_mantis *= 10.;
    if (DigCountD(roundl(val_mantis)) > elems->acc) {
      ++val_int_part;
      val_mantis = 0.;
    }
  }
  int dig_c_int = !val_int_part ? 1 : DigCountD(val_int_part);
  int str_len = dig_c_int + elems->acc;
  str_len += elems->acc || (elems->flags & F_HESHTAG) ? 1 : 0;
  result = (char *)malloc(sizeof(char) * (str_len + 1));
  int i = 0;
  long double degree = 10.;
  for (int j = dig_c_int - 1; j >= 0; --j, ++i) {
    result[j] = 48 + floorl(fmodl(val_int_part, degree) / (degree / 10.));
    degree *= 10.;
  }
  if (elems->acc || (elems->flags & F_HESHTAG)) result[i++] = '.';
  if (elems->acc) {
    long double val_int_mant = roundl(val_mantis);
    int dig_c_mant = DigCountD(val_int_mant);
    for (int j = 0; j < elems->acc - dig_c_mant; ++j, ++i) result[i] = '0';
    i = str_len - 1;
    degree = 10.;
    for (int j = 0; j < dig_c_mant; ++j, --i) {
      result[i] = 48 + floorl(fmodl(val_int_mant, degree) / (degree / 10.));
      degree *= 10.;
    }
  }
  result[str_len] = '\0';
  return result;
}

long double NormalE(long double val, int *degree) {
  if (val > 1e-323) {
    while (val < 1.) {
      val *= 10.;
      --(*degree);
    }
    while (val >= 10) {
      val /= 10.;
      ++(*degree);
    }
  }
  return val;
}

long double MantisE(long double val, long double *val_int, int *degree,
                    const S21SprintfArgs *elems) {
  long double val_mantis = 0.;
  if (*val_int >= 10) {
    *val_int /= 10.;
    ++(*degree);
    val_mantis = 0.;
  } else if (elems->acc) {
    val_mantis = val - floorl(val);
    for (int j = 0; j < elems->acc; ++j) val_mantis *= 10.;
    if (DigCountD(roundl(val_mantis)) > elems->acc) {
      ++(*val_int);
      if (*val_int >= 10) {
        *val_int /= 10.;
        ++(*degree);
      }
      val_mantis = 0.;
    }
  }
  return val_mantis;
}

int MallocDoubleLen(int degree_dig_count, const S21SprintfArgs *elems) {
  int result = elems->acc + 1 + 2;  // +1 для dig. + 2 для e+-
  result += elems->acc || (elems->flags & F_HESHTAG) ? 1 : 0;  //+1 для '.'
  result += degree_dig_count > 2 ? 3 : 2;  //, +2-+3 для degree
  return result;
}

char *StrDoubleE(long double val, const S21SprintfArgs *elems) {
  char *result = s21_NULL;
  int degree = 0;
  val = NormalE(val, &degree);
  long double val_int = elems->acc ? floorl(val) : roundl(val);
  long double val_mantis = MantisE(val, &val_int, &degree, elems);
  int degree_dig_count = DigCount(degree);
  int str_len = MallocDoubleLen(degree_dig_count, elems);
  result = (char *)malloc(sizeof(char) * (str_len + 1));
  int i = 0;
  result[i++] = 48 + val_int;
  if (elems->acc || (elems->flags & F_HESHTAG)) result[i++] = '.';
  if (elems->acc) {
    val_mantis = roundl(val_mantis);  //камень предкновения
    int dig_c_mant = DigCountD(val_mantis);
    for (int j = 0; j < elems->acc - dig_c_mant; ++j, ++i) result[i] = '0';
    double deg = 10.;
    for (int j = i + dig_c_mant - 1, k = 0; k < dig_c_mant; --j, ++k) {
      result[j] = 48 + floorl(fmodl(val_mantis, deg) / (deg / 10.));
      deg *= 10.;
    }
    i += dig_c_mant;
  }
  result[i++] = elems->format == 'e' ? 'e' : 'E';
  result[i++] = degree < 0 ? '-' : '+';
  degree = degree < 0 ? -degree : degree;
  if (degree <= 9) {
    result[i++] = '0';
    result[i++] = 48 + degree;
  } else {
    for (int j = 0; j < degree_dig_count; ++j) {
      result[i + degree_dig_count - 1 - j] = 48 + degree % 10;
      degree /= 10;
    }
    i += degree_dig_count;
  }
  result[str_len] = '\0';
  return result;
}

char *StrGE(long double val, S21SprintfArgs *elems) {
  char *result = s21_NULL;
  elems->acc = elems->acc - 1;
  elems->format = 'e';
  char *val_e = StrDoubleE(val, elems);
  int res_len = s21_strlen(val_e);
  char *ptr_e = s21_strchr(val_e, 'e') - 1;
  char *t_ptr_e = ptr_e;
  while (*ptr_e == '0' && !(elems->flags & F_HESHTAG)) --ptr_e;
  if (*ptr_e == '.' && !(elems->flags & F_HESHTAG)) --ptr_e;
  res_len -= (t_ptr_e - ptr_e);
  int print_dig = ptr_e - val_e + 1;
  result = (char *)malloc(sizeof(char) * (res_len + 1));
  int i = 0;
  for (; i < print_dig; ++i) result[i] = val_e[i];
  while (*(t_ptr_e++)) result[i++] = *t_ptr_e;
  result[res_len] = '\0';
  free(val_e);
  return result;
}

char *StrGF(long double val, S21SprintfArgs *elems) {
  char *result = s21_NULL;
  elems->acc = elems->acc < 0 ? 0 : elems->acc;
  elems->format = 'f';
  char *val_f = StrDouble(val, elems);
  int res_len = s21_strlen(val_f);
  if (s21_strchr(val_f, '.')) {
    char *ptr_e = val_f + res_len - 1;
    while (*ptr_e == '0' && !(elems->flags & F_HESHTAG)) {
      --res_len;
      --ptr_e;
    }
    if (*ptr_e == '.' && !(elems->flags & F_HESHTAG)) {
      --res_len;
      --ptr_e;
    }
  }
  result = (char *)malloc(sizeof(char) * (res_len + 1));
  for (int i = 0; i < res_len; ++i) {
    result[i] = val_f[i];
  }
  result[res_len] = '\0';
  free(val_f);
  return result;
}

char *StrDoubleG(long double val, S21SprintfArgs *elems) {
  char *result = s21_NULL;
  long double val_int_part = floorl(val);
  int dig_c_int = DigCountD(val_int_part);
  elems->acc = elems->acc ? elems->acc : 1;
  int small_f_e = 0;
  int e_deg = -1;
  if (!dig_c_int) {
    long double val_mantis = val - val_int_part;
    long long int val_int_mant = (long long int)val_mantis;
    for (int j = 0; j < 4; ++j) {
      ++e_deg;
      val_mantis *= 10.;
      if (val_int_mant) break;
    }
    small_f_e = val_int_mant ? 1 : 2;
  }
  if ((dig_c_int > elems->acc || small_f_e == 2) && val > 1e-322) {
    result = StrGE(val, elems);
  } else {
    elems->acc = small_f_e == 1 ? e_deg + elems->acc : elems->acc - dig_c_int;
    result = StrGF(val, elems);
  }
  return result;
}

char *StrDoubleVal(long double val, const S21SprintfArgs *elems) {
  char *result = s21_NULL;
  if (elems->format == 'f') {
    result = StrDouble(val, elems);
  } else if (elems->format == 'e' || elems->format == 'E') {
    result = StrDoubleE(val, elems);
  } else {
    result = StrDoubleG(val, (S21SprintfArgs *)elems);
  }
  return result;
}

int PlusSyms(const S21SprintfArgs *elems, long long int val, int dig_count) {
  int result = 0;
  if (elems->format == 'i' || elems->format == 'd') {
    if (val < 0) {
      result = 1;
    } else {
      result = (elems->flags & F_SIGN) || (elems->flags & F_SPACE) ? 1 : 0;
    }
  } else if (elems->format == 'p') {
    result += (((elems->flags & F_SIGN) || (elems->flags & F_SPACE)) &&
               S21_UNAME == 0)
                  ? 1
                  : 0;
    result += val || S21_UNAME == 1 ? 2 : 0;
  } else if (elems->format == 'o') {
    result =
        (elems->flags & F_HESHTAG) && val && dig_count >= elems->acc ? 1 : 0;
  } else if (elems->format == 'x' || elems->format == 'X') {
    result = (elems->flags & F_HESHTAG) && val ? 2 : 0;
  }
  return result;
}

void FillPlusSyms(char *result, int *i, long long int val,
                  const S21SprintfArgs *elems, int dig_count) {
  if (elems->format == 'i' || elems->format == 'd') {
    if (val < 0) {
      result[(*i)++] = '-';
    } else if (elems->flags & F_SIGN)
      result[(*i)++] = '+';
    else if (elems->flags & F_SPACE)
      result[(*i)++] = val < 0 ? '-' : ' ';
  } else if (elems->format == 'o') {
    if (elems->flags & F_HESHTAG && val && dig_count >= elems->acc)
      result[(*i)++] = '0';
  } else if (elems->format == 'x' || elems->format == 'X') {
    if (elems->flags & F_HESHTAG && val) {
      result[(*i)++] = '0';
      result[(*i)++] = elems->format == 'x' ? 'x' : 'X';
    }
  } else if (elems->format == 'p') {
    if (elems->flags & F_SIGN && S21_UNAME == 0)
      result[(*i)++] = '+';
    else if (elems->flags & F_SPACE && S21_UNAME == 0)
      result[(*i)++] = ' ';
    if (val != 0 || S21_UNAME == 1) {
      result[(*i)++] = '0';
      result[(*i)++] = 'x';
    }
  }
}

void FillPlusSymsDouble(char *result, int *i, long double val,
                        const S21SprintfArgs *elems) {
  if (val < 0) {
    result[(*i)++] = '-';
  } else if (elems->flags & F_SIGN) {
    result[(*i)++] = '+';
  } else if (elems->flags & F_SPACE) {
    result[(*i)++] = ' ';
  }
}

char *FormatChar(const S21SprintfArgs *elems, va_list *args) {
  char *result = s21_NULL;
  unsigned long int sym = elems->length == F_LONG_INT
                              ? va_arg(*args, unsigned long int)
                              : va_arg(*args, int);
  if (elems->width > 1) {
    result = (char *)malloc(sizeof(char) * (elems->width + 1));
    int i = 0;
    if (!(elems->flags & F_LEFT))
      for (; i < elems->width - 1; ++i)
        result[i] = (S21_UNAME == 1) ? (elems->flags & F_NULL ? '0' : ' ')
                                     : ' ';  // КРОСС!!
    result[i++] = sym;
    if (elems->flags & F_LEFT)
      for (; i < elems->width; ++i) result[i] = ' ';
    result[elems->width] = '\0';
  } else {
    result = (char *)malloc(sizeof(char) * 2);
    result[0] = sym;
    result[1] = '\0';
  }
  return result;
}

char *FormatStr(const S21SprintfArgs *elems, va_list *args) {
  char *result = s21_NULL;
  char *format_str = va_arg(*args, char *);
  int str_len = s21_strlen(format_str);
  if (elems->f_acc) {
    str_len = elems->acc < str_len ? elems->acc : str_len;
  }
  if (elems->width > str_len) {
    result = (char *)malloc(sizeof(char) * (elems->width + 1));
    int i = 0;
    if (!(elems->flags & F_LEFT))
      for (; i < elems->width - str_len; ++i)
        result[i] = elems->flags & F_NULL && S21_UNAME == 1 ? '0' : ' ';  // 0
    for (int j = 0; j < str_len; ++j, ++i) result[i] = format_str[j];
    if (elems->flags & F_LEFT)
      for (; i < elems->width; ++i)
        result[i] = elems->flags & F_NULL && S21_UNAME == 1 ? '0' : ' ';  // 0
    result[elems->width] = '\0';
  } else {
    result = (char *)malloc(sizeof(char) * (str_len + 1));
    for (int i = 0; i < str_len; ++i) result[i] = format_str[i];
    result[str_len] = '\0';
  }
  return result;
}

char *FormatInt(const S21SprintfArgs *elems, va_list *args) {
  char *result = s21_NULL;
  if (ErrFlagsInt((S21SprintfArgs *)elems)) {
    return result;
  }
  long long int val = GetValInt(elems, args);
  char *str_val = StrDec(llabs(val));
  int dig_count = !val && elems->f_acc && !elems->acc ? 0 : s21_strlen(str_val);
  int result_len = MallocIntLen(elems, dig_count, val);
  result = (char *)malloc(sizeof(char) * (result_len + 1));
  int print_dig_count = dig_count >= elems->acc ? dig_count : elems->acc;
  int f_plus_syms = PlusSyms(elems, val, dig_count);
  int i = 0;
  if ((elems->flags & F_NULL) && !(elems->f_acc) && !(elems->flags & F_LEFT)) {
    FillPlusSyms(result, &i, val, elems, dig_count);
    for (int j = 0; j < result_len - dig_count - f_plus_syms; ++i, ++j)
      result[i] = '0';
    i = result_len - 1;
  } else {
    if (!(elems->flags & F_LEFT))
      for (int j = 0; j < result_len - print_dig_count - f_plus_syms; ++j, ++i)
        result[i] = ' ';
    FillPlusSyms(result, &i, val, elems, dig_count);
    for (int j = 0; j < print_dig_count - dig_count; ++i, ++j) result[i] = '0';
    i = result_len - 1;
    if (elems->flags & F_LEFT)
      for (int j = 0; j < result_len - print_dig_count - f_plus_syms; ++j, --i)
        result[i] = ' ';
  }
  for (int j = 0; j < dig_count; ++j, --i) {
    result[i] = str_val[dig_count - j - 1];
  }
  free(str_val);
  result[result_len] = '\0';
  return result;
}

char *FillNPrintf(const S21SprintfArgs *elems, va_list *args) {  //заполнить n
  char *result = s21_NULL;
  int *n = va_arg(*args, int *);
  *n = elems->count_fill_sym;
  n = s21_NULL;
  return result;
}

char *FormatUInt(const S21SprintfArgs *elems, va_list *args) {
  char *result = s21_NULL;
  if (ErrFlagsInt((S21SprintfArgs *)elems)) {
    return result;
  }
  unsigned long long int val = GetValUInt(elems, args);
  char *str_val = StrUVal(val, elems);
  int dig_count =
      val == 0 && elems->f_acc && !elems->acc ? 0 : s21_strlen(str_val);
  int result_len = MallocUIntLen(elems, dig_count, val);

  result = (char *)malloc(sizeof(char) * (result_len + 1));
  int print_dig_count = dig_count >= elems->acc ? dig_count : elems->acc;
  int f_plus_syms = PlusSyms(elems, val, dig_count);
  int i = 0;
  if ((elems->flags & F_NULL) && !(elems->f_acc) && !(elems->flags & F_LEFT)) {
    FillPlusSyms(result, &i, val, elems, dig_count);
    for (int j = 0; j < result_len - dig_count - f_plus_syms; ++i, ++j)
      result[i] = '0';
    i = result_len - 1;
  } else {
    if (!(elems->flags & F_LEFT)) {
      for (int j = 0; j < result_len - print_dig_count - f_plus_syms; ++j, ++i)
        result[i] = ' ';
    }
    FillPlusSyms(result, &i, val, elems, dig_count);
    for (int j = 0; j < print_dig_count - dig_count; ++i, ++j) result[i] = '0';
    i = result_len - 1;
    if (elems->flags & F_LEFT)
      for (int j = 0; j < result_len - print_dig_count - f_plus_syms; ++j, --i)
        result[i] = ' ';
  }
  for (int j = 0; j < dig_count; ++j, --i) {
    result[i] = str_val[dig_count - j - 1];
  }
  free(str_val);
  result[result_len] = '\0';
  return result;
}

char *FormatDouble(const S21SprintfArgs *elems, va_list *args) {
  char *result = s21_NULL;
  long double val = GetValDouble(elems, args);
  if (isinf(val) || isnan(val)) {
    result = (char *)malloc(sizeof(char) * 4);
    isinf(val) ? s21_strncpy(result, "inf", 3) : s21_strncpy(result, "nan", 3);
    result[3] = '\0';
    return result;
  }
  int f = elems->flags & F_SPACE || elems->flags & F_SIGN || val < 0 ? 1 : 0;
  char *str_val = StrDoubleVal(fabsl(val), elems);
  int str_len = s21_strlen(str_val);
  int result_len = str_len + f;
  result_len = result_len >= elems->width ? result_len : elems->width;
  result = (char *)malloc(sizeof(char) * (result_len + 1));
  int i = 0;
  if ((elems->flags & F_NULL) && !(elems->flags & F_LEFT)) {
    FillPlusSymsDouble(result, &i, val, elems);
    for (int j = 0; j < result_len - str_len - f; ++i, ++j) result[i] = '0';
    for (int j = 0; j < str_len; ++j, ++i) result[i] = str_val[j];
  } else {
    if (!(elems->flags & F_LEFT))
      for (int j = 0; j < result_len - (str_len + f); ++j, ++i) result[i] = ' ';
    FillPlusSymsDouble(result, &i, val, elems);
    for (int j = 0; j < str_len; ++j, ++i) result[i] = str_val[j];
    if (elems->flags & F_LEFT)
      for (int j = 0; j < result_len - (str_len + f); ++j, ++i) result[i] = ' ';
  }
  free(str_val);
  result[result_len] = '\0';
  return result;
}

char *FormatString(const S21SprintfArgs *elems, va_list *args) {
  char *result = s21_NULL;
  switch (elems->format) {
    case 'c':
      result = FormatChar(elems, args);
      break;
    case 's':
      result = FormatStr(elems, args);
      break;
    case 'd':
    case 'i':
      result = FormatInt(elems, args);
      break;
    case 'o':
    case 'x':
    case 'X':
    case 'u':
    case 'p':
      result = FormatUInt(elems, args);
      break;
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      result = FormatDouble(elems, args);
      break;
    case 'n':
      result = FillNPrintf(elems, args);
      break;
  }
  return result;
}

S21SprintfArgs *ParseArgPrintf(const char **p_format, va_list *args) {
  S21SprintfArgs *result = s21_NULL;
  char *ident = s21_strpbrk(*p_format, "cdieEfgGosuxXpn");
  int err = 0;
  if (ident != s21_NULL) {
    result = (S21SprintfArgs *)malloc(sizeof(S21SprintfArgs));
    result->f_acc = 0;
    result->flags = ParseFlags(p_format);
    if (result->flags != -1) {
      if (*(*p_format) == '*') {
        result->width = va_arg(*args, int);
        ++(*p_format);
      } else
        result->width = ParseNum(p_format);
      if (*(*p_format) == '.') {
        result->f_acc = 1;
        ++(*p_format);
        if (*(*p_format) == '*') {
          result->acc = va_arg(*args, int);
          ++(*p_format);
        } else
          result->acc = ParseNum(p_format);
      } else if (*ident == 'e' || *ident == 'E' || *ident == 'f' ||
                 *ident == 'g' || *ident == 'G') {
        result->acc = 6;
      } else
        result->acc = 1;
      result->length = ParseLength(p_format);
      if (result->length != -1)
        result->format = *(*p_format);
      else
        err = 1;
    } else
      err = 1;
  }
  if (err) {
    free(result);
    result = s21_NULL;
  }
  return result;
}

void PrintfVal(char **str, const char **p_format, va_list *args,
               int *fill_count) {
  const char *t_p_format = *p_format;
  S21SprintfArgs *elems = ParseArgPrintf(p_format, args);
  if (elems == s21_NULL) {
    *p_format = t_p_format;
    (*str)[(*fill_count)++] = **p_format;
  } else {
    elems->count_fill_sym = *fill_count;
    char *temp = FormatString(elems, args);
    if (elems->format == 'c' && temp[0] == '\0') {
      (*str)[(*fill_count)++] = temp[0];
      (*str)[*fill_count] = '\0';
    } else if (elems->format != 'n') {
      (*str)[*fill_count] = '\0';
      s21_strncat(*str + *fill_count, temp, s21_strlen(temp));
      *fill_count += s21_strlen(temp);
      free(temp);
    }
    free(elems);
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int fill_count = 0;
  for (const char *p_format = format; *p_format != '\0'; ++p_format) {
    if (*p_format == '%') {
      ++p_format;
      if (*p_format == '%') {
        str[fill_count++] = *p_format;
      } else {
        PrintfVal(&str, &p_format, &args, &fill_count);
      }
    } else {
      str[fill_count++] = *p_format;
    }
  }
  str[fill_count] = '\0';
  va_end(args);
  return fill_count;
}

int IsSeparator(const char *s) {
  int result = 0;
  if (*s == ' ' || *s == '\n' || *s == '\t') {
    result = 1;
  }
  return result;
}

S21SscanfArgs *ParseArgScanf(const char **p_format) {
  S21SscanfArgs *result = s21_NULL;
  char *ident = s21_strpbrk(*p_format, "cdieEfgGosuxXpn");
  int err = 0;
  if (ident != s21_NULL) {
    result = (S21SscanfArgs *)malloc(sizeof(S21SscanfArgs));
    if (**p_format == '*') {
      result->not_fill = 1;
      ++(*p_format);
    } else {
      result->not_fill = 0;
    }
    if (**p_format >= '0' && **p_format <= '9') {
      result->width = ParseNum(p_format);
    } else {
      result->width = -1;
    }
    result->length = ParseLength(p_format);
    if (result->length != -1)
      result->format = *(*p_format);
    else
      err = 1;
  }
  if (err) {
    free(result);
    result = s21_NULL;
  }
  return result;
}

int FillChar(S21SscanfArgs *elems, va_list *args, const char **p_str) {
  int err = 0;
  if (**p_str != '\0') {
    if (!elems->not_fill) {
      char *sym = va_arg(*args, char *);
      *sym = **p_str;
    }
    int count = elems->width == -1 ? 1 : elems->width;
    while (**p_str != '\0' && count > 0) {
      (*p_str)++;
      --count;
    }
  } else {
    err = -1;
  }
  return err;
}

int FillStr(S21SscanfArgs *elems, va_list *args, const char **p_str) {
  int err = 0;
  while (IsSeparator(*p_str)) {
    ++(*p_str);
  }
  if (**p_str != '\0') {
    if (!elems->not_fill) {
      char *str = va_arg(*args, char *);
      while (**p_str != '\0' && !IsSeparator(*p_str) && elems->width != 0) {
        *(str++) = *((*p_str)++);
        --elems->width;
      }
      *str = '\0';
    } else {
      ;
      while (**p_str != '\0' && !IsSeparator(*p_str) && elems->width != 0) {
        (*p_str)++;
        --elems->width;
      }
    }
  } else {
    err = 1;
  }
  return err;
}

void FillIntVal(S21SscanfArgs *elems, va_list *args, long long val) {
  if (elems->length & F_SHORT_SHORT_INT) {
    char *n = va_arg(*args, char *);
    *n = val;
  } else if (elems->length & F_SHORT_INT) {
    short int *n = va_arg(*args, short int *);
    *n = val;
  } else if (elems->length & F_INT) {
    int *n = va_arg(*args, int *);
    *n = val;
  } else if (elems->length & F_LONG_INT) {
    long *n = va_arg(*args, long *);
    *n = val;
  } else {
    long long *n = va_arg(*args, long long *);
    *n = val;
  }
}

int FillNScanf(S21SscanfArgs *elems, va_list *args) {  //заполнить n
  int err = 0;
  FillIntVal(elems, args, elems->count_fill_sym);
  elems->not_fill = 1;
  return err;
}

long double ParseDoubleNum(const char **p_str, S21SscanfArgs *elems) {
  long double result = 0.;
  while (*(*p_str) >= '0' && *(*p_str) <= '9' && elems->width != 0) {
    result *= 10.;
    result += *(*p_str) - '0';
    ++(*p_str);
    --elems->width;
  }
  return result;
}

long double ParseMantis(const char **p_str, S21SscanfArgs *elems) {
  long double result = 0.;
  long double degree = 10.;
  while (*(*p_str) >= '0' && *(*p_str) <= '9' && elems->width != 0) {
    result += (*((*p_str)++) - '0') / degree;
    degree *= 10.;
    --elems->width;
  }
  return result;
}

void ParseEeGg(const char **p_str, int *plus, long double *degree,
               S21SscanfArgs *elems) {
  const char *temp_p_str = *p_str;
  if ((**p_str == 'e' || **p_str == 'E') &&
      elems->width != 0) {  // gG не поддерживается sscanf
    ++(*p_str);
    --elems->width;
    if (**p_str == '+' && elems->width != 0) {
      ++(*p_str);
      --elems->width;
    } else if (**p_str == '-' && elems->width != 0) {
      *plus = 0;
      ++(*p_str);
      --elems->width;
    }
    if (**p_str >= '0' && **p_str <= '9' && elems->width != 0) {
      *degree = ParseDoubleNum(p_str, elems);
    } else {
      *p_str = temp_p_str;
    }
  }
}

void FillDoubleVal(S21SscanfArgs *elems, va_list *args, long double val) {
  if (elems->length & F_Float) {
    float *n = va_arg(*args, float *);
    *n = val;
  } else if (elems->length & F_DOUBLE) {
    double *n = va_arg(*args, double *);
    *n = val;
  } else {
    long double *n = va_arg(*args, long double *);
    *n = val;
  }
}

int IsNan(const char **p_str) {
  int result = 0;
  const char *temp_p_str = *p_str;
  if (**p_str != '\0' && (**p_str == 'n' || **p_str == 'N')) {
    ++(*p_str);
    if (**p_str != '\0' && (**p_str == 'a' || **p_str == 'A')) {
      ++(*p_str);
      if (**p_str != '\0' && (**p_str == 'n' || **p_str == 'N')) {
        ++(*p_str);
        result = 1;
      } else {
        *p_str = temp_p_str;
      }
    } else {
      *p_str = temp_p_str;
    }
  }
  return result;
}

int IsInf(const char **p_str) {
  int result = 0;
  const char *temp_p_str = *p_str;
  if (**p_str != '\0' && (**p_str == 'i' || **p_str == 'I')) {
    ++(*p_str);
    if (**p_str != '\0' && (**p_str == 'n' || **p_str == 'N')) {
      ++(*p_str);
      if (**p_str != '\0' && (**p_str == 'f' || **p_str == 'F')) {
        ++(*p_str);
        result = 1;
      } else {
        *p_str = temp_p_str;
      }
    } else {
      *p_str = temp_p_str;
    }
  }
  return result;
}

int FillDouble(S21SscanfArgs *elems, va_list *args, const char **p_str) {
  int err = 0;
  while (IsSeparator(*p_str)) ++(*p_str);
  int sign_plus = 1;
  const char *temp_p_str = *p_str;
  if (**p_str != '\0' && (**p_str == '+' || **p_str == '-') &&
      elems->width != 0) {
    sign_plus = *((*p_str)++) == '+' ? 1 : 0;
    --elems->width;
  }
  long double val = 0;
  if (elems->width != 0 && elems->width != 1 && elems->width != 2 &&
      IsNan(p_str)) {
    val = sign_plus ? -NAN : -NAN;  // как получить -nan
    if (!elems->not_fill && !err) FillDoubleVal(elems, args, val);
  } else if (elems->width != 0 && elems->width != 1 && elems->width != 2 &&
             IsInf(p_str)) {
    val = sign_plus ? INFINITY : -INFINITY;
    if (!elems->not_fill && !err) FillDoubleVal(elems, args, val);
  } else if (**p_str != '\0' &&
             ((**p_str >= '0' && **p_str <= '9') || **p_str == '.') &&
             elems->width != 0) {
    long double val = ParseDoubleNum(p_str, elems);
    long double degree = 0.;
    if (**p_str == '.' && elems->width != 0) {
      ++(*p_str);
      --elems->width;
      val += ParseMantis(p_str, elems);
    }
    val *= sign_plus ? 1. : -1.;
    ParseEeGg(p_str, &sign_plus, &degree, elems);
    for (int i = 0; i < degree; ++i)
      val *= sign_plus == 1 ? 10. : 0.1;  //можно так сделать, так как degree =
                                          // 0, если plus не назначен
    if (!elems->not_fill) FillDoubleVal(elems, args, val);
  } else {
    *p_str = temp_p_str;
    err = **p_str == '\0' ? -1 : 1;
  }
  return err;
}

int isOverflowMult(long long val1, long long val2) {
  long long result = val1 * val2;
  return val1 == result / val2 ? 0 : 1;
}

int isOverflowSum(long long val1, long long val2) {
  return (LLONG_MAX - val1 >= val2) ? 0 : 1;
}

int isOverflowSub(long long val1, long long val2) {
  return (LLONG_MIN + val2 <= val1) ? 0 : 1;
}

unsigned long long GetUVal(S21SscanfArgs *elems, long long temp_res) {
  unsigned long long result = 0;
  switch (elems->length) {
    case F_SHORT_SHORT_INT:
      result = UCHAR_MAX - temp_res + 1;
      break;
    case F_SHORT_INT:
      result = USHRT_MAX - temp_res + 1;
      break;
    case F_INT:
      result = UINT_MAX - temp_res + 1;
      break;
    case F_LONG_INT:
      result = ULONG_MAX - temp_res + 1;
      break;
    case F_LONG_LONG_INT:
      result = ULLONG_MAX - temp_res + 1;
      break;
  }
  return result;
}

unsigned long long ParseOct(const char **p_str, S21SscanfArgs *elems,
                            int sign_plus) {
  unsigned long long result = 0;
  long long temp_res = 0;
  int is_overflow = 0;
  while (**p_str >= '0' && **p_str <= '7' && elems->width != 0) {
    if (isOverflowMult(temp_res, 8)) {
      temp_res = sign_plus ? LLONG_MAX : LLONG_MIN;
      is_overflow = 1;
      break;
    } else
      temp_res *= 8;
    int dig = *((*p_str)++) - '0';
    if (!sign_plus && isOverflowSub(temp_res, dig)) {
      is_overflow = 1;
      temp_res = LLONG_MIN;
      break;
    } else if (sign_plus && isOverflowSum(temp_res, dig)) {
      is_overflow = 1;
      temp_res = LLONG_MAX;
      break;
    } else
      temp_res += dig;
    --elems->width;
  }
  result = sign_plus ? (unsigned long long)temp_res : GetUVal(elems, temp_res);
  if (is_overflow)
    while (*(*p_str) >= '0' && *(*p_str) <= '9' && elems->width != 0) {
      ++(*p_str);
      --elems->width;
    }
  return result;
}

void SkipHexPrefix(const char **p_str, S21SscanfArgs *elems) {
  if (**p_str != '\0' && **p_str == '0' && elems->width != 0) {
    ++(*p_str);
    --elems->width;
  }
  if (**p_str != '\0' && (**p_str == 'x' || **p_str == 'X') &&
      elems->width != 0) {
    if (elems->width != 1) ++(*p_str);
    --elems->width;
  }
}

int GetHexDigit(const char **p_str) {
  int dig;
  if (**p_str >= '0' && **p_str <= '9')
    dig = (*((*p_str)++) - '0');
  else if (**p_str >= 'a' && **p_str <= 'f')
    dig = (*((*p_str)++) - 87);
  else
    dig = (*((*p_str)++) - 55);
  return dig;
}

unsigned long long ParseHex(const char **p_str, S21SscanfArgs *elems,
                            int sign_plus) {
  unsigned long long result = 0;
  long long temp_res = 0;
  int is_overflow = 0;
  SkipHexPrefix(p_str, elems);
  while (((**p_str >= '0' && **p_str <= '9') ||
          (**p_str >= 'a' && **p_str <= 'f') ||
          (**p_str >= 'A' && **p_str <= 'F')) &&
         elems->width != 0) {
    if (isOverflowMult(temp_res, 16)) {
      temp_res = sign_plus ? LLONG_MAX : LLONG_MIN;
      is_overflow = 1;
      break;
    } else
      temp_res *= 16;
    int dig = GetHexDigit(p_str);
    if (!sign_plus && isOverflowSub(temp_res, dig)) {
      is_overflow = 1;
      temp_res = LLONG_MIN;
      break;
    } else if (sign_plus && isOverflowSum(temp_res, dig)) {
      is_overflow = 1;
      temp_res = LLONG_MAX;
      break;
    } else
      temp_res += dig;
    --elems->width;
  }
  result = sign_plus ? (unsigned long long)temp_res : GetUVal(elems, temp_res);
  if (is_overflow) {
    while (((**p_str >= '0' && **p_str <= '9') ||
            (**p_str >= 'a' && **p_str <= 'f') ||
            (**p_str >= 'A' && **p_str <= 'F')) &&
           elems->width != 0) {
      ++(*p_str);
      --elems->width;
    }
  }
  return result;
}

void FillUIntVal(S21SscanfArgs *elems, va_list *args, unsigned long long val) {
  if (elems->format == 'p') {
    unsigned long long **n = va_arg(*args, unsigned long long **);
    *n = (unsigned long long *)val;
  } else if (elems->length & F_SHORT_SHORT_INT) {
    unsigned char *n = va_arg(*args, unsigned char *);
    *n = val;
  } else if (elems->length & F_SHORT_INT) {
    unsigned short int *n = va_arg(*args, unsigned short int *);
    *n = val;
  } else if (elems->length & F_INT) {
    unsigned int *n = va_arg(*args, unsigned int *);
    *n = val;
  } else if (elems->length & F_LONG_INT) {
    unsigned long *n = va_arg(*args, unsigned long *);
    *n = val;
  } else {
    unsigned long long *n = va_arg(*args, unsigned long long *);
    *n = val;
  }
}

long long ParseDec(const char **p_str, S21SscanfArgs *elems, int sign_plus) {
  long long result = 0.;
  int is_overflow = 0;
  while (*(*p_str) >= '0' && *(*p_str) <= '9' && elems->width != 0) {
    if (isOverflowMult(result, 10)) {
      result = sign_plus ? LLONG_MAX : LLONG_MIN;
      is_overflow = 1;
      break;
    } else {
      result *= 10;
    }
    int dig = *((*p_str)++) - '0';
    if (!sign_plus && isOverflowSub(result, dig)) {
      result = LLONG_MIN;
      is_overflow = 1;
      break;
    } else if (sign_plus && isOverflowSum(result, dig)) {
      result = LLONG_MAX;
      is_overflow = 1;
      break;
    } else {
      result += sign_plus ? dig : -dig;
    }
    --elems->width;
  }
  if (is_overflow) {
    while (*(*p_str) >= '0' && *(*p_str) <= '9' && elems->width != 0) {
      ++(*p_str);
      --elems->width;
    }
  }
  return result;
}

int FillDec(S21SscanfArgs *elems, va_list *args, const char **p_str,
            int sign_plus) {
  int res = 0;
  if (**p_str != '\0' && (**p_str >= '0' && **p_str <= '9') &&
      elems->width != 0) {
    long long val = ParseDec(p_str, elems, sign_plus);
    if (!elems->not_fill) {
      elems->format == 'd' ? FillIntVal(elems, args, val)
                           : FillUIntVal(elems, args, (unsigned long long)val);
    }
    res = 1;
  }
  return res;
}

int FillHex(S21SscanfArgs *elems, va_list *args, const char **p_str,
            int sign_plus) {
  int res = 0;
  if (**p_str != '\0' &&
      ((**p_str >= '0' && **p_str <= '9') ||
       (**p_str >= 'a' && **p_str <= 'f') ||
       (**p_str >= 'A' && **p_str <= 'F')) &&
      elems->width != 0) {  // hex
    unsigned long long int val = ParseHex(p_str, elems, sign_plus);
    if (!elems->not_fill) {
      FillUIntVal(elems, args, val);
    }
    res = 1;
  }
  return res;
}

int FillOct(S21SscanfArgs *elems, va_list *args, const char **p_str,
            int sign_plus) {
  int res = 0;
  if (**p_str != '\0' && (**p_str >= '0' && **p_str <= '7') &&
      elems->width != 0) {
    unsigned long long int val = ParseOct(p_str, elems, sign_plus);
    if (!elems->not_fill) {
      FillUIntVal(elems, args, val);
    }
    res = 1;
  }
  return res;
}

int FillIntOther(S21SscanfArgs *elems, va_list *args, const char **p_str) {
  int err = 0;
  while (IsSeparator(*p_str)) ++(*p_str);
  int sign_plus = 1;
  const char *temp_p_str = *p_str;
  if (**p_str != '\0' && (**p_str == '+' || **p_str == '-') &&
      elems->width != 0) {
    sign_plus = **p_str == '+' ? 1 : 0;
    ++(*p_str);
    --elems->width;
  }
  int f_fill = 0;
  switch (elems->format) {
    case 'd':
    case 'u':
      f_fill = FillDec(elems, args, p_str, sign_plus);
      break;
    case 'X':
    case 'x':
    case 'p':
      f_fill = FillHex(elems, args, p_str, sign_plus);
      break;
    case 'o':
      f_fill = FillOct(elems, args, p_str, sign_plus);
      break;
  }
  if (!f_fill) {
    *p_str = temp_p_str;
    err = **p_str == '\0' ? -1 : 1;
  }
  return err;
}

int FillInt(S21SscanfArgs *elems, va_list *args, const char **p_str) {
  int err = 0;
  while (IsSeparator(*p_str)) {
    ++(*p_str);
  }
  const char *temp_p_str = *p_str;
  if (*temp_p_str != '\0' && (*temp_p_str == '+' || *temp_p_str == '-')) {
    ++temp_p_str;
  }
  if (*temp_p_str != '\0' && *temp_p_str == '0' &&
      (*(temp_p_str + 1) == 'x' || *(temp_p_str + 1) == 'X')) {
    elems->format = 'x';
    err = FillIntOther(elems, args, p_str);
  } else if (*temp_p_str == '0') {
    elems->format = 'o';
    err = FillIntOther(elems, args, p_str);
  } else if (*temp_p_str >= '0' && *temp_p_str <= '9') {
    elems->format = 'd';
    err = FillIntOther(elems, args, p_str);
  } else {
    err = **p_str == '\0' ? -1 : 1;
  }
  return err;
}

int FillValue(S21SscanfArgs *elems, va_list *args, const char **p_str) {
  int err = 0;
  switch (elems->format) {
    case 'c':
      err = FillChar(elems, args, p_str);
      break;
    case 's':
      err = FillStr(elems, args, p_str);
      break;
    case 'i':
      err = FillInt(elems, args, p_str);
      break;
    case 'd':
    case 'o':
    case 'x':
    case 'X':
    case 'p':
    case 'u':
      err = FillIntOther(elems, args, p_str);
      break;
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      err = FillDouble(elems, args, p_str);
      break;
    case 'n':
      err = FillNScanf(elems, args);
      break;
  }
  return err;
}

int ScanVal(const char *str, const char **p_str, const char **p_format,
            va_list *args, int *fill_count) {
  int err = 0;
  S21SscanfArgs *elems = ParseArgScanf(p_format);
  if (elems != s21_NULL) {
    if (**p_str == '\0' && elems->format != 'n' && elems->format != 's') {
      err = -1;
    } else {
      elems->count_fill_sym = labs(*p_str - str);  //почему тут минус?
      err = FillValue(elems, args, p_str);
      if (err) {
        free(elems);
      } else {
        *fill_count += elems->not_fill ? 0 : 1;
        free(elems);
      }
    }
  } else {
    err = 1;
  }
  return err;
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int fill_count = 0;
  const char *p_str = str;
  int err = 0;
  for (const char *p_format = format; *p_format != '\0'; ++p_format) {
    if (IsSeparator(p_str) && IsSeparator(p_format))
      while (IsSeparator(p_str)) ++p_str;
    while (*p_format == *p_str && *p_format != '%' && *p_format != '\0') {
      ++p_format;
      ++p_str;
    }
    if (*p_format != '%' && !IsSeparator(p_str) && !IsSeparator(p_format) &&
        *p_format != *p_str)
      break;
    if (*p_format == '%') {
      ++p_format;
      if (*p_format == '%') {
        ++p_str;
      } else {
        err = ScanVal(str, &p_str, &p_format, &args, &fill_count);
        if (err) {
          break;
        }

        // S21SscanfArgs *elems = ParseArgScanf(&p_format);
        // if (elems == s21_NULL) {
        //   break;
        // } else {
        //   if (*p_str == '\0' && elems->format != 'n' &&
        //       elems->format != 's') {  //под вопросом
        //     err = -1;
        //     break;
        //   }
        //   elems->count_fill_sym = labs(p_str - str);  //почему тут минус?
        //   err = FillValue(elems, &args, &p_str);
        //   if (err) {
        //     free(elems);
        //     break;
        //   } else
        //       fill_count += elems->not_fill ? 0 : 1;
        //   free(elems);
        // }
      }
    }
  }
  va_end(args);
  return err == -1 ? err : fill_count;
}
