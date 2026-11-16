// queryInventory:withCallback: @ 103fa89ac (172 bytes)
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x20 bytes */

void InAppPurchaseController::queryInventory_withCallback_
               (ID param_1,SEL param_2,ID param_3,undefined4 *param_4)

{
  undefined *self;
  ID IVar1;
  
  self = (undefined *)0x0;
  _objc_alloc();
  IVar1 = objc_stub::thunk_FUN_10a7f3820((ID)(undefined *)0x0,param_3);
  IVar1 = objc_stub::thunk_FUN_10a7f30e0((ID)self,IVar1);
  objc_stub::thunk_FUN_10a7f37e0(param_1,param_4);
  objc_stub::thunk_FUN_10a7f3660(IVar1,param_1);
  objc_stub::thunk_FUN_10a7f3880(IVar1);
  return;
}

 (GhidraScript)  
real 5.51
user 4.33
sys 1.84
