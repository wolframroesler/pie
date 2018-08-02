/*
 * Pebble Pie Watchface
 * by Wolfram Rösler 2018-07-31
 */

#include <pebble.h>
#include <math.h>

// Main window
static Window *s_main_window = NULL;

// Main watchface layer
static Layer *s_watch_layer = NULL;

// 0=production mode, 1=developer mode.
// In developer mode, the pie segments display the second
// instead of the hour to allow easier debugging.
#define DEVELOP 0

// Precomputed sine and cosine values for a given radius,
// created with precompute.py
#define RADIUS 200
static const int xoffset[] = {
    0,1,3,5,6,8,10,12,13,15,17,19,20,22,24,26,27,29,31,33,34,36,38,39,41,43,44,46,48,50,51,53,55,56,58,60,61,63,65,66,68,70,71,73,74,76,78,79,81,82,84,86,87,89,90,92,93,95,96,98,99,101,103,104,105,107,108,110,111,113,114,116,117,118,120,121,123,124,125,127,128,129,131,132,133,135,136,137,138,140,141,142,143,145,146,147,148,149,150,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,174,175,176,177,178,178,179,180,181,181,182,183,184,184,185,186,186,187,187,188,189,189,190,190,191,191,192,192,193,193,194,194,194,195,195,195,196,196,196,197,197,197,198,198,198,198,198,199,199,199,199,199,199,199,199,199,199,199,200,199,199,199,199,199,199,199,199,199,199,199,198,198,198,198,198,197,197,197,196,196,196,195,195,195,194,194,194,193,193,192,192,191,191,190,190,189,189,188,187,187,186,186,185,184,184,183,182,181,181,180,179,178,178,177,176,175,174,174,173,172,171,170,169,168,167,166,165,164,163,162,161,160,159,158,157,156,155,154,153,152,150,149,148,147,146,145,143,142,141,140,138,137,136,135,133,132,131,129,128,127,125,124,123,121,120,118,117,116,114,113,111,110,108,107,105,104,103,101,99,98,96,95,93,92,90,89,87,86,84,82,81,79,78,76,74,73,71,70,68,66,65,63,61,60,58,56,55,53,51,50,48,46,44,43,41,39,38,36,34,33,31,29,27,26,24,22,20,19,17,15,13,12,10,8,6,5,3,1,0,-1,-3,-5,-6,-8,-10,-12,-13,-15,-17,-19,-20,-22,-24,-26,-27,-29,-31,-33,-34,-36,-38,-39,-41,-43,-44,-46,-48,-50,-51,-53,-55,-56,-58,-60,-61,-63,-65,-66,-68,-70,-71,-73,-74,-76,-78,-79,-81,-82,-84,-86,-87,-89,-90,-92,-93,-95,-96,-98,-100,-101,-103,-104,-105,-107,-108,-110,-111,-113,-114,-116,-117,-118,-120,-121,-123,-124,-125,-127,-128,-129,-131,-132,-133,-135,-136,-137,-138,-140,-141,-142,-143,-145,-146,-147,-148,-149,-150,-152,-153,-154,-155,-156,-157,-158,-159,-160,-161,-162,-163,-164,-165,-166,-167,-168,-169,-170,-171,-172,-173,-174,-174,-175,-176,-177,-178,-178,-179,-180,-181,-181,-182,-183,-184,-184,-185,-186,-186,-187,-187,-188,-189,-189,-190,-190,-191,-191,-192,-192,-193,-193,-194,-194,-194,-195,-195,-195,-196,-196,-196,-197,-197,-197,-198,-198,-198,-198,-198,-199,-199,-199,-199,-199,-199,-199,-199,-199,-199,-199,-200,-199,-199,-199,-199,-199,-199,-199,-199,-199,-199,-199,-198,-198,-198,-198,-198,-197,-197,-197,-196,-196,-196,-195,-195,-195,-194,-194,-194,-193,-193,-192,-192,-191,-191,-190,-190,-189,-189,-188,-187,-187,-186,-186,-185,-184,-184,-183,-182,-181,-181,-180,-179,-178,-178,-177,-176,-175,-174,-174,-173,-172,-171,-170,-169,-168,-167,-166,-165,-164,-163,-162,-161,-160,-159,-158,-157,-156,-155,-154,-153,-152,-150,-149,-148,-147,-146,-145,-143,-142,-141,-140,-138,-137,-136,-135,-133,-132,-131,-129,-128,-127,-125,-124,-123,-121,-120,-118,-117,-116,-114,-113,-111,-110,-108,-107,-105,-104,-103,-101,-100,-98,-96,-95,-93,-92,-90,-89,-87,-86,-84,-82,-81,-79,-78,-76,-74,-73,-71,-70,-68,-66,-65,-63,-61,-60,-58,-56,-55,-53,-51,-50,-48,-46,-44,-43,-41,-39,-38,-36,-34,-33,-31,-29,-27,-26,-24,-22,-20,-19,-17,-15,-13,-12,-10,-8,-6,-5,-3,-1,
};
static const int yoffset[] = {
    -200,-199,-199,-199,-199,-199,-199,-199,-199,-199,-199,-199,-198,-198,-198,-198,-198,-197,-197,-197,-196,-196,-196,-195,-195,-195,-194,-194,-194,-193,-193,-192,-192,-191,-191,-190,-190,-189,-189,-188,-187,-187,-186,-186,-185,-184,-184,-183,-182,-181,-181,-180,-179,-178,-178,-177,-176,-175,-174,-174,-173,-172,-171,-170,-169,-168,-167,-166,-165,-164,-163,-162,-161,-160,-159,-158,-157,-156,-155,-154,-153,-152,-150,-149,-148,-147,-146,-145,-143,-142,-141,-140,-138,-137,-136,-135,-133,-132,-131,-129,-128,-127,-125,-124,-123,-121,-120,-118,-117,-116,-114,-113,-111,-110,-108,-107,-105,-104,-103,-101,-100,-98,-96,-95,-93,-92,-90,-89,-87,-86,-84,-82,-81,-79,-78,-76,-74,-73,-71,-70,-68,-66,-65,-63,-61,-60,-58,-56,-55,-53,-51,-50,-48,-46,-44,-43,-41,-39,-38,-36,-34,-33,-31,-29,-27,-26,-24,-22,-20,-19,-17,-15,-13,-12,-10,-8,-6,-5,-3,-1,0,1,3,5,6,8,10,12,13,15,17,19,20,22,24,26,27,29,31,33,34,36,38,39,41,43,44,46,48,50,51,53,55,56,58,60,61,63,65,66,68,70,71,73,74,76,78,79,81,82,84,86,87,89,90,92,93,95,96,98,99,101,103,104,105,107,108,110,111,113,114,116,117,118,120,121,123,124,125,127,128,129,131,132,133,135,136,137,138,140,141,142,143,145,146,147,148,149,150,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,174,175,176,177,178,178,179,180,181,181,182,183,184,184,185,186,186,187,187,188,189,189,190,190,191,191,192,192,193,193,194,194,194,195,195,195,196,196,196,197,197,197,198,198,198,198,198,199,199,199,199,199,199,199,199,199,199,199,200,199,199,199,199,199,199,199,199,199,199,199,198,198,198,198,198,197,197,197,196,196,196,195,195,195,194,194,194,193,193,192,192,191,191,190,190,189,189,188,187,187,186,186,185,184,184,183,182,181,181,180,179,178,178,177,176,175,174,174,173,172,171,170,169,168,167,166,165,164,163,162,161,160,159,158,157,156,155,154,153,152,150,149,148,147,146,145,143,142,141,140,138,137,136,135,133,132,131,129,128,127,125,124,123,121,120,118,117,116,114,113,111,110,108,107,105,104,103,101,100,98,96,95,93,92,90,89,87,86,84,82,81,79,78,76,74,73,71,70,68,66,65,63,61,60,58,56,55,53,51,50,48,46,44,43,41,39,38,36,34,33,31,29,27,26,24,22,20,19,17,15,13,12,10,8,6,5,3,1,0,-1,-3,-5,-6,-8,-10,-12,-13,-15,-17,-19,-20,-22,-24,-26,-27,-29,-31,-33,-34,-36,-38,-39,-41,-43,-44,-46,-48,-50,-51,-53,-55,-56,-58,-60,-61,-63,-65,-66,-68,-70,-71,-73,-74,-76,-78,-79,-81,-82,-84,-86,-87,-89,-90,-92,-93,-95,-96,-98,-100,-101,-103,-104,-105,-107,-108,-110,-111,-113,-114,-116,-117,-118,-120,-121,-123,-124,-125,-127,-128,-129,-131,-132,-133,-135,-136,-137,-138,-140,-141,-142,-143,-145,-146,-147,-148,-149,-150,-152,-153,-154,-155,-156,-157,-158,-159,-160,-161,-162,-163,-164,-165,-166,-167,-168,-169,-170,-171,-172,-173,-174,-174,-175,-176,-177,-178,-178,-179,-180,-181,-181,-182,-183,-184,-184,-185,-186,-186,-187,-187,-188,-189,-189,-190,-190,-191,-191,-192,-192,-193,-193,-194,-194,-194,-195,-195,-195,-196,-196,-196,-197,-197,-197,-198,-198,-198,-198,-198,-199,-199,-199,-199,-199,-199,-199,-199,-199,-199,-199,
};

