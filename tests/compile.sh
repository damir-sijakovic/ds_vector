#!/bin/bash
gcc -o doublevec_insert_free ./doublevec_insert_free.c
gcc -o stepvec_insert_free ./stepvec_insert_free.c
gcc -o lastitem ./lastitem.c
gcc -o append_item ./append_item.c
gcc -o prepend_item ./prepend_item.c
gcc -o shrinkToFit ./shrinkToFit.c
gcc -o pack ./pack.c
gcc -o forEach ./forEach.c
gcc -o resize ./resize.c

# to check memory run: valgrind ./program
