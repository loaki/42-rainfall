# bonus3

## vars
local_98[64] -> this is the buffer from reading the local_14

local_14 -> opens end user .pass file.

iVar2 -> atoi of argv[1]

## analysis


If the file is opened successfully and there is 1 arg given then local_98 will store the 66 bytes read from user .pass file.

Then he will set the nth byte to 0 depending on atoi of argv[1]. 
It will then compare argv[1] with local_98 and if they are equal it launches /bin/sh.

## Finish

We set argv[1] to empty string "", this way the first byte of local98 will be 0 and our argv[1] string compared by strcmp will be 0 as well.

    $ ./bonus3 ""
    $ cat /home/user/end/.pass
    3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
    
## The End

    end@RainFall:~$ cat end 
    Congratulations graduate!
