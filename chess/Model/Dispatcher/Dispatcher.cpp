#include "Dispatcher.hpp"

Dispatcher::Dispatcher() {
    m_Handler = std::make_unique<Barriers_Handler>(Barriers_Handler());
}

bool Dispatcher::isKingAvailable(const Location& KingLocation, const Color enemyColor) {
    Board* m_Board{Board::getInstance()};
    const PieceList& pieceList {m_Board->getPieceList()};

    for (int i{0}; i < 8; ++i) {
        for (const auto& Piece : pieceList[i]) {
            if (Piece != nullptr && Piece.get()->getColor() == enemyColor) {
                if(SearchInAvailable_Coordinates(*Piece, KingLocation)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Dispatcher::SearchInAvailable_Coordinates(const Piece& myPiece, const Location& pieceLocation){
    if (isPawn(myPiece)) {
        if (isOnSameColum(myPiece.getCurrentLocation(), pieceLocation)) {
            return false;
        }
    }
    
    const AvailableCoordinates& m_Avaialble = myPiece.getAvailableCoordinates();
    for (const auto& coordinate : m_Avaialble) { 
        if (coordinate == pieceLocation) {
            if (m_Handler->handleRequest(myPiece, pieceLocation)) {
                m_InvadingPath = m_Handler->getInvadingPath();
                return true;
            } 
        }
    }
    return false;
}

Location Dispatcher::determineKingLocation(const wchar_t* King) {
    Board* m_Board{Board::getInstance()};
    const PieceList& pieceList {m_Board->getPieceList()};
    Location KingLocation; 

   for (int i{0}; i < 8; ++i) {
    std::optional<Location> KingLocation = SearchInRow(pieceList, i, King);
    if (KingLocation.has_value()) {
        return KingLocation.value();
    }
   }
}

bool Dispatcher::isPawn(const Piece& myPiece) const {
    const wchar_t* character = myPiece.getUnicodeCharacter();
    const wchar_t* blackPawn  = L"\u2659";
    const wchar_t* whitePawn  = L"\u265F";

    return (*character ==  *blackPawn || *character ==  *whitePawn) ? true : false;
}


bool Dispatcher::isOnSameColum(const Location& myLocation, const Location& KingLocation) const {
    return myLocation.second == KingLocation.second;
}

std::optional<Location> Dispatcher::SearchInRow(const PieceList& pieceList, const size_t i, const wchar_t* King) {
     std::optional<Location> KingLocation;

     for (const auto& Piece : pieceList[i]) {
        if (Piece != nullptr) {
            if (*Piece.get()->getUnicodeCharacter() == *King) {
                KingLocation = Piece.get()->getCurrentLocation();
                return KingLocation;
            }
        }
    }

    return std::nullopt;
}

Dispatcher::InvadingPath Dispatcher::getInvadingPath() {
    return m_InvadingPath;
}