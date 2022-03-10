

const char *font_dirs[4] = {"fonts_unknown", "fonts_permissive",
                            "fonts_gplcopyleft", "fonts_noncommercial"};

/*
    Insert file "insertname" between lines "start_line" and "end_line" of file "
   filename"
  */
int insert_file_into_file(const char *filename, const char *insertname,
                          const char *start_line, const char *end_line)
{
  int ch;
  static char line[1024 * 4];
  const char *tmpname = "tmp.h";
  FILE *source_fp;
  FILE *dest_fp;
  FILE *insert_fp;

  if (file_copy(filename, tmpname) == 0)
    return 0;

  source_fp = fopen(tmpname, "r");
  dest_fp = fopen(filename, "w");
  insert_fp = fopen(insertname, "r");

  if (source_fp == NULL || dest_fp == NULL || insert_fp == NULL)
    return 0;

  for (;;) {
    if (fgets(line, 1024 * 4, source_fp) == NULL)
      break;
    if (strncmp(line, start_line, strlen(start_line)) == 0) {
      fputs(line, dest_fp);

      while ((ch = fgetc(insert_fp)) != EOF)
        fputc(ch, dest_fp);

      fputs("\n", dest_fp);

      for (;;) {
        if (fgets(line, 1024 * 4, source_fp) == NULL)
          break;
        if (strncmp(line, end_line, strlen(end_line)) == 0) {
          fputs(line, dest_fp);
          break;
        }
      }
    }
    else {
      fputs(line, dest_fp);
    }
  }

  fclose(insert_fp);
  fclose(source_fp);
  fclose(dest_fp);

  unlink(tmpname);

  printf("patched %s\n", filename);

  return 1;
}

