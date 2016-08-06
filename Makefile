all: archive

archive:
	tar -cf my_prog-`date +%y%m%d%H%M`.tar agent  client client_sql server README Makefile
