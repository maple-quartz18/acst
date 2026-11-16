// updateInventory: @ 10778f7d0 (680 bytes)
/* Function Stack Size: 0x18 bytes */

void StoreKitManager::updateInventory_(ID param_1,SEL param_2,ID param_3)

{
  ulong uVar1;
  ID IVar2;
  ID IVar3;
  long *plVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  uint uVar7;
  undefined8 extraout_x8;
  undefined8 extraout_x8_00;
  long lVar8;
  ulong extraout_x9;
  ulong extraout_x9_00;
  long *plVar9;
  ulong uVar10;
  ulong local_478;
  undefined *local_470;
  undefined7 uStack_468;
  undefined1 local_461;
  uint uStack_460;
  undefined3 uStack_45c;
  undefined1 local_5b;
  long local_58;
  
  local_58 = *(long *)PTR_10b4d40c8;
  if (param_3 == 0) goto LAB_10778f9c0;
  IVar2 = _objc_msgSend(param_1,"RestoredPurchase");
  _objc_sync_enter();
  IVar3 = _objc_msgSend(param_1,"RestoredPurchase");
  IVar3 = _objc_msgSend(IVar3,"indexOfObject:",param_3);
  uVar7 = DAT_10d567384;
  if (IVar3 == 0x7fffffffffffffff) {
    if (DAT_10c5d38a0 != '\0') {
      local_470 = &DAT_10cd07558;
      uStack_468 = 0;
      local_461 = 0;
      uStack_460 = 0;
      uStack_45c = 0;
      local_5b = 0;
      if (DAT_10cd07575 == 0) {
        if (DAT_10cd07570 < 3) goto LAB_10778f874;
      }
      else if ((DAT_10cd07575 >> 2 & 1) != 0) {
LAB_10778f874:
        if (DAT_10d567384 < 2) {
          if (DAT_10d567384 == 0) {
            DAT_10d567384 = 0;
          }
          else {
            while (uVar7 = DAT_10d567384, DAT_10d567384 == 1) {
              _pthread_yield_np();
            }
          }
        }
        uStack_460 = uVar7;
        IVar3 = _objc_msgSend(param_3,"UTF8String");
        local_478 = 0;
        FUN_10043a8e0(&local_478,IVar3);
        FUN_10332c90c(&local_470,2,"","","",0x93,"0x21358D4D",&local_478);
        uVar1 = local_478;
        if (local_478 != 0) {
          lVar8 = *(long *)(DAT_10cd98750 + (local_478 >> 0x1f & 0xffffffff) * 8);
          if ((lVar8 == 0) || (*(char *)(lVar8 + (local_478 >> 0x10 & 0x7fff) * 2) == -1)) {
            puVar5 = &DAT_10ca87f10;
            (*DAT_10ca87f10)(&DAT_ffffdead00000008);
            *puVar5 = extraout_x8_00;
            uVar10 = extraout_x9_00;
            if ((int)extraout_x9_00 == 0xff) {
              FUN_107f8534c();
              puVar6 = puVar5;
              FUN_107f85398();
              uVar10 = 0xff;
              FUN_100002000(puVar5,(ulong)puVar6 & 0xffffffff,
                            "Invalid pointer not allocated by our allocators or already freed: 0x%p (allocatorId:%d)"
                           );
              FUN_107f853e0();
            }
          }
          else {
            puVar5 = &DAT_10ca87f10;
            (*DAT_10ca87f10)();
            *puVar5 = extraout_x8;
            uVar10 = extraout_x9;
          }
          plVar9 = (long *)(&DAT_10cd98758)[uVar10 & 0xff];
          plVar4 = plVar9;
          (**(code **)(*plVar9 + 0x20))(plVar9,uVar1,0,0);
          if ((int)plVar4 != 0) {
            LOAcquire();
            plVar9[4] = plVar9[4] - ((ulong)plVar4 & 0xffffffff);
            LORelease();
          }
          (**(code **)(*plVar9 + 0x90))(plVar9,uVar1);
        }
      }
    }
    IVar3 = _objc_msgSend(param_1,"RestoredPurchase");
    _objc_msgSend(IVar3,"addObject:",param_3);
  }
  _objc_sync_exit(IVar2);
LAB_10778f9c0:
  if (*(long *)PTR_10b4d40c8 == local_58) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}

 (GhidraScript)  
INFO 0x103fab070 disassemble=true body=348 instructions=87
DIAG completed=true cancelled=false hf=true
