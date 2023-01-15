struct test {
  int argc;
  char **argv;
};
struct test str_split(char *a_str, const char a_delim) ;
char *strcatn(unsigned nstr, unsigned max_len, ...);
void write_file(char *name, char *result);