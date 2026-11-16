// FUN_1033aeba4 @ 1033aebf8 (200 bytes)
void FUN_1033aeba4(long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)PTR_10b4d40c8;
  *(long *)(param_2 + 0x38) = param_1;
  if (*(char *)(*(long *)(param_2 + 8) + 10) == '\0') {
    FUN_10046df90(param_2,"LoadoutItemSaveData",0,0x52ee6a12,param_1);
  }
  FUN_10020a3e8(param_2,param_1 + 8,DAT_10d5d7ec0);
  FUN_10020b7b8(param_2,DAT_10cd62ab0._4_4_,param_1,DAT_10d5d7ec8);
  FUN_100169a2c(param_2);
  *(ushort *)(param_2 + 0xa2) = *(ushort *)(param_2 + 0xa2) & 0xefff;
  if (*(long *)PTR_10b4d40c8 == lVar1) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

 (GhidraScript)  
INFO 0x1033aab94 disassemble=true body=252 instructions=63
DIAG completed=true cancelled=false hf=true
