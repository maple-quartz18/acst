// FUN_1010eb6b4 @ 1010eb714 (848 bytes)
void FUN_1010eb6b4(long param_1,long param_2)

{
  long *plVar1;
  char cVar2;
  uint uVar3;
  long lVar4;
  undefined8 *puVar5;
  long *plVar6;
  long *plVar7;
  uint uVar8;
  ulong uVar9;
  long lVar10;
  undefined4 uVar11;
  ulong uVar12;
  uint local_6c;
  long *local_68;
  undefined1 local_60;
  long local_58;
  
  local_58 = *(long *)PTR_10b4d40c8;
  *(long *)(param_2 + 0x38) = param_1;
  if (*(char *)(*(long *)(param_2 + 8) + 10) == '\0') {
    FUN_10046df90(param_2,"ItemSlotsAttributesSaveData",0,0x399655bb,param_1);
    cVar2 = *(char *)(*(long *)(param_2 + 8) + 10);
    uVar11 = *(undefined4 *)(param_2 + 0x40);
    *(undefined4 *)(param_2 + 0x40) = 0;
    *(long *)(param_2 + 0x38) = param_1;
    if (cVar2 == '\0') {
      FUN_10046df90(param_2,"InventoryItemAttributesSaveData",0,0xea377936,param_1);
    }
  }
  else {
    uVar11 = *(undefined4 *)(param_2 + 0x40);
    *(undefined4 *)(param_2 + 0x40) = 0;
    *(long *)(param_2 + 0x38) = param_1;
  }
  FUN_100169a2c(param_2);
  *(ushort *)(param_2 + 0xa2) = *(ushort *)(param_2 + 0xa2) & 0xefff;
  *(undefined4 *)(param_2 + 0x40) = uVar11;
  plVar1 = (long *)(param_1 + 8);
  local_60 = 1;
  local_6c = *(uint *)(param_1 + 0x10) & 0x3fff;
  lVar4 = param_2;
  local_68 = plVar1;
  FUN_10016bd8c(param_2,&local_68,&local_6c,DAT_10d63c990);
  if ((int)lVar4 != 0) {
    if (*(char *)(*(long *)(param_2 + 8) + 10) != '\0') {
      if (local_6c == 0) {
        FUN_10017a8fc(plVar1,0,8,8,0,0);
      }
      else {
        if ((((*(long **)(param_2 + 0x88) != (long *)0x0) &&
             ((*(ushort *)(param_2 + 0xa2) >> 5 & 1) != 0)) && ((DAT_10c699732 & 1) == 0)) &&
           (local_6c << 3 != 0)) {
          lVar10 = **(long **)(param_2 + 0x88);
          lVar4 = *(long *)(lVar10 + 0x18);
          uVar12 = lVar4 + (ulong)(local_6c << 3);
          if ((uVar12 <= *(ulong *)(lVar10 + 0x20)) &&
             (*(ulong *)(lVar10 + 0x18) = uVar12, lVar4 != 0)) {
            FUN_100015028(plVar1,lVar4,0,local_6c,8,8,1,1,0x101);
          }
        }
        uVar3 = local_6c;
        uVar12 = (ulong)*(uint *)(param_1 + 0x10) & 0x3fff;
        uVar8 = *(uint *)(param_1 + 0x10) >> 0x10 & 0x3fff;
        if (uVar8 < local_6c) {
          plVar6 = plVar1;
          FUN_100021bbc(plVar1,local_6c << 3);
          plVar7 = DAT_10cd9f2b8;
          if (plVar6 != (long *)0x0) {
            plVar7 = plVar6;
          }
          uVar8 = *(ushort *)(param_1 + 0x12) & 0x3fff;
        }
        else {
          plVar7 = (long *)0x0;
        }
        if (uVar8 < uVar3) {
          FUN_100014a60(plVar1,uVar3,8,8,0,0,plVar7,0);
          puVar5 = &DAT_10ca87f10;
          (*DAT_10ca87f10)();
          *puVar5 = &DAT_ffffdead00000005;
          if (0x3fff < uVar3) {
            FUN_100002000(&DAT_10cd6d5e1,0x100,
                          "Too many elements for %sArray. Size: %u, Max Size: %u");
            *(undefined4 *)*puVar5 = 0;
          }
        }
        else {
          puVar5 = &DAT_10ca87f10;
          (*DAT_10ca87f10)();
          *puVar5 = &DAT_ffffdead00000005;
        }
        *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) & 0xffffc000 | uVar3 & 0x3fff;
        if (((uint)uVar12 < uVar3) &&
           (uVar9 = (ulong)((uVar3 & 0x3fff) << 3), uVar12 * 8 - uVar9 != 0)) {
          _bzero((void *)(*plVar1 + uVar12 * 8),uVar9 + uVar12 * -8);
        }
      }
    }
    lVar4 = ((ulong)*(uint *)(param_1 + 0x10) & 0x3fff) << 3;
    if ((int)lVar4 != 0) {
      lVar10 = *(long *)(param_1 + 8);
      do {
        FUN_10075dcc8(param_2,lVar10,DAT_10d63c990);
        lVar10 = lVar10 + 8;
        lVar4 = lVar4 + -8;
      } while (lVar4 != 0);
    }
    FUN_10016a69c(param_2);
  }
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
INFO 0x1010eb654 disassemble=true body=184 instructions=46
DIAG completed=true cancelled=false hf=true
