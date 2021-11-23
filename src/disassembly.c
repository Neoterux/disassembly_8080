#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disassembly.h"


int disassembly(byte* stream, char* out){

  printf("The given byte stream is: ");
  size_t length = strlen((char*) stream);
  char *opname = calloc(15, sizeof(char));
  for (int i = 0; i < length; i++) {
    int bytes = decode(stream, opname) - 1;
    printf("%s", opname);
    while (bytes--){
      printf("%02x", *(++stream));
    }
    printf("\n");
    stream++;
    printf("%x -> %c", stream[i], stream[i]);
    if (i < length) printf(", ");
  }
  printf("\n");

  return 0;
}

int decode(byte* codebuffer, char* opname)
{
  char *opn = "invalid";
  int opbytes = 1;
  switch(*codebuffer)
  {
    case 0x0:
    case 0x08:
    case 0x10:
    case 0x18:
    case 0x28:
    case 0x38:
    case 0xcb:
    case 0xd9:
    case 0xdd:
    case 0xed:
    case 0xfd:
      opn = "nop";
      break;
    case 0x01:
      opn = "lxi  b,#$"; opbytes = 3;
      break;
    case 0x02:
      opn = "stax b";
      break;
    case 0x03:
      opn = "inx  b";
      break;
    case 0x04:
      opn = "inr  b";
      break;
    case 0x05:
      opn = "dcr  b";
      break;
    case 0x06:
      opn = "mvi  b,#$"; opbytes = 2;
      break;
    case 0x07:
      opn ="rlc";
      break;
    case 0x09:
      opn = "dad";
      break;
    case 0x0a:
      opn = "ldax";
      break;
    case 0x0b:
      opn = "dcx";
      break;
    case 0x0c:
      opn = "inr";
      break;
    case 0x0d:
      opn = "dcr";
      break;
    case 0x0e:
      opn = "mvi  c,#$"; opbytes = 2; // Write 1 byte to register c
      break;
    case 0x0f:
      opn = "rrc"; // 1 bit shift to right?
      break;
    case 0x11:
      opn = "lxi  d,#$"; opbytes = 3; //Write 2 bytes to register d,e
      break;
    case 0x12:
      opn = "stax d";
      break;
    case 0x13:
      opn = "inx  d";
      break;
    case 0x14:
      opn = "inr  d";
      break;
    case 0x15:
      opn="dcr  d";
      break;
    case 0x16:
      opn="mvi  d,#$"; opbytes = 2;
      break;
    case 0x17:
      opn="ral";
      break;
//    case 0x18:
//     opn="--";
//    break;
    case 0x19:
      opn="dad  d";
      break;
    case 0x1a:
      opn="ldax d";
      break;
    case 0x1b:
      opn="dcx  d"; // decrement register e
      break;
    case 0x1c:
      opn="inr  e";
      break;
    case 0x1d:
      opn="dcr  e";
      break;
    case 0x1e:
      opn="mvi  e,#$"; opbytes = 2;
      break;
    case 0x1f:
      opn="rar";
      break;
    case 0x20:
      opn="rim";
      break;
    case 0x21:
      opn="lxi  h,#$"; opbytes = 3;
      break;
  case 0x22:
    opn="shld $"; opbytes = 3;
    break;
  case 0x23:
    opn="inx  h";
    break;
  case 0x24:
    opn="inr  h"; // increment h register
    break;
  case 0x25:
    opn="dcr  h"; // decrement h register
    break;
  case 0x26:
    opn="mvi  h,#$"; opbytes = 2; // assign the byte 2 to h register?
    break;
  case 0x27:
    opn="daa"; // special [NEED INFO]
    break;
//  case 0x28:
//    opn = "--";
//    break;
  case 0x29:
    opn="dad  h"; // add assign the HL register with the HI
    break;
  case 0x2a:
    opn="lhld $"; opbytes = 3; // copy the inserted address to register L(add) and H(add+1)
    break;
  case 0x2b:
    opn="dcx  h";
    break;
  case 0x2c:
    opn="inr  l"; // increment register L
    break;
  case 0x2d:
    opn="dcr  l"; // decrement register L
    break;
  case 0x2e:
    opn="mvi  L,#$"; opbytes = 2; // assign byte 2 to register L
    break;
  case 0x2f:
    opn="cma"; // register A <- !A [INVESTIGATE] ~Maybe invert bits?
    break;
  case 0x30:
    opn="sim"; // Special [INVESTIGATE]
    break;
  case 0x31:
    opn="lxi  sp,#$"; opbytes = 3;
    break;
  case 0x32:
    opn="sta  $"; opbytes = 3; // storage value of register A into (addr)
    break;
  case 0x33:
    opn="inx  sp"; // increment SP register
    break;
  case 0x34:
    opn="inr  m"; // ???? (HL) <- (HL) +1 ~ maybe address stored in HL increment?
    break;
  case 0x35:
    opn="dcr  m"; // ???? (HL) <- (HL) -1 ~ maybe address stored in HL decrement?
    break;
  case 0x36:
    opn="mvi  m,#$"; opbytes = 2; // move byte 2 to register HL
    break;
  case 0x37:
    opn="stc"; // set CY = 1
    break;
//  case 0x38:
//    opn="--";
//    break;
  case 0x39:
    opn="dad  sp"; 
    break;
  case 0x3a:
    opn="lda  $"; opbytes = 3; // Assign address to register A
    break;
  case 0x3b:
    opn="dcx  sp"; //decrement register SP
    break;
  case 0x3c:
    opn="inr  a"; // increment register A
    break;
  case 0x3d:
    opn="dcr  a"; // decremente register A
    break;
  case 0x3e:
    opn="mvi  a,#$"; opbytes = 2; // move byte 2 to register A
    break;
  case 0x3f:
    opn="cmc"; // CY = !CY ~ maybe invert bytes?
    break;
  case 0x40:
    opn="mov  b,b";
    break;
  case 0x41:
    opn="mov  b,c";
    break;
  case 0x42:
    opn="mov  b,d";
    break;
  case 0x43:
    opn="mov  b,e";
    break;
  case 0x44:
    opn="mov  b,h";
    break;
  case 0x45:
    opn="mov  b,l";
    break;
  case 0x46:
    opn="mov  b,m";
    break;
  case 0x47:
    opn="mov  b,a";
    break;
  case 0x48:
    opn="mov  c,b";
    break;
  case 0x49:
    opn="mov  c,c";
    break;
  case 0x4a:
    opn="mov  c,d";
    break;
  case 0x4b:
    opn="mov  c,e";
    break;
  case 0x4c:
    opn="mov  c,h";
    break;
  case 0x4d:
    opn="mov  c,l";
    break;
  case 0x4e:
    opn="mov  c,m";
    break;
  case 0x4f:
    opn="mov  c,a";
    break;
  case 0x50:
    opn="mov  d,b";
    break;
  case 0x51:
    opn="mov  d,c";
    break;
  case 0x52:
    opn="mov  d,d";
    break;
  case 0x53:
    opn="mov  d,e";
    break;
  case 0x54:
    opn="mov  d,h";
    break;
  case 0x55:
    opn="mov  d,l";
    break;
  case 0x56:
    opn="mov  d,m";
    break;
  case 0x57:
    opn="mov  d,a";
    break;
  case 0x58:
    opn="mov  e,b";
    break;
  case 0x59:
    opn="mov  e,c";
    break;
  case 0x5a:
    opn="mov  e,d";
    break;
  case 0x5b:
    opn="mov  e,e";
    break;
  case 0x5c:
    opn="mov  e,h";
    break;
  case 0x5d:
    opn="mov  e,l";
    break;
  case 0x5e:
    opn="mov  e,m";
    break;
  case 0x5f:
    opn="mov  e,a";
    break;
  case 0x60:
    opn="mov  h,b";
    break;
  case 0x61:
    opn="mov  h,c";
    break;
  case 0x62:
    opn="mov  h,d";
    break;
  case 0x63:
    opn="mov  h,e";
    break;
  case 0x64:
    opn="mov  h,h";
    break;
  case 0x65:
    opn="mov  h,l";
    break;
  case 0x66:
    opn="mov  h,m";
    break;
  case 0x67:
    opn="mov  h,a";
    break;
  case 0x68:
    opn="mov  l,b";
    break;
  case 0x69:
    opn="mov  l,c";
    break;
  case 0x6a:
    opn="mov  l,d";
    break;
  case 0x6b:
    opn="mov  l,e";
    break;
  case 0x6c:
    opn="mov  l,h";
    break;
  case 0x6d:
    opn="mov  l,l";
    break;
  case 0x6e:
    opn="mov  l,m";
    break;
  case 0x6f:
    opn="mov  l,a";
    break;
  case 0x70:
    opn="mov  m,b";
    break;
  case 0x71:
    opn="mov  m,c";
    break;
  case 0x72:
    opn="mov  m,d";
    break;
  case 0x73:
    opn="mov  m,e";
    break;
  case 0x74:
    opn="mov  m,h";
    break;
  case 0x75:
    opn="mov  m,l";
    break;
  case 0x76:
    opn="hlt";
    break;
  case 0x77:
    opn="mov  m,a";
    break;
  case 0x78:
    opn="mov  a,b";
    break;
  case 0x79:
    opn="mov  a,c";
    break;
  case 0x7a:
    opn="mov  a,d";
    break;
  case 0x7b:
    opn="mov  a,e";
    break;
  case 0x7c:
    opn="mov  a,h";
    break;
  case 0x7d:
    opn="mov  a,l";
    break;
  case 0x7e:
    opn="mov  a,m";
    break;
  case 0x7f:
    opn="mov  a,a";
    break;
  case 0x80:
    opn="add  b"; // a <- a+b  and the same with below
    break;
  case 0x81:
    opn="add  c";
    break;
  case 0x82:
    opn="add  d";
    break;
  case 0x83:
    opn="add  e";
    break;
  case 0x84:
    opn="add  h";
    break;
  case 0x85:
    opn="add  l";
    break;
  case 0x86:
    opn="add  m";
    break;
  case 0x87:
    opn="add  a";
    break;
  case 0x88:
    opn="adc  b"; // A <- A+B+CY and the same below
    break;
  case 0x89:
    opn="adc  c";
    break;
  case 0x8a:
    opn="adc  d";
    break;
  case 0x8b:
    opn="adc  e";
    break;
  case 0x8c:
    opn="adc  h";
    break;
  case 0x8d:
    opn="adc  l";
    break;
  case 0x8e:
    opn="adc  m";
    break;
  case 0x8f:
    opn="adc  a";
    break;
  case 0x90:
    opn="sub  b"; // A<- A-B and the same bellow
    break;
  case 0x91:
    opn="sub  c";
    break;
  case 0x92:
    opn="sub  d";
    break;
  case 0x93:
    opn="sub  e";
    break;
  case 0x94:
    opn="sub  h";
    break;
  case 0x95:
    opn="sub  l";
    break;
  case 0x96:
    opn="sub  m";
    break;
  case 0x97:
    opn="sub  a";
    break;
  case 0x98:
    opn="sbb  b"; // A <- A-B -CY and the same bellow
    break;
  case 0x99:
    opn="sbb  c";
    break;
  case 0x9a:
    opn="sbb  d";
    break;
  case 0x9b:
    opn="sbb  e";
    break;
  case 0x9c:
    opn="sbb  h"; 
    break;
  case 0x9d:
    opn="sbb  l";
    break;
  case 0x9e:
    opn="sbb  m";
    break;
  case 0x9f:
    opn="sbb  a";
    break;
  case 0xa0:
    opn="ana  b"; // A<- A & B
    break;
  case 0xa1:
    opn="ana  c";
    break;
  case 0xa2:
    opn="ana  d";
    break;
  case 0xa3:
    opn="ana  e";
    break;
  case 0xa4:
    opn="ana  h";
    break;
  case 0xa5:
    opn="ana  l";
    break;
  case 0xa6:
    opn="ana  m";
    break;
  case 0xa7:
    opn="ana  a";
    break;
  case 0xa8:
    opn="xra  b"; // A <-A ^ B and the same bellow
    break;
  case 0xa9:
    opn="xra  c";
    break;
  case 0xaa:
    opn="xra  d";
    break;
  case 0xab:
    opn="xra  e";
    break;
  case 0xac:
    opn="xra  h";
    break;
  case 0xad:
    opn="xra  l";
    break;
  case 0xae:
    opn="xra  m";
    break;
  case 0xaf:
    opn="xra  a";
    break;
  case 0xb0:
    opn="ora  b"; // A <- A | B and the same bellow
    break;
  case 0xb1:
    opn="ora  c";
    break;
  case 0xb2:
    opn="ora  d";
    break;
  case 0xb3:
    opn="ora  e";
    break;
  case 0xb4:
    opn="ora  h";
    break;
  case 0xb5:
    opn="ora  l";
    break;
  case 0xb6:
    opn="ora  m";
    break;
  case 0xb7:
    opn="ora  a";
    break;
  case 0xb8:
    opn="cmp  b"; // A - B and the same bellow
    break;
  case 0xb9:
    opn="cmp  c";
    break;
  case 0xba:
    opn="cmp  d";
    break;
  case 0xbb:
    opn="cmp  e";
    break;
  case 0xbc:
    opn="cmp  h";
    break;
  case 0xbd:
    opn="cmp  l";
    break;
  case 0xbe:
    opn="cmp  m";
    break;
  case 0xbf:
    opn="cmp  a";
    break;
  case 0xc0:
    opn="rnz"; // if NZ, RET
    break;
  case 0xc1:
    opn="pop  b";
    break;
  case 0xc2:
    opn="jnz  $"; opbytes = 3;
    break;
  case 0xc3:
    opn="jmp  $"; opbytes = 3;
    break;
  case 0xc4:
    opn="cnz  $"; opbytes = 3;
    break;
  case 0xc5:
    opn="push b";
    break;
  case 0xc6:
    opn="adi  #$"; opbytes = 2;
    break;
  case 0xc7:
    opn="rst  0"; // call $0
    break;
  case 0xc8:
    opn="rz";
    break;
  case 0xc9:
    opn="ret";
    break;
  case 0xca:
    opn="jz   $"; opbytes = 3; // if Z, PC <- adr
    break;
//  case 0xcb:
//    opn="--";
//    break;
  case 0xcc:
    opn="cz   $"; opbytes = 3;
    break;
  case 0xcd:
    opn="call $"; opbytes = 3;
    break;
  case 0xce:
    opn="aci  #$"; opbytes = 2;
    break;
  case 0xcf:
    opn="rst  1"; // call $8
    break;
  case 0xd0:
    opn="rnc";
    break;
  case 0xd1:
    opn="pop  d";
    break;
  case 0xd2:
    opn="jnc  $"; opbytes = 3; // if NCY, PC <- adr
    break;
  case 0xd3:
    opn="out  #$"; opbytes = 2;
    break;
  case 0xd4:
    opn="cnc  $"; opbytes = 3;
    break;
  case 0xd5:
    opn="push d";
    break;
  case 0xd6:
    opn="sui  #$"; opbytes = 2;
    break;
  case 0xd7:
    opn="rst  2";
    break;
  case 0xd8:
    opn="rc";
    break;
//  case 0xd9:
//    opn="--";
//    break;
  case 0xda:
    opn="jc   $"; opbytes = 3;
    break;
  case 0xdb:
    opn="in   #$"; opbytes = 2;
    break;
  case 0xdc:
    opn="cc   $"; opbytes = 3;
    break;
//  case 0xdd:
//    opn="--";
//    break;
  case 0xde:
    opn="sbi  #$"; opbytes = 2;
    break;
  case 0xdf:
    opn="rst  3"; // call $18
    break;
  case 0xe0:
    opn="rpo";
    break;
  case 0xe1:
    opn="pop  h";
    break;
  case 0xe2:
    opn="jpo  $"; opbytes = 3;
    break;
  case 0xe3:
    opn="xthl";
    break;
  case 0xe4:
    opn="cpo  $"; opbytes = 3;
    break;
  case 0xe5:
    opn="push h";
    break;
  case 0xe6:
    opn="ani  #$"; opbytes = 2;
    break;
  case 0xe7:
    opn="rst  4"; // call $20
    break;
  case 0xe8:
    opn="rpe";
    break;
  case 0xe9:
    opn="pchl";
    break;
  case 0xea:
    opn="jpe  $"; opbytes = 3;
    break;
  case 0xeb:
    opn="xchg";
    break;
  case 0xec:
    opn="cpe  $"; opbytes = 3;
    break;
//  case 0xed:
//    opn="--";
//    break;
  case 0xee:
    opn="xri  #$"; opbytes = 2;
    break;
  case 0xef:
    opn="rst  5"; //call $28
    break;
  case 0xf0:
    opn="rp";
    break;
  case 0xf1:
    opn="pop  psw";
    break;
  case 0xf2:
    opn="jp   $"; opbytes = 3;
    break;
  case 0xf3:
    opn="di";
    break;
  case 0xf4:
    opn="cp   $"; opbytes = 3;
    break;
  case 0xf5:
    opn="push psw";
    break;
  case 0xf6:
    opn="ori  #$"; opbytes = 2;
    break;
  case 0xf7:
    opn="rst  6"; // call $30
    break;
  case 0xf8:
    opn="rm";
    break;
  case 0xf9:
    opn="sphl";
    break;
  case 0xfa:
    opn="jm   $"; opbytes = 3;
    break;
  case 0xfb:
    opn="ei";
    break;
  case 0xfc:
    opn="cm   $"; opbytes = 3;
    break;
//  case 0xfd:
//    opn="--";
//    break;
  case 0xfe:
    opn="cpi  #$"; opbytes = 2;
    break;
  case 0xff:
    opn="rst  7"; // call $38
    break;
    default:
    opn = "errdec";
//    opbytes = -1;
   }
  strcpy(opname, opn);
  return opbytes;
}

// int interprete(byte* stream);
