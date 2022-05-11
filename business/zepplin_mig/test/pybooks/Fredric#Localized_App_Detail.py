## Section 1 : 


spark.sparkContext.addPyFile("s3://b2c-prod-dca-bdp-data/BDP-PROD-APP-INT-QA/bdp/user_data/application_name=aa_data_test_app/application_code/version=latest/code/bdp_resources/usr/lib/spark/python/dependencies.zip")

from data_lib.api import  spark_loader

loader = spark_loader(spark)
p_path = "s3://b2c-prod-data-pipeline-qa/fredric_localized_sample_apps/"
df = loader.load_parquet_as_table(p_path, "localized_detail_sample")

df1 = spark.sql("select date,country,app_id from localized_detail_sample limit 10")
df1.show(10)








    





## Section 2 : 

## Convert raw data to wide table

from  pyspark.storagelevel import StorageLevel
from pyspark.sql.functions import *

df = spark.read.parquet("s3://aardvark-prod-dca-data/interface/localized_app_detail/")

df.createOrReplaceTempView("raw_data")

raw_to_wide = '''

SELECT  date,
        country,
        app_id,
        platform,
        bundle_id,
        app_store_notes, banner_image_url, banner_md5, code, company_code, company_id, company_name, company_slug, release_date as current_release_date, description, features, first_release_date, icon_url, icon_md5, language_code, languages, replace(locale, '_', '-') as locale, name, permissions, coalesce(cast(price as  float),0.0) as price, primary_category_code, primary_category_id, promotional_text, release_notes, screenshots_json, screenshots_md5, file_size as size, slug, subtitle, version, status
    FROM raw_data  where date='2021-08-29' PIVOT (FIRST(value)
      FOR field_name IN ('app_store_notes', 'banner_image_url', 'banner_md5', 'code' ,'company_code', 'company_id', 'company_name', 'company_slug', 'release_date', 'description', 'features', 'first_release_date', 'icon_url', 'icon_md5', 'language_code', 'languages', 'locale', 'name', 'permissions', 'price', 'primary_category_code', 'primary_category_id', 'promotional_text', 'release_notes', 'screenshots_json', 'screenshots_md5', 'file_size', 'slug', 'subtitle', 'version', 'status'))
'''
df = spark.sql(raw_to_wide)
df.write.parquet("s3://b2c-prod-data-pipeline-qa/t_old_data")


## Section 3 : 


from data_lib.api import arrow_loader
from data_lib.utils.logger import logger

loader = arrow_loader() 
query = "select * from student order by grade asc"
df_table = loader.load_sf(query)
logger.error("NAME \t AGE \t GRADE")
for i in range(0, len(df_table)):
    logger.error(df_table["NAME"][i].as_py() + "\t" + str(df_table["AGE"][i].as_py()) + "\t" + str(df_table["GRADE"][i].as_py()))

## Section 4 : 


from data_lib.api import pd_loader
from data_lib.utils.logger import logger

loader = pd_loader() 
query = "select * from student order by grade asc"
df_table = loader.load_sf(query)
logger.error(df_table.head())


## Section 5 : 

spark.sparkContext.addPyFile("s3://b2c-prod-dca-bdp-data/BDP-PROD-APP-INT-QA/bdp/user_data/application_name=aa_data_test_app/application_code/version=latest/code/bdp_resources/usr/lib/spark/python/dependencies.zip")

from data_lib.api import pd_loader
from data_lib.utils.logger import logger

loader = pd_loader() 
query = "select * from student order by grade asc"
df_table = loader.load_aurora(query)
logger.error(df_table.head())

## Section 6 : 

from data_lib.api import  spark_loader
loader = spark_loader(spark)
p_path = "s3://b2c-prod-data-pipeline-qa/fredric_localized_sample_apps/"
df = loader.load_parquet_as_table(p_path, "localized_detail_sample")


## Section 7 : 

df = spark.read.parquet("s3://aardvark-prod-dca-data/fact/MKT_AD_REVENUE/version=1.0.0/range_type=WEEK")
# SQL  
df.createOrReplaceTempView("raw_data")

product_1_df = spark.sql("select * from raw_data where product_id=20600000112326")
product_1_df.show(100, False)



## Section 8 : 


SNOWFLAKE_SOURCE_NAME = "net.snowflake.spark.snowflake"

SF_OPTIONS = {
    "sfURL": "appannie_aa_int_prod.us-east-1.snowflakecomputing.com",
    "sfUser": "app_bdp_data_validation_qa",
    "sfPassword": "0HN#s@Wa5$1R8jVj",
    "sfDatabase": "AA_INTELLIGENCE_PRODUCTION",
    "sfWarehouse": "wh_dod_read7"
}

df = spark.read.format(SNOWFLAKE_SOURCE_NAME) \
            .options(**SF_OPTIONS) \
            .option("query", "select distinct(date) from AA_INTELLIGENCE_PRODUCTION.ADL_MARKET_PAID.FACT_MARKET_AD_REVENUE_FINAL_V1_CLUSTER_BY_DATE") \
            .load()

df.createOrReplaceTempView("snow_data")

df.show(10, False)


## Section 9 : 


spark.sparkContext.addPyFile("s3://b2c-prod-dca-bdp-data/BDP-PROD-APP-INT-QA/bdp/user_data/application_name=aa_data_test_app/application_code/version=latest/code/bdp_resources/usr/lib/spark/python/dependencies.zip")

from data_lib.api import  spark_loader

loader = spark_loader(spark)
df = loader.load_sf_as_table("select * from AA_INTELLIGENCE_PRODUCTION.ADL_MARKET_PAID.FACT_MARKET_AD_REVENUE_FINAL_V1_CLUSTER_BY_DATE limit 100000", "ad_revenue_final")
df_date = spark.sql("select distinct(date) from ad_revenue_final")
df_date.show(10)

## Section 10 : 



