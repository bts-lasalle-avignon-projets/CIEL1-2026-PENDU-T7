#include "controller.h"
#include "view.h"

#ifdef DEBUG_CONTROLLER
#include <iostream>
#endif

void jouer()
{
    std::string message = "Le jeu du PENDU va bientôt commencer !";

// exemple de débogage pour une variable
#ifdef DEBUG_CONTROLLER
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] "
              << "message = " << message << std::endl;
#endif

    afficherMessage(message);
}