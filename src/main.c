#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#include <string.h>
#include "disassembly.h"

#define BUFFER_SIZE 256

// The option given by the args
extern char* optarg;
// The index of the args
extern int optind;

//: Flags {{{
typedef unsigned char bool_opt;
bool_opt verbose_enabled = 0; // Verbose output dissassembly
bool_opt output_file     = 0; // Show the output to console instead to file
bool_opt use_stdin       = 0; // use stdin stream to read a file instead of give name
//: }}}

byte buffer[BUFFER_SIZE];

// Help string
void print_help(void);
void reverse_str(char*);

int main(int argc, char** argv)
{
  int opt;
  char* outfile = NULL;
  //: Parsing arguments {{{
  while ((opt = getopt(argc, argv, "shvo:")) != -1){
    switch (opt){
      case 'h': // Show help info
        print_help();
        return 0;
      case 's':
        use_stdin = 1;
        break;
      case 'v':
        verbose_enabled = 1;
        break;
      case 'o':
        output_file = 1;
        outfile = optarg;
        break;
      case '?':
      default:
        fprintf(stderr, "Unknown option inserted.\n");
        // Should show help
        print_help();
        return 1;
    }
  }
  //: }}} End of parsing args
  if (!use_stdin && optind == argc){
    fprintf(stderr, "No file provided.\n");
    return -1;
  }
  char* filename = argv[optind++];

  FILE *afile = (use_stdin)? stdin : fopen(filename, "rb");
  FILE *ofile = (output_file)? fopen(outfile, "w") : stdout;

  if (afile == NULL){
    fprintf(stderr, "File not found.\n");
    return -2;
  }

  //: Decoding needed Variables {{{
  size_t bytes_read = 0;
  uint64_t line = 0;                          // The line/pc 
  char *opname = malloc(sizeof(char) * 15);   // The opname/instruction name string container
  size_t bytes_needed = 0;                    // The quantity of extra bytes needed for an instruction
  byte *tmp;                                  // Auxiliar pointer to travel through buffer
  byte nbytes_stack[3] = {0x00, 0x00, 0x00};  // The bytes stack for instruction needs
  //: }}}
  
  while((bytes_read = fread(&buffer[0], sizeof(byte), BUFFER_SIZE, afile)) > 0){
    tmp = buffer;
    char mem[7] = {};
    byte reg_bytes[3] = {0, 0, 0};
    byte *bytes_helper;
    char *help;
    int bytes_mem = 0;

    while(bytes_read > 0){
      if (bytes_needed == 0){
        // Reset the bytes needed stack
        bytes_mem = 0;
        bytes_helper = &reg_bytes[0];
        // Decode the new instruction
        bytes_needed = decode(tmp++, opname);

        if (verbose_enabled)
          fprintf(ofile, "%08lx:   ", ++line);
        // print the instruction to stdout
        fprintf(ofile, "%s",opname);
        // Now decrease byte counters
        bytes_read--; 
        bytes_needed--;
      }

      //: Obtain or continue the bytes needed {{{
      while(bytes_needed > 0 && bytes_read > 0){
        *(bytes_helper++) = *(tmp++); // Add the byte to stack;
        bytes_mem++;                  // Increment bytes needed from stack
        bytes_needed--;               // Decrease bytes needed for decode
        bytes_read--;                 // Decrease bytes readed in total from buffer
      }
      //: }}}

      if(bytes_needed == 0){
        bytes_helper--;
        for (; bytes_mem > 0; bytes_mem--)
          fprintf(ofile, "%02x", *bytes_helper--);

        memset(&reg_bytes[0], 0, sizeof(reg_bytes));
        fprintf(ofile, "\n");
      }
      
    }// End of reading buffer

  } // End of reading file
  fclose(afile);
  fclose(ofile);

  // Free the op name reserved memory;
  free(opname);

  return 0;
}

inline void reverse_str(char *str){
  size_t len = strlen(str);

  for(int i = 0; i < len; i++){
    char tmp = str[i];
    *(str+i) = str[len-i-1];
    *(str+len-i-1) = tmp;
  }
}

//: Help Function {{{
void print_help(void) 
{//TODO: Change executable to receive it
  printf("This is a small disassembly for 8080 processor instructions\n");
  printf("Usage\n");
  printf("-h\t\tShow this message\n");
  printf("-s\t\tUse stdin instead of a specific file\n");
  printf("-o\t\tOutput file.\n");
  printf("Example:\n");
  printf("./d8080 -o rom.asm rom.h\n");
}
//: }}}
