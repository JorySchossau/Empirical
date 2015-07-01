#include <iostream>

#include "../../tools/assert.h"
#include "../../tools/command_line.h"
#include "../../tools/macros.h"

#define EMP_DECORATE(X) [X]

int main(int argc, char* argv[])
{
  std::vector<std::string> args = emp::cl::args_to_strings(argc, argv);
  const bool verbose = emp::cl::use_arg(args, "-v");

  // Test getting a specific argument.
  emp_assert(EMP_GET_ARG_5(11,12,13,14,15,16,17) == 15);

  // Test counting number of arguments.
  emp_assert( EMP_COUNT_ARGS(a, b, c) == 3 );

  // Make sure EMP_STRINGIFY can process macros before running
  emp_assert( std::string(EMP_STRINGIFY(EMP_MERGE(ab, c, de, f))) == "abcdef" );
  emp_assert( std::string(EMP_STRINGIFY("abcdef")) == "\"abcdef\"" );

  // Make sure we can assemble arbitrary macros
  emp_assert( std::string(EMP_STRINGIFY( EMP_ASSEMBLE_MACRO( EMP_GET_ARG_, 2, x, y, z ))) == "y" );

  if (verbose) {
    std::cout << EMP_STRINGIFY( EMP_ASSEMBLE_MACRO( EMP_GET_ARG_, 2, x, y, z ) ) << std::endl;
    std::cout << EMP_STRINGIFY(EMP_MERGE(a, bc, d, e, f, g, h)) << std::endl;
  }

  // Make sure we can wrap each argument in a macro.
  emp_assert( std::string(EMP_STRINGIFY( EMP_WRAP_EACH(EMP_DECORATE, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) )) == "[a] [b] [c] [d] [e] [f] [g] [h] [i] [j] [k] [l] [m] [n] [o] [p]" );
  emp_assert( EMP_STRINGIFY( EMP_LAYOUT(EMP_DECORATE, +, a, b, c, d, e, f, g, h) ) == "[a] + [b] + [c] + [d] + [e] + [f] + [g] + [h]" );
  emp_assert( EMP_STRINGIFY( EMP_WRAP_ARGS(EMP_DECORATE, a, b, c, d, e, f, g, h) ) == "[a], [b], [c], [d], [e], [f], [g], [h]" );

  if (verbose) {
    std::cout << EMP_STRINGIFY( EMP_WRAP_EACH(EMP_DECORATE, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) ) << std::endl;
    std::cout << EMP_STRINGIFY( EMP_LAYOUT(EMP_DECORATE, +, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z) ) << std::endl;
    std::cout << EMP_STRINGIFY( EMP_WRAP_ARGS(EMP_DECORATE, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9) ) << std::endl;
  }

  emp_assert( std::string(EMP_STRINGIFY( EMP_REVERSE_ARGS(a,b,c, d) )) == "d, c, b, a" );
  emp_assert( std::string(EMP_STRINGIFY( EMP_TYPES_TO_ARGS(int, char, bool, std::string) ))
              == "int arg1, char arg2, bool arg3, std::string arg4" );

  if (verbose) {
    std::cout << "Reverse a,b,c = '" << EMP_STRINGIFY( EMP_REVERSE_ARGS(a,b,c) )
              << "'" << std::endl;
    std::cout << EMP_STRINGIFY( EMP_TYPES_TO_ARGS(int, char, bool, std::string) ) << std::endl;
  }

  std::cout << "All tests passed." << std::endl;
}

