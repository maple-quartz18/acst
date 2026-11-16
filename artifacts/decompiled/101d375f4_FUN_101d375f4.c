// FUN_101d375f4 @ 101d375f4 (240 bytes)
undefined8 *
FUN_101d375f4(undefined8 *param_1,undefined8 param_2,undefined1 param_3,undefined1 param_4)

{
  long lVar1;
  
  lVar1 = *(long *)PTR_10b4d40c8;
  *param_1 = 0;
  FUN_10043a8e0(param_1,"Rarity");
  param_1[1] = 0;
  FUN_10043a8e0(param_1 + 1,"Id");
  param_1[2] = 0;
  FUN_10043a8e0(param_1 + 2,"Stats");
  param_1[3] = 0;
  FUN_10043a8e0(param_1 + 3,"Level");
  param_1[4] = 0;
  FUN_10043a8e0(param_1 + 4,"VisualId");
  *(undefined2 *)(param_1 + 5) = 0x101;
  *(undefined1 *)((long)param_1 + 0x2a) = 1;
  *(undefined1 *)((long)param_1 + 0x2b) = param_3;
  *(undefined1 *)((long)param_1 + 0x2c) = param_4;
  param_1[6] = 0;
  FUN_10043a8e0(param_1 + 6,param_2);
  if (*(long *)PTR_10b4d40c8 == lVar1) {
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

 (GhidraScript)  
real 6.15
user 4.77
sys 2.09
