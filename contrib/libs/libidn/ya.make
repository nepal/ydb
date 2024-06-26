# Generated by devtools/yamaker from nixpkgs 22.11.

DEFAULT(USE_IDN ${_USE_IDN})

LIBRARY()

WITHOUT_LICENSE_TEXTS()

VERSION(1.42)

ORIGINAL_SOURCE(mirror://gnu/libidn/libidn-1.42.tar.gz)

LICENSE(Service-Dll-Harness)

NO_RUNTIME()

IF (EXPORT_CMAKE)
    OPENSOURCE_EXPORT_REPLACEMENT(
        CMAKE
        IDN
        CMAKE_TARGET
        IDN::IDN
    )
ELSEIF (USE_IDN == "dynamic")
    PEERDIR(
        contrib/libs/libidn/dynamic
    )
ELSEIF (USE_IDN == "local")
    GLOBAL_CFLAGS(${USE_LOCAL_IDN_CFLAGS})
    DEFAULT(USE_LOCAL_IDN_LDFLAGS -lidn)
    LDFLAGS(${USE_LOCAL_IDN_LDFLAGS})
ELSE()
    PEERDIR(
        contrib/libs/libidn/static
    )
ENDIF()

END()

IF (USE_IDN != "local")
    RECURSE(
        dynamic
        static
    )
ENDIF()
