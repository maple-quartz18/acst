// FUN_1035afc48 @ 1035afc48 (516 bytes)
void FUN_1035afc48(long param_1,long param_2)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = *(long *)PTR_10b4d40c8;
  *(long *)(param_2 + 0x38) = param_1;
  if (*(char *)(*(long *)(param_2 + 8) + 10) == '\0') {
    FUN_10046df90(param_2,"AssassinSaveGameMetaData",0,0x43cc050b,param_1);
  }
  uVar1 = *(undefined4 *)(param_2 + 0x40);
  *(undefined4 *)(param_2 + 0x40) = 0;
  FUN_101de7430(param_1,param_2);
  *(undefined4 *)(param_2 + 0x40) = uVar1;
  FUN_10079bea0(param_2,DAT_10cceb6a0._4_4_,DAT_10cceb6e0,DAT_10cceb6e8,param_1 + 0x28,DAT_10d72d5a8
               );
  FUN_10079bea0(param_2,DAT_10cceb7a0._4_4_,DAT_10cceb7e0,DAT_10cceb7e8,param_1 + 0x30,DAT_10d72d5b0
               );
  FUN_10079bea0(param_2,DAT_10cceb6a0._4_4_,DAT_10cceb6e0,DAT_10cceb6e8,param_1 + 0x78,DAT_10d72d5b8
               );
  FUN_10079bea0(param_2,DAT_10cceb6a0._4_4_,DAT_10cceb6e0,DAT_10cceb6e8,param_1 + 0x80,DAT_10d72d5c0
               );
  FUN_10079bea0(param_2,DAT_10cceb6a0._4_4_,DAT_10cceb6e0,DAT_10cceb6e8,param_1 + 0x88,DAT_10d72d5c8
               );
  FUN_10020a3e8(param_2,param_1 + 0xac,DAT_10d72d5d0);
  FUN_10020a3e8(param_2,param_1 + 0xb0,DAT_10d72d5d8);
  FUN_10020b7b8(param_2,DAT_10d0c83b0._4_4_,param_1 + 0xa0,DAT_10d72d5e0);
  FUN_10018b974(param_2,0xedb19556,param_1 + 0xa8,DAT_10d72d5e8);
  FUN_10097a268(param_2,param_1 + 0x10,DAT_10d72d5f0);
  FUN_101473810(param_2,DAT_10d72d5f8,param_1 + 0x90);
  FUN_101473810(param_2,DAT_10d72d600,param_1 + 0x98);
  FUN_100169a2c(param_2);
  *(ushort *)(param_2 + 0xa2) = *(ushort *)(param_2 + 0xa2) & 0xefff;
  if (*(long *)PTR_10b4d40c8 == lVar2) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

 (GhidraScript)  
INFO 0x101de72d8 disassemble=true body=344 instructions=86
DIAG completed=true cancelled=false hf=true
