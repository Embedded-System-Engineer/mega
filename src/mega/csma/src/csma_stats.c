#include "inc/csma_internal.h"

// Statistics structure
typedef struct {
    uint32_t txFrames;
    uint32_t rxFrames;
    uint16_t collisions;
    uint16_t crcErrors;
    uint16_t retries;
} csmaStats_t;

static csmaStats_t stats;

void csmaStatsRecordTx(void) { stats.txFrames++; }
void csmaStatsRecordRx(void) { stats.rxFrames++; }
void csmaStatsRecordCollision(void) { stats.collisions++; }
void csmaStatsRecordCrcErr(void) { stats.crcErrors++; }
void csmaStatsRecordRetry(void) { stats.retries++; }

// Function to reset stats
void csmaStatsReset(void) {
    stats.txFrames = 0;
    stats.rxFrames = 0;
    stats.collisions = 0;
    stats.crcErrors = 0;
    stats.retries = 0;
}
