#define chk(severity, code)  __check(severity,\
			__FILE__,\
			__LINE__,\
			__builtin_return_address(0),\
			code)
#define chk_return(severity, code)\
			{chk(severity, code); return code;}


void __check(enum severity_e severity,
		const char *filename,
		int line,
		void *return_addr,
		int code);


int CHK_cnt();
const struct checker_record_s *CHK_getRecord(int idx);

