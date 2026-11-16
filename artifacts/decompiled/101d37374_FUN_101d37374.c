// FUN_101d37374 @ 101d37374 (368 bytes)
void FUN_101d37374(long param_1,long param_2)

{
  ulong *puVar1;
  ulong uVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  ulong uVar6;
  long *local_50;
  long local_48;
  
  local_48 = *(long *)PTR_10b4d40c8;
  if (param_2 != 0) {
    local_50 = &DAT_10cda23e8;
    lVar3 = param_1;
    FUN_10137e2d4(param_1,param_2,&local_50);
    if (((((int)lVar3 != 0) && (*(char *)((long)local_50 + 0xb) < '\0')) && (*local_50 != 0)) &&
       (plVar4 = *(long **)(param_1 + 0x28), plVar4 != (long *)0x0)) {
      (**(code **)(*plVar4 + 0x90))(plVar4,&local_50);
    }
    plVar4 = local_50;
    if (local_50 != &DAT_10cda23e8) {
      do {
        uVar5 = plVar4[1];
        uVar2 = uVar5 - 0x100000000;
        if ((uVar2 & 0x7fffffff01ffffff) == 0) {
          FUN_100394d68(&DAT_10cda2478);
          puVar1 = (ulong *)(plVar4 + 1);
          uVar6 = *puVar1;
          if (uVar6 == uVar5) {
            *puVar1 = uVar2;
            LOAcquire();
            uVar2 = *puVar1;
            *puVar1 = uVar2 | 0x8000000000000000;
            LORelease();
            FUN_10002e2dc(uVar2,&DAT_10cda2418,plVar4);
          }
          _os_unfair_recursive_lock_unlock(&DAT_10cda2478);
        }
        else {
          uVar6 = plVar4[1];
          if (uVar6 == uVar5) {
            plVar4[1] = uVar2;
          }
        }
      } while (uVar6 != uVar5);
    }
  }
  if (*(long *)PTR_10b4d40c8 == local_48) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

 (GhidraScript)
