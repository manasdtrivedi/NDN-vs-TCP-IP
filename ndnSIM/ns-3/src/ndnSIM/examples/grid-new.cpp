/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2011-2015  Regents of the University of California.
 *
 * This file is part of ndnSIM. See AUTHORS for complete list of ndnSIM authors and
 * contributors.
 *
 * ndnSIM is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * ndnSIM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ndnSIM, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 **/

// ndn-grid.cpp

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/point-to-point-layout-module.h"
#include "ns3/ndnSIM-module.h"
#include "ns3/netanim-module.h"

namespace ns3 {

/**
 * This scenario simulates a grid topology (using PointToPointGrid module)
 *
 * (consumer) -- ( ) ----- ( )
 *     |          |         |
 *    ( ) ------ ( ) ----- ( )
 *     |          |         |
 *    ( ) ------ ( ) -- (producer)
 *
 * All links are 1Mbps with propagation 10ms delay.
 *
 * FIB is populated using NdnGlobalRoutingHelper.
 *
 * Consumer requests data from producer with frequency 100 interests per second
 * (interests contain constantly increasing sequence number).
 *
 * For every received interest, producer replies with a data packet, containing
 * 1024 bytes of virtual payload.
 *
 * To run scenario and see what is happening, use the following command:
 *
 *     NS_LOG=ndn.Consumer:ndn.Producer ./waf --run=ndn-grid
 */

int
main(int argc, char* argv[])
{
  // Setting default parameters for PointToPoint links and channels
  Config::SetDefault("ns3::PointToPointNetDevice::DataRate", StringValue("1Mbps"));
  Config::SetDefault("ns3::PointToPointChannel::Delay", StringValue("10ms"));
  Config::SetDefault("ns3::QueueBase::MaxSize", StringValue("10p"));
  
  std::string animFile = "grid-animation.xml";
  // Read optional command-line parameters (e.g., enable visualizer with ./waf --run=<> --visualize
  CommandLine cmd;
  cmd.AddValue ("animFile",  "File Name for Animation Output", animFile);
  cmd.Parse(argc, argv);

  // Creating 3x3 topology
  PointToPointHelper p2p;
  PointToPointGridHelper grid(3, 3, p2p);
  grid.BoundingBox(100, 100, 200, 200);

  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  ndnHelper.SetOldContentStore("ns3::ndn::cs::Freshness::Lru", "MaxSize","0"); // ! Attention ! If set to 0, then MaxSize is infinite
  // ndnHelper.setCsSize(100);

  ndnHelper.InstallAll();

  // Set BestRoute strategy
  ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/best-route");
                
// commented here
  // Installing global routing interface on all nodes
  // ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
  // ndnGlobalRoutingHelper.InstallAll();

  // Getting containers for the consumer/producer
  Ptr<Node> producer = grid.GetNode(2, 2);
  Ptr<Node> consumer = grid.GetNode(0, 0);

  if (consumer == 0 || 
  producer == 0) {
    NS_FATAL_ERROR("Error in topology: one nodes c,p is missing");
  }
  
  std::string room = "room";
  std::string prefix = "/room";

  prefix = "/data/" + room + "/" + Names::FindName(producer);

  // Install NDN applications


  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
  consumerHelper.SetPrefix(prefix);
  consumerHelper.SetAttribute("Frequency", StringValue("100")); // 100 interests a second
  consumerHelper.Install(consumer);

  ndn::AppHelper producerHelper("ns3::ndn::Producer");
  producerHelper.SetPrefix(prefix);
  producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
  producerHelper.Install(producer);


  //commented here
  // Add /prefix origins to ndn::GlobalRouter
  // ndnGlobalRoutingHelper.AddOrigins(prefix, producer);


  // Manually configure FIB routes
  ndn::FibHelper::AddRoute(grid.GetNode(0,0), "/data", grid.GetNode(0,1), 1); // link to n1
  ndn::FibHelper::AddRoute(grid.GetNode(0,0), "/data", grid.GetNode(1,0), 1); // link to n3
  ndn::FibHelper::AddRoute(grid.GetNode(0,1), "/data", grid.GetNode(0,2), 1);  // link to n2
  ndn::FibHelper::AddRoute(grid.GetNode(0,1), "/data", grid.GetNode(1,1), 1);  // link to n4
  ndn::FibHelper::AddRoute(grid.GetNode(0,2), "/data", grid.GetNode(1,2), 1);  // link to n5
  ndn::FibHelper::AddRoute(grid.GetNode(1,0), "/data", grid.GetNode(1,1), 1);  // link to n4
  ndn::FibHelper::AddRoute(grid.GetNode(1,0), "/data", grid.GetNode(2,0), 1);  // link to n6
  ndn::FibHelper::AddRoute(grid.GetNode(1,1), "/data", grid.GetNode(2,1), 1);  // link to n7
  ndn::FibHelper::AddRoute(grid.GetNode(2,0), "/data", grid.GetNode(2,1), 1);  // link to n7
  ndn::FibHelper::AddRoute(grid.GetNode(1,1), "/data", grid.GetNode(1,2), 1);  // link to n5

  ndn::FibHelper::AddRoute(grid.GetNode(2,1), "/data/room/p", grid.GetNode(2,2), 1);  // link to n2
  ndn::FibHelper::AddRoute(grid.GetNode(1,2), "/data/room/p", grid.GetNode(2,2), 1);  // link to n2

 // commented here 
 // Calculate and install FIBs
 // ndn::GlobalRoutingHelper::CalculateRoutes();

  // Create the animation object and configure for specified output
  AnimationInterface anim (animFile);

  Simulator::Stop(Seconds(20.0));

  Simulator::Run();
  Simulator::Destroy();

  return 0;
}

} // namespace ns3

int
main(int argc, char* argv[])
{
  return ns3::main(argc, argv);
}
