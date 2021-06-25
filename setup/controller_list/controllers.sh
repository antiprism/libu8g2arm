

cat << END > out.txt
const char *controllers[][3] {
END

grep '^{.*,$' ../../../src/csrc/u8g2_controllers.c | sed 's!,$!},!' >> out.txt


cat << END >> out.txt
  {"", "", ""}
};
END

g++ -o controller_list controller_list.cpp
./controller_list > controllers.txt
sed -i -e '/CONTROLLER_LIST/ {' -e 'r controllers.txt' -e 'd' -e '}' ../../cppsrc/U8g2Controller.h

# sed -i 's!CONTROLLER_LIST!! r controllers.txt' ../../cppsrc/U8g2Controller.h
# sed -e '/SUBSTITUTETHIS/ {' -e 'r temp.TXT' -e 'd' -e '}' -i devel.txt
