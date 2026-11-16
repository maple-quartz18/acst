// findcall —— 扫描 Mach-O __TEXT 中所有 BL 到指定地址的调用点
// 用法: findcall <macho> <target_vm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
static uint8_t *gD; static size_t gN;
static uint64_t gVm, gOff, gSz;
static uint32_t rd32(size_t o){return *(uint32_t*)(gD+o);} 
static uint64_t rd64(size_t o){return *(uint64_t*)(gD+o);} 
int main(int argc,char**argv){
    if(argc<3){fprintf(stderr,"用法: %s <macho> <target_vm>\n",argv[0]);return 2;}
    FILE*f=fopen(argv[1],"rb"); if(!f){perror("open");return 1;}
    fseek(f,0,SEEK_END); gN=ftell(f); fseek(f,0,SEEK_SET);
    gD=malloc(gN); if(fread(gD,1,gN,f)!=gN) return 1; fclose(f);
    if(rd32(0)!=0xfeedfacf){fprintf(stderr,"不是 64 位 Mach-O\n");return 1;}
    uint32_t ncmds=rd32(16); size_t off=32;
    for(uint32_t i=0;i<ncmds;i++){
        uint32_t cmd=rd32(off), sz=rd32(off+4);
        if(cmd==0x19){
            char nm[17]; memcpy(nm,gD+off+8,16); nm[16]=0;
            if(!strcmp(nm,"__TEXT")){gVm=rd64(off+24);gOff=rd64(off+40);gSz=rd64(off+48);}
        }
        off+=sz;
    }
    if(!gSz){fprintf(stderr,"找不到 __TEXT\n");return 1;}
    uint64_t target=strtoull(argv[2],NULL,0);
    int n=0;
    for(size_t q=gOff;q+4<=gOff+gSz;q+=4){
        uint32_t w=rd32(q);
        if((w & 0xFC000000u)!=0x94000000u) continue;
        int32_t imm=(int32_t)(w & 0x3FFFFFFu);
        if(imm & (1<<25)) imm |= ~((1<<26)-1);
        uint64_t pc=gVm+(q-gOff);
        uint64_t tgt=pc+((int64_t)imm<<2);
        if(tgt==target){printf("%#llx\n",(unsigned long long)pc);n++;}
    }
    fprintf(stderr,"total %d\n",n);
    return 0;
}
