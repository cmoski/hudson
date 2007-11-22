/*
* Copyright (C) 2007, Alberto Giannetti
*
* This file is part of Hudson.
*
* Hudson is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Hudson is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Hudson.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _TRADER_HPP_
#define _TRADER_HPP_

#ifdef WIN32
#pragma warning (disable:4290)
#endif

// STL
#include <string>

// Boost
#include <boost/date_time/gregorian/gregorian.hpp>

// Hudson
#include "PositionSet.hpp"

class Price;


class TraderException: public std::exception
{
public:
  TraderException(const std::string& msg):
	  _Str("TraderException: ")
  {
    _Str += msg;
  }

  virtual ~TraderException(void) throw() { }
  virtual const char *what(void) const throw() { return _Str.c_str(); }

protected:
  std::string _Str;
};


class Trader
{
public:
  Trader(void);
  virtual ~Trader(void) { }

  /*!
  \brief Buy to open a new LongPosition.
  \param symbol The name of the LongPosition.
  \param dt Transaction date.
  \param price Transaction Price.
  \param size Transaction size.
  */
  Position::ID buy(const std::string& symbol, const boost::gregorian::date& dt, const Price& price, unsigned size = 1) throw(TraderException);  
  /*!
  \brief Buy to add to an existing LongPosition.
  \param id The LongPosition identifier.
  \param dt Transaction date.
  \param price Transaction Price.
  \param size Transaction size.
  */
  void buy(Position::ID id, const boost::gregorian::date& dt, const Price& price, unsigned size = 1) throw(TraderException);
  /*!
  \brief Sell to close or partially close an existing LongPosition.
  \param id The LongPosition identifier.
  \param dt Transaction date.
  \param price Transaction Price.
  \param size Transaction size.
  */
  void sell(Position::ID id, const boost::gregorian::date& dt, const Price& price, unsigned size = 1) throw(TraderException);

  /*!
  \brief Sell short to open a new ShortPosition.
  \param symbol The name of the ShortPosition.
  \param dt Transaction date.
  \param price Transaction Price.
  \param size Transaction size.
  */
  Position::ID sell_short(const std::string& symbol, const boost::gregorian::date& dt, const Price& price, unsigned size = 1) throw(TraderException);
  /*!
  \brief Sell short to open an existing ShortPosition.
  \param id The ShortPosition identifier.
  \param dt Transaction date.
  \param price Transaction Price.
  \param size Transaction size.
  */
  void sell_short(Position::ID, const boost::gregorian::date& dt, const Price& price, unsigned size = 1) throw(TraderException);
  /*!
  \brief Cover to close or partially close an existing ShortPosition.
  \param id The ShortPosition identifier.
  \param dt Transaction date.
  \param price Transaction Price.
  \param size Transaction size.
  */
  void cover(Position::ID, const boost::gregorian::date& dt, const Price& price, unsigned size = 1) throw(TraderException);
  
  /*!
  \brief Add a new StrategyPosition.
  \param symbol The name of the new StrategyPosition being added.
  \param pPos The first position added to the strategy.
  \see StrategyPosition.
  */
  Position::ID strategy(const std::string& symbol, PositionPtr pPos) throw(TraderException);

  /*!
  \brief Close an existing position of any type.
  \param id The Position unique identifier.
  \param dt Transaction date.
  \param price Transaction Price.
  */
  void close(Position::ID id, const boost::gregorian::date& dt, const Price& price) throw(TraderException);

  /*!
  \brief Return all the positions opened and closed by this Trader.
  */
  const PositionSet& positions(void) const { return _miPositions; }
  /*!
  \brief Return all positions opened and closed by this Trader for a specific symbol.
  \param symbol The name of the Position objects that will be returned.
  */
  PositionSet positions(const std::string& symbol);

protected:
  Position::ID _pid;
  PositionSet _miPositions;
};

#endif // _TRADER_HPP_
