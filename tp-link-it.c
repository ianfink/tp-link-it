/*
 * @author		Ian M. Fink
 *
 * @file		tp-link-it.c
 *
 * @copyright	Copyright (C) 2025 Ian M. Fink.  All rights reserved.
 *
 * Contact:		www.linkedin.com/in/ianfink
 *
 * Tabstop:	4
 *
 * This program is free software:  you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, please see: https://www.gnu.org/licenses.
 */

/*
 * Includes
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "tcpopen.h"

/*
 * Macros
 */

#define THE_PORT 9999
#define ON		"{\"system\":{\"set_relay_state\":{\"state\":1}}}"
#define OFF		"{\"system\":{\"set_relay_state\":{\"state\":0}}}"
#define REBOOT	"{\"system\":{\"reboot\":{\"delay\":1}}}"

/*
 * Prototypes
 */

int make_command_string(char *s);

/**************************************************************/

/**
 * Name:	make_command_string
 *
 * @brief	encode a command to be utilized by a TP-LINK Smart
 *			Home plug.
 *
 * @param	s	a pointer to a string with the command.
 *
 * @return	a length of an array of char with the encoded command
 *			to be utilized by a TP-LINK Smart Home plug.
 */

int
make_command_string(char *s)
{
	int		i;
	int		len = 4;
	char	a;
	char	key = (char)171;
	char	tmp_string[256];

	for (i=0; i<len; i++) {
		tmp_string[i] = '\0';
	}

	for (i=0; s[i]; i++) {
		a = key ^ s[i];
		key = a;
		tmp_string[len++] = a;
	}

	for (i=0; i<len; i++) {
		s[i] = tmp_string[i];
	}

	return len;
} /* make_command_string */

/**************************************************************/

/**
 * Name:	main
 *
 * @brief	a function that takes arguments and provides a command
 *			to a TP-LINK Smart Home plug based on the arguments.
 *
 * @param	argv[1]		a network identifier of the TP-LINK Smart
 *						Home plug.
 * @param	argv[2]		a command to turn on, off, or reboot the
 *						TP-LINK Smart Home plug.
 *
 * @return	an integer, where a 0 indicates success.
 */

int
main(int argc, char *argv[])
{
	int		fd;
	int		len;
	char	s[256];

	if (argc < 3) {
		printf("USAGE: %s <host> <cmd>\n", argv[0]);
		exit(__LINE__);
	}

	fd = tcp_open(argv[1], NULL, THE_PORT);
	if (fd < 0) {
		printf("%s could not open '%s'.\n", argv[0], argv[1]);
		exit(__LINE__);
	}

	if (!strcmp(argv[2], "on")) {
		strcpy(s, ON);
	} else if (!strcmp(argv[2], "off")) {
		strcpy(s, OFF);
	} else if (!strcmp(argv[2], "reboot")) {
		strcpy(s, REBOOT);
	} else {
		printf("cmd is 'on' or 'off' or 'reboot'\n");
		exit(__LINE__);
	}

	len = make_command_string(s);

	write(fd, (void *)s, len);

	close(fd);

	return 0;
} /* main */

/*
 * End of file: tp-link-it.c
 */

