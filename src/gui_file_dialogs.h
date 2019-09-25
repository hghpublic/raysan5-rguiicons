/*******************************************************************************************
*
*   File Dialogs
*
*   MODULE USAGE:
*       #define GUI_FILE_DIALOGS_IMPLEMENTATION
*       #include "gui_file_dialogs.h"
*
*   On game draw call:  GuiFileDialog(...);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2019 raylib technologies (@raylibtech). All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#ifndef GUI_FILE_DIALOGS_H
#define GUI_FILE_DIALOGS_H

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// Dialog type
typedef enum DialogType {
    DIALOG_OPEN = 0,
    DIALOG_SAVE,
    DIALOG_MESSAGE,
    DIALOG_TEXTINPUT,
    DIALOG_OTHER
} DialogType;


#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
// Multiplatform file dialogs
// NOTE 1: fileName parameters is used to display and store selected file name
// NOTE 2: Value returned is the operation result, on custom dialogs represents button option pressed
// NOTE 3: filters and message are used for buttons and dialog messages on DIALOG_MESSAGE and DIALOG_TEXTINPUT
int GuiFileDialog(int dialogType, const char *title, char *fileName, const char *filters, const char *message);

#ifdef __cplusplus
}
#endif

#endif // GUI_FILE_DIALOGS_H


/***********************************************************************************
*
*   GUI_FILE_DIALOGS IMPLEMENTATION
*
************************************************************************************/

#if defined(GUI_FILE_DIALOGS_IMPLEMENTATION)

#include "raylib.h"     // Required for: TextSplit()

#if defined(PLATFORM_DESKTOP) && !defined(CUSTOM_MODAL_DIALOGS)
    #include "external/tinyfiledialogs.h"   // Required for: Native open/save file dialogs
#else
    #include "raygui.h"
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------

// Multiplatform file dialogs
int GuiFileDialog(int dialogType, const char *title, char *fileName, const char *filters, const char *message)
{
    int result = -1;

#if defined(CUSTOM_MODAL_DIALOGS)
    static char tempFileName[256] = { 0 };
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)), 0.85f));

    switch (dialogType)
    {
        case DIALOG_OPEN: /* TODO: Load file modal dialog */ break;
        case DIALOG_SAVE: /* TODO: Load file modal dialog */ break;
        case DIALOG_MESSAGE: result = GuiMessageBox((Rectangle){ GetScreenWidth()/2 - 120, GetScreenHeight()/2 - 60, 240, 120 }, GuiIconText(RICON_FILE_OPEN, title), message, filters); break;
        case DIALOG_TEXTINPUT: result = GuiTextInputBox((Rectangle){ GetScreenWidth()/2 - 120, GetScreenHeight()/2 - 60, 240, 120 }, GuiIconText(RICON_FILE_SAVE, title), message, filters, tempFileName); break;
        default: break;
    }
    
    if ((result == 1) && (tempFileName[0] != '\0')) strcpy(fileName, tempFileName);
    
#else   // Use native OS dialogs (tinyfiledialogs)

    const char *tempFileName = NULL;
    int filterCount = 0;
    const char **filterSplit = TextSplit(filters, ';', &filterCount);
    
    switch (dialogType)
    {
        case DIALOG_OPEN: tempFileName = tinyfd_openFileDialog(title, fileName, filterCount, filterSplit, message, 0); break;
        case DIALOG_SAVE: tempFileName = tinyfd_saveFileDialog(title, fileName, filterCount, filterSplit, message); break;
        case DIALOG_MESSAGE: result = tinyfd_messageBox(title, message, "ok", "info", 0); break;
        case DIALOG_TEXTINPUT: tempFileName = tinyfd_inputBox(title, message, ""); break;
        default: break;
    }

    if (tempFileName != NULL) 
    {
        strcpy(fileName, tempFileName);
        result = 1;
    }
    else result = 0;
#endif

    return result;
}

#endif // GUI_WINDOW_ABOUT_IMPLEMENTATION