void txtconv(int i, int fm, char *fms, int bm, char *bms, int mm, char *mms)
{
  const char *gr = gi[fi[i].group].reference;
  const char *fn = fi[i].name;
  size_t buff_sz = 256;
  char section[buff_sz];
  char prefix[buff_sz];
  char buff[buff_sz];

  int font_licence_type;
  if(
    strcmp(gr, "fntgrpadobex11") == 0
    ||
    strcmp(gr, "fntgrphasankazan") == 0
    ||
    strcmp(gr, "fntgrpim") == 0
    ||
    strcmp(gr, "fntgrpangel") == 0
    ||
    (strcmp(gr, "fntgrpbitfontmaker2") == 0 && (
      strcmp(fn, "3x3basic") == 0
      ||
      strcmp(fn, "3x5im") == 0
      ||
      strcmp(fn, "8bitclassic") == 0
      ||
      strcmp(fn, "adventurer") == 0
      ||
      strcmp(fn, "botmaker") == 0
      ||
      strcmp(fn, "bpixel") == 0
      ||
      strcmp(fn, "bpixeldouble") == 0
      ||
      strcmp(fn, "bracketedbabies") == 0
      ||
      strcmp(fn, "bytesize") == 0
      ||
      strcmp(fn, "ciircle13") == 0
      ||
      strcmp(fn, "commodore64") == 0
      ||
      strcmp(fn, "doomalpha04") == 0
      ||
      strcmp(fn, "dystopia") == 0
      ||
      strcmp(fn, "efraneextracondensed") == 0
      ||
      strcmp(fn, "eckpixel") == 0
      ||
      strcmp(fn, "elispe") == 0
      ||
      strcmp(fn, "eventhrees") == 0
      ||
      strcmp(fn, "fivepx") == 0
      ||
      strcmp(fn, "fourmat") == 0
      ||
      strcmp(fn, "frikativ") == 0
      ||
      strcmp(fn, "greenbloodserif2") == 0
      ||
      strcmp(fn, "heavybottom") == 0
      ||
      strcmp(fn, "heisans") == 0
      ||
      strcmp(fn, "kibibyte") == 0
      ||
      strcmp(fn, "likeminecraft") == 0
      ||
      strcmp(fn, "littlemissloudonbold") == 0
      ||
      strcmp(fn, "medsans") == 0
      ||
      strcmp(fn, "mildras") == 0
      ||
      strcmp(fn, "minicute") == 0
      ||
      strcmp(fn, "minuteconsole") == 0
      ||
      strcmp(fn, "moosenooks") == 0
      ||
      strcmp(fn, "neuecraft") == 0
      ||
      strcmp(fn, "new3x9pixelfont") == 0
      ||
      strcmp(fn, "originalsans") == 0
      ||
      strcmp(fn, "pixzillav1") == 0
      ||
      strcmp(fn, "princess") == 0
      ||
      strcmp(fn, "scrum") == 0
      ||
      strcmp(fn, "simple1") == 0
      ||
      strcmp(fn, "sisterserif") == 0
      ||
      strcmp(fn, "smallsimple") == 0
      ||
      strcmp(fn, "smolfont") == 0
      ||
      strcmp(fn, "standardized3x5") == 0
      ||
      strcmp(fn, "sticker100complete") == 0
      ||
      strcmp(fn, "stylishcharm") == 0
      ||
      strcmp(fn, "tallpix") == 0
      ||
      strcmp(fn, "tallpixelextended") == 0
      ||
      strcmp(fn, "threepix") == 0
      ||
      strcmp(fn, "tiny_gk") == 0
      ||
      strcmp(fn, "tiny_simon") == 0
      ||
      strcmp(fn, "tinyface") == 0
      ||
      strcmp(fn, "tinypixie2") == 0
      ||
      strcmp(fn, "tinyunicode") == 0
      ||
      strcmp(fn, "wedge") == 0
      )
    )
    ||
    strcmp(gr, "fntgrpchristinaneofotistou") == 0
    ||
    strcmp(gr, "fntgrpcodeman38") == 0
    ||
    strcmp(gr, "fntgrpcrox") == 0
    ||
    strcmp(gr, "fntgrpcu12") == 0
    ||
    strcmp(gr, "fntgrpdafont") == 0
    ||
    strcmp(gr, "fntgrpefont") == 0
    ||
    strcmp(gr, "fntgrpextant") == 0
    ||
    (strcmp(gr, "fntgrpfontstruct") == 0 && (
      strcmp(fn, "amstrad_cpc_extended") == 0
      ||
      strcmp(fn, "lucasfont_alternate") == 0
      ||
      strcmp(fn, "p01type") == 0
      ||
      strcmp(fn, "m_c_kids_nes_credits_font") == 0
      )
    )
    ||
    strcmp(gr, "fntgrpfreeuniversal") == 0
    ||
    strcmp(gr, "fntgrpgeoff") == 0
    ||
    strcmp(gr, "fntgrpgilesbooth") == 0
    ||
    strcmp(gr, "fntgrpinconsolata") == 0
    ||
    strcmp(gr, "fntgrpjapanyoshi") == 0
    ||
    strcmp(gr, "fntgrpjaywright") == 0
    ||
    strcmp(gr, "fntgrpjosephknightcom") == 0
    ||
    strcmp(gr, "fntgrplogisoso") == 0
    ||
    strcmp(gr, "fntgrplucida") == 0
    ||
    strcmp(gr, "fntgrpmistressellipsis") == 0
    ||
    strcmp(gr, "fntgrpoldstandard") == 0
    ||
    strcmp(gr, "fntgrpopengameart") == 0
    ||
    strcmp(gr, "fntgrppentacom") == 0
    ||
    strcmp(gr, "fntgrppersian") == 0
    ||
    strcmp(gr, "fntgrpprofont") == 0
    ||
    strcmp(gr, "fntgrptlwg") == 0
    ||
    strcmp(gr, "fntgrptlwg") == 0
    ||
    strcmp(gr, "fntgrptomthumb") == 0
    ||
    strcmp(gr, "fntgrptulamide") == 0
    ||
    strcmp(gr, "fntgrpu8g") == 0
    ||
    strcmp(gr, "fntgrpttyp0") == 0
    ||
    strcmp(gr, "fntgrpx11") == 0
    ||
    strcmp(gr, "fntgrpiconic") == 0
    ||
    strcmp(gr, "fntgrpacademiasinica") == 0
    ||
    strcmp(gr, "fntgrpstreamline") == 0
    ||
    strcmp(gr, "fntgrpmysteryquest") == 0
    )
    font_licence_type = 1; /* permissive */
  else if(
    (strcmp(gr, "fntgrpfontstruct") == 0 && (
      strcmp(fn, "baby") == 0
      ||
      strcmp(fn, "blipfest_07") == 0
      ||
      strcmp(fn, "chikita") == 0
      ||
      strcmp(fn, "pixelle_micro") == 0
      ||
      strcmp(fn, "robot_de_niro") == 0
      ||
      strcmp(fn, "trixel_square") == 0
      ||
      strcmp(fn, "haxrcorp4089") == 0
      ||
      strcmp(fn, "bubble") == 0
      ||
      strcmp(fn, "cardimon_pixel") == 0
      ||
      strcmp(fn, "maniac") == 0
      ||
      strcmp(fn, "chargen_92") == 0
      ||
      strcmp(fn, "utopia24") == 0
      )
    )
    ||
    strcmp(gr, "fntgrpnbp") == 0
    ||
    strcmp(gr, "fntgrpoldschoolpcfonts") == 0
    ||
    strcmp(gr, "fntgrpunifont") == 0
    ||
    strcmp(gr, "fntgrpwqy") == 0
    ||
    strcmp(gr, "fntgrpsiji") == 0
    )
    font_licence_type = 2; /* GPL and compatible copyleft */
  else if(
    (strcmp(gr, "fntgrpbitfontmaker2") == 0 && (
      strcmp(fn, "busdisplay11x5") == 0
      ||
      strcmp(fn, "busdisplay8x5") == 0
      ||
      strcmp(fn, "fancypixels") == 0
      ||
      strcmp(fn, "iconquadpix") == 0
      ||
      strcmp(fn, "lastapprenticebold") == 0
      ||
      strcmp(fn, "lastapprenticethin") == 0
      ||
      strcmp(fn, "pxclassic") == 0
      ||
      strcmp(fn, "sonicmania") == 0
      )
    )
    ||
    (strcmp(gr, "fntgrpfontstruct") == 0 && (
      strncmp(fn, "lucasarts_scumm_subtitle", 15) == 0
      )
    )
    )
    font_licence_type = 3; /* Non-commercial */
  else
    font_licence_type = 0; /* Unknown */

  snprintf(buff, buff_sz, "cp single_font_files/%s.c %s",
           target_font_identifier, font_dirs[font_licence_type]);
  system(buff);

  if (target_font_identifier[2] == 'g') { /* u8g2_ */
    strcpy(section, "U8G2_FONT_SECTION");
    strcpy(prefix, "u8g2");
  }
  else { /* u8g2_ */
    strcpy(section, "U8X8_FONT_SECTION");
    strcpy(prefix, "u8x8");
  }

  snprintf(buff, buff_sz,
           "echo 'extern const uint8_t %s[] %s(\"%s\");' >> %s/%s_font_decls.txt",
           target_font_identifier, section, target_font_identifier,
           font_dirs[font_licence_type], prefix);
  system(buff);
  snprintf(buff, buff_sz,
           "echo '  { \"%s\", \"%s\", \"%s\", %s},' >> %s/%s_font_lookup.txt",
           target_font_identifier, fn, gr, target_font_identifier,
           font_dirs[font_licence_type], prefix);
  system(buff);


  //fprintf(stdout, "%d,%s,%s,%s,%d\n", i, fn, gr, target_font_identifier,
  //        font_licence_type);

  return;
}

