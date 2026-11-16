// FUN_107efef14 @ 107efef14 (156 bytes)
void FUN_107efef14(long param_1,long param_2)

{
  long lVar1;
  undefined4 *puVar2;
  
  lVar1 = *(long *)PTR_10b4d40c8;
  puVar2 = *(undefined4 **)(param_2 + 0x20);
  if (*(ulong *)(param_2 + 0x28) < (long)puVar2 + 0xdU) {
    FUN_100161ad4(param_2);
    puVar2 = *(undefined4 **)(param_2 + 0x20);
  }
  *(undefined4 *)(param_1 + 8) = *puVar2;
  *(long *)(param_2 + 0x20) = *(long *)(param_2 + 0x20) + 4;
  if (*(long *)PTR_10b4d40c8 == lVar1) {
    FUN_10010fbac(param_2,&DAT_10cd62a98,param_1);
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

 (GhidraScript)
