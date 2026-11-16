// FUN_107efaaac @ 107efab04 (492 bytes)
void FUN_107efaaac(long param_1,long param_2)

{
  ulong uVar1;
  long lVar2;
  undefined4 uVar3;
  long lVar4;
  long lVar5;
  uint uVar6;
  uint local_4c;
  long local_48;
  undefined1 local_40;
  long local_38;
  
  local_38 = *(long *)PTR_10b4d40c8;
  *(long *)(param_2 + 0x38) = param_1;
  if (*(char *)(*(long *)(param_2 + 8) + 10) == '\0') {
    FUN_10046df90(param_2,"ItemReferenceAttributesSaveData",0,0x2390a2e7,param_1);
  }
  uVar3 = *(undefined4 *)(param_2 + 0x40);
  *(undefined4 *)(param_2 + 0x40) = 0;
  FUN_1033ac834(param_1,param_2);
  *(undefined4 *)(param_2 + 0x40) = uVar3;
  lVar2 = param_1 + 8;
  local_40 = 1;
  local_4c = *(uint *)(param_1 + 0x10) & 0x3fff;
  lVar4 = param_2;
  local_48 = lVar2;
  FUN_10016bd8c(param_2,&local_48,&local_4c,DAT_10d5d7be8);
  if ((int)lVar4 == 0) goto LAB_107efac4c;
  if (*(char *)(*(long *)(param_2 + 8) + 10) != '\0') {
    if (local_4c == 0) {
LAB_107efac08:
      lVar4 = 0;
      uVar6 = local_4c;
    }
    else {
      if ((((*(long **)(param_2 + 0x88) != (long *)0x0) &&
           ((*(ushort *)(param_2 + 0xa2) >> 5 & 1) != 0)) && ((DAT_10c5c8332 & 1) == 0)) &&
         (local_4c << 2 != 0)) {
        lVar5 = **(long **)(param_2 + 0x88);
        lVar4 = *(long *)(lVar5 + 0x28);
        uVar1 = lVar4 + (ulong)(local_4c << 2);
        if ((uVar1 <= *(ulong *)(lVar5 + 0x30)) && (*(ulong *)(lVar5 + 0x28) = uVar1, lVar4 != 0)) {
          FUN_100015028(lVar2,lVar4,0,local_4c,4,4,1,1,0x101);
        }
      }
      uVar6 = local_4c;
      if (local_4c <= (*(ushort *)(param_1 + 0x12) & 0x3fff)) goto LAB_107efac08;
      lVar5 = lVar2;
      FUN_100021bbc(lVar2,local_4c << 2);
      lVar4 = DAT_10cd9f2b8;
      if (lVar5 != 0) {
        lVar4 = lVar5;
      }
    }
    FUN_10017a8fc(lVar2,uVar6,4,4,0,lVar4);
  }
  FUN_102464f20(param_2,*(undefined8 *)(param_1 + 8),4,1,*(uint *)(param_1 + 0x10) & 0x3fff,7);
  FUN_10016a69c(param_2);
LAB_107efac4c:
  *(undefined2 *)(param_2 + 0xa8) = 0;
  *(undefined1 *)(param_2 + 0xaa) = 0;
  FUN_100169a2c(param_2);
  *(ushort *)(param_2 + 0xa2) = *(ushort *)(param_2 + 0xa2) & 0xefff;
  if (*(long *)PTR_10b4d40c8 != local_38) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail();
  }
  return;
}

 (GhidraScript)  
INFO 0x1010eb714 disassemble=true body=848 instructions=212
DIAG completed=true cancelled=false hf=true
