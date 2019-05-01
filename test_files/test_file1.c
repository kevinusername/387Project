extern FILE *next_file(FILE *fp, FILE *temp_file) {
	static char *prev_file;
	char *file;
	char const *temp_file_name = "EXTENDED_TEMP_mTwvB4qKbUEizRC91fWp";

	if (fp) {
		assert(prev_file);
		if (ferror(fp)) {
			error(0, errno, "%s", quotef(prev_file));
			exit_status = EXIT_FAILURE;
		}
		if (STREQ(prev_file, "-"))
			clearerr(fp); /* Also clear EOF.  */
		else if (fclose(fp) != 0) {
			error(0, errno, "%s", quotef(prev_file));
			exit_status = EXIT_FAILURE;
		} else {
			/* replace the old file with the new expanded file */
			fclose(temp_file);
			remove(prev_file);
			rename(temp_file_name, prev_file);
		}
	}

	while ((file = *file_list++) != NULL) {
		if (STREQ(file, "-")) {
			have_read_stdin = true;
			fp = stdin;
		} else
			fp = fopen(file, "r");
		if (fp) {
			prev_file = file;
			fadvise(fp, FADVISE_SEQUENTIAL);
			return fp;
		}
		error(0, errno, "%s", quotef(file));
		exit_status = EXIT_FAILURE;
	}
	return NULL;
}
