static void expand() {
	/* Input stream.  */
	FILE *fp = next_file(NULL, NULL);

	/* generate a temporary file name, and open/create said file */
	char *const temp_file_name = "EXTENDED_TEMP_mTwvB4qKbUEizRC91fWp";
	FILE *new_file = fopen(temp_file_name, "w+");

	/* store original file name */

	if (!fp)
		return;

	while (true) {
		/* Input character, or EOF.  */
		int c;

		/* If true, perform translations.  */
		bool convert = true;

		/* The following variables have valid values only when CONVERT
		   is true:  */

		/* Column of next input character.  */
		uintmax_t column = 0;

		/* Index in TAB_LIST of next tab stop to examine.  */
		size_t tab_index = 0;

		/* Convert a line of text.  */

		do {
			while ((c = getc(fp)) < 0 && (fp = next_file(fp, new_file))) {
				new_file = fopen(temp_file_name, "w+");
				fputc(' ', new_file);
				continue;
			}

			if (convert) {
				if (c == '\t') {
					/* Column the next input tab stop is on.  */
					uintmax_t next_tab_column;
					bool last_tab IF_LINT(= 0);

					next_tab_column =
						get_next_tab_column(column, &tab_index, &last_tab);

					if (last_tab)
						next_tab_column = column + 1;

					if (next_tab_column < column)
						die(EXIT_FAILURE, 0, _("input line is too long"));

					while (++column < next_tab_column)
						fputc(' ', new_file);

					c = ' ';
				} else if (c == '\b') {
					/* Go back one column, and force recalculation of the
					   next tab stop.  */
					column -= !!column;
					tab_index -= !!tab_index;
				} else {
					column++;
					if (!column)
						die(EXIT_FAILURE, 0, _("input line is too long"));
				}

				convert &= convert_entire_line || !!isblank(c);
			}

			if (c < 0)
				return;

			/* write current character to file */
			fputc(c, new_file);

		} while (c != '\n');
	}
}
