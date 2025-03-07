/*
 * @author		Ian M. Fink
 *
 * @file		tcpopen.c
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
 * with this program.  If not, please see: https://www.gnu.org/licenses
 */

/*
 * Includes
 */

#include	<stdio.h>

#include	"netdefs.h"
#include	"tcpopen.h"

#include	<netdb.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<strings.h>

/*
 * Macros
 */

#ifndef	INADDR_NONE
#define	INADDR_NONE	0xffffffff	/* should be in <netinet/in.h> */
#endif

#define err_ret(format, ...)	(printf(format, ## __VA_ARGS__))

/*
 * The following globals are available to the caller, if desired.
 */

struct sockaddr_in	tcp_srv_addr;	/* server's Internet socket addr */
struct servent		tcp_serv_info;	/* from getservbyname() */
struct hostent		tcp_host_info;	/* from gethostbyname() */

/**************************************************************/

/**
 * Name:	tcp_open
 *
 * @brief	opens a TCP socket to a network host
 *
 * @param	host	a pointer to a string with the host name
 *					or IP address.
 * @param	service	a pointer to a string with the name of
 *					the service being requested.
 * @param	port	an integer of the TCP port.
 *
 * @return	a file descriptor of the socket connection to the
 *			network host or -1 if there is an error.
 */

int			/* return socket descriptor if OK, else -1 on error */
tcp_open(
	char	*host,		/* name or dotted-decimal addr of other system */
	char	*service,	/* name of service being requested */
			/* can be NULL, iff port > 0 */
	int	port)		/* if == 0, nothing special - use port# of service */
			/* if < 0, bind a local reserved port */
			/* if > 0, it's the port# of server (host-byte-order) */
{
	int				fd, resvport;
	unsigned long	inaddr;
/*	char			*host_err_str(); */
	struct servent	*sp;
	struct hostent	*hp;

	/*
	 * Initialize the server's Internet address structure.
	 * We'll store the actual 4-byte Internet address and the
	 * 2-byte port# below.
	 */

	bzero((void *) &tcp_srv_addr, sizeof(tcp_srv_addr));
	tcp_srv_addr.sin_family = AF_INET;

	tcp_srv_addr.sin_port = htons(port);

	/* 
	 * First try to convert the host name as a dotted-decimal number.
	 * Only if that fails do we call gethostbyname().
	 */

	if ((inaddr = inet_addr(host)) != INADDR_NONE) { /* it's dotted-decimal */
		bcopy((void *) &inaddr, (char *) &tcp_srv_addr.sin_addr, sizeof(inaddr));
		tcp_host_info.h_name = NULL;

	} else {
		if ((hp = gethostbyname(host)) == NULL) {
			err_ret("tcp_open: host name error: %s %s", host, "" /* host_err_str() */);
			return(-1);
		}
		tcp_host_info = *hp;	/* found it by name, structure copy */
		bcopy(hp->h_addr, (char *) &tcp_srv_addr.sin_addr, hp->h_length);
	}

	if (port >= 0) {
		if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			err_ret("tcp_open: can't create TCP socket");
			return(-1);
		}

	} else if (port < 0) {
		resvport = IPPORT_RESERVED - 1;
		if ((fd = rresvport(&resvport)) < 0) {
			err_ret("tcp_open: can't get a reserved TCP port");
			return(-1);
		}
	}

	/*
	 * Connect to the server.
	 */

	if (connect(fd, (struct sockaddr *) &tcp_srv_addr,
			sizeof(tcp_srv_addr)) < 0) {
		err_ret("tcp_open: can't connect to server");
		close(fd);
		return(-1);
	}

	return(fd);	/* all OK */
} /* tcp_open */

/*
 * End of file: tcpopen.c
 */

