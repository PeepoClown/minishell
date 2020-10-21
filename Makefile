libft :
	$(MAKE) -C ./lib
	mv lib/libft.a ./
	$(MAKE) -C ./lib clean

test : libft
	gcc -I include/ src/*/*.c src/*.c -L. -lft -o ./minishell
	rm -rf libft.a