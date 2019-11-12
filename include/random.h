#ifndef RANDOM

#include <time.h>
#include <stdlib.h>

#define RANDOM_INIT srandom(time(0));
#define RANDOM (static_cast<double>(random())/RAND_MAX)

#if 0

#define UL unsigned long
#define znew  ((z=36969*(z&65535)+(z>>16))<<16)
#define wnew  ((w=18000*(w&65535)+(w>>16))&65535)
#define MWC   (znew+wnew)
#define SHR3  (jsr=(jsr=(jsr=jsr^(jsr<<17))^(jsr>>13))^(jsr<<5))
#define CONG  (jcong=69069*jcong+1234567)
#define KISS  ((MWC^CONG)+SHR3)
#define LFIB4 (t[c]=t[c]+t[c+58]+t[c+119]+t[++c+178])
#define SWB   (t[c+237]=(x=t[c+15])-(y=t[++c]+(x<y)))
#define UNI   (KISS*2.328306e-10)
#define VNI   ((long) KISS)*4.656613e-10
/*  Global static variables: */
 static UL z=362436069, w=521288629, jsr=123456789, jcong=380116160;
 static UL t[256];
 static UL x=0,y=0; static unsigned char c=0;

/* Random seeds must be used to reset z,w,jsr,jcong and
the table t[256]  Here is an example procedure, using KISS: */

 void settable(UL i1,UL i2,UL i3,UL i4)
 { int i; z=i1;w=i2,jsr=i3; jcong=i4;
 for(i=0;i<256;i++)  t[i]=KISS;        }

/*  End of C code;  Only comments follow. Stick the above
   17 lines in your simulation programs, initialize the table,
   and have a variety of promising RNG's at your disposal.  */

/* You may want use more complicated names for the
   above simple 1-letter variable names: z,w,x,y,t,c,
   to avoid clashing with favorites in your code.    */

/* Any one of KISS, MWC, LFIB4, SWB, SHR3, or CONG
   can be used in an expression to provide a random
   32-bit integer, and UNI in an expression will
   provide a random uniform in (01), or VNI in (-1,1).
   For example, for int i, float v; i=(MWC>>24); will
   provide a random byte, while v=4.+3.*UNI; will
   provide a uniform v in the interval 4. to 7.
   For the super cautious, (KISS+SWB) in an expression
   would provide a random 32-bit integer from
   a sequence with period > 2^7700, and would only
   add some 300 nanoseconds to the computing
   time for that expression.                         */

/* The KISS generator, (Keep It Simple Stupid), is
   designed to combine the two multiply-with-carry
   generators in MWC with the 3-shift register SHR3
   and the congruential generator CONG, using
   addition and exclusive-or. Period about 2^123. It
   is one of my favorite generators.   */

/* The  MWC generator concatenates two 16-bit
  multiply-with-carry generators, x(n)=36969x(n-1)+carry,
  y(n)=18000y(n-1)+carry  mod 2^16, has  period  about
  2^60 and seems to pass all tests of randomness. A favorite
  stand-alone generator---faster than KISS, which contains it.*/

/* SHR3 is a 3-shift-register generator with
   period 2^32-1. It uses
   y(n)=y(n-1)(I+L^17)(I+R^13)(I+L^5), with the
   y's viewed as binary vectors, L the 32x32
   binary matrix that shifts a vector left 1, and
   R its transpose.  SHR3 seems to pass all except
   the binary rank test, since 32 successive
   values, as binary vectors, must be linearly
   independent, while 32 successive truly random
   32-bit integers, viewed as binary vectors, will
   be linearly independent only about 29% of the time.   */

/* CONG is a congruential generator with the
   widely used 69069 as multiplier:
   x(n)=69069x(n-1)+1234567.  It has period 2^32.
   The leading half of its 32 bits seem to pass
   all tests, but bits in the last half are too
   regular.                               */

/* LFIB4 is an extension of the class that I have
   previously defined as  lagged Fibonacci
   generators: x(n)=x(n-r) op x(n-s), with the x's
   in a finite set over which there is a binary
   operation op, such as +,- on integers mod 2^32,
   * on odd such integers, exclusive-or (xor) on
   binary vectors. Except for those using
   multiplication, lagged Fibonacci generators
   fail various tests of randomness, unless the
   lags are very long.  To see if more than two
   lags would serve to overcome the problems of 2-
   lag generators using +,- or xor, I have
   developed the 4-lag generator LFIB4:
   x(n)=x(n-256)+x(n-179)+x(n-119)+x(n-55) mod 2^32.
   Its period is 2^31*(2^256-1), about 2^287, and
   it seems to pass all tests---in particular,
   those of the kind for which 2-lag generators
   using +,-,xor seem to fail.  For even more
   confidence in its suitability,  LFIB4 can be
   combined with KISS, with a resulting period of
   about 2^410: just use (KISS+LFIB4) in any C
   expression.                               */

/* SWB is a subtract-with-borrow generator that I
   developed to give a simple method for producing
   extremely long periods:
   x(n)=x(n-222)-x(n-237)-borrow mod 2^32.
   The 'borrow' is 0 unless set to 1 if computing
   x(n-1) caused overflow in 32-bit integer
   arithmetic. This generator has a very long
   period, 2^7098(2^480-1), about 2^7578. It seems
   to pass all tests of randomness, but,
   suspicious of a generator so simple and fast
   (62 nanosecs at 300MHz), I would suggest
   combining SWB with KISS, MWC, SHR3, or CONG. */

/* Finally, because many simulations call for
   uniform random variables in 0<v<1 or -1<v<1, I
   use #define statements that permit inclusion of
   such variates directly in expressions:  using
   UNI will provide a uniform random real (float)
   in (0,1), while VNI will provide one in (-1,1).  */

/* All of these: MWC, SHR3, CONG, KISS, LFIB4,
   SWB, UNI and VNI, permit direct insertion of
   the desired random quantity into an expression,
   avoiding the time and space costs of a function
   call. I call these in-line-define functions.
   To use them, static variables z,w,jsr and
   jcong should be assigned seed values other than
   their initial values.  If LFIB4 or SWB are
   used, the static table t[256] must be
   initialized.  A sample procedure follows. */

/* A note on timing:  It is difficult to provide
   exact time costs for inclusion of one of these
   in-line-define functions in an expression.
   Times may differ widely for different
   compilers, as the C operations may be deeply
   nested and tricky. I suggest these rough
   comparisons, based on averaging ten runs of a
   routine that is essentially a long loop:
   for(i=1;i<10000000;i++) L=KISS; then with KISS
   replaced with SHR3, CONG,... or KISS+SWB, etc.
   The times on my home PC, a Pentium 300MHz, in
   nanoseconds: LFIB4=64; CONG=90; SWB=100;
   SHR3=110; KISS=209; KISS+LFIB4=252; KISS+SWB=310.     */

#endif
#endif
