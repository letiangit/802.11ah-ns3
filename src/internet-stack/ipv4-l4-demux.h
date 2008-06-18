// -*- Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*-
//
// Copyright (c) 2006 Georgia Tech Research Corporation
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation;
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// Author: George F. Riley<riley@ece.gatech.edu>
//

// Define the layer 4 demultiplexer object for ns3.
// George F. Riley, Georgia Tech, Fall 2006

#ifndef IPV4_L4_DEMUX_H
#define IPV4_L4_DEMUX_H

#include <list>
#include "ns3/object.h"
#include "ns3/ptr.h"

namespace ns3 {

class Ipv4L4Protocol;
class Node;

/**
 * \brief L4 Ipv4 Demux
 * 
 * This class demultiplexes IP datagrams to the correct layer four protocol
 * object.  This demux sits between IP and layer 4.
 */
class Ipv4L4Demux : public Object
{
public:
  static TypeId GetTypeId (void);
  Ipv4L4Demux ();
  virtual ~Ipv4L4Demux();

  void SetNode (Ptr<Node> node);

  /**
   * \param protocol a template for the protocol to add to this L4 Demux.
   * \returns the L4Protocol effectively added.
   *
   * Invoke Copy on the input template to get a copy of the input
   * protocol which can be used on the Node on which this L4 Demux 
   * is running. The new L4Protocol is registered internally as
   * a working L4 Protocol and returned from this method.
   * The caller does not get ownership of the returned pointer.
   */
  void Insert(Ptr<Ipv4L4Protocol> protocol);
  /**
   * \param protocolNumber number of protocol to lookup
   *        in this L4 Demux
   * \returns a matching L4 Protocol
   *
   * This method is typically called by lower layers
   * to forward packets up the stack to the right protocol.
   * It is also called from NodeImpl::GetUdp for example.
   */
  Ptr<Ipv4L4Protocol> GetProtocol(int protocolNumber);
  /**
   * \param protocol protocol to remove from this demux.
   *
   * The input value to this method should be the value
   * returned from the Ipv4L4Protocol::Insert method.
   */
  void Remove (Ptr<Ipv4L4Protocol> protocol);
protected:
  virtual void DoDispose (void);
private:
  typedef std::list<Ptr<Ipv4L4Protocol> > L4List_t;
  L4List_t m_protocols;
  Ptr<Node> m_node;
};

} //namespace ns3
#endif