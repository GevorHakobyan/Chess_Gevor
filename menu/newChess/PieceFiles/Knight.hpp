#ifndef  KNIGHT_HPP
#define  KNIGHT_HPP

#include "Piece.hpp"

class Knight : public Piece {
    public:
    Knight(const std::string& color, const wchar_t*, Location startLocation);
    void updateAvailableCoordinates() override;
    void setAvailableCoordinates() override;
    private:
    void setUpRight();
    void setUpLeft();
    void setDownRight();
    void setDownLeft();
    bool doesExist(Location);
};

#endif