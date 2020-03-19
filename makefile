diseaseMonitor:
		@echo "Compiling disease monitor...";
		gcc -I  ./headfiles ./src/diseaseMonitor.c ./src/max_heap.c ./src/avl_tree.c ./src/hash_table.c ./src/functions.c ./src/record_list.c ./src/queries.c -D_XOPEN_SOURCE -o  ./build/diseaseMonitor
		
debug:
		@echo "Preparing for debugging..";
		gcc -I  ./headfiles ./src/diseaseMonitor.c ./src/avl_tree.c  ./src/hash_table.c ./src/functions.c  ./src/record_list.c ./src/queries.c -D_XOPEN_SOURCE -o  ./build/diseaseMonitor -g3

clean: 
	rm  ./build/diseaseMonitor