// Find the coordinates at a certain position relative to the
// center of the watch (hrpos is 0...720)
#define POINTAT(hrpos) (GPoint){ .x = center.x + xoffset[hrpos], .y = center.y + yoffset[hrpos] }

// Configuration properties
static GColor AMColor;
static GColor PMColor;
static GColor MinuteHandColor;
static int MinuteHandWidth;

// Persistent storage keys
#define KEY_AMCOLOR 1
#define KEY_PMCOLOR 2
#define KEY_MINUTEHANDCOLOR 3
#define KEY_MINUTEHANDWIDTH 4

/*
 * Main watchface drawing function.
 */
static void watch_update_proc(Layer *layer, GContext *ctx) {
    const GRect bounds = layer_get_bounds(layer);
    GPoint center = grect_center_point(&bounds);

    const time_t now = time(NULL);
    const struct tm *const t = localtime(&now);

    // Background, part 1: From 0:00 to current hour.
    // The color is blue for day (AM, 0:00-11:59) and
    // red for night (PM, 12:00-23:59).
    GColor const piecolor = t->tm_hour < 12 ? AMColor : PMColor;
    GColor const bkcolor  = t->tm_hour < 12 ? PMColor  : AMColor;

    // Find out where the hour hand is, in half-degrees (0-720) of
    // a full circle. In other words, hrpos is the number of minutes
    // since 00:00 (AM) or 12:00 (PM).
    const int hrpos = DEVELOP
        ? t->tm_sec * 12
        : (t->tm_hour % 12) * 60 + t->tm_min;

    // Log output for emulator
    APP_LOG(APP_LOG_LEVEL_INFO,
        "[pie] Displaying %0d:%02d:%02d (hrpos %d), bounds are %dx%d-%d-%d",
        t->tm_hour,t->tm_min,t->tm_sec,
        hrpos,
        bounds.origin.x,bounds.origin.y,
        bounds.size.w,bounds.size.h
    );

    // So do it
    GPath *path;
    if (hrpos < 720 / 4) {
        // 0:00 to 3:00 (top right quadrant)
        graphics_context_set_fill_color(ctx,bkcolor);
        graphics_fill_rect(ctx,bounds,0,GCornerNone);

        graphics_context_set_fill_color(ctx,piecolor);
        GPathInfo pi = {
            .num_points = 3,
            .points = (GPoint []) {
                center,
                { center.x, -RADIUS },
                POINTAT(hrpos)
            }
        };
        path = gpath_create(&pi);
    } else if (hrpos < 720 / 2) {
        // 3:00 to 6:00 (buttom right quadrant)
        graphics_context_set_fill_color(ctx,bkcolor);
        graphics_fill_rect(ctx,bounds,0,GCornerNone);
        graphics_context_set_fill_color(ctx,piecolor);
        graphics_fill_rect(ctx,(GRect){
            .origin = { center.x, 0 },
            .size = { bounds.size.w/2, bounds.size.h/2 }
        },0,GCornerNone);

        graphics_context_set_fill_color(ctx,piecolor);
        GPathInfo pi = {
            .num_points = 3,
            .points = (GPoint []) {
                center,
                { center.x + RADIUS, center.y },
                POINTAT(hrpos)
            }
        };
        path = gpath_create(&pi);
    } else if (hrpos < 720 * 3/4) {
        // 6:00 to 9:00 (buttom left quadrant)
        graphics_context_set_fill_color(ctx,bkcolor);
        graphics_fill_rect(ctx,(GRect){
            .origin = { 0, 0 },
            .size = { bounds.size.w/2, bounds.size.h }
        },0,GCornerNone);
        graphics_context_set_fill_color(ctx,piecolor);
        graphics_fill_rect(ctx,(GRect){
            .origin = { center.x, 0 },
            .size = { bounds.size.w/2, bounds.size.h }
        },0,GCornerNone);

        graphics_context_set_fill_color(ctx,piecolor);
        GPathInfo pi = {
            .num_points = 3,
            .points = (GPoint []) {
                center,
                { center.x, center.y + RADIUS },
                POINTAT(hrpos)
            }
        };
        path = gpath_create(&pi);
    } else {
        // 9:00 to 12:00 (top left quadrant)
        graphics_context_set_fill_color(ctx,piecolor);
        graphics_fill_rect(ctx,bounds,0,GCornerNone);

        graphics_context_set_fill_color(ctx,bkcolor);
        GPathInfo pi = {
            .num_points = 3,
            .points = (GPoint []) {
                center,
                { center.x, center.y - RADIUS },
                POINTAT(hrpos)
            }
        };
        path = gpath_create(&pi);
    }

    // Draw the final segment of the background
    gpath_draw_filled(ctx, path);
    gpath_destroy(path);

    // Make sure the pie segment always goes all the way down to
    // the center of the watchface, even when it's very narrow
    if (hrpos != 0 && hrpos < 40) {
        graphics_context_set_stroke_color(ctx,piecolor);
        graphics_draw_line(ctx,center,(GPoint){ .x = center.x, .y = 0 });
    } else if (hrpos > 680) {
        graphics_context_set_stroke_color(ctx,bkcolor);
        graphics_draw_line(ctx,
            (GPoint){ .x = center.x-1, .y = center.y },
            (GPoint){ .x = center.x-1, .y = 0 });
    }

    // Now draw the minute hand
    graphics_context_set_stroke_color(ctx,MinuteHandColor);
    graphics_context_set_stroke_width(ctx,MinuteHandWidth);
    graphics_draw_line(ctx,center,POINTAT(t->tm_min*12));
}

