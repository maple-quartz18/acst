// _NativeQueryInventory @ 103fab070 (348 bytes)
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

void _NativeQueryInventory(undefined8 *param_1,uint param_2,code *param_3)

{
  undefined *self;
  ID self_00;
  ID IVar1;
  ulong uVar2;
  char *local_c0;
  char *pcStack_b8;
  char *local_b0;
  char *pcStack_a8;
  char *local_a0;
  char *pcStack_98;
  undefined4 local_90;
  char *local_88;
  char *pcStack_80;
  char *local_78;
  undefined8 local_70;
  undefined8 uStack_68;
  long local_60;
  long local_58;
  undefined8 local_50;
  long local_48;
  
  local_48 = *(long *)PTR_10b4d40c8;
  self = (undefined *)0x0;
  _objc_alloc();
  self_00 = objc_stub::thunk_FUN_10a7f3bc0((ID)self,(long)(int)param_2);
  if (0 < (int)param_2) {
    uVar2 = (ulong)param_2;
    do {
      if (((char *)*param_1 != (char *)0x0) && (*(char *)*param_1 != '\0')) {
        IVar1 = objc_stub::thunk_FUN_10a7f2680((ID)(undefined *)0x0);
        objc_stub::thunk_FUN_10a7f2ca0(self_00,IVar1);
      }
      param_1 = param_1 + 1;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  if (_iapController != 0) {
    IVar1 = objc_stub::thunk_FUN_10a7f2a80(self_00);
    if (IVar1 == 0) {
      local_c0 = "";
      pcStack_b8 = "";
      local_b0 = "";
      pcStack_a8 = "";
      local_a0 = "";
      pcStack_98 = "";
      local_90 = 0;
      local_88 = "";
      pcStack_80 = "";
      local_78 = "";
      uStack_68 = 0;
      local_70 = 0;
      local_58 = 0;
      local_60 = 0;
      local_50 = 0;
      (*param_3)(&local_c0,1,0xfffffc19,"The productIds are NULL or invalid.");
      if (local_60 != 0) {
        local_58 = local_60;
        __ZdlPv();
      }
    }
    else {
      objc_stub::thunk_FUN_10a7f3ce0(_iapController,self_00,param_3);
    }
  }
  if (*(long *)PTR_10b4d40c8 == local_48) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}

 (GhidraScript)  
INFO 0x103fa89ac disassemble=true body=172 instructions=43
DIAG completed=true cancelled=false hf=true
