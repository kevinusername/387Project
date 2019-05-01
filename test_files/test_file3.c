int main(int argc, char **argv) {
	int c;

	initialize_main(&argc, &argv);
	set_program_name(argv[0]);
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	atexit(close_stdout);
	convert_entire_line = true;

	while ((c = getopt_long(argc, argv, shortopts, longopts, NULL)) != -1) {
		switch (c) {
		case 'i':
			convert_entire_line = false;
			break;

		case 't':
			parse_tab_stops(optarg);
			break;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if (optarg)
				parse_tab_stops(optarg - 1);
			else {
				char tab_stop[2];
				tab_stop[0] = c;
				tab_stop[1] = '\0';
				parse_tab_stops(tab_stop);
			}
			break;

			case_GETOPT_HELP_CHAR;

			case_GETOPT_VERSION_CHAR(PROGRAM_NAME, AUTHORS);

		default:
			usage(EXIT_FAILURE);
		}
	}

	finalize_tab_stops();

	set_file_list((optind < argc) ? &argv[optind] : NULL);

	expand();

	cleanup_file_list_stdin();

	return exit_status;
}