// FUN_1033aab40 @ 1033aab94 (252 bytes)
void FUN_1033aab40(long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)PTR_10b4d40c8;
  *(long *)(param_2 + 0x38) = param_1;
  if (*(char *)(*(long *)(param_2 + 8) + 10) == '\0') {
    FUN_10046df90(param_2,"ItemDataSaveData",0,0x92fe047c,param_1);
  }
  FUN_10079bea0(param_2,DAT_10cd62ea0._4_4_,DAT_10cd62ee0,DAT_10cd62ee8,param_1 + 8,DAT_10d5d6c88);
  FUN_10079bea0(param_2,DAT_10d5d6a60._4_4_,DAT_10d5d6aa0,DAT_10d5d6aa8,param_1 + 0x48,DAT_10d5d6c90
               );
  FUN_10020a3e8(param_2,param_1,DAT_10d5d6c98);
  FUN_100169a2c(param_2);
  *(ushort *)(param_2 + 0xa2) = *(ushort *)(param_2 + 0xa2) & 0xefff;
  if (*(long *)PTR_10b4d40c8 == lVar1) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

 (GhidraScript)  
INFO 0x10020a0e8 disassemble=true body=864 instructions=216
DIAG completed=true cancelled=false hf=true
