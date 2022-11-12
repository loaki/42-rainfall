# Level0
ip: 196.168.56.101

Login shows an executable names level0 avaiable. we scp it to local:

    scp -P 4242 level0@196.168.56.101:~/level0 .

We decompile it with ghidra and check the main function (available in source.c).
Check 0x1a7 to decimal is 423. The function runs if the arg is equal to 423 only and execute /bin/sh.

    $ ./level0 423
    $ cat /home/user/level1/.pass
    > 1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
