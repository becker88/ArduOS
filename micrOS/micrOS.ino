#include "DeviceTree.h"
#include "Kern_Errors.h"
#include "micrOS_Apps.h"
#include "micrOS_Graphics_Cache.h"
#include <Vcc.h>
#include "micrOS_Power_Management.h"
#include <SD.h>
#include "micrOS_Storage.h"
#include "Kernel_Returns.h"
#include "Stage2Bootloader.h"
#include <avr/wdt.h>
#include "kernel.h"
#include "IODisplay.h"
#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <Flash.h>
#include <avr/boot.h>
#include <EEPROM.h>
#include "DeviceTree.h"
#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include <MCUFRIEND_kbv.h>
extern MCUFRIEND_kbv IODisplay;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 200); //Touch Panel initialization

void setup() {
	wdt_reset();
	boot_verbose();
	micrOS_SwitchBoard();
	int i;
	int unoSerial[6];
	int startAddr = 1018;
	unsigned long serno = 0;

	for (i = 0; i < 6; i++) {
		unoSerial[i] = EEPROM.read(startAddr + i);
	}
}

// the loop function runs over and over again until power down or reset
void loop() {
	wdt_reset(); // Reset the watchdog
	TSPoint p = ts.getPoint();
	AWAIT_TOUCH_SG();
	if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
		Serial.print(F("[TouchEvent] Registered touch at X = ")); Serial.print(p.x); Serial.print(F(" | Y = ")); Serial.println(p.y);
		if (p.x>899 && p.x<942 && p.y>852 && p.y<900 && inApp == 0) {
			Serial.println("[OverlaySwitchEvent] Menu has been launched.");
			menu_init();
		}
		else if (p.x>875 && p.x<894 && p.y>907 && p.y<942 && inApp == 1) {
			
		}
		else if (p.x>457 && p.x<420 && p.y>450 && p.y<870 && isMenuOpen == true) {
			//
		}
		else if (p.x>450 && p.x<495 && p.y>788 && p.y<860 && isMenuOpen == true) {
			Serial.print("\nTerminal App launched.");
			AWAIT_TOUCH_SG();
			inApp = 1;
			//terminal_app();
		}
	}
	else if (p.x>317 && p.x<344 && p.y>454 && p.y<342 && isMenuOpen == true) {
		Serial.print("\nMenu Close button pressed.");
		IODisplay.fillRect(44, 53, 396, 172, TestMenuBG);
		switchboard_set_wallpaper();
		isMenuOpen = false;
		AWAIT_TOUCH_SG();
	}
	else if (p.x>458 && p.x<335 && p.y>262 && p.y<452 && SysSdutDownReqConfirm == true) {
		Serial.print("\nShutdown Pop-up Close button pressed.");
		SysSdutDownReqConfirm = false;
		AWAIT_TOUCH_SG();
		IODisplay.fillRect(44, 53, 450, 172, TestMenuBG);
		switchboard_set_wallpaper();

	}
	else if (p.x>858 && p.x<905 && p.y>216 && p.y<260 && inApp == false) {
		Serial.print("\nShutdown button pressed.");
		AWAIT_TOUCH_SG();
		isMenuOpen = false;
		SysSdutDownReqConfirm = true;
		shutdown();
	}
	else if (p.x>710 && p.x<760 && p.y>297 && p.y<870 && SysSdutDownReqConfirm == true) {
		Serial.print("\nShutdown button pressed.");
		sleepNow();
		AWAIT_TOUCH_SG();

	}
	else if (p.x>458 && p.x<335 && p.y>262 && p.y<452 && low_battery_popup == true) {
		Serial.print("\nClose button pressed.");
		IODisplay.fillRect(44, 53, 396, 172, TestMenuBG);
		switchboard_set_wallpaper();
		low_battery_popup = false;
		AWAIT_TOUCH_SG();

	}
	else if (p.x>458 && p.x<335 && p.y>262 && p.y<452 && isMenuOpen == true) {
		Serial.print("\nMenu Close button pressed.");
		IODisplay.fillRect(44, 53, 396, 172, TestMenuBG);
		switchboard_set_wallpaper();
		isMenuOpen = false;
		AWAIT_TOUCH_SG();

	}
	else if (p.x>861 && p.x<895 && p.y>329 && p.y<369 && inApp == false) {
		Serial.println("\nLaunching Terminal app...\n");
		inApp = 1;
		isMenuOpen = false;
		//terminal_app();
		AWAIT_TOUCH_SG();

	}
	else if (p.x>391 && p.x<453 && p.y>453 && p.y<520 && isMenuOpen == true) {
		
		// Claculator ->
	}

}
