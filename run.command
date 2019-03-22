g++ aes.c -I/usr/include/mysql  -L/usr/lib/x86_64-linux-gnu  -lmariadbclient -lpthread -lz -lm -ldl BlackGlow.cpp -o blackglow	


g++ aes.c -I/usr/include/mysql  -L/usr/lib/x86_64-linux-gnu  -lmariadbclient -lpthread -lz -lm -ldl Spark0.cpp -o spark0	


g++ -g test.cpp -o test -lpthread aes.c	


g++ aes.c -I/usr/include/mysql  -L/usr/lib/x86_64-linux-gnu  -lmariadbclient -lpthread -lz -lm -ldl BlackGlow.cpp -o blackglow -g	


