#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <time.h>
#include <string.h>

#include "civetweb.h"
#include "functions.c"
// #include "functions.h"
// #include "functionslist.h"
extern farr func_arr[];
extern char * url_list[32];

#define DOCUMENT_ROOT "."
#define EXAMPLE_URI "/example"
#define EXIT_URI "/exit"
int exitNow = 0;

int CallHandler(struct mg_connection *conn, void *cbdata)
{
    const struct mg_request_info *req_info = mg_get_request_info(conn);
    char addr[32];
    strcpy(addr, req_info->uri);
    // printf("Addr: %s\n", addr);
	char qstr[32];
	char quer[32];
	if(req_info->query_string == NULL)strcpy(qstr, "No query");
	else strcpy(qstr,req_info->query_string);
	// printf("Query: %s\n", qstr);
	char var_name[32];
	char *delim = "=";
	int count = 0;
	char *token = strtok(qstr, delim);

	int x = mg_get_var(req_info->query_string, 32, token, quer, 32);
	// printf("%d\nVar: %s\n",x,  quer);

    // printf("Function Index:%d\n", url_index_map(addr));
	if(x<0||strcmp(quer, "")==0) strcpy(quer, "No query");
    int ind = url_index_map(addr);
    // printf("Function returns: %s\n" , func_arr[ind](quer));
    if(ind>=0){

        mg_printf(conn, "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n");
        mg_printf(conn, "<html><body>");
        mg_printf(conn, "%s", func_arr[ind](quer));
        mg_printf(conn, "</body></html>\n");
    }
    return 1;
}


int main(int argc, char *argv[])
{
    if(argc!=3){
		printf("Usage cflask <port> <thread_num>\n");
		return 0;
	}
	
	char port[10];
	strcpy(port, argv[1]);
	char t_num[10];
       	strcpy(t_num, argv[2]);
	printf("Given args, port: %s, number of threads: %s\n", port, t_num);
	
    const char *options[] = {
                            "listening_ports", port,
                            "request_timeout_ms", "10000",
                            "error_log_file", "error.log",
                            "num_threads", t_num,
                            #ifdef USE_WEBSOCKET
	                         "websocket_timeout_ms",
	                         "3600000",
#endif
#ifndef NO_SSL
	                         "ssl_certificate",
	                         "../../resources/cert/server.pem",
#endif
	                         0
                            };

    struct mg_callbacks callbacks;
    struct mg_context *ctx;
    struct mg_server_ports ports[32];
    int port_cnt, n;
    // int err = 0;

    /*Start CivetWeb web server*/
    memset(&callbacks, 0, sizeof(callbacks));
    ctx = mg_start(&callbacks, 0, options);

    // mg_set_request_handler(ctx, "/", CallHandler, (void *)0);
	for(int i =0; i<10;i++){
		mg_set_request_handler(ctx, url_list[i], CallHandler, (void *)0);
	}

    for (n = 0; n < port_cnt && n < 32; n++) {
		const char *proto = ports[n].is_ssl ? "https" : "http";
		const char *host;

		if ((ports[n].protocol & 1) == 1) {
			/* IPv4 */
			host = "127.0.0.1";
			printf("Browse files at %s://%s:%i/\n", proto, host, ports[n].port);
			printf("Run example at %s://%s:%i%s\n",
			       proto,
			       host,
			       ports[n].port,
			       EXAMPLE_URI);
			printf(
			    "Exit at %s://%s:%i%s\n", proto, host, ports[n].port, EXIT_URI);
			printf("\n");
		}

		if ((ports[n].protocol & 2) == 2) {
			/* IPv6 */
			host = "[::1]";
			printf("Browse files at %s://%s:%i/\n", proto, host, ports[n].port);
			printf("Run example at %s://%s:%i%s\n",
			       proto,
			       host,
			       ports[n].port,
			       EXAMPLE_URI);
			printf(
			    "Exit at %s://%s:%i%s\n", proto, host, ports[n].port, EXIT_URI);
			printf("\n");
		}
	}

    while(!exitNow)
    {
        sleep(1);
    }

	// return 0;
}