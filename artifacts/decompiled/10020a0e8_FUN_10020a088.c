// FUN_10020a088 @ 10020a0e8 (864 bytes)
void FUN_10020a088(long param_1,long param_2)

{
  long *plVar1;
  uint uVar2;
  long lVar3;
  undefined8 *puVar4;
  long *plVar5;
  long *plVar6;
  uint uVar7;
  ulong uVar8;
  long lVar9;
  ulong uVar10;
  uint local_6c;
  long *local_68;
  undefined1 local_60;
  long local_58;
  
  local_58 = *(long *)PTR_10b4d40c8;
  *(long *)(param_2 + 0x38) = param_1;
  if (*(char *)(*(long *)(param_2 + 8) + 10) == '\0') {
    FUN_10046df90(param_2,"InventoryItemInstanceSaveData",0,0x78b29320,param_1);
  }
  FUN_10020b7b8(param_2,DAT_10cd63e20._4_4_,param_1,DAT_10d5d77a8);
  FUN_10020a3e8(param_2,param_1 + 0x28,DAT_10d5d77b0);
  FUN_10020a3e8(param_2,param_1 + 0x2c,DAT_10d5d77b8);
  FUN_10079bea0(param_2,DAT_10cd607d0._4_4_,DAT_10cd60810,DAT_10cd60818,param_1 + 8,DAT_10d5d77c0);
  plVar1 = (long *)(param_1 + 0x30);
  local_60 = 1;
  local_6c = *(uint *)(param_1 + 0x38) & 0x3fff;
  lVar3 = param_2;
  local_68 = plVar1;
  FUN_10016bd8c(param_2,&local_68,&local_6c,DAT_10d5d77c8);
  if ((int)lVar3 != 0) {
    if (*(char *)(*(long *)(param_2 + 8) + 10) != '\0') {
      if (local_6c == 0) {
        puVar4 = &DAT_10ca87f10;
        (*DAT_10ca87f10)();
        *puVar4 = &DAT_ffffdead00000005;
        *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) & 0xffffc000;
      }
      else {
        if ((((*(long **)(param_2 + 0x88) != (long *)0x0) &&
             ((*(ushort *)(param_2 + 0xa2) >> 5 & 1) != 0)) && ((DAT_10c5c774a & 1) == 0)) &&
           (local_6c << 3 != 0)) {
          lVar9 = **(long **)(param_2 + 0x88);
          lVar3 = *(long *)(lVar9 + 0x18);
          uVar10 = lVar3 + (ulong)(local_6c << 3);
          if ((uVar10 <= *(ulong *)(lVar9 + 0x20)) &&
             (*(ulong *)(lVar9 + 0x18) = uVar10, lVar3 != 0)) {
            FUN_100015028(plVar1,lVar3,0,local_6c,8,8,1,1,0x101);
          }
        }
        uVar2 = local_6c;
        uVar10 = (ulong)*(uint *)(param_1 + 0x38) & 0x3fff;
        uVar7 = *(uint *)(param_1 + 0x38) >> 0x10 & 0x3fff;
        if (uVar7 < local_6c) {
          plVar5 = plVar1;
          FUN_100021bbc(plVar1,local_6c << 3);
          plVar6 = DAT_10cd9f2b8;
          if (plVar5 != (long *)0x0) {
            plVar6 = plVar5;
          }
          uVar7 = *(ushort *)(param_1 + 0x3a) & 0x3fff;
        }
        else {
          plVar6 = (long *)0x0;
        }
        if (uVar7 < uVar2) {
          FUN_100014a60(plVar1,uVar2,8,8,0,0,plVar6,0);
          puVar4 = &DAT_10ca87f10;
          (*DAT_10ca87f10)();
          *puVar4 = &DAT_ffffdead00000005;
          if (0x3fff < uVar2) {
            FUN_100002000(&DAT_10cd6d5e1,0x100,
                          "Too many elements for %sArray. Size: %u, Max Size: %u");
            *(undefined4 *)*puVar4 = 0;
          }
        }
        else {
          puVar4 = &DAT_10ca87f10;
          (*DAT_10ca87f10)();
          *puVar4 = &DAT_ffffdead00000005;
        }
        *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) & 0xffffc000 | uVar2 & 0x3fff;
        if (((uint)uVar10 < uVar2) &&
           (uVar8 = (ulong)((uVar2 & 0x3fff) << 3), uVar10 * 8 - uVar8 != 0)) {
          _bzero((void *)(*plVar1 + uVar10 * 8),uVar8 + uVar10 * -8);
        }
      }
    }
    lVar3 = ((ulong)*(uint *)(param_1 + 0x38) & 0x3fff) << 3;
    if ((int)lVar3 != 0) {
      lVar9 = *(long *)(param_1 + 0x30);
      do {
        FUN_10075dcc8(param_2,lVar9,DAT_10d5d77c8);
        lVar9 = lVar9 + 8;
        lVar3 = lVar3 + -8;
      } while (lVar3 != 0);
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
INFO 0x107efab04 disassemble=true body=492 instructions=123
DIAG completed=true cancelled=false hf=true
