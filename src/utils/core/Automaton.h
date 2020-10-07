/*
 * Copyright (C) 2020 DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/// 
/// \file   Automaton.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 7 octobre 2020, 12:50
///

#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <unordered_map>
#include <assert.h>


template <
  typename StateKey,
  typename TransiKey,
  typename State      = void,
  typename Transition = void, 
  typename StateHash    = std::hash<StateKey>, 
  typename StateEquals  = std::equal_to<StateKey>,
  typename TransiHash   = std::hash<TransiKey>, 
  typename TransiEquals = std::equal_to<TransiKey>>
class Automaton {
private:
  
  typedef std::pair<Transition,StateKey>                             Link;
  typedef std::unordered_map<TransiKey,Link,TransiHash,TransiEquals> LinkTable;
  typedef std::pair<State,LinkTable>                                 Node;
  typedef std::unordered_map<StateKey,Node,StateHash,StateEquals>    Graph;
  
  Graph     _graph;
  StateKey  _state;
  
public:
  
  void addState(const StateKey& key, const State& state) noexcept {
    auto res(_graph.emplace(key, std::make_pair(state,LinkTable())));
    assert(res.second);
  }
  
  void addNullTransition(
    const TransiKey& key, const Transition& transi, 
    const StateKey& state)
  noexcept {
    addTransition(key, transi, state, state);
  }
  
  void addTransition(
    const TransiKey& key, const Transition& transi, 
    const StateKey& stateFrom, const StateKey& stateTo) 
  noexcept {
    assert(_graph.find(stateFrom) != _graph.end());
    Node& from(_graph[stateFrom]);
    auto res(from.second.emplace(key, std::make_pair(transi,stateTo)));
    assert(res.second);
  }
  
  void setState(const StateKey& key) noexcept {
    assert(_graph.find(key) != _graph.end());
    _state = key;
  }
  
  std::pair<const StateKey&,const Node&> state() const noexcept {
    return std::make_pair(_state, _graph.at(_state));
  }
  
  const Transition& follow(const TransiKey& key) noexcept {
    assert(_graph[_state].second.find(key) != _graph[_state].second.end());
    const Link& link(_graph[_state].second[key]);
    _state = link.second;
    assert(_graph.find(_state) != _graph.end());
    return link.first;
  }
};

#endif /* AUTOMATON_H */

