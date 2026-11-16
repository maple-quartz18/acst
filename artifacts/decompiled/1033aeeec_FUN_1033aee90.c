// FUN_1033aee90 @ 1033aeeec (760 bytes)
void FUN_1033aee90(long *param_1,long param_2)

{
  uint uVar1;
  long lVar2;
  undefined8 *puVar3;
  long *plVar4;
  long *plVar5;
  uint uVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  uint local_5c;
  long *local_58;
  undefined1 local_50;
  long local_48;
  
  local_48 = *(long *)PTR_10b4d40c8;
  *(long **)(param_2 + 0x38) = param_1;
  if (*(char *)(*(long *)(param_2 + 8) + 10) == '\0') {
    FUN_10046df90(param_2,"LoadoutSaveData",0,0x52e22622,param_1);
  }
  local_50 = 1;
  local_5c = *(uint *)(param_1 + 1) & 0x3fff;
  lVar2 = param_2;
  local_58 = param_1;
  FUN_10016bd8c(param_2,&local_58,&local_5c,DAT_10d5d7fc8);
  if ((int)lVar2 != 0) {
    if (*(char *)(*(long *)(param_2 + 8) + 10) != '\0') {
      if (local_5c == 0) {
        FUN_10017a8fc(param_1,0,8,8,0,0);
      }
      else {
        if ((((*(long **)(param_2 + 0x88) != (long *)0x0) &&
             ((*(ushort *)(param_2 + 0xa2) >> 5 & 1) != 0)) && ((DAT_10c5c8962 & 1) == 0)) &&
           (local_5c << 3 != 0)) {
          lVar8 = **(long **)(param_2 + 0x88);
          lVar2 = *(long *)(lVar8 + 0x18);
          uVar9 = lVar2 + (ulong)(local_5c << 3);
          if ((uVar9 <= *(ulong *)(lVar8 + 0x20)) && (*(ulong *)(lVar8 + 0x18) = uVar9, lVar2 != 0))
          {
            FUN_100015028(param_1,lVar2,0,local_5c,8,8,1,1,0x101);
          }
        }
        uVar1 = local_5c;
        uVar9 = (ulong)*(uint *)(param_1 + 1) & 0x3fff;
        uVar6 = *(uint *)(param_1 + 1) >> 0x10 & 0x3fff;
        if (uVar6 < local_5c) {
          plVar4 = param_1;
          FUN_100021bbc(param_1,local_5c << 3);
          plVar5 = DAT_10cd9f2b8;
          if (plVar4 != (long *)0x0) {
            plVar5 = plVar4;
          }
          uVar6 = *(ushort *)((long)param_1 + 10) & 0x3fff;
        }
        else {
          plVar5 = (long *)0x0;
        }
        if (uVar6 < uVar1) {
          FUN_100014a60(param_1,uVar1,8,8,0,0,plVar5,0);
          puVar3 = &DAT_10ca87f10;
          (*DAT_10ca87f10)();
          *puVar3 = &DAT_ffffdead00000005;
          if (0x3fff < uVar1) {
            FUN_100002000(&DAT_10cd6d5e1,0x100,
                          "Too many elements for %sArray. Size: %u, Max Size: %u");
            *(undefined4 *)*puVar3 = 0;
          }
        }
        else {
          puVar3 = &DAT_10ca87f10;
          (*DAT_10ca87f10)();
          *puVar3 = &DAT_ffffdead00000005;
        }
        *(uint *)(param_1 + 1) = *(uint *)(param_1 + 1) & 0xffffc000 | uVar1 & 0x3fff;
        if (((uint)uVar9 < uVar1) &&
           (uVar7 = (ulong)((uVar1 & 0x3fff) << 3), uVar9 * 8 - uVar7 != 0)) {
          _bzero((void *)(*param_1 + uVar9 * 8),uVar7 + uVar9 * -8);
        }
      }
    }
    lVar2 = ((ulong)*(uint *)(param_1 + 1) & 0x3fff) << 3;
    if ((int)lVar2 != 0) {
      lVar8 = *param_1;
      do {
        FUN_100ba9774(param_2,DAT_10d5d7ee8._4_4_,DAT_10d5d7f28,DAT_10d5d7f30,lVar8,DAT_10d5d7fc8);
        lVar8 = lVar8 + 8;
        lVar2 = lVar2 + -8;
      } while (lVar2 != 0);
    }
    FUN_10016a69c(param_2);
  }
  *(undefined2 *)(param_2 + 0xa8) = 0;
  *(undefined1 *)(param_2 + 0xaa) = 0;
  FUN_100169a2c(param_2);
  *(ushort *)(param_2 + 0xa2) = *(ushort *)(param_2 + 0xa2) & 0xefff;
  if (*(long *)PTR_10b4d40c8 == local_48) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

 (GhidraScript)  
INFO 0x1033aebf8 disassemble=true body=200 instructions=50
DIAG completed=true cancelled=false hf=true
