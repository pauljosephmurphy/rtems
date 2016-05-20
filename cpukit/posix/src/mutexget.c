/**
 * @file
 *
 * @brief Convert POSIX Mutex ID to local object pointer
 * @ingroup POSIXAPI
 */

/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/posix/muteximpl.h>
#include <rtems/posix/posixapi.h>

POSIX_Mutex_Control *_POSIX_Mutex_Get_interrupt_disable(
  pthread_mutex_t  *mutex,
  ISR_lock_Context *lock_context
)
{
  _POSIX_Get_object_body(
    POSIX_Mutex_Control,
    mutex,
    lock_context,
    &_POSIX_Mutex_Information,
    PTHREAD_MUTEX_INITIALIZER,
    pthread_mutex_init
  );
}
