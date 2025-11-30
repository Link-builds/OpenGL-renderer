#include "CApplication.h"

int main( void )
{
    Application app( funs::setup_viewport( "GOD IS GOOD", SCR_WIDTH, SCR_HEIGHT, 1 ) );

    app.run();

    return 0;
}
