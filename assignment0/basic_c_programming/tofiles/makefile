all : tofiles_cont tofiles_noncont

tofiles_cont : tofiles_cont.c
	gcc -O1 -o tofiles_cont tofiles_cont.c
	gcc -O1 -o tofiles_cont_fwrite tofiles_cont_fwrite.c
tofiles_noncont : tofiles_noncont.c
	gcc -O1 -o tofiles_noncont tofiles_noncont.c
	gcc -O1 -o tofiles_noncont_fwrite tofiles_noncont_fwrite.c
clean :
	rm -f matrix.*
	rm -f tofiles_cont
	rm -f tofiles_cont_fwrite
	rm -f tofiles_noncont
	rm -f tofiles_noncont_fwrite

