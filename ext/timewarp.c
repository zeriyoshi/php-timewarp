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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"

#include "ext/date/php_date.h"
#include "ext/pdo/php_pdo_driver.h"

#include "Zend/zend_hash.h"

#include "php_timewarp.h"
#include "timewarp_arginfo.h"

ZEND_DECLARE_MODULE_GLOBALS(timewarp);

PHPAPI zend_class_entry *timewarp_ce_TimeWarp_QueryReplacerInterface;

PHP_FUNCTION(TimeWarp_timewarp_set)
{
	zend_object *obj = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(obj, php_date_get_interface_ce())
	ZEND_PARSE_PARAMETERS_END();

	TIMEWARP_G(fake) = php_date_obj_from_obj(obj);
}

PHP_FUNCTION(TimeWarp_timewarp_unset)
{
	TIMEWARP_G(fake) = NULL;

	ZEND_PARSE_PARAMETERS_NONE();
}

PHP_FUNCTION(TimeWarp_pdo_register_query_replacer)
{
	zend_string *drv = NULL;
	zend_object *obj = NULL;
	zend_function *transform = NULL, *cur = NULL;
	HashTable *tbl;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(drv)
		Z_PARAM_OBJ_OF_CLASS(obj, timewarp_ce_TimeWarp_QueryReplacerInterface)
	ZEND_PARSE_PARAMETERS_END();

	// transform = zend_hash_find_ptr(&obj->ce->function_table, ZSTR_INIT_LITERAL("transform", true));
	// ZEND_ASSERT(transform != NULL);

	// tbl = zend_hash_find_ptr(TIMEWARP_G(ftable), drv);
	// if (tbl == NULL) {
	// 	zend_hash_add_empty_element(TIMEWARP_G(ftable), drv);
	// 	tbl = zend_hash_find_ptr(TIMEWARP_G(ftable), drv);
	// }

	// zend_hash_next_index_insert_ptr(tbl, transform);
}

PHP_FUNCTION(TimeWarp_pdo_unregister_query_replacer)
{
	zend_string *drv = NULL;
	zend_object *obj = NULL;
	zend_function *transform = NULL;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(drv)
		Z_PARAM_OBJ_OF_CLASS(obj, timewarp_ce_TimeWarp_QueryReplacerInterface)
	ZEND_PARSE_PARAMETERS_END();
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(timewarp)
{
#if defined(ZTS) && defined(COMPILE_DL_TIMEWARP)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(timewarp)
{
	/* \TimeWarp\QueryReplacerInterface */
	timewarp_ce_TimeWarp_QueryReplacerInterface = register_class_TimeWarp_QueryReplacerInterface();
}
/* }}} */

/* {{{ PHP_GINIT_FUNCTION */
PHP_GINIT_FUNCTION(timewarp)
{
	timewarp_globals->fake = NULL;
	ALLOC_HASHTABLE(timewarp_globals->ftable);
	zend_hash_init(timewarp_globals->ftable, 1, NULL, NULL, 1);
}
/* }}} */

/* {{{ timewarp_module_entry */
zend_module_entry timewarp_module_entry = {
	STANDARD_MODULE_HEADER,
	"timewarp",
	ext_functions,
	PHP_MINIT(timewarp),
	NULL,
	PHP_RINIT(timewarp),
	NULL,
	NULL,
	PHP_TIMEWARP_VERSION,
	PHP_MODULE_GLOBALS(timewarp),
	PHP_GINIT(timewarp),
	NULL,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};
/* }}} */

#ifdef COMPILE_DL_TIMEWARP
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(timewarp)
#endif
