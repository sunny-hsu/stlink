/*
 * Ugly, low performance, configurable level, logging "framework"
 */

#ifndef LOGGING_H_
#define LOGGING_H_

#ifdef  __cplusplus
extern "C" {
#endif

enum ugly_loglevel {
    UDEBUG = 90,
    UINFO  = 50,
    UWARN  = 30,
    UERROR = 20
};

#if defined(__GNUC__)
#define PRINTF_ARRT __attribute__ ((format (printf, 3, 4)))
#else
#define PRINTF_ARRT
#endif

int ugly_init(int maximum_threshold);
int ugly_log(int level, const char *tag, const char *format, ...) PRINTF_ARRT;
int ugly_libusb_log_level(enum ugly_loglevel v);

#define UGLY_LOG_FILE (strstr(__FILE__, "/") != NULL ? \
                       strrchr(__FILE__, '/')  + 1 : strstr(__FILE__, "\\") != NULL ? \
                       strrchr(__FILE__, '\\') + 1 : __FILE__)

// TODO: we need to write this in a more generic way, for now this should compile
// on visual studio (See http://stackoverflow.com/a/8673872/1836746)
#define DLOG_HELPER(format, ...)   ugly_log(UDEBUG, UGLY_LOG_FILE, format, __VA_ARGS__)
#define DLOG(...) ugly_log(UDEBUG, UGLY_LOG_FILE, __VA_ARGS__)
#define ILOG_HELPER(format, ...)   ugly_log(UINFO, UGLY_LOG_FILE, format, __VA_ARGS__)
#define ILOG(...) ugly_log(UINFO, UGLY_LOG_FILE, __VA_ARGS__)
#define WLOG_HELPER(format, ...)   ugly_log(UWARN, UGLY_LOG_FILE, format, __VA_ARGS__)
#define WLOG(...) ugly_log(UWARN, UGLY_LOG_FILE, __VA_ARGS__)
#define ELOG_HELPER(format, ...)   ugly_log(UERROR, UGLY_LOG_FILE, format, __VA_ARGS__)
#define ELOG(...) ugly_log(UERROR, UGLY_LOG_FILE, __VA_ARGS__)

#ifdef  __cplusplus
}
#endif

#endif  // LOGGING_H_
