
# define MY_TEXT_NUM_STEPS    5

# define  PORTRAIT_ROTATE(rot1base)           (rot1base & 1)
# define LANDSCAPE_ROTATE(rot1base)      (0 == (rot1base & 1))
# define ADA_LIB_ROTATE(rot1base)      ((rot1base - 1) & 3)

# define BACKGROUND_COLOR    ILI9341_BLACK

# define FIRST_LINE_COLOR    ILI9341_WHITE
//# define FIRST_LINE_TEXT   F("Lyle Monster!")
# define FIRST_LINE_TEXT     F("Len radio dev")
# define FIRST_LINE_SIZE     3

# define SECOND_LINE_COLOR   ILI9341_YELLOW
# define SECND_LINE_LONG     F("Freq:")
# define SECND_LINE_SHORT    F("Fq:")
# define SECOND_LINE_SIZE    5
# define SPACE_LINE_SIZE     3

# define THIRD_LINE_COLOR    ILI9341_GREEN
# define THIRD_LINE_TEXT     F("W1ZTL ")
# define THIRD_LINE_SIZE     4

# define FOURTH_LINE_COLOR   ILI9341_GREEN
# define FOURTH_LINE_TEXT    F("Workshop")
# define FOURTH_LINE_SIZE     3

# define DEBUG_TEXT_SIZE      1

