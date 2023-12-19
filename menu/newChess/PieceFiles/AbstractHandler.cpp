#include "AbstractHandler.hpp"
#include <utility>

Handler* AbstractHandler::setNextHandler(Handler* handler) {
    this->m_nextHandler = handler;
    return handler;
}


bool AbstractHandler::handleRequest(const Piece& myPiece, const Location& myLocation) {
    if (this->m_nextHandler != nullptr) {
        return this->m_nextHandler->handleRequest(myPiece, myLocation);
    }
    return false;
}


