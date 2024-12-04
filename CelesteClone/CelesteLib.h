#pragma once
#include <iostream>

//----------------------------------------------------------------------------------------------------------------------------

#define DEBUG_BREAK() __debugbreak()
#define SM_TRACE(msg, ...) _log("TRACE: ", msg, ETextColor::TEXT_COLOR_GREEN, ##__VA_ARGS__)
#define SM_WARN(msg, ...) _log("WARN: ", msg, ETextColor::TEXT_COLOR_YELLOW, ##__VA_ARGS__)
#define SM_ERROR(msg, ...) _log("ERROR: ", msg, ETextColor::TEXT_COLOR_RED, ##__VA_ARGS__)

#define ASSERT(cond, msg, ...)          \
{                                       \
    if (!(cond))                        \
    {                                   \
        SM_ERROR(msg, ##__VA_ARGS__);   \
        DEBUG_BREAK();                  \
    }                                   \
}

//----------------------------------------------------------------------------------------------------------------------------

#define VERIFY(cond, msg)                                   \
{                                                           \
    if (!(cond))                                            \
    {                                                       \
        std::cerr << "VERIFY failed: " << msg << std::endl; \
        DEBUG_BREAK();                                      \
    }                                                       \
}

//----------------------------------------------------------------------------------------------------------------------------

enum class ETextColor
{
    TEXT_COLOR_BLACK,
    TEXT_COLOR_RED,
    TEXT_COLOR_GREEN,
    TEXT_COLOR_YELLOW,
    TEXT_COLOR_BLUE,
    TEXT_COLOR_MAGENTA,
    TEXT_COLOR_CYAN,
    TEXT_COLOR_WHITE,
    TEXT_COLOR_COUNT
};

//----------------------------------------------------------------------------------------------------------------------------

template <typename... Args>
void _log(const char * prefix, const char * msg, ETextColor textColor, Args... args)
{
    static const char * TextColorTable[static_cast<int>(ETextColor::TEXT_COLOR_COUNT)] =
    {
        "\x1b[30m", // Black
        "\x1b[31m", // Red
        "\x1b[32m", // Green
        "\x1b[33m", // Yellow
        "\x1b[34m", // Blue
        "\x1b[35m", // Magenta
        "\x1b[36m", // Cyan
        "\x1b[37m", // White
    };

    char formatBuffer[8192] = {};
    sprintf_s(formatBuffer, sizeof(formatBuffer), "%s%s%s\033[0m", TextColorTable[static_cast<int>(textColor)], prefix, msg);

    char textBuffer[8192] = {};
    sprintf_s(textBuffer, sizeof(textBuffer), formatBuffer, args...);

    puts(textBuffer);
}

//----------------------------------------------------------------------------------------------------------------------------
// EOF
//----------------------------------------------------------------------------------------------------------------------------