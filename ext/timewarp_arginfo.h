/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 3bbb0837365051b9ac633b72acb7a3bedf0b73b0 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_TimeWarp_timewarp_set, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, provider, TimeWarp\\ProviderInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_TimeWarp_timewarp_now, 0, 0, DateTimeInterface, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_TimeWarp_timewarp_unset, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_TimeWarp_pdo_register_query_replacer, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pdoDriverName, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, replacer, TimeWarp\\QueryReplacerInterface, 0)
ZEND_END_ARG_INFO()

#define arginfo_TimeWarp_pdo_unregister_query_replacer arginfo_TimeWarp_pdo_register_query_replacer

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_TimeWarp_QueryReplacerInterface_transform, 0, 1, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, query, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, now, DateTimeInterface, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_TimeWarp_ProviderInterface_provide, 0, 0, DateTimeInterface, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, datetime, IS_STRING, 0, "\'now\'")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, timezone, DateTimeZone, 1, "null")
ZEND_END_ARG_INFO()


ZEND_FUNCTION(TimeWarp_timewarp_set);
ZEND_FUNCTION(TimeWarp_timewarp_now);
ZEND_FUNCTION(TimeWarp_timewarp_unset);
ZEND_FUNCTION(TimeWarp_pdo_register_query_replacer);
ZEND_FUNCTION(TimeWarp_pdo_unregister_query_replacer);


static const zend_function_entry ext_functions[] = {
	ZEND_NS_FALIAS("TimeWarp", timewarp_set, TimeWarp_timewarp_set, arginfo_TimeWarp_timewarp_set)
	ZEND_NS_FALIAS("TimeWarp", timewarp_now, TimeWarp_timewarp_now, arginfo_TimeWarp_timewarp_now)
	ZEND_NS_FALIAS("TimeWarp", timewarp_unset, TimeWarp_timewarp_unset, arginfo_TimeWarp_timewarp_unset)
	ZEND_NS_FALIAS("TimeWarp", pdo_register_query_replacer, TimeWarp_pdo_register_query_replacer, arginfo_TimeWarp_pdo_register_query_replacer)
	ZEND_NS_FALIAS("TimeWarp", pdo_unregister_query_replacer, TimeWarp_pdo_unregister_query_replacer, arginfo_TimeWarp_pdo_unregister_query_replacer)
	ZEND_FE_END
};


static const zend_function_entry class_TimeWarp_QueryReplacerInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(TimeWarp_QueryReplacerInterface, transform, arginfo_class_TimeWarp_QueryReplacerInterface_transform, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};


static const zend_function_entry class_TimeWarp_ProviderInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(TimeWarp_ProviderInterface, provide, arginfo_class_TimeWarp_ProviderInterface_provide, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};

static zend_class_entry *register_class_TimeWarp_QueryReplacerInterface(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "TimeWarp", "QueryReplacerInterface", class_TimeWarp_QueryReplacerInterface_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_TimeWarp_ProviderInterface(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "TimeWarp", "ProviderInterface", class_TimeWarp_ProviderInterface_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}
