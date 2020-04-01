// Copyright (C) 2020 Megan Ruggiero
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const struct option options[] = {
	{ "spread", required_argument, NULL, 'p' },
	{ "freq", required_argument, NULL, 'F' },
	{ "seed", required_argument, NULL, 'S' },
	{ "version", no_argument, NULL, 'v' },
	{ "help", no_argument, NULL, 'h' },
	{ NULL, 0, NULL, 0 }
};

static const char help[] =
	"Usage: catlol [OPTION]...\n"
	"\n"
	"Colorize standard input to standard output.\n"
	"\n"
	"--spread, -p <f>: Rainbow spread (default: 3.0)\n"
	"  --freq, -F <f>: Rainbow frequency (default: 0.1)\n"
	"  --seed, -S <i>: Rainbow seed, 0 = random (default: 0)\n"
	"\n"
	"Report catlol bugs to <https://github.com/decadentsoup/catlol/issues>\n"
	"catlol home page: <https://github.com/decadentsoup/catlol>\n";

static double freq = 0.1, spread = 3.0;
static int os, i;

static void printc(char);
static void prints(const char *);

int
main(int argc, char **argv)
{
	enum { DEFAULT, VERSION, HELP } action;
	int c;

	action = DEFAULT;

	while ((c = getopt_long(argc, argv, "p:F:S:vh", options, NULL)) != -1)
		switch (c) {
		case 'p':
			spread = atof(optarg);
			break;
		case 'F':
			freq = atof(optarg);
			break;
		case 'S':
			os = atoi(optarg) + 1;
			break;
		case 'v':
			action = VERSION;
			break;
		case 'h':
			action = HELP;
			break;
		}

	if (!os) {
		srand(time(0));
		os = rand();
	}

	switch (action) {
	case DEFAULT:
		while ((c = getchar()) != EOF)
			printc(c);
		break;
	case VERSION:
		prints("catlol " PKGVER "\n");
		break;
	case HELP:
		prints(help);
		break;
	}

	printf("\33[m");

	return 0;
}

static void
printc(char c)
{
	double j;
	int r, g, b;

	if (c == '\n') {
		os += 1;
		i = 0;
		putchar('\n');
	} else {
		j = freq * (os + i++ / spread);
		r = sin(j) * 127 + 128;
		g = sin(j + 2 * 3.14159265358979323846 / 3) * 127 + 128;
		b = sin(j + 4 * 3.14159265358979323846 / 3) * 127 + 128;
		printf("\e[38;2;%d;%d;%dm%c", r, g, b, c);
	}
}

static void
prints(const char *s)
{
	for (; *s; s++)
		printc(*s);
}