/*
 * Tick handler (invoked once per minute).
 */
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    layer_mark_dirty(window_get_root_layer(s_main_window));
}

/*
 * Handle "save" clicked in settings dialog
 */
static void inbox_received_handler(DictionaryIterator *iter, void *context) {
    Tuple *t;

    APP_LOG(APP_LOG_LEVEL_INFO,"Processing changed settings");

    if ((t=dict_find(iter, MESSAGE_KEY_AMColor))!=NULL) {
        AMColor = GColorFromHEX(t->value->int32);
        persist_write_data(KEY_AMCOLOR, &AMColor, sizeof(AMColor));
    }

    if ((t=dict_find(iter, MESSAGE_KEY_PMColor))!=NULL) {
        PMColor = GColorFromHEX(t->value->int32);
        persist_write_data(KEY_PMCOLOR, &PMColor, sizeof(PMColor));
    }

    if ((t=dict_find(iter, MESSAGE_KEY_MinuteHandColor))!=NULL) {
        MinuteHandColor = GColorFromHEX(t->value->int32);
        persist_write_data(KEY_MINUTEHANDCOLOR, &MinuteHandColor, sizeof(MinuteHandColor));
    }

    if ((t=dict_find(iter, MESSAGE_KEY_MinuteHandWidth))!=NULL) {
        MinuteHandWidth = t->value->int32;
        persist_write_data(KEY_MINUTEHANDWIDTH, &MinuteHandWidth, sizeof(MinuteHandWidth));
    }

    // Redraw the watch face
    if (s_watch_layer) {
        layer_mark_dirty(s_watch_layer);
    }
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

    // Read persistent settings and set defaults if required
    if (persist_read_data(KEY_AMCOLOR, &AMColor, sizeof(AMColor)) != sizeof(AMColor)) {
        AMColor = GColorBlue;
    }
    if (persist_read_data(KEY_PMCOLOR, &PMColor, sizeof(PMColor)) != sizeof(PMColor)) {
        PMColor = GColorRed;
    }
    if (persist_read_data(KEY_MINUTEHANDCOLOR, &MinuteHandColor, sizeof(MinuteHandColor)) != sizeof(MinuteHandColor)) {
        MinuteHandColor = GColorWhite;
    }
    if (persist_read_data(KEY_MINUTEHANDWIDTH, &MinuteHandWidth, sizeof(MinuteHandWidth)) != sizeof(MinuteHandWidth)) {
        MinuteHandWidth = 11;
    }

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
    tick_timer_service_subscribe(
        DEVELOP ? SECOND_UNIT : MINUTE_UNIT,
        tick_handler
    );

    // Open AppMessage connection
    app_message_register_inbox_received(inbox_received_handler);
    app_message_open(128, 128);
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
