#/bin/bash
# Author: Adrian Rossiter <adrian@antiprism.com>
# Licence: CC0/Public Domain http://creativecommons.org/publicdomain/zero/1.0/

U8G2_SRC_DIR=../u8g2
SRC_DIR=src
SETUP_DIR=setup


# copy all the original source files into a single directory
rm -rf ${SRC_DIR}   
mkdir ${SRC_DIR} \
      ${SRC_DIR}/setup \
      ${SRC_DIR}/include

cp -a ${U8G2_SRC_DIR}/csrc ${SRC_DIR}
cp -a ${U8G2_SRC_DIR}/cppsrc ${SRC_DIR}
cp -a ${SETUP_DIR}/files/U8x8lib.cpp ${SRC_DIR}/cppsrc  # overwrite
cp -a ${SETUP_DIR}/files/U8g2lib.cpp ${SRC_DIR}/cppsrc  # overwrite
cp -a ${SETUP_DIR}/files/U8g2Controller.cpp ${SRC_DIR}/cppsrc
cp -a ${SETUP_DIR}/files/U8g2Controller.h ${SRC_DIR}/cppsrc
cp -a ${SETUP_DIR}/files/u8g2_controllers.c ${SRC_DIR}/csrc
cp -a ${SETUP_DIR}/files/u8g2_controllers.h ${SRC_DIR}/csrc
# cp -a ${SETUP_DIR}/files/u8g2_fonts_permissive.c ${SRC_DIR}/csrc
# cp -a ${SETUP_DIR}/files/u8g2_fonts_permissive.h ${SRC_DIR}/csrc
cp -a ${SETUP_DIR}/port ${SRC_DIR}
cp -a ${SETUP_DIR}/codebuild ${SRC_DIR}/setup
cp -a ${U8G2_SRC_DIR}/tools/codebuild/codebuild.c ${SRC_DIR}/setup/codebuild
cp -a ${U8G2_SRC_DIR}/tools/font ${SRC_DIR}/setup
cp -a ${SETUP_DIR}/files/font_build_inc.c ${SRC_DIR}/setup/font/build

# create license files
cat ${SETUP_DIR}/files/copying.txt \
  ${SETUP_DIR}/files/licence_text_permissive.txt \
  ${SETUP_DIR}/files/licence_text_gplcopyleft.txt \
  ${SETUP_DIR}/files/licence_text_noncommercial.txt \
  > COPYING
cp ${SETUP_DIR}/files/licence_text_permissive.txt COPYING_permissive
cp ${SETUP_DIR}/files/licence_text_gplcopyleft.txt COPYING_gplcopyleft
cp ${SETUP_DIR}/files/licence_text_noncommercial.txt COPYING_noncommercial

