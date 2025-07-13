# How to run the app locally?
To run this app locally on your machine you will need
1. POSIX shell (MacOS/Linux/BSD)
2. gcc/clang (C/C++ compiler)
3. golang (Go compiler)
## Server
```bash
cd server
gcc main.c -o server
./server
```
Default port for server is <strong>8080</strong>. You can change this if you want from the <strong>server/loader.h</strong> file by changing a <strong>DEFINE</strong>
## Client
``` bash
cd client
go run main.go 127.0.0.1:PORT
```
Replace "PORT" with the <strong>port</strong> that you are using for the server