openjdk version "28-ea" 2027-03-23
OpenJDK Runtime Environment (build 28-ea+23-1886)
OpenJDK 64-Bit Server VM (build 28-ea+23-1886, mixed mode)
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Features/SystemEmulation/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Processors/DATA/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Features/MicrosoftCodeAnalyzer/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Processors/PIC/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Features/PDB/ghidra_scripts
    /Volumes/LexarSSD/Applications/acst/tools/ghidra
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Debug/Debugger/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Features/BytePatterns/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Features/WildcardAssembler/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Features/FunctionID/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Features/GnuDemangler/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Processors/8051/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Features/PyGhidra/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Features/Base/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Features/DecompilerDependent/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Features/Decompiler/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Features/VersionTracking/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Debug/Debugger-rmi-trace/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Features/FileFormats/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Processors/JVM/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Processors/Atmel/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Features/BSim/ghidra_scripts
    /Users/<user>/tools/ghidra_12.1.4_PUBLIC/Ghidra/Features/SwiftDemangler/ghidra_scripts (HeadlessAnalyzer)  
openProgram=true
toggleCCode=true toggleSyntaxTree=true
INFO 0x10020b7b8 disassemble=true body=2476 instructions=619
DIAG completed=true cancelled=false hf=true

/* ===== FUN_10020b7b8 @ 10020b7b8 | 2476 bytes ===== */

void FUN_10020b7b8(undefined8 *param_1,undefined4 param_2,long *param_3,uint *param_4)

