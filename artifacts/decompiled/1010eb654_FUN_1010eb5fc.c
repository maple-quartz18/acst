// FUN_1010eb5fc @ 1010eb654 (184 bytes)
void FUN_1010eb5fc(undefined8 param_1,long param_2)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = *(long *)PTR_10b4d40c8;
  *(undefined8 *)(param_2 + 0x38) = param_1;
  if (*(char *)(*(long *)(param_2 + 8) + 10) == '\0') {
    FUN_10046df90(param_2,"ItemPartsAttributesSaveData",0,0x5e8c21f9,param_1);
  }
  uVar1 = *(undefined4 *)(param_2 + 0x40);
  *(undefined4 *)(param_2 + 0x40) = 0;
  FUN_1010eb6b4(param_1,param_2);
  *(undefined4 *)(param_2 + 0x40) = uVar1;
  FUN_100169a2c(param_2);
  *(ushort *)(param_2 + 0xa2) = *(ushort *)(param_2 + 0xa2) & 0xefff;
  if (*(long *)PTR_10b4d40c8 == lVar2) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

 (GhidraScript)  
INFO 0x10627c694 disassemble=true body=1028 instructions=257
DIAG completed=true cancelled=false hf=true
