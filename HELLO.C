#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

static const char *page_start =
  "<!doctype html>"
  "<html lang='en'><head><meta charset='utf-8'>"
  "<meta name='viewport' content='width=device-width,initial-scale=1'>"
  "<title>C Lab | Tiny Web Server</title>"
  "<style>"
  ":root{--ink:#18232b;--muted:#617078;--paper:#f4f0e8;--card:#fffdf8;--accent:#e5633f;--line:#d9d2c6}"
  "*{box-sizing:border-box}body{margin:0;background:var(--paper);color:var(--ink);font-family:Georgia,serif}"
  ".shell{max-width:1040px;margin:0 auto;padding:26px 22px 54px}"
  "nav{display:flex;justify-content:space-between;align-items:center;font-family:Arial,sans-serif;font-size:13px;letter-spacing:.08em;text-transform:uppercase}"
  ".mark{font-weight:800;color:var(--accent)}.status{color:var(--muted)}"
  ".hero{padding:92px 0 70px;max-width:760px}.kicker{font:700 12px Arial,sans-serif;letter-spacing:.16em;text-transform:uppercase;color:var(--accent)}"
  "h1{font-size:clamp(48px,8vw,92px);line-height:.92;letter-spacing:-.04em;margin:17px 0 24px;font-weight:500}"
  ".intro{font:20px/1.5 Arial,sans-serif;color:var(--muted);max-width:590px}"
  ".layout{display:grid;grid-template-columns:1.15fr .85fr;gap:22px;align-items:stretch}"
  ".panel{background:var(--card);border:1px solid var(--line);padding:30px;box-shadow:8px 8px 0 rgba(24,35,43,.08)}"
  ".panel h2{font-size:28px;font-weight:500;margin:0 0 8px}.panel p{font:14px/1.5 Arial,sans-serif;color:var(--muted);margin:0 0 24px}"
  "label{display:block;font:700 11px Arial,sans-serif;letter-spacing:.1em;text-transform:uppercase;margin:17px 0 7px}"
  "input{width:100%;border:1px solid var(--line);background:#fff;padding:14px;font:20px Georgia,serif;color:var(--ink)}"
  "input:focus{outline:2px solid var(--accent);outline-offset:2px}button{border:0;background:var(--accent);color:white;padding:15px 22px;margin-top:24px;font:700 13px Arial,sans-serif;letter-spacing:.08em;text-transform:uppercase;cursor:pointer}"
  "button:hover{background:#c94f30}.answer{margin-top:24px;padding:16px;background:#f0e8dc;border-left:4px solid var(--accent);font:17px Arial,sans-serif}.answer strong{font-size:28px;font-family:Georgia,serif}"
  ".notes{display:flex;flex-direction:column;justify-content:space-between}.number{font-size:86px;line-height:1;color:var(--accent);font-weight:500}.notes ul{padding:0;margin:28px 0 0;list-style:none;font:14px/2 Arial,sans-serif;color:var(--muted)}.notes li{border-top:1px solid var(--line);padding:10px 0}.notes li::before{content:'+';color:var(--accent);font-weight:bold;margin-right:10px}"
  "footer{font:12px Arial,sans-serif;color:var(--muted);margin-top:62px;border-top:1px solid var(--line);padding-top:16px}@media(max-width:700px){.hero{padding:65px 0 48px}.layout{grid-template-columns:1fr}.panel{padding:24px}.number{font-size:64px}}"
  "</style></head><body><main class='shell'><nav><span class='mark'>C / 01</span><span class='status'>localhost // online</span></nav>"
  "<section class='hero'><div class='kicker'>A tiny website, written in C</div><h1>Make the machine<br><em>answer.</em></h1><div class='intro'>This page is served directly by a lightweight C program. Enter two numbers and let the server do the arithmetic.</div></section>"
  "<section class='layout'><div class='panel'><h2>Quick addition</h2><p>Your request travels to C, gets calculated, and comes back as HTML.</p>"
  "<form method='get' action='/'><label for='first'>First number</label><input id='first' name='a' type='number' step='any' required placeholder='12'>"
  "<label for='second'>Second number</label><input id='second' name='b' type='number' step='any' required placeholder='30'><button type='submit'>Calculate sum</button></form>";

static void get_value(const char *request, const char *key, char *value, size_t value_size)
{
  const char *start = strstr(request, key);
  const char *end;
  size_t length;

  value[0] = '\0';
  if (start == NULL) {
    return;
  }

  start += strlen(key);
  end = strpbrk(start, "& ");
  length = end == NULL ? strlen(start) : (size_t)(end - start);
  if (length >= value_size) {
    length = value_size - 1;
  }
  memcpy(value, start, length);
  value[length] = '\0';
}

static void send_page(SOCKET client, const char *request)
{
  char first_text[64];
  char second_text[64];
  char result[160] = "";
  char response[16000];
  char body[15000];
  char *page_end;
  double first;
  double second;
  int body_length;

  get_value(request, "a=", first_text, sizeof(first_text));
  get_value(request, "b=", second_text, sizeof(second_text));
  if (first_text[0] != '\0' && second_text[0] != '\0') {
    first = strtod(first_text, &page_end);
    second = strtod(second_text, &page_end);
    snprintf(result, sizeof(result), "<div class='answer'>The answer is <strong>%.2f</strong></div>", first + second);
  }

  body_length = snprintf(body, sizeof(body), "%s%s</div><div class='panel notes'><div><div class='number'>8080</div><h2>One small port.</h2><p>A simple beginning for learning how browsers and servers talk.</p></div><ul><li>Written in C</li><li>Served over HTTP</li><li>No framework required</li></ul></div></section><footer>C LAB / RUNNING ON YOUR MACHINE</footer></main></body></html>", page_start, result);
  snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: %d\r\nConnection: close\r\n\r\n%s", body_length, body);
  send(client, response, (int)strlen(response), 0);
}

int main(void)
{
  WSADATA wsa_data;
  SOCKET server;
  SOCKET client;
  struct sockaddr_in address;
  int address_length = sizeof(address);
  char request[4096];
  int received;

  if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
    fprintf(stderr, "Could not start Winsock.\n");
    return 1;
  }

  server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (server == INVALID_SOCKET) {
    fprintf(stderr, "Could not create the server socket.\n");
    WSACleanup();
    return 1;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  address.sin_port = htons(PORT);
  if (bind(server, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR || listen(server, 5) == SOCKET_ERROR) {
    fprintf(stderr, "Could not listen on http://localhost:%d\n", PORT);
    closesocket(server);
    WSACleanup();
    return 1;
  }

  printf("C Lab is live at http://localhost:%d\nPress Ctrl+C to stop.\n", PORT);
  while (1) {
    client = accept(server, (struct sockaddr *)&address, &address_length);
    if (client == INVALID_SOCKET) {
      continue;
    }
    received = recv(client, request, sizeof(request) - 1, 0);
    if (received > 0) {
      request[received] = '\0';
      send_page(client, request);
    }
    closesocket(client);
  }
}