/*
 * Pebble Pie Watchface
 * by Wolfram Rösler 2018-07-31
 */

#include <pebble.h>

// Main window
static Window *s_main_window = NULL;

// Main watchface layer
static Layer *s_watch_layer = NULL;

/*
 * Main watchface drawing function.
 */
static void watch_update_proc(Layer *layer, GContext *ctx) {
    const GRect bounds = layer_get_bounds(layer);
    const GPoint center = grect_center_point(&bounds);

    const time_t now = time(NULL);
    const struct tm *const t = localtime(&now);
}

/*
 * Tick handler (invoked once per minute).
 */
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    layer_mark_dirty(window_get_root_layer(s_main_window));
}

static void main_window_load(Window *window) {
    // Get information about the Window
    Layer *const window_layer = window_get_root_layer(window);
    const GRect bounds = layer_get_bounds(window_layer);

    // Create the TextLayer with specific bounds
    s_watch_layer = layer_create(bounds);
    layer_set_update_proc(s_watch_layer, watch_update_proc);
    layer_add_child(window_layer, s_watch_layer);
}

static void main_window_unload(Window *window) {

    // Destroy the watchface layer
    layer_destroy(s_watch_layer);
}

static void init() {

    // Create main Window element and assign to pointer
    s_main_window = window_create();

    // Set handlers to manage the elements inside the Window
    window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
    });

    // Show the Window on the watch, with animated=true
    window_stack_push(s_main_window, true);

    // Register with TickTimerService
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {

    // Destroy Window
    window_destroy(s_main_window);
}

int main(void) {
    init();
    app_event_loop();
    deinit();
}
