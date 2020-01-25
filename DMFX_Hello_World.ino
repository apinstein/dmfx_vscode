#include <dreammakerfx.h>

/*
This is a basic looper pedal that uses the route_control() function to pass the tapped
loop length along to an echo effect. The echo effect is set to 1/4 the lenght of the loop
so each time a new loop is set, the echo time is updated to.

                +--------+    +-----------+
                |        |    |           |
                |        |    |           |
Instr In +----->+ Looper +--->+   Delay   +-----> Amp Out
                |        |    |           |
                |        |    |           |
                +---+----+    +------+----+
                    |                ^
                    +----------------+
                        loop length
 
 */

fx_looper   loopy( 0.8,   // Dry mix
                   0.8,   // Looped audio mix
                   12,    // Max loop length in seconds
                   false); // Disable FX processing as audio enters the loop

fx_delay    echo(3000,    // Max lenght of 3 seconds
                 0.7 );   // Feedback of 0.7

void setup() {
  
  // put your setup code here, to run once:
  pedal.init();

  // for template, just pass audio from input to output jack
  pedal.route_audio(pedal.instr_in, loopy.input);
  pedal.route_audio(loopy.output, echo.input);
  pedal.route_audio(echo.output, pedal.amp_out);

  // Connect the tapped loop length of our looper to the delay size and divide by 1/4 and convert to milliseconds (so four echoes per loop)
  pedal.route_control(loopy.loop_length_seconds, 
                      echo.length_ms, 
                      250.0,        // Scale by 1000 * 1/4 (convert to ms and then divide by 4 so we get four echoes)
                      0);           // Offset = 0

  // Optional code to print out the routing details to console
  if (true) {
    pedal.print_instance_stack();
    pedal.print_routing_table();
    pedal.print_param_tables();
  }
  
  // Run this effect
  pedal.run();

  // Disable echo initially
  echo.bypass();

}
  
void loop() {

  // Add an event if pot 0 has changed
  if (pedal.pot_0.has_changed()) { 
  } 

  // Add an event if pot 0 has changed
  if (pedal.pot_1.has_changed()) { 
  } 

  #if 0
    // Add an event if pot 2 has changed (DOESN'T WORK ON FIRST GEN HARDWARE YET)
    if (pedal.pot_2.has_changed()) { 
    } 
  #endif   

  // Service 
  pedal.service();
}

// Footswitch 1 - typically used for enable/bypass
void footswitch_1_pressed() { 
  
  // Declared as static so state is preserved between calls
  static bool bypassed = false;

  // Bypass code
  if (bypassed) {
    // If we are currently bypassed, switch pedal to active mode and turn on LED next to SW1
    pedal.enable_fx();
    digitalWrite(PIN_FOOTSW_LED_1, HIGH); // Turn on LED
  } else {
    // If we are currently active, switch pedal to bypassed mode and turn off LED next to SW1
    pedal.bypass_fx();
    digitalWrite(PIN_FOOTSW_LED_1, LOW);  // Turn off LED
  }
  bypassed = !bypassed; // Toggle bypassed state variable
}

// Footswitch 2 - used to trigger loop
void footswitch_2_pressed() {

  static bool looping = false;

  if (!looping) {
    loopy.start_loop_recording();
    Serial.println("\nLoop recording");
    digitalWrite(PIN_FOOTSW_LED_2, HIGH); // Turn on LED
  } else {
    loopy.stop_loop_recording();
    Serial.println("\nLoop recording complete");
    digitalWrite(PIN_FOOTSW_LED_2, LOW); // Turn off LED
    echo.enable();
  }

  looping = !looping;
}