int main(void)
{
  const char *prefixes[] = {"u8x8", "u8g2"};
  size_t buff_sz = 256;
  char out_file[buff_sz];
  char in_file[buff_sz];
  char buff[buff_sz];
  for(int i=0; i<4; i++) {
    snprintf(buff, buff_sz, "rm -rf %s", font_dirs[i]);
    system(buff);
    snprintf(buff, buff_sz, "mkdir -p %s", font_dirs[i]);
    system(buff);
    for( int j=0; j<2; j++) {
      const char *pre = prefixes[j];
      snprintf(buff, buff_sz, "> %s/%s_font_decls.txt", font_dirs[i], pre);
      system(buff);
      snprintf(buff, buff_sz, "> %s/%s_font_lookup.txt", font_dirs[i], pre);
      system(buff);
    }
  }

  do_font_loop(txtconv);

  // add extra fonts
  int font_licence_type = 2;
  const char *font_id = "u8g2_font_unifont_world";

  snprintf(buff, buff_sz, "cp single_font_files/%s.c %s",
           font_id, font_dirs[font_licence_type]);
  system(buff);
  snprintf(buff, buff_sz,
           "echo 'extern const uint8_t %s[] U8G2_FONT_SECTION(\"%s\");' >> "
           "%s/u8g2_font_decls.txt",
           font_id, font_id, font_dirs[font_licence_type]);
  system(buff);
  snprintf(buff, buff_sz,
           "echo '  { \"%s\", \"%s\", \"%s\", %s},' >> %s/u8g2_font_lookup.txt",
           font_id, "unifont", "fntgrpunifont", font_id,
           font_dirs[font_licence_type]);
  system(buff);

  // skip unknown == 0
  for(int i=1; i<4; i++) {
    const char *dir = font_dirs[i];
    for( int j=0; j<2; j++) {
      char path[buff_sz];
      const char *pre = prefixes[j];
      snprintf(path, buff_sz, "%s/%s_%s", dir, pre, dir);
      snprintf(buff, buff_sz, "echo > %s.h", path);
      system(buff);
      snprintf(buff, buff_sz, "echo > %s.cpp", path);
      system(buff);

      if(i != 1) {
        snprintf(buff, buff_sz, "echo '#include \"../%s.h\"\n' >> %s.h", pre, path);
        system(buff);
        if (j == 1) { /*u8g2 */
          snprintf(buff, buff_sz, "echo '#include \"%s_%s.h\"\n' >> %s.h", "u8x8",
                   dir, path);
          system(buff);
        }
      }

      snprintf(buff, buff_sz, "cat %s/%s_font_decls.txt >> %s.h", dir, pre,
               path);
      system(buff);

      if (i == 1 && j == 0) { // permissive and writing into u8x8.h
        snprintf(buff, buff_sz,
                 "echo '\\n\\ntypedef struct font_lookup {\n  const char "
                 "*id;\n  const char *name;\n  const char *group;\n   const "
                 "uint8_t *data;\n} font_lookup;\n'  >> %s.h",
                 path);
        system(buff);
      }

      snprintf(buff, buff_sz,
               "echo '\\n\\nextern const font_lookup %s_%s[];' >> %s.h", pre, dir,
               path);
      system(buff);

      snprintf(buff, buff_sz, "echo '#include \"%s_%s.h\"\n' >> %s.cpp", pre,
               dir, path);
      system(buff);

      snprintf(buff, buff_sz,
               "echo '\\n\\nconst font_lookup %s_%s[] = {' >> %s.cpp", pre, dir,
               path);
      system(buff);

      snprintf(buff, buff_sz, "cat %s/%s_font_lookup.txt >> %s.cpp", dir, pre,
               path);
      system(buff);

      snprintf(buff, buff_sz, "echo '};' >> %s.cpp", path);
      system(buff);

      if (i == 1) { // permissive will insert the text and not use the header
        snprintf(out_file, buff_sz, "../../../csrc/%s.h", pre);
        snprintf(in_file, buff_sz, "%s/%s_%s.h", dir, pre, dir);
        insert_file_into_file(out_file, in_file, "/* start font list */",
                         "/* end font list */");
      }
      //snprintf(buff, buff_sz, "rm %s/%s_font_decls.txt %s/%s_font_lookup.txt",
      //         dir, pre, dir, pre);
      //system(buff);
    }
  }

  return 0;
}
