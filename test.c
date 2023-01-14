#include <dirent.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "test.h"
#include "aux.h"
#include "opcode_map/opcode.h"
#include "register_module/register.h"
#include "byte_reader/reader.h"
struct test
{
    int argc;
    char **argv;
};

void run_test(){
    DIR *d;
    struct dirent *dir;
    d = opendir("../sample/");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
        if(dir->d_type==8){
            execute_test( dir->d_name);
        }
        }
        closedir(d);
    }
}
struct test str_split(char* a_str, const char a_delim)
{   struct test output;
    char** result    = 0;
    int count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    
    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
    
    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * (count+1));

    if (result)
    {
        size_t idx  = 1;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count);
        *(result + idx) = 0;
    }
    printf("%i\n",count);

    output.argc=count;
    output.argv=result;
    return output;
}
void execute_test(char *name){
     FILE* ptr;
    char *ch;
 
    // Opening file in reading mode
    ptr = fopen(strcatn(2,BUFSIZ,"../sample/" ,name), "r");
 
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }
 struct test output;
    char str[255];
    // Printing what is written in file
    // character by character using loop.
    while (fgets(str, 255, ptr) != NULL) {
       output = str_split(str, ' ');
    }
    // Closing the file
    fclose(ptr);
    set_reader(output.argc, &output.argv);
    while(is_next()){
        unsigned char byte = get_next_byte();
        decode(byte);
    }
}