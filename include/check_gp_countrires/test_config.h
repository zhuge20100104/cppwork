#ifndef _FREDRIC_TEST_CONFIG_H_
#define _FREDRIC_TEST_CONFIG_H_
#include <map>
#include <string>

#include "query_ele.h"

const std::string StoreProductRankPaidCase = "StoreProductRankPaidCase";
const std::string TopCompanyOverviewTableCase = "TopCompanyOverviewTableCase";
const std::string DownloadChannelTableCase = "DownloadChannelTableCase";

std::map<const std::string, QueryEle> TestEles{
    {StoreProductRankPaidCase,
     {"/ajax/v2/"
      "query?query_identifier=table_change%28top_apps%24gp_overview_paid%29",
      "store_product_rank_paid"}},
    {TopCompanyOverviewTableCase,
     {"/ajax/v2/"
      "query?query_identifier=table_change%28top_company_overview_table_v0_1%"
      "29",
      "top_company_overview_table"}},
    {DownloadChannelTableCase,
     {"/ajax/v2/"
      "query?query_identifier=table_change%28download_channel_table%29",
      "download_channel_table"}}};

#endif