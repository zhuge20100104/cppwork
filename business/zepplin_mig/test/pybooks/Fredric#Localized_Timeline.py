## Section 1 : 



## Convert narrow table to wide table

def narrow_to_wide(raw_table_name, data_range,  dst_s3_name):
    sql_date = '''
        select * from {} where date='{}' 
    '''.format(raw_table_name, data_range[0])
    

    df_date = spark.sql(sql_date)
    df_date.createOrReplaceTempView("df_date")
    raw_to_wide = '''
    
    SELECT  date,
            country,
            app_id,
            platform,
            bundle_id,
            app_store_notes, banner_image_url, banner_md5, code, company_code, company_id, company_name, company_slug, release_date as current_release_date, description, features, first_release_date, icon_url, icon_md5, language_code, languages, replace(locale, '_', '-') as locale, name, permissions, coalesce(cast(price as  float),0.0) as price, primary_category_code, primary_category_id, promotional_text, release_notes, screenshots_json, screenshots_md5, file_size as size, slug, subtitle, version, status
        FROM {} PIVOT (FIRST(value)
          FOR field_name IN ('app_store_notes', 'banner_image_url', 'banner_md5', 'code' ,'company_code', 'company_id', 'company_name', 'company_slug', 'release_date', 'description', 'features', 'first_release_date', 'icon_url', 'icon_md5', 'language_code', 'languages', 'locale', 'name', 'permissions', 'price', 'primary_category_code', 'primary_category_id', 'promotional_text', 'release_notes', 'screenshots_json', 'screenshots_md5', 'file_size', 'slug', 'subtitle', 'version', 'status'))
    '''
    
    raw_to_wide = raw_to_wide.format("df_date")
    df = spark.sql(raw_to_wide)
    dst_s3_path = "s3://b2c-prod-data-pipeline-qa/{}".format(dst_s3_name)
    df.write.mode("overwrite").parquet(dst_s3_path)


df = spark.read.parquet("s3://aardvark-prod-dca-data/interface/localized_app_detail/")
df.createOrReplaceTempView("raw")


narrow_to_wide("raw", ["2021-08-29"], "timeline_old")
narrow_to_wide("raw", ["2021-09-02"], "timeline_new")



## Section 2 : 


old_df = spark.read.parquet("s3://b2c-prod-data-pipeline-qa/timeline_old")
new_df = spark.read.parquet("s3://b2c-prod-data-pipeline-qa/timeline_new")

old_df.createOrReplaceTempView("old_df")
new_df.createOrReplaceTempView("new_df")

old_df.printSchema()

event_field_and_key_map = {
    "size": 15,
    "name": 3,
    "company_name": 33,
    "version": 1,
    "price": 2,
    "screenshots_md5": 40,
    "description": 39,
    "icon_md5": 12
}

event_df = None
for (field, event_key) in event_field_and_key_map.items():
    timeline_src_sql = '''
    select t1.*, new_value, {} as event_type_key from
        (select app_id as product_key, locale, country as country_key, platform, {} as old_value from old_df) t1
        left join 
        (select app_id as product_key, locale, country as country_key, platform, {} as new_value from new_df) t2
        on  
            t1.product_key = t2.product_key
            AND t1.locale = t2.locale
            AND t1.country_key = t2.country_key
            AND t1.platform = t2.platform
        where (t1.old_value != t2.new_value)
    '''.format(event_key, field, field)
    tmp_df = spark.sql(timeline_src_sql)
    if event_df is None:
        event_df = tmp_df
    else:
        event_df = event_df.union(tmp_df)

event_df.write.mode("overwrite").parquet("s3://b2c-prod-data-pipeline-qa/timeline_data")
    


print(event_df.count())

event_df.show(10, False)


## Section 3 : 



df = spark.read.parquet("s3://b2c-prod-data-pipeline-qa/timeline_data")
df.createOrReplaceTempView("timeline")
face_df = spark.sql("select count(distinct locale) from timeline where platform='Android'");
face_df.show(100, False)

## Section 4 : 


df = spark.read.parquet("s3://b2c-prod-data-pipeline-qa/timeline_data")
df.createOrReplaceTempView("timeline")


sql = '''
    select  distinct product_key as app_id,  country_key as country,locale
        from timeline
'''

df_raw_locale = spark.sql(sql)

# snowflake production
sfOptions = {
  "sfURL" : "appannie_aa_int_prod.us-east-1.snowflakecomputing.com",
  "sfUser" : "app_bdp_data_validation_qa",
  "sfPassword" : "0HN#s@Wa5$1R8jVj",
  "sfDatabase" : "AA_INTELLIGENCE_PRODUCTION",
  "sfSchema" : "ADL_MASTER",
  "sfWarehouse" : "wh_dod_read7"
}
SNOWFLAKE_SOURCE_NAME = "net.snowflake.spark.snowflake"
df_locale = spark.read.format(SNOWFLAKE_SOURCE_NAME) \
  .options(**sfOptions) \
  .option("query",  "select distinct product_key, language_code, country_code from AA_INTELLIGENCE_PRODUCTION.ADL_MASTER.dim_localized_event_service_v1_cluster_by_product_key ") \
  .load()


res_df = df_raw_locale.join(df_locale, on=[df_raw_locale['app_id']==df_locale['product_key'], df_raw_locale['country']==df_locale['country_code']], how="inner")

final_df =  res_df.filter("locale is not null and language_code is not null")
final_df.show(100)




## Section 5 : 



