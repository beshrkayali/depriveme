#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID {0x69, 0x5C, 0xE6, 0xFE, 0x5D, 0xC1, 0x43, 0x81, 0x85, 0x29, 0x9A, 0x82, 0xDB, 0x09, 0xA0, 0x69 }
PBL_APP_INFO(MY_UUID, "Deprive Me", "Beshr Kayali", 0, 1, RESOURCE_ID_APP_ICON , APP_INFO_STANDARD_APP);

Window window;

TextLayer titleLayer;
TextLayer minutesLayer;

AppTimerHandle timer_handle;


char *itoa(int num)
{
  static char buff[20] = {};
  int i = 0, temp_num = num, length = 0;
  char *string = buff;
  
  if(num >= 0) {
    // count how many characters in the number
    while(temp_num) {
      temp_num /= 10;
      length++;
    }
    
    // assign the number to the buffer starting at the end of the 
    // number and going to the begining since we are doing the
    // integer to character conversion on the last number in the
    // sequence
    for(i = 0; i < length; i++) {
      buff[(length-1)-i] = '0' + (num % 10);
      num /= 10;
    }
    buff[i] = '\0'; // can't forget the null byte to properly end our string
  }
  else
    return "Unsupported Number";
  
  return string;
}

// Decrease / Increase Minutes function + some other vars
const int MoveMinutesBy = 5;
const int MaxTopMin = 60;
const int MaxLowMin = 5;
static int TIMER = 25;

static int AppStatus = 1;
// 1: app main menu
// 2: app timer 

// -----

// Pulsing Function

const VibePattern custom_pattern = {
  .durations = (uint32_t []) {100, 700, 100, 200, 700, 100, 300, 100, 1000},
  .num_segments = 9
};

// Timer Vars and Functions
int pulseTimer = 5;
void handle_timer(AppContextRef ctx, AppTimerHandle handle, uint32_t cookie) {

  if (cookie == 1) { // Timer-set checker
      if (AppStatus == 2){
        text_layer_set_text(&titleLayer, "Timer Set");
        text_layer_set_font(&minutesLayer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
        text_layer_set_text(&minutesLayer, "Do Some Work!");
        timer_handle = app_timer_send_event(ctx, TIMER * 60000, 2);
      }else{
        timer_handle = app_timer_send_event(ctx, 1000, 1);
      }
  }

  if (cookie == 2) { // Timer Buzzed
      timer_handle = app_timer_send_event(ctx, 500, 3);
  }

  if (cookie == 3){ // Pulser
    if(pulseTimer > 1){
      text_layer_set_text(&titleLayer, "STAY UP!");
      vibes_enqueue_custom_pattern(custom_pattern);
      pulseTimer = pulseTimer - 1;
      timer_handle = app_timer_send_event(ctx, 500, 3);
      text_layer_set_text(&minutesLayer, itoa(pulseTimer));
    }else{
      text_layer_set_text(&titleLayer, "Timer Reset");
      text_layer_set_text(&minutesLayer, "");
      timer_handle = app_timer_send_event(ctx, TIMER * 60000, 2);
      pulseTimer = 5;
    }
  }

  // If you want the timer to run again you need to call `app_timer_send_event()`
  // again here.
}


// Modify these common button handlers

void up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  if (TIMER < MaxTopMin && AppStatus == 1){
    TIMER = TIMER + MoveMinutesBy;
    text_layer_set_text(&minutesLayer, itoa(TIMER));
  }
}


void down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {  
  if (TIMER > MaxLowMin && AppStatus == 1){
    TIMER = TIMER - MoveMinutesBy;
    text_layer_set_text(&minutesLayer, itoa(TIMER));
  }
}


void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  if(AppStatus == 1){
    AppStatus = 2;
    text_layer_set_text(&titleLayer, "Done. I'll keep you up." );  
  }
}


void select_long_click_handler(ClickRecognizerRef recognizer, Window *window) {

}


// This usually won't need to be modified

void click_config_provider(ClickConfig **config, Window *window) {

  config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) select_single_click_handler;

  config[BUTTON_ID_SELECT]->long_click.handler = (ClickHandler) select_long_click_handler;

  config[BUTTON_ID_UP]->click.handler = (ClickHandler) up_single_click_handler;
  config[BUTTON_ID_UP]->click.repeat_interval_ms = 100;

  config[BUTTON_ID_DOWN]->click.handler = (ClickHandler) down_single_click_handler;
  config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 100;
}


// Standard app initialisation

void handle_init(AppContextRef ctx) {

  window_init(&window, "Deprive Me");
  window_stack_push(&window, true /* Animated */);

  // Title
  text_layer_init(&titleLayer, GRect(0, 20, 140 /* width */, 50 /* height */));
  text_layer_set_text_alignment(&titleLayer, GTextAlignmentCenter);
  text_layer_set_text(&titleLayer, "Use Up/Down Buttons to Set Deprivation Timer (minutes):");
  text_layer_set_font(&titleLayer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
  layer_add_child(&window.layer, &titleLayer.layer);


  text_layer_init(&minutesLayer, GRect(0, 70, 144 /* width */, 85 /* height */));
  text_layer_set_text_alignment(&minutesLayer, GTextAlignmentCenter);
  text_layer_set_text(&minutesLayer, itoa(TIMER));
  text_layer_set_font(&minutesLayer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_color(&minutesLayer, GColorWhite);
  text_layer_set_background_color(&minutesLayer, GColorBlack);
  layer_add_child(&window.layer, &minutesLayer.layer);


  // Attach our desired button functionality
  window_set_click_config_provider(&window, (ClickConfigProvider) click_config_provider);

  // Start status check timer
  timer_handle = app_timer_send_event(ctx, 1000, 1);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .timer_handler = &handle_timer
  };
  app_event_loop(params, &handlers);
}
