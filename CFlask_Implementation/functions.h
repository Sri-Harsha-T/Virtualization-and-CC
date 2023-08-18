#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* url_list[32] = {"/", "/square", "/cube", "/hello", "/prime", "/fibonacci", "/pingpong", "/helloworld", "/arithmetic/prime", "/arithmetic/fibonacci"};

// int url_index_map(char *url_s){
// 	for(int i =0 ; i<6;i++){
// 		if(strcmp(url_s, url_list[i]) == 0){
// 			return i;
// 		}
// 	}
// 	return -1;
// }

int url_index_map(char *url_s);

