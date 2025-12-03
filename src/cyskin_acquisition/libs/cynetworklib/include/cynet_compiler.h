#ifndef CYNET_COMPILER_H
#define CYNET_COMPILER_H

/* use C++11's final if gcc supports it */
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 6)
# define FINAL final
#else
# define FINAL
#endif

#endif
