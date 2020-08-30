#ifndef _VALUE_H
#define _VALUE_H
#include "type.h"

/**
 * TODO:
 * this code is of terrible quality
 */

typedef union _ValueAny Any;
typedef struct _Value Value;

union _ValueAny {
    unsigned char _uchar;
    char _char;
    unsigned short _ushort;
    short _short;
    unsigned int _uint;
    int _int;
    unsigned long _ulong;
    long _long;
    bool _bool;
    float _float;
    double _double;
    void *_pointer;
    Type _type;
};

struct _Value {
    union _ValueAny val;
    struct {
        bool is_set : 1;
        Type type   : 63;
    };
};

#define any(x) _Generic((x), \
                unsigned char: (Any) { ._uchar = (x) },\
                char: (Any) { ._char = (x) },\
                unsigned short: (Any) { ._ushort = (x) },\
                short: (Any) { ._short = (x) },\
                unsigned int: (Any) { ._uint = (x) },\
                int: (Any) { ._int = (x) },\
                unsigned long: (Any) { ._ulong = (x) },\
                long: (Any) { ._long = (x) },\
                bool: (Any) { ._bool = (x) },\
                float: (Any) { ._float = (x) },\
                double: (Any) { ._double = (x) },\
                void *: (Any) { ._pointer = (x) },\
                Type: (Any) { ._type = (x) })

#define value_create(type_id) ((Value) { .type = type_id, .is_set = false, .val = any(0) })

#define value_init(v) ((Value) { .type = (_Generic((v), \
                unsigned char: TYPE_UCHAR,\
                char: TYPE_CHAR,\
                unsigned short: TYPE_USHORT,\
                short: TYPE_SHORT,\
                unsigned int: TYPE_UINT,\
                int: TYPE_INT,\
                unsigned long: TYPE_ULONG,\
                long: TYPE_LONG,\
                bool: TYPE_BOOL,\
                float: TYPE_FLOAT,\
                double: TYPE_DOUBLE,\
                void *: TYPE_POINTER)), .is_set = true, .val = any(v) })

Value *value_new (Type type);

#define value_set(self, tval, val) value_set_typed(self,tval,any(val))

#define value_set_value(self, value) value_set_typed(self,value->type,value->val)

void value_set_typed (Value *self, Type vtype, Any any);

Any value_get_typed (Value *self, Type rtype);

#endif
