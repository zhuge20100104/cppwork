# Download file

## Overview
    
This project is used to check whether a given URL is OK.

## Usage
1. Check out the CSV file from snowflake use the below SQL,
```
select product_key, old_value, new_value, change_time
    from  ADL_MASTER.DIM_EVENT_V2_CLUSTER_BY_PRODUCT_KEY
    where  event_type_name='artwork_url_change'
        and (old_value!='' and new_value!='' and old_value is not null and new_value is not null)
        and product_key=20600000009072
order by change_time desc;  
```

2.  Then modify the CSV file name in main.cpp and rebuild the whole project in build sub folder.
    You can build it as follows,

```
    cd build
    cmake ..
    make
```

3. Then run ./main. You will see the result for URL get. You can find the downloaded image files in ./build/images folder.
