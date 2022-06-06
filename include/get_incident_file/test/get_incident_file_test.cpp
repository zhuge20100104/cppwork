#include "get_incident_file/get_incident_file.h"

#include <gtest/gtest.h>

GTEST_TEST(GetIncidentFileTests, GetIncidentFile) {
    bool res = get_incident_file();
    ASSERT_TRUE(res);
}