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
#include "ext/standard/php_var.h"

#include "Zend/zend_hash.h"

#include "php_timewarp.h"
#include "timewarp_arginfo.h"

ZEND_DECLARE_MODULE_GLOBALS(timewarp);

PHPAPI zend_class_entry *timewarp_ce_TimeWarp_QueryReplacerInterface;
PHPAPI zend_class_entry *timewarp_ce_TimeWarp_ProviderInterface;

static void timewarp_provider_cleanup(void)
{
	if (TIMEWARP_G(intern)) {
		GC_DELREF(TIMEWARP_G(intern));
		TIMEWARP_G(intern) = NULL;
	}

	TIMEWARP_G(provider) = NULL;
}

static bool timewarp_provider_provide_interface(zval *retval)
{
	if (!TIMEWARP_G(intern) || !TIMEWARP_G(provider)) {
		return false;
	}

	zend_call_known_instance_method_with_0_params(
		TIMEWARP_G(provider),
		TIMEWARP_G(intern),
		retval
	);

	return true;
}

PHP_FUNCTION(TimeWarp_timewarp_set)
{
	zend_object *intern = NULL;
	zend_function *provider = NULL;
	zend_string *method_name = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(intern, timewarp_ce_TimeWarp_ProviderInterface)
	ZEND_PARSE_PARAMETERS_END();

	method_name = ZSTR_INIT_LITERAL("provide", 0);
	provider = zend_hash_find_ptr(&intern->ce->function_table, method_name);
	zend_string_release(method_name);
	if (UNEXPECTED(!provider)) {
		/* TODO: Illeg */
		return;
	}

	timewarp_provider_cleanup();

	GC_ADDREF(intern);
	TIMEWARP_G(intern) = intern;
	TIMEWARP_G(provider) = provider;
}

PHP_FUNCTION(TimeWarp_timewarp_now)
{
	ZEND_PARSE_PARAMETERS_NONE();

	if (!timewarp_provider_provide_interface(return_value)) {
		RETURN_NULL();
	}
}

PHP_FUNCTION(TimeWarp_timewarp_unset)
{
	ZEND_PARSE_PARAMETERS_NONE();

	timewarp_provider_cleanup();
}

PHP_FUNCTION(TimeWarp_pdo_register_query_replacer)
{
	zend_string *driver_name = NULL;
	zend_object *intern = NULL;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(driver_name)
		Z_PARAM_OBJ_OF_CLASS(intern, timewarp_ce_TimeWarp_QueryReplacerInterface)
	ZEND_PARSE_PARAMETERS_END();
}

PHP_FUNCTION(TimeWarp_pdo_unregister_query_replacer)
{
	zend_string *driver_name = NULL;
	zend_object *intern = NULL;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(driver_name)
		Z_PARAM_OBJ_OF_CLASS(intern, timewarp_ce_TimeWarp_QueryReplacerInterface)
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
	/* \TimeWarp\ProviderInterface */
	timewarp_ce_TimeWarp_ProviderInterface = register_class_TimeWarp_ProviderInterface();
}
/* }}} */

/* {{{ PHP_GINIT_FUNCTION */
PHP_GINIT_FUNCTION(timewarp)
{
	ALLOC_HASHTABLE(timewarp_globals->pdo_filter_map);
	zend_hash_init(timewarp_globals->pdo_filter_map, 1, NULL, NULL, 1);
	timewarp_globals->provider = NULL;
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
