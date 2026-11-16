// FUN_1002fb3f8 @ 1002fb3f8 (2660 bytes)
void FUN_1002fb3f8(long param_1,long *param_2,byte param_3,int param_4,int param_5,ulong param_6,
                  byte param_7,undefined4 param_8,char param_9,undefined4 param_10,long *param_11)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  code *pcVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  undefined8 uVar8;
  undefined8 *puVar9;
  byte *pbVar10;
  undefined8 uVar11;
  undefined1 *puVar12;
  long *plVar13;
  uint extraout_w8;
  int extraout_w8_00;
  int iVar14;
  uint extraout_w8_01;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  undefined8 extraout_x10;
  byte bVar18;
  long lVar19;
  byte bVar20;
  byte bVar21;
  long *plVar22;
  byte *pbVar23;
  ulong uVar24;
  ulong uVar25;
  ushort uStack_80;
  ushort uStack_7e;
  uint uStack_7c;
  uint uStack_78;
  ushort uStack_72;
  long lStack_70;
  long lStack_68;
  
  lStack_68 = *(long *)PTR_10b4d40c8;
  pbVar23 = (byte *)(param_1 + 0xd0);
  *pbVar23 = param_7;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(long **)(param_1 + 0x30) = param_2;
  bVar18 = 2;
  if (param_5 == 0) {
    bVar18 = 0;
  }
  *(undefined4 *)(param_1 + 0xcc) = param_8;
  bVar20 = 4;
  if (param_9 == '\0') {
    bVar20 = 0;
  }
  *(undefined8 *)(param_1 + 0xc0) = 0;
  bVar21 = 8;
  if (param_4 == 0) {
    bVar21 = 0;
  }
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x88) = 0xffffffff;
  *(byte *)(param_1 + 0xd1) =
       bVar21 | param_3 ^ 1 | bVar18 | bVar20 | *(byte *)(param_1 + 0xd1) & 0xe0;
  piVar7 = (int *)0x10ca88108;
  if ((param_3 & 1) == 0) {
    if (*(code **)(*param_2 + 0x60) == (code *)&LAB_10801c154) {
      func_0x00010005efd8(uRam000000010c51de20,&lStack_70,8);
      *(int *)((long)param_2 + 0xac) = *(int *)((long)param_2 + 0xac) + 8;
      iVar5 = 1;
    }
    else {
      plVar13 = param_2;
      (**(code **)(*param_2 + 0x60))(param_2,&lStack_70);
      iVar5 = (int)plVar13;
    }
    if (iVar5 == 0 || lStack_70 != 0x1004fa9957fbaa33) goto LAB_1002fbc98;
    if (*(code **)(*param_2 + 0x50) == (code *)&LAB_10801c074) {
      func_0x00010005efd8(uRam000000010c51de20,&uStack_72,2);
      *(int *)((long)param_2 + 0xac) = *(int *)((long)param_2 + 0xac) + 2;
      iVar5 = 1;
    }
    else {
      plVar13 = param_2;
      (**(code **)(*param_2 + 0x50))(param_2,&uStack_72);
      iVar5 = (int)plVar13;
    }
    if ((iVar5 == 0) || (3 < uStack_72)) goto LAB_1002fbc98;
    if (*(code **)(*param_2 + 0x48) == (code *)&LAB_10801c004) {
      func_0x00010005efd8(uRam000000010c51de20,pbVar23,1);
      *(int *)((long)param_2 + 0xac) = *(int *)((long)param_2 + 0xac) + 1;
    }
    else {
      plVar13 = param_2;
      (**(code **)(*param_2 + 0x48))(param_2,pbVar23);
      if ((int)plVar13 == 0) goto LAB_1002fbc98;
    }
    if ((0xc < (ulong)*pbVar23) || (*(long *)((ulong)*pbVar23 * 0x20 + 0x10ce34ef8) == 0))
    goto LAB_1002fbc98;
    uStack_78 = 0;
    if (*(code **)(*param_2 + 0x58) == (code *)&LAB_10801c0e4) {
      func_0x00010005efd8(uRam000000010c51de20,&uStack_78,4);
      *(int *)((long)param_2 + 0xac) = *(int *)((long)param_2 + 0xac) + 4;
    }
    else {
      (**(code **)(*param_2 + 0x58))(param_2,&uStack_78);
      if ((int)param_2 == 0) goto LAB_1002fbc98;
    }
    if ((int)uStack_78 < 0) {
      uStack_78 = uStack_78 & 0x7fffffff;
      bVar18 = *(byte *)(param_1 + 0xd1) | 8;
    }
    else {
      bVar18 = *(byte *)(param_1 + 0xd1) & 0xf7;
    }
    *(byte *)(param_1 + 0xd1) = bVar18;
    *(uint *)(param_1 + 200) = uStack_78;
    *(uint *)(param_1 + 0x98) = uStack_78;
    *(undefined8 *)(param_1 + 0xb0) = 0;
    *(uint *)(param_1 + 0xa8) = uStack_78;
    piVar6 = piVar7;
    (*pcRam000000010ca88108)();
    if (*piVar6 == 5) {
      *(undefined8 *)(param_1 + 0xb8) = 0x10cda4ef0;
      uVar16 = extraout_w8;
    }
    else {
      uVar16 = *(uint *)((ulong)*pbVar23 * 0x20 + 0x10ce34f00);
      if (uVar16 == 0) {
LAB_1002fbd14:
        plVar22 = (long *)0x0;
      }
      else {
        plVar13 = param_11;
        if (*(char *)((long)param_11 + 0x2a) == '\0') {
          puVar9 = (undefined8 *)0x10ca87f40;
          (*pcRam000000010ca87f40)();
          plVar13 = (long *)*puVar9;
          if ((long *)*puVar9 == (long *)0x0) {
            if (plRam000000010cd9f2b8 == param_11) {
              if (uVar16 - 0x91 < 0xffffff70) {
                if (uVar16 - 0x1c1 < 0xfffffed0) {
                  if (uVar16 - 0x301 < 0xfffffec0) goto LAB_1002fbbdc;
                  uVar15 = 0x1c1;
                  iVar5 = 0x49;
                  lVar19 = 2;
                }
                else {
                  uVar15 = 0x91;
                  iVar5 = 0x23;
                  lVar19 = 1;
                }
              }
              else {
                lVar19 = 0;
                iVar5 = 0;
                uVar15 = 1;
              }
              uVar2 = *(uint *)(&UNK_10afa77d8 + lVar19 * 0xc);
              uVar17 = (uVar16 + uVar2) - 1 & -uVar2;
              if (uVar17 < 9) {
                uVar17 = 8;
              }
              if (uVar15 < 9) {
                uVar15 = 8;
              }
              uVar3 = 0;
              if (uVar2 != 0) {
                uVar3 = (uVar17 - uVar15) / uVar2;
              }
              plVar13 = *(long **)((ulong)(uVar3 + iVar5) * 8 + 0x10cd9f328);
              if (plVar13 != (long *)0x0) goto LAB_1002fbbc0;
            }
LAB_1002fbbdc:
            uVar15 = 6;
            if (plRam000000010cd9f2f8 != param_11) {
              uVar15 = 4;
            }
            plVar13 = param_11;
            if ((-uVar16 & 0xffff) < uVar16 >> (ulong)uVar15) {
              plVar13 = plRam000000010cd9f308;
            }
          }
        }
LAB_1002fbbc0:
        plVar22 = plVar13;
        func_0x00010089ef8c(plVar13,uVar16);
        if (plVar22 == (long *)0x0) {
          (**(code **)(*plVar13 + 0x48))(plVar13,uVar16,1,0);
          goto LAB_1002fbd14;
        }
      }
      *(long **)(param_1 + 0xb8) = plVar22;
      uVar16 = (uint)*(byte *)(param_1 + 0xd1);
    }
    if ((uVar16 >> 3 & 1) != 0) {
      uStack_7c = 0;
      pbVar23 = *(byte **)(param_1 + 0x30);
      if (*(code **)(*(long *)pbVar23 + 0x58) == (code *)&LAB_10801c0e4) {
        func_0x00010005efd8(uRam000000010c51de20,&uStack_7c,4);
        *(int *)(pbVar23 + 0xac) = *(int *)(pbVar23 + 0xac) + 4;
      }
      else {
        pbVar10 = pbVar23;
        (**(code **)(*(long *)pbVar23 + 0x58))(pbVar23,&uStack_7c);
        if ((int)pbVar10 == 0) goto LAB_1002fbc98;
      }
      uVar16 = uStack_7c;
      uVar24 = (ulong)uStack_7c;
      if (uStack_7c != 0) {
        if (0x3ffffffe < uStack_7c) goto LAB_1002fbc98;
        pbVar23 = (byte *)(param_1 + 0x38);
        uVar15 = *(uint *)(param_1 + 0x44) & 0x3fffffff;
        if (uVar15 < uStack_7c) {
          puVar9 = (undefined8 *)0x10ca87f58;
          (*pcRam000000010ca87f58)();
          pcVar4 = pcRam000000010ca879e8;
          plVar13 = (long *)*puVar9;
          if (plVar13 == (long *)0x0) {
            plVar22 = (long *)0x0;
          }
          else {
            pbVar10 = (byte *)0x10ca879e8;
            (*pcRam000000010ca879e8)();
            uVar8 = 0x10ca879d0;
            if ((*pbVar10 & 1) == 0) {
              func_0x000108001218();
              uVar11 = uVar8;
              func_0x000108001224();
              func_0x000108001230(uVar8);
              puVar9 = (undefined8 *)0x10ca879d0;
              (*pcRam000000010ca879d0)();
              *puVar9 = extraout_x10;
              puVar9[1] = uVar11;
              puVar12 = (undefined1 *)0x10ca879e8;
              (*pcVar4)();
              *puVar12 = 1;
            }
            plVar22 = (long *)0x10ca879d0;
            (*pcRam000000010ca879d0)();
            if ((ulong)plVar22[1] <= (ulong)((long)pbVar23 - *plVar22)) {
              plVar22 = (long *)0x0;
              if ((pbVar23 < (byte *)plVar13[6]) ||
                 ((byte *)plVar13[6] + *(uint *)(plVar13 + 7) <= pbVar23)) goto LAB_1002fb8f8;
            }
            if (*(code **)(*plVar13 + 0x18) == (code *)&LAB_107fba978) {
              uVar15 = (int)plVar13[7] - 4;
            }
            else {
              plVar22 = plVar13;
              (**(code **)(*plVar13 + 0x18))();
              uVar15 = (uint)plVar22;
            }
            plVar22 = (long *)0x0;
            if (uVar16 << 3 <= uVar15) {
              plVar22 = plVar13;
            }
          }
LAB_1002fb8f8:
          plVar13 = plRam000000010cd9f2b8;
          if (plVar22 != (long *)0x0) {
            plVar13 = plVar22;
          }
          uVar15 = *(uint *)(param_1 + 0x44) & 0x3fffffff;
        }
        else {
          plVar13 = (long *)0x0;
        }
        if (uVar15 < uVar16) {
          func_0x00010001c3f4(pbVar23,uVar24,8,4,0,0,plVar13,0);
        }
        puVar9 = (undefined8 *)0x10ca87f10;
        (*pcRam000000010ca87f10)();
        *puVar9 = 0xffffdead00000005;
        *(ulong *)(param_1 + 0x40) = *(ulong *)(param_1 + 0x40) & 0xffffffffc0000000 | uVar24;
        if (uStack_72 == 1) {
          if (uStack_7c != 0) {
            uVar25 = 0;
            uVar24 = 0;
            do {
              plVar13 = *(long **)(param_1 + 0x30);
              (**(code **)(*plVar13 + 0x68))(plVar13,&uStack_7e,2);
              if ((int)plVar13 == 0) goto LAB_1002fbc98;
              plVar13 = *(long **)(param_1 + 0x30);
              (**(code **)(*plVar13 + 0x68))(plVar13,&uStack_80,2);
              if ((int)plVar13 == 0) goto LAB_1002fbc98;
              puVar1 = (uint *)(*(long *)pbVar23 + (uVar25 & 0xfffffff8));
              *puVar1 = (uint)uStack_7e;
              puVar1[1] = (uint)uStack_80;
              uVar24 = uVar24 + 1;
              uVar25 = uVar25 + 8;
            } while (uVar24 < uStack_7c);
          }
        }
        else {
          pbVar23 = *(byte **)(param_1 + 0x30);
          iVar5 = uStack_7c * 8;
          if (*(code **)(*(long *)pbVar23 + 0x68) == (code *)&LAB_10801c1c4) {
            func_0x00010005efd8(uRam000000010c51de20,*(undefined8 *)(param_1 + 0x38),iVar5);
            *(int *)(pbVar23 + 0xac) = *(int *)(pbVar23 + 0xac) + iVar5;
          }
          else {
            pbVar10 = pbVar23;
            (**(code **)(*(long *)pbVar23 + 0x68))(pbVar23,*(undefined8 *)(param_1 + 0x38),iVar5);
            if (((ulong)pbVar10 & 1) == 0) {
LAB_1002fbc98:
              uVar8 = 0;
              goto LAB_1002fb7a8;
            }
          }
        }
      }
    }
  }
  else {
    puVar9 = (undefined8 *)0x10ca87f10;
    (*pcRam000000010ca87f10)(param_7);
    uVar16 = (uint)param_6;
    *puVar9 = 0xffffdead00000009;
    if (0xc < extraout_w8_01) {
      func_0x000100002000(0x10cd6d5e1,0x100,"Write: Lzo Algo not supported.");
      *(undefined4 *)*puVar9 = 0;
    }
    *puVar9 = 0xffffdead00000009;
    uVar24 = (ulong)*pbVar23;
    if (*(long *)(uVar24 * 0x20 + 0x10ce34ef8) == 0) {
      func_0x000100002000(0x10cd6d5e1,0x100,
                          "LZO Algo 0x%08X for decompression not supported on platform");
      *(undefined4 *)*puVar9 = 0;
      uVar24 = (ulong)*pbVar23;
    }
    *(uint *)(param_1 + 200) = uVar16;
    uVar15 = (uint)uVar24;
    if (uVar15 - 5 < 2) {
      uVar16 = 8;
      func_0x00010167307c(8,param_6 & 0xffffffff);
    }
    else if (uVar15 < 0xb) {
      uVar17 = 1 << (ulong)(uVar15 & 0x1f);
      if ((uVar17 & 0x18) == 0) {
        if ((uVar17 & 0x180) == 0) {
          if ((1 << (ulong)(uVar15 & 0x1f) & 0x600U) == 0) goto LAB_1002fbd28;
          uVar16 = 0xb;
        }
        else {
          uVar16 = 9;
        }
        func_0x00010167307c(uVar16,param_6 & 0xffffffff);
      }
      else {
        func_0x00010658e4c8();
      }
    }
    else {
LAB_1002fbd28:
      uVar16 = uVar16 + (uVar16 >> 3) + 0x83;
    }
    *(uint *)(param_1 + 0x98) = uVar16;
    *(undefined4 *)(param_1 + 0xa8) = 0;
    *(undefined8 *)(param_1 + 0xb0) = 0;
    *(undefined8 *)(param_1 + 0xb8) = 0;
    if ((*(byte *)(param_1 + 0xd1) >> 3 & 1) == 0) {
      FUN_1002fbe5c(param_1);
    }
  }
  *(int *)(param_1 + 0xac) = *(int *)(param_1 + 200);
  iVar5 = *(int *)(param_1 + 200) + *(int *)(param_1 + 0x98);
  uVar16 = iVar5 + 0x90;
  pbVar23 = (byte *)(ulong)uVar16;
  (*pcRam000000010ca88108)();
  if (*piVar7 == 5 && cRam000000010cda4ee8 != '\0') {
    if ((uVar16 < 0x100001) &&
       ((plVar13 = (long *)0x10cda4ec8, cRam000000010cda4ed0 == '\0' ||
        (plVar13 = (long *)0x10cda4ed8, cRam000000010cda4ee0 == '\0')))) {
      *(undefined1 *)(plVar13 + 1) = 1;
      plVar13 = (long *)*plVar13;
    }
    else {
      plVar13 = (long *)0x0;
    }
    *(long **)(param_1 + 0xa0) = plVar13;
  }
  else {
    plVar13 = *(long **)(param_1 + 0xa0);
  }
  iVar14 = extraout_w8_00;
  if (plVar13 != (long *)0x0) goto LAB_1002fb794;
  if (uVar16 == 0) goto LAB_1002fbce4;
  plVar22 = param_11;
  if (*(char *)((long)param_11 + 0x2a) != '\0') goto LAB_1002fba7c;
  puVar9 = (undefined8 *)0x10ca87f40;
  (*pcRam000000010ca87f40)();
  plVar22 = (long *)*puVar9;
  if ((long *)*puVar9 != (long *)0x0) goto LAB_1002fba7c;
  if (plRam000000010cd9f2b8 == param_11) {
    uVar15 = iVar5 + 0x10fU & 0xffffff80;
    if (uVar15 - 0x91 < 0xffffff70) {
      if (uVar15 - 0x1c1 < 0xfffffed0) {
        if (uVar15 - 0x301 < 0xfffffec0) goto LAB_1002fba9c;
        uVar17 = 0x1c1;
        iVar5 = 0x49;
        lVar19 = 2;
      }
      else {
        uVar17 = 0x91;
        iVar5 = 0x23;
        lVar19 = 1;
      }
    }
    else {
      lVar19 = 0;
      iVar5 = 0;
      uVar17 = 1;
    }
    uVar2 = *(uint *)(&UNK_10afa77d8 + lVar19 * 0xc);
    uVar15 = (uVar15 + uVar2) - 1 & -uVar2;
    if (uVar15 < 9) {
      uVar15 = 8;
    }
    if (uVar17 < 9) {
      uVar17 = 8;
    }
    uVar3 = 0;
    if (uVar2 != 0) {
      uVar3 = (uVar15 - uVar17) / uVar2;
    }
    plVar22 = *(long **)((ulong)(uVar3 + iVar5) * 8 + 0x10cd9f328);
    if (plVar22 != (long *)0x0) goto LAB_1002fba7c;
  }
