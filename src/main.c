#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

// The option given by the args
extern char* optarg;
// The index of the args
extern int optind;

//: Flags {{{
typedef unsigned char bool_opt;
bool_opt verbose_enabled = 0; // Verbose output dissassembly
bool_opt show_output     = 0; // Show the output to console instead to file
bool_opt use_stdin       = 0; // use stdin stream to read a file instead of give name
// }}}


int main(int argc, char** argv)
{
  int opt;
  //: Parsing arguments {{{
  while ((opt = getopt(argc, argv, "shvo")) != -1){
    switch (opt){
      case 'h': // Show help info
        return 0;
      case 's':
        use_stdin = 1;
        break;
      case 'v':
        verbose_enabled = 1;
        break;
      case 'o':
        show_output = 1;
        break;
      case '?':
      default:
        fprintf(stderr, "Unknown option inserted.");
        return 1;
    }
  }
  //}}} End of parsing args

}
