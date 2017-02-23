/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Map.h"

#include<mutex>

namespace ORB_SLAM2
{

Map::Map():mnMaxKFid(0),mnBigChangeIdx(0)
{
}

void Map::AddKeyFrame(KeyFrame *pKF)
{
    unique_lock<mutex> lock(mMutexMap);
    mspKeyFrames.insert(pKF);
    if(pKF->mnId>mnMaxKFid)
        mnMaxKFid=pKF->mnId;
}

void Map::AddMapPoint(MapPoint *pMP)
{
    unique_lock<mutex> lock(mMutexMap);
    mspMapPoints.insert(pMP);
}

void Map::EraseMapPoint(MapPoint *pMP)
{
    unique_lock<mutex> lock(mMutexMap);
    mspMapPoints.erase(pMP);

    // TODO: This only erase the pointer.
    // Delete the MapPoint
}

void Map::EraseKeyFrame(KeyFrame *pKF)
{
    unique_lock<mutex> lock(mMutexMap);
    mspKeyFrames.erase(pKF);

    // TODO: This only erase the pointer.
    // Delete the MapPoint
}

//------------------------------------------------------------------------
//for Sharing Map
void Map::AddKeyFrameShared(KeyFrame *pKFS)
{
    unique_lock<mutex> lock(mMutexMap);
    mspKeyFramesShared.insert(pKFS);
    if(pKFS->mnId>mnMaxKFid)
        mnMaxKFid=pKFS->mnId;
}

void Map::AddMapPointShared(MapPoint *pMPS)
{
    unique_lock<mutex> lock(mMutexMap);
    mspMapPointsShared.insert(pMPS);
}

void Map::EraseMapPointShared(MapPoint *pMPS)
{
    unique_lock<mutex> lock(mMutexMap);
    mspMapPointsShared.erase(pMPS);

    // TODO: This only erase the pointer.
    // Delete the MapPoint
}

void Map::EraseKeyFrameShared(KeyFrame *pKFS)
{
    unique_lock<mutex> lock(mMutexMap);
    mspKeyFramesShared.erase(pKFS);

    // TODO: This only erase the pointer.
    // Delete the MapPoint
}
//-----------------------------------------------------------------------

void Map::SetReferenceMapPoints(const vector<MapPoint *> &vpMPs)
{
    unique_lock<mutex> lock(mMutexMap);
    mvpReferenceMapPoints = vpMPs;
}

void Map::InformNewBigChange()
{
    unique_lock<mutex> lock(mMutexMap);
    mnBigChangeIdx++;
}

int Map::GetLastBigChangeIdx()
{
    unique_lock<mutex> lock(mMutexMap);
    return mnBigChangeIdx;
}

vector<KeyFrame*> Map::GetAllKeyFrames()
{
    unique_lock<mutex> lock(mMutexMap);
    return vector<KeyFrame*>(mspKeyFrames.begin(),mspKeyFrames.end());
}

vector<MapPoint*> Map::GetAllMapPoints()
{
    unique_lock<mutex> lock(mMutexMap);
    return vector<MapPoint*>(mspMapPoints.begin(),mspMapPoints.end());
}
//-----------------------------------------------------------------------
//for Sharing Map
vector<KeyFrame*> Map::GetAllKeyFramesShared()
{
    unique_lock<mutex> lock(mMutexMap);
    return vector<KeyFrame*>(mspKeyFramesShared.begin(),mspKeyFramesShared.end());
}

vector<MapPoint*> Map::GetAllMapPointsShared()
{
    unique_lock<mutex> lock(mMutexMap);
    return vector<MapPoint*>(mspMapPointsShared.begin(),mspMapPointsShared.end());
}
//-----------------------------------------------------------------------

long unsigned int Map::MapPointsInMap()
{
    unique_lock<mutex> lock(mMutexMap);
    return mspMapPoints.size();
}

long unsigned int Map::KeyFramesInMap()
{
    unique_lock<mutex> lock(mMutexMap);
    return mspKeyFrames.size();
}

//-----------------------------------------------------------------------
//for Sharing Map
long unsigned int Map::MapPointsSharedInMap()
{
    unique_lock<mutex> lock(mMutexMap);
    return mspMapPointsShared.size();
}

long unsigned int Map::KeyFramesSharedInMap()
{
    unique_lock<mutex> lock(mMutexMap);
    return mspKeyFramesShared.size();
}
//-----------------------------------------------------------------------

vector<MapPoint*> Map::GetReferenceMapPoints()
{
    unique_lock<mutex> lock(mMutexMap);
    return mvpReferenceMapPoints;
}

long unsigned int Map::GetMaxKFid()
{
    unique_lock<mutex> lock(mMutexMap);
    return mnMaxKFid;
}

void Map::clear()
{
    for(set<MapPoint*>::iterator sit=mspMapPoints.begin(), send=mspMapPoints.end(); sit!=send; sit++)
        delete *sit;

    for(set<KeyFrame*>::iterator sit=mspKeyFrames.begin(), send=mspKeyFrames.end(); sit!=send; sit++)
        delete *sit;

    mspMapPoints.clear();
    mspKeyFrames.clear();
    mnMaxKFid = 0;
    mvpReferenceMapPoints.clear();
    mvpKeyFrameOrigins.clear();
}

void Map::clearSharedMap()
{
    for(set<MapPoint*>::iterator sit=mspMapPointsShared.begin(), send=mspMapPointsShared.end(); sit!=send; sit++)
        delete *sit;

    for(set<KeyFrame*>::iterator sit=mspKeyFramesShared.begin(), send=mspKeyFramesShared.end(); sit!=send; sit++)
        delete *sit;

    mspMapPointsShared.clear();
    mspKeyFramesShared.clear();
    // mnMaxKFid = 0;
    // mvpReferenceMapPoints.clear();
    // mvpKeyFrameOrigins.clear();
}

} //namespace ORB_SLAM
