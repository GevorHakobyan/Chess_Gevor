#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include "Board.hpp"
#include "BarriersHandler.hpp"

class Dispatcher {
    public:
    using HandlerPtr = std::unique_ptr<Barriers_Handler>;
    using InvadingPath = std::vector<Location>;
    Dispatcher();
    Location determineKingLocation(const wchar_t*);
    virtual bool Dispatch(const Piece&) = 0;
    bool isKingAvailable(const Location&, const Color);
    bool SearchInAvailable_Coordinates(const Piece&, const Location&);
    InvadingPath getInvadingPath();
    virtual ~Dispatcher() = default;
    protected:
    std::optional<Location> SearchInRow(const PieceList&, const size_t, const wchar_t*);
    bool isPawn(const Piece&) const;
    bool isOnSameColum(const Location&, const Location&) const;
    protected:
    HandlerPtr m_Handler;
    InvadingPath m_InvadingPath;
};
#endif