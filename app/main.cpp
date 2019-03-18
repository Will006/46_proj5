// main.cpp
//
// ICS 46 Winter 2019
// Project #4: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.
#include <iostream>
#include "InputReader.hpp"
#include "Digraph.hpp"
#include "RoadMapReader.hpp"
#include "TripReader.hpp"
#include "TripMetric.hpp"
#include "RoadSegment.hpp"
#include "RoadMapWriter.hpp"
#include <vector>
#include <math.h>
#include <algorithm>
#include <functional>
#include <iomanip>
//#include <function>


//set precision for doubles at 2
//std::map<int,int> shortEdgeList ;
//std::vector<Trip>;
double totalTime=0, totalDist=0;
RoadMap mainMap;


void printInfoDist(int currentVertIn, int nextVertIn, std::map<int,int> currentEdgeList, Trip currentTripIn)
{
    if(nextVertIn!= currentTripIn.startVertex)
    {
        printInfoDist(nextVertIn,currentEdgeList.at(nextVertIn), currentEdgeList, currentTripIn);
            
    }
    //else
    {
       //compute time 
    
        double tempDist = (mainMap.edgeInfo(nextVertIn, currentVertIn)).miles;
        totalDist +=tempDist;

        std::cout<<"\tContiue to "<< mainMap.vertexInfo(currentVertIn)<<
        " ("<<(mainMap.edgeInfo(nextVertIn, currentVertIn)).miles<<" miles)\n";
    }
}

void printInfoTime(int currentVertIn, int nextVertIn, std::map<int,int> currentEdgeList, Trip currentTripIn)
{
    if(nextVertIn!= currentTripIn.startVertex)
    {
        printInfoTime(nextVertIn,currentEdgeList.at(nextVertIn), currentEdgeList, currentTripIn);
            
    }
    //else
    {
       //compute time 

        double tempTime = (3600*
                (mainMap.edgeInfo(nextVertIn, currentVertIn)).miles/
                ((mainMap.edgeInfo(nextVertIn, currentVertIn)).milesPerHour));
        totalTime += tempTime;
        int tempHrs = (int)(tempTime/3600);
        int tempMins = (int)(fmod(tempTime,3600)/60);
        double tempSecs = fmod(fmod(tempTime,3600),60);

        std::cout<<"\tContiue to "<< mainMap.vertexInfo(currentVertIn)<<
        " ("<<(mainMap.edgeInfo(nextVertIn, currentVertIn)).miles<<" miles & "<<
        (mainMap.edgeInfo(nextVertIn, currentVertIn)).milesPerHour<<"mph = ";

        if(tempHrs!=0)
        {
            std::cout<<tempHrs<<" hours ";
        }
        if(tempMins!=0)
        {
            std::cout<<tempMins<<" minutes ";
        }
        std::cout<<tempSecs<<" seconds)\n";
    }
}

int main()
{
    std::cout<<std::fixed<<std::setprecision(2);
    InputReader mainInputReader(std::cin);
    //Locations

    //ROAD SEGMENTS
    RoadMapReader mainRoadMapReader;
    //A roadMap is a Digraph<std::string, RoadSegment(edge)
    mainMap = mainRoadMapReader.readRoadMap(mainInputReader);
    
    
    
    
    //TRIPs    
    TripReader mainTripReader;
    
    //ar Trip has int start/endVertex and a TripMetric ("Time, Distance")
    std::vector<Trip> trips = mainTripReader.readTrips(mainInputReader);


//EdgeInfo is of type RoadSegment


    std::map<int,int> shortEdgeList;
    //for each trip, display the 
    for(int i=0; i<trips.size();i++)
    {
        totalTime=0;
        if(trips[i].metric == TripMetric::Time)
        {
            //compute the number of second it will take
            shortEdgeList = mainMap.findShortestPaths(
                trips[i].startVertex,
                [](RoadSegment edgeInfo)
                {return (3600*edgeInfo.miles/edgeInfo.milesPerHour);});
            //time compute
            
            //double totalTime =            int hrs
            //out put
            std::cout<<"Shortest driving time from "<<
            mainMap.vertexInfo(trips[i].startVertex)<<
            " to "<<mainMap.vertexInfo(trips[i].endVertex)<<":\n";

            std::cout<<"\tBeging at "<<mainMap.vertexInfo(trips[i].startVertex)<<"\n";
            int currentVert = trips[i].endVertex;
            int nextVert = shortEdgeList.at(currentVert);

            printInfoTime(currentVert, nextVert, shortEdgeList, trips[i]);
            //from the map you go from nextVertex to currentVert
            std::cout<<"Total time: ";
            int tempHrs = (int)(totalTime/3600);
            int tempMins = (int)(fmod(totalTime,3600)/60);
            double tempSecs = fmod(fmod(totalTime,3600),60);

            if(tempHrs!=0)
            {
                std::cout<<tempHrs<<" hours ";
            }
            if(tempMins!=0)
            {
                std::cout<<tempMins<<" minutes ";
            }
            std::cout<<tempSecs<<" seconds)\n\n";
        
        }
        else//distance
        {
            shortEdgeList = mainMap.findShortestPaths(
                trips[i].startVertex,
                [](RoadSegment edgeInfo){return edgeInfo.miles;});
            std::cout<<"Shortest distance from "<<
            "\n\nTEST:"<<trips[i].startVertex<<
            mainMap.vertexInfo(trips[i].startVertex)<<" to "<<
            mainMap.vertexInfo(trips[i].endVertex)<<":\n";
            
            std::cout<<"\tBeging at "<<mainMap.vertexInfo(trips[i].startVertex)<<"\n";
            int currentVert = trips[i].endVertex;
            int nextVert = shortEdgeList.at(currentVert);

            printInfoDist(currentVert, nextVert, shortEdgeList, trips[i]);
            //from the map you go from nextVertex to currentVert
            std::cout<<"Total distance: "<<totalDist<<" miles\n";


        }
    }
    return 0;
}

