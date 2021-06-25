#include "codebuild.c"

FILE *init_c_fp;
FILE *init_h_fp;

void do_print_init(int controller_idx, int display_idx, const char *postfix, int interface_idx)
{
  FILE *fp = init_c_fp;

  if(*postfix != 'f')
    return;

  fprintf(fp, "{");
  fprintf(fp, "\"%s\", ", struppercase(controller_list[controller_idx].name));
  fprintf(fp, "\"%s\",",
          struppercase(
              controller_list[controller_idx].display_list[display_idx].name));
  fprintf(fp, "\"%s\",",
          struppercase(interface_list[interface_idx].interface_name));
  fprintf(fp, "\n            ");
  fprintf(fp, "%d, %d, ",
          controller_list[controller_idx].tile_width * 8,
          controller_list[controller_idx].tile_height * 8);

  fprintf(fp, "%s", get_setup_function_name(controller_idx, display_idx, postfix));

  fprintf(fp, "},\n");
}




void do_display2(int controller_idx, int display_idx, const char *postfix)
{
  // libu8g2 START01
  if ( controller_list[controller_idx].com & COM_4WSPI )
  {
    /* SW SPI */
    do_display_interface(controller_idx, display_idx, postfix, 0);
    do_print_init(controller_idx, display_idx, postfix, 0);
    /* HW SPI */
    do_display_interface(controller_idx, display_idx, postfix, 1);
    do_print_init(controller_idx, display_idx, postfix, 1);
  }
  if ( controller_list[controller_idx].com & COM_3WSPI )
  {
    /* 3wire SW SPI */
    do_display_interface(controller_idx, display_idx, postfix, 4);
    do_print_init(controller_idx, display_idx, postfix, 4);
  }
  if ( controller_list[controller_idx].com & COM_8080 )
  {
    /* 8080 mode */
    do_display_interface(controller_idx, display_idx, postfix, 3);
    do_print_init(controller_idx, display_idx, postfix, 3);
  }
  if ( controller_list[controller_idx].com & COM_I2C )
  {
    /* SW I2C */
    do_display_interface(controller_idx, display_idx, postfix, 6);
    do_print_init(controller_idx, display_idx, postfix, 6);
    /* HW I2C */
    do_display_interface(controller_idx, display_idx, postfix, 7);
    do_print_init(controller_idx, display_idx, postfix, 7);
  }
  return;
  // libu8g2 END01
}



void do_controller_buffer_code2(int idx, const char *postfix, int buf_len, int rows)
{
  int display_idx = 0;
  while( controller_list[idx].display_list[display_idx].name != NULL )
  {
    do_display2(idx, display_idx, postfix);
    display_idx++;
  }
}

void do_controller_list2(void)
{
  int i;

  fprintf(init_h_fp,
"typedef void (*setup_func_t)(\n"
"    u8g2_t *, const u8g2_cb_t *, u8x8_msg_cb, u8x8_msg_cb);\n"
"\n"
"typedef struct controller_details_t { \n"
"    const char *controller_type;\n"
"    const char *display_name;\n"
"    const char *com_type;\n"
"    int width;\n"
"    int height;\n"
"    setup_func_t setup_func;\n"
"} controller_details_t;\n"
"\n"
"extern controller_details_t controller_details[];\n"
"extern size_t controller_details_size;\n"
"\n");

fprintf(init_c_fp, "controller_details_t controller_details[] = {\n"
"/*\n"
"{\"CONTROLLER_TYPE\", \"DISPLAY_NAME\", \"COM_TYPE\"\n"
"      \"WIDTH\", \"HEIGHT\", setup_func}\n*/\n"
"\n");

  //fprintf(init_func_fp, "U8G2 *");
  for( i = 0; i < sizeof(controller_list)/sizeof(*controller_list); i++ )
  {
    do_controller_buffer_code2(i, "1", controller_list[i].tile_width*8, 1);
    do_controller_buffer_code2(i, "2", controller_list[i].tile_width*8*2, 2);
    do_controller_buffer_code2(i, "f", controller_list[i].tile_width*8*controller_list[i].tile_height, controller_list[i].tile_height);
    printf("\n");
  }
  fprintf(init_c_fp,
"};\n"
"\n"
"size_t controller_details_size = sizeof(controller_details) / sizeof(*controller_details);\n"
"\n");
}


int main(void)
{
  u8g2_cpp_header_fp = fopen("U8g2lib.h", "w");
  fprintf(u8g2_cpp_header_fp, "/* generated code (codebuild), u8g2 project */\n");

  u8x8_cpp_header_fp = fopen("U8x8lib.h", "w");
  fprintf(u8x8_cpp_header_fp, "/* generated code (codebuild), u8g2 project */\n");

  init_c_fp = fopen("u8g2_controllers.c", "w");
  init_h_fp = fopen("u8g2_controllers.h", "w");

  do_controller_list2();

  fclose(u8g2_cpp_header_fp);
  fclose(u8x8_cpp_header_fp);
  fclose(init_c_fp);
  fclose(init_h_fp);

  insert_into_file("../../cppsrc/U8g2lib.cpp", "U8g2lib.cpp", "// setup details start", "// setup details end */");
  insert_into_file("../../cppsrc/U8g2lib.h", "U8g2lib.h", "/* Arduino constructor list start */", "/* Arduino constructor list end */");
  insert_into_file("../../csrc/u8g2_controllers.c", "u8g2_controllers.c", "/* controller details start */", "/* controller details end */");
  insert_into_file("../../csrc/u8g2_controllers.h", "u8g2_controllers.h", "/* controller details start */", "/* controller details end */");
  insert_into_file("../../cppsrc/U8x8lib.h", "U8x8lib.h", "// constructor list start", "// constructor list end");

  return 0;
}

