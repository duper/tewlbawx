/* Copyright 2016 Google Inc
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<err.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void) {
	static struct addrinfo hints = { 0 }, *res = NULL;
	register signed int r = 0x0;
  const char ifs_def[]=" \t\n";
  const char *ifs = NULL;

	memset(&hints, '\0', sizeof hints);

	hints.ai_socktype = SOCK_STREAM;

	if((r = getaddrinfo("127.0.0.1", "domain", &hints, &res)))
		errx(1, "getaddrinfo: %s", gai_strerror(r));

  ifs = getenv("IFS");

  if(!ifs)
    ifs = ifs_def;

  fprintf(stdout, "flags: %d", res->ai_flags);
  fputc(*ifs, stdout);
  fprintf(stdout, "family: %d", res->ai_family);
  fputc(*ifs, stdout);
  fprintf(stdout, "socktype: %d", res->ai_socktype);
  fputc(*ifs, stdout);
  fprintf(stdout, "protocol: %d", res->ai_protocol);
  fputc(*ifs, stdout);
  fprintf(stdout, "socktype: %d", res->ai_socktype);
  fputc(*ifs, stdout);
  fprintf(stdout, "addrlen: %d", res->ai_addrlen);
  fputc(*ifs, stdout);
  fprintf(stdout, "canonname: %s", res->ai_canonname);
  fputc(*ifs, stdout);
  fputs("\r\n", stdout);

  freeaddrinfo(res);

	exit(EXIT_SUCCESS);
}
