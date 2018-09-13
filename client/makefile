CC = gcc
ARG = client.c filesel.c calc.c cale.c personal_information.c create_leftbox.c create_rightbox.c f.c history.c login_failed.c register_window.c addFace.c
all:
	$(CC) -g -o client $(ARG) `pkg-config --cflags --libs gtk+-2.0 gthread-2.0`
