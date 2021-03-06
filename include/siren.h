#ifndef SIREN_H_
#define SIREN_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef int32_t siren_status_t;
typedef int32_t siren_event_t;
typedef int32_t siren_state_t;


typedef int (*init_input_stream_t)();
typedef void (*release_input_stream_t)();
typedef void (*start_input_stream_t)();
typedef void (*stop_input_stream_t)();
typedef int (*read_input_stream_t)(char *buff, int len);
typedef void (*on_err_input_stream_t)();


typedef struct {
    init_input_stream_t init_input;
    release_input_stream_t release_input;
    start_input_stream_t start_input;
    stop_input_stream_t stop_input;
    read_input_stream_t read_input;
    on_err_input_stream_t on_err_input;
} siren_input_if_t;

typedef void (*on_voice_event_t)(int length, siren_event_t event,
                                 void *buff, int has_sl,
                                 int has_voice, double sl_degree,
                                 int has_voiceprint);

typedef struct {
    on_voice_event_t voice_event_callback;
} siren_proc_callback_t;

typedef void (*on_raw_voice_t)(int length, void *buff);

typedef struct {
    on_raw_voice_t raw_voice_callback;
} siren_raw_stream_callback_t;

typedef void (*on_siren_state_changed)(int current);

typedef struct {
    on_siren_state_changed state_changed_callback;
} siren_state_changed_callback_t;

enum {
    SIREN_STATUS_OK = 0,
    SIREN_STATUS_CONFIG_ERROR,
    SIREN_STATUS_CONFIG_NO_FOUND,
    SIREN_STATUS_ERROR
};

enum {
    SIREN_EVENT_VAD_START = 100,
    SIREN_EVENT_VAD_DATA,
    SIREN_EVENT_VAD_END,
    SIREN_EVENT_VAD_CANCEL,
    SIREN_EVENT_WAKE_VAD_START,
    SIREN_EVENT_WAKE_VAD_DATA,
    SIREN_EVENT_WAKE_VAD_END,
    SIREN_EVENT_WAKE_PRE,
    SIREN_EVENT_WAKE_NOCMD,
    SIREN_EVENT_WAKE_CMD,
    SIREN_EVENT_WAKE_CANCEL,
    SIREN_EVENT_SLEEP,
    SIREN_EVENT_HOTWORD,
    SIREN_EVENT_SR,
    SIREN_EVENT_VOICE_PRINT,
    SIREN_EVENT_DIRTY
};

enum {
    SIREN_STATE_AWAKE =1 ,
    SIREN_STATE_SLEEP
};

siren_status_t init_siren(const char *path, siren_input_if_t *input);
void start_siren_process_stream(siren_proc_callback_t *callback);
void start_siren_raw_stream(siren_raw_stream_callback_t *callback);
void stop_siren_process_stream();
void stop_siren_raw_stream();
void stop_siren_stream();
void set_siren_state(siren_state_t state, siren_state_changed_callback_t *callback);
void set_siren_steer(float ho, float ver);
void destroy_siren();
siren_status_t rebuild_vt_word_list(const char **vt_word_list);

#ifdef __cplusplus
}
#endif

#endif
