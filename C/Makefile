CC=gcc
CFLAGS="-lm"
PREFIX="/usr/local"
DESTDIR=""

all:
	for i in $$(ls Projects/NumberSystem/*.c); do \
		$(CC) $$i -o $$(basename $$i .c); \
		mv $$(basename $$i .c) $$PWD/Out/; \
	done; 
	for i in $$(ls Projects/*.c); do \
		$(CC $(CFLAGS)) $$i -o $$(basename $$i .c); \
		mv $${i%.c} $$PWD/Out/; \
	done
numbersystem:
	$(CC) Projects/NumberSystem/DecimalToBinary.c -o Bin/DecimalToBinary
install:
	install -v Bin/* $(PREFIX)
uninstall:
	rm -v $(PREFIX)/DecimalToBinary
