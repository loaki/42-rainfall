// function o()

void o(void)

{
  system("/bin/sh");
                    /* WARNING: Subroutine does not return */
  _exit(1);
}

// function n()

void n(void)

{
  char local_20c [520];
  
  fgets(local_20c,0x200,stdin);
  printf(local_20c);
                    /* WARNING: Subroutine does not return */
  exit(1);
}

// function main()

void main(void)

{
  n();
  return;
}