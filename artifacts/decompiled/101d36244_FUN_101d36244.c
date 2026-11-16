// FUN_101d36244 @ 101d36244 (4148 bytes)
void FUN_101d36244(long param_1,long param_2,uint param_3)

{
  code *pcVar1;
  ulong *puVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  long *plVar6;
  undefined ***pppuVar7;
  undefined ***pppuVar8;
  undefined8 *puVar9;
  undefined *puVar10;
  long lVar11;
  ulong uVar12;
  long lVar13;
  long *plVar14;
  code *pcVar15;
  long *plVar16;
  uint uVar17;
  ulong uVar18;
  uint local_fc;
  long local_f8;
  long local_f0;
  undefined **local_e8;
  undefined **ppuStack_e0;
  undefined **local_d8;
  long *local_d0;
  long *local_c8;
  long *local_c0;
  long local_b8;
  long local_b0;
  undefined4 local_a4;
  code *local_a0;
  code *local_98;
  long *aplStack_90 [4];
  long local_70;
  
  local_70 = *(long *)PTR_10b4d40c8;
  if ((((param_2 == 0) || (DAT_10cb7d3a0 == (long *)0x0)) ||
      ((*(uint *)(DAT_10cb7d3a0 + 1) & 0x3fff) <= DAT_10bf22d68)) ||
     (lVar13 = *(long *)(*DAT_10cb7d3a0 + (ulong)DAT_10bf22d68 * 8), lVar13 == 0))
  goto LAB_101d36948;
  if ((DAT_10d438898 & 1) == 0) {
    iVar5 = 0xd438898;
    ___cxa_guard_acquire();
    if (iVar5 != 0) {
      FUN_101d375f4(&DAT_10d438860,"Body",1,1);
      ___cxa_atexit(FUN_105621ed0,&DAT_10d438860,0x100000000);
      ___cxa_guard_release(&DAT_10d438898);
    }
  }
  if ((DAT_10d4388d8 & 1) == 0) {
    iVar5 = 0xd4388d8;
    ___cxa_guard_acquire();
    if (iVar5 != 0) {
      FUN_101d375f4(&DAT_10d4388a0,"Head",1,1);
      ___cxa_atexit(FUN_105621ed0,&DAT_10d4388a0,0x100000000);
      ___cxa_guard_release(&DAT_10d4388d8);
    }
  }
  if ((DAT_10d438918 & 1) == 0) {
    iVar5 = 0xd438918;
    ___cxa_guard_acquire();
    if (iVar5 != 0) {
      FUN_101d375f4(&DAT_10d4388e0,"WeaponSlot1",1,1);
      ___cxa_atexit(FUN_105621ed0,&DAT_10d4388e0,0x100000000);
      ___cxa_guard_release(&DAT_10d438918);
    }
  }
  if ((DAT_10d438958 & 1) == 0) {
    iVar5 = 0xd438958;
    ___cxa_guard_acquire();
    if (iVar5 != 0) {
      FUN_101d375f4(&DAT_10d438920,"WeaponSlot2",1,1);
      ___cxa_atexit(FUN_105621ed0,&DAT_10d438920,0x100000000);
      ___cxa_guard_release(&DAT_10d438958);
    }
  }
  if ((DAT_10d438998 & 1) == 0) {
    iVar5 = 0xd438998;
    ___cxa_guard_acquire();
    if (iVar5 != 0) {
      FUN_101d375f4(&DAT_10d438960,"Horse",0,0);
      ___cxa_atexit(FUN_105621ed0,&DAT_10d438960,0x100000000);
      ___cxa_guard_release(&DAT_10d438998);
    }
  }
  if ((DAT_10d4389d8 & 1) == 0) {
    iVar5 = 0xd4389d8;
    ___cxa_guard_acquire();
    if (iVar5 != 0) {
      FUN_101d375f4(&DAT_10d4389a0,"Trinket",0,0);
      ___cxa_atexit(FUN_105621ed0,&DAT_10d4389a0,0x100000000);
      ___cxa_guard_release(&DAT_10d4389d8);
    }
  }
  plVar14 = *(long **)(param_2 + 0xc00);
  if (plVar14 == (long *)0x0) goto LAB_101d36948;
  local_b0 = 0;
  local_e8 = (undefined **)0x0;
  if ((ulong)*(byte *)(plVar14 + 0x2d) == 0xff) {
    local_a0 = (code *)0x0;
  }
  else {
    lVar11 = *(long *)(*(long *)((long)plVar14 + 0x13c) + (ulong)*(byte *)(plVar14 + 0x2d) * 8);
    local_a0 = (code *)0x0;
    if (lVar11 != 0) {
      local_a0 = *(code **)(lVar11 + 0x38);
    }
  }
  FUN_10214a9a0(&local_a0,&local_e8,&local_b0);
  local_b8 = 0;
  local_e8 = (undefined **)0x0;
  if ((ulong)*(byte *)(plVar14 + 0x2d) == 0xff) {
    local_a0 = (code *)0x0;
  }
  else {
    lVar11 = *(long *)(*(long *)((long)plVar14 + 0x13c) + (ulong)*(byte *)(plVar14 + 0x2d) * 8);
    local_a0 = (code *)0x0;
    if (lVar11 != 0) {
      local_a0 = *(code **)(lVar11 + 0x38);
    }
  }
  FUN_10214a7b8(&local_a0,&local_e8,&local_b8);
  local_e8 = &PTR_FUN_10b9c8d28;
  ppuStack_e0 = &PTR_FUN_10b9c8ec8;
  local_d8 = &PTR_FUN_10b9c8f78;
  plVar16 = plVar14;
  (*(code *)*DAT_10c5c9ec8)(plVar14,DAT_10c5c9ec8 + 2);
  plVar6 = plVar14;
  local_d0 = plVar16;
  (*(code *)DAT_10c5c9ec8[6])(plVar14,DAT_10c5c9ec8 + 8);
  plVar16 = plVar14;
  local_c8 = plVar6;
  (*(code *)DAT_10c5c9ec8[0xc])(plVar14,DAT_10c5c9ec8 + 0xe);
  pppuVar7 = &local_e8;
  local_c0 = plVar16;
  FUN_101d37374(pppuVar7,local_b8);
  bVar3 = (uint)*(byte *)(param_1 + 0x1b0) != (uint)pppuVar7;
  local_fc = (uint)bVar3;
  if (bVar3) {
    *(char *)(param_1 + 0x1b0) = (char)pppuVar7;
  }
  pppuVar8 = &local_e8;
  FUN_101d37374(pppuVar8,local_b0);
  if ((uint)*(byte *)(param_1 + 0x1b1) != (uint)pppuVar8) {
    *(char *)(param_1 + 0x1b1) = (char)pppuVar8;
    local_fc = 1;
  }
  FUN_101d378d0(lVar13,plVar14,local_b0,&DAT_10d438860);
  uVar4 = 0;
  if ((*(byte *)((long)*(ulong **)(param_1 + 0x180) + 0xb) & 0x80) != 0) {
    uVar4 = **(ulong **)(param_1 + 0x180);
  }
  if ((local_b0 == 0) || (lVar11 = local_b0, uVar4 != 0)) {
    if ((local_b0 == 0) && (uVar4 != 0)) {
      lVar11 = 0;
      goto LAB_101d36bac;
    }
    if ((uVar4 != 0) && (FUN_100de4d84(uVar4,local_b0,0), lVar11 = local_b0, (uVar4 & 1) == 0))
    goto LAB_101d36bac;
  }
  else {
LAB_101d36bac:
    puVar10 = &DAT_10cda2418;
    FUN_100024dac(&DAT_10cda2418,0,lVar11,&DAT_10cd62d90);
    puVar9 = *(undefined8 **)(param_1 + 0x180);
    if (puVar9 != &DAT_10cda23e8) {
      do {
        uVar18 = puVar9[1];
        uVar4 = uVar18 - 0x100000000;
        if ((uVar4 & 0x7fffffff01ffffff) == 0) {
          FUN_100394d68(&DAT_10cda2478);
          puVar2 = puVar9 + 1;
          uVar12 = *puVar2;
          if (uVar12 == uVar18) {
            *puVar2 = uVar4;
            LOAcquire();
            uVar4 = *puVar2;
            *puVar2 = uVar4 | 0x8000000000000000;
            LORelease();
            FUN_10002e2dc(uVar4,&DAT_10cda2418,puVar9);
          }
          _os_unfair_recursive_lock_unlock(&DAT_10cda2478);
        }
        else {
          uVar12 = puVar9[1];
          if (uVar12 == uVar18) {
            puVar9[1] = uVar4;
          }
        }
      } while (uVar12 != uVar18);
    }
    *(undefined **)(param_1 + 0x180) = puVar10;
    local_fc = 1;
  }
  FUN_101d378d0(lVar13,plVar14,local_b8,&DAT_10d4388a0,pppuVar7);
  uVar4 = 0;
  if ((*(byte *)((long)*(ulong **)(param_1 + 0x188) + 0xb) & 0x80) != 0) {
    uVar4 = **(ulong **)(param_1 + 0x188);
  }
  if ((local_b8 == 0) || (lVar11 = local_b8, uVar4 != 0)) {
    if ((local_b8 == 0) && (uVar4 != 0)) {
      lVar11 = 0;
      goto LAB_101d36d48;
    }
    if ((uVar4 != 0) && (FUN_100de4d84(uVar4,local_b8,0), lVar11 = local_b8, (uVar4 & 1) == 0))
    goto LAB_101d36d48;
  }
  else {
LAB_101d36d48:
    puVar10 = &DAT_10cda2418;
    FUN_100024dac(&DAT_10cda2418,0,lVar11,&DAT_10cd62d90);
    puVar9 = *(undefined8 **)(param_1 + 0x188);
    if (puVar9 != &DAT_10cda23e8) {
      do {
        uVar18 = puVar9[1];
        uVar4 = uVar18 - 0x100000000;
        if ((uVar4 & 0x7fffffff01ffffff) == 0) {
          FUN_100394d68(&DAT_10cda2478);
          puVar2 = puVar9 + 1;
          uVar12 = *puVar2;
          if (uVar12 == uVar18) {
            *puVar2 = uVar4;
            LOAcquire();
            uVar4 = *puVar2;
            *puVar2 = uVar4 | 0x8000000000000000;
            LORelease();
            FUN_10002e2dc(uVar4,&DAT_10cda2418,puVar9);
          }
          _os_unfair_recursive_lock_unlock(&DAT_10cda2478);
        }
        else {
          uVar12 = puVar9[1];
          if (uVar12 == uVar18) {
            puVar9[1] = uVar4;
          }
        }
      } while (uVar12 != uVar18);
    }
    *(undefined **)(param_1 + 0x188) = puVar10;
    local_fc = 1;
  }
  plVar16 = plVar14;
  FUN_101d37278(plVar14,0);
  if (plVar16 == (long *)0x0) {
LAB_101d36e0c:
    uVar17 = 0;
  }
  else {
    pcVar15 = (code *)plVar16[0xd];
    if (pcVar15 == (code *)&DAT_10cda23e8) {
      pcVar15 = (code *)&DAT_10cda2418;
      FUN_100024dac(&DAT_10cda2418,0,plVar16,&DAT_10cd62a98);
      local_a0 = pcVar15;
    }
    else {
      pcVar1 = pcVar15 + 8;
      LOAcquire();
      *(long *)pcVar1 = *(long *)pcVar1 + 0x100000000;
      LORelease();
      LOAcquire();
      *(long *)pcVar1 = *(long *)pcVar1 + 0x100000000;
      LORelease();
      local_a0 = pcVar15;
      do {
        uVar18 = *(ulong *)(pcVar15 + 8);
        uVar4 = uVar18 - 0x100000000;
        if ((uVar4 & 0x7fffffff01ffffff) == 0) {
          FUN_100394d68(&DAT_10cda2478);
          pcVar1 = pcVar15 + 8;
          uVar12 = *(ulong *)pcVar1;
          if (uVar12 == uVar18) {
            *(ulong *)pcVar1 = uVar4;
            LOAcquire();
            uVar4 = *(ulong *)pcVar1;
            *(ulong *)pcVar1 = uVar4 | 0x8000000000000000;
            LORelease();
            FUN_10002e2dc(uVar4,&DAT_10cda2418,pcVar15);
          }
          _os_unfair_recursive_lock_unlock(&DAT_10cda2478);
        }
        else {
          uVar12 = *(ulong *)(pcVar15 + 8);
          if (uVar12 == uVar18) {
            *(ulong *)(pcVar15 + 8) = uVar4;
          }
        }
      } while (uVar12 != uVar18);
    }
    plVar16 = (long *)0x0;
    if (((char)local_a0[0xb] < '\0') && (*(long *)local_a0 != 0)) {
      if (local_c0 == (long *)0x0) {
        plVar16 = (long *)0x0;
      }
      else {
        plVar16 = local_c0;
        (**(code **)(*local_c0 + 0x50))(local_c0,&local_a0);
      }
    }
    pcVar15 = local_a0;
    if (local_a0 != (code *)&DAT_10cda23e8) {
      do {
        uVar18 = *(ulong *)(pcVar15 + 8);
        uVar4 = uVar18 - 0x100000000;
        if ((uVar4 & 0x7fffffff01ffffff) == 0) {
          FUN_100394d68(&DAT_10cda2478);
          pcVar1 = pcVar15 + 8;
          uVar12 = *(ulong *)pcVar1;
          if (uVar12 == uVar18) {
            *(ulong *)pcVar1 = uVar4;
            LOAcquire();
            uVar4 = *(ulong *)pcVar1;
            *(ulong *)pcVar1 = uVar4 | 0x8000000000000000;
            LORelease();
            FUN_10002e2dc(uVar4,&DAT_10cda2418,pcVar15);
          }
          _os_unfair_recursive_lock_unlock(&DAT_10cda2478);
        }
        else {
          uVar12 = *(ulong *)(pcVar15 + 8);
          if (uVar12 == uVar18) {
            *(ulong *)(pcVar15 + 8) = uVar4;
          }
        }
      } while (uVar12 != uVar18);
    }
    FUN_101d378d0(lVar13,plVar14,plVar16,&DAT_10d4388e0,0);
    uVar4 = 0;
    if ((*(byte *)((long)*(ulong **)(param_1 + 400) + 0xb) & 0x80) != 0) {
      uVar4 = **(ulong **)(param_1 + 400);
    }
    if (((plVar16 == (long *)0x0) || (uVar4 != 0)) && ((plVar16 != (long *)0x0 || (uVar4 == 0)))) {
      if (uVar4 == 0) goto LAB_101d36e0c;
      FUN_100de4d84(uVar4,plVar16,0);
      uVar17 = 0;
      if ((uVar4 & 1) == 0) goto LAB_101d36c70;
    }
    else {
LAB_101d36c70:
      puVar10 = &DAT_10cda2418;
      FUN_100024dac(&DAT_10cda2418,0,plVar16,&DAT_10cd62d90);
      puVar9 = *(undefined8 **)(param_1 + 400);
      if (puVar9 != &DAT_10cda23e8) {
        do {
          uVar18 = puVar9[1];
          uVar4 = uVar18 - 0x100000000;
          if ((uVar4 & 0x7fffffff01ffffff) == 0) {
            FUN_100394d68(&DAT_10cda2478);
            puVar2 = puVar9 + 1;
            uVar12 = *puVar2;
            if (uVar12 == uVar18) {
              *puVar2 = uVar4;
              LOAcquire();
              uVar4 = *puVar2;
              *puVar2 = uVar4 | 0x8000000000000000;
              LORelease();
              FUN_10002e2dc(uVar4,&DAT_10cda2418,puVar9);
            }
            _os_unfair_recursive_lock_unlock(&DAT_10cda2478);
          }
          else {
            uVar12 = puVar9[1];
            if (uVar12 == uVar18) {
              puVar9[1] = uVar4;
            }
          }
        } while (uVar12 != uVar18);
      }
      *(undefined **)(param_1 + 400) = puVar10;
      uVar17 = 1;
    }
  }
  plVar16 = plVar14;
  FUN_101d37278(plVar14,1);
  if (plVar16 != (long *)0x0) {
    pcVar15 = (code *)plVar16[0xd];
    if (pcVar15 == (code *)&DAT_10cda23e8) {
      pcVar15 = (code *)&DAT_10cda2418;
      FUN_100024dac(&DAT_10cda2418,0,plVar16,&DAT_10cd62a98);
      local_a0 = pcVar15;
    }
    else {
      pcVar1 = pcVar15 + 8;
      LOAcquire();
      *(long *)pcVar1 = *(long *)pcVar1 + 0x100000000;
      LORelease();
      LOAcquire();
      *(long *)pcVar1 = *(long *)pcVar1 + 0x100000000;
      LORelease();
      local_a0 = pcVar15;
      do {
        uVar18 = *(ulong *)(pcVar15 + 8);
        uVar4 = uVar18 - 0x100000000;
        if ((uVar4 & 0x7fffffff01ffffff) == 0) {
          FUN_100394d68(&DAT_10cda2478);
          pcVar1 = pcVar15 + 8;
          uVar12 = *(ulong *)pcVar1;
          if (uVar12 == uVar18) {
            *(ulong *)pcVar1 = uVar4;
            LOAcquire();
            uVar4 = *(ulong *)pcVar1;
            *(ulong *)pcVar1 = uVar4 | 0x8000000000000000;
            LORelease();
            FUN_10002e2dc(uVar4,&DAT_10cda2418,pcVar15);
          }
          _os_unfair_recursive_lock_unlock(&DAT_10cda2478);
        }
        else {
          uVar12 = *(ulong *)(pcVar15 + 8);
          if (uVar12 == uVar18) {
            *(ulong *)(pcVar15 + 8) = uVar4;
          }
        }
      } while (uVar12 != uVar18);
    }
    plVar16 = (long *)0x0;
    if (((char)local_a0[0xb] < '\0') && (*(long *)local_a0 != 0)) {
      if (local_c0 == (long *)0x0) {
        plVar16 = (long *)0x0;
      }
      else {
        plVar16 = local_c0;
        (**(code **)(*local_c0 + 0x50))(local_c0,&local_a0);
      }
    }
    pcVar15 = local_a0;
    if (local_a0 != (code *)&DAT_10cda23e8) {
      do {
        uVar18 = *(ulong *)(pcVar15 + 8);
        uVar4 = uVar18 - 0x100000000;
        if ((uVar4 & 0x7fffffff01ffffff) == 0) {
          FUN_100394d68(&DAT_10cda2478);
          pcVar1 = pcVar15 + 8;
          uVar12 = *(ulong *)pcVar1;
          if (uVar12 == uVar18) {
            *(ulong *)pcVar1 = uVar4;
            LOAcquire();
            uVar4 = *(ulong *)pcVar1;
            *(ulong *)pcVar1 = uVar4 | 0x8000000000000000;
            LORelease();
            FUN_10002e2dc(uVar4,&DAT_10cda2418,pcVar15);
          }
          _os_unfair_recursive_lock_unlock(&DAT_10cda2478);
        }
        else {
          uVar12 = *(ulong *)(pcVar15 + 8);
          if (uVar12 == uVar18) {
            *(ulong *)(pcVar15 + 8) = uVar4;
          }
        }
      } while (uVar12 != uVar18);
    }
    FUN_101d378d0(lVar13,plVar14,plVar16,&DAT_10d438920,0);
    uVar4 = 0;
    if ((*(byte *)((long)*(ulong **)(param_1 + 0x198) + 0xb) & 0x80) != 0) {
      uVar4 = **(ulong **)(param_1 + 0x198);
    }
    if ((((plVar16 != (long *)0x0) && (uVar4 == 0)) || ((plVar16 == (long *)0x0 && (uVar4 != 0))))
       || ((uVar4 != 0 && (FUN_100de4d84(uVar4,plVar16,0), (uVar4 & 1) == 0)))) {
      puVar10 = &DAT_10cda2418;
      FUN_100024dac(&DAT_10cda2418,0,plVar16,&DAT_10cd62d90);
      puVar9 = *(undefined8 **)(param_1 + 0x198);
      if (puVar9 != &DAT_10cda23e8) {
        do {
          uVar18 = puVar9[1];
          uVar4 = uVar18 - 0x100000000;
          if ((uVar4 & 0x7fffffff01ffffff) == 0) {
            FUN_100394d68(&DAT_10cda2478);
            puVar2 = puVar9 + 1;
            uVar12 = *puVar2;
            if (uVar12 == uVar18) {
              *puVar2 = uVar4;
              LOAcquire();
              uVar4 = *puVar2;
              *puVar2 = uVar4 | 0x8000000000000000;
              LORelease();
              FUN_10002e2dc(uVar4,&DAT_10cda2418,puVar9);
            }
            _os_unfair_recursive_lock_unlock(&DAT_10cda2478);
          }
          else {
            uVar12 = puVar9[1];
            if (uVar12 == uVar18) {
              puVar9[1] = uVar4;
            }
          }
        } while (uVar12 != uVar18);
      }
      *(undefined **)(param_1 + 0x198) = puVar10;
      uVar17 = 1;
    }
  }
  local_f0 = 0;
  FUN_101d374e4(param_2,&local_f0);
  FUN_101d378d0(lVar13,plVar14,local_f0,&DAT_10d438960,0);
  uVar4 = 0;
  if ((*(byte *)((long)*(ulong **)(param_1 + 0x1a0) + 0xb) & 0x80) != 0) {
    uVar4 = **(ulong **)(param_1 + 0x1a0);
  }
  if ((local_f0 == 0) || (lVar11 = local_f0, uVar4 != 0)) {
    if ((local_f0 == 0) && (uVar4 != 0)) {
      lVar11 = 0;
      goto LAB_101d36a2c;
    }
    if ((uVar4 != 0) && (FUN_100de4d84(uVar4,local_f0,0), lVar11 = local_f0, (uVar4 & 1) == 0))
    goto LAB_101d36a2c;
  }
  else {
LAB_101d36a2c:
    puVar10 = &DAT_10cda2418;
    FUN_100024dac(&DAT_10cda2418,0,lVar11,&DAT_10cd62d90);
    puVar9 = *(undefined8 **)(param_1 + 0x1a0);
    if (puVar9 != &DAT_10cda23e8) {
      do {
        uVar18 = puVar9[1];
        uVar4 = uVar18 - 0x100000000;
        if ((uVar4 & 0x7fffffff01ffffff) == 0) {
          FUN_100394d68(&DAT_10cda2478);
          puVar2 = puVar9 + 1;
          uVar12 = *puVar2;
          if (uVar12 == uVar18) {
            *puVar2 = uVar4;
            LOAcquire();
            uVar4 = *puVar2;
            *puVar2 = uVar4 | 0x8000000000000000;
            LORelease();
            FUN_10002e2dc(uVar4,&DAT_10cda2418,puVar9);
          }
          _os_unfair_recursive_lock_unlock(&DAT_10cda2478);
        }
        else {
          uVar12 = puVar9[1];
          if (uVar12 == uVar18) {
            puVar9[1] = uVar4;
          }
        }
      } while (uVar12 != uVar18);
    }
    *(undefined **)(param_1 + 0x1a0) = puVar10;
    local_fc = 1;
  }
  lVar11 = DAT_10c046d90;
  if (DAT_10c046d90 == 0) {
    lVar11 = DAT_10cd06b88;
    if (DAT_10cd06b88 == 0) {
      DAT_10c046d90 = 0;
    }
    else {
      FUN_100cc4f74();
      DAT_10c046d90 = lVar11;
      if (lVar11 != 0) goto LAB_101d367cc;
    }
    FUN_104781d30();
  }
LAB_101d367cc:
  puVar9 = (undefined8 *)(lVar11 + 0x10);
  (**(code **)*puVar9)();
  FUN_101d376e4();
  local_f8 = 0;
  aplStack_90[0] = &local_f8;
  local_98 = FUN_10564080c;
  local_a0 = FUN_105640864;
  if ((local_c0 == (long *)0x0) ||
     ((**(code **)(*local_c0 + 0xa0))(local_c0,&local_a0,puVar9[2]), local_98 != (code *)0x0)) {
    (*local_98)(aplStack_90,0,0);
  }
  FUN_101d378d0(lVar13,plVar14,local_f8,&DAT_10d4389a0,0);
  uVar4 = 0;
  if ((*(byte *)((long)*(ulong **)(param_1 + 0x1a8) + 0xb) & 0x80) != 0) {
    uVar4 = **(ulong **)(param_1 + 0x1a8);
  }
  if ((local_f8 == 0) || (lVar13 = local_f8, uVar4 != 0)) {
    if ((local_f8 == 0) && (uVar4 != 0)) {
      lVar13 = 0;
      goto LAB_101d36984;
    }
    if ((uVar4 != 0) && (FUN_100de4d84(uVar4,local_f8,0), lVar13 = local_f8, (uVar4 & 1) == 0))
    goto LAB_101d36984;
  }
  else {
LAB_101d36984:
    puVar10 = &DAT_10cda2418;
    FUN_100024dac(&DAT_10cda2418,0,lVar13,&DAT_10cd62d90);
    puVar9 = *(undefined8 **)(param_1 + 0x1a8);
    if (puVar9 != &DAT_10cda23e8) {
      do {
        uVar18 = puVar9[1];
        uVar4 = uVar18 - 0x100000000;
        if ((uVar4 & 0x7fffffff01ffffff) == 0) {
          FUN_100394d68(&DAT_10cda2478);
          puVar2 = puVar9 + 1;
          uVar12 = *puVar2;
          if (uVar12 == uVar18) {
            *puVar2 = uVar4;
            LOAcquire();
            uVar4 = *puVar2;
            *puVar2 = uVar4 | 0x8000000000000000;
            LORelease();
            FUN_10002e2dc(uVar4,&DAT_10cda2418,puVar9);
          }
          _os_unfair_recursive_lock_unlock(&DAT_10cda2478);
        }
        else {
          uVar12 = puVar9[1];
          if (uVar12 == uVar18) {
            puVar9[1] = uVar4;
          }
        }
      } while (uVar12 != uVar18);
    }
    *(undefined **)(param_1 + 0x1a8) = puVar10;
    uVar17 = 1;
  }
  if ((local_fc | param_3) == 1) {
    local_a4 = 0;
    FUN_10123c1e8(&local_a0,&local_a4,0);
    FUN_10171bf18(0x1e,&local_a0);
    FUN_10123c86c(&local_a0);
    local_a4 = 0;
    FUN_10123c1e8(&local_a0,&local_a4,0);
    FUN_10171bf18(0x1d,&local_a0);
    FUN_10123c86c(&local_a0);
  }
  if ((uVar17 | param_3) == 1) {
    local_a4 = 0;
    FUN_10123c1e8(&local_a0,&local_a4,0);
    FUN_10171bf18(0x1c,&local_a0);
    FUN_10123c86c(&local_a0);
    local_a4 = 0;
    FUN_10123c1e8(&local_a0,&local_a4,0);
    FUN_10171bf18(0x1b,&local_a0);
    FUN_10123c86c(&local_a0);
  }
LAB_101d36948:
  if (*(long *)PTR_10b4d40c8 == local_70) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

 (GhidraScript)  
INFO 0x101d375f4 disassemble=true body=240 instructions=60
DIAG completed=true cancelled=false hf=true
