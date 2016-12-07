# - Find libgmpxx
# Find the libgmpxx includes and library
#
#  LIBGMPXX_INCLUDE_DIR - Where to find xercesc include sub-directory.
#  LIBGMPXX_LIBRARIES   - List of libraries when using LIBGMPXX.
#  LIBGMPXX_FOUND       - True if LIBGMPXX found.
IF (LIBGMPXX_INCLUDE_DIR)
  # Already in cache, be silent.
  SET(LIBGMPXX_FIND_QUIETLY TRUE)
ENDIF (LIBGMPXX_INCLUDE_DIR)

set(LIBGMPXX_INCLUDE_DIR /usr/include)
set(LIBGMP_INCLUDE_DIR /usr/include)

SET(LIBGMPXX_NAMES gmpxx )
SET(LIBGMP_NAMES gmp )
FIND_LIBRARY(LIBGMPXX_LIBRARY NAMES ${LIBGMPXX_NAMES} )
FIND_LIBRARY(LIBGMP_LIBRARY NAMES ${LIBGMP_NAMES} )

# Handle the QUIETLY and REQUIRED arguments and set LIBGMPXX_FOUND to
# TRUE if all listed variables are TRUE.
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
	LIBGMPXX DEFAULT_MSG
	LIBGMPXX_LIBRARY LIBGMPXX_INCLUDE_DIR
)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
	LIBGMP DEFAULT_MSG
	LIBGMP_LIBRARY LIBGMP_INCLUDE_DIR
)

IF(LIBGMPXX_FOUND AND LIBGMP_FOUND)
	SET(LIBGMPXX_LIBRARIES ${LIBGMPXX_LIBRARY} ${LIBGMP_LIBRARY})
ELSE(LIBGMPXX_FOUND)
	SET(LIBGMPXX_LIBRARIES )
ENDIF(LIBGMPXX_FOUND AND LIBGMP_FOUND)

MARK_AS_ADVANCED( LIBGMPXX_LIBRARY LIBGMPXX_INCLUDE_DIR )
