libft :
	$(MAKE) -C ./lib
	mv lib/libft.a ./
	$(MAKE) -C ./lib clean

test : libft
	gcc -I include/ src/env/*.c src/cmd/*.c src/*.c -L. -lft