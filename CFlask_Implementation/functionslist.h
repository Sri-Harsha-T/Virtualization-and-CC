
char* rootmsg(char* quer);
char* square(char* p);
char* cube(char* p);
char* fibonacci(char* p);
char* prime(char* p);
char* pingpong(char* quer);
char* helloworld(char* quer);

typedef char* (*farr)(char*);
// char* url_list[32] = {"/", "/square", "/cube", "/hello", "/prime", "/fibonacci", "/pingpong", "/helloworld", "/arithmetic/prime", "/arithmetic/fibonacci"};
farr func_arr[10] = {&rootmsg, &square, &cube, &helloworld, &prime, &fibonacci, &pingpong, &helloworld, &prime, &fibonacci};