{
  ulong *puVar1;
  uint uVar2;
  long *plVar3;
  uint uVar4;
  ulong uVar5;
  undefined *puVar6;
  ushort uVar7;
  uint uVar8;
  int iVar9;
  long lVar10;
  long *plVar11;
  undefined8 *puVar12;
  long lVar13;
  long *plVar14;
  undefined8 *puVar15;
  ulong uVar16;
  ulong uVar17;
  undefined8 *local_78;
  undefined8 *local_70;
  long local_68;
  
  local_68 = *(long *)PTR_10b4d40c8;
  uVar7 = *(ushort *)((long)param_1 + 0xa2);
  plVar3 = (long *)0x0;
  if ((uVar7 & 8) != 0) {
    plVar3 = param_3;
  }
  *(undefined2 *)((long)param_1 + 0xfa) = 1;
  param_1[10] = param_4;
  uVar8 = *(uint *)(param_1 + 0x17);
  if (((uVar8 | 2) != 3) && (uVar8 != 2 && (*param_4 & 1) == 0)) {
    *(ushort *)((long)param_1 + 0xa2) = uVar7 & 0xff7f;
    goto LAB_10020bb70;
  }
  local_70 = (undefined8 *)0x0;
  if (plVar3 == (long *)0x0) {
    if (*(char *)(param_1[1] + 10) == '\0') {
      puVar15 = *(undefined8 **)(*param_3 + 0x10);
      puVar12 = puVar15;
      if (*(int *)(param_1 + 0x21) == 3) {
        if (((undefined8 *)0xffffffffec2f6fff < puVar15 + -0x20000000 ||
            0xffffff0000000000 < (long)puVar15 + 0x8000000000000001U) ||
            0xc000000000000000 < (long)puVar15 + 1U) {
          puVar12 = (undefined8 *)0x0;
        }
      }
      else if (puVar15 != (undefined8 *)0x0 &&
               (uVar8 != 1 && (*(char *)(param_1[1] + 0xb) == '\0' && (uVar7 & 0x80) == 0))) {
        puVar12 = &DAT_10cda3608;
        FUN_107ff08f0(&DAT_10cda3608,puVar15);
        uVar8 = *(uint *)(param_1 + 0x17);
      }
      local_70 = puVar12;
      if (((((((undefined8 *)0xffffffffec2f6fff < puVar15 + -0x20000000 ||
              0xffffff0000000000 < (long)puVar15 + 0x8000000000000001U) ||
             0xc000000000000000 < (long)puVar15 + 1U) && puVar12 != puVar15) && uVar8 == 0) &&
          (*(char *)(*param_3 + 0xb) < '\0')) && (*(long *)*param_3 != 0)) {
        puVar6 = &DAT_10cda2418;
        FUN_100024dac(&DAT_10cda2418,puVar12,0,&DAT_10cda21b8);
        puVar12 = (undefined8 *)*param_3;
        if (puVar12 != &DAT_10cda23e8) {
          do {
            uVar16 = puVar12[1];
            uVar5 = uVar16 - 0x100000000;
            if ((uVar5 & 0x7fffffff01ffffff) == 0) {
              FUN_100394d68(&DAT_10cda2478);
              puVar1 = puVar12 + 1;
              uVar17 = *puVar1;
              if (uVar17 == uVar16) {
                *puVar1 = uVar5;
                LOAcquire();
                uVar5 = *puVar1;
                *puVar1 = uVar5 | 0x8000000000000000;
                LORelease();
                FUN_10002e2dc(uVar5,&DAT_10cda2418,puVar12);
              }
              _os_unfair_recursive_lock_unlock(&DAT_10cda2478);
            }
            else {
              uVar17 = puVar12[1];
              if (uVar17 == uVar16) {
                puVar12[1] = uVar5;
              }
            }
          } while (uVar17 != uVar16);
        }
        *param_3 = (long)puVar6;
      }
    }
  }
  else {
    local_70 = (undefined8 *)plVar3[2];
  }
  if ((*(ushort *)((long)param_1 + 0xa2) >> 7 & 1) != 0) {
    local_70 = (undefined8 *)0x0;
  }
  puVar12 = param_1;
  FUN_10020a880(param_1,param_4);
  if ((int)puVar12 == 0) goto LAB_10020bb70;
  iVar9 = *(int *)(param_1 + 0x17);
  if (iVar9 == 2) {
    if ((((byte)*param_4 >> 5 & 1) != 0) || ((*(ushort *)((long)param_1 + 0xa2) >> 4 & 1) != 0)) {
      FUN_107fd220c(param_1[0x1d],param_4,&local_70);
      iVar9 = *(int *)(param_1 + 0x17);
      goto LAB_10020b908;
    }
  }
  else {
LAB_10020b908:
    if (iVar9 == 1) {
      local_78 = (undefined8 *)CONCAT44(local_78._4_4_,param_2);
      if ((*(char *)(*param_3 + 0xb) < '\0') &&
         (plVar14 = *(long **)*param_3, plVar14 != (long *)0x0)) {
        (**(code **)(*plVar14 + 0x40))();
        local_78 = (undefined8 *)CONCAT44(local_78._4_4_,(int)plVar14);
      }
      plVar14 = (long *)param_1[1];
      (**(code **)(*plVar14 + 0x30))(plVar14,"ClassID");
      (**(code **)(*plVar14 + 0xd0))(plVar14,&local_78);
      (**(code **)(*plVar14 + 0x48))(plVar14,"ClassID");
    }
  }
  plVar14 = (long *)param_1[1];
  lVar10 = *plVar14;
  if (*(code **)(lVar10 + 0x30) != FUN_10016b398) {
    (**(code **)(lVar10 + 0x30))(plVar14,"Value");
    lVar10 = *plVar14;
  }
  puVar12 = local_70;
  if (*(code **)(lVar10 + 0x138) == FUN_10016b928) {
    if ((ulong)*(ushort *)(plVar14 + 0x404) == 0) {
      if (*(char *)((long)plVar14 + 10) == '\0') goto LAB_10020b964;
LAB_10020bc74:
      plVar11 = (long *)plVar14[2];
      if (*(code **)(*plVar11 + 0x60) == FUN_1018bd0ec) {
        puVar12 = (undefined8 *)plVar11[5];
        if ((long)puVar12 + (8 - plVar11[4]) <= (long)(ulong)*(uint *)(plVar11 + 6)) {
          local_70 = (undefined8 *)*puVar12;
          if ((*(byte *)(plVar11 + 1) & 1) != 0) {
            uVar5 = ((ulong)local_70 & 0xff00ff00ff00ff00) >> 8 |
                    ((ulong)local_70 & 0xff00ff00ff00ff) << 8;
            uVar5 = (uVar5 & 0xffff0000ffff0000) >> 0x10 | (uVar5 & 0xffff0000ffff) << 0x10;
            local_70 = (undefined8 *)(uVar5 >> 0x20 | uVar5 << 0x20);
          }
          goto LAB_10020b9c4;
        }
      }
      else {
        (**(code **)(*plVar11 + 0x60))(plVar11,&local_70);
      }
    }
    else {
      plVar11 = plVar14 + (ulong)*(ushort *)(plVar14 + 0x404) * 2 + 2;
      if (*(char *)((long)plVar14 + 10) != '\0') {
        *(int *)plVar11 = (int)*plVar11 + -8;
        goto LAB_10020bc74;
      }
      *(int *)plVar11 = (int)*plVar11 + 8;
LAB_10020b964:
      plVar11 = (long *)plVar14[2];
      if (*(code **)(*plVar11 + 0x98) != FUN_1018bd178) {
        (**(code **)(*plVar11 + 0x98))(plVar11,local_70);
        goto LAB_10020b9cc;
      }
      if ((int)plVar11[8] != 0) {
        uVar5 = (ulong)(uint)((int)plVar11[5] - (int)plVar11[4]) + 8;
        if (*(uint *)(plVar11 + 6) < uVar5) {
          FUN_100026e44(plVar11,(int)uVar5 - *(uint *)(plVar11 + 6));
        }
      }
      uVar5 = ((ulong)puVar12 & 0xff00ff00ff00ff00) >> 8 | ((ulong)puVar12 & 0xff00ff00ff00ff) << 8;
      uVar5 = (uVar5 & 0xffff0000ffff0000) >> 0x10 | (uVar5 & 0xffff0000ffff) << 0x10;
      if ((*(uint *)(plVar11 + 1) & 1) != 0) {
        puVar12 = (undefined8 *)(uVar5 >> 0x20 | uVar5 << 0x20);
      }
      *(undefined8 **)plVar11[5] = puVar12;
      puVar12 = (undefined8 *)plVar11[5];
LAB_10020b9c4:
      plVar11[5] = (long)(puVar12 + 1);
    }
  }
  else {
    (**(code **)(lVar10 + 0x138))(plVar14,&local_70);
  }
LAB_10020b9cc:
  if (*(code **)(*plVar14 + 0x48) != FUN_10016b3dc) {
    (**(code **)(*plVar14 + 0x48))(plVar14,"Value");
  }
  iVar9 = *(int *)(param_1 + 0x17);
  if (iVar9 == 1) {
    puVar12 = &DAT_10cda3608;
    FUN_107ff08a8(&DAT_10cda3608,local_70);
    plVar14 = (long *)param_1[1];
    local_78 = puVar12;
    (**(code **)(*plVar14 + 0x30))(plVar14,"ValueAlt");
    (**(code **)(*plVar14 + 0x138))(plVar14,&local_78);
    (**(code **)(*plVar14 + 0x48))(plVar14,"ValueAlt");
    iVar9 = *(int *)(param_1 + 0x17);
  }
  else if ((*(char *)(param_1[1] + 10) != '\0') &&
          (((0xc000000000000000 < (long)local_70 + 1U ||
            (0xffffff0000000000 < (long)local_70 + 0x8000000000000001U)) ||
           ((undefined8 *)0xffffffffec2f6fff < local_70 + -0x20000000)))) {
    local_70 = (undefined8 *)0x0;
  }
  uVar7 = *(ushort *)((long)param_1 + 0xa2);
  *(ushort *)((long)param_1 + 0xa2) = uVar7 & 0xff7f;
  if ((iVar9 - 4U < 0xfffffffd) && ((uVar7 & 1) == 0)) {
    plVar14 = (long *)param_1[1];
    if (*(code **)(*plVar14 + 0x50) == FUN_10018be60) {
      uVar7 = (short)plVar14[0x404] - 1;
      *(ushort *)(plVar14 + 0x404) = uVar7;
      uVar8 = *(uint *)(plVar14 + (ulong)uVar7 * 2 + 4);
      if (*(char *)((long)plVar14 + 10) == '\0') {
        plVar11 = (long *)plVar14[2];
        lVar10 = plVar14[(ulong)uVar7 * 2 + 5];
        lVar13 = *plVar11;
        if (*(code **)(lVar13 + 0xd0) == FUN_1002b1524) {
          plVar11[7] = plVar11[5] - plVar11[4];
          plVar11[5] = plVar11[4] + lVar10;
        }
        else {
          (**(code **)(lVar13 + 0xd0))(plVar11,lVar10);
          plVar11 = (long *)plVar14[2];
          lVar13 = *plVar11;
        }
        if (*(code **)(lVar13 + 0x90) == FUN_1000944c4) {
          if ((int)plVar11[8] != 0) {
            uVar5 = (ulong)(uint)((int)plVar11[5] - (int)plVar11[4]) + 4;
            if (*(uint *)(plVar11 + 6) < uVar5) {
              FUN_100026e44(plVar11,(int)uVar5 - *(uint *)(plVar11 + 6));
            }
          }
          uVar4 = (uVar8 & 0xff00ff00) >> 8 | (uVar8 & 0xff00ff) << 8;
          uVar2 = uVar8;
          if ((*(uint *)(plVar11 + 1) & 1) != 0) {
            uVar2 = uVar4 >> 0x10 | uVar4 << 0x10;
          }
          *(uint *)plVar11[5] = uVar2;
          plVar11[5] = plVar11[5] + 4;
        }
        else {
          (**(code **)(lVar13 + 0x90))(plVar11);
        }
        plVar11 = (long *)plVar14[2];
        if (*(code **)(*plVar11 + 0xd8) == FUN_108025a5c) {
          plVar11[5] = plVar11[4] + plVar11[7];
        }
        else {
          (**(code **)(*plVar11 + 0xd8))(plVar11);
        }
        if ((ulong)*(ushort *)(plVar14 + 0x404) != 0) {
          iVar9 = uVar8 + 4;
          if (*(char *)((long)plVar14 + 10) != '\0') {
            iVar9 = -iVar9;
          }
          *(int *)(plVar14 + (ulong)*(ushort *)(plVar14 + 0x404) * 2 + 2) =
               (int)plVar14[(ulong)*(ushort *)(plVar14 + 0x404) * 2 + 2] + iVar9;
        }
      }
      else {
        if (uVar8 != 0) {
          (**(code **)(*(long *)plVar14[2] + 0xb0))((long *)plVar14[2]);
          uVar7 = *(ushort *)(plVar14 + 0x404);
        }
        if (uVar7 != 0) {
          iVar9 = (int)plVar14[(ulong)uVar7 * 2 + 2];
          if (*(char *)((long)plVar14 + 10) == '\0') {
            iVar9 = iVar9 + 4;
          }
          else {
            iVar9 = iVar9 + -4;
          }
          *(int *)(plVar14 + (ulong)uVar7 * 2 + 2) = iVar9;
        }
      }
    }
    else {
      (**(code **)(*plVar14 + 0x50))(plVar14,"Property");
    }
  }
  if ((*(int *)((long)param_1 + 0x44) < 2) && (local_70 == (undefined8 *)0xffffffff)) {
    local_70 = (undefined8 *)0x0;
  }
  if ((*(ushort *)((long)param_1 + 0xa2) >> 3 & 1) == 0) {
    if ((*(char *)(param_1[1] + 10) != '\0') && (local_70 != *(undefined8 **)(*param_3 + 0x10))) {
      puVar6 = &DAT_10cda2418;
      FUN_100024dac(&DAT_10cda2418,local_70,0,&DAT_10cda21b8);
      puVar12 = (undefined8 *)*param_3;
      if (puVar12 != &DAT_10cda23e8) {
        do {
          uVar16 = puVar12[1];
          uVar5 = uVar16 - 0x100000000;
          if ((uVar5 & 0x7fffffff01ffffff) == 0) {
            FUN_100394d68(&DAT_10cda2478);
            puVar1 = puVar12 + 1;
            uVar17 = *puVar1;
            if (uVar17 == uVar16) {
              *puVar1 = uVar5;
              LOAcquire();
              uVar5 = *puVar1;
              *puVar1 = uVar5 | 0x8000000000000000;
              LORelease();
              FUN_10002e2dc(uVar5,&DAT_10cda2418,puVar12);
            }
            _os_unfair_recursive_lock_unlock(&DAT_10cda2478);
          }
          else {
            uVar17 = puVar12[1];
            if (uVar17 == uVar16) {
              puVar12[1] = uVar5;
            }
          }
        } while (uVar17 != uVar16);
      }
      *param_3 = (long)puVar6;
    }
  }
  else {
    plVar3[2] = (long)local_70;
    *(undefined4 *)(plVar3 + 4) = param_2;
    *(byte *)((long)plVar3 + 0x24) = *(byte *)((long)plVar3 + 0x24) & 0xc0 | 0xb;
  }
  *param_1 = local_70;
LAB_10020bb70:
  if (*(long *)PTR_10b4d40c8 != local_68) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail();
  }
  return;
}

 (GhidraScript)  