# Split fonts by licence
# Remove combined fnts files
rm ${SRC_DIR}/csrc/u8g2_fonts.c
rm ${SRC_DIR}/csrc/u8x8_fonts.c
# Add header needed to compile individual font files
sed -i '/^const uint8_t.*/i #include "../u8g2.h"' ${SRC_DIR}/setup/font/build/single_font_files/*.c

# Ensure PIN code is included
sed -i 's!#ifdef ARDUINO!#if 1     // libug8arm: was #ifdef ARDUINO!' ${SRC_DIR}/csrc/u8x8.h
# Ensure USER_PTR code is enabled
sed -i 's!^//#define U8X8_WITH_USER_PTR!#define U8X8_WITH_USER_PTR!' ${SRC_DIR}/csrc/u8x8.h

# Create C++ interface
sed -i 's!#include <Arduino.h>!!' ${SRC_DIR}/cppsrc/U8x8lib.h
sed -i 's!#include <Print.h>!!' ${SRC_DIR}/cppsrc/U8x8lib.h
sed -i 's!#include "u8x8.h"!#include "../csrc/u8x8.h"!' ${SRC_DIR}/cppsrc/U8x8lib.h
sed -i 's! : public Print!!' ${SRC_DIR}/cppsrc/U8x8lib.h
sed -i 's!_byte_arduino_!_byte_arm_linux_!' ${SRC_DIR}/cppsrc/U8x8lib.h
sed -i 's!u8x8_gpio_and_delay_arduino!u8x8_arm_linux_gpio_and_delay!' ${SRC_DIR}/cppsrc/U8x8lib.h

sed -i 's!#include <Arduino.h>!!' ${SRC_DIR}/cppsrc/U8g2lib.h
sed -i 's!#include <Print.h>!!' ${SRC_DIR}/cppsrc/U8g2lib.h
sed -i 's!void writeBuffer!//void writeBuffer!' ${SRC_DIR}/cppsrc/U8g2lib.h
sed -i 's!#include "u8g2.h"!#include "../csrc/u8g2.h"!' ${SRC_DIR}/cppsrc/U8g2lib.h
sed -i 's! : public Print!!' ${SRC_DIR}/cppsrc/U8g2lib.h

sed -i $'s!^int main.*!#include "font_build_inc.c"\\\n\\\nint main_orig(void)!' ${SRC_DIR}/setup/font/build/build.c

(cd src/setup/font/build && rm -f build1 && make && ./build1)

FONTS_DIR=${SRC_DIR}/setup/font/build/
cp -a ${FONTS_DIR}/fonts_gplcopyleft ${FONTS_DIR}/fonts_noncommercial ${FONTS_DIR}/fonts_permissive ${SRC_DIR}/csrc
# leave working files in src/setup but remove from final source directory
rm ${SRC_DIR}/csrc/fonts_permissive/*.txt \
   ${SRC_DIR}/csrc/fonts_gplcopyleft/*.txt \
   ${SRC_DIR}/csrc/fonts_noncommercial/*.txt

sed -i 's!_byte_arduino_!_byte_arm_linux_!' ${SRC_DIR}/setup/codebuild/codebuild.c
sed -i 's!u8x8_gpio_and_delay_arduino!u8x8_arm_linux_gpio_and_delay!' ${SRC_DIR}/setup/codebuild/codebuild.c
sed -i 's!u8x8_gpio_and_delay_arduino!u8x8_arm_linux_gpio_and_delay!' ${SRC_DIR}/setup/codebuild/codebuild.c
sed -i 's!int main!int main_orig!' ${SRC_DIR}/setup/codebuild/codebuild.c
(cd src/setup/codebuild; make -f makefile; ./codebuild_cpp)
# Add controller list to header docs
cp -a ${SETUP_DIR}/controller_list ${SRC_DIR}/setup
(cd src/setup/controller_list; sh controllers.sh)

U8G2_VER=$(sh ../u8g2/tools/release/print_release.sh)

# generate Makefile.am 
# TAB="$(printf '\t')"
cat << END >> ${SRC_DIR}/Makefile.am
lib_LTLIBRARIES = libu8g2arm.la
libu8g2arm_la_SOURCES =
libu8g2arm_la_LIBADD = libu8g2armport.la libu8g2armcsrc.la
libu8g2arm_la_LDFLAGS = -release ${U8G2_VER}
noinst_LTLIBRARIES = libu8g2armport.la libu8g2armcsrc.la

libu8g2armport_la_SOURCES = \\
END

for p in ${SRC_DIR}/port/*.c ${SRC_DIR}/port/*.h ; do
f=$(basename $p)
echo -e "\tport/${f} \\" >> ${SRC_DIR}/Makefile.am
done
echo -e "\t# terminate list" >> ${SRC_DIR}/Makefile.am


cat << END >> ${SRC_DIR}/Makefile.am

libu8g2armcsrc_la_SOURCES = \\
END

for p in ${SRC_DIR}/csrc/*.c ${SRC_DIR}/csrc/*.h ; do
f=$(basename $p)
echo -e "\tcsrc/${f} \\" >> ${SRC_DIR}/Makefile.am
done
for p in ${SRC_DIR}/csrc/fonts_permissive/*.c ; do
f=$(basename $p)
echo -e "\tcsrc/fonts_permissive/${f} \\" >> ${SRC_DIR}/Makefile.am
done
for p in ${SRC_DIR}/cppsrc/*.cpp ${SRC_DIR}/cppsrc/*.h ; do
f=$(basename $p)
echo -e "\tcppsrc/${f} \\" >> ${SRC_DIR}/Makefile.am
done
echo -e "\t# terminate list" >> ${SRC_DIR}/Makefile.am





cat << END >> ${SRC_DIR}/Makefile.am

lib_LTLIBRARIES += libu8g2fonts_gplcopyleft.la
libu8g2fonts_gplcopyleft_la_LDFLAGS = -release ${U8G2_VER}
libu8g2fonts_gplcopyleft_la_SOURCES = \\
END

for p in ${SRC_DIR}/csrc/fonts_gplcopyleft/*.c ; do
f=$(basename $p)
echo -e "\tcsrc/fonts_gplcopyleft/${f} \\" >> ${SRC_DIR}/Makefile.am
done
echo -e "\t# terminate list" >> ${SRC_DIR}/Makefile.am

cat << END >> ${SRC_DIR}/Makefile.am

lib_LTLIBRARIES += libu8g2fonts_noncommercial.la
libu8g2fonts_noncommercial_la_LDFLAGS = -release ${U8G2_VER}
libu8g2fonts_noncommercial_la_SOURCES = \\
END

for p in ${SRC_DIR}/csrc/fonts_noncommercial/*.c ; do
f=$(basename $p)
echo -e "\tcsrc/fonts_noncommercial/${f} \\" >> ${SRC_DIR}/Makefile.am
done
echo -e "\t# terminate list" >> ${SRC_DIR}/Makefile.am

cat << END >> ${SRC_DIR}/Makefile.am







pkginclude_HEADERS = \\
END
for p in ${SRC_DIR}/port/*.h  ${SRC_DIR}/csrc/*.h ${SRC_DIR}/cppsrc/*.h ${SRC_DIR}/csrc/fonts_gplcopyleft/*.h ${SRC_DIR}/csrc/fonts_noncommercial/*.h; do
cp ${p} ${SRC_DIR}/include
f=$(basename $p)
echo -e "\tinclude/${f} \\" >> ${SRC_DIR}/Makefile.am
done
echo -e "\t# terminate list" >> ${SRC_DIR}/Makefile.am

# sed 's!<u8g2.h>!"u8g2.h"!' ${PORT_SRC_DIR}/port/U8g2lib.h > ${SRC_DIR}/include/u8g2arm.h
sed -i 's!\.\./[^/]*/!!' ${SRC_DIR}/include/*.h
sed -i 's!\.\./!!' ${SRC_DIR}/include/*.h
