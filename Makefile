# Збірка: make        Запуск прикладу: make run
CC     = gcc
CFLAGS = -O2 -Wall -Wno-unused-function
SRC    = parser.tab.c lex.yy.c ast.c sema.c interp.c codegen.c main.c

c2py: $(SRC) ast.h sema.h
	$(CC) $(CFLAGS) -o $@ $(SRC) -lm

parser.tab.c parser.tab.h: parser.y
	bison -d -v parser.y          # -v створює parser.output (таблиця станів LALR)

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

run: c2py
	./c2py examples/demo.c -t
	@echo "===== Виконання згенерованого Python ====="
	python3 out.py

clean:
	rm -f c2py lex.yy.c parser.tab.c parser.tab.h parser.output out.py ast.json web/ast_data.js
