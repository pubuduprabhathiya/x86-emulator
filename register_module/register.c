#include "register.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
// #include "../modrm_map/modrm_map.h"

const char *r8[8] = {"AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH"};
const char *r16[8] = {"AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI"};
const char *r32[8] = {"EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"};
const char *mm[8] = {"MM0", "MM1", "MM2", "MM3", "MM4", "MM5", "MM6", "MM7"};
const char *xmm[8] = {"XMM0", "XMM1", "XMM2", "XMM3",
                      "XMM4", "XMM5", "XMM6", "XMM7"};

const char *eip[1] = {"EIP"};
const char *eflags[1] = {"EFLAGS"};

const char *cs[1] = {"CS"};
const char *ss[1] = {"SS"};
const char *ds[1] = {"DS"};
const char *es[1] = {"ES"};
const char *fs[1] = {"FS"};
const char *gs[1] = {"GS"};

Register_8 **registers_r8 = NULL;
Register_16 **registers_r16 = NULL;
Register_32 **registers_r32 = NULL;
Register_64 **registers_mm = NULL;
Register_128 **registers_xmm = NULL;

Register_32 **registers_eip = NULL;
Register_32 **registers_eflags = NULL;

Register_16 **registers_cs = NULL;
Register_16 **registers_ss = NULL;
Register_16 **registers_ds = NULL;
Register_16 **registers_es = NULL;
Register_16 **registers_fs = NULL;
Register_16 **registers_gs = NULL;

void init_registers() {
  registers_r8 = (Register_8 **)malloc(sizeof(Register_8 *) * 8);
  registers_r16 = (Register_16 **)malloc(sizeof(Register_16 *) * 8);
  registers_r32 = (Register_32 **)malloc(sizeof(Register_32 *) * 8);
  registers_mm = (Register_64 **)malloc(sizeof(Register_64 *) * 8);
  registers_xmm = (Register_128 **)malloc(sizeof(Register_128 *) * 8);

  registers_eip = (Register_32 **)malloc(sizeof(Register_32 *));
  registers_eflags = (Register_32 **)malloc(sizeof(Register_32 *));

  registers_cs = (Register_16 **)malloc(sizeof(Register_16 *));
  registers_ss = (Register_16 **)malloc(sizeof(Register_16 *));
  registers_ds = (Register_16 **)malloc(sizeof(Register_16 *));
  registers_es = (Register_16 **)malloc(sizeof(Register_16 *));
  registers_fs = (Register_16 **)malloc(sizeof(Register_16 *));
  registers_gs = (Register_16 **)malloc(sizeof(Register_16 *));

  for (int i = 0; i < 8; i++) {
    registers_r8[i] = (Register_8 *)malloc(sizeof(Register_8));
  }
  for (int i = 0; i < 8; i++) {
    registers_r16[i] = (Register_16 *)malloc(sizeof(Register_16));
  }
  for (int i = 0; i < 8; i++) {
    registers_r32[i] = (Register_32 *)malloc(sizeof(Register_32));
  }
  for (int i = 0; i < 8; i++) {
    registers_mm[i] = (Register_64 *)malloc(sizeof(Register_64));
  }
  for (int i = 0; i < 8; i++) {
    registers_xmm[i] = (Register_128 *)malloc(sizeof(Register_128));
  }

  for (int i = 0; i < 1; i++) {
    registers_eip[i] = (Register_32 *)malloc(sizeof(Register_32));
  }
  for (int i = 0; i < 1; i++) {
    registers_eflags[i] = (Register_32 *)malloc(sizeof(Register_32));
  }

  for (int i = 0; i < 1; i++) {
    registers_cs[i] = (Register_16 *)malloc(sizeof(Register_16));
  }
  for (int i = 0; i < 1; i++) {
    registers_ss[i] = (Register_16 *)malloc(sizeof(Register_16));
  }
  for (int i = 0; i < 1; i++) {
    registers_ds[i] = (Register_16 *)malloc(sizeof(Register_16));
  }
  for (int i = 0; i < 1; i++) {
    registers_es[i] = (Register_16 *)malloc(sizeof(Register_16));
  }
  for (int i = 0; i < 1; i++) {
    registers_fs[i] = (Register_16 *)malloc(sizeof(Register_16));
  }
  for (int i = 0; i < 1; i++) {
    registers_gs[i] = (Register_16 *)malloc(sizeof(Register_16));
  }


  printf("Register Init success. \n");
}

