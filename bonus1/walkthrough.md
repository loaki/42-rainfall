# bonus1

looking at ghidra, we have a program with 2 arguments. 
- local_14 > argv[1]: should be a number < 10
- local_3c[40] > argv[2]: this is where we will overflow. 

    memcpy(local_3c,*(void **)(param_2 + 8),local_14 * 4);
    if (local_14 == 0x574f4c46) {
      execl("/bin/sh","sh",0);
    }

void * memcpy( void * destination, const void * source, size_t size );  

memcpy takes size_t as 3rd argument which is an unsigned int. If we give it a signed int it will be <10 so we have enough space for the buffer 