// FUN_1002fbe5c @ 1002fbe5c (300 bytes)
void FUN_1002fbe5c(long param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  long lVar3;
  undefined4 *puVar4;
  
  lVar3 = *(long *)PTR_10b4d40c8;
  (**(code **)(**(long **)(param_1 + 0x30) + 0x98))(*(long **)(param_1 + 0x30),0x1004fa9957fbaa33);
  (**(code **)(**(long **)(param_1 + 0x30) + 0x88))(*(long **)(param_1 + 0x30),3);
  (**(code **)(**(long **)(param_1 + 0x30) + 0x80))
            (*(long **)(param_1 + 0x30),*(undefined1 *)(param_1 + 0xd0));
  (**(code **)(**(long **)(param_1 + 0x30) + 0x90))
            (*(long **)(param_1 + 0x30),
             *(uint *)(param_1 + 200) | (*(byte *)(param_1 + 0xd1) & 8) << 0x1c);
  if ((*(byte *)(param_1 + 0xd1) >> 3 & 1) != 0) goto LAB_1002fbf24;
  while (*(long *)PTR_10b4d40c8 != lVar3) {
    func_0x0001080011d0();
LAB_1002fbf24:
    (**(code **)(**(long **)(param_1 + 0x30) + 0x90))
              (*(long **)(param_1 + 0x30),*(uint *)(param_1 + 0x40) & 0x3fffffff);
    uVar2 = *(int *)(param_1 + 0x40) << 3;
    if (uVar2 != 0) {
      puVar4 = *(undefined4 **)(param_1 + 0x38);
      puVar1 = (undefined4 *)((long)puVar4 + (ulong)uVar2);
      do {
        (**(code **)(**(long **)(param_1 + 0x30) + 0x90))(*(long **)(param_1 + 0x30),*puVar4);
        (**(code **)(**(long **)(param_1 + 0x30) + 0x90))(*(long **)(param_1 + 0x30),puVar4[1]);
        puVar4 = puVar4 + 2;
      } while (puVar4 != puVar1);
    }
  }
  return;
}

 (GhidraScript)  
INFO 0x1002d6984 disassemble=true body=2764 instructions=691
DIAG completed=true cancelled=false hf=true
