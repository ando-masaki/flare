/**
 *	handler_request.cc
 *	
 *	implementation of gree::flare::handler_request
 *
 *	@author	Masaki Fujimoto <fujimoto@php.net>
 *	
 *	$Id$
 */
#include "handler_request.h"

namespace gree {
namespace flare {

// {{{ ctor/dtor
/**
 *	ctor for handler_request
 */
handler_request::handler_request(shared_thread t, shared_connection c):
		thread_handler(t),
		_connection(c) {
}

/**
 *	dtor for handler_request
 */
handler_request::~handler_request() {
}
// }}}

// {{{ operator overloads
// }}}

// {{{ public methods
/**
 *	run thread proc
 */
int handler_request::run() {
	this->_thread->set_peer(this->_connection->get_host(), this->_connection->get_port());

	for (;;) {
		this->_thread->set_state("wait");
		this->_thread->set_op("");

		op* p = op_parser::parse_server<op_parser_binary_index, op_parser_text_index>(this->_connection);
		if (p == NULL) {
			this->_thread->set_state("shutdown");
			if (this->_thread->is_shutdown_request()) {
				log_info("thread shutdown request -> breaking loop", 0);
			} else {
				log_warning("something is going wrong while parsing request -> breaking loop", 0);
			}
			break;
		}

		p->set_thread(this->_thread);
		this->_thread->set_state("accept");
		this->_thread->set_op(p->get_ident());

		p->run_server();

		if (p->is_shutdown_request()) {
			this->_thread->set_state("shutdown");
			log_info("session shutdown request -> breaking loop", 0);
			_delete_(p);
			break;
		}

		_delete_(p);

		if (this->_thread->is_shutdown_request()) {
			this->_thread->set_state("shutdown");
			log_info("thread shutdown request -> breaking loop", 0);
			break;
		}
	}

	return 0;
}
// }}}

// {{{ protected methods
// }}}

// {{{ private methods
// }}}

}	// namespace flare
}	// namespace gree

// vim: foldmethod=marker tabstop=2 shiftwidth=2 autoindent
