#include <stdlib.h>
#include "cpuid.h"
#include "m512-check.h"
#include "avx512f-os-support.h"

static void avx512vl_test (void);

static void __attribute__ ((noinline)) do_test (void)
{
  avx512vl_test ();
}

int
main ()
{
  unsigned int eax, ebx, ecx, edx;

  if (!__get_cpuid (1, &eax, &ebx, &ecx, &edx))
    return 0;

  /* Run avx512vl test only if host has avx512vl support.  */
  if (ecx & bit_OSXSAVE)
    {
      if (__get_cpuid_max (0, NULL) < 7)
	return 0;

      __cpuid_count (7, 0, eax, ebx, ecx, edx);

      if ((ebx & bit_AVX512VL) && avx512f_os_support ())
	{
	  do_test ();
#ifdef DEBUG
	  printf ("PASSED\n");
#endif
	  return 0;
	}
#ifdef DEBUG
      printf ("SKIPPED\n");
#endif
    }
#ifdef DEBUG
  else
    printf ("SKIPPED\n");
#endif

  return 0;
}
