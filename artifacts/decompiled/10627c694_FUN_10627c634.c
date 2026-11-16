// FUN_10627c634 @ 10627c694 (1028 bytes)
void FUN_10627c634(long param_1,long param_2)

{
  long *plVar1;
  ulong *puVar2;
  uint uVar3;
  long *plVar4;
  ulong uVar5;
  long *plVar6;
  undefined8 *puVar7;
  ulong uVar8;
  uint uVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  undefined8 *puVar13;
  uint uVar14;
  ulong uVar15;
  ulong uVar16;
  uint local_6c;
  long *local_68;
  undefined1 local_60;
  long local_58;
  
  local_58 = *(long *)PTR_10b4d40c8;
  *(long *)(param_2 + 0x38) = param_1;
  if (*(char *)(*(long *)(param_2 + 8) + 10) == '\0') {
    FUN_10046df90(param_2,"MultiLoadoutSaveData",0,0x47bdefc0,param_1);
  }
  FUN_10020a3e8(param_2,param_1 + 8,DAT_10d4845c0);
  FUN_100ba9774(param_2,DAT_10cd65088._4_4_,DAT_10cd650c8,DAT_10cd650d0,param_1,DAT_10d4845c8);
  plVar1 = (long *)(param_1 + 0xc);
  local_60 = 1;
  local_6c = *(uint *)(param_1 + 0x14) & 0x3fff;
  lVar12 = param_2;
  local_68 = plVar1;
  FUN_10016bd8c(param_2,&local_68,&local_6c,DAT_10d4845d0);
  if ((int)lVar12 == 0) goto LAB_10627c8f8;
  if (*(char *)(*(long *)(param_2 + 8) + 10) != '\0') {
    uVar15 = (ulong)local_6c;
    if (local_6c == 0) {
      uVar9 = *(uint *)(param_1 + 0x14);
    }
    else {
      if ((((*(long **)(param_2 + 0x88) != (long *)0x0) &&
           ((*(ushort *)(param_2 + 0xa2) >> 5 & 1) != 0)) && ((DAT_10c4ab962 & 1) == 0)) &&
         (local_6c << 3 != 0)) {
        lVar10 = **(long **)(param_2 + 0x88);
        lVar12 = *(long *)(lVar10 + 0x18);
        uVar11 = lVar12 + (ulong)(local_6c << 3);
        if ((uVar11 <= *(ulong *)(lVar10 + 0x20)) &&
           (*(ulong *)(lVar10 + 0x18) = uVar11, lVar12 != 0)) {
          FUN_100015028(plVar1,lVar12,0,uVar15,8,8,1,1,0x101);
          uVar15 = (ulong)local_6c;
        }
      }
      uVar9 = *(uint *)(param_1 + 0x14);
      uVar14 = (uint)uVar15;
      if ((uVar9 >> 0x10 & 0x3fff) < uVar14) {
        plVar6 = plVar1;
        FUN_100021bbc(plVar1,uVar14 << 3);
        plVar4 = DAT_10cd9f2b8;
        if (plVar6 != (long *)0x0) {
          plVar4 = plVar6;
        }
        FUN_100014a60(plVar1,uVar15,8,8,0,0,plVar4,0);
        uVar9 = *(uint *)(param_1 + 0x14);
      }
      uVar3 = uVar9 & 0x3fff;
      if (uVar3 < uVar14) {
        puVar7 = &DAT_10ca87f10;
        (*DAT_10ca87f10)();
        *puVar7 = &DAT_ffffdead00000005;
        if (0x3fff < uVar14) {
          FUN_100002000(&DAT_10cd6d5e1,0x100,"Too many elements for %sArray. Size: %u, Max Size: %u"
                       );
          *(undefined4 *)*puVar7 = 0;
        }
        *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) & 0xffffc000 | uVar14 & 0x3fff;
        uVar15 = (ulong)((uVar14 & 0x3fff) << 3);
        if ((ulong)uVar3 << 3 != uVar15) {
          _memset_pattern16((void *)(*(long *)(param_1 + 0xc) + (ulong)uVar3 * 8),&PTR_DAT_10be8a9f0
                            ,uVar15 + (ulong)uVar3 * -8);
        }
        goto LAB_10627c8bc;
      }
    }
    uVar11 = (ulong)((uVar9 & 0x3fff) << 3);
    if (uVar15 << 3 != uVar11) {
      lVar12 = *plVar1;
      puVar7 = (undefined8 *)(lVar12 + uVar15 * 8);
      do {
        puVar13 = (undefined8 *)*puVar7;
        if (puVar13 != &DAT_10cda23e8) {
          do {
            uVar16 = puVar13[1];
            uVar5 = uVar16 - 0x100000000;
            if ((uVar5 & 0x7fffffff01ffffff) == 0) {
              uVar8 = 0;
              _os_unfair_recursive_lock_trylock();
              if ((uVar8 & 1) == 0) {
                _os_unfair_recursive_lock_lock_with_options(&DAT_10cda2478,0x40000);
              }
              puVar2 = puVar13 + 1;
              uVar8 = *puVar2;
              if (uVar8 == uVar16) {
                *puVar2 = uVar5;
                LOAcquire();
                uVar5 = *puVar2;
                *puVar2 = uVar5 | 0x8000000000000000;
                LORelease();
                FUN_10002e2dc(uVar5,&DAT_10cda2418,puVar13);
              }
              _os_unfair_recursive_lock_unlock(&DAT_10cda2478);
            }
            else {
              uVar8 = puVar13[1];
              if (uVar8 == uVar16) {
                puVar13[1] = uVar5;
              }
            }
          } while (uVar8 != uVar16);
        }
        puVar13 = puVar7 + 1;
        *puVar7 = 0;
        puVar7 = puVar13;
      } while (puVar13 != (undefined8 *)(lVar12 + uVar11));
    }
    puVar7 = &DAT_10ca87f10;
    (*DAT_10ca87f10)();
    *puVar7 = &DAT_ffffdead00000005;
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) & 0xffffc000 | (uint)uVar15 & 0x3fff;
  }
LAB_10627c8bc:
  lVar12 = ((ulong)*(uint *)(param_1 + 0x14) & 0x3fff) << 3;
  if ((int)lVar12 != 0) {
    lVar10 = *(long *)(param_1 + 0xc);
    do {
      FUN_10020b7b8(param_2,DAT_10cd62ab0._4_4_,lVar10,DAT_10d4845d0);
      lVar10 = lVar10 + 8;
      lVar12 = lVar12 + -8;
    } while (lVar12 != 0);
  }
  FUN_10016a69c(param_2);
LAB_10627c8f8:
  *(undefined2 *)(param_2 + 0xa8) = 0;
  *(undefined1 *)(param_2 + 0xaa) = 0;
  FUN_100169a2c(param_2);
  *(ushort *)(param_2 + 0xa2) = *(ushort *)(param_2 + 0xa2) & 0xefff;
  if (*(long *)PTR_10b4d40c8 == local_58) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

 (GhidraScript)  
real 4.30
user 5.14
sys 1.83
