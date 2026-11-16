// FUN_101d378d0 @ 101d378d0 (3424 bytes)
void FUN_101d378d0(undefined8 param_1,undefined8 param_2,long *param_3,long param_4,int param_5)

{
  long *plVar1;
  ulong uVar2;
  bool bVar3;
  int iVar4;
  char *pcVar5;
  long *plVar6;
  long **pplVar7;
  void *pvVar8;
  void *pvVar9;
  undefined8 *puVar10;
  int extraout_w8;
  int extraout_w8_00;
  int extraout_w8_01;
  int extraout_w8_02;
  int extraout_w8_03;
  int extraout_w8_04;
  int extraout_w8_05;
  int extraout_w8_06;
  int extraout_w8_07;
  int extraout_w8_08;
  int extraout_w8_09;
  int extraout_w8_10;
  int extraout_w8_11;
  int extraout_w8_12;
  int extraout_w8_13;
  int extraout_w8_14;
  int extraout_w8_15;
  int extraout_w8_16;
  long lVar11;
  undefined8 *puVar12;
  long *plVar13;
  ulong local_188;
  long **local_180;
  long *local_178;
  undefined8 local_170;
  long **pplStack_168;
  long local_160;
  undefined8 uStack_158;
  long *local_150;
  long lStack_148;
  void *local_140;
  undefined1 *local_138;
  long local_130;
  undefined8 uStack_128;
  long **local_120;
  undefined8 local_118;
  long lStack_110;
  void *local_108;
  undefined8 uStack_100;
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined4 local_e8;
  undefined1 local_e4;
  char *local_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  long *plStack_c8;
  long *local_c0;
  undefined8 uStack_b8;
  long local_b0;
  void *pvStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined4 local_88;
  undefined8 local_80;
  long local_78;
  
  local_78 = *(long *)PTR_10b4d40c8;
  if (param_3 == (long *)0x0) {
    if (*(long *)PTR_10b4d40c8 == local_78) {
      FUN_101d39424(param_1,param_4);
      return;
    }
    goto LAB_101d38250;
  }
  puVar10 = &DAT_10ca87f10;
  if (*(char *)(param_4 + 0x29) != '\0') {
    FUN_101d38870(&local_120,param_4 + 0x30,param_4 + 8);
    pcVar5 = "0x%08llX";
    FUN_10053d824("0x%08llX");
    local_e0 = (char *)0x0;
    FUN_10043a8e0(&local_e0,pcVar5);
    FUN_1007d6808(param_1,&local_120,&local_e0);
    pcVar5 = local_e0;
    if (local_e0 != (char *)0x0) {
      lVar11 = *(long *)(DAT_10cd98750 + ((ulong)local_e0 >> 0x1f & 0xffffffff) * 8);
      if ((lVar11 == 0) || (*(char *)(lVar11 + ((ulong)local_e0 >> 0x10 & 0x7fff) * 2) == -1)) {
        puVar12 = puVar10;
        (*DAT_10ca87f10)(DAT_10cd98f5c);
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_10;
        if (extraout_w8_10 == 0xff) {
          FUN_100002000(&DAT_10cd6d5e1,0x100,
                        "Invalid pointer not allocated by our allocators or already freed: 0x%p (allocatorId:%d)"
                       );
          *(undefined4 *)*puVar12 = 0;
          iVar4 = 0xff;
        }
      }
      else {
        puVar12 = puVar10;
        (*DAT_10ca87f10)();
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8;
      }
      plVar13 = (long *)(&DAT_10cd98758)[(byte)iVar4];
      plVar6 = plVar13;
      (**(code **)(*plVar13 + 0x20))(plVar13,pcVar5,0,0);
      if ((int)plVar6 != 0) {
        LOAcquire();
        plVar13[4] = plVar13[4] - ((ulong)plVar6 & 0xffffffff);
        LORelease();
      }
      (**(code **)(*plVar13 + 0x90))(plVar13,pcVar5);
    }
    pplVar7 = local_120;
    if (local_120 != (long **)0x0) {
      lVar11 = *(long *)(DAT_10cd98750 + ((ulong)local_120 >> 0x1f & 0xffffffff) * 8);
      if ((lVar11 == 0) || (*(char *)(lVar11 + ((ulong)local_120 >> 0x10 & 0x7fff) * 2) == -1)) {
        puVar12 = puVar10;
        (*DAT_10ca87f10)(DAT_10cd98f5c);
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_11;
        if (extraout_w8_11 == 0xff) {
          FUN_100002000(&DAT_10cd6d5e1,0x100,
                        "Invalid pointer not allocated by our allocators or already freed: 0x%p (allocatorId:%d)"
                       );
          *(undefined4 *)*puVar12 = 0;
          iVar4 = 0xff;
        }
      }
      else {
        puVar12 = puVar10;
        (*DAT_10ca87f10)();
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_00;
      }
      plVar13 = (long *)(&DAT_10cd98758)[(byte)iVar4];
      plVar6 = plVar13;
      (**(code **)(*plVar13 + 0x20))(plVar13,pplVar7,0,0);
      if ((int)plVar6 != 0) {
        LOAcquire();
        plVar13[4] = plVar13[4] - ((ulong)plVar6 & 0xffffffff);
        LORelease();
      }
      (**(code **)(*plVar13 + 0x90))(plVar13,pplVar7);
    }
  }
  if (*(char *)(param_4 + 0x2b) != '\0') {
    FUN_101d38870(&local_e0,param_4 + 0x30,param_4 + 0x18);
    FUN_100a14aac(param_1,&local_e0,(int)param_3[0xb],0);
    pcVar5 = local_e0;
    if (local_e0 != (char *)0x0) {
      lVar11 = *(long *)(DAT_10cd98750 + ((ulong)local_e0 >> 0x1f & 0xffffffff) * 8);
      if ((lVar11 == 0) || (*(char *)(lVar11 + ((ulong)local_e0 >> 0x10 & 0x7fff) * 2) == -1)) {
        puVar12 = puVar10;
        (*DAT_10ca87f10)(DAT_10cd98f5c);
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_16;
        if (extraout_w8_16 == 0xff) {
          FUN_100002000(&DAT_10cd6d5e1,0x100,
                        "Invalid pointer not allocated by our allocators or already freed: 0x%p (allocatorId:%d)"
                       );
          *(undefined4 *)*puVar12 = 0;
          iVar4 = 0xff;
        }
      }
      else {
        puVar12 = puVar10;
        (*DAT_10ca87f10)();
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_01;
      }
      plVar13 = (long *)(&DAT_10cd98758)[(byte)iVar4];
      plVar6 = plVar13;
      (**(code **)(*plVar13 + 0x20))(plVar13,pcVar5,0,0);
      if ((int)plVar6 != 0) {
        LOAcquire();
        plVar13[4] = plVar13[4] - ((ulong)plVar6 & 0xffffffff);
        LORelease();
      }
      (**(code **)(*plVar13 + 0x90))(plVar13,pcVar5);
    }
  }
  if (*(char *)(param_4 + 0x28) != '\0') {
    FUN_101d38870(&local_120,param_4 + 0x30,param_4);
    plVar6 = param_3;
    FUN_1003fa338();
    pplVar7 = &local_150;
    local_150 = plVar6;
    FUN_101d38630(pplVar7);
    local_e0 = (char *)0x0;
    FUN_10043a8e0(&local_e0,pplVar7);
    FUN_1007d6808(param_1,&local_120,&local_e0);
    pcVar5 = local_e0;
    if (local_e0 != (char *)0x0) {
      lVar11 = *(long *)(DAT_10cd98750 + ((ulong)local_e0 >> 0x1f & 0xffffffff) * 8);
      if ((lVar11 == 0) || (*(char *)(lVar11 + ((ulong)local_e0 >> 0x10 & 0x7fff) * 2) == -1)) {
        puVar12 = puVar10;
        (*DAT_10ca87f10)(DAT_10cd98f5c);
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_12;
        if (extraout_w8_12 == 0xff) {
          FUN_100002000(&DAT_10cd6d5e1,0x100,
                        "Invalid pointer not allocated by our allocators or already freed: 0x%p (allocatorId:%d)"
                       );
          *(undefined4 *)*puVar12 = 0;
          iVar4 = 0xff;
        }
      }
      else {
        puVar12 = puVar10;
        (*DAT_10ca87f10)();
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_02;
      }
      plVar13 = (long *)(&DAT_10cd98758)[(byte)iVar4];
      plVar6 = plVar13;
      (**(code **)(*plVar13 + 0x20))(plVar13,pcVar5,0,0);
      if ((int)plVar6 != 0) {
        LOAcquire();
        plVar13[4] = plVar13[4] - ((ulong)plVar6 & 0xffffffff);
        LORelease();
      }
      (**(code **)(*plVar13 + 0x90))(plVar13,pcVar5);
    }
    pplVar7 = local_120;
    if (local_120 != (long **)0x0) {
      lVar11 = *(long *)(DAT_10cd98750 + ((ulong)local_120 >> 0x1f & 0xffffffff) * 8);
      if ((lVar11 == 0) || (*(char *)(lVar11 + ((ulong)local_120 >> 0x10 & 0x7fff) * 2) == -1)) {
        puVar12 = puVar10;
        (*DAT_10ca87f10)(DAT_10cd98f5c);
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_13;
        if (extraout_w8_13 == 0xff) {
          FUN_100002000(&DAT_10cd6d5e1,0x100,
                        "Invalid pointer not allocated by our allocators or already freed: 0x%p (allocatorId:%d)"
                       );
          *(undefined4 *)*puVar12 = 0;
          iVar4 = 0xff;
        }
      }
      else {
        puVar12 = puVar10;
        (*DAT_10ca87f10)();
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_03;
      }
      plVar13 = (long *)(&DAT_10cd98758)[(byte)iVar4];
      plVar6 = plVar13;
      (**(code **)(*plVar13 + 0x20))(plVar13,pplVar7,0,0);
      if ((int)plVar6 != 0) {
        LOAcquire();
        plVar13[4] = plVar13[4] - ((ulong)plVar6 & 0xffffffff);
        LORelease();
      }
      (**(code **)(*plVar13 + 0x90))(plVar13,pplVar7);
    }
  }
  if (*(char *)(param_4 + 0x2a) != '\0') {
    FUN_1004b10bc(&local_180,1,&local_120,&local_e0);
    local_170 = 0;
    uStack_158 = 0;
    local_160 = 0;
    local_180[1] = (long *)0x0;
    local_180[2] = (long *)0x0;
    *local_180 = (long *)0x0;
    *(undefined2 *)((long)local_180 + 0x16) = 3;
    pplStack_168 = local_180;
    FUN_101d39080(&local_180,param_2,param_3,1);
    pvStack_a8 = (void *)0x0;
    local_b0 = 0;
    uStack_98 = 0;
    uStack_a0 = 0;
    plStack_c8 = (long *)0x0;
    local_d0 = 0;
    uStack_b8 = 0;
    local_c0 = (long *)0x0;
    uStack_d8 = 0;
    local_e0 = (char *)0x0;
    local_90 = 0x400;
    local_88 = 0;
    local_80 = 0;
    plVar13 = (long *)&DAT_00000028;
    __Znwm();
    plVar6 = local_178;
    *plVar13 = 0;
    plVar13[1] = 0x10000;
    plVar13[3] = 0;
    plVar13[4] = 0;
    plVar13[2] = 0;
    local_120 = local_180;
    plStack_c8 = plVar13;
    local_c0 = plVar13;
    if (local_178 == (long *)0x0) {
      FUN_100270f98(&local_e0,pplStack_168,plVar13,0);
    }
    else {
      plVar1 = local_178 + 1;
      LOAcquire();
      lVar11 = *plVar1;
      *(int *)plVar1 = (int)lVar11 + 1;
      LORelease();
      FUN_100270f98((int)lVar11,&local_e0,pplStack_168,plVar13,0);
      LOAcquire();
      lVar11 = *plVar1;
      *(int *)plVar1 = (int)lVar11 + -1;
      LORelease();
      if ((int)lVar11 == 1) {
        (**(code **)(*plVar6 + 0x10))(plVar6);
        LOAcquire();
        iVar4 = *(int *)((long)plVar6 + 0xc);
        *(int *)((long)plVar6 + 0xc) = iVar4 + -1;
        LORelease();
        if (iVar4 == 1) {
          (**(code **)(*plVar6 + 0x18))(plVar6);
        }
      }
    }
    lStack_148 = 0;
    local_150 = (long *)0x0;
    local_138 = (undefined1 *)0x0;
    local_140 = (void *)0x0;
    local_130 = 0;
    uStack_128 = 0x100;
    local_120 = &local_150;
    lStack_110 = 0;
    local_118 = 0;
    uStack_100 = 0;
    local_108 = (void *)0x0;
    local_f8 = 0;
    uStack_f0 = 0x200;
    local_e8 = 0x144;
    local_e4 = 0;
    FUN_100e14a68(&local_e0,&local_120);
    if (local_130 - (long)local_138 < 1) {
      FUN_100e1629c(&local_150,1);
    }
    *local_138 = 0;
    local_188 = 0;
    FUN_10043a8e0(&local_188,local_140);
    _free(local_108);
    if (lStack_110 != 0) {
      __ZdlPv();
    }
    _free(local_140);
    if (lStack_148 != 0) {
      __ZdlPv();
    }
    plVar6 = local_c0;
    if (local_c0 != (long *)0x0) {
      pvVar8 = (void *)*local_c0;
      bVar3 = pvVar8 == (void *)local_c0[2];
      if ((pvVar8 != (void *)0x0) && (pvVar9 = pvVar8, !bVar3)) {
        do {
          pvVar8 = *(void **)((long)pvVar9 + 0x10);
          _free(pvVar9);
          *plVar6 = (long)pvVar8;
          bVar3 = pvVar8 == (void *)plVar6[2];
          pvVar9 = pvVar8;
        } while (pvVar8 != (void *)0x0 && pvVar8 != (void *)plVar6[2]);
      }
      if (pvVar8 != (void *)0x0 && bVar3) {
        *(undefined8 *)((long)pvVar8 + 8) = 0;
      }
      if (plVar6[4] != 0) {
        __ZdlPv();
      }
      __ZdlPv(plVar6);
    }
    _free(pvStack_a8);
    if (local_b0 != 0) {
      __ZdlPv();
    }
    FUN_101d38870(&local_e0,param_4 + 0x30,param_4 + 0x10);
    FUN_1007d6808(param_1,&local_e0,&local_188);
    pcVar5 = local_e0;
    if (local_e0 != (char *)0x0) {
      lVar11 = *(long *)(DAT_10cd98750 + ((ulong)local_e0 >> 0x1f & 0xffffffff) * 8);
      if ((lVar11 == 0) || (*(char *)(lVar11 + ((ulong)local_e0 >> 0x10 & 0x7fff) * 2) == -1)) {
        puVar12 = puVar10;
        (*DAT_10ca87f10)(DAT_10cd98f5c);
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_08;
        if (extraout_w8_08 == 0xff) {
          FUN_100002000(&DAT_10cd6d5e1,0x100,
                        "Invalid pointer not allocated by our allocators or already freed: 0x%p (allocatorId:%d)"
                       );
          *(undefined4 *)*puVar12 = 0;
          iVar4 = 0xff;
        }
      }
      else {
        puVar12 = puVar10;
        (*DAT_10ca87f10)();
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_04;
      }
      plVar13 = (long *)(&DAT_10cd98758)[(byte)iVar4];
      plVar6 = plVar13;
      (**(code **)(*plVar13 + 0x20))(plVar13,pcVar5,0,0);
      if ((int)plVar6 != 0) {
        LOAcquire();
        plVar13[4] = plVar13[4] - ((ulong)plVar6 & 0xffffffff);
        LORelease();
      }
      (**(code **)(*plVar13 + 0x90))(plVar13,pcVar5);
    }
    uVar2 = local_188;
    if (local_188 != 0) {
      lVar11 = *(long *)(DAT_10cd98750 + (local_188 >> 0x1f & 0xffffffff) * 8);
      if ((lVar11 == 0) || (*(char *)(lVar11 + (local_188 >> 0x10 & 0x7fff) * 2) == -1)) {
        puVar12 = puVar10;
        (*DAT_10ca87f10)(DAT_10cd98f5c);
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_09;
        if (extraout_w8_09 == 0xff) {
          FUN_100002000(&DAT_10cd6d5e1,0x100,
                        "Invalid pointer not allocated by our allocators or already freed: 0x%p (allocatorId:%d)"
                       );
          *(undefined4 *)*puVar12 = 0;
          iVar4 = 0xff;
        }
      }
      else {
        puVar12 = puVar10;
        (*DAT_10ca87f10)();
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_05;
      }
      plVar13 = (long *)(&DAT_10cd98758)[(byte)iVar4];
      plVar6 = plVar13;
      (**(code **)(*plVar13 + 0x20))(plVar13,uVar2,0,0);
      if ((int)plVar6 != 0) {
        LOAcquire();
        plVar13[4] = plVar13[4] - ((ulong)plVar6 & 0xffffffff);
        LORelease();
      }
      (**(code **)(*plVar13 + 0x90))(plVar13,uVar2);
    }
    lVar11 = local_160;
    if (local_160 != 0) {
      plVar6 = (long *)&DAT_10cd98748;
      FUN_10006ff2c(&DAT_10cd98748,local_160);
      plVar13 = plVar6;
      (**(code **)(*plVar6 + 0x20))();
      if ((int)plVar13 != 0) {
        LOAcquire();
        plVar6[4] = plVar6[4] - ((ulong)plVar13 & 0xffffffff);
        LORelease();
      }
      (**(code **)(*plVar6 + 0x90))(plVar6,lVar11);
      local_160 = 0;
    }
    if (local_178 != (long *)0x0) {
      LOAcquire();
      iVar4 = (int)local_178[1];
      *(int *)(local_178 + 1) = iVar4 + -1;
      LORelease();
      if (iVar4 == 1) {
        (**(code **)(*local_178 + 0x10))(local_178);
        LOAcquire();
        iVar4 = *(int *)((long)local_178 + 0xc);
        *(int *)((long)local_178 + 0xc) = iVar4 + -1;
        LORelease();
        if (iVar4 == 1) {
          (**(code **)(*local_178 + 0x18))(local_178);
        }
      }
    }
  }
  if (*(char *)(param_4 + 0x2c) != '\0') {
    local_e0 = (char *)0x0;
    if (param_5 == 0) {
      plVar6 = param_3;
      FUN_10108fe5c(param_3,&DAT_10cf01b60);
      if (plVar6 == (long *)0x0) {
        puVar12 = (undefined8 *)param_3[7];
      }
      else {
        (**(code **)(*plVar6 + 0x98))();
        puVar12 = (undefined8 *)*plVar6;
      }
      pcVar5 = (char *)0x0;
      if (*(int *)(puVar12 + 1) < 0) {
        pcVar5 = (char *)*puVar12;
      }
      FUN_101d38ef0();
      if (local_e0 != pcVar5) goto LAB_101d38088;
    }
    else {
      pcVar5 = "Hidden";
LAB_101d38088:
      FUN_10043a8e0(&local_e0,pcVar5);
    }
    FUN_101d38870(&local_120,param_4 + 0x30,param_4 + 0x20);
    FUN_1007d6808(param_1,&local_120,&local_e0);
    pplVar7 = local_120;
    if (local_120 != (long **)0x0) {
      lVar11 = *(long *)(DAT_10cd98750 + ((ulong)local_120 >> 0x1f & 0xffffffff) * 8);
      if ((lVar11 == 0) || (*(char *)(lVar11 + ((ulong)local_120 >> 0x10 & 0x7fff) * 2) == -1)) {
        puVar12 = puVar10;
        (*DAT_10ca87f10)(DAT_10cd98f5c);
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_14;
        if (extraout_w8_14 == 0xff) {
          FUN_100002000(&DAT_10cd6d5e1,0x100,
                        "Invalid pointer not allocated by our allocators or already freed: 0x%p (allocatorId:%d)"
                       );
          *(undefined4 *)*puVar12 = 0;
          iVar4 = 0xff;
        }
      }
      else {
        puVar12 = puVar10;
        (*DAT_10ca87f10)();
        *puVar12 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_06;
      }
      plVar13 = (long *)(&DAT_10cd98758)[(byte)iVar4];
      plVar6 = plVar13;
      (**(code **)(*plVar13 + 0x20))(plVar13,pplVar7,0,0);
      if ((int)plVar6 != 0) {
        LOAcquire();
        plVar13[4] = plVar13[4] - ((ulong)plVar6 & 0xffffffff);
        LORelease();
      }
      (**(code **)(*plVar13 + 0x90))(plVar13,pplVar7);
    }
    pcVar5 = local_e0;
    if (local_e0 != (char *)0x0) {
      lVar11 = *(long *)(DAT_10cd98750 + ((ulong)local_e0 >> 0x1f & 0xffffffff) * 8);
      if ((lVar11 == 0) || (*(char *)(lVar11 + ((ulong)local_e0 >> 0x10 & 0x7fff) * 2) == -1)) {
        (*DAT_10ca87f10)(DAT_10cd98f5c);
        *puVar10 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_15;
        if (extraout_w8_15 == 0xff) {
          FUN_100002000(&DAT_10cd6d5e1,0x100,
                        "Invalid pointer not allocated by our allocators or already freed: 0x%p (allocatorId:%d)"
                       );
          *(undefined4 *)*puVar10 = 0;
          iVar4 = 0xff;
        }
      }
      else {
        (*DAT_10ca87f10)();
        *puVar10 = &DAT_ffffdead00000008;
        iVar4 = extraout_w8_07;
      }
      plVar13 = (long *)(&DAT_10cd98758)[(byte)iVar4];
      plVar6 = plVar13;
      (**(code **)(*plVar13 + 0x20))(plVar13,pcVar5,0,0);
      if ((int)plVar6 != 0) {
        LOAcquire();
        plVar13[4] = plVar13[4] - ((ulong)plVar6 & 0xffffffff);
        LORelease();
      }
      (**(code **)(*plVar13 + 0x90))(plVar13,pcVar5);
    }
  }
  if (*(long *)PTR_10b4d40c8 == local_78) {
    return;
  }
LAB_101d38250:
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

 (GhidraScript)  
INFO 0x101d37374 disassemble=true body=368 instructions=92
DIAG completed=true cancelled=false hf=true
