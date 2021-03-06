#include "pf/basic/global.h"
#include "pf/basic/type/variable.h"
#include "pf/net/connection/config.h"
#include "pf/script/config.h"
#include "pf/db/config.h"
#include "pf/basic/util.h"

/**
 * GLOBALS["app.basepath"] = string;              //default the exe file path.
 * GLOBALS["app.name"] = string;                  //default "".
 * GLOBALS["app.status"] = number;                //default kAppStatusStop.
 * GLOBALS["app.cmdmodel"] = number;              //default 0.
 * GLOBALS["log.active"] = bool;                  //default true.
 * GLOBALS["log.directory"] = number;             //default the exe file path with "/log".
 * GLOBALS["log.singlefile"] = bool;              //default false.
 * GLOBALS["log.fast"] = bool;                    //default true.
 * GLOBALS["log.print"] = bool;                   //default true.
 * GLOBALS["log.clear"] = bool;                   //default false.
 * GLOBALS["thread.collects"] = number;           //default 0.
 * GLOBALS["default.engine.frame"] = number;      //default 100.
 * GLOBALS["default.net.open"] = bool;            //default false.
 * GLOBALS["default.net.service"] = bool;         //default false.
 * GLOBALS["default.net.service_ip"] = string;    //default "".
 * GLOBALS["default.net.service_port"] = number;  //default 0.
 * GLOBALS["default.net.conn_max"] = number;      //default NET_CONNECTION_MAX.
 * GLOBALS["default.script.open"] = bool;         //default false.
 * GLOBALS["default.script.rootpath"] = string;   //default SCRIPT_ROOT_PATH.
 * GLOBALS["default.script.workpath"] = string;   //default SCRIPT_WORK_PATH.
 * GLOBALS["default.script.bootstrap"] = string;  //default "bootstrap.lua".
 * GLOBALS["default.script.type"] = number;       //default pf_script::kTypeLua.
 * GLOBALS["default.cache.open"] = bool;          //default fasle.
 * GLOBALS["default.cache.service"] = bool;       //default fasle.
 * GLOBALS["default.cache.conf"] = string;        //default "".
 * GLOBALS["default.cache.key_map"] = number;     //default ID_INVALID.
 * GLOBALS["default.cache.recycle_map"] = number; //default ID_INVALID.
 * GLOBALS["default.cache.query_map"] = number;   //default ID_INVALID.
 * GLOBALS["default.db.open"] = bool;             //default fasle.
 * GLOBALS["default.db.type"] = number;           //default kDBConnectorTypeODBC.
 * GLOBALS["default.db.server"] = string;         //default "".
 * GLOBALS["default.db.user"] = string;           //default "".
 * GLOBALS["default.db.password"] = string;       //default "".
 **/
namespace pf_basic {

void set_base_path(type::variable_set_t &g) {
  using namespace pf_basic::util;
  char app_basepath[FILENAME_MAX]{0};
  char exe_filepath[FILENAME_MAX]{0};
  get_module_filename(exe_filepath, sizeof(exe_filepath));
  path_tounix(exe_filepath, sizeof(exe_filepath));
  dirname(exe_filepath, app_basepath);
  if ('\0' == app_basepath[0]) {
    snprintf(app_basepath, sizeof(app_basepath) - 1, "%s", "./");
  }
  complementpath(app_basepath, sizeof(app_basepath));
  g["app.basepath"] = app_basepath;
}

void set_default_globals(type::variable_set_t &g) {
  
  if (g["globals"] == true) return;

  set_base_path(g);
  g["app.name"] = "";
  g["app.status"] = kAppStatusStop;
  g["app.cmdmodel"] = 0;

  g["log.active"] = true;
  g["log.directory"] = g["app.basepath"];
  g["log.directory"] += "log";
  g["log.singlefile"] = false;
  g["log.fast"] = true;
  g["log.print"] = true;
  g["log.clear"] = false;

  g["thread.collects"] = 0;

  g["default.engine.frame"] = 100;
  g["default.net.open"] = false;
  g["default.net.service"] = false;
  g["default.net.service_ip"] = "";
  g["default.net.service_port"] = 0;
  g["default.net.conn_max"] = NET_CONNECTION_MAX;
  g["default.script.open"] = false;
  g["default.script.rootpath"] = SCRIPT_ROOT_PATH;
  g["default.script.workpath"] = SCRIPT_WORK_PATH;
  g["default.script.bootstrap"] = "bootstrap.lua";
  g["default.script.type"] = pf_script::kTypeLua;
  g["default.cache.open"] = false;
  g["default.cache.service"] = false;
  g["default.cache.conf"] = "";
  g["default.cache.key_map"] = ID_INVALID;
  g["default.cache.recycle_map"] = ID_INVALID;
  g["default.cache.query_map"] = ID_INVALID;
  g["default.db.open"] = false;
  g["default.db.type"] = kDBConnectorTypeODBC;
  g["default.db.server"] = "";
  g["default.db.user"] = "";
  g["default.db.password"] = "";

  //The set flag.
  g["globals"] = true;
}

type::variable_set_t &get_globals() {
  static type::variable_set_t vars;
  set_default_globals(vars);
  return vars;
}

}; //namespace pf_basic
