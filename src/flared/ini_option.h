/**
 *	ini_option.h
 *
 *	@author	Masaki Fujimoto <fujimoto@php.net>
 *
 *	$Id$
 */
#ifndef __INI_OPTION_H__
#define __INI_OPTION_H__

#include "ini.h"
#include "storage.h"

namespace gree {
namespace flare {

#define	ini_option_object()			singleton<ini_option>::instance()

/**
 *	flared global configuration class
 */
class ini_option : public ini {
private:
	int					_argc;
	char**			_argv;

	string			_config_path;
	bool				_daemonize;
	string			_data_dir;
	string			_index_server_name;
	int					_index_server_port;
	string			_log_facility;
	uint32_t		_max_connection;
	int					_mutex_slot;
#ifdef ENABLE_MYSQL_REPLICATION
	bool				_mysql_replication;
	int					_mysql_replication_port;
	uint32_t		_mysql_replication_id;
	string			_mysql_replication_db;
	string			_mysql_replication_table;
#endif
	int					_proxy_concurrency;
	string			_server_name;
	int					_server_port;
	int					_stack_size;
	uint32_t		_storage_ap;
	uint64_t		_storage_bucket_size;
	int					_storage_cache_size;
	string			_storage_compress;
	bool				_storage_large;
	string			_storage_type;
	int					_thread_pool_size;
	
public:
	static const int default_index_server_port = 12120;
	static const uint32_t default_max_connection = 128;
	static const int default_mutex_slot = 64;
#ifdef ENABLE_MYSQL_REPLICATION
	static const int default_mysql_replication_port = 12122;
	static const int default_mysql_replication_id = 19790217;
#endif
	static const int default_proxy_concurrency = 2;
	static const int default_server_port = 12121;
	static const int default_stack_size = 128;
	static const uint32_t default_storage_ap = 4;
	static const uint64_t default_storage_bucket_size = 131071;
	static const int default_storage_cache_size = 65536;
	static const int default_thread_pool_size = 5;

	ini_option();
	virtual ~ini_option();

	int load();
	int reload();

	int set_args(int argc, char** argv) { this->_argc = argc; this->_argv = argv; return 0; };

	string get_config_path() { return this->_config_path; };
	bool is_daemonize() { return this->_daemonize; };
	string get_data_dir() { return this->_data_dir; };
	string get_index_server_name() { return this->_index_server_name; };
	int get_index_server_port() { return this->_index_server_port; };
	string get_log_facility() { return this->_log_facility; };
	uint32_t get_max_connection() { return this->_max_connection; };
	int get_mutex_slot() { return this->_mutex_slot; };
#ifdef ENABLE_MYSQL_REPLICATION
	bool is_mysql_replication() { return this->_mysql_replication; };
	int get_mysql_replication_port() { return this->_mysql_replication_port; };
	uint32_t get_mysql_replication_id() { return this->_mysql_replication_id; };
	string get_mysql_replication_db() { return this->_mysql_replication_db; };
	string get_mysql_replication_table() { return this->_mysql_replication_table; };
#endif
	int get_proxy_concurrency() { return this->_proxy_concurrency; };
	string get_server_name() { return this->_server_name; };
	int get_server_port() { return this->_server_port; };
	int get_stack_size() { return this->_stack_size; };
	uint32_t get_storage_ap() { return this->_storage_ap; };
	uint64_t get_storage_bucket_size() { return this->_storage_bucket_size; };
	int get_storage_cache_size() { return this->_storage_cache_size; };
	string get_storage_compress() { return this->_storage_compress; };
	bool is_storage_large() { return this->_storage_large; };
	string get_storage_type() { return this->_storage_type; };
	int get_thread_pool_size() { return this->_thread_pool_size; };

private:
	int _setup_cli_option(program_options::options_description& option);
	int _setup_config_option(program_options:: options_description& option);
};

}	// namespace flare
}	// namespace gree

#endif // __INI_OPTION_H__
// vim: foldmethod=marker tabstop=2 shiftwidth=2 autoindent
