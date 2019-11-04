#include <iostream>
#include <cstddef> // pour size_t (c++11)
#include <cstdlib> // pour rand

////////////////////////////////////////
//
// Fonction qui applique 'divmod' entre
// deux vecteurs.
//
void divmod_vec(size_t n,
                int dividendes[], int diviseurs[],
                int quotients[], int restes[]
                )
 {
    //https://www.csie.ntu.edu.tw/~acpang/course/asm_2004/slides/chapt_07_PartIISolve.pdf
     asm(".intel_syntax noprefix;"
         "mov rcx, %[counter];"
         "mov r8, %[dividendes];"
         "mov r9, %[diviseurs];"
         "mov r10, %[quotients];"
         "mov r11, %[restes];"

         "cmp %[counter], 0;"
         "jz .end%=;"

         "dec rcx;"

         ".loop%=:"
         "mov eax, [r8 + rcx * 4];"
         "mov ebx, [r9 + rcx * 4];"
         "CDQ;"
         "IDIV ebx;"
         "mov DWORD PTR [r10 + rcx * 4], eax;"
         "mov DWORD PTR [r11 + rcx * 4], edx;"
         "cmp rcx, 0;"
         "je .end%=;"
         "dec rcx;"
         "jmp .loop%=;"

         ".end%=:"
         ".att_syntax;"
     :
     : [counter]"R"(n), [dividendes]"R"(dividendes), [diviseurs]"R"(diviseurs),
        [quotients]"R"(quotients), [restes]"R"(restes)
     : "rcx", "r8", "r9", "r10", "r11");
 }

////////////////////////////////////////
int main()
 {
  const size_t n=20; // whatever.

  int dividendes[n],
   diviseurs[n],
   quotients[n],
   restes[n];

  // on remplit!
  for (size_t i=0;i<n;i++)
   {
    dividendes[i]=rand() % 100;
    diviseurs[i]=1+(rand() % 20); // pourquoi pas.
   }

  divmod_vec(n, dividendes, diviseurs, quotients, restes);

  // on affiche!
  for (size_t i=0;i<n;i++)
   std::cout
    << dividendes[i]
    << "\tdiv\t"
    << diviseurs[i]
    << "\t=\t"
    << quotients[i]
    << " reste "
    << restes[i]
    << std::endl;



  return 0;
 }
