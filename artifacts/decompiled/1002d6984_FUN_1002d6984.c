// FUN_1002d6984 @ 1002d6984 (2764 bytes)
undefined8 *
FUN_1002d6984(undefined8 *param_1,long *param_2,byte param_3,int param_4,int param_5,ulong param_6,
             byte param_7,undefined4 param_8,char param_9,undefined4 param_10,long *param_11)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  code *pcVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int *piVar8;
  byte *pbVar9;
  undefined8 *puVar10;
  long *plVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined1 *puVar14;
  int extraout_w8;
  int iVar15;
  uint extraout_w8_00;
  uint uVar16;
  byte bVar17;
  undefined4 uVar18;
  undefined8 extraout_x9;
  uint uVar19;
  long lVar20;
  byte bVar21;
  byte bVar22;
  long *plVar23;
  long *plVar24;
  long *plVar25;
  ulong uVar26;
  ulong uVar27;
  ushort uStack_80;
  ushort uStack_7e;
  uint uStack_7c;
  uint uStack_78;
  ushort uStack_72;
  long lStack_70;
  long lStack_68;
  
  lStack_68 = *(long *)PTR_10b4d40c8;
  *(uint *)(param_1 + 1) = *(uint *)(param_1 + 1) & 0xfffffffe;
  *(undefined8 *)((long)param_1 + 0xc) = 0;
  *param_1 = &UNK_10b9d5c58;
  plVar24 = param_1 + 7;
  *plVar24 = (long)(param_1 + 9);
  param_1[8] = param_1[8] & 0x8000000000000000 | 0x880000000;
  pbVar9 = (byte *)(param_1 + 0x1a);
  *pbVar9 = param_7;
  *(undefined4 *)(param_1 + 0x13) = 0;
  param_1[0x17] = 0;
  param_1[0x16] = 0;
  plVar23 = param_1 + 0x14;
  param_1[0x15] = 0;
  *plVar23 = 0;
  param_1[0x12] = 0;
  bVar17 = 2;
  if (param_5 == 0) {
    bVar17 = 0;
  }
  *(undefined4 *)(param_1 + 0x19) = 0;
  *(undefined4 *)((long)param_1 + 0xcc) = param_8;
  bVar21 = 4;
  if (param_9 == '\0') {
    bVar21 = 0;
  }
  param_1[0x18] = 0;
  bVar22 = 8;
  if (param_4 == 0) {
    bVar22 = 0;
  }
  param_1[5] = 0;
  param_1[6] = param_2;
  param_1[3] = 0;
  param_1[4] = 0;
  *(undefined4 *)(param_1 + 0x11) = 0xffffffff;
  *(byte *)((long)param_1 + 0xd1) =
       bVar22 | param_3 ^ 1 | bVar17 | *(byte *)((long)param_1 + 0xd1) & 0xe0 | bVar21;
  piVar8 = (int *)0x10ca88108;
  if ((param_3 & 1) == 0) {
    if (*(code **)(*param_2 + 0x60) == (code *)&LAB_10801c154) {
      func_0x00010005efd8(uRam000000010c51de20,&lStack_70,8);
      *(int *)((long)param_2 + 0xac) = *(int *)((long)param_2 + 0xac) + 8;
      iVar5 = 1;
    }
    else {
      plVar25 = param_2;
      (**(code **)(*param_2 + 0x60))(param_2,&lStack_70);
      iVar5 = (int)plVar25;
    }
    if ((iVar5 == 0) || (lStack_70 != 0x1004fa9957fbaa33)) goto LAB_1002d727c;
    if (*(code **)(*param_2 + 0x50) == (code *)&LAB_10801c074) {
      func_0x00010005efd8(uRam000000010c51de20,&uStack_72,2);
      *(int *)((long)param_2 + 0xac) = *(int *)((long)param_2 + 0xac) + 2;
      iVar5 = 1;
    }
    else {
      plVar25 = param_2;
      (**(code **)(*param_2 + 0x50))(param_2,&uStack_72);
      iVar5 = (int)plVar25;
    }
    if ((iVar5 == 0) || (3 < uStack_72)) goto LAB_1002d727c;
    if (*(code **)(*param_2 + 0x48) == (code *)&LAB_10801c004) {
      func_0x00010005efd8(uRam000000010c51de20,pbVar9,1);
      *(int *)((long)param_2 + 0xac) = *(int *)((long)param_2 + 0xac) + 1;
    }
    else {
      plVar25 = param_2;
      (**(code **)(*param_2 + 0x48))(param_2,pbVar9);
      if ((int)plVar25 == 0) goto LAB_1002d727c;
    }
    if ((0xc < (ulong)*pbVar9) || (*(long *)((ulong)*pbVar9 * 0x20 + 0x10ce34ef8) == 0))
    goto LAB_1002d727c;
    uStack_78 = 0;
    if (*(code **)(*param_2 + 0x58) == (code *)&LAB_10801c0e4) {
      func_0x00010005efd8(uRam000000010c51de20,&uStack_78,4);
      *(int *)((long)param_2 + 0xac) = *(int *)((long)param_2 + 0xac) + 4;
    }
    else {
      (**(code **)(*param_2 + 0x58))(param_2,&uStack_78);
      if ((int)param_2 == 0) goto LAB_1002d727c;
    }
    if ((int)uStack_78 < 0) {
      uStack_78 = uStack_78 & 0x7fffffff;
      bVar17 = *(byte *)((long)param_1 + 0xd1) | 8;
    }
    else {
      bVar17 = *(byte *)((long)param_1 + 0xd1) & 0xf7;
    }
    *(byte *)((long)param_1 + 0xd1) = bVar17;
    *(uint *)(param_1 + 0x19) = uStack_78;
    *(uint *)(param_1 + 0x13) = uStack_78;
    param_1[0x16] = 0;
    *(uint *)(param_1 + 0x15) = uStack_78;
    piVar7 = piVar8;
    (*pcRam000000010ca88108)();
    if (*piVar7 == 5) {
      plVar11 = (long *)0x10cda4ef0;
    }
    else {
      uVar6 = *(uint *)((ulong)*pbVar9 * 0x20 + 0x10ce34f00);
      if (uVar6 != 0) {
        plVar25 = param_11;
        if (*(char *)((long)param_11 + 0x2a) == '\0') {
          puVar10 = (undefined8 *)0x10ca87f40;
          (*pcRam000000010ca87f40)();
          plVar25 = (long *)*puVar10;
          if ((long *)*puVar10 == (long *)0x0) {
            if (plRam000000010cd9f2b8 == param_11) {
              if (uVar6 - 0x91 < 0xffffff70) {
                if (uVar6 - 0x1c1 < 0xfffffed0) {
                  if (uVar6 - 0x301 < 0xfffffec0) goto LAB_1002d71c0;
                  uVar16 = 0x1c1;
                  iVar5 = 0x49;
                  lVar20 = 2;
                }
                else {
                  uVar16 = 0x91;
                  iVar5 = 0x23;
                  lVar20 = 1;
                }
              }
              else {
                lVar20 = 0;
                iVar5 = 0;
                uVar16 = 1;
              }
              uVar2 = *(uint *)(&UNK_10afa77d8 + lVar20 * 0xc);
              uVar19 = (uVar6 + uVar2) - 1 & -uVar2;
              if (uVar19 < 9) {
                uVar19 = 8;
              }
              if (uVar16 < 9) {
                uVar16 = 8;
              }
              uVar3 = 0;
              if (uVar2 != 0) {
                uVar3 = (uVar19 - uVar16) / uVar2;
              }
              plVar25 = *(long **)((ulong)(uVar3 + iVar5) * 8 + 0x10cd9f328);
              if (plVar25 != (long *)0x0) goto LAB_1002d71ac;
            }
LAB_1002d71c0:
            uVar16 = 6;
            if (plRam000000010cd9f2f8 != param_11) {
              uVar16 = 4;
            }
            plVar25 = param_11;
            if ((-uVar6 & 0xffff) < uVar6 >> (ulong)uVar16) {
              plVar25 = plRam000000010cd9f308;
            }
          }
        }
LAB_1002d71ac:
        plVar11 = plVar25;
        func_0x00010089ef8c(plVar25,uVar6);
        if (plVar11 != (long *)0x0) goto LAB_1002d6c08;
        (**(code **)(*plVar25 + 0x48))(plVar25,uVar6,1,0);
      }
      plVar11 = (long *)0x0;
    }
LAB_1002d6c08:
    param_1[0x17] = plVar11;
    if ((*(byte *)((long)param_1 + 0xd1) >> 3 & 1) != 0) {
      uStack_7c = 0;
      plVar25 = (long *)param_1[6];
      if (*(code **)(*plVar25 + 0x58) == (code *)&LAB_10801c0e4) {
        func_0x00010005efd8(uRam000000010c51de20,&uStack_7c,4);
        *(int *)((long)plVar25 + 0xac) = *(int *)((long)plVar25 + 0xac) + 4;
      }
      else {
        (**(code **)(*plVar25 + 0x58))(plVar25,&uStack_7c);
        if ((int)plVar25 == 0) goto LAB_1002d727c;
      }
      uVar6 = uStack_7c;
      uVar26 = (ulong)uStack_7c;
      if (uStack_7c != 0) {
        if (0x3ffffffe < uStack_7c) goto LAB_1002d727c;
        uVar16 = *(uint *)((long)param_1 + 0x44) & 0x3fffffff;
        if (uVar16 < uStack_7c) {
          puVar10 = (undefined8 *)0x10ca87f58;
          (*pcRam000000010ca87f58)();
          pcVar4 = pcRam000000010ca879e8;
          plVar25 = (long *)*puVar10;
          if (plVar25 == (long *)0x0) {
            plVar11 = (long *)0x0;
          }
          else {
            pbVar9 = (byte *)0x10ca879e8;
            (*pcRam000000010ca879e8)();
            uVar12 = 0x10ca879d0;
            if ((*pbVar9 & 1) == 0) {
              func_0x000108001218();
              uVar13 = uVar12;
              func_0x000108001224();
              func_0x000108001230(uVar12);
              puVar10 = (undefined8 *)0x10ca879d0;
              (*pcRam000000010ca879d0)();
              *puVar10 = extraout_x9;
              puVar10[1] = uVar13;
              puVar14 = (undefined1 *)0x10ca879e8;
              (*pcVar4)();
              *puVar14 = 1;
            }
            plVar11 = (long *)0x10ca879d0;
            (*pcRam000000010ca879d0)();
            if ((ulong)plVar11[1] <= (ulong)((long)plVar24 - *plVar11)) {
              plVar11 = (long *)0x0;
              if ((plVar24 < (long *)plVar25[6]) ||
                 ((long *)(plVar25[6] + (ulong)*(uint *)(plVar25 + 7)) <= plVar24))
              goto LAB_1002d6ee4;
            }
            if (*(code **)(*plVar25 + 0x18) == (code *)&LAB_107fba978) {
              uVar16 = (int)plVar25[7] - 4;
            }
            else {
              plVar11 = plVar25;
              (**(code **)(*plVar25 + 0x18))();
              uVar16 = (uint)plVar11;
            }
            plVar11 = (long *)0x0;
            if (uVar6 << 3 <= uVar16) {
              plVar11 = plVar25;
            }
          }
LAB_1002d6ee4:
          plVar25 = plRam000000010cd9f2b8;
          if (plVar11 != (long *)0x0) {
            plVar25 = plVar11;
          }
          uVar16 = *(uint *)((long)param_1 + 0x44) & 0x3fffffff;
        }
        else {
          plVar25 = (long *)0x0;
        }
        if (uVar16 < uVar6) {
          func_0x00010001c3f4(plVar24,uVar26,8,4,0,0,plVar25,0);
        }
        puVar10 = (undefined8 *)0x10ca87f10;
        (*pcRam000000010ca87f10)();
        *puVar10 = 0xffffdead00000005;
        param_1[8] = param_1[8] & 0xffffffffc0000000 | uVar26;
        if (uStack_72 == 1) {
          if (uStack_7c != 0) {
            uVar27 = 0;
            uVar26 = 0;
            do {
              plVar25 = (long *)param_1[6];
              (**(code **)(*plVar25 + 0x68))(plVar25,&uStack_7e,2);
              if ((int)plVar25 == 0) goto LAB_1002d727c;
              plVar25 = (long *)param_1[6];
              (**(code **)(*plVar25 + 0x68))(plVar25,&uStack_80,2);
              if ((int)plVar25 == 0) goto LAB_1002d727c;
              puVar1 = (uint *)(*plVar24 + (uVar27 & 0xfffffff8));
              *puVar1 = (uint)uStack_7e;
              puVar1[1] = (uint)uStack_80;
              uVar26 = uVar26 + 1;
              uVar27 = uVar27 + 8;
            } while (uVar26 < uStack_7c);
          }
        }
        else {
          plVar24 = (long *)param_1[6];
          iVar5 = uStack_7c * 8;
          if (*(code **)(*plVar24 + 0x68) == (code *)&LAB_10801c1c4) {
            func_0x00010005efd8(uRam000000010c51de20,param_1[7],iVar5);
            *(int *)((long)plVar24 + 0xac) = *(int *)((long)plVar24 + 0xac) + iVar5;
          }
          else {
            plVar25 = plVar24;
            (**(code **)(*plVar24 + 0x68))(plVar24,param_1[7],iVar5);
            if (((ulong)plVar25 & 1) == 0) {
LAB_1002d727c:
              uVar18 = 1;
              goto LAB_1002d6d8c;
            }
          }
        }
      }
    }
  }
  else {
    puVar10 = (undefined8 *)0x10ca87f10;
    (*pcRam000000010ca87f10)(param_7);
    uVar6 = (uint)param_6;
    *puVar10 = 0xffffdead00000009;
    if (0xc < extraout_w8_00) {
      func_0x000100002000(0x10cd6d5e1,0x100,"Write: Lzo Algo not supported.");
      *(undefined4 *)*puVar10 = 0;
    }
    *puVar10 = 0xffffdead00000009;
    uVar26 = (ulong)*pbVar9;
    if (*(long *)(uVar26 * 0x20 + 0x10ce34ef8) == 0) {
      func_0x000100002000(0x10cd6d5e1,0x100,
                          "LZO Algo 0x%08X for decompression not supported on platform");
      *(undefined4 *)*puVar10 = 0;
      uVar26 = (ulong)*pbVar9;
    }
    *(uint *)(param_1 + 0x19) = uVar6;
    uVar16 = (uint)uVar26;
    if (uVar16 - 5 < 2) {
      uVar6 = 8;
      func_0x00010167307c(8,param_6 & 0xffffffff);
    }
    else if (uVar16 < 0xb) {
      uVar19 = 1 << (ulong)(uVar16 & 0x1f);
      if ((uVar19 & 0x18) == 0) {
        if ((uVar19 & 0x180) == 0) {
          if ((1 << (ulong)(uVar16 & 0x1f) & 0x600U) == 0) goto LAB_1002d730c;
          uVar6 = 0xb;
        }
        else {
          uVar6 = 9;
        }
        func_0x00010167307c(uVar6,param_6 & 0xffffffff);
      }
      else {
        func_0x00010658e4c8();
      }
    }
    else {
LAB_1002d730c:
      uVar6 = uVar6 + (uVar6 >> 3) + 0x83;
    }
    *(uint *)(param_1 + 0x13) = uVar6;
    *(undefined4 *)(param_1 + 0x15) = 0;
    param_1[0x16] = 0;
    param_1[0x17] = 0;
    if ((*(byte *)((long)param_1 + 0xd1) >> 3 & 1) == 0) {
      FUN_1002fbe5c(param_1);
    }
  }
  *(int *)((long)param_1 + 0xac) = *(int *)(param_1 + 0x19);
  iVar5 = *(int *)(param_1 + 0x19) + *(int *)(param_1 + 0x13);
  uVar6 = iVar5 + 0x90;
  plVar24 = (long *)(ulong)uVar6;
  (*pcRam000000010ca88108)();
  if (*piVar8 == 5 && cRam000000010cda4ee8 != '\0') {
    if ((uVar6 < 0x100001) &&
       ((plVar25 = (long *)0x10cda4ec8, cRam000000010cda4ed0 == '\0' ||
        (plVar25 = (long *)0x10cda4ed8, cRam000000010cda4ee0 == '\0')))) {
      *(undefined1 *)(plVar25 + 1) = 1;
      plVar25 = (long *)*plVar25;
    }
    else {
      plVar25 = (long *)0x0;
    }
    *plVar23 = (long)plVar25;
  }
  else {
    plVar25 = (long *)*plVar23;
  }
  iVar15 = extraout_w8;
  if (plVar25 != (long *)0x0) goto LAB_1002d6d78;
  if (uVar6 == 0) goto LAB_1002d72c8;
  plVar23 = param_11;
  if (*(char *)((long)param_11 + 0x2a) != '\0') goto LAB_1002d7068;
  puVar10 = (undefined8 *)0x10ca87f40;
  (*pcRam000000010ca87f40)();
  plVar23 = (long *)*puVar10;
  if ((long *)*puVar10 != (long *)0x0) goto LAB_1002d7068;
  if (plRam000000010cd9f2b8 == param_11) {
    uVar16 = iVar5 + 0x10fU & 0xffffff80;
    if (uVar16 - 0x91 < 0xffffff70) {
      if (uVar16 - 0x1c1 < 0xfffffed0) {
        if (uVar16 - 0x301 < 0xfffffec0) goto LAB_1002d7088;
        uVar19 = 0x1c1;
        iVar5 = 0x49;
        lVar20 = 2;
      }
      else {
        uVar19 = 0x91;
        iVar5 = 0x23;
        lVar20 = 1;
      }
    }
    else {
      lVar20 = 0;
      iVar5 = 0;
      uVar19 = 1;
    }
    uVar2 = *(uint *)(&UNK_10afa77d8 + lVar20 * 0xc);
    uVar16 = (uVar16 + uVar2) - 1 & -uVar2;
    if (uVar16 < 9) {
      uVar16 = 8;
    }
    if (uVar19 < 9) {
      uVar19 = 8;
    }
    uVar3 = 0;
    if (uVar2 != 0) {
      uVar3 = (uVar16 - uVar19) / uVar2;
    }
    plVar23 = *(long **)((ulong)(uVar3 + iVar5) * 8 + 0x10cd9f328);
    if (plVar23 != (long *)0x0) goto LAB_1002d7068;
  }