LAB_1002fba9c:
  uVar15 = 6;
  if (plRam000000010cd9f2f8 != param_11) {
    uVar15 = 4;
  }
  plVar22 = param_11;
  if ((-uVar16 & 0xffff) < uVar16 >> (ulong)uVar15) {
    plVar22 = plRam000000010cd9f308;
  }
LAB_1002fba7c:
  while( true ) {
    plVar13 = plVar22;
    func_0x000100009f38(plVar22,pbVar23,0x80);
    if (plVar13 == (long *)0x0) {
      (**(code **)(*plVar22 + 0x48))(plVar22,pbVar23,0x80,0);
LAB_1002fbce4:
      plVar13 = (long *)0x0;
    }
    *(long **)(param_1 + 0xa0) = plVar13;
    iVar14 = *(int *)(param_1 + 0xac);
LAB_1002fb794:
    *(ulong *)(param_1 + 0x90) = (long)plVar13 + (ulong)(iVar14 + 0x7fU & 0xffffff80);
    uVar8 = 1;
LAB_1002fb7a8:
    if (*(long *)PTR_10b4d40c8 == lStack_68) break;
    func_0x0001080011d0(uVar8);
    plVar22 = param_11;
  }
  return;
}

 (GhidraScript)  
real 149.23
user 170.62
sys 4.69
