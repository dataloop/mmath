#if defined(__linux__)
#  define __USE_BSD
#  include <stdint.h>
#  include <endian.h>
#  define htonll(v) htobe64(v)
#  define ntohll(v) be64toh(v)
#elif defined(__APPLE__)
#  include <libkern/OSByteOrder.h>
#  define htonll(v) OSSwapHostToBigInt64(v)
#  define ntohll(v) OSSwapBigToHostInt64(v)
#elif defined(SOLARIS)
#  include <sys/byteorder.h>
#endif

#define IS_SET(v) ((v & 0x00000000000000FFLL) != 0)
#define FROM_DDB(v) ((ErlNifSInt64) htonll((v & 0x0000000000000100LL) ? ((v & 0xFFFFFFFFFFFFFF00LL) | 0x00000000000000FFLL) : (v & 0xFFFFFFFFFFFFFF00LL)))
#define TO_DDB(v) ((ntohll(v) & 0xFFFFFFFFFFFFFF00LL) | 0x0000000000000001LL)


#define GET_CHUNK(chunk)                                                \
  if (!enif_get_int64(env, argv[1], &chunk))                            \
    return enif_make_badarg(env);                                       \
  if (chunk < 1)                                                        \
    return enif_make_badarg(env)

#define GET_BIN(pos, bin, count, vs)              \
  if (!enif_inspect_binary(env, argv[pos], &bin)) \
    return enif_make_badarg(env);                 \
  if (bin.size % sizeof(ErlNifSInt64))            \
    return enif_make_badarg(env);                 \
  count = bin.size / sizeof(ErlNifSInt64);        \
  vs = (ErlNifSInt64 *) bin.data
