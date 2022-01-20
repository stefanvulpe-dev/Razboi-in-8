extern FILE * fptr;

struct settings {
    int WIDTH, HEIGHT, GameBoard_SIZE, GameBoard_CELL_SIZE, GameBoard_BORDER_WIDTH, BUTTON_SIZE, BUTTON_MARGIN,
    PlayerA_TEXT_SIZE, PlayerB_TEXT_SIZE, TOP_LABEL_TEXT_SIZE, BOTTOM_LABEL_HEIGHT, UTILITY_BUTTON_WIDTH, UTILITY_BUTTON_HEIGHT, TITLE_WIDTH, TITLE_HEIGHT;
};

extern settings screenResolution;

void meniu();

void placeSoundButton(int xStart, int yStart, int xEnd, int yEnd);

void setari();

void initializeSizes();

void writeAndReadSettings();
