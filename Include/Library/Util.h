#ifndef UTIL_H
#define UTIL_H 1

#include <PiDxe.h>
#include <Guid/FileInfo.h>

#include <Library/BaseLib.h>
#include <Library/FileHandleLib.h>

#ifndef LIBUTIL_NOAROMA
#include <aroma.h>
#endif

#define ROUNDUP(a, b)   (((a) + ((b)-1)) & ~((b)-1))
#define ROUNDDOWN(a, b) ((a) & ~((b)-1))

#if defined (MDE_CPU_IA32)
#define CACHE_LINE 32
#elif defined (MDE_CPU_X64)
#define CACHE_LINE 32
#elif defined (MDE_CPU_ARM)
#define CACHE_LINE ArmDataCacheLineLength()
#else
#error "Unsupported platform"
#endif

#define STACKBUF_DMA_ALIGN(var, size) \
	UINT8 __##var[(size) + CACHE_LINE]; UINT8 *var = (UINT8 *)(ROUNDUP((UINTN)__##var, CACHE_LINE))

#define BASE64_ENCODED_SIZE(n) (ROUNDUP(4*((n)/3)+1, 4)+1)

#define UtilBase64Encode __b64_ntop
#define UtilBase64Decode __b64_pton

INT32 __b64_ntop (UINT8 CONST *, UINTN, CHAR8 *, UINTN);
INT32 __b64_pton (CHAR8 CONST *, UINT8 *, UINTN);

typedef
EFI_STATUS
(EFIAPI *PROTOCOL_INSTANCE_CALLBACK)(
  IN EFI_HANDLE           Handle,
  IN VOID                 *Instance,
  IN VOID                 *Context
  );

CHAR8*
Unicode2Ascii (
  CONST CHAR16* UnicodeStr
);

CHAR16*
Ascii2Unicode (
  CONST CHAR8* AsciiStr
);

CHAR8*
AsciiStrDup (
  IN CONST CHAR8* Str
  );

CHAR16*
UnicodeStrDup (
  IN CONST CHAR16* Str
  );

VOID
PathToUnix(
  CHAR16* fname
);

VOID
PathToUefi(
  CHAR16* fname
);

BOOLEAN
NodeIsDir (
  IN EFI_FILE_INFO      *NodeInfo
  );

#ifndef LIBUTIL_NOAROMA
LIBAROMA_STREAMP
libaroma_stream_ramdisk(
  CONST CHAR8* Path
);
#endif

UINT32
RangeOverlaps (
  UINT32 x1,
  UINT32 x2,
  UINT32 y1,
  UINT32 y2
);

UINT32
RangeLenOverlaps (
  UINT32 x,
  UINT32 xl,
  UINT32 y,
  UINT32 yl
);

UINT32
AlignMemoryRange (
  IN UINT32 Addr,
  IN OUT UINTN *Size,
  OUT UINTN  *AddrOffset,
  IN UINTN Alignment
);

EFI_STATUS
FreeAlignedMemoryRange (
  IN UINT32 Address,
  IN OUT UINTN Size,
  IN UINTN Alignment
);

EFI_STATUS
VisitAllInstancesOfProtocol (
  IN EFI_GUID                    *Id,
  IN PROTOCOL_INSTANCE_CALLBACK  CallBackFunction,
  IN VOID                        *Context
  );

EFI_FILE_HANDLE
UtilOpenRoot (
  IN EFI_HANDLE                   DeviceHandle
  );

VOID *
UtilFileInfo (
  IN EFI_FILE_HANDLE      FHand,
  IN EFI_GUID             *InfoType
  );

CHAR16*
UtilGetTypeFromName (
  IN CHAR16   *FileName
  );

VOID
UtilToLowerString (
  IN CHAR16  *String
  );

CHAR16*
UtilGetExtensionLower (
  IN UINT16  *FileName
  );

#endif /* ! UTIL_H */
