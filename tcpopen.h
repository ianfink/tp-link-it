/*
 * @author		Ian M. Fink
 *
 * @file		tcpopen.h
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

#ifndef _H_TCPOPEN_
#define _H_TCPOPEN_

#include <stdio.h>
#include <unistd.h>

int tcp_open(
	char    *host,		/* name or dotted-decimal addr of other system */
	char    *service,	/* name of service being requested */
						/* can be NULL, iff port > 0 */
	int     port);		/* if == 0, nothing special - use port# of service */
	/* if < 0, bind a local reserved port */
	/* if > 0, it's the port# of server (host-byte-order) */

#endif /* _H_TCPOPEN_ */

/*
 * End of file: tcpopen.h
 */

