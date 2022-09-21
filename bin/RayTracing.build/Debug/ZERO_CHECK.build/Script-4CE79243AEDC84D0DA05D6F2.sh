#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/Johan/Documents/Liu/TNCG15/RayTracing/bin
  make -f /Users/Johan/Documents/Liu/TNCG15/RayTracing/bin/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/Johan/Documents/Liu/TNCG15/RayTracing/bin
  make -f /Users/Johan/Documents/Liu/TNCG15/RayTracing/bin/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/Johan/Documents/Liu/TNCG15/RayTracing/bin
  make -f /Users/Johan/Documents/Liu/TNCG15/RayTracing/bin/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/Johan/Documents/Liu/TNCG15/RayTracing/bin
  make -f /Users/Johan/Documents/Liu/TNCG15/RayTracing/bin/CMakeScripts/ReRunCMake.make
fi