LAB_1002d7088:
  uVar16 = 6;
  if (plRam000000010cd9f2f8 != param_11) {
    uVar16 = 4;
  }
  plVar23 = param_11;
  if ((-uVar6 & 0xffff) < uVar6 >> (ulong)uVar16) {
    plVar23 = plRam000000010cd9f308;
  }
LAB_1002d7068:
  while( true ) {
    plVar25 = plVar23;
    func_0x000100009f38(plVar23,plVar24,0x80);
    if (plVar25 == (long *)0x0) {
      (**(code **)(*plVar23 + 0x48))(plVar23,plVar24,0x80,0);
LAB_1002d72c8:
      plVar25 = (long *)0x0;
    }
    param_1[0x14] = plVar25;
    iVar15 = *(int *)((long)param_1 + 0xac);
LAB_1002d6d78:
    uVar18 = 0;
    param_1[0x12] = (long)plVar25 + (ulong)(iVar15 + 0x7fU & 0xffffff80);
LAB_1002d6d8c:
    *(undefined4 *)((long)param_1 + 0xd4) = uVar18;
    if (*(long *)PTR_10b4d40c8 == lStack_68) break;
    func_0x0001080011d0();
    plVar23 = param_11;
  }
  return param_1;
}

 (GhidraScript)  
INFO 0x1002fb3f8 disassemble=true body=2660 instructions=665
DIAG completed=true cancelled=false hf=true
