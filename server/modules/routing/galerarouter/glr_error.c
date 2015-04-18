/*
 * This file is distributed as part of the MariaDB Corporation MaxScale.  It is free
 * software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation,
 * version 2.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Copyright MariaDB Corporation Ab 2015
 */

/**
 * @file glr.c	The Galera router entry points
 *
 * This file contains error hadling functions for the Galera router.
 *
 * @verbatim
 * Revision History
 *
 * Date			Who				Description
 * 09/04/2015	Markus Makela	Initial implementation
 * 
 * @endverbatim
 */

#include <galerarouter.h>

int retry_commit(GALERA_SESSION* ses,DCB* dcb)
{
    int rval;
    GWBUF* buffer;

    if((buffer = modutil_create_query("COMMIT")) == NULL)
    {
	return 0;
    }

    rval = dcb->func.write(dcb,buffer);
    atomic_add(&ses->conflict.n_retries,1);
    return rval;
}