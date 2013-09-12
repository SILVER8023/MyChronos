// *************************************************************************************************
//
//      Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
//
//
//        Redistribution and use in source and binary forms, with or without
//        modification, are permitted provided that the following conditions
//        are met:
//
//          Redistributions of source code must retain the above copyright
//          notice, this list of conditions and the following disclaimer.
//
//          Redistributions in binary form must reproduce the above copyright
//          notice, this list of conditions and the following disclaimer in the
//          documentation and/or other materials provided with the
//          distribution.
//
//          Neither the name of Texas Instruments Incorporated nor the names of
//          its contributors may be used to endorse or promote products derived
//          from this software without specific prior written permission.
//
//        THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//        "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//        LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//        A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//        OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//        SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//        LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//        DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//        THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//        (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//        OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// *************************************************************************************************
// Wireless Update functions.
// *************************************************************************************************


// *************************************************************************************************
// Include section

// system
#include "project.h"

// driver
#include "display.h"
#include "ports.h"
#include "temperature.h"
#include "altitude.h"

// logic
//#include "rfbsl.h"
//#include "bluerobin.h"
//#include "rfsimpliciti.h"

// *************************************************************************************************
// Global Variable section
u8 reset_button_confirmation;

// *************************************************************************************************
// @fn          sx_rfbsl
// @brief       This functions starts the RFBSL
// @param       line            LINE1, LINE2
// @return      none
// *************************************************************************************************
void sx_reset(u8 line)
{
    reset_button_confirmation++;

    if (reset_button_confirmation == 2)
    {
        // Before entering RFBSL clear the LINE1 Symbols
//        display_symbol(LCD_SYMB_AM, SEG_OFF);

//        clear_line(LINE2);

        // Write RAM to indicate we will be downloading the RAM Updater first
    	display_chars(LCD_SEG_L2_5_0, (u8 *) "  DONE", SEG_ON);

        // Reset Values
        sTemp.tempMax=999;
        sTemp.tempMin=999;
        sAlt.altMax=9999;
        sAlt.altMin=9999;

        reset_button_confirmation=0;
    }
}

// *************************************************************************************************
// @fn          display_rfbsl
// @brief       RFBSL display routine.
// @param       u8 line                 LINE2
//                              u8 update               DISPLAY_LINE_UPDATE_FULL
// @return      none
// *************************************************************************************************
void display_reset(u8 line, u8 update)
{
    if (update == DISPLAY_LINE_UPDATE_FULL)
    {
        if (reset_button_confirmation == 0)
        {
        	display_chars(LCD_SEG_L2_5_0, (u8 *) " RESET", SEG_ON);
        }
        else if (reset_button_confirmation < 2)
        {
            // Request one more button press to confirm rfBSL call
            display_chars(LCD_SEG_L2_5_0, (u8 *) " CONF", SEG_ON);
        }
    }
}

