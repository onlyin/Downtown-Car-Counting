#ifndef _CAR_COUNTER_H_
#define _CAR_COUNTER_H_

#include "Blob.h"
#include "EastboundObjectIdentifier.h"
#include "WestboundObjectIdentifier.h"
#include "opencv2/core/core.hpp"
#include <vector>

class CarCounter {

public:
    CarCounter();

    void setOutputLogFile(const char * path) {
        logFilePath = path;
    }

    ~CarCounter();

    int getCarCount() {
        return carCount;
    }

    double getAvgSpeed(int numFrames);

    int classifyObjects(bool forceAll);

    int updateStats(std::vector<Blob>& blobs, long currentTime); //TODO: use timestamps instead?

private:
    ObjectIdentifier * getFit(Blob b, std::vector<ObjectIdentifier*> oi, long currentTime);

    double distanceThreshold;
    double expectedPathSlope;
    int carCount;
    int bikeCount;
    int streetcarCount;
    int xBoundary;
    bool useSlopeOfPathFilter;

    cv::Rect * boundaries;

    std::vector<EastboundObjectIdentifier*> eastboundObjects;
    std::vector<WestboundObjectIdentifier*> westboundObjects;
    std::vector<Blob> unidentifiedBlobs;

    std::vector<Blob> allBlobs;

    int rosCreated;

    int frameNumber;

    // Logging
    int writeToLog(const char * line);
    // Also deletes blobs after logging them
    void blobsToLogAndRemove(int numBlobs);
    FILE * logFile;
    const char * logFilePath;
    int writesToLog;

    const static int MIN_NUM_POINTS = 7;
    const static int MIN_FRAME_TIMEOUT = 5 * 10; // 10 seconds at 5 fps
    const static int MAX_FRAME_TIMEOUT = 5 * 60 * 2; // 2 minutes at 5 fps

    const static int NUM_POINTS_FOR_LINEAR_REGRESSION = 5;
    const static int NUM_POINTS_FOR_OVERLAP_CHECK = 2;
    const static int NUM_POINTS_TO_AVG = 5;
    const static double OVERLAP_PCT_THRESHOLD = 1; // 100%
    const static double NUM_PIXELS_LINEAR_REGRESSION_THRESHOLD = 5;
    const static double BOUNDS_THRESHOLD_PCT = 0.1;
    const static int VEHICLE_SIZE_THRESHOLD = 700;
    const static double SLOPE_FILTER_THRESHOLD = 0.1;
};

#endif
