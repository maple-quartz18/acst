// FUN_101de72d8 @ 101de72d8 (344 bytes)
void FUN_101de72d8(long param_1,long param_2)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = *(long *)PTR_10b4d40c8;
  *(long *)(param_2 + 0x38) = param_1;
  if (*(char *)(*(long *)(param_2 + 8) + 10) == '\0') {
    FUN_10046df90(param_2,"HubRedSaveMetaData",0,0x40794930,param_1);
  }
  uVar1 = *(undefined4 *)(param_2 + 0x40);
  *(undefined4 *)(param_2 + 0x40) = 0;
  FUN_101de7430(param_1,param_2);
  *(undefined4 *)(param_2 + 0x40) = uVar1;
  FUN_10079bea0(param_2,DAT_10cb2ef08._4_4_,DAT_10cb2ef48,DAT_10cb2ef50,param_1 + 0x60,DAT_10d46f0d0
               );
  FUN_10079bea0(param_2,DAT_10cceb6a0._4_4_,DAT_10cceb6e0,DAT_10cceb6e8,param_1 + 0x10,DAT_10d46f0d8
               );
  FUN_10079bea0(param_2,DAT_10cceb7a0._4_4_,DAT_10cceb7e0,DAT_10cceb7e8,param_1 + 0x18,DAT_10d46f0e0
               );
  FUN_10020a3e8(param_2,param_1 + 0x78,DAT_10d46f0e8);
  FUN_10020a3e8(param_2,param_1 + 0x7c,DAT_10d46f0f0);
  FUN_100169a2c(param_2);
  *(ushort *)(param_2 + 0xa2) = *(ushort *)(param_2 + 0xa2) & 0xefff;
  if (*(long *)PTR_10b4d40c8 == lVar2) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

 (GhidraScript)
