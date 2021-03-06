#include "pf/basic/string.h"
#include "pf/sys/assert.h"
#include "pf/db/define.h"

//目前查询还是存在性能上的问题，以后在想法修复

void db_query_t::clear() {
  memset(sql_str_, '\0', sizeof(sql_str_));
}

void db_query_t::parse(const char *temp, ...) {
  va_list argptr;
  va_start(argptr, temp);
  int nchars  = vsnprintf(sql_str_, 
                          sizeof(sql_str_) - 1, 
                          temp, 
                          argptr);
  int32_t sqlstr_length = static_cast<int32_t>(sizeof(sql_str_));
  va_end(argptr);
  if (-1 == nchars || sqlstr_length - 1 < nchars) {
    Assert(false);
  }
}

void db_query_t::concat(const char *temp, ...) {
  va_list argptr;
  va_start(argptr, temp);
  size_t havelength = strlen(sql_str_);
  int nchars  = vsnprintf(sql_str_ + havelength, 
                          sizeof(sql_str_) - 1 - havelength,
                          temp, 
                          argptr);
  int32_t sqlstr_length = static_cast<int32_t>(sizeof(sql_str_));
  va_end(argptr);
  if (-1 == nchars || sqlstr_length - 1 < nchars) {
    Assert(false);
  }
}

db_fetch_array_struct::db_fetch_array_struct() {
  clear();
}

pf_basic::type::variable_t *db_fetch_array_struct::get(
    int32_t row, int32_t column) {
  if (INDEX_INVALID == column || 0 == row) return nullptr;
  uint32_t columncount = static_cast<uint32_t>(keys.size());
  if (0 == columncount) return nullptr;
  uint32_t valuecount = static_cast<uint32_t>(values.size());
  uint32_t totalrow = valuecount / columncount;
  if (row > static_cast<int32_t>(totalrow)) return nullptr;
  pf_basic::type::variable_t *result = &values[(row - 1) * columncount];
  pf_basic::type::variable_t *_result = &result[column];
  return _result;
}

pf_basic::type::variable_t *db_fetch_array_struct::get(
    int32_t row, const char *key) {
  int32_t keyindex = INDEX_INVALID;
  for (uint8_t i = 0; i < keys.size(); ++i) {
    if (0 == strcmp(keys[i].string(), key)) {
      keyindex = i;
    }
  }
  pf_basic::type::variable_t *result = get(row, keyindex);
  return result;
}

uint32_t db_fetch_array_struct::size() const {
  uint32_t columncount = static_cast<uint32_t>(keys.size());
  if (0 == columncount) return 0;
  uint32_t valuecount = static_cast<uint32_t>(values.size());
  uint32_t totalrow = valuecount / columncount;
  return totalrow;
}

db_fetch_array_struct::db_fetch_array_struct(const db_fetch_array_t &object) {
  keys = object.keys;
  values = object.values;
}

db_fetch_array_struct::db_fetch_array_struct(const db_fetch_array_t *object) {
  if (object) {
    keys = object->keys;
    values = object->values;
  }
}

db_fetch_array_t &
  db_fetch_array_struct::operator = (const db_fetch_array_t &object) {
  keys = object.keys;
  values = object.values;
  return *this;
}
  
db_fetch_array_t *
  db_fetch_array_struct::operator = (const db_fetch_array_t *object) {
  if (object) {
    keys = object->keys;
    values = object->values;
  }
  return this;
}

void db_fetch_array_struct::clear() {
  values.clear();
}