char *get_reg_name(enum reg_type type, int index) {
  if (type == reg_8) {
    return (char *)r8[index];
  } else if (type == reg_16) {
    return (char *)r16[index];
  } else if (type == reg_32) {
    return (char *)r32[index];
  } else if (type == reg_mm) {
    return (char *)mm[index];
  } else {
    return (char *)xmm[index];
  }
}

void *get_register(enum reg_type type, char *reg_name) {
  if (type == reg_8) {
    int i = 0;
    for (i; i < 8; i++) {
      char *str1 = r8[i];
      char *str2 = reg_name;

      if (strcmp(str1, str2) == 0) {
        return registers_r8[i];
      }
    }
  }
  if (type == reg_16) {
    int i = 0;
    for (i; i < 8; i++) {
      char *str1 = r16[i];
      char *str2 = reg_name;

      if (strcmp(str1, str2) == 0) {
        return registers_r16[i];
      }
    }
  }
  if (type == reg_32) {
    int i = 0;
    for (i; i < 8; i++) {
      char *str1 = r32[i];
      char *str2 = reg_name;

      if (strcmp(str1, str2) == 0) {
        return registers_r32[i];
      }
    }
  }
  if (type == reg_mm) {
    int i = 0;
    for (i; i < 8; i++) {
      char *str1 = mm[i];
      char *str2 = reg_name;

      if (strcmp(str1, str2) == 0) {
        return registers_mm[i];
      }
    }
  }
  if (type == reg_xmm) {
    int i = 0;
    for (i; i < 8; i++) {
      char *str1 = xmm[i];
      char *str2 = reg_name;

      if (strcmp(str1, str2) == 0) {
        return registers_xmm[i];
      }
    }
  }

  if (type == reg_eip) {
    int i = 0;
    for (i; i < 8; i++) {
      char *str1 = eip[i];
      char *str2 = reg_name;

      if (strcmp(str1, str2) == 0) {
        return registers_eip[i];
      }
    }
  }
  if (type == reg_eflags) {
    int i = 0;
    for (i; i < 8; i++) {
      char *str1 = eflags[i];
      char *str2 = reg_name;

      if (strcmp(str1, str2) == 0) {
        return registers_eflags[i];
      }
    };
  }
  if (type == reg_cs) {
    int i = 0;
    for (i; i < 8; i++) {
      char *str1 = cs[i];
      char *str2 = reg_name;

      if (strcmp(str1, str2) == 0) {
        return registers_cs[i];
      }
    }
  }
  if (type == reg_ss) {
    int i = 0;
    for (i; i < 8; i++) {
      char *str1 = ss[i];
      char *str2 = reg_name;

      if (strcmp(str1, str2) == 0) {
        return registers_ss[i];
      }
    }
  }
  if (type == reg_ds) {
    int i = 0;
    for (i; i < 8; i++) {
      char *str1 = ds[i];
      char *str2 = reg_name;

      if (strcmp(str1, str2) == 0) {
        return registers_ds[i];
      }
    }
  }
  if (type == reg_es) {
    int i = 0;
    for (i; i < 8; i++) {
      char *str1 = es[i];
      char *str2 = reg_name;

      if (strcmp(str1, str2) == 0) {
        return registers_es[i];
      }
    }
  }
  if (type == reg_fs) {
    int i = 0;
    for (i; i < 8; i++) {
      char *str1 = fs[i];
      char *str2 = reg_name;

      if (strcmp(str1, str2) == 0) {
        return registers_fs[i];
      }
    }
  }
  if (type == reg_gs) {
    int i = 0;
    for (i; i < 8; i++) {
      char *str1 = gs[i];
      char *str2 = reg_name;

      if (strcmp(str1, str2) == 0) {
        return registers_gs[i];
      }
    }
  }
}

// int main(){

//     init_registers();
//     enum reg_type type_of_reg = reg_32;
//     char * reg_name = "EAX";
//     uint32_t a = 0x11111111;

//     Register_32 *reg_to_write =
//     (Register_32*)get_register(type_of_reg,reg_name); reg_to_write->value =
//     &a;

//     Register_32 *reg_to_read =
//     (Register_32*)get_register(type_of_reg,reg_name); int b =
//     *(reg_to_read->value);

//     printf("read value from EAX : %x\n",b);

//     return 0;
// }