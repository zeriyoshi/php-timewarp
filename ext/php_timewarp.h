/*
  +----------------------------------------------------------------------+
  | Timewarp                                                             |
  +----------------------------------------------------------------------+
  | Copyright (c) Go Kudo                                                |
  | Copyright (c) The PHP Group                                          |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Go Kudo <zeriyoshi@gmail.com>                                |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_TIMEWARP_H
# define PHP_TIMEWARP_H

# include "ext/date/php_date.h"

extern zend_module_entry timewarp_module_entry;
# define phpext_timewarp_ptr &timewarp_module_entry

# define PHP_TIMEWARP_VERSION "0.0.1"

ZEND_BEGIN_MODULE_GLOBALS(timewarp)
	HashTable *pdo_filter_map;
  zend_object *intern;
  zend_function *provider;
ZEND_END_MODULE_GLOBALS(timewarp)

ZEND_EXTERN_MODULE_GLOBALS(timewarp)

# define TIMEWARP_G(v)	ZEND_MODULE_GLOBALS_ACCESSOR(timewarp, v)

# if defined(ZTS) && defined(COMPILE_DL_TIMEWARP)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_TIMEWARP_H */
