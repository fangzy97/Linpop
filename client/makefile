CC = gcc
ARG = client.c filesel.c
all:
	$(CC) -g -o client $(ARG) `pkg-config --cflags --libs gtk+-2.0 gthread-2.0`
